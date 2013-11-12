/*********************************************************************
 *
 *  UART Configuration Menu
 *    - UART configuration
 *    - XMODEM uploads of MPFS classic image
 *
 *********************************************************************
 * FileName:        UARTConfig.c
 * Dependencies:    TCP/IP stack
 * Processor:       PIC18, PIC24F, PIC24H, dsPIC30F, dsPIC33F, PIC32
 * Compiler:        Microchip C32 v1.05 or higher
 *					Microchip C30 v3.12 or higher
 *					Microchip C18 v3.30 or higher
 *					HI-TECH PICC-18 PRO 9.63PL2 or higher
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 *
 * Copyright (C) 2002-2009 Microchip Technology Inc.  All rights
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
 *
 * V5.36 ---- STACK_USE_MPFS has been removed and DownloadMPFS has upgraded to MPFS2
 ********************************************************************/
#define __UARTCONFIG_C

#include "TCPIPConfig.h"

#if defined(STACK_USE_UART)

#include "TCPIP Stack/TCPIP.h"
#include "Main.h"

#define MAX_USER_RESPONSE_LEN   (24u)

void
DoUARTConfig(void)
{
    BYTE response[MAX_USER_RESPONSE_LEN];
    IP_ADDR tempIPValue;
    IP_ADDR *destIPValue;

    while ( 1 )
    {
        // Display the menu
        putrsUART("\fWiFi  &  TCP-IP configuration utility\r\n\n");
        putrsUART("0: Reset Security mode and DHCP\r\n");
        putrsUART("1: Change WiFi SSID:(");
        putsUART((char *) AppConfig.MySSID);
        putrsUART(")\r\n");

        putrsUART("2: Enable WPA2 security mode and set Passphrase\r\n");

        putrsUART("3: ");
        putrsUART((ROM char*) (AppConfig.Flags.bIsDHCPEnabled ? "Dis" : "En"));
        putrsUART("able DHCP\r\n");
      
        if (!AppConfig.Flags.bIsDHCPEnabled )
        {
            putrsUART("4: Change static IP address:(");
            DisplayIPValue(AppConfig.MyIPAddr);
            putrsUART(")\r\n");

            putrsUART("5: Change static subnet mask:(");
            DisplayIPValue(AppConfig.MyMask);
            putrsUART(")\r\n");
        }

        putrsUART("\r\nS: Save & Reboot.");
        putrsUART("\r\nE: Exit without saving.");
        putrsUART("\r\nEnter a menu choice: ");

        // Wait for the user to press a key
        while (!DataRdyUART())
            ;

        putrsUART((ROM char*) "\r\n\n");

        // Execute the user selection
        switch (ReadUART())
        {
            case '0':
                 AppConfig.SecurityMode = WF_SECURITY_OPEN;
                 AppConfig.Flags.bIsDHCPEnabled = 1;
                break;
            case '1':
                putrsUART("New SSID: ");
                ReadStringUART(response, sizeof (response) > sizeof (AppConfig.MySSID) ? sizeof (AppConfig.MySSID) : sizeof (response));
                if (response[0] != '\0')
                {
                    strcpy((char *) AppConfig.MySSID, (char *) response);
                    AppConfig.SsidLength = strlen((char *) response);
                }
                break;

            case '2':
                putrsUART("New Passphrase: ");
                ReadStringUART(response, (sizeof (response) > sizeof (AppConfig.SecurityKey)) ? sizeof (AppConfig.SecurityKey) : sizeof (response));
                if (response[0] != '\0')
                {
                    AppConfig.SecurityKeyLength = strlen((char *) response);
                    strcpy((char *) AppConfig.SecurityKey, (char *) response);
                    AppConfig.SecurityMode = WF_SECURITY_WPA_AUTO_WITH_PASS_PHRASE;

                }
                break;
                
            case '3':
                AppConfig.Flags.bIsDHCPEnabled = !AppConfig.Flags.bIsDHCPEnabled;
                break;


            case '4':
                destIPValue = &AppConfig.MyIPAddr;
                goto ReadIPConfig;

            case '5':
                destIPValue = &AppConfig.MyMask;
                goto ReadIPConfig;

ReadIPConfig:
            if (!AppConfig.Flags.bIsDHCPEnabled )
            {
                putrsUART("New setting: ");
                ReadStringUART(response, sizeof (response));

                if (StringToIPAddress(response, &tempIPValue))
                    destIPValue->Val = tempIPValue.Val;
                else
                    putrsUART("Invalid input.\r\n");
            }
                break;

           case 'E':
           case 'e':
               Reset();
               break;

           case 'S':
           case 's':
#if defined(EEPROM_CS_TRIS) || defined(SPIFLASH_CS_TRIS)
                SaveAppConfig(&AppConfig);
#else
                putrsUART("External EEPROM/Flash not present -- settings will be lost at reset.\r\n");
#endif
                Reset();
                break;
        }
    }
}

#endif
