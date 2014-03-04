/* 
 * File:   nist.h
 * Author: gary
 *
 * Created on August 27, 2012, 5:41 PM
 */

#ifndef NIST_H
#define	NIST_H

#ifdef	__cplusplus
extern "C" {
#endif
// The following URLS are only reference examples -- The implementation is using IP addresses instead of URLs
// The website http://tf.nist.gov/tf-cgi/servers.cgi has a current lits of active and able servers with their IP address listed
//#define NIST_TIME_URL "time.nist.gov"
//#define NIST_TIME_URL "time-a.nist.gov"
//#define NIST_TIME_URL "time-b.nist.gov"
//#define NIST_TIME_URL "utcnist.colorado.edu"
//#define NIST_TIME_URL "time-nw.nist.gov"            // Washington
//#define NIST_TIME_URL "nist1.aol-ca.symmetricom.com" // Mountain View
//#define NIST_TIME_URL "nist1.symmetricom.com" // San Jose
//#define NIST_TIME_URL "nist1-la.ustiming.org"  // LA


#define NIST_DAYTIME_PORT	13 	// for Date_time service
//#define NIST_NTP_PORT	123 	// for Network  Time Protocol
#define NIST_TIMEOUT 	10       // time to wait for a reply from a NIST server before timeout, also time to wait to retry the call

enum _nist_SM{
    SM_START = 0,
    SM_SOCKET_OBTAINED,
    SM_PROCESS_RESPONSE,
    SM_DISCONNECT,
    SM_RETRY,
    SM_RETRY_DELAY,
    SM_IDLE
};
extern void NIST_TimeSyncRequest( void);   // resets the NISTDaytime_Client statemachine to request the time again
extern void NIST_DAYTIME_Client(void);
extern BOOL NIST_Time_Status ( void );
#ifdef	__cplusplus
}
#endif

#endif	/* NIST_H */

