/* Functions to initialzie and read the HP03 Barometer device */
#include "TCPIP Stack/TCPIP.h"
#include "WX_perm_data.h"
#include "math.h"
#include "i2c1.h"


//////////////////////////////////////////// HP03 sensor  //////////////////////
// The Device is actially two individual i2c Devices inside one package, hence the two addresses
#define HP03_EEPROM_ADDR 0xA0
#define HP03_ADC_ADDR 0xEE

static BOOL i2cBusErr = TRUE;

// Structure to read the on chip calibration values

static union {
    WORD vals[9];
    BYTE bytes[18];

    struct {
        WORD C1, C2, C3, C4, C5, C6, C7;
        BYTE A, B, C, D;
    } Coeff;

} HP03_Cal;

static float Alt_comp;

// Calculates the compesation in inches Hg pressure for the elevation of the station

static void
calc_alt_comp(short Station_elev)
{

    float tmp;
    // Calculate altitude correction for station height -- formula from http://www.csgnetwork.com/barcorrecthcalc.html
    tmp = 60 + 459.67; // fixed Rankine temp-- 60F == std temp at sea level
    Alt_comp = (29.92126 * (1 - (1 / pow(10, ((0.0081350 * Station_elev) / (tmp + (0.00178308 * Station_elev)))))));
}

/*
 *  Initialize the HP03 device by reading the calibration coefficients from it's 24c02-like eeprom memory
 *  and calculating the pressure offset due to the station elevation.
 */


void
HP03_init(short station_elevation)
{

    BYTE i;
    calc_alt_comp(station_elevation);
    

    TRISGbits.TRISG0 = 0;
    LATGbits.LATG0 = 0; //  HP03  XCLR signal low, device inactive

    if (I2C1_Xfer(Open, 0) != 0)
    {
        i2cBusErr = TRUE;
        return;
    }

    if (I2C1_Xfer(Start, 0) == 0)
    {
        I2C1_Xfer(Close, 0);
        i2cBusErr = TRUE;
        return;
    }

    if (I2C1_Xfer(AddrTX, HP03_EEPROM_ADDR) == 0)
    {
        i2cBusErr = FALSE;
        // The HP03 acknowledged an address cycle on the EEPROM address
        I2C1_Xfer(TX, 16); // Set word pointer to 16 for read of first coefficient, -- will auto increment

        I2C1_Xfer(ReStart, 0); // switch to master read mode
        I2C1_Xfer(AddrRX, HP03_EEPROM_ADDR); // readdress in read mode

        for (i = 0; i < 7; i++) // Read words
        {
            // read cal coeffs MSB
            I2C1_Xfer(RX, 0);
            I2C1_Xfer(M_ACK, 0);
            HP03_Cal.vals[i] = (I2C1_GetRX_Byte() << 8);
            // read cal coeffs LSB
            I2C1_Xfer(RX, 0);
            I2C1_Xfer(M_ACK, 0);
            // read cal coeffs LSB
            HP03_Cal.vals[i] += I2C1_GetRX_Byte();
        }

        for (i = 14; i < 18; i++) // Read bytes
        {
            I2C1_Xfer(RX, 0); // read cal coeffs ABCD
            I2C1_Xfer(M_ACK, 0);
            HP03_Cal.bytes[i] = I2C1_GetRX_Byte();
        }

        I2C1_Xfer(RX, 0);
        I2C1_Xfer(M_NACK, 0);
    }
    else
        i2cBusErr = TRUE; // The HP03 failed to acknowledged an address cycle on the EEPROM address
    I2C1_Xfer(Stop, 0); // and finish by transition into stop state

}

