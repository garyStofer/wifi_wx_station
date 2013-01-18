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
    T2CON = 0;
    TMR2 = 0;
    PR2 = 0xfffe; // the large number in the preset/compare register prevenst the counter to ever self reset
    T2CONbits.TCS = 1; // external clock input on T2CK
    T2CONbits.TON = 1; // Enable the counter
}
void
RainCounterInit(void)
{
    T4CON = 0;
    TMR4 = 0;
    PR4 = 0xfffe; // the large number in the preset/compare register prevenst the counter to ever self reset
    T4CONbits.TCS = 1; // external clock input on T4CK
    T4CONbits.TON = 1; // Enable the counter
}