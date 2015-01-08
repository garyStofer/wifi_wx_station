
/*
 *  This task is called once per second and collects the stations sensor readings then kiks off reporting to the cloud server
 */

// Include all headers for any enabled TCPIP Stack functions
#include "TCPIP Stack/TCPIP.h"
#include "math.h"
#include "rtcc.h"
#include "WX_perm_data.h"
#include "wind_rain_cnt.h"
#include "Once_per_second.h"
#include "Configs/Wunder_cfg.h"

#define WIND_AVG_INTERVAL 128 // Must be power of 2 and must match width of index below  128 Seconds , 2 min 8 seconds
                              // is is the maximum time the wind direction and speed are averaged -- For slow reporting when
                              // the reporting interval is above this time, the last 128 seconds of readings will be averaged
#define LONG_GUST_COUNT 5     // This is to collect the wind gust for 5 times WIND_AVG_INTERVAL seconds (10 min 40 secs)
                              // so that Wunderground records all gust readings with their 5 to 10 minute data sampling time.

struct tag_WindAvgNdx{
    unsigned short n:7;         // To make the indexing math automatic on wrap around of circular buffer
};

static struct tagWind_avg {
    float NS_comp;
    float EW_comp;
    float Spd;
} Wind_avg[WIND_AVG_INTERVAL] = {0};


static float LongWindGustSamples[ LONG_GUST_COUNT] ;


static unsigned char RAIN_Count_Samples[RAIN_SAMPLES_P_HOUR] = {0};
static unsigned short rain_sample_ndx = 0;