enum _HP03_READ_SM {
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
static enum _HP03_READ_SM ThisState = SM_IDLE;

void
HP03_startMeasure( void )
{
    if ( ThisState == SM_IDLE )
        ThisState = SM_START;
}
BOOL
HP03_Read_Process(void )
{
    static DWORD Timer;
    

    static union {
        BYTE bytes[2];
        WORD val;
    } D2, D1; // D2 = raw Temperatur data , D1 = Raw Pressure data



    if (i2cBusErr) // Disable the device from further reads if it failed to init or ever failed to communicate
        return FALSE;

    switch (ThisState)
    {
        case SM_START:
            TRISGbits.TRISG0 = 0;
            LATGbits.LATG0 = 1; //  HP03  XCLR signal, take device out of reset)

            // initiate the temperature Reading
            if ((I2C1_Xfer(Start, 0)) == 0)
            { // set the bus to idle
                ThisState = SM_ERROR;
                break;
            }

            if (I2C1_Xfer(AddrTX, HP03_ADC_ADDR) != 0) // if the device fails to ack the address
            {
                ThisState = SM_ERROR;
                break;
            }

            I2C1_Xfer(TX, 0xff);
            I2C1_Xfer(TX, 0xE8); // Temperatur reading address
            I2C1_Xfer(Stop, 0);

            Timer = TickGet();
            ThisState++;
            break;

        case SM_Wait_for_Temp:
            if (TickGet() - Timer > 4 * TICK_SECOND / 100) // wait for 40 ms for the result to arrive
                ThisState++;
            break;

        case SM_Read_Temp:
            // get Temp result now
            I2C1_Xfer(Start, 0);
            I2C1_Xfer(AddrTX, HP03_ADC_ADDR);
            I2C1_Xfer(TX, 0xFD);
            I2C1_Xfer(ReStart, 0);
            I2C1_Xfer(AddrRX, HP03_ADC_ADDR);
            I2C1_Xfer(RX, 0); // read temp data msb
            I2C1_Xfer(M_ACK, 0);
            D2.bytes[1] = I2C1_GetRX_Byte();
            I2C1_Xfer(RX, 0);
            I2C1_Xfer(M_NACK, 0); // read temp data lsb
            D2.bytes[0] = I2C1_GetRX_Byte();
            I2C1_Xfer(Stop, 0);

            // initiate the Pressure reading
            I2C1_Xfer(Start, 0);
            I2C1_Xfer(AddrTX, HP03_ADC_ADDR);
            I2C1_Xfer(TX, 0xff);
            I2C1_Xfer(TX, 0xF0); // Pressure reading address
            I2C1_Xfer(Stop, 0);

            Timer = TickGet();
            ThisState++;
            break;

        case SM_Wait_for_Press:
            // wait for 40ms in this state
            if (TickGet() - Timer > 4 * TICK_SECOND / 100) // wait for 40 ms for the result to arrive
                ThisState++;
            break;

        case SM_Read_Press:
            // get Pressure result now
            I2C1_Xfer(Start, 0);
            I2C1_Xfer(AddrTX, HP03_ADC_ADDR);
            I2C1_Xfer(TX, 0xFD);
            I2C1_Xfer(ReStart, 0);
            I2C1_Xfer(AddrRX, HP03_ADC_ADDR);
            I2C1_Xfer(RX, 0);
            I2C1_Xfer(M_ACK, 0);
            // read temp data msb
            D1.bytes[1] = I2C1_GetRX_Byte();
            I2C1_Xfer(RX, 0);
            I2C1_Xfer(M_NACK, 0);
            // read temp data lsb
            D1.bytes[0] = I2C1_GetRX_Byte();
            I2C1_Xfer(Stop, 0);
            ThisState++;
            break;

        case SM_Calc:
        {
            BYTE i;
            WORD Y;
            float X, Z;
            float dUT;
            float Offs;
            float Sens;
            float Pressure;

            // CALC barometer reading
            if (D2.val < HP03_Cal.Coeff.C5)
                Z = HP03_Cal.Coeff.B;
            else
                Z = HP03_Cal.Coeff.A;

            X = (float) D2.val - HP03_Cal.Coeff.C5;

            //Y =  pow(2,HP03_Cal.Coeff.C);
            for (Y = 1, i = 0; i < HP03_Cal.Coeff.C; i++)
                Y *= 2;

            // dUT = X-(X*X/16384.0) * Z / Y;
            dUT = X - X * X * Z / (16384.0 * Y);

            //Y = pow(2,HP03_Cal.Coeff.D;
            for (Y = 1, i = 0; i < HP03_Cal.Coeff.D; i++)
                Y *= 2;

            SensorReading.TempC = (250.0 + (dUT * HP03_Cal.Coeff.C6 / 65536.0) - (dUT / Y)) / 10;
            SensorReading.TempF = SensorReading.TempC * 9.0 / 5 + 32; // Conversion to deg F
            SensorReading.TempF  += WX.Calib.Temp_offs/10.0;

            Offs = (HP03_Cal.Coeff.C2 + (HP03_Cal.Coeff.C4 - 1024.0) * dUT / 16384.0)* 4;
            Sens = HP03_Cal.Coeff.C1 + (HP03_Cal.Coeff.C3 * dUT / 1024.0);
            X = (Sens * (D1.val - 7168.0) / 16384.0) - Offs;
            Pressure = ((X / 32.0) + HP03_Cal.Coeff.C7 / 10.0); // in hPa
            Pressure = Pressure * 0.0295299830714; // Conversion factor to inches Hg
            Pressure += Alt_comp; // add the altitude compensation of the barometer due to elevation
            // assigne values to global sensor struct
            SensorReading.BaromIn = Pressure + WX.Calib.Baro_offs/100.0;
            ThisState = SM_STOP;
        }
            break;

        case SM_ERROR:
            i2cBusErr = TRUE;
            I2C1_Xfer(Stop, 0);
            // don't break -- fall through to stop
        case SM_STOP:
            LATGbits.LATG0 = 0; //  HP03  XCLR signal , device inactive
            Timer = TickGet();
            ThisState++;
            break;

        case SM_IDLE: // park here until someone starts the process again.
            break;
    }
    
    return TRUE;
}
