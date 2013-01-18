/*********************************************************************
 *
 *  Main Application Entry Point and TCP/IP Stack Demo
 *  Module for Microchip TCP/IP Stack
 *   -Demonstrates how to call and use the Microchip TCP/IP stack
 *	 -Reference: Microchip TCP/IP Stack Help (TCPIP Stack Help.chm)
 *
 *********************************************************************
 * FileName:        MainDemo.c
 * Dependencies:    TCPIP.h
 * Processor:       PIC18, PIC24F, PIC24H, dsPIC30F, dsPIC33F, PIC32
 * Compiler:        Microchip C32 v1.11b or higher
 *					Microchip C30 v3.24 or higher
 *					Microchip C18 v3.36 or higher
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 *
 * Copyright (C) 2002-2010 Microchip Technology Inc.  All rights
 * reserved.
 *
 * Microchip licenses to you the right to use, modify, copy, and
 * distribute:
 * (i)  the Software when embedded on a Microchip microcontroller or
 *      digital signal controller product ("Device") which is
 *      integrated into Licensee's product; or
 * (ii) ONLY the Software driver source files ENC28J60.c, ENC28J60.h,
 *		ENCX24J600.c and ENCX24J600.h ported to a non-Microchip device
 *		used in conjunction with a Microchip ethernet controller for
 *		the sole purpose of interfacing with the ethernet controller.
 *
 * You should refer to the license agreement accompanying this
 * Software for additional information regarding your rights and
 * obligations.
 *
 * THE SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT
 * WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT
 * LIMITATION, ANY WARRANTY OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * MICROCHIP BE LIABLE FOR ANY INCIDENTAL, SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF
 * PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, ANY CLAIMS
 * BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE
 * THEREOF), ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION, OR OTHER
 * SIMILAR COSTS, WHETHER ASSERTED ON THE BASIS OF CONTRACT, TORT
 * (INCLUDING NEGLIGENCE), BREACH OF WARRANTY, OR OTHERWISE.
 *
 * File Description:
 * Change History:
 * Rev   Description
 * ----  -----------------------------------------
 * 1.0   Initial release
 * V5.36 ---- STACK_USE_MPFS support has been removed 
 ********************************************************************/
/*
 * This macro uniquely defines this file as the main entry point.
 * There should only be one such definition in the entire project,
 * and this file must define the AppConfig variable as described below.
 */
#define THIS_IS_STACK_APPLICATION

// Include all headers for any enabled TCPIP Stack functions
#include "TCPIP Stack/TCPIP.h"
#include "APP_cfg.h"
#include "WX_perm_data.h"
#include "math.h"
#include "rtcc.h"
#include "Mail_Alarm.h"
#include "Main.h"
#include "wind_rain_cnt.h"


// needs to go into config space
#define TZ_OFFS (-8)

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

// Use UART2 instead of UART1 for stdout (printf functions).  Explorer 16 
// serial port hardware is on PIC UART2 module.
#if defined(EXPLORER_16) || defined(PIC24FJ256DA210_DEV_BOARD)
int __C30_UART = 2;
#endif

#if defined(WF_CS_TRIS) && !defined(MRF24WG)
extern BOOL gRFModuleVer1209orLater;
#endif

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

#if defined(WF_CS_TRIS)
// Global variables
UINT8 ConnectionProfileID;
#endif

#if defined(WF_CS_TRIS)

/*****************************************************************************
 * FUNCTION: WF_Connect
 *
 * RETURNS:  None
 *
 * PARAMS:   None
 *
 *  NOTES:   Connects to an 802.11 network.  Customize this function as needed 
 *           for your application.
 *****************************************************************************/
