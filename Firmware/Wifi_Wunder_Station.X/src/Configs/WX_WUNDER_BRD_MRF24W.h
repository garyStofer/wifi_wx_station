 /*********************************************************************
 *
 *	Hardware specific definitions for:
 *    - Explorer 16
 *    - PIC24F, PIC24H, dsPIC33F
 *    - MRF24W Wi-Fi PICtail Plus
 *
 *********************************************************************
 * FileName:        HardwareProfile.h
 * Dependencies:    Compiler.h
 * Processor:       PIC24F, PIC24H, dsPIC30F, dsPIC33F
 * Compiler:        Microchip C30 v3.24 or higher
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
 *
 * Author               Date		Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Howard Schlunder		09/16/2010	Regenerated for specific boards
 ********************************************************************/
#ifndef HARDWARE_PROFILE_H
#define HARDWARE_PROFILE_H

#define MRF24WG
#include "Compiler.h"

// Clock frequency values
// Create a PIC dependant macro for the maximum supported internal clock
#if defined(__PIC24F__) 
	#define MAXIMUM_PIC_FREQ		(32000000ul)
#else	
	 #erro "Wrong MCU architecture for product"
#endif

// These directly influence timed events using the Tick module.  They also are used for UART and SPI baud rate generation.
#define GetSystemClock()	(MAXIMUM_PIC_FREQ)			// Hz
#define GetInstructionClock()	(GetSystemClock()/2)	// Normally GetSystemClock()/4 for PIC18, GetSystemClock()/2 for PIC24/dsPIC, and GetSystemClock()/1 for PIC32.  Might need changing if using Doze modes.
#define GetPeripheralClock()	(GetSystemClock()/2)	// Normally GetSystemClock()/4 for PIC18, GetSystemClock()/2 for PIC24/dsPIC, and GetSystemClock()/1 for PIC32.  Divisor may be different if using a PIC32 since it's configurable.


// Hardware I/O pin mappings

// Inputs on SV2
#define IN0_TRIS			(TRISDbits.TRISD0)	// SV2 Pin1
#define IN0_OUT				(LATDbits.LATD0)
#define IN0_IN                          (PORTDbits.RD0)
#define IN1_TRIS			(TRISDbits.TRISD1)	// SV2 Pin2
#define IN1_OUT				(LATDbits.LATD1)
#define IN1_IN                          (PORTDbits.RD1)
#define IN2_TRIS			(TRISDbits.TRISD2)	// SV2 Pin3
#define IN2_OUT				(LATDbits.LATD2)
#define IN2_IN                          (PORTDbits.RD2)
#define IN3_TRIS			(TRISDbits.TRISD3)
#define IN3_OUT				(LATDbits.LATD3)
#define IN3_IN                          (PORTDbits.RD3)
#define IN4_TRIS			(TRISDbits.TRISD12)
#define IN4_OUT				(LATDbits.LATD12)
#define IN4_IN                          (PORTDbits.RD12)
#define IN5_TRIS			(TRISDbits.TRISD13)
#define IN5_OUT				(LATDbits.LATD13)
#define IN5_IN                          (PORTDbits.RD13)        // Alarm#1, SV2:6
#define IN6_TRIS			(TRISDbits.TRISD4)
#define IN6_OUT				(LATDbits.LATD4)
#define IN6_IN                          (PORTDbits.RD4)         // Alarm#2, SV2:7
#define IN7_TRIS			(TRISDbits.TRISD5)
#define IN7_OUT				(LATDbits.LATD5)
#define IN7_IN                          (PORTDbits.RD5)         // Alarm#3, SV2:8
#define IN8_TRIS			(TRISDbits.TRISD6)
#define IN8_OUT				(LATDbits.LATD6)
#define IN8_IN                          (PORTDbits.RD6)         // Alarm#4, SV2:9
#define IN9_TRIS			(TRISDbits.TRISD7)      // SV2 pin 10
#define IN9_OUT				(LATDbits.LATD7)
#define IN9_IN                          (PORTDbits.RD7)         //Alarm#5, SV2:10

#define ALARM_1_input  IN5_IN
#define ALARM_2_input  IN6_IN
#define ALARM_3_input  IN7_IN
#define ALARM_4_input  IN8_IN
#define ALARM_5_input  IN9_IN


