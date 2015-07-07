/* 
 * File:   RF_Sensors.h
 * Author: Me
 *
 * Created on February 23, 2015, 12:20 PM
 */

#ifndef RF_SENSORS_H
#define	RF_SENSORS_H

#include "rtcc.h"

#ifdef	__cplusplus
extern "C" {
#endif
#define N_RF_SENSORS 6           // nymber of RF sensors the station can handle

typedef struct
{
  int ID;                // this is a 12 bit number derived from the MAC address of the sensor node, a 0 indicates an unused location
  unsigned char Typ;     // The type of measurment the sensor provides  8 == Soil M
  unsigned char rssi;    // The relative Signal Strengt Indication from the sensor at the receiver
  float v[4];            // 4 readings from the sensor, v[0] is always battery voltage
  BCD_RTCC time;         // timestamp when last read

} t_RF_sens_data;



extern t_RF_sens_data RF_sens[];        // the number of 900 mhz RF sensors

extern void Read_RF_sensors(void);

#ifdef	__cplusplus
}
#endif

#endif	/* RF_SENSORS_H */

