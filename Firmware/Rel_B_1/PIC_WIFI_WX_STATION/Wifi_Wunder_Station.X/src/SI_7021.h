/* 
 * File:   SI_7021.h
 * Author: Gary Stofer
 *
 * Created on December 18, 2013, 8:25 PM
 */

#ifndef SI_7021_H
#define	SI_7021_H

#ifdef	__cplusplus
extern "C" {
#endif
extern BOOL SI7021_BusErr;
extern void SI7021_init(void);
extern void SI7021_startMeasure(void);
extern BOOL SI7021_Read_Process(void );


#ifdef	__cplusplus
}
#endif

#endif	/* SI_7021_H */

