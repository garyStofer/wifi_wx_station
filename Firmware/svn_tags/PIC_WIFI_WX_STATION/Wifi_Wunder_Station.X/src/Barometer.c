// Interface functions to access one or the other of the possible Barometer devices
// The individual init function fill pass of fail depending wheter the particiular device is connect
// The Bus_errors so obtained will then be used to steer the code to invoke the correct read functions.

#include "TCPIP Stack/TCPIP.h"
#include "WX_perm_data.h"
#include "math.h"
#include "Barometer.h"
#include "HP03_baro.h"
#include "BMP085_baro.h"

float Alt_comp;
static BOOL HP03_BusErr = TRUE;
static BOOL BMP085_BusErr = TRUE;
// Calculates the compesation in inches Hg pressure for the elevation of the station

static void
calc_alt_comp(short Station_elev)
{

    float tmp;
    // Calculate altitude correction for station height -- formula from http://www.csgnetwork.com/barcorrecthcalc.html
    tmp = 60 + 459.67; // fixed Rankine temp-- 60F == std temp at sea level
    Alt_comp = (29.92126 * (1 - (1 / pow(10, ((0.0081350 * Station_elev) / (tmp + (0.00178308 * Station_elev)))))));
}
void
Baro_init(short station_elevation)
{
     calc_alt_comp(station_elevation);

     BMP085_BusErr = BMP085_init( );    // check and init bosh BMP805 barometer

      if (BMP085_BusErr )   // If BMP805 is not responding check and init HP03 device
          HP03_BusErr = HP03_init();


}
void
Baro_startMeasure( void )
{
    if (!BMP085_BusErr )
        BMP085_startMeasure();
    else if (!HP03_BusErr)
        HP03_startMeasure();
    else
    {

    }
}


void
Baro_Read_Process(void )
{
     if (!BMP085_BusErr )
            BMP085_Read_Process( );
     else if (!HP03_BusErr)
         HP03_Read_Process( );
}
