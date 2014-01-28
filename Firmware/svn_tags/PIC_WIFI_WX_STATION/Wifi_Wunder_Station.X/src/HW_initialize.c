#include "TCPIP Stack/TCPIP.h"
#include "rtcc.h"
#include "wind_rain_cnt.h"
#include "Mail_Alarm.h"
#include "HW_initialize.h"
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
void
InitializeBoard(void)
{
    BUTTON1_TRIS = 1;
    BUTTON2_TRIS = 1;
    CNPU2bits.CN20PUE = 1; // Weak pull up Button S1
    CNPU2bits.CN21PUE = 1; // Weak pull up Button S2

    LED1_TRIS = 0;
    LED2_TRIS = 0;
    LED3_TRIS = 0;
    All_LEDS_on();

// All inputs --
    IN0_TRIS = 1;
    IN1_TRIS = 1;
    IN2_TRIS = 1;
    IN3_TRIS = 1;
    IN4_TRIS = 1;
    IN5_TRIS = 1; // Alarm 1
    IN6_TRIS = 1; // Alarm 2
    IN7_TRIS = 1; // Alarm 3
    IN8_TRIS = 1; // Alarm 4
    IN9_TRIS = 1; // Alarm 5




    // invoke the Bootloader immediatly -- This is a problem if there is no BL loaded
    if(BUTTON2_IO == 0)
    {
	//setup and call bootloader
	RCON = 0;
	asm("goto 0x400");  // The entry point of the bootloader
    }


    // pic24FJ128GA008 has no pulldown register defined in linker file !! I assume they are missing
    // Enable pulldown on the 5 Change notification inputs we are going to use for alarms
#if defined(__PIC24FJ256GA108__)
    CNPD2bits.CN16PDE =1;
    CNPD2bits.CN19PDE =1;
    CNPD1bits.CN13PDE =1;
    CNPD1bits.CN14PDE =1;
    CNPD1bits.CN15PDE =1;
#endif


     // enable the change notification interupt on 5 inputs used for Alarms
    SMTP_Alarm_Arm(1);
   


    IFS1bits.CNIF =0;       // clear Change Notification interrupt flag
    IEC1bits.CNIE =1;       // Enable interrupts from Change Motification
   

      // All IOs on SV2 make inputs
     IO0_TRIS = 1;
     IO1_TRIS = 1;
     IO2_TRIS = 1;
     IO3_TRIS = 1;
     IO4_TRIS = 1;
     IO5_TRIS = 1;
     IO6_TRIS = 1;
     IO7_TRIS = 1;


    // All outputs on SV3
     OUT0_TRIS = 0;
     OUT1_TRIS = 0;
     OUT2_TRIS = 0;
     OUT3_TRIS = 0;
     OUT4_TRIS = 0;
     OUT5_TRIS = 0;
     OUT6_TRIS = 0;
     OUT7_TRIS = 0;
     OUT8_TRIS = 0;


    CLKDIVbits.RCDIV = 0; // Set 1:1 8MHz FRC postscalar

    // ADC
    AD1CON1bits.ADON = 0; // disable during configuration

    AD1CHSbits.CH0NA = 0; // V- for mux A (-) inputs
    AD1CHSbits.CH0SA = 0; // CH0 is AN0

    AD1PCFGbits.PCFG0 = 0; // Disable digital input on AN0
    AD1PCFGbits.PCFG1 = 0; // Disable digital input on AN1
    AD1PCFGbits.PCFG2 = 0; // Disable digital input on AN2
    AD1PCFGbits.PCFG3 = 0; // Disable digital input on AN3
    AD1PCFGbits.PCFG4 = 0; // Disable digital input on AN4
    AD1PCFGbits.PCFG5 = 0; // Disable digital input on AN5


    // ADC
    // The ADC of this device is autmatically taking samples and storing them in an ADCBUFFER
    // No ISR or other code is required once the autmatic scan is started. 
    AD1CON1bits.FORM = 0; // data form is unsigned integer
    AD1CON1bits.SSRC = 0x7; // conversion trigger internal counter/ autoconvert
    AD1CON1bits.ASAM = 1; // A/D Sample Auto-Start Mode  1 = Sampling begins immediately after last conversion
    AD1CON2bits.VCFG = 0; // use Vdd and Vss for reference
    AD1CON2bits.CSCNA = 1; // Use channel scan register to select inputs for MUXA
    AD1CON2bits.ALTS = 0; // Do not alternate between MUX A and B
    AD1CON3 = 0x1003; // 16 Tad auto-sample, Tad = 3*Tcy

    AD1CSSL = 0;

    AD1CSSLbits.CSSL0 = 1; // AN0, ANA pin5
    AD1CSSLbits.CSSL1 = 1; // AN1, ANA pin4
    AD1CSSLbits.CSSL2 = 1; // AN2, ANA pin3
    AD1CSSLbits.CSSL3 = 1; // AN3, Sol
    AD1CSSLbits.CSSL4 = 1; // AN4, Wind_dir
    AD1CSSLbits.CSSL5 = 1; // AN5, +5V pwr
    AD1CON2bits.SMPI = 5; // NUMBER of conversion before interrupt is generaterd --- This is the numbver of inputs scanned

    AD1CON1bits.ADON = 1; // enable the device

    // UART
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
#if defined(__PIC24FJ256GA108__)
    ALTRPbits.SCK1CM =1 ;       // remaps SCK1 to pin 45 ASCK1 -- same as on 128Ga008
    // Unlock Registers
    __builtin_write_OSCCONL(OSCCON & 0xBF);

    // Configure Output Functions (Table 10-3)
    // Assign pin RP16 to U1TX function
    RPOR8bits.RP16R = 3;    // 3 is U1TX
    RPOR8bits.RP17R = 5;    // 5 is U2TX
    RPOR10bits.RP21R = 11;  // 11 = SCK2OUT

    RPOR9bits.RP19R = 10;   // 10 = SDO2OUT
    RPOR7bits.RP15R =7;     // 7 = SDO1OUT
    // Note SCK1 has to be rempped via ALTRP register
    // RPOR13bits.RP27R =12;   // 12 = SS2OUT // not used as Slave select -- used via RG9 port funtion

    // Configure Input Functions (Table 10-2))
  
    RPINR18bits.U1RXR = 30;   // Assign U1RX To Pin RP30
    RPINR19bits.U2RXR = 10;
    RPINR0bits.INT1R = 33;
    RPINR1bits.INT2R = 34;
    RPINR22bits.SDI2R = 26;
    RPINR20bits.SDI1R = 44;
    RPINR3bits.T2CKR = 38;
    RPINR4bits.T4CKR = 40;
    
    // Lock Registers
    __builtin_write_OSCCONL(OSCCON | 0x40);
#endif
    WindCounterInit();
    RainCounterInit();
    RTC_Init();         // Real Time Clock init
}