void
WF_Connect(void)
{
    UINT8 channelList[] = MY_DEFAULT_CHANNEL_LIST;

    /* create a Connection Profile */
    WF_CPCreate(&ConnectionProfileID);
    WF_SetRegionalDomain(MY_DEFAULT_DOMAIN);

    WF_CPSetSsid(ConnectionProfileID,
            AppConfig.MySSID,
            AppConfig.SsidLength);

    WF_CPSetNetworkType(ConnectionProfileID, MY_DEFAULT_NETWORK_TYPE);
    WF_CASetScanType(MY_DEFAULT_SCAN_TYPE);
    WF_CASetChannelList(channelList, sizeof (channelList));

    // The Retry Count parameter tells the WiFi Connection manager how many attempts to make when trying
    // to connect to an existing network.  In the Infrastructure case, the default is to retry forever so that
    // if the AP is turned off or out of range, the radio will continue to attempt a connection until the
    // AP is eventually back on or in range.  In the Adhoc case, the default is to retry 3 times since the 
    // purpose of attempting to establish a network in the Adhoc case is only to verify that one does not
    // initially exist.  If the retry count was set to WF_RETRY_FOREVER in the AdHoc mode, an AdHoc network
    // would never be established. 
    WF_CASetListRetryCount(MY_DEFAULT_LIST_RETRY_COUNT);
    WF_CASetEventNotificationAction(MY_DEFAULT_EVENT_NOTIFICATION_LIST);
    WF_CASetBeaconTimeout(MY_DEFAULT_BEACON_TIMEOUT);

#if defined(MRF24WG)

    if (gRFModuleVer1209orLater)
    {
        // If WEP security is used, set WEP Key Type.  The default WEP Key Type is Shared Key.
        if (AppConfig.SecurityMode == WF_SECURITY_WEP_40 || AppConfig.SecurityMode == WF_SECURITY_WEP_104)
        {
            WF_CPSetWepKeyType(ConnectionProfileID, MY_DEFAULT_WIFI_SECURITY_WEP_KEYTYPE);
        }
    }
    // Error check items specific to WPS Push Button mode
#if (MY_DEFAULT_WIFI_SECURITY_MODE==WF_SECURITY_WPS_PUSH_BUTTON)
#if !defined(WF_P2P)
    WF_ASSERT(strlen(AppConfig.MySSID) == 0); // SSID must be empty when using WPS
    WF_ASSERT(sizeof (channelList) == 11); // must scan all channels for WPS
#endif

#if (MY_DEFAULT_NETWORK_TYPE == WF_P2P)
    WF_ASSERT(strcmp((char *) AppConfig.MySSID, "DIRECT-") == 0);
    WF_ASSERT(sizeof (channelList) == 3);
    WF_ASSERT(channelList[0] == 1);
    WF_ASSERT(channelList[1] == 6);
    WF_ASSERT(channelList[2] == 11);
#endif
#endif    

#endif /* MRF24WG */

    WF_CPSetSecurity(ConnectionProfileID,
            AppConfig.SecurityMode,
            AppConfig.WepKeyIndex, /* only used if WEP enabled */
            AppConfig.SecurityKey,
            AppConfig.SecurityKeyLength);

#if MY_DEFAULT_PS_POLL == WF_ENABLED
    WF_PsPollEnable(TRUE);
#if !defined(MRF24WG) 
    if (gRFModuleVer1209orLater)
        WFEnableDeferredPowerSave();
#endif	/* !defined(MRF24WG) */
#else	/* MY_DEFAULT_PS_POLL != WF_ENABLED */
    WF_PsPollDisable();
#endif	/* MY_DEFAULT_PS_POLL == WF_ENABLED */

#ifdef WF_AGGRESSIVE_PS
#if !defined(MRF24WG)
    if (gRFModuleVer1209orLater)
        WFEnableAggressivePowerSave();
#endif
#endif

#if defined(STACK_USE_UART)  
    WF_OutputConnectionInfo(&AppConfig);
#endif

#if defined(DISABLE_MODULE_FW_CONNECT_MANAGER_IN_INFRASTRUCTURE)
    WF_DisableModuleConnectionManager();
#endif

#if defined(MRF24WG)
    WFEnableDebugPrint(ENABLE_WPS_PRINTS | ENABLE_P2P_PRINTS);
#endif
    WF_CMConnect(ConnectionProfileID);
}
#endif /* WF_CS_TRIS */

// Writes an IP address to the LCD display and the UART as available

