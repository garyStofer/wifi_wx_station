#include "TCPIP Stack/TCPIP.h"
#include "wind_rain_cnt.h"

// since the measurment window for the wind is 1 second ther RTC interrupt handler captures the Windcount from the HW counter register
// and stores it in this variable for the One Second task
volatile unsigned short Wind_1Sec_count = 0;

// Since Raincounts are only evaluated every 5 minutes the OneSecond task directly reads and resets the rain count HW rehister

/* Initializes counter/timer2 so that it counts edges on it's external clock input, used for wind speed counts*/
/* this coule be changed so that timer2 and timer 4 create an interrupt on every clock by setting the PR register to 0x1 and enabling interrupts */

void
WindCounterInit(void)
{
    TRISCbits.TRISC1 = 1;
    T2CON = 0;
    TMR2 = 0;       // WIND_COUNTER
    PR2 = 0xfffe; // the large number in the preset/compare register prevenst the counter to ever self reset
    T2CONbits.TCS = 1; // external clock input on T2CK
    T2CONbits.TON = 1; // Enable the counter
}
void
RainCounterInit(void)
{
    // Timer 4 has a clock sync circuit on the external clock input 
    // The clock input needs to be held low when the counter is enabled, otherwise it will miss the first count
    
    TRISCbits.TRISC3 = 0;
    LATCbits.LATC3 = 0;
    DelayMs(1);
    T4CON = 0;
    PR4 = 0xfff0; // the large number in the preset/compare register prevenst the counter to ever self reset
    T4CONbits.TCS = 1; // external clock input on T4CK
    T4CONbits.TON = 1; // Enable the counter

    LATCbits.LATC3 = 0; LATCbits.LATC3 = 0;;
    LATCbits.LATC3 = 0; LATCbits.LATC3 = 0;;
    LATCbits.LATC3 = 0; LATCbits.LATC3 = 0;
    TRISCbits.TRISC3 = 1; // remove the drive low on T4ck input
    DelayMs(1);

    TMR4 = 0;       // RAIN_COUNTER reset
}
