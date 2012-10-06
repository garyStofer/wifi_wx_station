#define __WX_HTTP_CLIENT_C

#include "TCPIPConfig.h"
#include "TCPIP Stack/TCPIP.h"
#include "rtcc.h"
#include "WX_perm_data.h"
#include <stdlib.h>
#include <math.h>

enum _Http_WunderClientState
{
        SM_START = 0,
        SM_SOCKET_OBTAINED,
        SM_PROCESS_RESPONSE,
        SM_DISCONNECT,
        SM_IDLE
};


static ROM BYTE const msgURL[] = "GET /weatherstation/updateweatherstation.php";
static ROM BYTE const msgID[] = "?ID="; // i.e. KCACONCO18
static ROM BYTE const msgPWD[] = "&PASSWORD="; //
static ROM BYTE const msgACT[] = "&action=updateraw";
static ROM BYTE const msgDate[] = "&dateutc=";
static ROM BYTE const msgDateSep[] = "-";
static ROM BYTE const msgTemp[] = "&tempf="; // temp in deg F
static ROM BYTE const msgWindDir[] = "&winddir="; // in deg 0-360
static ROM BYTE const msgWindSpd[] = "&windspeedmph="; // mph -- Statute I presume --
static ROM BYTE const msgWindGstSpd[] = "&windgustmph=";
static ROM BYTE const msgBaro[] = "&baromin="; // in inches Mercury
static ROM BYTE const msgSolar[] = "&solarradiation="; // in Watts per sq meter
//ROM BYTE const msgWingGstSpd10m[]= "&windgustmph_10m=";
//ROM BYTE const msgWingGstDir10m[]= "&windgustdir_10m=300";
//ROM BYTE const msgWingGstDir[]= "&windgustdir=300";
static ROM BYTE const msgDPt[] = "&dewptf="; // Relative humidity in %
static ROM BYTE const msgRH[] = "&humidity="; // Relative humidity in %
//ROM BYTE const msgVis[]=	 	"&visibility=10";		// in NAUTICAL miles ( strange, wind is in mph..)
// additionally the following could be added.
// weather - [text] -- metar style (+RA)
// clouds - [text] -- SKC, FEW, SCT, BKN, OVC

static ROM BYTE const msgHTTP[] = " HTTP/1.0\r\n"; // Requierd, Wunderground does not serve 0.9 http-- Do not remove the leading space
static ROM BYTE const msgAccept[] = "Accept: text/html"; // required plus contains the double NL for termination of HTTP
static ROM BYTE const msgDeliniter[] ="\r\n\r\n";       // HTTP Headerdelimiter

static BYTE  WunderConnectionSuccess = 0;
static enum _Http_WunderClientState  ThisState = SM_IDLE;

// TCPPUT that can handle a  ROM string and returns the number of chars attempted to output
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
/* Sends the const message string onto Put_WX_param()then formats argument 'w' according to n decimal points and tacks the
        formatted result onto the constant string by putting it into the output queues
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

BOOL
WunderIsConnectionSuccess (void)
{
    return WunderConnectionSuccess;
}

void
WunderSendData(  void )
{
    if (ThisState == SM_IDLE)
        ThisState = SM_START;
}


/*****************************************************************************

  ***************************************************************************/
void WunderHttpClient(void)
{
    WORD len =0;

        BCD_RTCC                *time;
	WORD			l1,l2,w;
	char			vBuffer[20];
	static DWORD		Timer;
	static TCP_SOCKET	MySocket = INVALID_SOCKET;
	
      
        if (! WX.Wunder.Enabled)
            return;

	switch(ThisState)
	{
		case SM_START:
                        WunderConnectionSuccess = 0;
                   //     IP_addr = WX.Wunder.Wunder_IP.Val;
                        // get current time for the report
                        if ( (time = RTC_Read_BCD_Time()) == NULL )     // can not report if the RTC is not currently set and running
                        {
putrsUART((ROM char*) "WX NO RTC \r\n");
                            ThisState = SM_IDLE;
                            break;
                        }
putrsUART((ROM char*) "WX opening Socket\r\n");
			// Connect a socket to the remote TCP server
			MySocket = TCPOpen( WX.Wunder.Wunder_IP.Val,TCP_OPEN_IP_ADDRESS, HTTP_PORT, TCP_PURPOSE_WUNDER_CLIENT);
			
			// Abort operation if no TCP socket of type TCP_PURPOSE_GENERIC_TCP_CLIENT is available
			// If this ever happens, you need to go add one to TCPIPConfig.h
			if(MySocket == INVALID_SOCKET)
				break;

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
putrsUART((ROM char*) "WX socket failed to open\r\n");
				}
				break;
			}
