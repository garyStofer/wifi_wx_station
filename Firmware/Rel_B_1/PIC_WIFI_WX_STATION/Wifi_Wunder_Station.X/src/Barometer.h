/* 
 * File:   Barometer.h
 * Author: Me
 *
 * Created on May 6, 2013, 5:34 PM
 */

#ifndef BAROMETER_H
#define	BAROMETER_H

#ifdef	__cplusplus
extern "C" {
#endif


    extern float Alt_comp;
    extern void Baro_init(short station_elevation);
    extern void Baro_startMeasure( void );
    extern void Baro_Read_Process(void );

#ifdef	__cplusplus
}
#endif

#endif	/* BAROMETER_H */

