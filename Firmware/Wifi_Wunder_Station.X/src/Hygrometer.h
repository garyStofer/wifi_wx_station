/* 
 * File:   Hygrometer.h
 * Author: Me
 *
 * Created on December 18, 2013, 8:25 PM
 */

#ifndef HYGROMETER_H
#define	HYGROMETER_H

#include "HIH_6130.h"
#include "SI_7021.h"
#ifdef	__cplusplus
extern "C" {
#endif

    extern void Hygro_init(void);
    extern void Hygro_startMeasure( void );
    extern void Hygro_Read_Process(void );



#ifdef	__cplusplus
}
#endif

#endif	/* HYGROMETER_H */

