/* 
 * File:   WX_perm_data.h
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

typedef struct __attribute__((__packed__))
{
    short SoilM_Sensor_ID1;      // Sensor ID of sensord that is used to report readings to the cloud server
}t_other_data;

typedef struct __attribute__((__packed__))
{
    short Rain_counts;
    short Hyg_offs;
    short Sol_gain;
    short Baro_offs;
    short WDir_offs;
    short Temp_offs;
    short WDir_min;
    short WDir_max;
    short Wind_counts;
    float Wind_AN_CalFactor;

}t_cal_data;

typedef  struct __attribute__((__packed__))
{
   unsigned short UplnkInterval;
   char unused1[3];
   char StationID[13];
   char StationPW[13];
   short StationElev;
   struct tag_Report_enables
    {
       short Station:4;
       short Wind :1;
       short Hyg : 1;
       short Sol : 1;
       short Rain : 1;
       short BaroT: 1;
       short SoilM1:1;
       short unused: 6;
    }report_enable;
    char TZ_offset;
    float Lat;
    float Lon;
}t_wunder_data;

typedef struct __attribute__((__packed__))
{
   IP_ADDR   NIST1;
   IP_ADDR   NIST2;
} t_WX_NIST_data;

typedef  struct __attribute__((__packed__))
{
   char SendTo[31];
   char Server[31];
   char User_name[21];
   char password[21];
   short port;
   // short unused[2];
}t_MAIL_data;

typedef  struct __attribute__((__packed__))
{
   char User_name[13];
   char password[13];
}t_ST_data;

typedef struct __attribute__((__packed__))
{
    unsigned char enable;
    short adc_thresh[4];
} t_ALARM_Data;

typedef struct __attribute__((__packed__))
{
    t_wunder_data Wunder;
    t_WX_NIST_data TimeServer;
    t_MAIL_data Mail;
    t_ST_data Station;
    t_ALARM_Data Alarms;
    t_cal_data Calib;
    t_other_data Other;
} t_WX_perm_data;



extern t_WX_perm_data WX;


extern void WX_Sensor_fakeInit();
extern void WX_perm_data_init_toDefault( void);
extern void WX_readPerm_data(void);
extern void WX_writePerm_data(void);

extern void stoa_dec( char * buff,  long data, short dec_places);


#ifdef	__cplusplus
}
#endif

#endif	/* WX_H */

