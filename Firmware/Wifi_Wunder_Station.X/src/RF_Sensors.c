#include "rtcc.h"
#include "RF_Sensors.h"
#include "WX_perm_data.h"
#include "WX_sensor_data.h"

#define UART_buff2 60
t_RF_sens_data RF_sens[N_RF_SENSORS];
/*
 *  This function reads from the UART ring buffer and parses the message from a RF sensor attached to the network
 *  Sensors send a colon seperated string starting with the worrd "SENS" and containing the word RSSI as the second to last tag
 *  A sensor returns 4 floating point readings along with a unique sensor ID and sensor type value. The first of the the 4 readings
 *  is always the battery voltage, followed by the sensors main measurment -- the last two readings are raw voltage readings.
 *
 * This function fills in a position in the global RF_sens array upon reception of a new message from a sensor.
 */
void
Read_RF_sensors(void)
{
    char * cp;
    static char in_buff[UART_buff2];
    volatile unsigned short n;
    t_RF_sens_data sens_tmp;

    while (n = UART1_GetStringLen()) // read all strings that are ready in the input ring buffer of the UART1
    {
        BOOL reading_valid = FALSE;

        if (n <= sizeof (in_buff)) // if the string fits in out buffer
        {
            reading_valid = FALSE;

            n = UART1_GetString(in_buff);
            cp = strtok(in_buff, ":");

            if (strcmp(cp, "SENS") == 0) // a sentence from a RF sensor
            {
                if (cp = strtok(NULL, ":"))
                    sens_tmp.ID = atoi(cp);

                if (cp = strtok(NULL, ":"))
                    sens_tmp.Typ = atoi(cp);

                if (cp = strtok(NULL, ":"))
                    sens_tmp.v[0] = atof(cp);

                if (cp = strtok(NULL, ":"))
                    sens_tmp.v[1] = atof(cp);

                if (cp = strtok(NULL, ":"))
                    sens_tmp.v[2] = atof(cp);

                if (cp = strtok(NULL, ":"))
                    sens_tmp.v[3] = atof(cp);

                if (cp = strtok(NULL, ":"))
                {
                    // If we received the string RSSI: at the end of the records we consider the transmission successful
                    if (strcmp(cp, "RSSI") == 0)
                    {
                        if (cp = strtok(NULL, ":"))
                        {
                            sens_tmp.rssi = atoi(cp);
                            reading_valid = TRUE;       // If we have a valid reading we record the time it was received.
                            // We don't re-read the time from the RTC but use the last captured time from the once per second task
                            memcpy( &sens_tmp.time, &_RTC_time, sizeof( _RTC_time));

                        }
                    }

                }

                if (reading_valid)
                {
                    int i;
                    // see if we have an entry for this sensor already -- if so copy the new values into it
                    for ( i=0; i< N_RF_SENSORS ;i++)
                    {
                        if ( RF_sens[i].ID == sens_tmp.ID)
                        {
                            memcpy( &RF_sens[i],  &sens_tmp, sizeof(sens_tmp ) );
                            break;
                        }
                    }

                    // else this is the first time we see this sensor ID, add it to the list of reporting sensors if there is room
                    if (i >= N_RF_SENSORS)
                    {
                        for ( i=0; i< N_RF_SENSORS ;i++)

                        if ( RF_sens[i].ID <= 0)
                        {
                            memcpy( &RF_sens[i],  &sens_tmp, sizeof(sens_tmp ) );
                            break;
                        }

                    }


                }
            }

        }
        else // Clear out a string that's too long for this buffer
            UART1_GetString(NULL);

    }

}

