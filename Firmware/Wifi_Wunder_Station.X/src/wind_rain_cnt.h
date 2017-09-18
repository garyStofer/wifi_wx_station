/*
 * File:   wind_rain_cnt.h
 * Author: gary
 *
 * Created on September 27, 2012, 11:25 AM
 */
extern volatile unsigned short Wind_1Sec_count;
extern volatile unsigned short RainCountSinceMidnight;
/* Initializes counter/timer2 so that it counts edges on it's external clock input, used for wind speed counts*/
extern void WindSpeedCounterInit(void);
extern void RainCounterInit(void);