void
DisplayIPValue(IP_ADDR IPVal)
{
    //	printf("%u.%u.%u.%u", IPVal.v[0], IPVal.v[1], IPVal.v[2], IPVal.v[3]);

    BYTE IPDigit[4];
    BYTE i;
#ifdef USE_LCD
    BYTE j;
    BYTE LCDPos = 16;
#endif

#if defined(STACK_USE_UART)
    putrsUART((ROM char*) "\r\nIP Address: ");
#endif
    for (i = 0; i < sizeof (IP_ADDR); i++)
    {
        uitoa((WORD) IPVal.v[i], IPDigit);

#if defined(STACK_USE_UART)
        putsUART((char *) IPDigit);
#endif

#ifdef USE_LCD
        for (j = 0; j < strlen((char*) IPDigit); j++)
        {
            LCDText[LCDPos++] = IPDigit[j];
        }
        if (i == sizeof (IP_ADDR) - 1)
            break;
        LCDText[LCDPos++] = '.';
#else
        if (i == sizeof (IP_ADDR) - 1)
            break;
#endif

#if defined(STACK_USE_UART)
        while (BusyUART());
        WriteUART('.');
#endif
    }

#ifdef USE_LCD
    if (LCDPos < 32u)
        LCDText[LCDPos] = 0;
    LCDUpdate();
#endif
#if defined(STACK_USE_UART)
    putrsUART((ROM char*) "\r\n");
#endif
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
        DisplayIPValue(AppConfig.MyIPAddr);

#if defined(STACK_USE_ANNOUNCE)
        AnnounceIP(); // This is for the Microchip TCPIP discover tool
#endif

#if defined(STACK_USE_ZEROCONF_MDNS_SD)
        mDNSFillHostRecord();
#endif
    }
}

/****************************************************************************
  Function:
    static void InitializeBoard(void)

  Description:
    This routine initializes the hardware.  It is a generic initialization
    routine for many of the Microchip development boards, using definitions
    in HardwareProfile.h to determine specific initialization.

  Precondition:
    None

  Parameters:
    None - None

  Returns:
    None

  Remarks:
    None
 ***************************************************************************/
