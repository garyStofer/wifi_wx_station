/* 
 * File:   HP03_baro.h
 * Author: Me
 *
 * Created on May 7, 2013, 9:38 AM
 */

#ifndef HP03_BARO_H
#define	HP03_BARO_H

#ifdef	__cplusplus
extern "C" {
#endif

extern BOOL HP03_init(void);
extern void HP03_startMeasure( void );
extern void HP03_Read_Process(void );



#ifdef	__cplusplus
}
#endif

#endif	/* HP03_BARO_H */

