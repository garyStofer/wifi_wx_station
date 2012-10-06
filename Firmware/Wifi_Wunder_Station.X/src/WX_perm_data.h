/* 
 * File:   WX.h
 * Author: gary
 *
 * Created on August 16, 2012, 3:54 PM
 */
#include "TCPIP Stack/TCPIP.h"
#ifndef WX_H
#define	WX_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef  struct
{
    float BaromIn;
    float TempF;
    float DewptF;
    float RH;
    unsigned short Wind_dir;
    float Wind_speed;
    float Wind_gust;
    short SolRad;
} t_WX_Sensor_data;

typedef struct __attribute__((__packed__))
{
    short Temp_gain;
    short Hyg_gain;
    short Sol_gain;
    short Baro_offs;
    short WDir_offs;
    short Hyg_offs;
 
}t_cal_data;

typedef  struct __attribute__((__packed__))
{
   char Enabled;
   IP_ADDR Wunder_IP;
   char StationID[13];
   char StationPW[13];
   short StationElev;
}t_wunder_data;

typedef struct __attribute__((__packed__))
{
   IP_ADDR   NIST1;
   IP_ADDR   NIST2;
} t_WX_NIST_data;

typedef struct __attribute__((__packed__))
{
    t_cal_data Calib;
    t_wunder_data Wunder;
    t_WX_NIST_data TimeServer;
} t_WX_perm_data;



extern t_WX_perm_data WX;
extern t_WX_Sensor_data SensorReading;

extern void WX_Sensor_fakeInit();
extern void WX_perm_data_init_toDefault( void);
extern void WX_readPerm_data(void);
extern void WX_writePerm_data(void);

extern void stoa_dec( char * buff,  short data, short dec_places);


#ifdef	__cplusplus
}
#endif

#endif	/* WX_H */

