/* 
 * File:   WX_sensor_data.h
 * Author: Me
 *
 * Created on February 23, 2015, 10:38 AM
 *
 * Dynamic sensor data 
 */

#include "rtcc.h"

#ifndef WX_SENSOR_DATA_H
#define	WX_SENSOR_DATA_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef  struct
{
    float BaromIn;
    float TempF;
    float TempC;
    float DewptF;
    float DewptC;
    float RH;
    short Wind_dir;             // momentary wind direction (1 sec)
    float Wind_speed;           // momentary wind speed     (1 sec)
    float Wind_gust;            // Wind peak over  update interval
    float Wind_gust_5min;      // Wind peak over last 5 minutes
    short AvgWindDir;           // Average wind direction over  update interval
    float AvgWindSpd;           // Average wind speed  ""
    short SolRad;
    float RainIn;
    float RainDaily;
    float SoilM1;
} t_WX_Sensor_data;


extern t_WX_Sensor_data SensorReading;

#ifdef	__cplusplus
}
#endif

#endif	/* WX_SENSOR_DATA_H */

