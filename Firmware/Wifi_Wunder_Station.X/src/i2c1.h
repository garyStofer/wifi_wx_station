/* 
 * File:   i2c1.h
 * Author: gary
 *
 * Created on October 2, 2012, 6:13 PM
 */

#ifndef I2C1_H
#define	I2C1_H

#ifdef	__cplusplus
extern "C" {
#endif

#define I2C_READ_ADDR 0x1
#define I2c_100Khz 140

typedef enum {
    Start = 0,
    ReStart,
    AddrTX,
    AddrRX,
    TX,
    RX,
    M_ACK,
    M_NACK,
    Stop,
    Open,
    Close,
} I2C_mode; // I2c operation modes for Master transmit and Master receive modes

extern BYTE I2C1_GetRX_Byte(void);
extern BYTE I2C1_Xfer(I2C_mode mode, unsigned char data);



#ifdef	__cplusplus
}
#endif

#endif	/* I2C1_H */

