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

#if defined(STACK_USE_ZEROCONF_LINK_LOCAL)
#include "TCPIP Stack/ZeroconfLinkLocal.h"
#endif
#if defined(STACK_USE_ZEROCONF_MDNS_SD)
#include "TCPIP Stack/ZeroconfMulticastDNS.h"
#endif

// Used for Wi-Fi assertions
#define WF_MODULE_NUMBER   WF_MODULE_MAIN_DEMO

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


// Writes an IP address to the LCD display and the UART as available

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
    g_isPSK_Ready = 0;

    // Initialize application specific hardware
    InitializeBoard();
  
    // Initialize stack-related hardware components that may be
    // required by the UART configuration routines
    TickInit();

#if defined(STACK_USE_MPFS2)
    MPFSInit();             // EEprom oor Flash Files System init
#endif

    // Initialize Stack and application related NV variables into AppConfig.
    InitAppConfig();

    putrsUART("\f");
    putrsUART("*** WiFi Wunder Weather Station ***\r\n\n");
    putrsUART("To restore factury defaults press and hold S1 for > 4 seconds during reset.\r\n");
    putrsUART("To enter configuration utility press and hold S1 for < 4 seconds during reset.\r\n\n");

    // Resets board to factory values if button is depressed on startup and allows UART based communication configuration
    if (BUTTON1_IO == 0u)
    {
#if defined(EEPROM_CS_TRIS) || defined(SPIFLASH_CS_TRIS)
        // Invalidate the EEPROM contents if BUTTON0 is held down for more than 4 seconds
        DWORD StartTime = TickGet();
        All_LEDS_off();

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

        DoUARTConfig(); // This is a RS232 based configuration option

    }
//  WX_perm_data_init_toDefault();  To force the default config during debugging
    WX_readPerm_data(); // Get the station NV data from EEprom
 
    putrsUART("User Name and Password:");
    putsUART(WX.Station.User_name);
    putrsUART(",");
    putsUART(WX.Station.password);
    putrsUART("\r\n\n");

    HP03_init(WX.Wunder.StationElev); // must be done after we read the WX_perm_data
    HIH6130_init();

    StackInit(); // Initialize core stack layers (MAC, ARP, TCP, UDP) and application modules (HTTP, SNMP, etc.)

#if defined(WF_CS_TRIS)
    WF_Connect();
#endif


#if defined(STACK_USE_ZEROCONF_LINK_LOCAL)
    ZeroconfLLInitialize();
#endif

#if defined(STACK_USE_ZEROCONF_MDNS_SD)
    mDNSInitialize(MY_DEFAULT_HOST_NAME);
    mDNSServiceRegister(
            (const char *) "DemoWebServer", // base name of the service
            "_http._tcp.local", // type of the service
            80, // TCP or UDP port, at which this service is available
            ((const BYTE *) "path=/index.htm"), // TXT info
            1, // auto rename the service when if needed
            NULL, // no callback function
            NULL // no application context
            );

    mDNSMulticastFilterRegister();
#endif


    putrsUART("\nInit complete... waiting for WiFi connection...\r\n");

    if (AppConfig.SecurityMode == WF_SECURITY_WPA_WITH_PASS_PHRASE ||
        AppConfig.SecurityMode == WF_SECURITY_WPA2_WITH_PASS_PHRASE ||
        AppConfig.SecurityMode == WF_SECURITY_WPA_AUTO_WITH_PASS_PHRASE)
    {
        putrsUART("Waiting for WPA Passphrase encryption.....\r\nThis takes about 1 Minute. Do not interrupt!.\r\n");
    }

    All_LEDS_off();
 
    // Begin of the co-operative multitasking loop.
    while (1)
    {
        // This task performs normal stack task including checking
        // for incoming packet, type of packet and calling
        // appropriate stack entity to process it.
        StackTask();

#if defined(WF_CS_TRIS)
        if (!WiFi_isConnected()) // if there is no WIFI connection there is no use to do anything else
        {
             DelayMs(25);// blink fast
             LED1_IO ^= 1;
             continue;
        }
#if defined (WF_USE_POWER_SAVE_FUNCTIONS)
#if !defined(MRF24WG)
        if (gRFModuleVer1209orLater)
#endif
            WiFiPowerSavingTask();
#endif
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
        HP03_Read_Process();    // Reads the Barometer pressure and temp
        HIH6130_Read_Process(); // Reads the Hygrometer
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


        // TODO: This should go somewhere else, i.e inside an event ??
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



