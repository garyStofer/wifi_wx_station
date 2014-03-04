/*************************************************************************
 *
 * Main file for WX-Wunder Station
 *
 *
 *************************************************************************/
#define THIS_IS_STACK_APPLICATION

// Include all headers for any enabled TCPIP Stack functions
#include "TCPIP Stack/TCPIP.h"
#include "APP_cfg.h"
#include "WX_perm_data.h"
#include "rtcc.h"
#include "Mail_Alarm.h"
#include "Main.h"
#include "HW_initialize.h"
#include "Once_per_second.h"
#include "Barometer.h"
#include "Hygrometer.h"


#if defined(WF_CS_TRIS) &&  !defined(MRF24WG)
 extern BOOL gRFModuleVer1209orLater;
#endif

// Application is written for C30 compiler and PIC24F family 
#if !defined (__C30__)
#error "This project needs to be compiled with a C30 compiler!"
#endif
#if !defined(__PIC24F__)
#error "This Project is for a PIC24F family device"
#endif

#if !defined(WF_CS_TRIS)
#error "This project requires a WiFi netwotk access controller"
#endif

#if defined(STACK_USE_ZEROCONF_LINK_LOCAL)
#include "TCPIP Stack/ZeroconfLinkLocal.h"
#endif
#if defined(STACK_USE_ZEROCONF_MDNS_SD)
#include "TCPIP Stack/ZeroconfMulticastDNS.h"
#endif

// Used for Wi-Fi assertions
#define WF_MODULE_NUMBER   WF_MODULE_MAIN_DEMO

/* BOOTLOADER stuff
        Store Boot loader delay timeout value & user reset vector at 0x100
        (can't be used with bootloader's vector protect mode).

        Value of userReset should match reset vector as defined in linker script.
        BLreset space must be defined in linker script.
*/
unsigned int userReset  __attribute__ ((space(prog),section(".BLreset"))) = 0xC00 ;
unsigned char BL_timeout  __attribute__ ((space(prog),section(".BLreset"))) = 0x0 ; // Boot loader listens for bootloader app on UART for "n" seconds
// End of Bootloader Stuff


// traps for system errors -- useful for debugging
 
void _ISR __attribute__((__no_auto_psv__))
_AddressError(void)
{
    Nop();
    Nop();
}

void _ISR __attribute__((__no_auto_psv__))
_StackError(void)
{
    Nop();
    Nop();
}
/* Interrupt service routine to handle the pin change notification interupt
 Change Notification is used to trigger mail alarms when a active high signal is detected on an active alarm
 input
 */
volatile unsigned short tmp;


void _ISR __attribute__((__no_auto_psv__))
_CNInterrupt(void)
{
    unsigned short alarms = 0;

    tmp = PORTD;


    // Alarms are triggert on active high signal on the enambed  alarm inputs

    if (( WX.Alarms.enable & 1<<1) && ALARM_1_input)
        alarms |= 1<<1;

    if ( (WX.Alarms.enable & 1<<2) && ALARM_2_input)
        alarms |= 1<<2;

    if ( (WX.Alarms.enable & 1<<3) && ALARM_3_input)
        alarms |= 1<<3;

    if ( (WX.Alarms.enable & 1<<4) && ALARM_4_input)
        alarms |= 1<<4;

    if ( (WX.Alarms.enable & 1<<5) && ALARM_5_input)
        alarms |= 1<<5;

   if (alarms )
     SMTP_set_alarm(alarms);

   IFS1bits.CNIF =0;
}
static void
Display_MAC_Addr( void )
{
    BYTE digit;
    BYTE i;

    putrsUART("MAC Address: ");

    for (i = 0; i < sizeof (MAC_ADDR); i++)
    {
        if (i)
            putcUART(':');
        digit = btohexa_high(AppConfig.MyMACAddr.v[i]);
        putcUART(digit);
        digit = btohexa_low(AppConfig.MyMACAddr.v[i]);
        putcUART(digit);

    }

    putrsUART("\r\n");
}


