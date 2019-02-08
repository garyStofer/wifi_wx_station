/* 
 * File:   Once_per_second.h
 * Author: gary
 *
 * Created on February 1, 2013, 10:06 AM
 */

#ifndef ONCE_PER_SECOND_H
#define	ONCE_PER_SECOND_H

#ifdef	__cplusplus
extern "C" {
#endif

 typedef  struct tagwind_dirCal
 {
     BOOL DoWindDirCal;
     DWORD timeout;
     short WindDir_north;
     short WindDir_min;
     short WindDir_max;
 } t_wind_cal_temp;

extern t_wind_cal_temp  WDIR_cal_tmp;
extern void Wind_dir_cal (void );
extern void Once_perSecTask(void);

#define Hours_24 24
extern short SnowFall24Hrs[];
extern short SnowFall1Hr;
extern short SnowRange;

#ifdef	__cplusplus
}
#endif

#endif	/* ONCE_PER_SECOND_H */

