/* 
 * File:   BMP085_baro.h
 * Author: Me
 *
 * Created on May 7, 2013, 9:35 AM
 */

#ifndef BMP085_BARO_H
#define	BMP085_BARO_H

#ifdef	__cplusplus
extern "C" {
#endif

extern BOOL BMP085_init(void);
extern void BMP085_startMeasure( void );
extern void BMP085_Read_Process(void );

#ifdef	__cplusplus
}
#endif

#endif	/* BMP085_BARO_H */

