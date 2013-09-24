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

#define MY_DEFAULT_WUNDER_IP_ADDR_BYTE1        (38ul)
#define MY_DEFAULT_WUNDER_IP_ADDR_BYTE2        (102ul)
#define MY_DEFAULT_WUNDER_IP_ADDR_BYTE3        (136ul)
#define MY_DEFAULT_WUNDER_IP_ADDR_BYTE4        (125ul)

#define MY_DEFAULT_NIST1_IP_ADDR_BYTE1        (128ul)
#define MY_DEFAULT_NIST1_IP_ADDR_BYTE2        (138ul)
#define MY_DEFAULT_NIST1_IP_ADDR_BYTE3        (140ul)
#define MY_DEFAULT_NIST1_IP_ADDR_BYTE4        (44ul)

#define MY_DEFAULT_NIST2_IP_ADDR_BYTE1        (128ul)
#define MY_DEFAULT_NIST2_IP_ADDR_BYTE2        (138ul)
#define MY_DEFAULT_NIST2_IP_ADDR_BYTE3        (141ul)
#define MY_DEFAULT_NIST2_IP_ADDR_BYTE4        (172ul)

#define MAX_UPLINK_INTERVAL 120
#define MIN_UPLINK_INTERVAL 2
#define WIND_GUST_INTERVAL 60       // Local display wind-gusts are held for 60 seconds --

#define UPLINK_INTERVAL_DEFAULT 60
#define GMT_TZ_OFFSET_DEFAULT (-8)
#define WIND_COUNT_CAL_DEFAULT 8
#define AN_CAL_FACTOR_DEFAULT  2.25 // Anemometer calibration factor from DAVIS Instruments
#define BARO_HYG_TEMP_MEAS_Interval 5 // not too fast because of sensor self heating
#define RAIN_MEAS_Interval (60*1)    // Read and reset the rain counter every 1 minutes
#define RAIN_SAMPLES_P_HOUR   (60*60/RAIN_MEAS_Interval) // sum up this many samples for one hours worth of rain

#ifdef	__cplusplus
}
#endif

#endif	/* WUNDER_CFG_H */

