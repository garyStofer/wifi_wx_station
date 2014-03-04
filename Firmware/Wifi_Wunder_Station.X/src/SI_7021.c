/* Functions to initialzie and read the HIH 6130 Relative humidity sensor device */
#include "TCPIP Stack/TCPIP.h"
#include "WX_perm_data.h"
#include "math.h"
#include "i2c1.h"
#include "SI_7021.h"

//////////////////////////////////////////// Humidity sensor HIH6130  //////////////////////

#define SI7021_ADDR (0x40<<1)
#define SI7021_RESET_CMD    0xFE
#define SI7021_Convert_CMD 0xF5        // Starts a temperature and RH conversion cycle, but doe not hold CLK line until complete
#define SI7021_ReadPrevTemp_CMD 0xE0     // Read out the temperature reading from the previous conversion
#define SI7021_WriteUserRegister 0xE6    // used to turn the heater on and set ADC resolution
#define SI7021_ReadUserRegister  0xE7


BOOL SI7021_BusErr = TRUE;

// Check if the Device can be addressed -- Listen for the ACK on address
void
SI7021_init(void)
{
    if (I2C1_Xfer(Open, 0) != 0)
    {
        SI7021_BusErr = TRUE;     // i2c bus could not be opened
        return;
    }

    if (I2C1_Xfer(Start, 0) == 0)
    {
        I2C1_Xfer(Close, 0);    // i2c bus could not assume start condition
        SI7021_BusErr = TRUE;
        return;
    }

    if (I2C1_Xfer(AddrTX, SI7021_ADDR) == 0)
        SI7021_BusErr = FALSE; // The device acknowledged an address cycle
    else
        SI7021_BusErr = TRUE; // The device failed to acknowledged an address cycle on the EEPROM address

    I2C1_Xfer(Stop, 0); // and finish by transition into stop state

}

// Structure to read the on chip calibration values
enum _SI7021_READ_SM {
    SM_START = 0,
    SM_Wait_Results,
    SM_Read_Results,
    SM_ERROR,
    SM_STOP,
    SM_IDLE
};
static enum _SI7021_READ_SM ThisState = SM_IDLE;

void
SI7021_startMeasure(void)
{
    if(ThisState == SM_IDLE)
        ThisState = SM_START;
}

BOOL
SI7021_Read_Process(void )
{
    static DWORD Timer;
    
    static union {
        unsigned char bytes[2];
        WORD val;
    } ADC_RH;

    union {
        unsigned char  bytes[2];
        unsigned short val;
    } ADC_TEMP;

    if (SI7021_BusErr )    // Device did not init or failed-- This should not get called
    {
        return FALSE;
    }

    switch (ThisState)
    {
        case SM_START: // initiate the Temp and RH  conversion

            if ((I2C1_Xfer(Start, 0)) == 0)     // If bus is not free
            { // set the bus to idle
                ThisState = SM_ERROR;
                break;
            }

            // address device in Write mode starts a measurment cycle
            if (I2C1_Xfer(AddrTX, SI7021_ADDR) != 0) // if the device fails to ack the address
            {
                ThisState = SM_ERROR;
                break;
            }
            if (I2C1_Xfer(TX,SI7021_Convert_CMD) != 0) // if the device fails to ack the commnad
            {
                ThisState = SM_ERROR;
                break;
            }

            I2C1_Xfer(Stop, 0);

            Timer = TickGet();
            ThisState++;
            break;

        case SM_Wait_Results:   // The conversion should take a maximum of 20.4 ms
            if (TickGet() - Timer > 4 * TICK_SECOND / 100) // wait 40 ms for the result to arrive
                ThisState++;
            break;

        case SM_Read_Results:
        {
            float RH, Temp_C;

            I2C1_Xfer(Start, 0);
            if ( I2C1_Xfer(AddrRX, SI7021_ADDR) != 0)  // Check for ACK-- If conversion is not ready yet device repsonds with NACK
            {
                ThisState = SM_ERROR;
                break;
            }

            I2C1_Xfer(RX, 0); // read rh data msb
            I2C1_Xfer(M_ACK, 0);
            ADC_RH.bytes[1] = I2C1_GetRX_Byte();

            I2C1_Xfer(RX, 0);
            I2C1_Xfer(M_NACK, 0); // read rh data lsb
            ADC_RH.bytes[0] = I2C1_GetRX_Byte();
            I2C1_Xfer(Stop, 0);

            // Collect the temperature data from the last conversion
            I2C1_Xfer(Start, 0);
            I2C1_Xfer(AddrTX, SI7021_ADDR);
            I2C1_Xfer(TX,SI7021_ReadPrevTemp_CMD);
            I2C1_Xfer(ReStart, 0);
            I2C1_Xfer(AddrRX, SI7021_ADDR);

            I2C1_Xfer(RX, 0); // read Temp data msb
            I2C1_Xfer(M_ACK, 0);
            ADC_TEMP.bytes[1] = I2C1_GetRX_Byte();

            I2C1_Xfer(RX, 0); // read Temp data lsb
            I2C1_Xfer(M_NACK, 0);
            ADC_TEMP.bytes[0] = I2C1_GetRX_Byte();
            I2C1_Xfer(Stop, 0);

            Temp_C = (ADC_TEMP.val*175.72/65536) -46.85;    // Magic numbers from SI datasheet  
            
            // Overwrite temp reading from  Baro 
            SensorReading.TempC = Temp_C;
            SensorReading.TempC += (WX.Calib.Temp_offs/10.0) * 5.0/9;         // apply cal offset
            SensorReading.TempF = SensorReading.TempC * 9.0 / 5.0 + 32;       // Conversion to deg F


            RH = (ADC_RH.val*125.0/65536)-6.0;              // Magic numbers from SI datasheet
            SensorReading.RH = RH;      // need to do this in FP
            SensorReading.RH += WX.Calib.Hyg_offs/10.0;

            ThisState = SM_STOP;
            return TRUE;
        }
            break;

        case SM_ERROR:
            I2C1_Xfer(Stop, 0);
            SI7021_BusErr = TRUE;
            // don't break -- fall through to stop
        case SM_STOP:
            Timer = TickGet();
            ThisState++;
            break;

        case SM_IDLE: // park here until someone starts the process again.
            break;
    }
    
    return FALSE;
}
