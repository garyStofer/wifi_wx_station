
#define WIND_COUNTER  TMR2    // the count the anemometer generates in one second as captured by the RTCC one second interrupt
#define RAIN_COUNTER  TMR4    // The count the Rain bucket generates in the Rain Measure Interval

extern volatile unsigned short Wind_1Sec_count;
/* Initializes counter/timer2 so that it counts edges on it's external clock input, used for wind speed counts*/
extern void WindSpeedCounterInit(void);
extern void RainCounterInit(void);