void
Once_perSecTask(void)
{
    static unsigned short sec_count = 0;        // Count will wrap around
    static unsigned char LongGust_ndx = 0;
    short s_tmp;
    float sum_NS, sum_EW, sum_spd, f_tmp;
    int i;
    struct tag_WindAvgNdx Wind_ndx ;

    // Blink green LED
    LED1_IO ^= 1;

    // start the daily rain accumulation at midnight.
    if (RTC_isMidnight(RTC_Read_BCD_Time(),WX.Wunder.TZ_offset))        // this also reads the RTC every one second
    {
        SensorReading.RainDaily = 0.0;
        NIST_TimeSyncRequest();                             // Daily refresh the RTC with NIST time
    }

    if (sec_count % BARO_HYG_TEMP_MEAS_Interval == 0)
    {
        Baro_startMeasure();
        Hygro_startMeasure();
     }

    if (sec_count % RAIN_MEAS_Interval == 0)
    {

        s_tmp = RAIN_COUNTER;
        RAIN_COUNTER=0;

        RAIN_Count_Samples[rain_sample_ndx++] = s_tmp;
        SensorReading.RainDaily += s_tmp/(float) WX.Calib.Rain_counts;

        if ( rain_sample_ndx >= RAIN_SAMPLES_P_HOUR )
             rain_sample_ndx =0;

       // sum up all the individual Rain counts for the last hour to calculate the rain amounth in inches that fell over the last hour
        s_tmp = 0;
        for (i = 0; i < RAIN_SAMPLES_P_HOUR; i++)
        {
            s_tmp += RAIN_Count_Samples[i];
        }

       SensorReading.RainIn =   s_tmp  / (float) WX.Calib.Rain_counts;

     }

    SensorReading.SolRad = (short) (((float) SOL_ADCBUFF * WX.Calib.Sol_gain) / 1000.0);
 

    // The Wind Speed:
    // Davis Cup anemometer conversion to MPH is 2.25 x revolution/sec
    // The wind speed data is aquired as follows:
    // The RTCC ISR captures counter/Timer2 once per second and stores the reading in Var Wind_1Sec_count
    // The Once_perSecond task executes once following a one second RTCC tic change.
    // The one second momentary wind spead is calculated and added to an averaging array that spans the entire duration
    // of the update interval.
    // The average and peak values for the update interval are calculated and reported to Wunderground, while the momentary data
    // is reported on the stations local display.
    // The 10 minute peak gust could be calculated and reported to Wunderground, but it seems that they do not record or display it

    // convert counts to MPH, since the measure window is 1 seconds and there are 7 pulses per revolution
    // the following formual gives MPH in  miles resolution
    // MPH = wind_counts_per_sec  *2.25 /7;
    // or MPH = wind_counts_per_sec * 0.32142

    
    SensorReading.Wind_speed = ((float)Wind_1Sec_count * WX.Calib.Wind_AN_CalFactor)/WX.Calib.Wind_counts; // momentary wind speed
    Wind_avg[sec_count%WIND_AVG_INTERVAL].Spd = SensorReading.Wind_speed ;


    //SensorReading.Wind_gust is the maximum of the individual wind speed samples in WIND_AVG_INTERVAL ( ~2 Minutes )
    f_tmp = 0;
    for (i = 0; i < WIND_AVG_INTERVAL; i++)
    {
        if (Wind_avg[i].Spd > f_tmp)
            f_tmp = Wind_avg[i].Spd;
    }
    SensorReading.Wind_gust = f_tmp;

    // store the 2 minute peaks in the long Gust array ( ~10 Minutes)
    if (sec_count%WIND_AVG_INTERVAL == 0)
    {
        LongWindGustSamples[LongGust_ndx++ ] = SensorReading.Wind_gust;
        if (LongGust_ndx  >= LONG_GUST_COUNT)
            LongGust_ndx = 0;
    }


    // The Wind direction
    // the PWM of the wind-vane does not fully go between 0 and 100 %PWM i.e not fully between DC 0V and DC 5V
    // Winddir_min_ADC and Winddir_max_adc are calibrated values considering the variance in 5V from the powersupply
    // and voltage losses/offset on the cable to the wind vane

    s_tmp = (WIND_ADCBUFF - WX.Calib.WDir_min)* 360.0 /( WX.Calib.WDir_max - WX.Calib.WDir_min); //This is from the PWM of the magnetic rotary encoder

    // precautions
    if (s_tmp > 360)
        s_tmp = 360;
    else if (s_tmp < 0)
        s_tmp = 0;

    SensorReading.Wind_dir = (s_tmp + WX.Calib.WDir_offs) % 360; // Momentary wind diretion

    f_tmp = SensorReading.Wind_dir * 6.2832 / 360.0; // convert to radians
    // Vector addition of NS and EW wind vector samples for average calculation
    Wind_avg[sec_count%WIND_AVG_INTERVAL].NS_comp = cos(f_tmp) * SensorReading.Wind_speed;
    Wind_avg[sec_count%WIND_AVG_INTERVAL].EW_comp = sin(f_tmp) * SensorReading.Wind_speed;




    // Average and Peak calculation for WX_UPLINK_INTERVAL/Sec
    // Pre-increment so that it runs for WX_UPLINK_INTERVAL before data is sent out
    if (++sec_count % WX.Wunder.UplnkInterval == 0)
    {
        // Calculate the average wind direction from the NS and EW vectors
        sum_spd = sum_NS = sum_EW = 0.0;
     
        Wind_ndx.n = (sec_count-1)%WIND_AVG_INTERVAL;  // last location that was filled with wind data 
        
        s_tmp = WX.Wunder.UplnkInterval;
        if (s_tmp > WIND_AVG_INTERVAL)
            s_tmp = WIND_AVG_INTERVAL;
         
        for (i=0;  i<s_tmp ; i++)
        {
            sum_NS += Wind_avg[Wind_ndx.n].NS_comp;
            sum_EW += Wind_avg[Wind_ndx.n].EW_comp;
            sum_spd += Wind_avg[Wind_ndx.n].Spd;
            Wind_ndx.n--;
        }

        SensorReading.AvgWindSpd = sum_spd / s_tmp; // The linear average of the speed in wind average interval -- not the vector average --
        f_tmp = atan2(sum_EW, sum_NS); // the vector average of the direction -- using atan2() to get the 4 quadrands resolved automaticaly
        SensorReading.AvgWindDir = f_tmp * 360 / 6.2832; // Convert to deg


        if (SensorReading.AvgWindDir < 0)
            SensorReading.AvgWindDir += 360;

        // collect the long gust ( ~10 min)
        f_tmp = 0;
        for (i = 0; i < LONG_GUST_COUNT; i++)
        {
           if ( LongWindGustSamples[i] > f_tmp)
               f_tmp = LongWindGustSamples[i];
        }
        SensorReading.Wind_gust_5min = f_tmp;

        WunderSendData(); // starts the HTTP client process to send data to Wunderground and others that do HTTP GET protocol
        CWOPSendData();   // CWOP and WunderSendata are mutually exclusice  by the Uplink mode variable
     }
 
}

t_wind_cal_temp  WDIR_cal_tmp;
/* 
 * Utility to find min, max and north on wind vane 
 */
void
Wind_dir_cal ( void )
{
    // Kludge to turn yourself off if the user naviagets away from the WinDir cal page
    // broser event onunload doesn't seem to work

    if ( TickGet() > WDIR_cal_tmp.timeout )
         WDIR_cal_tmp.DoWindDirCal = FALSE;

    WDIR_cal_tmp.WindDir_north = WIND_ADCBUFF;

    if ( WDIR_cal_tmp.WindDir_north < WDIR_cal_tmp.WindDir_min )
        WDIR_cal_tmp.WindDir_min = WDIR_cal_tmp.WindDir_north;

    if (WDIR_cal_tmp.WindDir_north > WDIR_cal_tmp.WindDir_max)
            WDIR_cal_tmp.WindDir_max = WDIR_cal_tmp.WindDir_north;
}