// Writes an IP address to the UART 
void
DisplayIPValue(IP_ADDR IPVal)
{
    //	printf("%u.%u.%u.%u", IPVal.v[0], IPVal.v[1], IPVal.v[2], IPVal.v[3]);

    BYTE IPDigit[4];
    BYTE i;

    for (i = 0; i < sizeof (IP_ADDR); i++)
    {
        uitoa((WORD) IPVal.v[i], IPDigit);
        putsUART((char *) IPDigit);

        if (i == sizeof (IP_ADDR) - 1)
            break;

        while (BusyUART())
            ;
        WriteUART('.');
    }

}

static void
Announce_My_IP_addr(void)
{
    static DWORD My_last_IP_addr = 0;

    // If the local IP address has changed (ex: due to DHCP lease change)
    // write the new IP address to the LCD display, UART, and Announce
    // service
    if (My_last_IP_addr != AppConfig.MyIPAddr.Val)
    {
        My_last_IP_addr = AppConfig.MyIPAddr.Val;
        putrsUART((ROM char*) "\r\nIP Address: ");
        DisplayIPValue(AppConfig.MyIPAddr);
        putrsUART((ROM char*) "\r\n");

#if defined(STACK_USE_ANNOUNCE)
        AnnounceIP(); // This is for the Microchip TCPIP discover tool
#endif

#if defined(STACK_USE_ZEROCONF_MDNS_SD)
        mDNSFillHostRecord();
#endif
    }
}

//
// Main application entry point.
//
short g_isPSK_Ready = 0;

