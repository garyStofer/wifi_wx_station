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
void HTTPPrint_W_SID(void);
void HTTPPrint_led(WORD);
void HTTPPrint_WindDir(void);
void HTTPPrint_WindGust(void);
void HTTPPrint_WindSpeed(void);
void HTTPPrint_Temp_F(void);
void HTTPPrint_Dew_F(void);
void HTTPPrint_RelH(void);
void HTTPPrint_Baro_In(void);
void HTTPPrint_Sol_W(void);
void HTTPPrint_Rain_In(void);
void HTTPPrint_RainDay(void);
void HTTPPrint_adc(WORD);
void HTTPPrint_inp(WORD);
void HTTPPrint_btn(WORD);
void HTTPPrint_out(WORD);
void HTTPPrint_builddate(void);
void HTTPPrint_Ala(WORD);
void HTTPPrint_status_fail(void);
void HTTPPrint_status_msg(void);
void HTTPPrint_config_mac(void);
void HTTPPrint_config_hostname(void);
void HTTPPrint_config_dhcpchecked(void);
void HTTPPrint_config_ip(void);
void HTTPPrint_config_gw(void);
void HTTPPrint_config_subnet(void);
void HTTPPrint_config_dns1(void);
void HTTPPrint_config_dns2(void);
void HTTPPrint_wifiSSID(void);
void HTTPPrint_wifiEnc(WORD);
void HTTPPrint_wifiKey(void);
void HTTPPrint_M_TO(void);
void HTTPPrint_M_SRV(void);
void HTTPPrint_M_PRT(void);
void HTTPPrint_M_USR(void);
void HTTPPrint_M_PWD(void);
void HTTPPrint_TZoff(void);
void HTTPPrint_nist_1(void);
void HTTPPrint_nist_2(void);
void HTTPPrint_reboot(void);
void HTTPPrint_rebootaddr(void);
void HTTPPrint_CALsg(void);
void HTTPPrint_CALto(void);
void HTTPPrint_CALho(void);
void HTTPPrint_CALbo(void);
void HTTPPrint_CALra(void);
void HTTPPrint_CALwf(void);
void HTTPPrint_CALws(void);
void HTTPPrint_CALwo(void);
void HTTPPrint_version(void);
void HTTPPrint_time(void);
void HTTPPrint_date(void);
void HTTPPrint_W_ENB(void);
void HTTPPrint_pwr5V(void);
void HTTPPrint_ST_USR(void);
void HTTPPrint_ST_PWD(void);
void HTTPPrint_va_curr(void);
void HTTPPrint_va_min(void);
void HTTPPrint_va_max(void);
void HTTPPrint_W_PASS(void);
void HTTPPrint_ELEV(void);
void HTTPPrint_UpInt(void);
void HTTPPrint_R_WND(void);
void HTTPPrint_R_HYG(void);
void HTTPPrint_R_SOL(void);
void HTTPPrint_R_RAIN(void);
void HTTPPrint_W_LAT(void);
void HTTPPrint_W_LON(void);
void HTTPPrint_BARO_T(void);
void HTTPPrint_R_SOILM1(void);
void HTTPPrint_rfid(WORD);
void HTTPPrint_rfvb(WORD);
void HTTPPrint_rfr1_(WORD);
void HTTPPrint_rfr2_(WORD);
void HTTPPrint_rfr3_(WORD);
void HTTPPrint_rfsi(WORD);
void HTTPPrint_rftm(WORD);
void HTTPPrint_SmID1(void);

