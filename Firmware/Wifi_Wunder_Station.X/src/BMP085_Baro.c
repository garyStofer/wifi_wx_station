/* Functions to initialzie and read the HP03 Barometer device */
#include "TCPIP Stack/TCPIP.h"
#include "WX_perm_data.h"
#include "WX_sensor_data.h"
#include "math.h"
#include "i2c1.h"
#include "Barometer.h"
#include "BMP085_baro.h"
#include "SI_7021.h"


//////////////////////////////////////////// BMP805 sensor  //////////////////////
#define BMP085_I2C_Addr 0xEE
#define BMP085_EEprom 0xAA
#define BMP085_Ctrl_Reg 0xF4
#define BMP085_ReadADC 0xF6
#define BMP085_ConvTemp 0x2E	// 16 bits, conversion time 4.5ms
//#define BMP085_ConvPress 0x34   // 16 bits 1 internal sample 4.5Ms
#define BMP085_ConvPress 0xF4   // 16 bits 8 internal samples 25.5ms

#define HP03_EEPROM_ADDR 0xA0   // to check that this is not an HP03 device

// Structure to read the on chip calibration values
union {
	unsigned short dat[11];
	struct{
			short   AC1,AC2,AC3;
			unsigned short AC4,AC5,AC6;
			short  	B1,B2;
			short 	MB,MC,MD;
		} Coeff;
}BMP085_Cal;

enum _BMP085_READ_SM {
    SM_START = 0,
    SM_Wait_for_Temp,
    SM_Read_Temp,
    SM_Wait_for_Press,
    SM_Read_Press,
    SM_Calc,
    SM_ERROR,
    SM_STOP,
    SM_IDLE
};
static  enum _BMP085_READ_SM ThisState = SM_IDLE;

BOOL
BMP085_init()
{
    BYTE i;
    BOOL BusErr = TRUE;

    BARO_CS_TRIS = 0;
    BARO_CS_IO = 1; //  if  XCLR signal low, device inactive
    DelayMs(11);        // Device has a 10 ms startup delay 

    if (I2C1_Xfer(Open, 0) != 0)
    {
        return ( BusErr = TRUE);     // i2c bus could not be opened
    }

 
    if (I2C1_Xfer(Start, 0) == 0)
    {
        I2C1_Xfer(Close, 0);    // i2c bus could not assume start condition
        return (BusErr = TRUE);
    }


    // Check if this is by any chance a HP03 device and not a BMP085 By testing if it responds to the HP03 EEprom adddress
    if (I2C1_Xfer(AddrTX, HP03_EEPROM_ADDR)  == 0)
    {
        I2C1_Xfer(Close, 0);
        return (BusErr = TRUE);
    }
    
    I2C1_Xfer(ReStart, 0);
    if (I2C1_Xfer(AddrTX, BMP085_I2C_Addr)  == 0)
    {
    	BusErr = FALSE;
    	I2C1_Xfer(TX, BMP085_EEprom); 	// internal register address
    	I2C1_Xfer(ReStart,0);			// restart for read mode next
    	I2C1_Xfer(AddrRX,BMP085_I2C_Addr);
    	for (i=0; i <= 10; i++)
	{
            I2C1_Xfer(RX,0);
            I2C1_Xfer(M_ACK, 0);
            BMP085_Cal.dat[i]=(I2C1_GetRX_Byte() << 8);

            I2C1_Xfer(RX,0);
            I2C1_Xfer(M_ACK, 0);
            BMP085_Cal.dat[i]+=I2C1_GetRX_Byte();
	}
    	I2C1_Xfer(RX, 0);
        I2C1_Xfer(M_NACK, 0);
    }
    else
          BusErr = TRUE; // The device failed to acknowledged an address cycle on the EEPROM address
    I2C1_Xfer(Stop, 0); // and finish by transition into stop state
    return BusErr ;

}



