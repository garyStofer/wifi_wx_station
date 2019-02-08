/* 
 * File:   UART1.h
 * Author: Me
 *
 * Created on February 13, 2015, 9:27 PM
 */

#ifndef UART1_H
#define	UART1_H

#ifdef	__cplusplus
extern "C" {
#endif
extern void
UART1_Init(unsigned int BaudRt);
#ifdef  notNeededforSNOWsensor
extern  short
UART1_GetStringLen( void );

extern  short
UART1_GetString ( char * s);
#endif

extern unsigned char *
UART1_GetInBuff( void);

extern unsigned char
UART1_GetInBuffFilled( void);

extern unsigned char *
UART1_ClearRXBuffer( void );

extern void
UART1_PutS( char *);



#ifdef	__cplusplus
}
#endif

#endif	/* UART1_H */

