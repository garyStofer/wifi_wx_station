/* Functions to initialzie and read the HIH 6130 Relative humidity sensor device */
#include "TCPIP Stack/TCPIP.h"
#include "WX_perm_data.h"
#include "math.h"
#include "i2c1.h"

//////////////////////////////////////////// Humidity sensor HIH6130  //////////////////////

#define HIH6130_ADDR (0x27 <<1)

static BOOL HIH6130_BusErr = TRUE;

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
    union {
        unsigned char  bytes[2];
        unsigned short val;
    } ADC_TEMP;

    if (HIH6130_BusErr )    // Device did not init or failed
    {
        // set impossible values for display
        SensorReading.RH = SensorReading.DewptF = SensorReading.DewptC =0;
        return;
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
            volatile float Y,tmp;
            // get Temp result now
            I2C1_Xfer(Start, 0);
            I2C1_Xfer(AddrRX, HIH6130_ADDR);

            I2C1_Xfer(RX, 0); // read rh data msb
            I2C1_Xfer(M_ACK, 0);
            ADC_RH.bytes[1] = I2C1_GetRX_Byte();

            I2C1_Xfer(RX, 0);
            I2C1_Xfer(M_ACK, 0); // read rh data lsb
            ADC_RH.bytes[0] = I2C1_GetRX_Byte();
            // temp
            ADC_TEMP.val =0;
            I2C1_Xfer(RX, 0); // read temp data msb
            I2C1_Xfer(M_ACK, 0);
            ADC_TEMP.bytes[1] = I2C1_GetRX_Byte();

            I2C1_Xfer(RX, 0); // read temp data lsb
            I2C1_Xfer(M_NACK, 0);
            ADC_TEMP.bytes[1] = I2C1_GetRX_Byte();
            ADC_TEMP.val >>= 2; // Lower two bits of tempdata is not valid

            I2C1_Xfer(Stop, 0);

            tmp = (ADC_TEMP.val/16382.0 * 165)-40.0;

            // assigne values to global sensor struct
            SensorReading.RH = ADC_RH.val / 16382.0 * 100;      // need to do this in FP
            SensorReading.RH += WX.Calib.Hyg_offs/10.0;

/*	 Calculate DewPoint from Temp and humidity

            Simple approximation formula: (not used)
            Td = Temp_c -(100-RH)/5
            tmp = (100 - tmp)/5;
            tmp = Temp_c - tmp;
            T_dewptF  = (tmp*9/5+32)*10;		// convert to 1/10 deg F


            Close approximation formula:    (used)
            This expression is based on the August?Roche?Magnus approximation for the saturation vapor
            pressure of water in air as a function of temperature. It is considered valid for
            0 °C < T < 60 °C
            1% < RH < 100%
            0 °C < Td < 50 °C

             Formula:
             a = 17.271
             b = 237.7 °C
             Tc = Temp in Celsius
             Td = Dew point in Celsius
             RH = Relative Humidity
             Y = (a*Tc /(b+Tc)) + ln(RH/100)
             Td = b * Y / (a - Y)
*/

            Y = ((17.271 * SensorReading.TempC) / (237.7+SensorReading.TempC ))+ log(SensorReading.RH/100);
            SensorReading.DewptC = 237.7 * Y/(17.271-Y);
            SensorReading.DewptF = SensorReading.DewptC*9/5.0+32;
    
            ThisState = SM_STOP;
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
    
    return TRUE;
}
