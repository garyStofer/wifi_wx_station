#include "TCPIPConfig.h"
#include "TCPIP Stack/TCPIP.h"
#include "WX_perm_data.h"
#include <stdlib.h>
#include <math.h>
#include "Main.h"
#include "WunderHttpClient.h"
#include "rtcc.h"
#include "UART1.h"


#define Debug_CWOP_Response

//#define POSTSENDWAIT

#define APRS_BUFF_SZ 128
static char aprs_buff[APRS_BUFF_SZ+1];  // Buffer to assemble the APRS message in
static unsigned char aprs_buf_ndx = 0 ;

static short
aprs_buff_cat (char * s)
{
    while ( *s != 0)
    {
        if ( aprs_buf_ndx >= APRS_BUFF_SZ)
                break;

        aprs_buff[aprs_buf_ndx++] = *s++;

    }
    aprs_buff[aprs_buf_ndx] = 0;
    return aprs_buf_ndx;
}
static short
aprs_buff_set(char * s)
{
    aprs_buf_ndx = 0;
    return aprs_buff_cat (s);
}

enum CWOP_ClientState
{
        SM_START = 0,
        SM_SOCKET_OBTAINED,
        SM_GET_SERVER_VERSION,
        SM_SEND_LOGIN,
        SM_WAIT_LOGIN_ACK,
        SM_SEND_CWOP_PREAMBLE,
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

// Kick-off function to send a report to CWOP/APRS via TCP/IP
void
CWOPSendData(  void )
{   
    if (WX.Wunder.report_enable.Station == CWOP_CLIENT && WiFi_isConnected() )
    {
        if (ThisState == SM_IDLE)
            ThisState = SM_START;
    }
}

// Kick-off function to send a report to APRS-RF via modem and 2M ham radio tuned to the local APRS frequency (144.390Mhz in the US)
// This function also initializes some aspects of the modem on first run, namemly the ham radio station callsign , ssid and APRS
// display symbol.
// NOTE: the Station ID must be set to the HAM radio station callsign, and a current ham radio licence (Technician) needs to be present
// to operate a RF APRS station.
void
APRSSendData(  void )
{
    static char ModemInitialized = 0;
    
    if (WX.Wunder.report_enable.Station == APRS_CLIENT)
    {
        if (ModemInitialized == 0)
        {   // UART1 is initialized in HW_Init
            ModemInitialized = 1;
            OUT0_IO = 0;   // controls the powerswitch for the radio -- Low active
            LED3_IO = 1;   // user feedback
            DelayMs(2000); // Delay for radio bootup

            putrsUART("APRS modem init:");
            DelayMs(50);
            aprs_buff_set("c");         // set call sign from station ID
            aprs_buff_cat(WX.Wunder.StationID);
            UART1_PutS(aprs_buff);
            putrsUART(aprs_buff);
            DelayMs(50);

            UART1_PutS("sc13");         // set staion ssid to 13 as suggested for WX stations
            DelayMs(50);
            UART1_PutS( "ls_");         // set Symbol to "_" indicating Weather stations
            DelayMs(50);

            UART1_PutS("mcAPRS");       // set message recipient and destignation to APRS as suggested for WX stations
            DelayMs(50);
            UART1_PutS("dAPRS");
            DelayMs(50);

            UART1_PutS("s1WIDE1-1");       // set PATH SSIDs
            DelayMs(50);
            UART1_PutS("s2WIDE2-2");
            DelayMs(50);

            UART1_PutS("w200");       // set preamble and tail delay for PTT
            DelayMs(50);
            UART1_PutS("W50");
            DelayMs(50);

            UART1_PutS("S");    // Save Configuration
            DelayMs(50);



            UART1_PutS( "!>WunderWXstation, See http://WWS.us.to\n"); // This is the status message
            DelayMs(1000); // makes sure that the message went on the air
            OUT0_IO = 1;   // disables the powerswitch for the radio,  low active
            LED3_IO = 0;   // user feedback
            
          // for diagnostics
          // UART1_PutS("H");                        // This prints out the configuration for debugging
        }
        if (ThisState == SM_IDLE)
            ThisState = SM_SEND_APRS_REPORT;
    }
}


/*----------------------------------------------------------------------------------------------------------------------
 * This is the state machine that manages the connction and sending of data to either CWOP/APRS via a TCP/IP connection or
 * direct via modem and 2M radio on 144.390Mhz to other APRS users and via APRS I-GATE stations to the internet. For an RF APRS 
 * connection this statemachine is entered atSM_SEND_APRS_REPORT, whereas for the TCP/IP connection it is entered at SM_START.
 *
 * The option to send a time record is if-defed out and the "!" symbol is sent indicationg that the transmit time and the data
 * aquisition time are the same, i.e. now.
 *
 * 
 */
short
APRS_Client(void)
{
       
  	char	buff[60];
        // Variables that span from state to state --- NEED to be static !!
        static DWORD		Timer;
	static TCP_SOCKET	MySocket = INVALID_SOCKET;
        short tmp;
        float ftmp;
        short retry=0;

#ifdef Debug_CWOP_Response
        WORD    len;
#endif
 

        // this test is redundnt since the kick-off functions check to see if it's valid to start the client

        if ( WX.Wunder.report_enable.Station != CWOP_CLIENT && WX.Wunder.report_enable.Station != APRS_CLIENT)
            return 0;


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
                            ThisState = SM_IDLE;
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

		case SM_SEND_CWOP_PREAMBLE:
                    	if(TCPIsPutReady(MySocket) < 250u)
                        {
                            ThisState = SM_DISCONNECT;
                            putrsUART((ROM char*) "\r\nSock buffer <250, too small to send data");
                            break;
                        }
                        putrsUART((ROM char*) "\r\nSending APRS data:\r\n");
                        WX_TCPPut(MySocket, WX.Wunder.StationID);
                        WX_TCPPut(MySocket,">APRS,TCPIP*:"); // The APRS boiler plate header
                        ThisState++; // and fall through to next

                case  SM_SEND_APRS_REPORT:

                        aprs_buff_set("!"); // The "!" indicates that I don't send a time and that the report is from NOW

                        // i.e. WX_TCPPut(MySocket,"3758.73N/12159.69W");
                        // Our location. This is ddmm.mm -- i.e. degrees, minutes and hundreths of minutes.
                        ftmp = fabs(WX.Wunder.Lat);
                        aprs_buff_cat( s_to_a(buff, (short) ftmp,2,0 ));         // in dd format
                        ftmp -= abs((short)WX.Wunder.Lat);
                        aprs_buff_cat( s_to_a(buff, (short) (ftmp*6000),2,2 ));  // in mm.mm format

                        if (WX.Wunder.Lat <0)
                            aprs_buff_cat( "S/");
                        else
                            aprs_buff_cat( "N/");

                        ftmp = fabs(WX.Wunder.Lon);
                        aprs_buff_cat( s_to_a(buff, (short) ftmp,3,0 ));      //longitude has 3 ddd with leading 0's
                        ftmp -= abs((short)WX.Wunder.Lon);
                        aprs_buff_cat( s_to_a(buff, (short) (ftmp*6000),2,2 ));  // in mm.mm format

                        if (WX.Wunder.Lon <0)
                            aprs_buff_cat( "W");
                        else
                            aprs_buff_cat( "E");
                

                        // Wind is mendatory to report -- sending "..." if Wind is not measured
                        if (WX.Wunder.report_enable.Wind)
                        {
                            if (SensorReading.AvgWindSpd >1)
                                tmp = SensorReading.AvgWindDir;
                            else
                                tmp = SensorReading.Wind_dir;

                            aprs_buff_cat("_");      // THE WIND dir
                            aprs_buff_cat(s_to_a( buff,tmp,3,0 ));
                            aprs_buff_cat("/");      // THE WIND speed
                            aprs_buff_cat(s_to_a(buff, (short) SensorReading.AvgWindSpd,3,0 ));
                            aprs_buff_cat("g");      // THE WIND speed
                            aprs_buff_cat(s_to_a(buff, (short) SensorReading.Wind_gust_5min,3,0 ));
                        }
                        else
                            aprs_buff_cat("_000/000g...");      // Space holder for no-wind reporting

                        // Temp is mendatory to report
                        aprs_buff_cat( "t");
                        aprs_buff_cat( s_to_a(buff,(short)SensorReading.TempF,3,0));  // Send the Temperature in whole deg F

                        if (WX.Wunder.report_enable.Rain)
                        {
                            aprs_buff_cat("r");
                            aprs_buff_cat(s_to_a(buff, (short)(SensorReading.RainIn*100) ,3,0 ));
       
                            aprs_buff_cat("P");
                            aprs_buff_cat(s_to_a(buff, (short) (SensorReading.RainDaily*100) ,3,0 ));
                        }

                        if (WX.Wunder.report_enable.Sol)
                        {
                            if ( SensorReading.SolRad < 1000)
                            {
                                aprs_buff_cat("L");
                                aprs_buff_cat(s_to_a( buff,SensorReading.SolRad ,3,0 ));
                            }
                            else
                            {
                                aprs_buff_cat("l");
                                aprs_buff_cat(s_to_a( buff,(SensorReading.SolRad -1000) ,3,0 ));
                            }

                        }

                        if (WX.Wunder.report_enable.Hyg)
                        {
                            aprs_buff_cat("h");
                            tmp =(short)SensorReading.RH;
                            if (tmp>=100)       // send 00 for 100% or condensing
                                tmp = 0;
                            aprs_buff_cat(s_to_a( buff,tmp ,2,0 ));       // CWOP calculates dewpoint
                        }

                        aprs_buff_cat("b");
                        tmp = SensorReading.BaromIn * 338.6388157895;   // Connvert to 1/10 of millibar
                        aprs_buff_cat(s_to_a( buff,tmp ,5,0 ));
                        // the end -- could send station software idetifier or some other status info
                        //aprs_buff_cat("WunderWeatherStation");
                        //aprs_buff_cat("See http://WWS.us.to");

                        // displaying the battery voltage measured at ADC0 as the status message
                        aprs_buff_cat("Vbat ");
                        ftmp = ADC1BUF0 * (ADC_SCALE_15V * 3.3 / 1024);
                        tmp =ftmp*100;
                        aprs_buff_cat(s_to_a( buff,tmp,2,2 ));
                        aprs_buff_cat("V");

                        tmp = aprs_buff_cat("\r\n");       // Without this only some of the servers take the data
                        
                        if ( tmp >= APRS_BUFF_SZ)
                            putrsUART((ROM char*) "\r\nAPRS Buffer overflow!!\r\n");

                        if ( MySocket != INVALID_SOCKET)       // This is going out to CWOP via TCP
                        {
                            WX_TCPPut(MySocket,aprs_buff);
                            TCPFlush(MySocket);

                           ThisState++;
                           Timer = TickGet();
                        }
                        else    // it's going out to the RF APRS modem via UART1
                        {
                            OUT0_IO = 0;           //Enables the step down power converter for the radio, low active
                            LED3_IO = 1;           // user feedback
                            DelayMs(2500);         // Delay for radio bootup
                            putrsUART("!");        // This goes to the USB UART2 just to see a trace on the monitor
                            putsUART(aprs_buff);   // this is for user feedback only

                            UART1_PutS("!");        // This is the send command of the NanoAPRS modem
                            UART1_PutS(aprs_buff);  // this is the assembled message for APRS modem
  
                            ThisState = SM_IDLE ;   // skip over disconnect
                            DelayMs(1500);          // Delay to make sure the radio transmitted everything
                            OUT0_IO = 1;            // Disable the stepdown converter for the radio
                            LED3_IO = 0;            // user feedback LED off
                        }

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
                        if ( MySocket != INVALID_SOCKET)
                        {
                            TCPDisconnect(MySocket);        // This sends a "FIN"
                            TCPDisconnect(MySocket);        // This sends a "RST" to force the connection closed and immediatly reliquisches the socket
                            MySocket = INVALID_SOCKET;
                            ThisState = SM_IDLE;
                            putrsUART((ROM char*) "\r\nSock disconnected\r\n");
                            LED2_IO = 0;    //Clear yellow and red LEDs
                            LED3_IO = 0;
                        }
 			break;
	
		case SM_IDLE:
			// Do nothing , park here until someone starts the process again
                         MySocket = INVALID_SOCKET;
                         break;
	}
        return retry;
}

