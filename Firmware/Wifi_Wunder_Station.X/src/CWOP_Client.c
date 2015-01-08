#include "TCPIPConfig.h"
#include "TCPIP Stack/TCPIP.h"
#include "WX_perm_data.h"
#include <stdlib.h>
#include <math.h>
#include "Main.h"
#include "WunderHttpClient.h"
#include "rtcc.h"

#define Debug_CWOP_Response
//#define CWOP_SEND_TIME
//#define POSTSENDWAIT

enum CWOP_ClientState
{
        SM_START = 0,
        SM_SOCKET_OBTAINED,
        SM_GET_SERVER_VERSION,
        SM_SEND_LOGIN,
        SM_WAIT_LOGIN_ACK,
        SM_SEND_APRS_REPORT,
#ifdef POSTSENDWAIT
        SM_POST_SEND_WAIT,
#endif
        SM_DISCONNECT,
        SM_IDLE
};


static enum CWOP_ClientState  ThisState = SM_IDLE;


// Function to format CWOP responses with n digits before the decial pt and leading 0's --
static char *
s_to_a( char * buff,  short data, short sig_places, short dec_places)
{
    short digit;
    short n;            // current digit beeing converted
    short div;          // The decade divisor
    char *b = buff;

    if (data < 0)       // add in the minus sign, then proceed with positive number
    {
        *buff++ = '-';
        data = -data;
    }

    for ( n = sig_places + dec_places; n>0  ; n--)     // convert each digit from the front
    {
        if (dec_places && (n - dec_places == 0))       // insert decimal point if needed
        {
            *buff++ = '.';
        }
        
        div = pow(10,n-1);
        digit = data/div;
        data -=  digit*div;
        *buff++ = digit +'0';
     }

    *buff++ = 0;
    return b;
}

/*----------------------------------------------------------------------------------------------------------------------
 * Kiks off a data transmit process
 */
void
CWOPSendData(  void )
{   
    if (WX.Wunder.report_enable.Station == CWOP_CLIENT)
    {
        if (ThisState == SM_IDLE)
            ThisState = SM_START;
    }
}



/*----------------------------------------------------------------------------------------------------------------------
 *  This is the TCP client state machine that prepares the connection to CWOP and sends
 *  the report via a CWOP defined connection protocol in a APRS define data format.
 */