void
BMP085_startMeasure( void )
{
    if ( ThisState == SM_IDLE )
        ThisState = SM_START;
}
void
BMP085_Read_Process(void )
{
    static long T;
    static long X1,X2,X3;
    static long B5;
    static long  Up;
    static DWORD Timer;
    static BOOL bus_err = FALSE;        // in case the device becomes unresponsive - i.e. unplugged

    if (bus_err) // Disable the device from further reads if it failed to init
    {
        // set impossible values
        SensorReading.TempC =0;
        SensorReading.BaromIn = 0;
        return;
    }

    switch (ThisState)
    {
        case SM_START:
            BARO_CS_TRIS = 0;
            BARO_CS_IO = 1;

               // initiate the temperature Reading
            if ((I2C1_Xfer(Start, 0)) == 0)     // can not esatblish i2C bus Start condition
            { // set the bus to idle
                ThisState = SM_ERROR;
                break;
            }

            if ( I2C1_Xfer(AddrTX, BMP085_I2C_Addr ) != 0) // if the device fails to ack the address
            {
                ThisState = SM_ERROR;
                break;
            }

            I2C1_Xfer(TX, BMP085_Ctrl_Reg); 	// internal register address
            I2C1_Xfer(TX, BMP085_ConvTemp); 	// internal register address
            I2C1_Xfer(Stop,0);

            Timer = TickGet();
            ThisState++;
            break;

        case SM_Wait_for_Temp:
            if (TickGet() - Timer > 5 * TICK_SECOND / 1000) // wait for 5 ms for the result to arrive
                ThisState++;
            break;

        case SM_Read_Temp:
        {   
            long Ut;
     
            // get Temp result now
            I2C1_Xfer(Start,0);
            I2C1_Xfer(AddrTX, BMP085_I2C_Addr);
            I2C1_Xfer(TX, BMP085_ReadADC); 	// internal command register address
            I2C1_Xfer(ReStart,0);		// command
            I2C1_Xfer(AddrRX,BMP085_I2C_Addr);
            I2C1_Xfer(RX,0);
            I2C1_Xfer(M_ACK, 0);
            Ut = (unsigned short) (I2C1_GetRX_Byte() << 8 );
            I2C1_Xfer(RX,0);
            I2C1_Xfer(M_NACK, 0);
            Ut+=I2C1_GetRX_Byte();
            
            I2C1_Xfer(Stop,0);

            X1 =(Ut - BMP085_Cal.Coeff.AC6) * BMP085_Cal.Coeff.AC5 / 32768L;
            X2 = BMP085_Cal.Coeff.MC * 2048L /(X1 + BMP085_Cal.Coeff.MD);
            B5 = X1+X2;
            T = (B5+8)/16;

            // calculate the Temperature only if selected so  or there is no 7021
            if ( SI7021_BusErr || WX.Wunder.report_enable.BaroT )
            {
                SensorReading.TempC = T/10.0;
                SensorReading.TempC += (WX.Calib.Temp_offs/10.0) * 5.0/9;         // apply cal offset
                SensorReading.TempF = SensorReading.TempC * 9.0 / 5.0 + 32;           // Conversion to deg F
            }
            // initiate the Pressure reading
            I2C1_Xfer(Start,0);
            I2C1_Xfer(AddrTX, BMP085_I2C_Addr);
            I2C1_Xfer(TX, BMP085_Ctrl_Reg); 	// internal command register address
            I2C1_Xfer(TX, BMP085_ConvPress); 	// Command
            I2C1_Xfer(Stop,0);

            Timer = TickGet();
            ThisState++;
            break;
        }
        case SM_Wait_for_Press:
            // wait for 40ms in this state
            if (TickGet() - Timer > 4 * TICK_SECOND / 100) // wait for 40 ms for the result to arrive
                ThisState++;
            break;

        case SM_Read_Press:      // get Pressure result now
        {
            I2C1_Xfer(Start,0);
            I2C1_Xfer(AddrTX, BMP085_I2C_Addr);
            I2C1_Xfer(TX, BMP085_ReadADC); 	// internal register address
            I2C1_Xfer(ReStart,0);			// restart for read mode next
            I2C1_Xfer(AddrRX,BMP085_I2C_Addr);
            I2C1_Xfer(RX,0);
            I2C1_Xfer(M_ACK, 0);
            Up = (unsigned short) ((I2C1_GetRX_Byte() << 8));
            I2C1_Xfer(RX,0);
            I2C1_Xfer(M_NACK, 0);
            Up += I2C1_GetRX_Byte();
           
            I2C1_Xfer(Stop,0);

            ThisState++;
          }
            break;

        case SM_Calc:
        {
            float Pressure;
            long p;
            unsigned long B4,B7;
            long B3,B6;

            B6=B5-4000L;
            X1 = (B6*B6)>>12;
            X1 *= BMP085_Cal.Coeff.B2;
            X1 >>= 11;

            X2 = BMP085_Cal.Coeff.AC2*B6;
            X2 >>= 11;

            X3=X1+X2;

            B3 = ((BMP085_Cal.Coeff.AC1 *4L + X3) +2) >> 2;
            X1 = (BMP085_Cal.Coeff.AC3* B6) >> 13;
            X2 = (BMP085_Cal.Coeff.B1 * ((B6*B6) >> 12) ) >> 16;
            X3 = ((X1 + X2) + 2) >> 2;
            B4 = (BMP085_Cal.Coeff.AC4 * (unsigned long) (X3 + 32768L)) >> 15;
            B7 = ((unsigned long)(Up - B3) * 50000L );

            if (B7 < (unsigned long)0x80000000)
            {
                    p = (B7 << 1) / B4;
            }
            else
            {
                    p = (B7 / B4) << 1;
            }

            X1 = p >> 8;
            X1 *= X1;
            X1 = (X1 * 3038L) >> 16;
            X2 = (p * -7357L) >> 16;
            p += ((X1 + X2 + 3791L) >> 4);	// p in Pa

  
            Pressure = p/100.0; // in hPa
            Pressure = Pressure * 0.02952998; // Conversion factor to inches Hg at 32F -- number and precision from Wikipedia
            Pressure += Alt_comp; // add the altitude compensation of the barometer due to elevation
            // assigne values to global sensor struct
            SensorReading.BaromIn = Pressure + WX.Calib.Baro_offs/100.0;
            ThisState = SM_STOP;
        }
            break;

        case SM_ERROR:
            bus_err = TRUE;  // enabling this stops the device from beeing read if it ever failed to ack. i.e.unplugged
            I2C1_Xfer(Stop, 0);
            BARO_CS_IO = 0; //  if  XCLR signal low, device inactive
            // don't break -- fall through to stop
        case SM_STOP:
            BARO_CS_TRIS = 0; //  HP03  XCLR signal , device inactive
            Timer = TickGet();
            ThisState++;
            break;

        case SM_IDLE: // park here until someone starts the process again.
            break;
    }
    
    return ;
}