static void
InitializeBoard(void)
{

    // TODO: need to change this code to be specific to the final WX board, rather than Exlorer 16
#if defined(EXPLORER_16)
    // LEDs
    LED0_TRIS = 0;
    LED1_TRIS = 0;
    LED2_TRIS = 0;
    LED3_TRIS = 0;
    LED4_TRIS = 0;
    LED5_TRIS = 0;
    LED6_TRIS = 0;
    LED7_TRIS = 0;
    LED_PUT(0x00);

    CLKDIVbits.RCDIV = 0; // Set 1:1 8MHz FRC postscalar

    // ADC
    AD1CON1bits.ADON = 0; // diable during configuration

#if defined(__PIC24FJ256DA210__) || defined(__PIC24FJ256GB210__)
    // Disable analog on all pins
    ANSA = 0x0000;
    ANSB = 0x0000;
    ANSC = 0x0000;
    ANSD = 0x0000;
    ANSE = 0x0000;
    ANSF = 0x0000;
    ANSG = 0x0000;
#else

    AD1CHSbits.CH0NA = 0; // V- for mux A (-) inputs
    AD1PCFGbits.PCFG0 = 0; // Disable digital input on AN0
    AD1PCFGbits.PCFG1 = 0; // Disable digital input on AN1
//    AD1PCFGbits.PCFG2 = 0; // Disable digital input on AN2
//    AD1PCFGbits.PCFG3 = 0; // Disable digital input on AN3
//    AD1PCFGbits.PCFG4 = 0; // Disable digital input on AN4
    AD1PCFGbits.PCFG5 = 0; // Disable digital input on AN5
//    AD1PCFGbits.PCFG6 = 0; // Disable digital input on AN6
//    AD1PCFGbits.PCFG7 = 0; // Disable digital input on AN7

#endif
    // ADC
    AD1CON1bits.FORM = 0; // data form is unsigned integer
    AD1CON1bits.SSRC = 0x7; // conversion trigger internal counter/ autoconvert
    AD1CON1bits.ASAM = 1; // A/D Sample Auto-Start Mode  1 = Sampling begins immediately after last conversion
    // AD1CON1bits.ADON = 1; // enable the device
    // AD1CON1 = 0x84E4; // Turn on, auto sample start, auto-convert, 12 bit mode (on parts with a 12bit A/D)
    AD1CON2bits.VCFG = 0; // use Vdd and Vss for reference
    AD1CON2bits.CSCNA = 1; // Use channel scan register to select inputs for MUXA
    AD1CON2bits.ALTS = 0; // Do not alternate between MUX A and B
    AD1CON2bits.SMPI = 3; // interrupt every secend conversion --- NOT sure if this is needed since no interrupt is used
    // AD1CON2 = 0x0404; // AVdd, AVss, int every 2 conversions, MUXA only, scan

    AD1CON3 = 0x1003; // 16 Tad auto-sample, Tad = 3*Tcy

    AD1CSSL = 0;
    AD1CSSLbits.CSSL0 = 1; // AN0
    AD1CSSLbits.CSSL1 = 1; // AN1
  //  AD1CSSLbits.CSSL2 = 1; // AN2
  //  AD1CSSLbits.CSSL3 = 1; // AN3
  //  AD1CSSLbits.CSSL4 = 1; // AN4
    AD1CSSLbits.CSSL5 = 1; // AN5 -- the potentiometer
  // AD1CSSLbits.CSSL6 = 1; // AN6
  // AD1CSSLbits.CSSL7 = 1; // AN7
    AD1CON1bits.ADON = 1; // enable the device


    // UART
#if defined(STACK_USE_UART)
    UARTTX_TRIS = 0;
    UARTRX_TRIS = 1;
    UMODE = 0x8000; // Set UARTEN.  Note: this must be done before setting UTXEN
    USTA = 0x0400; // UTXEN set

#define CLOSEST_UBRG_VALUE ((GetPeripheralClock()+8ul*BAUD_RATE)/16/BAUD_RATE-1)
#define BAUD_ACTUAL (GetPeripheralClock()/16/(CLOSEST_UBRG_VALUE+1))
#define BAUD_ERROR ((BAUD_ACTUAL > BAUD_RATE) ? BAUD_ACTUAL-BAUD_RATE : BAUD_RATE-BAUD_ACTUAL)
#define BAUD_ERROR_PRECENT	((BAUD_ERROR*100+BAUD_RATE/2)/BAUD_RATE)

#if (BAUD_ERROR_PRECENT > 3)
#warning UART frequency error is worse than 3%
#elif (BAUD_ERROR_PRECENT > 2)
#warning UART frequency error is worse than 2%
#endif

    UBRG = CLOSEST_UBRG_VALUE;
#endif



    // Deassert all chip select lines so there isn't any problem with
    // initialization order.  Ex: When ENC28J60 is on SPI2 with Explorer 16,

#if defined(EEPROM_CS_TRIS)
    EEPROM_CS_IO = 1;
    EEPROM_CS_TRIS = 0;
#endif

#if defined(WF_CS_TRIS)
    WF_CS_IO = 1;
    WF_CS_TRIS = 0;
#endif

#if defined(__PIC24FJ256DA210__)
    __builtin_write_OSCCONL(OSCCON & 0xBF); // Unlock PPS

    // Inputs
    RPINR19bits.U2RXR = 11; // U2RX = RP11
    RPINR20bits.SDI1R = 0; // SDI1 = RP0
    RPINR0bits.INT1R = 34; // Assign RE9/RPI34 to INT1 (input) for MRF24W Wi-Fi PICtail Plus interrupt

    // Outputs
    RPOR8bits.RP16R = 5; // RP16 = U2TX
    RPOR1bits.RP2R = 8; // RP2 = SCK1
    RPOR0bits.RP1R = 7; // RP1 = SDO1

    __builtin_write_OSCCONL(OSCCON | 0x40); // Lock PPS
#endif

#if defined(__PIC24FJ256GB110__) || defined(__PIC24FJ256GB210__)
    __builtin_write_OSCCONL(OSCCON & 0xBF); // Unlock PPS

    // Configure SPI1 PPS pins (ENC28J60/ENCX24J600/MRF24W or other PICtail Plus cards)
    RPOR0bits.RP0R = 8; // Assign RP0 to SCK1 (output)
    RPOR7bits.RP15R = 7; // Assign RP15 to SDO1 (output)
    RPINR20bits.SDI1R = 23; // Assign RP23 to SDI1 (input)

    // Configure SPI2 PPS pins (25LC256 EEPROM on Explorer 16)
    RPOR10bits.RP21R = 11; // Assign RG6/RP21 to SCK2 (output)
    RPOR9bits.RP19R = 10; // Assign RG8/RP19 to SDO2 (output)
    RPINR22bits.SDI2R = 26; // Assign RG7/RP26 to SDI2 (input)

    // Configure UART2 PPS pins (MAX3232 on Explorer 16)
#if !defined(ENC100_INTERFACE_MODE) || (ENC100_INTERFACE_MODE == 0) || defined(ENC100_PSP_USE_INDIRECT_RAM_ADDRESSING)
    RPINR19bits.U2RXR = 10; // Assign RF4/RP10 to U2RX (input)
    RPOR8bits.RP17R = 5; // Assign RF5/RP17 to U2TX (output)
#endif

    // Configure INT1 PPS pin (MRF24W Wi-Fi PICtail Plus interrupt signal when in SPI slot 1)
    RPINR0bits.INT1R = 33; // Assign RE8/RPI33 to INT1 (input)

    // Configure INT3 PPS pin (MRF24W Wi-Fi PICtail Plus interrupt signal when in SPI slot 2)
    RPINR1bits.INT3R = 40; // Assign RC3/RPI40 to INT3 (input)

    __builtin_write_OSCCONL(OSCCON | 0x40); // Lock PPS
#endif

#if defined(__PIC24FJ256GA110__)
    __builtin_write_OSCCONL(OSCCON & 0xBF); // Unlock PPS

    // Configure SPI2 PPS pins (25LC256 EEPROM on Explorer 16 and ENC28J60/ENCX24J600/MRF24W or other PICtail Plus cards)
    // Note that the ENC28J60/ENCX24J600/MRF24W PICtails SPI PICtails must be inserted into the middle SPI2 socket, not the topmost SPI1 slot as normal.  This is because PIC24FJ256GA110 A3 silicon has an input-only RPI PPS pin in the ordinary SCK1 location.  Silicon rev A5 has this fixed, but for simplicity all demos will assume we are using SPI2.
    RPOR10bits.RP21R = 11; // Assign RG6/RP21 to SCK2 (output)
    RPOR9bits.RP19R = 10; // Assign RG8/RP19 to SDO2 (output)
    RPINR22bits.SDI2R = 26; // Assign RG7/RP26 to SDI2 (input)

    // Configure UART2 PPS pins (MAX3232 on Explorer 16)
    RPINR19bits.U2RXR = 10; // Assign RF4/RP10 to U2RX (input)
    RPOR8bits.RP17R = 5; // Assign RF5/RP17 to U2TX (output)

    // Configure INT3 PPS pin (MRF24W PICtail Plus interrupt signal)
    RPINR1bits.INT3R = 36; // Assign RA14/RPI36 to INT3 (input)

    __builtin_write_OSCCONL(OSCCON | 0x40); // Lock PPS
#endif

#if defined(EEPROM_CS_TRIS)
    XEEInit();
#endif

#if defined(USE_LCD)
    // Initialize and display the stack version on the LCD
    LCDInit();
    strcpypgm2ram((char*) LCDText, "TCPStack " TCPIP_STACK_VERSION "  "
            "Waiting for WiFi");
    LCDUpdate();
#endif

#endif
}
/* 
 *  This task executes onec per second and collects the stations sensor readings
 */