// Outputs on SV2
#define OUT0_TRIS			(TRISFbits.TRISF0)	// SV3 Pin1
#define OUT0_IO				(LATFbits.LATF0)
#define OUT1_TRIS			(TRISFbits.TRISF1)	// SV3 Pin2
#define OUT1_IO				(LATFbits.LATF1)
#define OUT2_TRIS			(TRISGbits.TRISG1)	// SV3 Pin3
#define OUT2_IO				(LATGbits.LATG1)
#define OUT3_TRIS			(TRISGbits.TRISG0)
#define OUT3_IO				(LATGbits.LATG0)
#define OUT4_TRIS			(TRISEbits.TRISE0)
#define OUT4_IO				(LATEbits.LATE0)
#define OUT5_TRIS			(TRISEbits.TRISE1)
#define OUT5_IO				(LATEbits.LATE1)
#define OUT6_TRIS			(TRISEbits.TRISE2)
#define OUT6_IO				(LATEbits.LATE2)
#define OUT7_TRIS			(TRISEbits.TRISE3)
#define OUT7_IO				(LATEbits.LATE3)
#define OUT8_TRIS			(TRISEbits.TRISE4)
#define OUT8_IO				(LATEbits.LATE4)


// IO on SV1 unassigned

#define IO0_TRIS			(TRISBbits.TRISB8)          // SV1 pin 2, also AN8
#define IO0_IO				(LATBbits.LATB8)
#define IO1_TRIS			(TRISBbits.TRISB9)          // SV1 pin3, also AN9
#define IO1_IO				(LATBbits.LATB9)
#define IO2_TRIS			(TRISBbits.TRISB10)         // also AN10
#define IO2_IO				(LATBbits.LATB10)
#define IO3_TRIS			(TRISBbits.TRISB11)          // also AN11
#define IO3_IO				(LATBbits.LATB11)
#define IO4_TRIS			(TRISBbits.TRISB12)          // also AN12
#define IO4_IO				(LATBbits.LATB12)
#define IO5_TRIS			(TRISBbits.TRISB13)          // also AN13
#define IO5_IO				(LATBbits.LATB13)
#define IO6_TRIS			(TRISBbits.TRISB14)          // also AN14
#define IO6_IO				(LATBbits.LATB14)
#define IO7_TRIS			(TRISBbits.TRISB15)          // SV1 pin 9, also AN15
#define IO7_IO				(LATBbits.LATB15)
// LEDs

#define LED1_TRIS			(TRISEbits.TRISE5)	// Ref L1
#define LED1_IO				(LATEbits.LATE5)
#define LED2_TRIS			(TRISEbits.TRISE6)	// Ref L2
#define LED2_IO				(LATEbits.LATE6)
#define LED3_TRIS			(TRISEbits.TRISE7)	// Ref L3
#define LED3_IO				(LATEbits.LATE7)

#define All_LEDS_on()                  LATE = 0xE0
#define All_LEDS_off()                 LATE = 0

// Momentary push buttons

#define BUTTON1_TRIS		(TRISDbits.TRISD14)	// Ref S1
#define	BUTTON1_IO		(PORTDbits.RD14)
#define BUTTON2_TRIS		(TRISDbits.TRISD15)	// Ref S2
#define	BUTTON2_IO		(PORTDbits.RD15)

#define BARO_CS_TRIS    (TRISDbits.TRISD8)
#define BARO_CS_IO      (LATDbits.LATD8)

#define UART2TX_TRIS		(TRISFbits.TRISF5)
#define UART2TX_IO		(PORTFbits.RF5)
#define UART2RX_TRIS		(TRISFbits.TRISF4)
#define UART2RX_IO		(PORTFbits.RF4)

#define UART1TX_TRIS		(TRISFbits.TRISF3)
#define UART1TX_IO		(PORTFbits.RF3)
#define UART1RX_TRIS		(TRISFbits.TRISF2)
#define UART1RX_IO		(PORTFbits.RF2)

