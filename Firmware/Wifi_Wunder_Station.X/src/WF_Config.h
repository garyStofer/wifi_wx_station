/******************************************************************************

 MRF24W Driver Customization
 Module for Microchip TCP/IP Stack
  -Provides access to MRF24W WiFi controller
  -Reference: MRF24W Data sheet, IEEE 802.11 Standard

*******************************************************************************
 FileName:		WF_Config.h
 Dependencies:	TCP/IP Stack header files
 Processor:		PIC18, PIC24F, PIC24H, dsPIC30F, dsPIC33F, PIC32
 Compiler:		Microchip C32 v1.10b or higher
				Microchip C30 v3.22 or higher
				Microchip C18 v3.34 or higher
 Company:		Microchip Technology, Inc.

 Software License Agreement

 Copyright (C) 2002-2010 Microchip Technology Inc.  All rights reserved.

 Microchip licenses to you the right to use, modify, copy, and distribute:
 (i)  the Software when embedded on a Microchip microcontroller or digital 
      signal controller product ("Device") which is integrated into 
      Licensee's product; or
 (ii) ONLY the Software driver source files ENC28J60.c, ENC28J60.h,
      ENCX24J600.c and ENCX24J600.h ported to a non-Microchip device used in 
	  conjunction with a Microchip ethernet controller for the sole purpose 
	  of interfacing with the ethernet controller.

 You should refer to the license agreement accompanying this Software for 
 additional information regarding your rights and obligations.

 THE SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY
 OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, TITLE AND
 NON-INFRINGEMENT. IN NO EVENT SHALL MICROCHIP BE LIABLE FOR ANY INCIDENTAL,
 SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST
 OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, ANY CLAIMS BY
 THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), ANY CLAIMS
 FOR INDEMNITY OR CONTRIBUTION, OR OTHER SIMILAR COSTS, WHETHER ASSERTED ON
 THE BASIS OF CONTRACT, TORT (INCLUDING NEGLIGENCE), BREACH OF WARRANTY, OR
 OTHERWISE.


 Author				Date		Comment
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 KH                 27 Jan 2010 Created for MRF24W
******************************************************************************/


#ifndef __WF_CONFIG_H_
#define __WF_CONFIG_H_

/*
*********************************************************************************************************
*                                           DEFINES                               
*********************************************************************************************************
*/

#define WF_TCPIP_DEMO



/*****************************************************************************/
/*****************************************************************************/
/*                             WIFI SECURITY COMPILE-TIME DEFAULTS           */
/*****************************************************************************/
/*****************************************************************************/
// Security modes available on WiFi network:
//   WF_SECURITY_OPEN                      : No security
//   WF_SECURITY_WEP_40                    : WEP Encryption using 40 bit keys
//   WF_SECURITY_WEP_104                   : WEP Encryption using 104 bit keys
//   WF_SECURITY_WPA_WITH_KEY              : WPA-PSK Personal where binary key is given to MRF24W 
//   WF_SECURITY_WPA_WITH_PASS_PHRASE      : WPA-PSK Personal where passphrase is given to MRF24W and it calculates the binary key
//   WF_SECURITY_WPA2_WITH_KEY             : WPA2-PSK Personal where binary key is given to MRF24W 
//   WF_SECURITY_WPA2_WITH_PASS_PHRASE     : WPA2-PSK Personal where passphrase is given to MRF24W and it calculates the binary key
//   WF_SECURITY_WPA_AUTO_WITH_KEY         : WPA-PSK Personal or WPA2-PSK Personal where binary key is given and MRF24W will 
//                                             connect at highest level AP supports (WPA or WPA2)                                                
//   WF_SECURITY_WPA_AUTO_WITH_PASS_PHRASE : WPA-PSK Personal or WPA2-PSK Personal where passphrase is given to MRF24W and it 
//                                             calculates the binary key and connects at highest level AP supports (WPA or WPA2)
//   WF_SECURITY_WPS_PUSH_BUTTON		   : WPS push button method
//   WF_SECURITY_WPS_PIN		   		   : WPS PIN method

//#define CFG_WF_INFRASTRUCTURE 1
//#define CFG_WF_P2P            3

#define MY_DEFAULT_NETWORK_TYPE             WF_INFRASTRUCTURE   /* CFG_WF_INFRASTRUCTURE, CFG_WF_P2P */
#define MY_DEFAULT_DOMAIN                   WF_DOMAIN_FCC
#define MY_DEFAULT_LIST_RETRY_COUNT         WF_RETRY_FOREVER            /* Number of times to try to connect to the SSID when using Infrastructure network type */

