#include <time.h>
#include "TCPIPConfig.h"
#include "TCPIP Stack/TCPIP.h"
#include "rtcc.h"
#include "nist.h"
#include "WX_perm_data.h"

static enum _nist_SM ThisState = SM_RETRY;   // Start out with SM_RETRY. This provides an intial delay for the stack to get DHCP completed
static  BOOL NistGotGoodTime = FALSE;


void        // Function to restart a time sync from NIST
NIST_TimeSyncRequest( void)
{
    NistGotGoodTime = FALSE;
    ThisState = SM_START;
    return;
}

BOOL  
NIST_Time_Status ( void )
{
    return NistGotGoodTime;
}

// NIST time sync process calls a NIST time server with a DAYTIME request so that the real time clock in the PIC can be set
// The Process continues to ask for Time from one of two time servers periodically until a good time is obtained and the RTC is set.

void
NIST_DAYTIME_Client(void)
{
    WORD w;
    char NistRspBuffer[31];
    BCD_RTCC rtc_time;
   

    static DWORD NistIP_addr =0;
    static DWORD Timer;
    static TCP_SOCKET sock = INVALID_SOCKET;
    

    switch (ThisState)
    {
        case SM_START:
            if (NistIP_addr == 0)                               // initialize the IP address for the time server to call
                NistIP_addr = WX.TimeServer.NIST1.Val;
            else if (NistIP_addr == WX.TimeServer.NIST1.Val)    // toggle server address every time we try to call
                NistIP_addr = WX.TimeServer.NIST2.Val;
            else
                NistIP_addr = WX.TimeServer.NIST1.Val;

            // Connect a socket to the remote TCP server
            //sock = TCPOpen((DWORD) NIST_TIME_URL, TCP_OPEN_ROM_HOST, NIST_DAYTIME_PORT, TCP_PURPOSE_NIST_CLIENT);
           // sock = TCPOpen((DWORD) "128.138.140.44", TCP_OPEN_ROM_HOST, NIST_DAYTIME_PORT, TCP_PURPOSE_NIST_CLIENT);
            sock = TCPOpen( NistIP_addr, TCP_OPEN_IP_ADDRESS, NIST_DAYTIME_PORT, TCP_PURPOSE_NIST_CLIENT);

            // Abort operation if no socket of proper type is available
            // If this ever happens, you need to go add one to TCPIPConfig.h
            if (sock == INVALID_SOCKET)
            {
#if defined(STACK_USE_UART)         
                putrsUART((ROM char*) "NIST ERROR: no Socket of proper type defined in .h file\r\n");
#endif
                ThisState = SM_IDLE;
                break;
            }

            ThisState++;
            Timer = TickGet();
#if defined(STACK_USE_UART)
            putrsUART((ROM char*) "NIST waiting for socket connect\r\n");
#endif
            break;

        case SM_SOCKET_OBTAINED:

            // Wait for the remote server to accept our connection request
            if (!TCPIsConnected(sock))
            {

                // Time out if too much time is spent in this state
                if (TickGet() - Timer > NIST_TIMEOUT * TICK_SECOND)
                {
#if defined(STACK_USE_UART)
                    putrsUART((ROM char*) "Nist timedout waiting for Socket connection,aborting\r\n");
#endif
                    // Close the socket so it can be used by other modules
                    ThisState = SM_DISCONNECT;
                }
                break;
            }

            Timer = TickGet();
            ThisState++;
            break;

        case SM_PROCESS_RESPONSE:
            // collect the time data output from the sever and/or react to a Disconnect from the server
            // The Server automatically disconnects from the client after it output the data
            w = sizeof (NistRspBuffer) - 1;
            if (TCPIsGetReady(sock) >= w)
            {
                NistRspBuffer[28] = 0xff;
                w = TCPGetArray(sock, (unsigned char *)NistRspBuffer, w);

                if (NistRspBuffer[28] - '0' < 2)  // The time servers health status
                {
#if defined(STACK_USE_UART)
                    putrsUART((ROM char*) "Nist got good time\r\n");
#endif
                    //extracting the time from the response and setting the RTC clock

                    rtc_time.yr = ((NistRspBuffer[7] - '0') << 4) + (NistRspBuffer[8] - '0');
                    rtc_time.mth = ((NistRspBuffer[10] - '0') << 4) + (NistRspBuffer[11] - '0');
                    rtc_time.day = ((NistRspBuffer[13] - '0') << 4) + (NistRspBuffer[14] - '0');
                    rtc_time.hr = ((NistRspBuffer[16] - '0') << 4) + (NistRspBuffer[17] - '0');
                    rtc_time.min = ((NistRspBuffer[19] - '0') << 4) + (NistRspBuffer[20] - '0');
                    rtc_time.sec = ((NistRspBuffer[22] - '0') << 4) + (NistRspBuffer[23] - '0');
                    // TT field ==0 indicates Standard time in efect, NOTE sotred in decimal format
                    rtc_time.TT = ((NistRspBuffer[25] - '0') *10) + (NistRspBuffer[26] - '0');


                    RTC_Set_BCD_time(&rtc_time);           // SET THE RTC with the current time
                    NistGotGoodTime = TRUE;

                    // set flag that we got good time
                }
                ThisState = SM_DISCONNECT;
            }
            else
            {
#if defined(STACK_USE_UART)
                //                putrsUART((ROM char*)"w");
#endif
                // wait to get data and abort if it takes too long
                if (TickGet() - Timer > NIST_TIMEOUT * TICK_SECOND)
                {
#if defined(STACK_USE_UART)
                    putrsUART((ROM char*) "Nist timed-out waiting for Data, aborting\r\n");
#endif
                    ThisState = SM_DISCONNECT;
                    break;
                }
            }

            if (!TCPIsConnected(sock))
            {
#if defined(STACK_USE_UART)
                putrsUART((ROM char*) "NIST Server has disconnected\r\n");
#endif
                ThisState = SM_DISCONNECT;
            }
            break;

        case SM_DISCONNECT:
            // Close the socket so it can be used by other modules
#if defined(STACK_USE_UART)
            putrsUART((ROM char*) "Nist Disconnect\r\n");
#endif
            TCPDisconnect(sock);
            sock = INVALID_SOCKET;
            if (NistGotGoodTime )
            {
                ThisState = SM_IDLE;
            }
            else
                ThisState = SM_RETRY;
            break;

        case SM_RETRY:
            Timer = TickGet();
            ThisState++;
            break;

        case SM_RETRY_DELAY:
             if (TickGet() - Timer > NIST_TIMEOUT * TICK_SECOND)
                 ThisState = SM_START;
             break;

        case SM_IDLE:
        default:
            break;

    }
}

