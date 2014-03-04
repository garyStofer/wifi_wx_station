#include "TCPIPConfig.h"
#include "TCPIP Stack/TCPIP.h"
#include "rtcc.h"
#include "WX_perm_data.h"
#include <stdlib.h>
#include <math.h>
#include "Main.h"
#include "WunderHttpClient.h"


enum _Http_WunderClientState
{
        SM_START = 0,
        SM_SOCKET_OBTAINED,
        SM_SOCKET_CONNECTED,
        SM_PROCESS_RESPONSE,
        SM_DISCONNECT,
        SM_IDLE
};

/* ---------------------------------------------------------------------------------------------------------------------
 * These are the tokens that Wundergrounds / PWS data ingest service requires
 */
//#define WU_URL "38.102.137.157"                       // This is a direct path bypassing their load balancing routing
#define WU_URL "weatherstation.wunderground.com"        // This is the correct path so that it goes  through their load balancing center
#define PWS_URL "pwsweather.com"
#define WXBUG_URL "data.backyard2.weatherbug.com"

#define msgURL_WU "/weatherstation/updateweatherstation.php"
#define msgURL_PWS "/pwsupdate/pwsupdate.php"
#define msgURL_WXbg "/data/livedata.aspx"

#define  msgID "?ID=" // Station Identifier
#define  msgPWD "&PASSWORD=" // Station Password
#define  msgACT "&action=updateraw"
#define  msgDateNow "&dateutc=now"

#define msgDate "&dateutc="
#define msgDateSep  "-"
#define msgHrsSep  "+"
#define msgMinSep "%3A"

#define msgTemp "&tempf=" // temp in deg F
#define msgRain  "&rainin=" // rain in inches/hour
#define msgRaindaily  "&dailyrainin="
#define msgWindDir  "&winddir=" // in deg 0-360
#define msgWindSpd  "&windspeedmph=" // mph -- Statute I presume --
#define msgWindGstSpd  "&windgustmph="
#define msgBaro  "&baromin=" // in inches Mercury
#define msgSolar  "&solarradiation=" // in Watts per sq meter
#define msgSWtype  "&softwaretype=WuWxSt"
// static ROM BYTE const msgWingGstSpd10m[]= "&windgustmph_10m="; This is not read by Wunderground
//ROM BYTE const msgWingGstDir10m[]= "&windgustdir_10m=300";
//ROM BYTE const msgWingGstDir[]= "&windgustdir=300";

/*
winddir - [0-360 instantaneous wind direction]
windspeedmph - [mph instantaneous wind speed]
windgustmph - [mph current wind gust, using software specific time period]
windgustdir - [0-360 using software specific time period]
windspdmph_avg2m  - [mph 2 minute average wind speed mph]
winddir_avg2m - [0-360 2 minute average wind direction]
windgustmph_10m - [mph past 10 minutes wind gust mph ]
windgustdir_10m - [0-360 past 10 minutes wind gust direction]
 */
#define msgDPt "&dewptf=" // Relative humidity in %
#define msgRH "&humidity=" // Relative humidity in %
//ROM BYTE const msgVis[]=	 	"&visibility=10";		// in NAUTICAL miles ( strange, wind is in mph..)
// additionally the following could be added.
// weather - [text] -- metar style (+RA)
// clouds - [text] -- SKC, FEW, SCT, BKN, OVC
#define msgRapid "&realtime=1&rtfreq="

#define msgAccept "Accept: text/html\r\n"// required 
#define msgDeliniter "\r\n"       // HTTP Header delimiter

static enum _Http_WunderClientState  ThisState = SM_IDLE;

WORD
WX_TCPPutC(TCP_SOCKET theSocket, BYTE b)
{
    putcUART(b);
    TCPPut(theSocket, b);
    return 1;
}
/*----------------------------------------------------------------------------------------------------------------------
 * TCPPUT that can handle a  ROM string and returns the number of chars attempted to output
 */
