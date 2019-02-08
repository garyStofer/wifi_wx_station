/* 
 * File:   Wunder_cfg.h
 * Author: gary
 *
 * Created on September 28, 2012, 1:15 PM
 */

#ifndef WUNDER_CFG_H
#define	WUNDER_CFG_H

#ifdef	__cplusplus
extern "C" {
#endif
#define MY_DEFAULT_WUNDER_STATION_ID "StationID"
#define MY_DEFAULT_WUNDER_STATION_PWD "passwd" 
/*
#define MY_DEFAULT_WUNDER_IP_ADDR_BYTE1        (38ul)
#define MY_DEFAULT_WUNDER_IP_ADDR_BYTE2        (102ul)
#define MY_DEFAULT_WUNDER_IP_ADDR_BYTE3        (136ul)
#define MY_DEFAULT_WUNDER_IP_ADDR_BYTE4        (125ul)
*/
    //Colorado  : 132.163.92.1
#define MY_DEFAULT_NIST1_IP_ADDR_BYTE1        (132ul)
#define MY_DEFAULT_NIST1_IP_ADDR_BYTE2        (163ul)
#define MY_DEFAULT_NIST1_IP_ADDR_BYTE3        (92ul)
#define MY_DEFAULT_NIST1_IP_ADDR_BYTE4        (1ul)

    // UC Colorado, Boulder
#define MY_DEFAULT_NIST2_IP_ADDR_BYTE1        (128ul)
#define MY_DEFAULT_NIST2_IP_ADDR_BYTE2        (138ul)
#define MY_DEFAULT_NIST2_IP_ADDR_BYTE3        (141ul)
#define MY_DEFAULT_NIST2_IP_ADDR_BYTE4        (172ul)

#define MAX_UPLINK_INTERVAL 3600
#define MIN_UPLINK_INTERVAL 2
//#define WIND_GUST_INTERVAL 60     // Local display wind-gusts are held for 60 seconds --


#define UPLINK_INTERVAL_DEFAULT 60
#define GMT_TZ_OFFSET_DEFAULT (-8)
#define WIND_COUNT_CAL_DEFAULT 8
#define AN_CAL_FACTOR_DEFAULT  2.5 // Anemometer calibration factor from DAVIS Instruments
#define BARO_HYG_TEMP_MEAS_Interval 5 // not too fast because of sensor self heating
#define RAIN_MEAS_Interval (60)    // Read and reset the rain counter every 1 minutes
#define RAIN_SAMPLES    (60)       // 60 minutes summing interval as per WU specs for RainIn
                                   // WU states that RainIn is to report the rain that has fallen in the last 60 minutes
      // average this many RAIN_MEAS_Intervals data points to calculate the rain rateper hour --
      // No less than 5 minutes becasue of the WU 5 min sample rate.  The lower the number the less the rain rate resolution
      // will be. For example for a 5 min window the rate resolution will be < 0.12"/hr, becasue 1 tip per 5 minute expanded
      // to a rate/hr that comes out to be (60/5) * 0.01"  == 0.12" .   15 min == 0.04"/hr resolution.
      // This means that at 15Min mesure interval ( moving average of 15 one minute samples) rain less than 0.04"/hr will cause a
      // a spiky grapgh toggling between 0 and 0.04"/hr

#define SNOW_MEAS_Interval (60)

#ifdef	__cplusplus
}
#endif

#endif	/* WUNDER_CFG_H */

