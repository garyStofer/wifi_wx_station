/*********************************************************************
 * FileName: HTTPPrint.h
 * Provides callback headers and resolution for user's custom
 * HTTP Application.
 * Processor: PIC18,PIC24E, PIC24F, PIC24H, dsPIC30F, dsPIC33F, dsPIC33E,PIC32
 * Compiler:  Microchip C18, C30, C32
 * 
 * This file is automatically generated by the MPFS Utility
 * ALL MODIFICATIONS WILL BE OVERWRITTEN BY THE MPFS GENERATOR
 *
 * Software License Agreement
 *
 * Copyright (C) 2012 Microchip Technology Inc.  All rights
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
 *********************************************************************/

#ifndef __HTTPPRINT_H
#define __HTTPPRINT_H

#include "TCPIP Stack/TCPIP.h"

#if defined(STACK_USE_HTTP2_SERVER)

extern HTTP_STUB httpStubs[MAX_HTTP_CONNECTIONS];
extern BYTE curHTTPID;

void HTTPPrint(DWORD callbackID);
void HTTPPrint_builddate(void);
void HTTPPrint_led(WORD);
void HTTPPrint_version(void);
void HTTPPrint_reboot(void);
void HTTPPrint_W_PASS(void);
void HTTPPrint_ELEV(void);
void HTTPPrint_W_ENB(void);
void HTTPPrint_status_fail(void);
void HTTPPrint_config_mac(void);
void HTTPPrint_config_hostname(void);
void HTTPPrint_config_dhcpchecked(void);
void HTTPPrint_config_ip(void);
void HTTPPrint_config_gw(void);
void HTTPPrint_config_subnet(void);
void HTTPPrint_config_dns1(void);
void HTTPPrint_config_dns2(void);
void HTTPPrint_rebootaddr(void);
void HTTPPrint_wifiSSID(void);
void HTTPPrint_wifiKey(void);
void HTTPPrint_wifiEnc(WORD);
void HTTPPrint_status_msg(void);
void HTTPPrint_nist_1(void);
void HTTPPrint_nist_2(void);
void HTTPPrint_WindDir(void);
void HTTPPrint_WindGust(void);
void HTTPPrint_WindSpeed(void);
void HTTPPrint_Temp_F(void);
void HTTPPrint_Dew_F(void);
void HTTPPrint_RelH(void);
void HTTPPrint_Baro_In(void);
void HTTPPrint_Sol_W(void);
void HTTPPrint_CALbo(void);
void HTTPPrint_CALho(void);
void HTTPPrint_CALwo(void);
void HTTPPrint_CALsg(void);
void HTTPPrint_W_IP(void);
void HTTPPrint_W_SID(void);
void HTTPPrint_R_WND(void);
void HTTPPrint_R_HYG(void);
void HTTPPrint_R_SOL(void);
void HTTPPrint_CALto(void);
void HTTPPrint_M_TO(void);
void HTTPPrint_M_SRV(void);
void HTTPPrint_M_PRT(void);
void HTTPPrint_M_USR(void);
void HTTPPrint_M_PWD(void);
void HTTPPrint_ST_USR(void);
void HTTPPrint_ST_PWD(void);
void HTTPPrint_CALra(void);
void HTTPPrint_R_RAIN(void);
void HTTPPrint_Ala(WORD);
void HTTPPrint_inp(WORD);
void HTTPPrint_out(WORD);
void HTTPPrint_adc(WORD);
void HTTPPrint_time(void);
void HTTPPrint_date(void);
void HTTPPrint_Rain_In(void);
void HTTPPrint_RainDay(void);