putrsUART((ROM char*) "WX socket connetced\r\n");
 
			Timer = TickGet();
 
			// Make certain the socket can be written to
			if(TCPIsPutReady(MySocket) < 300u) // 300 comes from buffer definition in TCIPMRF24W.h: {TCP_PURPOSE_WUNDER_CLIENT, TCP_ETH_RAM, 300,50 }
                        {
putrsUART((ROM char*) "WX socket buffer too small\r\n");
				break;
                        }
putrsUART((ROM char*) "WX socket PutReady\r\n");

			// Place the application protocol data into the transmit buffer.  For this example, we are connected to an HTTP server, so we'll send an HTTP GET request.
			len += WX_TCPPut(MySocket, msgURL);
			len += WX_TCPPut(MySocket, msgID);
                        len += WX_TCPPut(MySocket, (BYTE *) WX.Wunder.StationID);

                        len += WX_TCPPut(MySocket, msgPWD);
                        len += WX_TCPPut(MySocket, (BYTE *) WX.Wunder.StationPW);
                        len += WX_TCPPut(MySocket, msgACT);

                        len += put_WXparam_arg (MySocket, msgDate, mRTCCbcd2bin(time->yr)+2000, 0);
                        len += put_WXparam_arg (MySocket, msgDateSep, mRTCCbcd2bin(time->mth), 0);
                        len += put_WXparam_arg (MySocket, msgDateSep, mRTCCbcd2bin(time->day), 0);
                        len += put_WXparam_arg (MySocket, msgDateSep, mRTCCbcd2bin(time->hr), 0);
                        len += put_WXparam_arg (MySocket, msgDateSep, mRTCCbcd2bin(time->min), 0);
                        len += put_WXparam_arg (MySocket, msgDateSep, mRTCCbcd2bin(time->sec), 0);

                        len += put_WXparam_arg (MySocket, msgTemp, (short)(SensorReading.TempF *10), 1);  // Send the Temperature
                     //   len += put_WXparam_arg (MySocket, msgDPt,(short)(SensorReading.DewptF*10), 1);   // Send Dew point
                     //   len += put_WXparam_arg (MySocket, msgRH,(short) SensorReading.RH, 0);   // Send Relative Humidity
                     //   len += put_WXparam_arg (MySocket, msgWindSpd, (short)(SensorReading.Wind_speed *10), 1); // Send the wind speed
                     //   len += put_WXparam_arg (MySocket, msgWindGstSpd, (short)(SensorReading.Wind_gust*10), 1);// Send the Windgust
                     //   len += put_WXparam_arg (MySocket, msgWindDir, (short) SensorReading.Wind_dir, 0);    // Send the Wind Direction
                        len += put_WXparam_arg (MySocket, msgBaro, (short)(SensorReading.BaromIn*100), 2);  // Send the Barometer reading, convert to inches Mercury at 0 degC
                   //     len += put_WXparam_arg (MySocket, msgSolar,(short) SensorReading.SolRad, 0); // Send the solar radiation index in watts/ sq Meter ( estimated)

			len += WX_TCPPut(MySocket, msgHTTP);
			len += WX_TCPPut(MySocket, msgAccept);
                        len += WX_TCPPut(MySocket, msgDeliniter);

                        if (len >= 300 )
                        {
                            putrsUART((ROM char*) "WX TCP BUFFER OVERFLOW");
                            while(1);
                        }
			// Send the packet
			TCPFlush(MySocket);
		
			ThisState++;
                       break;

		case SM_PROCESS_RESPONSE:
			// Check to see if the remote node has disconnected 
			if(!TCPIsConnected(MySocket))
			{
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
                                     vBuffer[l2] = 0;                         // terminate
putsUART(vBuffer);
                                     if (strncmp ( vBuffer, "success",7u) == 0)
                                     {
                                         WunderConnectionSuccess = 1;
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
   			break;
	
		case SM_DISCONNECT:
			// Close the socket so it can be used again later
                        TCPDisconnect(MySocket);
			MySocket = INVALID_SOCKET;
			ThisState = SM_IDLE;
putrsUART((ROM char*) "WX socket Disconnected\r\n");
			break;
	
		case SM_IDLE:
			// Do nothing unless the user pushes BUTTON1 and wants to restart the whole connection/download process
			if(BUTTON2_IO == 0u)
                        {
				ThisState = SM_START;
putrsUART((ROM char*) "WX start\r\n");
                        }
                         break;
	}
}