short
CWOP_Client(void)
{
       
  	char	buff[60];
        // Variables that span from state to state --- NEED to be static !!
        static DWORD		Timer;
	static TCP_SOCKET	MySocket = INVALID_SOCKET;
        short tmp;
        float ftmp;
        short retry=0;
        static BCD_RTCC         *time;
#ifdef Debug_CWOP_Response
        WORD    len;
#endif
 

        if ( WX.Wunder.report_enable.Station != 4)
            return retry;


	switch(ThisState)
	{
		case SM_START:
                        putrsUART((ROM char*) "\r\nOpening socket to CWOP");
                        MySocket = TCPOpen((DWORD)(PTR_BASE) "cwop.aprs.net", TCP_OPEN_ROM_HOST, 14580, TCP_PURPOSE_WUNDER_CLIENT);
                         
                        // Abort operation if no TCP socket of type TCP_PURPOSE_WUNDER_CLIENT is available
			// If this ever happens, you need to go add one to TCPIPConfig.h
			if(MySocket == INVALID_SOCKET)
                        {   
                            LED2_IO = 1;
                            LED3_IO = 1;
                            putrsUART((ROM char*) "\r\n!!NO SOCKET avaialble for CWOP!!");
                            ThisState == SM_IDLE;
                            break;
                        }
#ifdef CWOP_SEND_TIME
                        if ( (time = RTC_Read_BCD_Time()) == NULL )     // can not report if the RTC is not currently set and running
                        {
                                putrsUART((ROM char*) "WX RTC not set! Can not upload data\r\n");
                                ThisState = SM_IDLE;
                                break;
                        }
#endif
			ThisState++;
			Timer = TickGet();
			break;


		case SM_SOCKET_OBTAINED:
			// Wait for the remote server to accept our connection request
			if(!TCPIsConnected(MySocket))
			{
				// Time out if too much time is spent in this state
				if(TickGet()-Timer > 30*TICK_SECOND)
				{
                                        LED3_IO = 1;
					ThisState = SM_DISCONNECT;
                                        putrsUART((ROM char*) "CWOP sock failed to open >30 sec\r\n");
                                        retry=1;
				}
				break;
			}
                       
                       ThisState++;
                       Timer = TickGet();
                       break;

                case SM_GET_SERVER_VERSION:

#ifdef Debug_CWOP_Response
                         if ((len = TCPIsGetReady(MySocket)) > 9)
                         {
                             putsUART("\r\nCWOP says: ");

                             if ( len > sizeof(buff))
                                 len = sizeof(buff);

                             TCPGetArray(MySocket, (BYTE *)buff, len);
                             buff[len-1] = 0;
                             
                             putsUART(buff);
                             TCPDiscard(MySocket);
                             ThisState++;
                             Timer = TickGet();
                             break;
                         }
                
#else
                         if (TCPIsGetReady(MySocket) >= 2 )
                         {
                             if ( TCPFindROMArray(MySocket,"\r\n",2,0,FALSE)!= 0xFFFF)
                             {
                                TCPDiscard(MySocket);
                                ThisState++;
                                Timer = TickGet();

                                break;

                             }
                         }
#endif
                         else
                         {
                            if(TickGet()-Timer > 20*TICK_SECOND)
                            {
                                    LED3_IO = 1;
                                    ThisState = SM_DISCONNECT;
                                    putrsUART((ROM char*) "\r\nTimed Out:CWOP did not send SW version");
                                    break;
                            }

                         }
                         break;
                       

                case SM_SEND_LOGIN:
			// Make certain the socket can be written to
			if(TCPIsPutReady(MySocket) < 512u) // 512 comes from buffer definition in TCIPMRF24W.h: {TCP_PURPOSE_WUNDER_CLIENT, TCP_PIC_RAM, 400,50 }
                        {
                            ThisState = SM_DISCONNECT;
                            putrsUART((ROM char*) "\r\nSock buffer too small");
                            break;
                        }

			// Place the application protocol data into the transmit buffer.  For this example, we are connected to an HTTP server, so we'll send an HTTP GET request.
                        putrsUART((ROM char*) "\r\nSending login credentials:\r\n");
                        WX_TCPPut(MySocket, "user ");
                        WX_TCPPut(MySocket, WX.Wunder.StationID);
                        WX_TCPPut(MySocket, " pass ");
                        WX_TCPPut(MySocket, WX.Wunder.StationPW);
                        WX_TCPPut(MySocket, " vers WUWX 1.0");
                        WX_TCPPut(MySocket,"\r\n");
                        // Send the login packet
                        LED2_IO = 1;    // indicate sending data

                        TCPFlush(MySocket);
                      	ThisState++;
                        Timer = TickGet();
                        break;


                case SM_WAIT_LOGIN_ACK:
#ifdef Debug_CWOP_Response
                         if ((len = TCPIsGetReady(MySocket)) >9)
                         {
                             putsUART("\r\nCWOP says: ");

                             if ( len > sizeof(buff))
                                 len = sizeof(buff);

                             TCPGetArray(MySocket, (BYTE *)buff, len);
                             buff[len-1] = 0;
                             
                             putsUART(buff);
                             TCPDiscard(MySocket);
                             ThisState++;
                             Timer = TickGet();
                             break;
                         }
#else
                         if (TCPIsGetReady(MySocket) >= 2 )
                         {
                             if ( TCPFindROMArray(MySocket,"\r\n",2,0,FALSE)!= 0xFFFF)
                             {
                                TCPDiscard(MySocket);
                                ThisState++;
                                Timer = TickGet();
#ifndef NO_BREAK
                                break;
#endif
                             }
                         }
#endif
                         else
                         {
                            if(TickGet()-Timer > 20*TICK_SECOND)
                            {
                                    LED3_IO = 1;
                                    ThisState = SM_DISCONNECT;
                                    putrsUART((ROM char*) "\r\nTimed out:CWOP did not send login ack");
                                    break;
                            }
                         }
                         break;

		case SM_SEND_APRS_REPORT:
                    	if(TCPIsPutReady(MySocket) < 250u)
                        {
                            ThisState = SM_DISCONNECT;
                            putrsUART((ROM char*) "\r\nSock buffer <250, too small to send data");
                            break;
                        }
                        putrsUART((ROM char*) "\r\nSending APRS data:\r\n");
                        WX_TCPPut(MySocket, WX.Wunder.StationID);
                        WX_TCPPut(MySocket,">APRS,TCPIP*:"); // The APRS boiler plate header
#ifdef CWOP_SEND_TIME
                        WX_TCPPut(MySocket,"@");
                        WX_TCPPutC(MySocket,(time->day>>4) +'0');    // tens
                        WX_TCPPutC(MySocket,(time->day&0x0f) +'0');  // ones

                        WX_TCPPutC(MySocket,(time->hr>>4) +'0');    // tens
                        WX_TCPPutC(MySocket,(time->hr&0x0f) +'0');  // ones

                        WX_TCPPutC(MySocket,(time->min>>4) +'0');    // tens
                        WX_TCPPutC(MySocket,(time->min&0x0f) +'0');  // ones
                        WX_TCPPut(MySocket,"z"); // The "z" indicates that I don't send a time
#else
                        WX_TCPPut(MySocket,"!"); // The "!" indicates that I don't send a time
#endif

                        // i.e. WX_TCPPut(MySocket,"3758.73N/12159.69W");
                        // Our location. This is ddmm.mm -- i.e. degrees, minutes and hundreths of minutes.
                        ftmp = fabs(WX.Wunder.Lat);
                        WX_TCPPut(MySocket, s_to_a(buff, (short) ftmp,2,0 ));         // in dd format
                        ftmp -= abs((short)WX.Wunder.Lat);
                        WX_TCPPut(MySocket, s_to_a(buff, (short) (ftmp*6000),2,2 ));  // in mm.mm format

                        if (WX.Wunder.Lat <0)
                            WX_TCPPut(MySocket, "S/");
                        else
                            WX_TCPPut(MySocket, "N/");

                        ftmp = fabs(WX.Wunder.Lon);
                        WX_TCPPut(MySocket, s_to_a(buff, (short) ftmp,3,0 ));      //longitude has 3 ddd with leading 0's
                        ftmp -= abs((short)WX.Wunder.Lon);
                        WX_TCPPut(MySocket, s_to_a(buff, (short) (ftmp*6000),2,2 ));  // in mm.mm format

                        if (WX.Wunder.Lon <0)
                            WX_TCPPut(MySocket, "W");
                        else
                            WX_TCPPut(MySocket, "E");
                

                        // Wind is mendatory to report -- sending "..." if Wind is not measured
                        if (WX.Wunder.report_enable.Wind)
                        {
                            if (SensorReading.AvgWindSpd >1)
                                tmp = SensorReading.AvgWindDir;
                            else
                                tmp = SensorReading.Wind_dir;

                            WX_TCPPut( MySocket,"_");      // THE WIND dir
                            WX_TCPPut( MySocket,s_to_a( buff,tmp,3,0 ));
                            WX_TCPPut( MySocket,"/");      // THE WIND speed
                            WX_TCPPut( MySocket,s_to_a(buff, (short) SensorReading.AvgWindSpd,3,0 ));
                            WX_TCPPut( MySocket,"g");      // THE WIND speed
                            WX_TCPPut( MySocket,s_to_a(buff, (short) SensorReading.Wind_gust_5min,3,0 ));
                        }
                        else
                            WX_TCPPut( MySocket,"_000/000g...");      // Space holder for no-wind reporting

                        // Temp is mendatory to report
                        WX_TCPPut(MySocket, "t");
                        WX_TCPPut(MySocket, s_to_a(buff,(short)SensorReading.TempF,3,0));  // Send the Temperature in whole deg F

                        if (WX.Wunder.report_enable.Rain)
                        {
                            WX_TCPPut( MySocket,"r");
                            WX_TCPPut( MySocket,s_to_a(buff, (short)(SensorReading.RainIn*100) ,3,0 ));
                            WX_TCPPut( MySocket,"P");
                            WX_TCPPut( MySocket,s_to_a(buff, (short) (SensorReading.RainDaily*100) ,3,0 ));
                        }

                        if (WX.Wunder.report_enable.Hyg)
                        {
                            WX_TCPPut( MySocket,"h");
                            tmp =(short)SensorReading.RH;
                            if (tmp>=100)       // send 00 for 100% or condensing
                                tmp = 0;
                            WX_TCPPut( MySocket,s_to_a( buff,tmp ,2,0 ));       // CWOP calculates dewpoint
                        }

                        WX_TCPPut( MySocket,"b");
                        tmp = SensorReading.BaromIn * 338.6388157895;   // Connvert to 1/10 of millibar
                        WX_TCPPut( MySocket,s_to_a( buff,tmp ,5,0 ));        
                        // the end -- send station software idetifier
                        WX_TCPPut( MySocket,"-WWX");
                        WX_TCPPut( MySocket,"\r\n");       // Without this only some of the servers take the data

                        TCPFlush(MySocket);
                        ThisState++;
                        Timer = TickGet();
                        break;

#ifdef POSTSENDWAIT
                case SM_POST_SEND_WAIT:
                        if(TickGet()-Timer > 1*TICK_SECOND)
                        {
                            ThisState++;
                        }
                        break;
#endif
		case SM_DISCONNECT:
			// Close the socket so it can be used again later
                        //  TCPClose(MySocket);
                        TCPDisconnect(MySocket);        // This sends a "FIN"
                        TCPDisconnect(MySocket);        // This sends a "RST" to force the connection closed and immediatly reliquisches the socket
			MySocket = INVALID_SOCKET;
			ThisState = SM_IDLE;
                        putrsUART((ROM char*) "\r\nSock disconnected\r\n");
                        LED2_IO = 0;    //Clear yellow and red LEDs
                        LED3_IO = 0;
 			break;
	
		case SM_IDLE:
			// Do nothing , park here until someone starts the process again 
                         break;
	}
        return retry;
}

