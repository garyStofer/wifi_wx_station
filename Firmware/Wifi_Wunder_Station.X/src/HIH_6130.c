/* Functions to initialzie and read the HIH 6130 Relative humidity sensor device */
#include "TCPIP Stack/TCPIP.h"
#include "WX_perm_data.h"
#include "WX_sensor_data.h"
#include "math.h"
#include "i2c1.h"
#include "HIH_6130.h"

//////////////////////////////////////////// Humidity sensor HIH6130  //////////////////////

#define HIH6130_ADDR (0x27 <<1)

BOOL HIH6130_BusErr = TRUE;

void
HIH6130_init(void)
{
    if (I2C1_Xfer(Open, 0) != 0)
    {
        HIH6130_BusErr = TRUE;     // i2c bus could not be opened
        return;
    }

    if (I2C1_Xfer(Start, 0) == 0)
    {
        I2C1_Xfer(Close, 0);    // i2c bus could not assume start condition
        HIH6130_BusErr = TRUE;
        return;
    }

    if (I2C1_Xfer(AddrTX, HIH6130_ADDR) == 0)
        HIH6130_BusErr = FALSE; // The device acknowledged an address cycle
    else
        HIH6130_BusErr = TRUE; // The device failed to acknowledged an address cycle on the EEPROM address

    I2C1_Xfer(Stop, 0); // and finish by transition into stop state

}

// Structure to read the on chip calibration values
enum _HIH6130_READ_SM {
    SM_START = 0,
    SM_Wait_Results,
    SM_Read_Results,
    SM_ERROR,
    SM_STOP,
    SM_IDLE
};
static enum _HIH6130_READ_SM ThisState = SM_IDLE;

void
HIH6130_startMeasure(void)
{
    if(ThisState == SM_IDLE)
        ThisState = SM_START;
}

BOOL
HIH6130_Read_Process(void )
{
    static DWORD Timer;
    static union {
        BYTE bytes[2];
        WORD val;
    } ADC_RH;


    if (HIH6130_BusErr )    // Device did not init or failed
    {
        return FALSE;
    }
    switch (ThisState)
    {
        case SM_START:

            // initiate the temperature Reading
            if ((I2C1_Xfer(Start, 0)) == 0)
            { // set the bus to idle
                ThisState = SM_ERROR;
                break;
            }

            // address device in Write mode starts a measurment cycle
            if (I2C1_Xfer(AddrTX, HIH6130_ADDR) != 0) // if the device fails to ack the address
            {
                ThisState = SM_ERROR;
                break;
            }

            I2C1_Xfer(Stop, 0);

            Timer = TickGet();
            ThisState++;
            break;

        case SM_Wait_Results:
            if (TickGet() - Timer > 4 * TICK_SECOND / 100) // wait for 40 ms for the result to arrive
                ThisState++;
            break;

        case SM_Read_Results:
        {

            I2C1_Xfer(Start, 0);
            I2C1_Xfer(AddrRX, HIH6130_ADDR);

            I2C1_Xfer(RX, 0); // read rh data msb
            I2C1_Xfer(M_ACK, 0);
            ADC_RH.bytes[1] = I2C1_GetRX_Byte();

            I2C1_Xfer(RX, 0);
            I2C1_Xfer(M_NACK, 0); // read rh data lsb
            ADC_RH.bytes[0] = I2C1_GetRX_Byte();
            
            I2C1_Xfer(Stop, 0);

          // Temp does not seem to work with i2C version of  HIH6131
          // tmp = (ADC_TEMP.val/16382.0 * 165)-40.0;

            // assigne values to global sensor struct
            SensorReading.RH = ADC_RH.val / 16382.0 * 100;      // need to do this in FP
            SensorReading.RH += WX.Calib.Hyg_offs/10.0;

            ThisState = SM_STOP;
            return TRUE;
        }
            break;

        case SM_ERROR:
            I2C1_Xfer(Stop, 0);
            HIH6130_BusErr = TRUE;
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
