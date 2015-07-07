// Interface functions to access one or the other of the possible Hygrometer devices
// The individual init function fill pass of fail depending wheter the particiular device is connect
// The Bus_errors so obtained will then be used to steer the code to invoke the correct read functions.

#include "TCPIP Stack/TCPIP.h"
#include "WX_perm_data.h"
#include "WX_sensor_data.h"
#include "math.h"
#include "Hygrometer.h"

void
Hygro_init(void)
{
      HIH6130_init( );    // check and init Honewell Hygrometer

      if (HIH6130_BusErr )   // If HIH6130 is not responding check and init SI7021
           SI7021_init();
}

void
Hygro_startMeasure( void )
{
    if (! HIH6130_BusErr )
        HIH6130_startMeasure();
    else if (!SI7021_BusErr)
        SI7021_startMeasure();
    else
    {
        SensorReading.RH = SensorReading.DewptF = SensorReading.DewptC =0;
        // if only the SI7021 had a bus error then the temp will still be available from the BMP085 baro 
    }

}

void
Hygro_Read_Process(void )
{
    float Y;
    BOOL new_measure;

    if (!HIH6130_BusErr )
       new_measure = HIH6130_Read_Process( );
    else if (!SI7021_BusErr)
       new_measure = SI7021_Read_Process( );

    if ( HIH6130_BusErr && SI7021_BusErr)
    {
         // No hygrometer -- Can't calculate Dew Point
         return;
    }
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
    // SI Hygro sends values >100% for condensing and user offset can add up to >100%
    // Limit RH for all cases
    if ( new_measure )
    {
        if (SensorReading.RH >100 )
            SensorReading.RH = 100;

        Y = ((17.271 * SensorReading.TempC) / (237.7+SensorReading.TempC ))+ log(SensorReading.RH/100);
        SensorReading.DewptC = 237.7 * Y/(17.271-Y);
        SensorReading.DewptF = SensorReading.DewptC*9/5.0+32;
    }

}