WORD
WX_TCPPut(TCP_SOCKET theSocket, ROM char const * pMsg)
{
    WORD n = 0;
    BYTE  b;

    if (pMsg != NULL)
    {
        while (b = *pMsg++)
        {
            WX_TCPPutC( theSocket, b);
            n++;
        }
    }
    return n;
}


/* ---------------------------------------------------------------------------------------------------------------------
 * Sends the const message string onto Put_WX_param()then formats argument 'w' according to n decimal points and
 *  tacks the formatted result onto the constant string by putting it into the output queues
 */
WORD
put_WXparam_arg(TCP_SOCKET theSocket, ROM char const * pMsg, short data, BYTE dec_places)
{

    WORD n = 0;
    BYTE i, b;
    char strTmp[10];

    n += WX_TCPPut( theSocket,  (char *) pMsg);

    stoa_dec(strTmp, data, dec_places);

    // Now tack on the formatted result to the output
    i = 0;
    while (b = strTmp[i++])
    {
        putcUART(b);
        TCPPut(theSocket, b);
        n++;
    }

    return n;
}

/*----------------------------------------------------------------------------------------------------------------------
 * Kiks off a data transmit process
 */
void
WunderSendData(  void )
{
    if (ThisState == SM_IDLE)
        ThisState = SM_START;
}


/*----------------------------------------------------------------------------------------------------------------------
 *  This is the HTTP client state machine that prepares the connection to Wunderground and sends
 *  the report via a HTTP GET request
 */