// Default pass phrase used for WF_SECURITY_WPA_WITH_PASS_PHRASE and
// WF_SECURITY_WPA2_WITH_PASS_PHRASE security modes
#define MY_DEFAULT_PSK_PHRASE  "dapassword"

#if MY_DEFAULT_NETWORK_TYPE == WF_INFRASTRUCTURE
    #define MY_DEFAULT_SSID_NAME                "linksys"
    #define MY_DEFAULT_WIFI_SECURITY_MODE       WF_SECURITY_OPEN
    //#define MY_DEFAULT_WIFI_SECURITY_MODE       WF_SECURITY_WPA_AUTO_WITH_PASS_PHRASE
    #define MY_DEFAULT_SCAN_TYPE                WF_ACTIVE_SCAN              /* WF_ACTIVE_SCAN or WF_PASSIVE_SCAN */
    #define MY_DEFAULT_BEACON_TIMEOUT           (40)                        /* Number of beacon periods          */
    #define MY_DEFAULT_CHANNEL_LIST         {1,2,3,4,5,6,7,8,9,10,11}   /* Default channel list for FCC */

    /* Select Infrastructure Power Save Mode */
    #define MY_DEFAULT_PS_POLL                   	WF_DISABLED	/* PS is not supported in Adhoc */
    #if !defined(MRF24WG)
    /* #define WF_AGGRESSIVE_PS */	/* WARNING !!! : This only can work with 1209 module FW version or later.
						* If you use the earlier version such as 1207 or 1205, then you should not define this.
						* Defining this will lead ASSERT problem with old module FW.
						*/
    #endif

/* Warning !!! Please note that :
* RF Module FW has a built-in connection manager, and it is enabled by default.
* So if you want to run your own connection manager in host stack application side,
* then you should disable the module connection manager to avoid some possible conflict
* between the two.  Especially these two APIs can be affected if you do not disable it.  
* A) UINT16 WF_CMDisconnect(void)
* B) UINT16 WF_Scan(UINT8 CpId)
* If some conflict occurs then these APIs will return failure. 
* Furthermore if you use old MRF24WB FW version, older than 120C, then 
* it can cause fatal issue in module FW side such as FW crash.
* So for simplicity, if you want to run your own connection manager actively,
* we strongly recommend to disable the module connection manager, and this
* #define is make that thing possible. Just un-comment it to do so !
*/
//#define DISABLE_MODULE_FW_CONNECT_MANAGER_IN_INFRASTRUCTURE	

/*------------------------------------------------------*/
/* else if starting this demo in P2P(Wi-Fi Direct) mode */
/*------------------------------------------------------*/
#elif MY_DEFAULT_NETWORK_TYPE == WF_P2P
#if defined (MRF24WG)
	/* 
	* Wi-Fi Direct has been validated with Samsung Galaxy Tab 2 7.0 ( Android 4.0.3, Ice cream Sandwitch)
	* and a flag-ship Android device Galaxy-Nexus. We can connect to a GO as a GC.
	* This demo runs a HTTP server, so you can connect to our device via a web browser in your Android device.
	*/
    #define MY_DEFAULT_WIFI_SECURITY_MODE              	WF_SECURITY_WEP_40
    #define MY_DEFAULT_SCAN_TYPE                       	WF_ACTIVE_SCAN   
    #define MY_DEFAULT_SSID_NAME                       	"linksys"    /* Fixed SSID. Do not change */
    #define MY_DEFAULT_CHANNEL_LIST                	{1,2,3,4,5,6,7,8,9,10,11}    /* Social channels. Do not change */
    #define MY_DEFAULT_BEACON_TIMEOUT                  	(40)   /* Number of beacon periods */
    #define MY_DEFAULT_PS_POLL                         	WF_DISABLED
#else	/* !defined (MRF24WG) */
    #error "MRF24WB does not support Wi-Fi Direct (P2P)"
#endif	/* defined (MRF24WG) */
#endif	/* MY_DEFAULT_NETWORK_TYPE == CFG_WF_INFRASTRUCTURE */


#if defined (MRF24WG)
/* The module HW has 2 hardware multicast filters. If that is not enough on your application, 
* then you can choose this option to extend it to max 16.  As the macro name indicates this forces 
* the module FW to use software to run the filters instead of hardware.  Downside of this option 
* is the performance can degrade when there are so many multicast packets on air becasue the 
* filtering is done by SW
*/
//#define ENABLE_SOFTWARE_MULTICAST_FILTER
#endif