main(void)
{
    unsigned short WiFi_con_watchdog;  // This is a work around for the problem when the WIFI board crashes and stops sending interrupts
    g_isPSK_Ready = 0;


    // Initialize application specific hardware
    InitializeBoard();
  
    // Initialize stack-related hardware components that may be
    // required by the UART configuration routines
    TickInit();

#if defined(STACK_USE_MPFS2)
    MPFSInit();             // EEprom or Flash Files System init
#endif

    // Initialize Stack and application related NV variables into AppConfig.
    InitAppConfig();

    putrsUART("\f");
    putrsUART("*** WiFi Wunder Weather Station ***\r\n\r\n");
    putrsUART("To restore factory defaults press and hold S1 for > 4 seconds during reset.\r\n");
    putrsUART("To enter configuration utility press and hold S1 for < 4 seconds during reset.\r\n\r\n");

  
    All_LEDS_off();

    // Resets board to factory values if button is depressed on startup and allows UART based communication configuration
    if (BUTTON1_IO == 0u)
    {
#if defined(EEPROM_CS_TRIS) || defined(SPIFLASH_CS_TRIS)
        // Invalidate the EEPROM contents if BUTTON0 is held down for more than 4 seconds
        DWORD StartTime = TickGet();

        while (BUTTON1_IO == 0u)
        {
            if (TickGet() - StartTime > 4 * TICK_SECOND)
            {

                putrsUART("\r\n\r\nButton S1 held for > 4 seconds.  Default settings restored.\r\n\r\n");

                while (BUTTON1_IO == 0u)
                {
                    DelayMs(100);
                    All_LEDS_on();
                    DelayMs(100);
                    All_LEDS_off();
                }

                InvalidateAppConfig();
                WX_perm_data_init_toDefault();
                Reset();
                break;
            }
        }

#endif
        LED2_IO = 1;
        DoUARTConfig(); // This is a RS232 based configuration option
        LED2_IO = 0;

    }

   
   
//  WX_perm_data_init_toDefault();  To force the default config during debugging
    WX_readPerm_data(); // Get the station NV data from EEprom

    Display_MAC_Addr( );
    putrsUART("User Name and Password:");
    putsUART(WX.Station.User_name);
    putrsUART(",");
    putsUART(WX.Station.password);
    putrsUART("\r\n");
    putrsUART("Netbios name: ");putsUART(AppConfig.NetBIOSName);
    putrsUART("\r\n\r\n");
   

    Baro_init(WX.Wunder.StationElev); // must be done after we read the WX_perm_data
    Hygro_init();

    StackInit(); // Initialize core stack layers (MAC, ARP, TCP, UDP) and application modules (HTTP, SNMP, etc.)

    WF_Connect();
    WiFi_con_watchdog = 0;
    putrsUART("\r\nInit complete... waiting for WiFi connection...\r\n");

    if (AppConfig.SecurityMode == WF_SECURITY_WPA_WITH_PASS_PHRASE ||
        AppConfig.SecurityMode == WF_SECURITY_WPA2_WITH_PASS_PHRASE ||
        AppConfig.SecurityMode == WF_SECURITY_WPA_AUTO_WITH_PASS_PHRASE)
    {
        putrsUART("Waiting for WPA Passphrase encryption.....\r\nThis takes about 1 Minute. Do not interrupt!.\r\n");
    }

 
    SMTP_Alarm_Arm( WX.Alarms.enable & 0x1); // ARM or Disarm
 
    // Begin of the co-operative multitasking loop.
    while (1)
    {
        // This task performs normal stack task including checking
        // for incoming packet, type of packet and calling
        // appropriate stack entity to process it.
        StackTask();        // StackTask also calls MACProcess which in tems calls WFProcess

        if (!WiFi_isConnected()) // if there is no WIFI connection there is no use to do anything else
        {
             DelayMs(25);// blink fast
             LED1_IO ^= 1;
             if ( WiFi_con_watchdog++ %1000 == 0)
                 putrsUART("... waiting for WiFi connection...\r\n");

             if ( WiFi_con_watchdog > 24000) // That's 10 minues worth of (25ms) delays with no connection
             {
                 putrsUART("WiFi connection failed to establish for 10 minutes -- Rebooting. \r\n");
                 Reset(); // This would get triggert in case there is no connection with a accesspoint for >10 min.
                          // This can also be the case if the Wifi Adapter crahes internally 
             }
             continue;
        }

#if defined (WF_USE_POWER_SAVE_FUNCTIONS)
#if !defined(MRF24WG)
        if (gRFModuleVer1209orLater)
#endif
            WiFiPowerSavingTask();
#endif


        // This tasks invokes each of the core stack application tasks
        StackApplications();
        Announce_My_IP_addr();      // For the TCPIP discover tool
#if defined(STACK_USE_ZEROCONF_LINK_LOCAL)
        ZeroconfLLProcess();
#endif

#if defined(STACK_USE_ZEROCONF_MDNS_SD)
        mDNSProcess();
        // Use this function to exercise service update function
        // HTTPUpdateRecord();
#endif

        SMTP_Mail_alarm();      // checks and sends mail alarms
        Baro_Read_Process();    // Reads the Barometer pressure and temp
        Hygro_Read_Process(); // Reads the Hygrometer
        NIST_DAYTIME_Client();  // Start One-shot to get time from a NIST server and periodically calls NIST again to update time

        if (WDIR_cal_tmp.DoWindDirCal)
        {
            Wind_dir_cal();
            continue;
        }

        if (RTC_1Sec_flag )     //  time yet
        {
            RTC_1Sec_flag = FALSE;
            Once_perSecTask();      // This is the main application task that starts measurements and computes readings and averages
        }

        WunderHttpClient();
        CWOP_Client();


        // TODO: This could go somewhere else, i.e inside an event ??
        if (g_isPSK_Ready)
        {
            g_isPSK_Ready = 0;
            //  This is to extract the computed encryption key  from the MRF24 module and to store it instead of the passphrase
            //   so that next time the device is rebooted it can connect without having to re-calculate it
            if (AppConfig.SecurityMode == WF_SECURITY_WPA_WITH_PASS_PHRASE ||
                    AppConfig.SecurityMode == WF_SECURITY_WPA2_WITH_PASS_PHRASE ||
                    AppConfig.SecurityMode == WF_SECURITY_WPA_AUTO_WITH_PASS_PHRASE)
            {
                tWFCPElements profile;
                UINT8 connState;
                UINT8 connID;

                putrsUART("Storing WPA encryption key for future use \r\n");

                WF_CMGetConnectionState(&connState, &connID);
                WF_CPGetElements(connID, &profile);
                AppConfig.SecurityKeyLength = 32;
                memcpy((char*) AppConfig.SecurityKey, (char*) profile.securityKey, AppConfig.SecurityKeyLength);
                AppConfig.SecurityMode--;
                SaveAppConfig(&AppConfig);
            }
        }

    } // end while for ever loop
}



