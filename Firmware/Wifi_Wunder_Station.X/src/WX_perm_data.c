#include <string.h>
#include "WX_perm_data.h"
#include "Configs/Wunder_cfg.h"
#include "APP_cfg.h"
#include "Configs/Wunder_cfg.h"

t_WX_Sensor_data SensorReading = {0};
t_WX_perm_data WX;       // all WX station related data

void
WX_writePerm_data(void)
{
    unsigned short loc = sizeof (NVM_VALIDATION_STRUCT) + sizeof (APP_CONFIG);

    if (loc + sizeof (WX) >= MPFS_RESERVE_BLOCK)
    {
        putrsUART((ROM char*) "MPFS_RESERVE_BLOCK too small!");

        while (1);
    }

    XEEBeginWrite(loc);
    XEEWriteArray((BYTE *) & WX, sizeof (WX));
    XEEEndWrite();
}

void
WX_readPerm_data(void)
{
    unsigned short loc = sizeof (NVM_VALIDATION_STRUCT) + sizeof (APP_CONFIG) ;

    if (loc + sizeof (WX) >= MPFS_RESERVE_BLOCK)
    {
        loc += sizeof (WX);

        putrsUART((ROM char*) "MPFS_RESERVE_BLOCK too small!");

        while (1);
    }

    XEEReadArray(loc, (BYTE*) & WX, sizeof (WX));

    // if EEPROM is empty
    if (WX.Calib.Rain_counts == 0xffff)
        WX_perm_data_init_toDefault();


}

void WX_perm_data_init_toDefault( void)
{
   memset(&WX,0,sizeof(WX));

   strcpy(WX.Wunder.StationID,MY_DEFAULT_WUNDER_STATION_ID);
   strcpy(WX.Wunder.StationPW,MY_DEFAULT_WUNDER_STATION_PWD);
   WX.Wunder.Lat =0.0;
   WX.Wunder.Lon = 0.0;
   strcpy(WX.Station.User_name,HTTP_USERNAME);
   strcpy(WX.Station.password,HTTP_PASSWORD);


   // WX.Wunder.StationElev = 0;
   // WX.Wunder.Enabled=0;

   WX.TimeServer.NIST1.v[0] =MY_DEFAULT_NIST1_IP_ADDR_BYTE1 ;
   WX.TimeServer.NIST1.v[1] =MY_DEFAULT_NIST1_IP_ADDR_BYTE2 ;
   WX.TimeServer.NIST1.v[2] =MY_DEFAULT_NIST1_IP_ADDR_BYTE3 ;
   WX.TimeServer.NIST1.v[3] =MY_DEFAULT_NIST1_IP_ADDR_BYTE4 ;
   
   WX.TimeServer.NIST2.v[0] =MY_DEFAULT_NIST2_IP_ADDR_BYTE1;
   WX.TimeServer.NIST2.v[1] =MY_DEFAULT_NIST2_IP_ADDR_BYTE2;
   WX.TimeServer.NIST2.v[2] =MY_DEFAULT_NIST2_IP_ADDR_BYTE3;
   WX.TimeServer.NIST2.v[3] =MY_DEFAULT_NIST2_IP_ADDR_BYTE4;

   //  WX.Calib.Baro_offs = WX.Calib.WDir_offs = 0;
   WX.Calib.Sol_gain = 1000;
   WX.Calib.Rain_counts = 100;
   WX.Calib.WDir_min = 1023;
   
   WX.Mail.port = 25;
   WX.Wunder.UplnkInterval = UPLINK_INTERVAL_DEFAULT;
   WX.Wunder.TZ_offset = GMT_TZ_OFFSET_DEFAULT;
   WX.Calib.Wind_counts = WIND_COUNT_CAL_DEFAULT;
   WX.Calib.Wind_AN_CalFactor = AN_CAL_FACTOR_DEFAULT;
   WX_writePerm_data();
}

// Convert a signed short to an ascii string with 'n' decimal places
// dec_places == 0 == no decial point
// dec_places == 1 == decimal point and 1 digit after
//  buff must be at least 9 bytes long for worst case: -0.00001\0
void
stoa_dec( char * buff,  long data, short dec_places)
{
    short digit;
    short n;            // current digit beeing converted
    long div;          // The decade divisor
    char leading0 = 1;  // flag to insert leading 0 if needed

    if ( data == 0)     // The trivial case -- nothing to calculate, simply set and return
    {
        *buff++ = '0';
        if (dec_places)
        {
            *buff++ = '.';
            *buff++ = '0';
        }
        *buff++ = 0;
        return;
    }

    if (data < 0)     // add in the minus sign, then proceed with positive number
    {
        *buff++ = '-';
        data = -data;
    }

    for ( n=8,div=10000000; div ; n--,div/=10)     // convert each digit from the front
    {
        if (n-dec_places == 0)                  // insert decimal point and leading 0 if needed
        {
            if (leading0)                       // insert a leading 0 if value to be printed is <1
                *buff++ = '0';

            *buff++ = '.';
            leading0 =0;
        }

        digit = data/div;
        data -=  digit*div;

        if (digit == 0 && leading0)         // skipp leading 0's
            continue;

        *buff++ = digit +'0';
        leading0 =0;
     }

    *buff++ = 0;
}