void HTTPPrint(DWORD callbackID)
{
	switch(callbackID)
	{
        case 0x00000000:
			HTTPIncFile((ROM BYTE*)"header.inc");
			break;
        case 0x00000001:
			HTTPIncFile((ROM BYTE*)"footer.inc");
			break;
        case 0x00000002:
			HTTPPrint_W_SID();
			break;
        case 0x00000003:
			HTTPPrint_led(0);
			break;
        case 0x00000004:
			HTTPPrint_WindDir();
			break;
        case 0x00000005:
			HTTPPrint_WindGust();
			break;
        case 0x00000006:
			HTTPPrint_WindSpeed();
			break;
        case 0x00000007:
			HTTPPrint_Temp_F();
			break;
        case 0x00000008:
			HTTPPrint_Dew_F();
			break;
        case 0x00000009:
			HTTPPrint_RelH();
			break;
        case 0x0000000a:
			HTTPPrint_Baro_In();
			break;
        case 0x0000000b:
			HTTPPrint_Sol_W();
			break;
        case 0x0000000c:
			HTTPPrint_Rain_In();
			break;
        case 0x0000000d:
			HTTPPrint_RainDay();
			break;
        case 0x0000000e:
			HTTPPrint_adc(0);
			break;
        case 0x0000000f:
			HTTPPrint_adc(1);
			break;
        case 0x00000010:
			HTTPPrint_adc(2);
			break;
        case 0x00000011:
			HTTPPrint_adc(3);
			break;
        case 0x00000012:
			HTTPPrint_adc(4);
			break;
        case 0x00000013:
			HTTPPrint_adc(5);
			break;
        case 0x00000014:
			HTTPPrint_inp(0);
			break;
        case 0x00000015:
			HTTPPrint_inp(1);
			break;
        case 0x00000016:
			HTTPPrint_inp(2);
			break;
        case 0x00000017:
			HTTPPrint_inp(3);
			break;
        case 0x00000018:
			HTTPPrint_inp(4);
			break;
        case 0x00000019:
			HTTPPrint_inp(5);
			break;
        case 0x0000001a:
			HTTPPrint_inp(6);
			break;
        case 0x0000001b:
			HTTPPrint_inp(7);
			break;
        case 0x0000001c:
			HTTPPrint_inp(8);
			break;
        case 0x0000001d:
			HTTPPrint_inp(9);
			break;
        case 0x0000001e:
			HTTPPrint_btn(1);
			break;
        case 0x0000001f:
			HTTPPrint_btn(2);
			break;
        case 0x00000020:
			HTTPPrint_led(1);
			break;
        case 0x00000021:
			HTTPPrint_led(2);
			break;
        case 0x00000022:
			HTTPPrint_led(3);
			break;
        case 0x00000023:
			HTTPPrint_out(0);
			break;
        case 0x00000024:
			HTTPPrint_out(1);
			break;
        case 0x00000025:
			HTTPPrint_out(2);
			break;
        case 0x00000026:
			HTTPPrint_out(3);
			break;
        case 0x00000027:
			HTTPPrint_out(4);
			break;
        case 0x00000028:
			HTTPPrint_out(5);
			break;
        case 0x00000029:
			HTTPPrint_out(6);
			break;
        case 0x0000002a:
			HTTPPrint_out(7);
			break;
        case 0x0000002b:
			HTTPPrint_out(8);
			break;
        case 0x0000002c:
			HTTPPrint_builddate();
			break;
        case 0x0000002d:
			HTTPPrint_Ala(1);
			break;
        case 0x0000002e:
			HTTPPrint_Ala(2);
			break;
        case 0x0000002f:
			HTTPPrint_Ala(3);
			break;
        case 0x00000030:
			HTTPPrint_Ala(4);
			break;
        case 0x00000031:
			HTTPPrint_Ala(5);
			break;
        case 0x00000032:
			HTTPPrint_Ala(0);
			break;
        case 0x00000033:
			HTTPPrint_status_fail();
			break;
        case 0x00000034:
			HTTPPrint_status_msg();
			break;
        case 0x00000035:
			HTTPPrint_config_mac();
			break;
        case 0x00000036:
			HTTPPrint_config_hostname();
			break;
        case 0x00000037:
			HTTPPrint_config_dhcpchecked();
			break;
        case 0x00000038:
			HTTPPrint_config_ip();
			break;
        case 0x00000039:
			HTTPPrint_config_gw();
			break;
        case 0x0000003a:
			HTTPPrint_config_subnet();
			break;
        case 0x0000003b:
			HTTPPrint_config_dns1();
			break;
        case 0x0000003c:
			HTTPPrint_config_dns2();
			break;
        case 0x0000003d:
			HTTPPrint_wifiSSID();
			break;
        case 0x0000003e:
			HTTPPrint_wifiEnc(0);
			break;
        case 0x0000003f:
			HTTPPrint_wifiEnc(1);
			break;
        case 0x00000040:
			HTTPPrint_wifiEnc(2);
			break;
        case 0x00000041:
			HTTPPrint_wifiEnc(3);
			break;
        case 0x00000042:
			HTTPPrint_wifiEnc(4);
			break;
        case 0x00000043:
			HTTPPrint_wifiEnc(5);
			break;
        case 0x00000044:
			HTTPPrint_wifiEnc(6);
			break;
        case 0x00000045:
			HTTPPrint_wifiEnc(7);
			break;
        case 0x00000046:
			HTTPPrint_wifiEnc(8);
			break;
        case 0x00000047:
			HTTPPrint_wifiKey();
			break;
        case 0x00000048:
			HTTPPrint_M_TO();
			break;
        case 0x00000049:
			HTTPPrint_M_SRV();
			break;
        case 0x0000004a:
			HTTPPrint_M_PRT();
			break;
        case 0x0000004b:
			HTTPPrint_M_USR();
			break;
        case 0x0000004c:
			HTTPPrint_M_PWD();
			break;
        case 0x0000004d:
			HTTPPrint_TZoff();
			break;
        case 0x0000004e:
			HTTPPrint_nist_1();
			break;
        case 0x0000004f:
			HTTPPrint_nist_2();
			break;
        case 0x00000050:
			HTTPPrint_reboot();
			break;
        case 0x00000051:
			HTTPPrint_rebootaddr();
			break;
        case 0x00000052:
			HTTPPrint_CALsg();
			break;
        case 0x00000053:
			HTTPPrint_CALto();
			break;
        case 0x00000054:
			HTTPPrint_CALho();
			break;
        case 0x00000055:
			HTTPPrint_CALbo();
			break;
        case 0x00000056:
			HTTPPrint_CALra();
			break;
        case 0x00000057:
			HTTPPrint_CALwf();
			break;
        case 0x00000058:
			HTTPPrint_CALws();
			break;
        case 0x00000059:
			HTTPPrint_CALwo();
			break;
        case 0x0000005a:
			HTTPPrint_version();
			break;
        case 0x0000005b:
			HTTPPrint_time();
			break;
        case 0x0000005c:
			HTTPPrint_date();
			break;
        case 0x0000005d:
			HTTPPrint_W_ENB();
			break;
        case 0x0000005e:
			HTTPPrint_pwr5V();
			break;
        case 0x0000005f:
			HTTPPrint_ST_USR();
			break;
        case 0x00000060:
			HTTPPrint_ST_PWD();
			break;
        case 0x00000061:
			HTTPPrint_va_curr();
			break;
        case 0x00000062:
			HTTPPrint_va_min();
			break;
        case 0x00000063:
			HTTPPrint_va_max();
			break;
        case 0x00000064:
			HTTPPrint_W_PASS();
			break;
        case 0x00000065:
			HTTPPrint_ELEV();
			break;
        case 0x00000066:
			HTTPPrint_UpInt();
			break;
        case 0x00000067:
			HTTPPrint_R_WND();
			break;
        case 0x00000068:
			HTTPPrint_R_HYG();
			break;
        case 0x00000069:
			HTTPPrint_R_SOL();
			break;
        case 0x0000006a:
			HTTPPrint_R_RAIN();
			break;
        case 0x0000006b:
			HTTPPrint_W_LAT();
			break;
        case 0x0000006c:
			HTTPPrint_W_LON();
			break;
        case 0x0000006d:
			HTTPPrint_BARO_T();
			break;
        case 0x0000006f:
			HTTPPrint_R_SOILM1();
			break;
        case 0x00000070:
			HTTPPrint_rfid(0);
			break;
        case 0x00000072:
			HTTPPrint_rfvb(0);
			break;
        case 0x00000073:
			HTTPPrint_rfr1_(0);
			break;
        case 0x00000074:
			HTTPPrint_rfr2_(0);
			break;
        case 0x00000075:
			HTTPPrint_rfr3_(0);
			break;
        case 0x00000076:
			HTTPPrint_rfsi(0);
			break;
        case 0x00000077:
			HTTPPrint_rftm(0);
			break;
        case 0x00000078:
			HTTPPrint_rfid(1);
			break;
        case 0x0000007a:
			HTTPPrint_rfvb(1);
			break;
        case 0x0000007b:
			HTTPPrint_rfr1_(1);
			break;
        case 0x0000007c:
			HTTPPrint_rfr2_(1);
			break;
        case 0x0000007d:
			HTTPPrint_rfr3_(1);
			break;
        case 0x0000007e:
			HTTPPrint_rfsi(1);
			break;
        case 0x0000007f:
			HTTPPrint_rftm(1);
			break;
        case 0x00000080:
			HTTPPrint_rfid(2);
			break;
        case 0x00000082:
			HTTPPrint_rfvb(2);
			break;
        case 0x00000083:
			HTTPPrint_rfr1_(2);
			break;
        case 0x00000084:
			HTTPPrint_rfr2_(2);
			break;
        case 0x00000085:
			HTTPPrint_rfr3_(2);
			break;
        case 0x00000086:
			HTTPPrint_rfsi(2);
			break;
        case 0x00000087:
			HTTPPrint_rftm(2);
			break;
        case 0x00000088:
			HTTPPrint_rfid(3);
			break;
        case 0x0000008a:
			HTTPPrint_rfvb(3);
			break;
        case 0x0000008b:
			HTTPPrint_rfr1_(3);
			break;
        case 0x0000008c:
			HTTPPrint_rfr2_(3);
			break;
        case 0x0000008d:
			HTTPPrint_rfr3_(3);
			break;
        case 0x0000008e:
			HTTPPrint_rfsi(3);
			break;
        case 0x0000008f:
			HTTPPrint_rftm(3);
			break;
        case 0x00000090:
			HTTPPrint_rfid(4);
			break;
        case 0x00000092:
			HTTPPrint_rfvb(4);
			break;
        case 0x00000093:
			HTTPPrint_rfr1_(4);
			break;
        case 0x00000094:
			HTTPPrint_rfr2_(4);
			break;
        case 0x00000095:
			HTTPPrint_rfr3_(4);
			break;
        case 0x00000096:
			HTTPPrint_rfsi(4);
			break;
        case 0x00000097:
			HTTPPrint_rftm(4);
			break;
        case 0x00000098:
			HTTPPrint_rfid(5);
			break;
        case 0x0000009a:
			HTTPPrint_rfvb(5);
			break;
        case 0x0000009b:
			HTTPPrint_rfr1_(5);
			break;
        case 0x0000009c:
			HTTPPrint_rfr2_(5);
			break;
        case 0x0000009d:
			HTTPPrint_rfr3_(5);
			break;
        case 0x0000009e:
			HTTPPrint_rfsi(5);
			break;
        case 0x0000009f:
			HTTPPrint_rftm(5);
			break;
        case 0x000000a0:
			HTTPPrint_SmID1();
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
