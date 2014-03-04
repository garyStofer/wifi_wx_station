/* 
 * File:   Mail_Alarm.h
 * Author: gary
 *
 * Created on January 11, 2013, 6:07 PM
 */

#ifndef MAIL_ALARM_H
#define	MAIL_ALARM_H

#ifdef	__cplusplus
extern "C" {
#endif

extern void SMTP_trigger_mail( char * message);
extern void SMTP_set_alarm( unsigned short alarm_no );
extern void SMTP_Alarm_Arm( unsigned char ON_off);
extern void SMTP_Mail_alarm(void);


#ifdef	__cplusplus
}
#endif

#endif	/* MAIL_ALARM_H */