static struct tagWind_avg {
    float NS_comp;
    float EW_comp;
    float Spd;
} Wind_avg[WX_UPLINK_INTERVAL] = {0};
static unsigned char RAIN_Count_Samples[RAIN_SAMPLES_P_HOUR] = {0};
static unsigned short rain_sample_ndx = 0;

static void
Once_perSecTask(void)
{
    static unsigned short sec_count = 0;        // Count will wrap around
    short s_tmp;
    float max, sum_NS, sum_EW, sum_spd, f_tmp;
    int i;

    if (RTC_1Sec_flag == FALSE) // not time yet
        return;

    RTC_1Sec_flag = FALSE; // clear for next time around

    // start the daily rain accumulation at midnight.
    if (RTC_isMidnight(RTC_Read_BCD_Time(),TZ_OFFS))        // this also reads the RTC every one second
    {
        SensorReading.RainDaily =0.0;
        NIST_TimeSyncRequest();                             // Daily refres the RTC with NIST time
    }

    // Blink LED0 (right most one) every second.
    LED0_IO ^= 1;

    if (sec_count % BARO_HYG_TEMP_MEAS_Interval == 0)
    {
        HIH6130_startMeasure();
        HP03_startMeasure();
    }

    if (sec_count % RAIN_MEAS_Interval == 0)
    {
        s_tmp = RAIN_COUNTER;
        RAIN_COUNTER=0;
        RAIN_Count_Samples[rain_sample_ndx++] = s_tmp;
        SensorReading.RainDaily += s_tmp/(float) WX.Calib.Rain_counts;

        if ( rain_sample_ndx >= RAIN_SAMPLES_P_HOUR )
             rain_sample_ndx =0;
        
       // sum up all the individual Rain counts for the last hour to calculate the rain amounth in inches that fell over the last hour
        s_tmp = 0;
        for (i = 0; i < RAIN_SAMPLES_P_HOUR; i++)
        {
            s_tmp += RAIN_Count_Samples[i];
        }
       
       SensorReading.RainIn =   s_tmp  / (float) WX.Calib.Rain_counts;
       
     }

    SensorReading.SolRad = (short) (((float) ADC1BUF1 * WX.Calib.Sol_gain) / 1000.0);

    // The Wind Speed:
    // Davis Cup anemometer conversion to MPH is 2.25 x revolution/sec
    // The wind speed data is aquired as follows:
    // The RTCC ISR captures counter/Timer2 once per second and stores the reading in Var Wind_1Sec_count
    // The Once_perSecond task executes once following a one second RTCC tic change.
    // The one second momentary wind spead is calculated and added to an averaging array that spans the entire duration
    // of the update interval.
    // The average and peak values for the update interval are calculated and reported to Wunderground, while the momentary data
    // is reported on the stations local display.
    // The 10 minute peak gust could be calculated and reported to Wunderground, but it seems that they do not record or display it

    // convert counts to MPH, since the measure window is 1 seconds and there are 7 pulses per revolution
    // the following formual gives MPH in  miles resolution
    // MPH = wind_counts_per_sec  *2.25 /7;
    // or MPH = wind_counts_per_sec * 0.32142
    Wind_avg[sec_count%WX_UPLINK_INTERVAL].Spd = SensorReading.Wind_speed = Wind_1Sec_count * AN_CAL_FACTOR; // momentary wind speed

    //SensorReading.Wind_gust is the maximum of the individual wind speed samples in WX_UPLINK_INTERVAL
    max = 0.0;
    for (i = 0; i < WX_UPLINK_INTERVAL; i++)
    {
        if (Wind_avg[i].Spd > max)
            max = Wind_avg[i].Spd;
    }
    SensorReading.Wind_gust = max;


    // The Wind direction
    // the PWM of the wind-vane does not fully go between 0 and 100 %PWM i.e not fully between DC 0V and DC 5V
    // With a voltage divider 6.8K/12.6K the lowest ADC reading is 4 counts when pointing at 0Deg
    // and the highest is 970 when pointing at 359.99 deg

    //  Wind_dir =  (ADC1BUF0-4)* 360.0 /970; // calculating degress while compensating for the ~1-99% of the PWM
    s_tmp = (ADC1BUF0 - 4)* 360.0 / 970; // This is from the PWM of the magnetic rotary encoder

    // precautions
    if (s_tmp > 360)
        s_tmp = 360;
    else if (s_tmp < 0)
        s_tmp = 0;

    SensorReading.Wind_dir = (s_tmp + WX.Calib.WDir_offs) % 360; // Momentary wind diretion
    f_tmp = SensorReading.Wind_dir * 6.2832 / 360.0; // convert to radians
    // Vector addition of NS and EW wind vector samples for average calculation
    Wind_avg[sec_count%WX_UPLINK_INTERVAL].NS_comp = cos(f_tmp) * SensorReading.Wind_speed;
    Wind_avg[sec_count%WX_UPLINK_INTERVAL].EW_comp = sin(f_tmp) * SensorReading.Wind_speed;

    // Average and Peak calculation for WX_UPLINK_INTERVAL/Sec
    // Pre-increment so that it runs for WX_UPLINK_INTERVAL before data is sent to wunderground
    if (++sec_count % WX_UPLINK_INTERVAL == 0)
    {
        // Calculate the average wind direction from the NS and EW vectors
        sum_spd = sum_NS = sum_EW = 0.0;
        for (i = 0; i < WX_UPLINK_INTERVAL; i++)
        {
            sum_NS += Wind_avg[i].NS_comp;
            sum_EW += Wind_avg[i].EW_comp;
            sum_spd += Wind_avg[i].Spd;
        }

        SensorReading.AvgWindSpd = sum_spd / i; // The linear average of the speed in interval
        f_tmp = atan2(sum_EW, sum_NS); // the vector average of the direction -- using atan2() to get the 4 quadrands resolved automaticaly
        SensorReading.AvgWindDir = f_tmp * 360 / 6.2832; // Convert to deg
        if (SensorReading.AvgWindDir < 0)
            SensorReading.AvgWindDir += 360;

        WunderSendData(); // starts the HTTP client process to send data to Wunderground
     }

    // read time and display
#ifdef  notused
#if defined(USE_LCD)
    BCD_RTCC *time;
    if ((time = RTC_Read_BCD_Time()) != NULL)
    {
        strcpy((char*) LCDText, (char *) (RTC_Convert_BCD_Time_to_String(time)));
        strcat((char*) LCDText, RTC_Convert_BCD_Date_to_String(time));
        LCDUpdate();

    }
#endif
#endif
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
    WindCounterInit();
    RainCounterInit();
    RTC_Init();         // Real Time Clock init



    // Initialize stack-related hardware components that may be
    // required by the UART configuration routines
    TickInit();
#if defined(STACK_USE_MPFS2)
    MPFSInit();             // EEprom oor Flash Files System init
#endif

    // Initialize Stack and application related NV variables into AppConfig.
    InitAppConfig();

    // Initiates board to factory values if button is depressed on startup
    // and allows UART based communication configuration
    if (BUTTON0_IO == 0u)
    {
#if defined(EEPROM_CS_TRIS) || defined(SPIFLASH_CS_TRIS)
        // Invalidate the EEPROM contents if BUTTON0 is held down for more than 4 seconds
        DWORD StartTime = TickGet();
        LED_PUT(0x00);

        while (BUTTON0_IO == 0u)
        {
            if (TickGet() - StartTime > 4 * TICK_SECOND)
            {
#if defined(STACK_USE_UART)
                putrsUART("\r\n\r\nButton A held for > 4 seconds.  Default settings restored.\r\n\r\n");
#endif
                while (BUTTON0_IO == 0u)
                {
                    DelayMs(100);
                    LED_PUT(0x0F);
                    DelayMs(100);
                    LED_PUT(0x00);
                }

                InvalidateAppConfig();
                WX_perm_data_init_toDefault();
                Reset();
                break;
            }
        }

#endif
#if defined(STACK_USE_UART)
        // TODO: I'm not sure how useful this actually is anymore
        // possibly delete to make room in flash        --
        DoUARTConfig(); // This is a RS232 based configuration option
#endif
    }

    WX_readPerm_data(); // Get the station NV data from EEprom

    HP03_init(WX.Wunder.StationElev); // must be done after we read the WX_perm_data

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
#if defined(STACK_USE_UART)
    putrsUART((ROM char*) "Init complete... waiting for wifi connection...\r\n");

    if (AppConfig.SecurityMode == WF_SECURITY_WPA_WITH_PASS_PHRASE ||
            AppConfig.SecurityMode == WF_SECURITY_WPA2_WITH_PASS_PHRASE ||
            AppConfig.SecurityMode == WF_SECURITY_WPA_AUTO_WITH_PASS_PHRASE)
    {
        putrsUART((ROM char*) "Waiting for WPA Passphrase encryption, takes 30sec.\r\n");
    }
#endif

    // Begin the co-operative multitasking loop.
    while (1)
    {
        // This task performs normal stack task including checking
        // for incoming packet, type of packet and calling
        // appropriate stack entity to process it.
        StackTask();

#if defined(WF_CS_TRIS)
        if (!WiFi_isConnected()) // if there is no WIFI connection there is no use to do anything else
            continue;
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
        Once_perSecTask();      // This is the main application task that starts measurements and computes readings and averages
        NIST_DAYTIME_Client();  // Start One-shot to get time from a NIST server,
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

#if defined(STACK_USE_UART)
                putrsUART("Storing WPA encryption key for future use \r\n");
#endif
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



