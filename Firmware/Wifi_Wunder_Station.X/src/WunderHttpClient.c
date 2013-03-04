#define __WX_HTTP_CLIENT_C

#include "TCPIPConfig.h"
#include "TCPIP Stack/TCPIP.h"
#include "rtcc.h"
#include "WX_perm_data.h"
#include <stdlib.h>
#include <math.h>
#include "Main.h"

//#define ReportDATE_TIME_UTC
#define  Checking_for_Wunder_success

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
 * These are the tokens that Wundergrounds data ingest service requires
 */
static ROM BYTE const msgURL[] = "GET /weatherstation/updateweatherstation.php";
static ROM BYTE const msgID[] = "?ID="; // i.e. KCACONCO18
static ROM BYTE const msgPWD[] = "&PASSWORD="; //
static ROM BYTE const msgACT[] = "&action=updateraw";
static ROM BYTE const msgDateNow[] = "&dateutc=now";
#ifdef ReportDATE_TIME_UTC
static ROM BYTE const msgDate[] = "&dateutc=";
static ROM BYTE const msgDateSep[] = "-";
#endif
static ROM BYTE const msgTemp[] = "&tempf="; // temp in deg F
static ROM BYTE const msgRain[] = "&rainin="; // rain in inches/hour
static ROM BYTE const msgRaindaily[] = "&dailyrainin=";
static ROM BYTE const msgWindDir[] = "&winddir="; // in deg 0-360
static ROM BYTE const msgWindSpd[] = "&windspeedmph="; // mph -- Statute I presume --
static ROM BYTE const msgWindGstSpd[] = "&windgustmph=";
static ROM BYTE const msgBaro[] = "&baromin="; // in inches Mercury
static ROM BYTE const msgSolar[] = "&solarradiation="; // in Watts per sq meter
//static ROM BYTE const msgWingGstSpd10m[]= "&windgustmph_10m=";
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
static ROM BYTE const msgDPt[] = "&dewptf="; // Relative humidity in %
static ROM BYTE const msgRH[] = "&humidity="; // Relative humidity in %
//ROM BYTE const msgVis[]=	 	"&visibility=10";		// in NAUTICAL miles ( strange, wind is in mph..)
// additionally the following could be added.
// weather - [text] -- metar style (+RA)
// clouds - [text] -- SKC, FEW, SCT, BKN, OVC
static ROM BYTE const msgRapid[] = "&realtime=1&rtfreq=";
static ROM BYTE const msgHTTP[] = " HTTP/1.0\r\n"; // Requierd, Wunderground does not serve 0.9 http-- Do not remove the leading space
static ROM BYTE const msgAccept[] = "Accept: text/html"; // required plus contains the double NL for termination of HTTP
static ROM BYTE const msgDeliniter[] ="\r\n\r\n";       // HTTP Headerdelimiter

static enum _Http_WunderClientState  ThisState = SM_IDLE;

/*----------------------------------------------------------------------------------------------------------------------
 * TCPPUT that can handle a  ROM string and returns the number of chars attempted to output
 */
static WORD
WX_TCPPut(TCP_SOCKET theSocket, ROM BYTE const * pMsg)
{
    WORD n = 0;
    BYTE  b;

    if (pMsg != NULL)
    {
        while (b = *pMsg++)
        {
            TCPPut(theSocket, b);
            n++;
        }
    }
    return n;
}


/* ---------------------------------------------------------------------------------------------------------------------
 * Sends the const message string onto Put_WX_param()then formats argument 'w' according to n decimal points and
 *  tacks the formatted result onto the constant string by putting it into the output queues
 */