void HTTPPrint(DWORD callbackID)
{
	switch(callbackID)
	{
        case 0x00000006:
			HTTPPrint_builddate();
			break;
        case 0x0000000c:
			HTTPPrint_led(2);
			break;
        case 0x0000000d:
			HTTPPrint_led(1);
			break;
        case 0x0000000e:
			HTTPPrint_led(0);
			break;
        case 0x0000001c:
			HTTPPrint_version();
			break;
        case 0x0000001d:
			HTTPPrint_reboot();
			break;
        case 0x00000023:
			HTTPPrint_W_PASS();
			break;
        case 0x00000024:
			HTTPPrint_ELEV();
			break;
        case 0x00000026:
			HTTPPrint_W_ENB();
			break;
        case 0x00000027:
			HTTPPrint_status_fail();
			break;
        case 0x00000028:
			HTTPPrint_config_mac();
			break;
        case 0x00000029:
			HTTPPrint_config_hostname();
			break;
        case 0x0000002a:
			HTTPPrint_config_dhcpchecked();
			break;
        case 0x0000002b:
			HTTPPrint_config_ip();
			break;
        case 0x0000002c:
			HTTPPrint_config_gw();
			break;
        case 0x0000002d:
			HTTPPrint_config_subnet();
			break;
        case 0x0000002e:
			HTTPPrint_config_dns1();
			break;
        case 0x0000002f:
			HTTPPrint_config_dns2();
			break;
        case 0x00000030:
			HTTPPrint_rebootaddr();
			break;
        case 0x00000033:
			HTTPPrint_wifiSSID();
			break;
        case 0x00000035:
			HTTPPrint_wifiKey();
			break;
        case 0x00000036:
			HTTPPrint_wifiEnc(0);
			break;
        case 0x00000037:
			HTTPPrint_wifiEnc(1);
			break;
        case 0x00000038:
			HTTPPrint_wifiEnc(2);
			break;
        case 0x00000039:
			HTTPPrint_wifiEnc(3);
			break;
        case 0x0000003a:
			HTTPPrint_wifiEnc(4);
			break;
        case 0x0000003b:
			HTTPPrint_wifiEnc(5);
			break;
        case 0x0000003c:
			HTTPPrint_wifiEnc(6);
			break;
        case 0x0000003d:
			HTTPPrint_wifiEnc(7);
			break;
        case 0x0000003e:
			HTTPPrint_wifiEnc(8);
			break;
        case 0x0000003f:
			HTTPPrint_status_msg();
			break;
        case 0x00000042:
			HTTPPrint_nist_1();
			break;
        case 0x00000043:
			HTTPPrint_nist_2();
			break;
        case 0x00000044:
			HTTPPrint_WindDir();
			break;
        case 0x00000045:
			HTTPPrint_WindGust();
			break;
        case 0x00000046:
			HTTPPrint_WindSpeed();
			break;
        case 0x00000047:
			HTTPPrint_Temp_F();
			break;
        case 0x00000048:
			HTTPPrint_Dew_F();
			break;
        case 0x00000049:
			HTTPPrint_RelH();
			break;
        case 0x0000004a:
			HTTPPrint_Baro_In();
			break;
        case 0x0000004b:
			HTTPPrint_Sol_W();
			break;
        case 0x0000004f:
			HTTPPrint_CALbo();
			break;
        case 0x00000050:
			HTTPPrint_CALho();
			break;
        case 0x00000051:
			HTTPPrint_CALwo();
			break;
        case 0x00000052:
			HTTPPrint_CALsg();
			break;
        case 0x00000053:
			HTTPPrint_W_IP();
			break;
        case 0x00000054:
			HTTPPrint_W_SID();
			break;
        case 0x00000055:
			HTTPPrint_R_WND();
			break;
        case 0x00000056:
			HTTPPrint_R_HYG();
			break;
        case 0x00000057:
			HTTPPrint_R_SOL();
			break;
        case 0x00000058:
			HTTPPrint_CALto();
			break;
        case 0x0000005b:
			HTTPPrint_M_TO();
			break;
        case 0x0000005c:
			HTTPPrint_M_SRV();
			break;
        case 0x0000005d:
			HTTPPrint_M_PRT();
			break;
        case 0x0000005e:
			HTTPPrint_M_USR();
			break;
        case 0x0000005f:
			HTTPPrint_M_PWD();
			break;
        case 0x00000060:
			HTTPPrint_ST_USR();
			break;
        case 0x00000061:
			HTTPPrint_ST_PWD();
			break;
        case 0x00000062:
			HTTPPrint_CALra();
			break;
        case 0x00000063:
			HTTPPrint_R_RAIN();
			break;
        case 0x00000072:
			HTTPPrint_Ala(1);
			break;
        case 0x00000073:
			HTTPPrint_Ala(2);
			break;
        case 0x00000074:
			HTTPPrint_Ala(3);
			break;
        case 0x00000075:
			HTTPPrint_Ala(4);
			break;
        case 0x00000076:
			HTTPPrint_inp(0);
			break;
        case 0x00000077:
			HTTPPrint_inp(1);
			break;
        case 0x00000078:
			HTTPPrint_inp(2);
			break;
        case 0x00000079:
			HTTPPrint_inp(3);
			break;
        case 0x0000007a:
			HTTPPrint_out(0);
			break;
        case 0x0000007b:
			HTTPPrint_out(1);
			break;
        case 0x0000007c:
			HTTPPrint_out(2);
			break;
        case 0x0000007d:
			HTTPPrint_out(3);
			break;
        case 0x0000007e:
			HTTPPrint_out(4);
			break;
        case 0x0000007f:
			HTTPPrint_out(5);
			break;
        case 0x00000080:
			HTTPPrint_out(6);
			break;
        case 0x00000081:
			HTTPPrint_out(7);
			break;
        case 0x00000082:
			HTTPPrint_adc(0);
			break;
        case 0x00000083:
			HTTPPrint_adc(1);
			break;
        case 0x00000084:
			HTTPPrint_adc(2);
			break;
        case 0x00000085:
			HTTPPrint_adc(3);
			break;
        case 0x00000086:
			HTTPPrint_adc(4);
			break;
        case 0x00000087:
			HTTPPrint_adc(5);
			break;
        case 0x00000088:
			HTTPPrint_adc(6);
			break;
        case 0x00000089:
			HTTPPrint_adc(7);
			break;
        case 0x0000008a:
			HTTPPrint_time();
			break;
        case 0x0000008b:
			HTTPPrint_date();
			break;
        case 0x0000008c:
			HTTPPrint_Rain_In();
			break;
        case 0x0000008d:
			HTTPPrint_RainDay();
			break;
		default:
			// Output notification for undefined values
			TCPPutROMArray(sktHTTP, (ROM BYTE*)"!DEF", 4);
	}

	return;
}

void HTTPPrint_(void)
{
	TCPPut(sktHTTP, '~');
	return;
}

#endif

#endif
