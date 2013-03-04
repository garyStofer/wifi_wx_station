// Include all headers for any enabled TCPIP Stack functions
#include "TCPIP Stack/TCPIP.h"
#include "math.h"
#include "rtcc.h"
#include "WX_perm_data.h"
#include "wind_rain_cnt.h"
#include "Once_per_second.h"
#include "Configs/Wunder_cfg.h"
/*
 *  This task is called once per second and collects the stations sensor readings and kisks of reporting to wunderground
 */
static struct tagWind_avg {
    float NS_comp;
    float EW_comp;
    float Spd;
} Wind_avg[MAX_UPLINK_INTERVAL] = {0};

static float WindGustSamples[WIND_GUST_INTERVAL]= {0};


static unsigned char RAIN_Count_Samples[RAIN_SAMPLES_P_HOUR] = {0};
static unsigned short rain_sample_ndx = 0;

void
Once_perSecTask(void)
{
    static unsigned short sec_count = 0;        // Count will wrap around
    short s_tmp;
    float sum_NS, sum_EW, sum_spd, f_tmp;
    int i;
    float gust;

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
        HIH6130_startMeasure();
        HP03_startMeasure();
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
    SensorReading.Plus5V = PWR_5V_ADCBUFF * (3.3/1024*2); // ADC is referenced of the 3.3V PS , AN5 input has 2:1 voltage divider

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

    Wind_avg[sec_count%WX.Wunder.UplnkInterval].Spd = SensorReading.Wind_speed = ((float)Wind_1Sec_count * WX.Calib.Wind_AN_CalFactor)/WX.Calib.Wind_counts; // momentary wind speed
    WindGustSamples[sec_count%WIND_GUST_INTERVAL]  =  SensorReading.Wind_speed;

    //SensorReading.Wind_gust is the maximum of the individual wind speed samples in WIND_GUST_INTERVAL
    gust = 0;
    for (i = 0; i < WIND_GUST_INTERVAL; i++)
    {
        if (WindGustSamples[i] > gust)
            gust = WindGustSamples[i];
    }
    SensorReading.Wind_gust = gust;

    // The Wind direction
    // the PWM of the wind-vane does not fully go between 0 and 100 %PWM i.e not fully between DC 0V and DC 5V
    // Winddir_min_ADC and Winddir_max_adc are calibrated values considering the variance in 5V from the powersupply
    // and voltage losses/offset on the cable to the wind vane

    s_tmp = (WIND_ADCBUFF - WX.Calib.WDir_min)* 360.0 / WX.Calib.WDir_max ; //This is from the PWM of the magnetic rotary encoder

    // precautions
    if (s_tmp > 360)
        s_tmp = 360;
    else if (s_tmp < 0)
        s_tmp = 0;

    SensorReading.Wind_dir = (s_tmp + WX.Calib.WDir_offs) % 360; // Momentary wind diretion
    f_tmp = SensorReading.Wind_dir * 6.2832 / 360.0; // convert to radians
    // Vector addition of NS and EW wind vector samples for average calculation
    Wind_avg[sec_count%WX.Wunder.UplnkInterval].NS_comp = cos(f_tmp) * SensorReading.Wind_speed;
    Wind_avg[sec_count%WX.Wunder.UplnkInterval].EW_comp = sin(f_tmp) * SensorReading.Wind_speed;

    // Average and Peak calculation for WX_UPLINK_INTERVAL/Sec
    // Pre-increment so that it runs for WX_UPLINK_INTERVAL before data is sent to wunderground
    if (++sec_count % WX.Wunder.UplnkInterval == 0)
    {
        // Calculate the average wind direction from the NS and EW vectors
        sum_spd = sum_NS = sum_EW = 0.0;
        for (i = 0; i < WX.Wunder.UplnkInterval; i++)
        {
            sum_NS += Wind_avg[i].NS_comp;
            sum_EW += Wind_avg[i].EW_comp;
            sum_spd += Wind_avg[i].Spd;
        }

        SensorReading.AvgWindSpd = sum_spd / i; // The linear average of the speed in interval
        f_tmp = atan2(sum_EW, sum_NS); // the vector average of the direction -- using atan2() to get the 4 quadrands resolved automaticaly
        SensorReading.AvgWindDir = f_tmp * 360 / 6.2832; // Convert to deg


        if (SensorReading.AvgWindDir < 0)
            SensorReading.AvgWindDir += 360;

        WunderSendData(); // starts the HTTP client process to send data to Wunderground
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