static WORD
put_WXparam_arg(TCP_SOCKET theSocket, ROM BYTE const * pMsg, short data, BYTE dec_places)
{

    WORD n = 0;
    BYTE i, b;
    char strTmp[10];

    n += WX_TCPPut( theSocket,  pMsg);

    stoa_dec(strTmp, data, dec_places);

    // Now tack on the formatted result to the output
    i = 0;
    while (b = strTmp[i++])
    {
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
/* caching ex
  // Reopen a client socket without repeating DNS or ARP
    SOCKET_INFO cache = TCPGetSocketInfo(skt);  // Call with the old socket
    skt = TCPOpen((DWORD)(PTR_BASE)&cache.remote, TCP_OPEN_NODE_INFO, cache.remotePort.Val, TCP_PURPOSE_WUNDER_CLIENT);

*/


/*----------------------------------------------------------------------------------------------------------------------
 *  This is the HTTP client state machine that prepares the connection to Wunderground and sends
 *  the report via a HTTP GET request
 */
void WunderHttpClient(void)
{
        WORD len =0;
        volatile short dat;
       	WORD			l1,l2,w;
	char			vBuffer[20];
        // Variables that span from state to state --- NEED to be static !!
        static DWORD		Timer;
	static TCP_SOCKET	MySocket = INVALID_SOCKET;
        static SOCKET_INFO      *cache = NULL;

#ifdef ReportDATE_TIME_UTC
        static BCD_RTCC         *time;
#endif
      
        if (! WX.Wunder.report_enable.Station)
            return;

	switch(ThisState)
	{
		case SM_START:
#ifdef ReportDATE_TIME_UTC
                        // get current time for the report
                        if ( (time = RTC_Read_BCD_Time()) == NULL )     // can not report if the RTC is not currently set and running
                        {
                            //putrsUART((ROM char*) "WX RTC not set\r\n");
                            ThisState = SM_IDLE;
                            break;
                        }

#endif
//putrsUART((ROM char*) "WX opening Socket\r\n");
			// Connect a socket to the remote TCP server
			//MySocket = TCPOpen( WX.Wunder.Wunder_IP.Val,TCP_OPEN_IP_ADDRESS, HTTP_PORT, TCP_PURPOSE_WUNDER_CLIENT);
                        if (cache == NULL )
                        {
                            MySocket = TCPOpen( (DWORD)(PTR_BASE)"weatherstation.wunderground.com",TCP_OPEN_ROM_HOST, HTTP_PORT, TCP_PURPOSE_WUNDER_CLIENT);
                            putrsUART((ROM char*) "Opening WU-TCP connection via DNS \r\n");
                        }
                        else
                        {
                            MySocket = TCPOpen((DWORD)(PTR_BASE)&cache->remote, TCP_OPEN_NODE_INFO, cache->remotePort.Val, TCP_PURPOSE_WUNDER_CLIENT);
                            putrsUART((ROM char*) "Opening WU-TCP connection via cache \r\n");
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
               putrsUART((ROM char*) "WU socket failed to open for 5 sec\r\n");
				}
				break;
			}
                        else
                        {
                            if (cache == NULL)
                                cache = TCPGetRemoteInfo (MySocket);
                            ThisState++;
                        }
                        break;



                case SM_SOCKET_CONNECTED:
                    //putrsUART((ROM char*) "WU socket connetced\r\n");
			Timer = TickGet();
 
			// Make certain the socket can be written to
			if(TCPIsPutReady(MySocket) < 400u) // 400 comes from buffer definition in TCIPMRF24W.h: {TCP_PURPOSE_WUNDER_CLIENT, TCP_PIC_RAM, 400,50 }
                        {
putrsUART((ROM char*) "WU socket buffer too small\r\n");
				break;
                        }
//putrsUART((ROM char*) "WX socket PutReady\r\n");

			// Place the application protocol data into the transmit buffer.  For this example, we are connected to an HTTP server, so we'll send an HTTP GET request.
			len += WX_TCPPut(MySocket, msgURL);
			len += WX_TCPPut(MySocket, msgID);
                        len += WX_TCPPut(MySocket, (BYTE *) WX.Wunder.StationID);

                        len += WX_TCPPut(MySocket, msgPWD);
                        len += WX_TCPPut(MySocket, (BYTE *) WX.Wunder.StationPW);
                        len += WX_TCPPut(MySocket, msgACT);
#ifdef ReportDATE_TIME_UTC
                        // reporting time
                        dat = mRTCCbcd2bin(time->yr)+2000;
                        len += put_WXparam_arg (MySocket,msgDate, dat, 0);
                        dat = mRTCCbcd2bin(time->mth);
                        len += put_WXparam_arg (MySocket,msgDateSep,dat, 0);
                        dat = mRTCCbcd2bin(time->day);
                        len += put_WXparam_arg (MySocket, msgDateSep,dat, 0);
                        dat =  mRTCCbcd2bin(time->hr);
                        len += put_WXparam_arg (MySocket, msgDateSep,dat, 0);
                        dat = mRTCCbcd2bin(time->min);
                        len += put_WXparam_arg (MySocket, msgDateSep,dat, 0);
                        dat = mRTCCbcd2bin(time->sec);
                        len += put_WXparam_arg (MySocket, msgDateSep,dat, 0);
#else
                        len += WX_TCPPut(MySocket, msgDateNow);
#endif
                        len += put_WXparam_arg (MySocket, msgRapid, (short)(WX.Wunder.UplnkInterval), 0);  // Send the rapid update flag and interval

                        len += put_WXparam_arg (MySocket, msgTemp, (short)(SensorReading.TempF *10), 1);  // Send the Temperature

                        if (WX.Wunder.report_enable.Rain)
                        {
                            len += put_WXparam_arg (MySocket, msgRain, (short)(SensorReading.RainIn *100), 2);  // Send the rain in inch/hr with two decials
                            len += put_WXparam_arg (MySocket, msgRaindaily, (short)(SensorReading.RainDaily *100), 2);
                        }

                        if (WX.Wunder.report_enable.Hyg)
                        {
                            len += put_WXparam_arg (MySocket, msgDPt,(short)(SensorReading.DewptF*10), 1);   // Send Dew point
                            len += put_WXparam_arg (MySocket, msgRH,(short) SensorReading.RH, 0);   // Send Relative Humidity
                        }

                        if (WX.Wunder.report_enable.Wind)
                        {
                            len += put_WXparam_arg (MySocket, msgWindSpd, (short)(SensorReading.AvgWindSpd *10), 1); // Send the wind speed
                            len += put_WXparam_arg (MySocket, msgWindGstSpd, (short)(SensorReading.Wind_gust*10), 1);// Send the Windgust

                            if (SensorReading.AvgWindSpd <1)
                                 len += put_WXparam_arg (MySocket, msgWindDir, (short) SensorReading.Wind_dir, 0);    // Send the momentary vane direction if there was no wind
                            else
                                len += put_WXparam_arg (MySocket, msgWindDir, (short) SensorReading.AvgWindDir, 0);    // Send the Wind Direction
                        }

                        len += put_WXparam_arg (MySocket, msgBaro, (short)(SensorReading.BaromIn*100), 2);  // Send the Barometer reading, convert to inches Mercury at 0 degC
                        
                        if (WX.Wunder.report_enable.Sol)
                            len += put_WXparam_arg (MySocket, msgSolar,(short) SensorReading.SolRad, 0); // Send the solar radiation index in watts/ sq Meter ( estimated)

			len += WX_TCPPut(MySocket, msgHTTP);
			len += WX_TCPPut(MySocket, msgAccept);
                        len += WX_TCPPut(MySocket, msgDeliniter);

                        if (len >= 400 )
                        {
// putrsUART((ROM char*) "WX TCP BUFFER OVERFLOW-- Locking up");

                            LED1_IO = 1;
                            LED2_IO = 1;
                            LED3_IO = 1;
                            while(1);
                        }
			// Send the packet
			TCPFlush(MySocket);
                        putrsUART((ROM char*) "Uploading to WU\r\n");
			ThisState++;
                       break;


		case SM_PROCESS_RESPONSE:

#ifdef Checking_for_Wunder_success
// Checking for the word success dosn't really buy anything, since success only means that we where talking to thr right URL
// and not that that the data sent was accepted.

			// Check to see if the remote node has disconnected 
			if(!TCPIsConnected(MySocket))
                        {
                                putrsUART((ROM char*) "WU HOST disconnected\r\n");
                            	ThisState = SM_DISCONNECT;// Do not break;  We might still have data in the TCP RX FIFO waiting for us
			}

	
                        // The Wunderground server always replies with the word "success" as long as Station ID and password match
                        // The fact that the server replies "success" does not indicate that the data was actually ingested into the
                        // system, so testing for the return of "success" only indicates what we are talking to Wunderground
                        // and with proper credentials


		        // The full reply message, including header, is:
                        // HTTP/1.0 200 OK
                        // Content-type: text/html
                        // Date: Tue, 25 Sep 2012 18:33:43 GMT
                        // Content-Length: 8
                        // Connection: close
                        //
                        // success
                        //
                        if (w = TCPIsGetReady(MySocket))
                        {

                            l1 = TCPFindROMArray(MySocket,msgDeliniter,4,0,FALSE); // find end of Headers, beginning of Content

                            if ( l1 < 0xffff) // if the double \r\n was found  check for the word success
                            {
                                 l2 = TCPFindROMArray(MySocket,"\n",1,l1+4,FALSE); // find nl after content
                                 if (l2 < 0xfff)
                                 {
                                     TCPGetArray(MySocket, NULL, l1+4);      // skip all data before "Content"

                                     l2 = TCPGetArray(MySocket, (BYTE *)vBuffer, sizeof(vBuffer)-1);      // read "success" or error meesage
   
                                     vBuffer[sizeof(vBuffer)-1] = 0;                         // terminate
                                     putsUART((ROM char*) "WU says: ");
                                     putsUART(vBuffer);
                                     putsUART((ROM char*) "\r");
                                  
                                     if (strncmp ( vBuffer, "success",7u) == 0)
                                     {

                                         TCPDiscard(MySocket);
                                         ThisState = SM_DISCONNECT;
                                         break;
                                     }
                                      // if no "success" is  sent from host we time out because the host eventually closes the connection
                                 }

                            }
                            else
                                TCPGetArray(MySocket, NULL, l1);      // skip headers
                        }
#endif
                        break;
	
		case SM_DISCONNECT:
			// Close the socket so it can be used again later
                        //  TCPClose(MySocket);
                        TCPDisconnect(MySocket);        // This sends a "FIN"
                        TCPDisconnect(MySocket);        // This sends a "RST" to force the connection closed and immediatly reliquisches the socket
			MySocket = INVALID_SOCKET;
			ThisState = SM_IDLE;
                        putrsUART((ROM char*) "Socket Disconnected\r\n\n");
			break;
	
		case SM_IDLE:
			// Do nothing , park here until someone starts the process again 
                         break;
	}
}

