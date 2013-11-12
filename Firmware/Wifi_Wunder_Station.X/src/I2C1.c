#define USE_AND_OR      // This is to steer the defines in i2c.h of the C30 compiler peripheral lib
#include  "TCPIP Stack/TCPIP.h"
#include "math.h"
#include "i2c.h"
#include "i2c1.h"





//******************** Interrupt sevice rotuine for I2C1 Master ***************************
/*
void __attribute__((interrupt, no_auto_psv))
_MI2C1Interrupt(void)
{
    // IFS1bits.MI2C1IF = 0;  //Clear Interrupt status of I2C1
    while (1);
}
*/
BYTE
I2C1_GetRX_Byte(void)
{
    return I2C1RCV;
}

BYTE
I2C1_Xfer(I2C_mode mode, unsigned char data)
{

    switch (mode)
    {
        case Start:
            I2C1CONbits.SEN = 1; /* initiate Start on SDA and SCL pins */
            break;

        case ReStart:
            I2C1CONbits.RSEN = 1; /* initiate restart on SDA and SCL pins */
            break;

        case AddrTX:
            I2C1TRN = data & ~I2C_READ_ADDR;
            break;

        case AddrRX:
            I2C1TRN = data | I2C_READ_ADDR;
            break;

        case TX:
            I2C1TRN = data;
            break;

        case RX:
            data = I2C1RCV; // Clear RBUF flag,  just in case
            I2C1STATbits.I2COV = 0; // Clear any receive overflow flag, just in case
            I2C1CONbits.RCEN = 1;
            break;

        case M_ACK:
            I2C1CONbits.ACKDT = 0;
            I2C1CONbits.ACKEN = 1; // Master Receiver mode, send ACK
            break;

        case M_NACK:
            I2C1CONbits.ACKDT = 1;
            I2C1CONbits.ACKEN = 1; // Master Receiver mode, send NACK
            break;

        case Stop:
            I2C1CONbits.PEN = 1; /* initiate Stop on SDA and SCL pins */
            break;

        case Open:
            // for interrupt based commumication
            //IPC4bits.SI2C1P = n;  /* set the SI2C priority */
            //IPC4bits.MI2C1P = n;    /* set the MI2C priority */
            /* set the SI2C & MI2C Interrupt enable bits */
            //IEC1bits.SI2C1IE = n;
            //IEC1bits.MI2C1IE = n;

           // I2C1BRG = I2c_100Khz;
            I2C1BRG = I2c_Slow_Clock;
            I2C1CON = I2C_ON ; // Enable the peripheral
            IEC1bits.SI2C1IE = 0;
            IEC1bits.MI2C1IE = 0;
            /* clear the SI2C & MI2C Interrupt flag bits */
            IFS1bits.SI2C1IF = 0;
            IFS1bits.MI2C1IF = 0;
            // No interrupt is generated -- return immediatly
            return (I2C1CONbits.SEN || I2C1CONbits.RSEN ||
                    I2C1CONbits.PEN || I2C1CONbits.RCEN ||
                    I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT);

        default:
        case Close:
            I2C1CONbits.I2CEN = 0; // disable device

            /* clear the SI2C & MI2C Interrupt enable bits */
            IEC1bits.SI2C1IE = 0;
            IEC1bits.MI2C1IE = 0;
            /* clear the SI2C & MI2C Interrupt flag bits */
            IFS1bits.SI2C1IF = 0;
            IFS1bits.MI2C1IF = 0;
            // or for intrrupt based commumication
            //IPC4bits.SI2C1P = 0;  /* set the SI2C priority */
            //IPC4bits.MI2C1P = 0;    /* set the MI2C priority */
            /* set the SI2C & MI2C Interrupt enable bits */
            //IEC1bits.SI2C1IE = 0;
            //IEC1bits.MI2C1IE = 0;
            // No interrupt is generated -- return immediatly
            return 0;
    }
// TODO :: need guard timeout if i2C can not complete transaction
    /* wait for interrupt flag indicating completion of transaction  */
    while (IFS1bits.MI2C1IF == 0)
    {

    }

    IFS1bits.MI2C1IF = 0; // and clear flag again

    switch (mode)
    {
        case Start:
        case ReStart:
            return I2C1STATbits.S;
            break;

        case Stop:
            return I2C1STATbits.P;
            break;

        case TX:
        case AddrTX:
        case AddrRX:
            if (I2C1STATbits.IWCOL) /* If write collision occurred,return -1 */
            { // This indicates a sequence error, i.e. Transmit register is written
                // before device was ready to accept new transmit data.
                I2C1STATbits.IWCOL = 0;
                return -1;
            }
            return (I2C1STATbits.ACKSTAT); // Returns the last ACK status received or sent 0 == ACK, 1 == NOT ACK
            break;

        default:
            break;
    }
    return 0;
}



