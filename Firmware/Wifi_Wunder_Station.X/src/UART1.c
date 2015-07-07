#define __UART1_RingBuff_C

#include "HardwareProfile.h"
#include "TCPIP Stack/TCPIP.h"
#include "UART1.h"

#if !defined (__C30__)
#error "This project needs to be compiled with a C30 compiler!"
#endif
#if !defined(__PIC24F__)
#error "This Project is for a PIC24F family device"
#endif

static unsigned char  RX_buff[256]= {0,};       // ring buffer for recieving
static unsigned char  wr_ndx = 0;         // write index
static unsigned char  rd_ndx= 0;        // read index

void
UART1_Init(unsigned int BaudRt)
{
    
	// Initilize UART1

// TODO: is this neccessary ? -- I don't think so as long as the uart is in charge it dictates the state of the port
 //	UART2TX_TRIS = 0;
 //	UART2RX_TRIS = 1;

    	U1MODE = 0x8000;	// Set UARTEN.  Note: this must be done before setting UTXEN
        U1STA = 0x0400;		// UTXEN set

	U1BRG = BaudRt;

        IEC0bits.U1RXIE = 1;
//	IEC0bits.U1TXIE = 0;

        if(U1STAbits.OERR)  // Clear overflow error  ????
            U1STAbits.OERR = 0;

}
/* returns the lenght of the next string in the buffer, not counting the terminating 0*/
/* If there is a null string in the buffer, skipp across it, eliminating the null string from the input */
short
UART1_GetStringLen( void )
{
    unsigned short n = 0;
    unsigned short ndx = rd_ndx;
    unsigned char c;

    // seek through the ring buffer for the next null terminated string -- absorb extra null chars in the buffer
    while (ndx != wr_ndx)   // while we have charcaters in the buffer
    {
        c = RX_buff[ndx];

        ndx++;

        if(c == 0 )         // the null charcater
        {
            if (n == 0 )    // this is s null string -- skipp it, thus eliminate it from the buffer
            {
                rd_ndx = ndx;
                continue;
            }
            else
                break;      // this is the end of a string
        }
        n++;
    }
    return n;
}

BOOL
UART1_GetBuffOvl( void )
{
    return ( wr_ndx ==  (unsigned char)  (rd_ndx -1)  );
}

/*
 * Copies a null terminated string into the return buffer provided by the caller.
 * Returns ther number of charaters read from the UART input ring buffer.
 * If there is a null at the current rd_ndx, read the null out of the ring buffer and return a null string indicating  0 bytes read.
 * If there is not a complete null terminated string in the buffer discard the read and return a null string indicating  0 bytes read.
 * If called with a NULL pointer as input argument the next null terminated string is discarded from the ring buffer indicating number of bytes discarded.
 */
short
UART1_GetString ( char * s)
{
    unsigned short n = 0;
    unsigned char c;
    unsigned char ndx = rd_ndx;
   
    do
    {
         c = RX_buff[ndx];       // copy the string out of the buffer
   
        if (s!= NULL)            // Copy the string to the output buffer, otherwise discard it
            s[n] = c;

        if (ndx == wr_ndx )      // if the read pointer catches up to the write pointer before finding a null character then we don't have a complete string in the buffer
        {
            s[0] = '\0';         // reurn with a NULL string and 0 charaters read
            return 0;
        }
         n++;
        ndx++;
    } while (c);

    rd_ndx= ndx;                    // for sucessful reads advance the read index to the next string
    return n-1;                     // return the number of characters read -- not counting the 0 terminateion
}

// Flushes the input buffer, discards any unread content
void
UART1_ClearBuffer( void )
{
    wr_ndx = rd_ndx;
}

void _ISR __attribute__((__no_auto_psv__))
_U1RXInterrupt(void)
{
    volatile unsigned char c;       // Volatile to prevent compiler optimizing the read out in the overflow condition

    IFS0bits.U1RXIF = 0; // clear interrupt flag
    c = U1RXREG;

    // Copy the byte into the ringbuffer and replace newlines with nul terminators for strings
    // Note that the UART also generates null characters when plugging and unplugging the device

    if ( wr_ndx !=   (unsigned char)  (rd_ndx -1)  ) // as long as there is room in the buffer
    {
        if (c == 0xa)   //NL== delimiter,
            RX_buff[wr_ndx] = 0;
        else
            RX_buff[wr_ndx] = c;

        wr_ndx++;
    }
    else
        RX_buff[wr_ndx] = 0;  // the buffer wrapped around -- incoming characters are beeing lost
                              // put a null into the boundry byte and don't increment any furter --
   

}

#ifdef needed_for_senind_via_interrupt
/*********************************************************************
 * Function:        void _ISR _U2TXInterrupt(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Copies bytes to and from the local UART TX and 
 *					RX FIFOs
 *
 * Note:            None
 ********************************************************************/
void _ISR
_U2TXInterrupt(void)
{
	// Transmit a byte, if pending, if possible
	if(TXHeadPtr != TXTailPtr)
	{
		// Clear the TX interrupt flag before transmitting again
		IFS0bits.U1TXIF = 0;

		U1TXREG = *TXTailPtr++;
		if(TXTailPtr >= vUARTTXFIFO + sizeof(vUARTTXFIFO))
			TXTailPtr = vUARTTXFIFO;
	}
	else	// Disable the TX interrupt if we are done so that we don't keep entering this ISR
	{
		IEC0bits.U1TXIE = 0;
	}
}


#endif