// 25LC256,  25LC512 I/O pins
#define EEPROM_CS_TRIS		(TRISGbits.TRISG9)
#define EEPROM_CS_IO		(LATGbits.LATG9)
#define EEPROM_SCK_TRIS		(TRISGbits.TRISG6)
#define EEPROM_SDI_TRIS		(TRISGbits.TRISG7)
#define EEPROM_SDO_TRIS		(TRISGbits.TRISG8)
#define EEPROM_SPI_IF		(IFS2bits.SPI2IF)
#define EEPROM_SSPBUF		(SPI2BUF)
#define EEPROM_SPICON1		(SPI2CON1)
#define EEPROM_SPICON1bits	(SPI2CON1bits)
#define EEPROM_SPICON2		(SPI2CON2)
#define EEPROM_SPISTAT		(SPI2STAT)
#define EEPROM_SPISTATbits	(SPI2STATbits)
#define USE_EEPROM_25LC512      // Also defined in TCPIPMRF24W.h

// WiFi board connection
#define WF_CS_TRIS		(TRISDbits.TRISD11)
#define WF_CS_IO		(LATDbits.LATD11)

#define WF_SDI_TRIS		(TRISFbits.TRISF7)
#define WF_SCK_TRIS		(TRISFbits.TRISF6)
#define WF_SDO_TRIS		(TRISFbits.TRISF8)

#define WF_RESET_TRIS		(TRISDbits.TRISD9)
#define WF_RESET_IO		(LATDbits.LATD9)

#define WF_INT_TRIS             (TRISEbits.TRISE8)  // INT1
#define WF_INT_IO		(PORTEbits.RE8)

#define WF_HIBERNATE_TRIS	(TRISDbits.TRISD10)
#define	WF_HIBERNATE_IO		(PORTDbits.RD10)

#define WF_INT_EDGE		(INTCON2bits.INT1EP)
#define WF_INT_IE		(IEC1bits.INT1IE)
#define WF_INT_IF		(IFS1bits.INT1IF)

#define WF_SSPBUF		(SPI1BUF)
#define WF_SPISTAT		(SPI1STAT)
#define WF_SPISTATbits		(SPI1STATbits)
#define WF_SPICON1		(SPI1CON1)
#define WF_SPICON1bits		(SPI1CON1bits)
#define WF_SPICON2		(SPI1CON2)
#define WF_SPI_IE		(IEC0bits.SPI1IE)
//	#define WF_SPI_IP		(IPC2bits.SPI1IP)
#define WF_SPI_IF		(IFS0bits.SPI1IF)

// Select which UART the STACK_USE_UART and STACK_USE_UART2TCP_BRIDGE 
// options will use.  You can change these to U1BRG, U1MODE, etc. if you 
// want to use the UART1 module instead of UART2.
#define BAUD_RATE               (38400)		// bps
#define UARTTX_TRIS             UART2TX_TRIS
#define UARTTX_IO               UART2TX_IO
#define UARTRX_TRIS             UART2RX_TRIS
#define UARTRX_IO               UART2RX_IO

#define UBRG			U2BRG
#define UMODE			U2MODE
#define USTA			U2STA
#define BusyUART()		BusyUART2()
#define CloseUART()		CloseUART2()
#define ConfigIntUART(a)	ConfigIntUART2(a)
#define DataRdyUART()		DataRdyUART2()
#define OpenUART(a,b,c)		OpenUART2(a,b,c)
#define ReadUART()		ReadUART2()
#define WriteUART(a)		WriteUART2(a)
#define getsUART(a,b,c)		getsUART2(a,b,c)
#define putsUART(a)		putsUART2((unsigned int*)a)
#define getcUART()		getcUART2()
#define putcUART(a)		do{while(BusyUART()); WriteUART(a); while(BusyUART()); }while(0)
#define putrsUART(a)		putrsUART2(a)

#define WIND_COUNTER  TMR2    // the count the anemometer generates in one second as captured by the RTCC one second interrupt
#define RAIN_COUNTER  TMR4    // The count the Rain bucket generates in the Rain Measure Interval

#define ADC_R1 (14.0)          // Voltage divider R1 on external ADC inputs
#define ADC_R2 ( 26.1 )        // Voltage divider R2 on external ADC inputs
#define ADC_SCALE ((ADC_R1+ADC_R2) / ADC_R2)


#define SOL_ADCBUFF  ADC1BUF3
#define WIND_ADCBUFF ADC1BUF4
#define PWR_5V_ADCBUFF ADC1BUF5
#endif // #ifndef HARDWARE_PROFILE_H