// For WPS Push-Button demo, press the button of AP (Registrar) first before running this demo.
// Input this pin number on AP (Registrar), and activate Registrar first before connection attempt
// Also note that this 8 digit is not randomly generated. Last digit is the checksum of first 7 digits.
// The checksum must be correct, otherwise MRF24WG module wil reject the pin code
#define MY_DEFAULT_WPS_PIN   "12390212"    /* only used when security is WF_SECURITY_WPS_PIN */

#define MY_DEFAULT_WIFI_SECURITY_WEP_KEYTYPE  WF_SECURITY_WEP_OPENKEY  /* WF_SECURITY_WEP_OPENKEY (default) or	  */
																		 /*  WF_SECURITY_WEP_SHAREDKEY. 			 */ 

//-----------------------------------------------------------------------------------
// Default WEP keys used in WF_SECURITY_WEP_40  and WF_SECURITY_WEP_104 security mode
//-----------------------------------------------------------------------------------

// string 4 40-bit WEP keys 
#define MY_DEFAULT_WEP_KEYS_40 "\
\x00\x00\x00\x00\x00\
\x00\x00\x00\x00\x00\
\x00\x00\x00\x00\x00\
\x00\x00\x00\x00\x00"
// Do not indent above string as it will inject spaces 

// string containing 4 104-bit WEP keys 
#define MY_DEFAULT_WEP_KEYS_104 "\
\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\
\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\
\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\
\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"

// Do not indent above string as it will inject spaces 
#define MY_DEFAULT_WEP_KEY_INDEX        (0u)     /* Valid Key Index: 0, 1, 2, 3  */




// The tool at http://www.wireshark.org/tools/wpa-psk.html can be used to generate this field gtom SSID and pass_phrase
#define MY_DEFAULT_PSK "\
\x00\x00\x00\x00\x00\x00\x00\x00\
\x00\x00\x00\x00\x00\x00\x00\x00\
\x00\x00\x00\x00\x00\x00\x00\x00\
\x00\x00\x00\x00\x00\x00\x00\x00"
// Do not indent above string as it will inject spaces 

/*** Selecting Event Notification Type ***/
#define MY_DEFAULT_EVENT_NOTIFICATION_LIST  (WF_NOTIFY_CONNECTION_ATTEMPT_SUCCESSFUL  |         \
                                             WF_NOTIFY_CONNECTION_ATTEMPT_FAILED      |         \
                                             WF_NOTIFY_CONNECTION_TEMPORARILY_LOST    |         \
                                             WF_NOTIFY_CONNECTION_PERMANENTLY_LOST    |         \
                                             WF_NOTIFY_CONNECTION_REESTABLISHED)


#endif /* __WF_CONFIG_H_ */


/*  WF_ASSERT MACRO & WF_DEBUG    ====================================================*/
/* Customize how the WiFi driver assert macro (WF_ASSERT) should operate.             */
/*  To DISABLE the WF_ASSERT macro: Comment out '#define WF_DEBUG'                    */
/*  To ENABLE the WF_ASSERT macro:  Uncomment  '#define WF_DEBUG'                     */
/*====================================================================================*/
//#define WF_DEBUG
#if !defined(__18CXX) && defined WF_DEBUG
    #define DISPLAY_FILENAME  /* will diplay file names instead of module numbers on an assert */
#endif


/*----------------------------------------------------------------------------*/
/* This block of defines allows for code and data reduction by removing       */
/* WiFi driver code and or data that is not needed by the application.        */
/* Comment out those function blocks that are not needed.                     */
/*----------------------------------------------------------------------------*/
#define WF_USE_SCAN_FUNCTIONS	

#define WF_USE_TX_POWER_CONTROL_FUNCTIONS		

#define WF_USE_POWER_SAVE_FUNCTIONS		

#define WF_USE_MULTICAST_FUNCTIONS		

#define WF_USE_INDIVIDUAL_SET_GETS		

#define WF_USE_GROUP_SET_GETS		

//#define WF_USE_DATA_TX_RX_FUNCTIONS		

#define USE_GRATUITOUS_ARP

extern void WF_Connect(void);
extern void WF_ProcessEvent(UINT8 event, UINT16 eventInfo, UINT8 *extraInfo);
extern BOOL gRFModuleVer1209orLater;
//#define WF_CONSOLE		

//#define WF_CONSOLE_IFCFGUTIL		

//#define STACK_USE_EZ_CONFIG		

//#define EZ_CONFIG_SCAN		

//#define EZ_CONFIG_STALL		

//#define EZ_CONFIG_STORE		