void
WunderHttpClient(void)
{
        WORD len =0;
        volatile short dat;
       	WORD			l1,l2,w;
	char			vBuffer[20];
        // Variables that span from state to state --- NEED to be static !!
        static DWORD		Timer;
	static TCP_SOCKET	MySocket = INVALID_SOCKET;
        static SOCKET_INFO      *cache = NULL;
        char * url;
        static BCD_RTCC         *time;
        ROM char  * msg_url;
        char cache_ID = 0;

        switch ( WX.Wunder.report_enable.Station )
        {
             case WU_CLIENT:     //WU
                url = WU_URL;
                msg_url =  msgURL_WU;
                break;
           
            case PWS_CLIENT:     //PWS
                 url = PWS_URL;
                 msg_url =  msgURL_PWS;
                break;
                           
            case WXBUG_CLIENT:     //WXbg
                url = WXBUG_URL;
                msg_url =  msgURL_WXbg;
                break;
                        
            default:
                cache_ID =0;
                return;
        }

        //clear cache if user swites from one to the other mid stream
        if ( cache_ID != WX.Wunder.report_enable.Station)
            cache = NULL;

	switch(ThisState)
	{
		case SM_START:
                        if (WX.Wunder.report_enable.Station != WU_CLIENT )   // PWS has dateutc as mendatory, WU uses dateutc=now
                        {// get current time for the report
                            if ( (time = RTC_Read_BCD_Time()) == NULL )     // can not report if the RTC is not currently set and running
                            {
                                putrsUART((ROM char*) "WX RTC not set! Can not upload data\r\n");
                                ThisState = SM_IDLE;
                                break;
                            }
                        }

                        if (cache == NULL )
                        {
                            putrsUART((ROM char*) "Opening via DNS to ");
                            putrsUART((ROM char*) url);
                            putrsUART((ROM char*) "\r\n");
                            MySocket = TCPOpen((DWORD)(PTR_BASE) url, TCP_OPEN_ROM_HOST, HTTP_PORT, TCP_PURPOSE_WUNDER_CLIENT);
                         
                        }
                        else
                        {
                            MySocket = TCPOpen((DWORD)(PTR_BASE)&cache->remote, TCP_OPEN_NODE_INFO, cache->remotePort.Val, TCP_PURPOSE_WUNDER_CLIENT);
                            putrsUART((ROM char*) "Opening via cache \r\n");
                        }

                        // Abort operation if no TCP socket of type TCP_PURPOSE_WUNDER_CLIENT is available
			// If this ever happens, you need to go add one to TCPIPConfig.h
			if(MySocket == INVALID_SOCKET)
                        {   
                            LED2_IO = 1;
                            LED3_IO = 1;
                            break;
                        }

			ThisState++;
			Timer = TickGet();
			break;

		case SM_SOCKET_OBTAINED:
			// Wait for the remote server to accept our connection request
			if(!TCPIsConnected(MySocket))
			{
				// Time out if too much time is spent in this state
				if(TickGet()-Timer > 5*TICK_SECOND)
				{
					// Close the socket 
					TCPDisconnect(MySocket);
					MySocket = INVALID_SOCKET;
					ThisState = SM_IDLE;
                                        cache = NULL;
                                        putrsUART((ROM char*) "Socket failed to open for 5 sec\r\n");
				}
				break;
			}
                        else
                        {
                            if (cache == NULL)
                            {
                                cache = TCPGetRemoteInfo (MySocket);
                                cache_ID = WX.Wunder.report_enable.Station;
                            }
                            ThisState++;
                        }
                        break;



                case SM_SOCKET_CONNECTED:
//putrsUART((ROM char*) "Socket connetced\r\n");
			Timer = TickGet();
 
			// Make certain the socket can be written to
			if(TCPIsPutReady(MySocket) < 512u) // 512 comes from buffer definition in TCIPMRF24W.h: {TCP_PURPOSE_WUNDER_CLIENT, TCP_PIC_RAM, 400,50 }
                        {
putrsUART((ROM char*) "Socket buffer too small\r\n");
				break;
                        }
//putrsUART((ROM char*) "WX socket PutReady\r\n");

			// Place the application protocol data into the transmit buffer.
                        len += WX_TCPPut(MySocket, "GET ");
                        len += WX_TCPPut(MySocket, msg_url);
                        len += WX_TCPPut(MySocket, msgID);
                        len += WX_TCPPut(MySocket, WX.Wunder.StationID);

                        if (WX.Wunder.report_enable.Station == WXBUG_CLIENT)       // WXbg
                        {
                            len += WX_TCPPut(MySocket,"&Key=");
                            len += WX_TCPPut(MySocket,WX.Wunder.StationPW);
                            // len += WX_TCPPut(MySocket,"&num=31352");  // Seems to work without the NUM parameter just as well
                            // I never could get clarification as to what this would be good for from WX-Bug support
                        }
                        else
                        {
                            len += WX_TCPPut(MySocket,msgPWD);
                            len += WX_TCPPut(MySocket,WX.Wunder.StationPW);

                        }
           
                     
                        if (WX.Wunder.report_enable.Station != WU_CLIENT)   // if not WU
                        {// reporting time for  PWS and WxBug
                            dat = mRTCCbcd2bin(time->yr)+2000;
                            len += put_WXparam_arg (MySocket,msgDate, dat, 0);

                            len += WX_TCPPut(MySocket,msgDateSep);
                            len += WX_TCPPutC(MySocket,(time->mth>>4) +'0');    //tens of months from bcd to asc
                            len += WX_TCPPutC(MySocket,(time->mth&0x0f) +'0');  // ones of month from bcd to asc

                            len += WX_TCPPut(MySocket,msgDateSep);
                            len += WX_TCPPutC(MySocket,(time->day>>4) +'0');    // tens
                            len += WX_TCPPutC(MySocket,(time->day&0x0f) +'0');  // ones

                            len += WX_TCPPut(MySocket,msgHrsSep);
                            len += WX_TCPPutC(MySocket,(time->hr>>4) +'0');    // tens
                            len += WX_TCPPutC(MySocket,(time->hr&0x0f) +'0');  // ones

                            len += WX_TCPPut(MySocket,msgMinSep);
                            len += WX_TCPPutC(MySocket,(time->min>>4) +'0');    // tens
                            len += WX_TCPPutC(MySocket,(time->min&0x0f) +'0');  // ones

                            len += WX_TCPPut(MySocket,msgMinSep);
                            len += WX_TCPPutC(MySocket,(time->sec>>4) +'0');    // tens
                            len += WX_TCPPutC(MySocket,(time->sec&0x0f) +'0');  // ones
                        }
                    
                        else
                        {
                            len += WX_TCPPut(MySocket, msgDateNow);
                            len += put_WXparam_arg (MySocket, msgRapid, (short)(WX.Wunder.UplnkInterval), 0);  // Send the rapid update flag and interval

                        }
                        // start sending measurment data
                        len += put_WXparam_arg (MySocket, msgTemp, (short)(SensorReading.TempF *10), 1);  // Send the Temperature
/*
                        if (WX.Wunder.report_enable.Station == WXBUG_CLIENT)   // These are mendatory, but we don't have data for them ever
                        {
                            len += put_WXparam_arg (MySocket, "&tempfhi=",0, 1);
                            len += put_WXparam_arg (MySocket, "&tempflo=", 0, 1);
                        }
*/

                        if (WX.Wunder.report_enable.Rain)
                        {
                            len += put_WXparam_arg (MySocket, msgRain, (short)(SensorReading.RainIn *100), 2);  // Send the rain in inch/hr with two decials
                            len += put_WXparam_arg (MySocket, msgRaindaily, (short)(SensorReading.RainDaily *100), 2);

                            if (WX.Wunder.report_enable.Station == WXBUG_CLIENT) // some more mendatory fields for WXbug
                            {
                                len += put_WXparam_arg (MySocket, "&monthlyrainin", (short)(SensorReading.RainDaily *100), 2);
                                len += put_WXparam_arg (MySocket, "&Yearlyrainin", (short)(SensorReading.RainDaily *100), 2);
                            }
                        }
                        else if (WX.Wunder.report_enable.Station == WXBUG_CLIENT) // For WX bug this is a mendatory parameter and must be sent as 0s
                        {
                            len += put_WXparam_arg (MySocket, msgRain, 0, 2);  // Send the rain in inch/hr with  decials
                            len += put_WXparam_arg (MySocket, msgRaindaily, 0, 2);
                            len += put_WXparam_arg (MySocket, "&monthlyrainin", 0, 2);
                            len += put_WXparam_arg (MySocket, "&Yearlyrainin", 0, 2);
                        }

                        if (WX.Wunder.report_enable.Hyg)
                        {
                            len += put_WXparam_arg (MySocket, msgDPt,(short)(SensorReading.DewptF*10), 1);   // Send Dew point
                            len += put_WXparam_arg (MySocket, msgRH,(short) SensorReading.RH, 0);   // Send Relative Humidity
                        }

                        if (WX.Wunder.report_enable.Wind)
                        {
                            len += put_WXparam_arg (MySocket, msgWindSpd, (short)(SensorReading.AvgWindSpd *10), 1); // Send the wind speed

                            // Use a 5 minute gust reading for Wunderground since they record samples every 5 minutes for the graph -- their WindGust10M parameter doesn't work
                            len += put_WXparam_arg (MySocket, msgWindGstSpd, (short)(SensorReading.Wind_gust_5min *10), 1);// Send the Windgust --

                            if (SensorReading.AvgWindSpd <1)
                                len += put_WXparam_arg (MySocket, msgWindDir, (short) SensorReading.Wind_dir, 0);    // Send the momentary vane direction if there was no wind
                            else
                                len += put_WXparam_arg (MySocket, msgWindDir, (short) SensorReading.AvgWindDir, 0);    // Send the Wind Direction
                        }
                        else if (WX.Wunder.report_enable.Station == WXBUG_CLIENT)   // for WXbug this is a mendatory parameter and must be sent as 0's
                        {
                             len += put_WXparam_arg (MySocket, msgWindSpd, 0, 1);
                             len += put_WXparam_arg (MySocket, msgWindGstSpd, 0, 1);
                             len += put_WXparam_arg (MySocket, msgWindDir, 0, 0);
                        }

                        len += put_WXparam_arg (MySocket, msgBaro, (short)(SensorReading.BaromIn*100), 2);  // Send the Barometer reading, convert to inches Mercury at 0 degC
                        
                        if (WX.Wunder.report_enable.Sol)
                            len += put_WXparam_arg (MySocket, msgSolar,(short) SensorReading.SolRad, 0); // Send the solar radiation index in watts/ sq Meter ( estimated)

                        if (WX.Wunder.report_enable.Station == PWS_CLIENT)   // if PWS
                            len += WX_TCPPut(MySocket, msgSWtype);
                       
                        if (WX.Wunder.report_enable.Station == WXBUG_CLIENT)   // if WXbg
                            len += WX_TCPPut(MySocket, "&action=live");
                        else
                            len += WX_TCPPut(MySocket, msgACT);


                        len += WX_TCPPut(MySocket, " HTTP/1.1\r\nHOST: ");       // HTTP1.1 with mendatory HOST header
                        len += WX_TCPPut(MySocket, url );
                        len += WX_TCPPut(MySocket, msgDeliniter );
                        len += WX_TCPPut(MySocket, "Accept: text/html");
                        len += WX_TCPPut(MySocket, msgDeliniter);
                        len += WX_TCPPut(MySocket, msgDeliniter);

                        if(TCPIsPutReady(MySocket) < 1u)
                            putrsUART((ROM char*) "TCP was not put-ready -- overflow?");
                        
                        if (len >= 512 )
                        {
                            putrsUART((ROM char*) "WX TCP BUFFER OVERFLOW-- Locking up");

                            LED1_IO = 1;
                            LED2_IO = 1;
                            LED3_IO = 1;
                            while(1);
                        }
                        
			// Send the packet
                        LED2_IO = 1;    // indicate sending of WU data
			TCPFlush(MySocket);
                        putrsUART((ROM char*) "Uploading WX to host\r\n");
			ThisState++;
                       break;


		case SM_PROCESS_RESPONSE:
// Checking for the word success dosn't really buy anything, since success only means that we where talking to the right URL
// and not that that the data sent was accepted.

			// Check to see if the remote node has disconnected 
			if(!TCPIsConnected(MySocket))
                        {
                                putrsUART((ROM char*) "WX HOST has disconnected\r\n");
                            	ThisState = SM_DISCONNECT;// Do not break;  We might still have data in the TCP RX FIFO waiting for us
			}


                        // The Wunderground server always replies with the word "success" as long as Station ID and password match
                        // The fact that the server replies "success" does not indicate that the data was actually ingested into the
                        // system, so testing for the return of "success" only indicates what we are talking to Wunderground
                        // and with proper credentials.
                        // WU does NOT send anything back, "success" or otherwise, if the data or credentials are misformed. It is
                        // therefore not possible to give some kind of fail feedback to the user, i.e. a red light  etc..


		        // The full reply message for WU, including header, is:
                        // HTTP/1.0 200 OK
                        // Content-type: text/html
                        // Date: Tue, 25 Sep 2012 18:33:43 GMT
                        // Content-Length: 8
                        // Connection: close
                        //
                        // success
                        //

                       //  weatherforyou pws its a html file with body etc..
                        if (w = TCPIsGetReady(MySocket))
                        {
                             putsUART((ROM char*) "WX host says: ");

                             l1 = sizeof(vBuffer)-1;    // leave space for null

                             while ( (l2 = TCPGetArray(MySocket, (BYTE *)vBuffer,l1))>0)      // read "success" or error meesage
                             {
                                vBuffer[l2] = 0;           // put null at end
                                putsUART(vBuffer);
                             }

                             putsUART((ROM char*) "\r\n");

                             TCPDiscard(MySocket);
                             ThisState = SM_DISCONNECT;
                             break;
                        }
                        break;
	
		case SM_DISCONNECT:
			// Close the socket so it can be used again later
                        //  TCPClose(MySocket);
                        TCPDisconnect(MySocket);        // This sends a "FIN"
                        TCPDisconnect(MySocket);        // This sends a "RST" to force the connection closed and immediatly reliquisches the socket
			MySocket = INVALID_SOCKET;
			ThisState = SM_IDLE;
                        putrsUART((ROM char*) "WX sock disconnected\r\n\r\n");
                        LED2_IO = 0;    // indicate done sending of WU data
 			break;
	
		case SM_IDLE:
			// Do nothing , park here until someone starts the process again 
                         break;
	}
}

