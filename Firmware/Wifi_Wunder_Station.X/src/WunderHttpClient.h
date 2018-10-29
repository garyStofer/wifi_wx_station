/* 
 * File:   WunderHttpClient.h
 * Author: Me
 *
 * Created on February 6, 2014, 3:52 PM
 */

#ifndef WUNDERHTTPCLIENT_H
#define	WUNDERHTTPCLIENT_H

#ifdef	__cplusplus
extern "C" {
#endif

#define NO_WX_HTTP_CLIENT 0
#define WU_CLIENT 1
#define PWS_CLIENT  2
#define WXBUG_CLIENT 3
#define CWOP_CLIENT 4
#define WOW_CLIENT  5
#define APRS_CLIENT 6

extern short
APRS_Client(void);
extern void
CWOPSendData(  void );
extern void
APRSSendData(  void );
extern void
WunderSendData(  void );
extern void
WunderHttpClient(void);
extern WORD
put_WXparam_arg(TCP_SOCKET , ROM char const * , short , BYTE );
extern WORD
WX_TCPPut(TCP_SOCKET , ROM char const * );
extern WORD
WX_TCPPutC(TCP_SOCKET, BYTE);

#ifdef	__cplusplus
}
#endif

#endif	/* WUNDERHTTPCLIENT_H */

