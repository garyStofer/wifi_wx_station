/* 
 * File:   HIH_6130.h
 * Author: Gary Stofer
 *
 * Created on December 18, 2013, 8:24 PM
 */

#ifndef HIH_6130_H
#define	HIH_6130_H

#ifdef	__cplusplus
extern "C" {
#endif

extern BOOL HIH6130_BusErr;
extern void HIH6130_init(void);
extern void HIH6130_startMeasure(void);
extern BOOL HIH6130_Read_Process(void );


#ifdef	__cplusplus
}
#endif

#endif	/* HIH_6130_H */

