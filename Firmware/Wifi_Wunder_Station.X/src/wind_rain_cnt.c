#include "TCPIP Stack/TCPIP.h"
#include "wind_rain_cnt.h"

// since the measurement window for wind is 1 second the RTC interrupt handler captures the wind count from the HW counter register
// and stores it in this variable for the One Second task
volatile unsigned short Wind_1Sec_count = 0;



/* Initializes counter/timer2 so that it counts edges on it's external clock input, used for wind speed counts*/
void
WindCounterInit(void)
{
    TRISCbits.TRISC1 = 1;
    T2CON = 0;
    TMR2 = 0;       // WIND_COUNTER
    PR2 = 0xfffe; // the large number in the preset/compare register prevents the counter to ever self reset
    T2CONbits.TCS = 1; // external clock input on T2CK
    T2CONbits.TON = 1; // Enable the counter
}

// Configure TMR4 used for Rain counts so that it creates an interrupt on every edge -- ISR then counts ticks
volatile unsigned short RainCountSinceMidnight =0;

void
RainCounterInit(void)
{
    // Timer 4 has a clock sync circuit on the external clock input 
    // The clock input needs to be held low when the counter is enabled, otherwise it will miss the first count
    
    TRISCbits.TRISC3 = 0;
    LATCbits.LATC3 = 0;
    DelayMs(1);
    T4CON = 0;
    PR4 = 0x1;         // this causes an interrupt on the next clock edge
    T4CONbits.TCS = 1; // external clock input on T4CK
    T4CONbits.TON = 1; // Enable the counter

    LATCbits.LATC3 = 0; LATCbits.LATC3 = 0;
    LATCbits.LATC3 = 0; LATCbits.LATC3 = 0;
    LATCbits.LATC3 = 0; LATCbits.LATC3 = 0;
    TRISCbits.TRISC3 = 1; // remove the drive low on T4ck input
    DelayMs(1);

    TMR4 = 0;       // RAIN_COUNTER reset
    IFS1bits.T4IF = 0;       // clear interrupt flag
    IEC1bits.T4IE = 1;      // enable interrupt for Timer4
    //  IPC6bits.T4IP = 4;  // the interrupt priority bits -- left unchanged from the default 4

}

void _ISR __attribute__((__no_auto_psv__))
_T4Interrupt(void)
{
    RainCountSinceMidnight++;
    TMR4 = 0;           // Reset Counter to 0 otherwise it will take one more clock to be reset and therefore only interrupt on every other clock edge
    IFS1bits.T4IF =0;   // clear interrupt flag
}
