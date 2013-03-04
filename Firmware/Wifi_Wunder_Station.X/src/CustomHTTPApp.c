
#define __CUSTOMHTTPAPP_C
 
#include "TCPIPConfig.h"

#if defined(STACK_USE_HTTP2_SERVER)

#include "TCPIP Stack/TCPIP.h"
#include "Main.h"
#include "WX_perm_data.h"		// Needed for SaveAppConfig() prototype
#include "APP_cfg.h"
#include "rtcc.h"
#include "Mail_Alarm.h"
#include "Once_per_second.h"
#include "Configs/Wunder_cfg.h"

/****************************************************************************
  Section:
        Function Prototypes and Memory Globalizers
 ***************************************************************************/

// RAM allocated for DDNS parameters
#if defined(STACK_USE_DYNAMICDNS_CLIENT)
static BYTE DDNSData[100];
static HTTP_IO_RESULT HTTPPostExecDDNSConfig(void);
#endif
#if defined(STACK_USE_SMTP_CLIENT)&& defined (HAS_HTTP_FORM_POSTMAIL)
static HTTP_IO_RESULT HTTPPostExecEmail(void);
#endif

// Sticky status message variable.
// This is used to indicated whether or not the previous POST operation was 
// successful.  The application uses these to store status messages when a 
// POST operation redirects.  This lets the application provide status messages
// after a redirect, when connection instance data has already been lost.
static BOOL lastSuccess = FALSE;

// Stick status message variable.  See lastSuccess for details.
static char *lastFailure = NULL;
static char lastErrorMsg[40];

/****************************************************************************
  Section:
        Authorization Handlers
 ***************************************************************************/

/*****************************************************************************
  Function:
        BYTE HTTPNeedsAuth(BYTE* cFile)
	
  Internal:
        See documentation in the TCP/IP Stack API or HTTP2.h for details.
 ***************************************************************************/
#if defined(HTTP_USE_AUTHENTICATION)

BYTE
HTTPNeedsAuth(BYTE* cFile)
{
    // If the filename begins with the folder "protect", then require auth
    if (memcmppgm2ram(cFile, (ROM void*) "protect", 7) == 0)
        return 0x00; // Authentication will be needed later

    // If the filename begins with the folder "admin", then require auth
    if (memcmppgm2ram(cFile, (ROM void*) "admin", 5) == 0)
        return 0x00; // Authentication will be needed later

#if defined(HTTP_MPFS_UPLOAD_REQUIRES_AUTH)
    if (memcmppgm2ram(cFile, (ROM void*) "HTTP_MPFS_UPLOAD", 10) == 0)
        return 0x00;
#endif

    // You can match additional strings here to password protect other files.
    // You could switch this and exclude files from authentication.
    // You could also always return 0x00 to require auth for all files.
    // You can return different values (0x00 to 0x79) to track "realms" for below.

    return 0x80; // No authentication required
}
#endif

/*****************************************************************************
  Function:
        BYTE HTTPCheckAuth(BYTE* cUser, BYTE* cPass)
	
  Internal:
        See documentation in the TCP/IP Stack API or HTTP2.h for details.
 ***************************************************************************/
#if defined(HTTP_USE_AUTHENTICATION)

BYTE
HTTPCheckAuth(BYTE* cUser, BYTE* cPass)
{
     if (   strcmp((char *) cUser, WX.Station.User_name) == 0
         && strcmp((char *) cPass,  WX.Station.password) == 0)
         return 0x80; // We accept this combination

    return 0x00; // Provided user/pass is invalid
}
#endif

static void
HTTP_GetExec_wuncgf_htm()
{
    BYTE *ptr;
    BYTE err = 0;
    BOOL enaRain = FALSE, enaStation = FALSE,enaWind =FALSE,enaHyg=FALSE,enaSol=FALSE;

    if ((ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *) "W_SID")) != NULL )
        strncpy((char *) WX.Wunder.StationID, (char *) ptr, sizeof (WX.Wunder.StationID));

    
    if ((ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *) "W_PASS")) != NULL)
        strncpy((char *) WX.Wunder.StationPW, (char*) ptr, sizeof (WX.Wunder.StationPW));

    if ((ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *) "ELEV")) != NULL)
        WX.Wunder.StationElev = atoi((char *) ptr);

    if ((ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *) "UpInt")) != NULL)
    {
        WX.Wunder.UplnkInterval= atoi((char *) ptr);

        // limitto sane values
        if (WX.Wunder.UplnkInterval >MAX_UPLINK_INTERVAL )
            WX.Wunder.UplnkInterval = MAX_UPLINK_INTERVAL;

        if (WX.Wunder.UplnkInterval < MIN_UPLINK_INTERVAL )
            WX.Wunder.UplnkInterval = MIN_UPLINK_INTERVAL;

    }

    if ((ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *) "TZoff")) != NULL)
    {
        WX.Wunder.TZ_offset= atoi((char *) ptr);
        // limit to valid GMT timezone offsets
        if (WX.Wunder.TZ_offset < (-12))
            WX.Wunder.TZ_offset = -12;

        if (WX.Wunder.TZ_offset > 13)
            WX.Wunder.TZ_offset = 13;
    }

    if ((ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *) "NIST_1")) != NULL)
    {
        if (!StringToIPAddress(ptr, &WX.TimeServer.NIST1))
            err++;
    }


    if (( ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *) "NIST_2")) != NULL)
    {
        if (!StringToIPAddress(ptr, &WX.TimeServer.NIST2))
            err++;
    }


    // these are checkbox input, only checked items are transmitted, so we have to assume that they are notc checked if we don recive them
    // since there are multiple forms on the page we have to special case them and only set or clear when we know that the wunder config
    // form sent the form submit
    if (HTTPGetROMArg(curHTTP.data, (ROM BYTE *) "W_ENB"))
        enaStation  = 1;

    if (HTTPGetROMArg(curHTTP.data, (ROM BYTE *) "R_WND"))
        enaWind=1;

    if (HTTPGetROMArg(curHTTP.data, (ROM BYTE *) "R_HYG"))
       enaHyg=1;


    if (HTTPGetROMArg(curHTTP.data, (ROM BYTE *) "R_SOL"))
        enaSol= 1;

    if (HTTPGetROMArg(curHTTP.data, (ROM BYTE *) "R_RAIN"))
        enaRain= 1;

    if ((ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *) "CALto")) != NULL)
        WX.Calib.Temp_offs =  atoi((char *) ptr);

    if ((ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *) "CALho")) != NULL)
        WX.Calib.Hyg_offs =  atoi((char *) ptr);

    if ((ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *) "CALsg")) != NULL)
        WX.Calib.Sol_gain =  atoi((char *) ptr);

    if ((ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *) "CALbo")) != NULL)
        WX.Calib.Baro_offs =  atoi((char *) ptr);

    if ((ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *) "CALra")) != NULL)
    {
        WX.Calib.Rain_counts =  atoi((char *) ptr);
        
        // to prevent div/0 potential
        if (WX.Calib.Rain_counts < 1 )
            WX.Calib.Rain_counts = 1;
    }

    // allows manual entry of the north offset without having to go on top of the roof
    if ((ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *) "CALwo")) != NULL)
    {
        WX.Calib.WDir_offs =  atoi((char *) ptr);
    }


    if ((ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *) "CALws")) != NULL)
    {    
        WX.Calib.Wind_counts =  atoi((char *) ptr);
       
        // to prevent div/0 potential
        if ( WX.Calib.Wind_counts <1 )
            WX.Calib.Wind_counts = 1;
    }
    if ((ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *) "CALwf")) != NULL)
    {
        WX.Calib.Wind_AN_CalFactor =  atof((char *) ptr);

        // no negative numbers
        if ( WX.Calib.Wind_AN_CalFactor <= 0 )
            WX.Calib.Wind_AN_CalFactor = 0;

        if ( WX.Calib.Wind_AN_CalFactor > 20 )
            WX.Calib.Wind_AN_CalFactor = 20;
    }

    if ((ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *) "_CALwd")) != NULL)
    {
        WDIR_cal_tmp.WindDir_max = 0;
        WDIR_cal_tmp.WindDir_min = 1023;    // reset earlier calibrations
        WDIR_cal_tmp.DoWindDirCal = TRUE;    // turns on the wind dir calibration function in main which reads the vane min/max and north
    }

    if ((ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *) "_CANc")) != NULL)
    {
        WDIR_cal_tmp.DoWindDirCal = FALSE;
    }

    if ( HTTPGetROMArg(curHTTP.data, (ROM BYTE *) "_SAV1") )
    {
              WX.Wunder.report_enable.Station  = enaStation;
              WX.Wunder.report_enable.Wind = enaWind;
              WX.Wunder.report_enable.Hyg = enaHyg;
              WX.Wunder.report_enable.Sol = enaSol;
              WX.Wunder.report_enable.Rain= enaRain;
              WX_writePerm_data();
              WDIR_cal_tmp.DoWindDirCal = FALSE;
    }
    if ( HTTPGetROMArg(curHTTP.data, (ROM BYTE *) "_SAV2") )
    {
        WX_writePerm_data();
        WDIR_cal_tmp.DoWindDirCal = FALSE;
    }
    
    if ( HTTPGetROMArg(curHTTP.data, (ROM BYTE *) "_SAV3") )
    {
        short tmp;
        
        if (WDIR_cal_tmp.DoWindDirCal)
        {
            tmp =  (WDIR_cal_tmp.WindDir_max - WDIR_cal_tmp.WindDir_north )/((WDIR_cal_tmp.WindDir_max - WDIR_cal_tmp.WindDir_min) / 360.0 );

            if (tmp < 360 && tmp > 0)  // precaution in case the user did not spin the vane
            {
                WX.Calib.WDir_offs = tmp;
                WX.Calib.WDir_min = WDIR_cal_tmp.WindDir_min;
                WX.Calib.WDir_max = WDIR_cal_tmp.WindDir_max;
                WX_writePerm_data();
            }
        }
        WDIR_cal_tmp.DoWindDirCal = FALSE;
    }
}



static void
HTTP_GetExec_mailcgf_htm()
{
    BYTE *ptr;
   
    if ((ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *) "M_TO")) != NULL )
        strncpy((char *) WX.Mail.SendTo, (char *) ptr, sizeof (WX.Mail.SendTo));

    if ((ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *) "M_SRV")) != NULL)
        strncpy((char *) WX.Mail.Server, (char*) ptr, sizeof (WX.Mail.Server));

    if ((ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *) "M_USR")) != NULL)
        strncpy((char *) WX.Mail.User_name, (char*) ptr, sizeof (WX.Mail.User_name));

    if ((ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *) "M_PWD")) != NULL)
        strncpy((char *) WX.Mail.password, (char*) ptr, sizeof (WX.Mail.password));

    if ((ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *) "M_PRT")) != NULL)
        WX.Mail.port = atoi((char *) ptr);

    if ( HTTPGetROMArg(curHTTP.data, (ROM BYTE *) "_SAVE") )
    {
        WX_writePerm_data();
    }

    if ( HTTPGetROMArg(curHTTP.data, (ROM BYTE *) "_TSTMAIL") )
    {
        if ((ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *) "_MSG")) != NULL)
            SMTP_trigger_mail( (char *)  ptr);
    }
}

static void
HTTP_GetExec_stcgf_htm()
{
    BYTE *ptr;

    if ((ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *) "ST_USR")) != NULL)
        strncpy((char *) WX.Station.User_name, (char*) ptr, sizeof (WX.Station.User_name));

    if ((ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *) "ST_PWD")) != NULL)
        strncpy((char *) WX.Station.password, (char*) ptr, sizeof (WX.Station.password));

    if ( HTTPGetROMArg(curHTTP.data, (ROM BYTE *) "_SAVE") )
    {
        WX_writePerm_data();
    }
}



static void
HTTP_GetExec_togg_outputs_cgi()
{
    BYTE *ptr;

    // Determine which LED/output to toggle
    ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *) "out");
    if (ptr)
    {
        // Toggle the specified outputs
// TODO: need to change this to the actual outputs on the WX board
        switch (*ptr)
        {
              case '0':
                OUT0_IO ^= 1;
                break;
            case '1':
                OUT1_IO ^= 1;
                break;
            case '2':
                OUT2_IO ^= 1;
                break;
            case '3':
                OUT3_IO ^= 1;
                break;
            case '4':
                OUT4_IO ^= 1;
                break;
            case '5':
                OUT5_IO ^= 1;
                break;
            case '6':
                OUT6_IO ^= 1;
                break;
             case '7':
                OUT7_IO ^= 1;
                break;
             case '8':
                OUT8_IO ^= 1;
                break;
             case '9':
                OUT9_IO ^= 1;
                break;
              
        }
    }
    else
    {
        ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *) "led");
        if (ptr)
        {
            switch (*ptr)
            {
                case '1':
                    LED1_IO ^= 1;
                    break;
                case '2':
                    LED2_IO ^= 1;
                    break;
                case '3':
                    LED3_IO ^= 1;
                    break;
             }
        }
    }

}

static void
HTTP_GetExec_alarmcfg_htm()
{
    BYTE *ptr;
    BYTE tmp =0;

    if ((ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *) "AL_1")) != NULL)
         tmp |= 1<<1;

    if ((ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *) "AL_2")) != NULL)
         tmp |= 1<<2;

     if ((ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *) "AL_3")) != NULL)
         tmp |= 1<<3;

     if ((ptr = HTTPGetROMArg(curHTTP.data, (ROM BYTE *) "AL_4")) != NULL)
         tmp |= 1<<4;

    if ( HTTPGetROMArg(curHTTP.data, (ROM BYTE *) "_SAVAL") )
    {
        WX.Alarms.enable =tmp;
        WX_writePerm_data();
    }
}
/****************************************************************************
  Section:
        GET Form Handlers
 ***************************************************************************/

/*****************************************************************************
  Function:
        HTTP_IO_RESULT HTTPExecuteGet(void)
	
  Internal:
        See documentation in the TCP/IP Stack API or HTTP2.h for details.
 ***************************************************************************/
HTTP_IO_RESULT
HTTPExecuteGet(void)
{

    BYTE filename[24];

    // Load the file name
    // Make sure BYTE filename[] above is large enough for your longest name
    MPFSGetFilename(curHTTP.file, filename, 24);

    // If it's the LED updater file
    if (!memcmppgm2ram(filename, "togg.cgi", 8))
        HTTP_GetExec_togg_outputs_cgi();
    else if (!memcmppgm2ram(filename, "protect/wuncfg.htm", 18))
        HTTP_GetExec_wuncgf_htm();
    else if (!memcmppgm2ram(filename, "protect/snscfg.htm", 18))
        HTTP_GetExec_wuncgf_htm();
    else if (!memcmppgm2ram(filename, "protect/nistcfg.htm", 19))
        HTTP_GetExec_wuncgf_htm();
    else if (!memcmppgm2ram(filename, "protect/mailcfg.htm", 19))
        HTTP_GetExec_mailcgf_htm();
    else if (!memcmppgm2ram(filename, "protect/stcfg.htm", 17))
        HTTP_GetExec_stcgf_htm();
    else if (!memcmppgm2ram(filename, "protect/alarmcfg.htm", 20))
        HTTP_GetExec_alarmcfg_htm();


    return HTTP_IO_DONE;
}


/****************************************************************************
  Section:
        POST Form Handlers
 ***************************************************************************/
#if defined(HTTP_USE_POST)
#if defined(STACK_USE_HTTP_APP_RECONFIG)
#define NAME_SZ 6

static HTTP_IO_RESULT
reboot_(char *NBname)
{
    int i;
    // Prepare a HTTP_Redirect to a user htm file that gives info about the reboot in progress
    // The reboot.htm will then call reboot.cgi which has the ~reboot~ tag that, when served will
    // call the Reset function.

    strcpypgm2ram((char*) curHTTP.data, "/protect/reboot.htm");
    memcpy((void*) (AppConfig.NetBIOSName), (void*) NBname, 16); // this is for ~rebootaddr~
    curHTTP.httpStatus = HTTP_REDIRECT;
    return HTTP_IO_DONE;
}

static void
process_MAC(BYTE *ptr, APP_CONFIG *aptr)
{
    // Read new MAC address
    WORD w;
    BYTE i;

    for (i = 0; i < 12u; i++) // Read the MAC address
    {
        // Skip non-hex bytes
        while (*ptr != 0x00u && !(*ptr >= '0' && *ptr <= '9') && !(*ptr >= 'A' && *ptr <= 'F') && !(*ptr >= 'a' && *ptr <= 'f'))
            ptr++;

        // MAC string is over, so zeroize the rest
        if (*ptr == 0x00u)
        {
            for (; i < 12u; i++)
                curHTTP.data[i] = '0';
            break;
        }

        // Save the MAC byte
        curHTTP.data[i] = *ptr++;
    }

    // Read MAC Address, one byte at a time
    for (i = 0; i < 6u; i++)
    {
        ((BYTE*) & w)[1] = curHTTP.data[i * 2];
        ((BYTE*) & w)[0] = curHTTP.data[i * 2 + 1];
        aptr->MyMACAddr.v[i] = hexatob(*((WORD_VAL*) & w));
    }
}

// TODO: this form processing could be done via GET instead of POST to save memory
/*****************************************************************************
  Function:
        static HTTP_IO_RESULT HTTPPostConfig(void)

  Summary:
        Processes the configuration form on config/index.htm

  Description:
        Accepts configuration parameters from the form, saves them to a
        temporary location in RAM, then eventually saves the data to EEPROM or
        external Flash.

        When complete, this function redirects to config/reboot.htm, which will
        display information on reconnecting to the board.

        This function creates a shadow copy of the AppConfig structure in
        RAM and then overwrites incoming data there as it arrives.  For each
        name/value pair, the name is first read to curHTTP.data[0:5].  Next, the
        value is read to newAppConfig.  Once all data has been read, the new
        AppConfig is saved back to EEPROM and the browser is redirected to
        reboot.htm.  That file includes an AJAX call to reboot.cgi, which
        performs the actual reboot of the machine.

        If an IP address cannot be parsed, too much data is POSTed, or any other
        parsing error occurs, the browser reloads config.htm and displays an error
        message at the top.

  Precondition:
        None

  Parameters:
        None

  Return Values:
        HTTP_IO_DONE - all parameters have been processed
        HTTP_IO_NEED_DATA - data needed by this function has not yet arrived
 ***************************************************************************/
static HTTP_IO_RESULT
HTTPPostExecConfig(char *filename)
{
    APP_CONFIG newAppConfig;
    BYTE *value;
    char *name;
    char *lastParse = NULL;
    BOOL reboot_flag = 0;
    BOOL updt_flag = 0;

    // Check to see if the browser is attempting to submit more data than we
    // can parse at once.  This function needs to receive all updated
    // parameters and validate them all before committing them to memory so that
    // orphaned configuration parameters do not get written (for example, if a
    // static IP address is given, but the subnet mask fails parsing, we
    // should not use the static IP address).  Everything needs to be processed
    // in a single transaction.  If this is impossible, fail and notify the user.
    // As a web devloper, if you add parameters to AppConfig and run into this
    // problem, you could fix this by to splitting your update web page into two
    // seperate web pages (causing two transactional writes).  Alternatively,
    // you could fix it by storing a static shadow copy of AppConfig someplace
    // in memory and using it instead of newAppConfig.  Lastly, you could
    // increase the TCP RX FIFO size for the HTTP server.  This will allow more
    // data to be POSTed by the web browser before hitting this limit.


    lastFailure = NULL;
    if (curHTTP.byteCount > (TCPIsGetReady(sktHTTP) + TCPGetRxFIFOFree(sktHTTP)))
    {
        lastFailure = "POST data too big";
        goto ConfigFailure;
    }
    // Ensure that all data is waiting to be parsed.  If not, keep waiting for
    // all of it to arrive.
    if (TCPIsGetReady(sktHTTP) < curHTTP.byteCount)
        return HTTP_IO_NEED_DATA;

    // Get a copy of the current appconfig structure from persistent storage to start out from.
    // not all fields might be posted by the form. E.g. if DHCP is not checked the various address fields are not submitted

#if defined(EEPROM_CS_TRIS)
    XEEReadArray(sizeof (NVM_VALIDATION_STRUCT), (BYTE*) & newAppConfig, sizeof ( newAppConfig));
#elif defined(SPIFLASH_CS_TRIS)
    SPIFlashReadArray(sizeof (NVM_VALIDATION_STRUCT), (BYTE*) ptrAppConfig, sizeof ( APP_CONFIG));
#endif

    // Start out assuming that DHCP is disabled.  This is necessary since the
    // browser doesn't submit this field if it is unchecked (meaning zero).
    // However, if it is checked, this will be overridden since it will be
    // submitted.

    while (curHTTP.byteCount > 0) // Read all POSDTed name/value pairs
    {
        if (HTTPReadPostValue(curHTTP.data, sizeof (curHTTP.data)) != HTTP_READ_OK) // returns two null terminated strings in sequence
        {
            lastFailure = "Could not Read POST data";
            goto ConfigFailure;
        }

        name = (char *) curHTTP.data;
        value = (BYTE *) name + strlen(name) + 1; //

        if (!strcmp(name, (ROM char*) (lastParse = "Reboot")) && !strcmp((char*) value, (ROM char*) "Now"))
        {
            reboot_flag++;
        }

        if (!strcmp(name, (ROM char*) (lastParse = "MAC_addr")))
        {
            updt_flag++;
            process_MAC(value, &newAppConfig);
        }

        if (!strcmp(name, (ROM char*) (lastParse = "NET_BiosName")))
        {
            updt_flag++;
            FormatNetBIOSName(value);
            memcpy((void*) newAppConfig.NetBIOSName, (void*) value, 16);
            // kludge for now to clear the dhcp field here because the POST doesn't post anything for checkboxes that are not checked
            // -- depends on that host/netbiosname is on the same fieldset in the html file and that is appears ahead of the DHCP  item
            newAppConfig.Flags.bIsDHCPEnabled = 0;
        }

        if (!strcmp(name, (ROM char*) (lastParse = "DHCP")))
        {
            updt_flag++;
            if (*value == '1')
                newAppConfig.Flags.bIsDHCPEnabled = 1;
        }

        if (!strcmp(name, (ROM char*) (lastParse = "IP_addr")))
        {
            if (!StringToIPAddress(value, &newAppConfig.MyIPAddr))
                goto ConfigFailure;

            updt_flag++;
            newAppConfig.DefaultIPAddr.Val = newAppConfig.MyIPAddr.Val;
        }

        if (!strcmp(name, (ROM char*) (lastParse = "Gateway")))
        {
            if (!StringToIPAddress(value, &newAppConfig.MyGateway))
                goto ConfigFailure;

            updt_flag++;
        }
        if (!strcmp(name, (ROM char*) (lastParse = "Mask")))
        {

            if (!StringToIPAddress(value, &newAppConfig.MyMask))
                goto ConfigFailure;

            updt_flag++;
        }

        if (!strcmp(name, (ROM char*) (lastParse = "DNS_1")))
        {

            if (!StringToIPAddress(value, &newAppConfig.PrimaryDNSServer))
                goto ConfigFailure;

            updt_flag++;

        }
        if (!strcmp(name, (ROM char*) (lastParse = "DNS_2")))
        {

            if (!StringToIPAddress(value, &newAppConfig.SecondaryDNSServer))
                goto ConfigFailure;

            updt_flag++;

        }


        if (!strcmp(name, (ROM char*) (lastParse = "wifi_SSID")))
        {
            updt_flag++;
            strcpy((char *) newAppConfig.MySSID, (char *) value);
            newAppConfig.SsidLength = strlen((char *) value);
        }

        if (!strcmp(name, (ROM char*) (lastParse = "wifi_Enc")))
        {
            WORD_VAL b;
            updt_flag++;
            b.byte.LB = *value;
            b.byte.HB = '0';
            *value = hexatob(b); // convert ascii string value  to a byte value
            if (*value > WF_SECURITY_WPA_AUTO_WITH_PASS_PHRASE)
                *value = 0;
            newAppConfig.SecurityMode = *value;
        }

        if (!strcmp(name, (ROM char*) (lastParse = "wifi_Key")))
        {
            updt_flag++;
            WORD_VAL b;
            int i;
            int len;

            switch (newAppConfig.SecurityMode)
            {
                case WF_SECURITY_WEP_40:
                    newAppConfig.SecurityKeyLength = len = 5;
                    newAppConfig.WepKeyIndex = 0;
                    break;

                case WF_SECURITY_WEP_104:
                    newAppConfig.SecurityKeyLength = len = 13;
                    newAppConfig.WepKeyIndex = 0;
                    break;

                case WF_SECURITY_WPA_WITH_KEY:
                case WF_SECURITY_WPA2_WITH_KEY:
                case WF_SECURITY_WPA_AUTO_WITH_KEY:
                    newAppConfig.SecurityKeyLength = len = 32;
                    break;

                case WF_SECURITY_WPA_WITH_PASS_PHRASE:
                case WF_SECURITY_WPA2_WITH_PASS_PHRASE:
                case WF_SECURITY_WPA_AUTO_WITH_PASS_PHRASE:
                    len = 0;
                    newAppConfig.SecurityKeyLength = strlen((char *) value);
                    strcpy((char *) newAppConfig.SecurityKey, (char *) value);
                    break;

                default:
                    len = 0;
            }


            for (i = 0; i < len; i++)
            {
                b.byte.HB = *value++;
                b.byte.LB = *value++;
                newAppConfig.SecurityKey[i] = hexatob(b);
            }
        }
    }

    if (updt_flag)
        SaveAppConfig(&newAppConfig);

    if (reboot_flag)
    {
        reboot_((char *) newAppConfig.NetBIOSName);
    }

    return HTTP_IO_DONE;

    //reload the page in the browser so the error shows up
ConfigFailure:
    if (lastFailure == NULL)
    {
        strcpy(lastErrorMsg, "Could not parse field: ");
        strcat(lastErrorMsg, lastParse);
        lastFailure = lastErrorMsg;
    }
    strcpy((char*) curHTTP.data, filename);
    curHTTP.httpStatus = HTTP_REDIRECT;

    return HTTP_IO_DONE;
}

#endif	// #if defined(STACK_USE_HTTP_APP_RECONFIG)

/*****************************************************************************
  Function:
        HTTP_IO_RESULT HTTPExecutePost(void)

  Internal:
        See documentation in the TCP/IP Stack API or HTTP2.h for details.
 ***************************************************************************/
HTTP_IO_RESULT
HTTPExecutePost(void)
{
    // Resolve which function to use and pass along
    BYTE filename[20];

    // Load the file name
    // Make sure BYTE filename[] above is large enough for your longest name
    MPFSGetFilename(curHTTP.file, filename, sizeof (filename));

#if defined(STACK_USE_HTTP_APP_RECONFIG)
    if (!memcmppgm2ram(filename, "protect/ipcfg.htm", 17) || !memcmppgm2ram(filename, "protect/wificfg.htm", 19) )
        return HTTPPostExecConfig((char *)filename);

#endif

#if defined(STACK_USE_SMTP_CLIENT) && defined( HAS_HTTP_FORM_POSTMAIL)
    if (!strcmppgm2ram((char*) filename, "email/index.htm"))
        return HTTPPostExecEmail();
#endif

#if defined(STACK_USE_DYNAMICDNS_CLIENT)
    if (!strcmppgm2ram((char*) filename, "dyndns/index.htm"))
        return HTTPPostExecDDNSConfig();
#endif

    return HTTP_IO_DONE;
}


/****************************************************************************
  Function:
    HTTP_IO_RESULT HTTPPostDDNSConfig(void)
    
  Summary:
    Parsing and collecting http data received from http form.

  Description:
    This routine will be excuted every time the Dynamic DNS Client
    configuration form is submitted.  The http data is received 
    as a string of the variables seperated by '&' characters in the TCP RX
    buffer.  This data is parsed to read the required configuration values, 
    and those values are populated to the global array (DDNSData) reserved 
    for this purpose.  As the data is read, DDNSPointers is also populated
    so that the dynamic DNS client can execute with the new parameters.
    
  Precondition:
     curHTTP is loaded.

  Parameters:
    None.

  Return Values:
    HTTP_IO_DONE 		-  Finished with procedure
    HTTP_IO_NEED_DATA	-  More data needed to continue, call again later
    HTTP_IO_WAITING 	-  Waiting for asynchronous process to complete, 
                                                call again later
 ***************************************************************************/
#if defined(STACK_USE_DYNAMICDNS_CLIENT)

static HTTP_IO_RESULT
HTTPPostExecDDNSConfig(void)
{
    static BYTE *ptrDDNS;

#define SM_DDNS_START			(0u)
#define SM_DDNS_READ_NAME		(1u)
#define SM_DDNS_READ_VALUE		(2u)
#define SM_DDNS_READ_SERVICE	(3u)
#define SM_DDNS_DONE			(4u)

#define DDNS_SPACE_REMAINING				(sizeof(DDNSData) - (ptrDDNS - DDNSData))

    switch (curHTTP.smPost)
    {
            // Sets defaults for the system
        case SM_DDNS_START:
            ptrDDNS = DDNSData;
            DDNSSetService(0);
            DDNSClient.Host.szROM = NULL;
            DDNSClient.Username.szROM = NULL;
            DDNSClient.Password.szROM = NULL;
            DDNSClient.ROMPointers.Host = 0;
            DDNSClient.ROMPointers.Username = 0;
            DDNSClient.ROMPointers.Password = 0;
            curHTTP.smPost++;

            // Searches out names and handles them as they arrive
        case SM_DDNS_READ_NAME:
            // If all parameters have been read, end
            if (curHTTP.byteCount == 0u)
            {
                curHTTP.smPost = SM_DDNS_DONE;
                break;
            }

            // Read a name
            if (HTTPReadPostName(curHTTP.data, HTTP_MAX_DATA_LEN) == HTTP_READ_INCOMPLETE)
                return HTTP_IO_NEED_DATA;

            if (!strcmppgm2ram((char *) curHTTP.data, (ROM char*) "service"))
            {
                // Reading the service (numeric)
                curHTTP.smPost = SM_DDNS_READ_SERVICE;
                break;
            } else if (!strcmppgm2ram((char *) curHTTP.data, (ROM char*) "user"))
                DDNSClient.Username.szRAM = ptrDDNS;
            else if (!strcmppgm2ram((char *) curHTTP.data, (ROM char*) "pass"))
                DDNSClient.Password.szRAM = ptrDDNS;
            else if (!strcmppgm2ram((char *) curHTTP.data, (ROM char*) "host"))
                DDNSClient.Host.szRAM = ptrDDNS;

            // Move to reading the value for user/pass/host
            curHTTP.smPost++;

            // Reads in values and assigns them to the DDNS RAM
        case SM_DDNS_READ_VALUE:
            // Read a name
            if (HTTPReadPostValue(ptrDDNS, DDNS_SPACE_REMAINING) == HTTP_READ_INCOMPLETE)
                return HTTP_IO_NEED_DATA;

            // Move past the data that was just read
            ptrDDNS += strlen((char*) ptrDDNS);
            if (ptrDDNS < DDNSData + sizeof (DDNSData) - 1)
                ptrDDNS += 1;

            // Return to reading names
            curHTTP.smPost = SM_DDNS_READ_NAME;
            break;

            // Reads in a service ID
        case SM_DDNS_READ_SERVICE:
            // Read the integer id
            if (HTTPReadPostValue(curHTTP.data, HTTP_MAX_DATA_LEN) == HTTP_READ_INCOMPLETE)
                return HTTP_IO_NEED_DATA;

            // Convert to a service ID
            DDNSSetService((BYTE) atol((char*) curHTTP.data));

            // Return to reading names
            curHTTP.smPost = SM_DDNS_READ_NAME;
            break;

            // Sets up the DDNS client for an update
        case SM_DDNS_DONE:
            // Since user name and password changed, force an update immediately
            DDNSForceUpdate();

            // Redirect to prevent POST errors
            lastSuccess = TRUE;
            strcpypgm2ram((char*) curHTTP.data, "/dyndns/index.htm");
            curHTTP.httpStatus = HTTP_REDIRECT;
            return HTTP_IO_DONE;
    }

    return HTTP_IO_WAITING; // Assume we're waiting to process more data
}
#endif	// #if defined(STACK_USE_DYNAMICDNS_CLIENT)


#endif //defined(HTTP_USE_POST)


/****************************************************************************
  Section:
        Dynamic Variable Callback Functions
 ***************************************************************************/

/*****************************************************************************
  Function:
        void HTTPPrint_varname(void)

  Internal:
        See documentation in the TCP/IP Stack API or HTTP2.h for details.
 ***************************************************************************/

void
HTTPPrint_builddate(void)
{
    curHTTP.callbackPos = 0x01;
    if (TCPIsPutReady(sktHTTP) < strlenpgm((ROM char*) __DATE__))
        return;

    curHTTP.callbackPos = 0x00;
    TCPPutROMString(sktHTTP, (ROM void*) __DATE__);
}

void
HTTPPrint_version(void)
{
    TCPPutROMString(sktHTTP, (ROM void*) TCPIP_STACK_VERSION);
}

void
HTTPPrint_inp(WORD num)
{
    // Determine which Inputs
    switch (num)
    {
        case 0:
            num = IN0_IO;
            break;
        case 1:
            num = IN1_IO;
            break;
        case 2:
            num = IN2_IO;
            break;
         case 3:
            num = IN3_IO;
            break;
         case 4:
            num = IN4_IO;
            break;
         case 5:
            num = IN5_IO;
            break;
         case 6:
            num = IN6_IO;
            break;
         case 7:
            num = IN7_IO;
            break;

        default:
            num = 0;
    }

    // Print the output
    TCPPutROMString(sktHTTP, (num ? "-": "+"));
}

void
HTTPPrint_btn(WORD num)
{
    // Determine which button
    switch (num)
    {

        case 1:
            num = BUTTON1_IO;
            break;
        case 2:
            num = BUTTON2_IO;
            break;
        default:
            num = 0;
    }

    // Print the output
    TCPPutROMString(sktHTTP, (num ? "+": "-"));
}
void
HTTPPrint_led(WORD num)
{
    // Determine which LED
    switch (num)
    {
        case 1:
            num = LED1_IO;
            break;

        case 2:
            num = LED2_IO;
            break;
        
        case 3:
            num = LED3_IO;
            break;
       
        default:
            num = 0;
    }

    // Print the output
    TCPPut(sktHTTP, (num ? '+' : '-'));
}

void
HTTPPrint_out(WORD num)
{
    // Determine which Output
    switch (num)
    {
        case 0:
            num = OUT0_IO;
            break;
        case 1:
            num = OUT1_IO;
            break;
        case 2:
            num = OUT2_IO;
            break;
        case 3:
            num = OUT3_IO;
            break;
        case 4:
            num = OUT4_IO;
            break;
        case 5:
            num = OUT5_IO;
            break;
        case 6:
            num = OUT6_IO;
            break;
        case 7:
            num = OUT7_IO;
            break;
        case 8:
            num = OUT8_IO;
            break;
        case 9:
            num = OUT9_IO;
            break;
        default:
            num = 0;
    }

    // Print the output
    TCPPut(sktHTTP, (num ? '+' : '-'));
}
void
HTTPPrint_pwr5V()
{
    BYTE temp[8];
    stoa_dec((char*) temp, SensorReading.Plus5V * 100, 2);
    TCPPutString(sktHTTP, temp);

}

void
HTTPPrint_va_curr()
{
    BYTE temp[8];
    
    stoa_dec((char*) temp, WDIR_cal_tmp.WindDir_north, 0);
    if (WDIR_cal_tmp.DoWindDirCal)
        TCPPutString(sktHTTP, temp);
    else
        TCPPutROMString(sktHTTP, "-");

    // Kludge to time out windir cal mode
    // depends on the fact the Wind dir Cal page repeadetly calls this token to update the screen
   WDIR_cal_tmp.timeout =  TickGet()+4 * TICK_SECOND;
}

void
HTTPPrint_va_min()
{
    BYTE temp[8];

    stoa_dec((char*) temp, WDIR_cal_tmp.WindDir_min, 0);

    if (WDIR_cal_tmp.DoWindDirCal)
        TCPPutString(sktHTTP, temp);
    else
        TCPPutROMString(sktHTTP, "-");
}
void
HTTPPrint_va_max()
{
    BYTE temp[8];
    stoa_dec((char*) temp, WDIR_cal_tmp.WindDir_max * 1, 0);

    if (WDIR_cal_tmp.DoWindDirCal)
        TCPPutString(sktHTTP, temp);
    else
        TCPPutROMString(sktHTTP, "-");
}
void
HTTPPrint_adc(WORD num)
{
    BYTE AN0String[8];
    WORD ADval;

// Note: the ADC1BUFn are assigned on a dynamic basisand do not necessarily map to correspoinding AN inputs.
// A 1:1 mapping is only achieved if all analog inputs are ennabled  in the ADC configuration.
    switch (num)
    {
        case 0:
            ADval = (WORD) ADC1BUF0;
            break;
        case 1:
            ADval = (WORD) ADC1BUF1;
            break;
        case 2:
            ADval = (WORD) ADC1BUF2;
            break;
        case 3:
            ADval = (WORD) ADC1BUF3;
            break;
        case 4:
            ADval = (WORD) ADC1BUF4;
            break;
        case 5:
            ADval = (WORD) ADC1BUF5;
            break;
        default:
            ADval =0;

    }
    uitoa(ADval, (BYTE*) AN0String);
    TCPPutString(sktHTTP, AN0String);
}
HTTPPrint_time(void)
{
    BCD_RTCC *date_time;

    if ((date_time = RTC_Read_BCD_Time()) != NULL)
    {
        TCPPutString(sktHTTP, (BYTE *) RTC_Convert_BCD_Time_to_String(date_time));
    }
}
HTTPPrint_date(void)
{
    BCD_RTCC *date_time;

    if ((date_time = RTC_Read_BCD_Time()) != NULL)
    {
        TCPPutString(sktHTTP, (BYTE *) RTC_Convert_BCD_Date_to_String(date_time));
    }
}


static void
printIP(IP_ADDR ip)
{
    BYTE digits[4];
    BYTE i;

    for (i = 0; i < 4u; i++)
    {
        if (i)
            TCPPut(sktHTTP, '.');
        uitoa(ip.v[i], digits);
        TCPPutString(sktHTTP, digits);
    }
}

void
HTTPPrint_config_hostname(void)
{
    TCPPutString(sktHTTP, AppConfig.NetBIOSName);
}

void
HTTPPrint_W_SID(void)
{
    TCPPutString(sktHTTP, (BYTE*) WX.Wunder.StationID);
}


void
HTTPPrint_W_PASS(void)
{
    TCPPutString(sktHTTP, (BYTE *) WX.Wunder.StationPW);
}



ROM BYTE HTML_checked[] = "checked";
ROM BYTE HTML_off[] = "Off";
void
HTTPPrint_W_ENB(void)
{
    if (WX.Wunder.report_enable.Station)
        TCPPutROMString(sktHTTP, HTML_checked);
    else
        TCPPutROMString(sktHTTP, HTML_off);
}
void
HTTPPrint_R_WND(void)
{
    if ( WX.Wunder.report_enable.Wind)
        TCPPutROMString(sktHTTP, HTML_checked);
    else
        TCPPutROMString(sktHTTP, HTML_off);
}
void
HTTPPrint_R_HYG(void)
{
    if ( WX.Wunder.report_enable.Hyg)
        TCPPutROMString(sktHTTP, HTML_checked);
    else
        TCPPutROMString(sktHTTP, HTML_off);
}
void
HTTPPrint_R_SOL(void)
{
    if ( WX.Wunder.report_enable.Sol)
        TCPPutROMString(sktHTTP, HTML_checked);
    else
        TCPPutROMString(sktHTTP, HTML_off);
}
void
HTTPPrint_R_RAIN(void)
{
    if ( WX.Wunder.report_enable.Rain)
        TCPPutROMString(sktHTTP, HTML_checked);
    else
        TCPPutROMString(sktHTTP, HTML_off);
}

void
HTTPPrint_Ala(WORD num)
{
    if (WX.Alarms.enable & 1<<num )
        TCPPutROMString(sktHTTP, HTML_checked);
    else
        TCPPutROMString(sktHTTP, HTML_off);
}
void
HTTPPrint_ELEV(void)
{
    BYTE temp[8];
    stoa_dec((char*) temp, WX.Wunder.StationElev, 0);
    TCPPutString(sktHTTP, temp);
}
void
HTTPPrint_UpInt(void)
{
    BYTE temp[8];
    stoa_dec((char*) temp, WX.Wunder.UplnkInterval, 0);
    TCPPutString(sktHTTP, temp);
}
void
HTTPPrint_TZoff(void)
{
    BYTE temp[8];
    stoa_dec((char*) temp, WX.Wunder.TZ_offset, 0);
    TCPPutString(sktHTTP, temp);
}

void
HTTPPrint_WindDir(void)
{
    BYTE temp[8];
    stoa_dec((char*) temp, SensorReading.Wind_dir, 0);
    TCPPutString(sktHTTP, temp);
}

void
HTTPPrint_WindGust(void)
{
    BYTE temp[8];
    stoa_dec((char*) temp, SensorReading.Wind_gust * 10, 1);
    TCPPutString(sktHTTP, temp);
}

void
HTTPPrint_WindSpeed(void)
{
    BYTE temp[8];
    stoa_dec((char*) temp, SensorReading.Wind_speed * 10, 1);
    TCPPutString(sktHTTP, temp);
}

void
HTTPPrint_Temp_F(void)
{
    BYTE temp[8];
    stoa_dec((char*) temp, SensorReading.TempF * 10, 1);
    TCPPutString(sktHTTP, temp);
}

void
HTTPPrint_Dew_F(void)
{
    BYTE temp[8];
    stoa_dec((char*) temp, SensorReading.DewptF * 10, 1);
    TCPPutString(sktHTTP, temp);
}

void
HTTPPrint_RelH(void)
{
    BYTE temp[8];
    stoa_dec((char*) temp, SensorReading.RH * 10, 1);
    TCPPutString(sktHTTP, temp);

}

void
HTTPPrint_Baro_In(void)
{
    BYTE temp[8];
    stoa_dec((char*) temp, SensorReading.BaromIn * 100, 2);
    TCPPutString(sktHTTP, temp);
}

void
HTTPPrint_Rain_In(void)
{
    BYTE temp[8];
    stoa_dec((char*) temp, SensorReading.RainIn * 100, 2);
    TCPPutString(sktHTTP, temp);
}

void
HTTPPrint_RainDay(void)
{
    BYTE temp[8];
    stoa_dec((char*) temp, SensorReading.RainDaily * 100, 2);
    TCPPutString(sktHTTP, temp);
}
void
HTTPPrint_Sol_W(void)
{
    BYTE temp[8];
    stoa_dec((char*) temp, SensorReading.SolRad, 0);
    TCPPutString(sktHTTP, temp);
}

void
HTTPPrint_wifiSSID(void)
{
    TCPPutString(sktHTTP, AppConfig.MySSID);
}

void HTTPPrint_CALho(void)
{
    BYTE temp[8];
    stoa_dec((char*) temp, WX.Calib.Hyg_offs, 0);
    TCPPutString(sktHTTP, temp);
}
void
HTTPPrint_CALto(void)
{
    BYTE temp[8];
    stoa_dec((char*) temp, WX.Calib.Temp_offs, 0);
    TCPPutString(sktHTTP, temp);
}
void HTTPPrint_CALsg(void)
{
    BYTE temp[8];
    stoa_dec((char*) temp, WX.Calib.Sol_gain, 0);
    TCPPutString(sktHTTP, temp);
}

void HTTPPrint_CALbo(void)
{
    BYTE temp[8];
    stoa_dec((char*) temp, WX.Calib.Baro_offs, 0);
    TCPPutString(sktHTTP, temp);
}

void HTTPPrint_CALwo(void)
{
    BYTE temp[8];
    stoa_dec((char*) temp, WX.Calib.WDir_offs, 0);
    TCPPutString(sktHTTP, temp);
}

void HTTPPrint_CALra(void)
{
    BYTE temp[8];
    stoa_dec((char*) temp, WX.Calib.Rain_counts, 0);
    TCPPutString(sktHTTP, temp);
}

void HTTPPrint_CALws(void)
{
    BYTE temp[8];
    stoa_dec((char*) temp, WX.Calib.Wind_counts, 0);
    TCPPutString(sktHTTP, temp);
}

void HTTPPrint_CALwf(void)      // AN_CAL_FACTOR
{
    BYTE temp[8];
    stoa_dec((char*) temp, WX.Calib.Wind_AN_CalFactor *100,2);
    TCPPutString(sktHTTP, temp);
}

void
HTTPPrint_wifiEnc(WORD num)
{
    BYTE temp [4];
    if (num == AppConfig.SecurityMode)
        TCPPutROMString(sktHTTP, (ROM BYTE*) "selected");

    uitoa(num, (BYTE*) temp);
    TCPPutROMString(sktHTTP, (ROM BYTE*) " value=\"");
    TCPPutString(sktHTTP, temp);
    TCPPutROMString(sktHTTP, (ROM BYTE*) "\"");
}


void
HTTPPrint_wifiKey(void)
{
    int i;
    int len;


    switch (AppConfig.SecurityMode)
    {
        case WF_SECURITY_WEP_40:
            len = 5;
            break;

        case WF_SECURITY_WEP_104:
            len = 13;
            break;

        case WF_SECURITY_WPA_WITH_KEY:
        case WF_SECURITY_WPA2_WITH_KEY:
        case WF_SECURITY_WPA_AUTO_WITH_KEY:
            len = 32;
            break;

        case WF_SECURITY_WPA_WITH_PASS_PHRASE:
        case WF_SECURITY_WPA2_WITH_PASS_PHRASE:
        case WF_SECURITY_WPA_AUTO_WITH_PASS_PHRASE:
            TCPPutString(sktHTTP, AppConfig.SecurityKey);
            len = 0;
            break;
        default:
            len = 0;
    }

    // convert the binary number to asci encoded hex string and put it out 
    for (i = 0; i < len; i++)
    {
        TCPPut(sktHTTP, btohexa_high(AppConfig.SecurityKey[i]));
        TCPPut(sktHTTP, btohexa_low(AppConfig.SecurityKey[i]));

        if (TCPIsPutReady(sktHTTP) < 2) // To check if there is room in the put buffer and if not run the stack task to send off
        { // what is ready, so we don't loose output
            while (TCPIsPutReady(sktHTTP) < 40)
            {
                StackTask();
                // StackApplications();
            }
        }

    }
}

void
HTTPPrint_config_dhcpchecked(void)
{
    if (AppConfig.Flags.bIsDHCPEnabled)
        TCPPutROMString(sktHTTP, HTML_checked);
    else
        TCPPutROMString(sktHTTP, HTML_off);

}

void
HTTPPrint_config_ip(void)
{
    printIP(AppConfig.MyIPAddr);
    return;
}

void
HTTPPrint_config_gw(void)
{
    printIP(AppConfig.MyGateway);
}

void
HTTPPrint_config_subnet(void)
{
    printIP(AppConfig.MyMask);
}

void
HTTPPrint_config_dns1(void)
{
    printIP(AppConfig.PrimaryDNSServer);
}

void
HTTPPrint_config_dns2(void)
{
    printIP(AppConfig.SecondaryDNSServer);
}

void
HTTPPrint_nist_1(void)
{
    printIP(WX.TimeServer.NIST1);
}

void
HTTPPrint_nist_2(void)
{
    printIP(WX.TimeServer.NIST2);
}

void
HTTPPrint_config_mac(void)
{
    BYTE i;

    if (TCPIsPutReady(sktHTTP) < 18u)
    {//need 17 bytes to write a MAC
        curHTTP.callbackPos = 0x01;
        return;
    }

    // Write each byte
    for (i = 0; i < 6u; i++)
    {
        if (i)
            TCPPut(sktHTTP, ':');
        TCPPut(sktHTTP, btohexa_high(AppConfig.MyMACAddr.v[i]));
        TCPPut(sktHTTP, btohexa_low(AppConfig.MyMACAddr.v[i]));
    }

    // Indicate that we're done
    curHTTP.callbackPos = 0x00;
}


void
HTTPPrint_reboot(void)
{
    // This is not so much a print function, but causes the board to reboot
    // when the configuration is changed.  If called via an AJAX call, this
    // will gracefully reset the board and bring it back online immediately
    Reset();
}

void
HTTPPrint_rebootaddr(void)
{// This is the expected address of the board upon rebooting
    TCPPutString(sktHTTP, AppConfig.NetBIOSName);
}
#if defined(STACK_USE_DYNAMICDNS_CLIENT)
void
HTTPPrint_ddns_user(void)
{
#if defined(STACK_USE_DYNAMICDNS_CLIENT)
    if (DDNSClient.ROMPointers.Username || !DDNSClient.Username.szRAM)
        return;
    if (curHTTP.callbackPos == 0x00u)
        curHTTP.callbackPos = (PTR_BASE) DDNSClient.Username.szRAM;
    curHTTP.callbackPos = (PTR_BASE) TCPPutString(sktHTTP, (BYTE*) (PTR_BASE) curHTTP.callbackPos);
    if (*(BYTE*) (PTR_BASE) curHTTP.callbackPos == '\0')
        curHTTP.callbackPos = 0x00;
#endif
}

void
HTTPPrint_ddns_pass(void)
{
#if defined(STACK_USE_DYNAMICDNS_CLIENT)
    if (DDNSClient.ROMPointers.Password || !DDNSClient.Password.szRAM)
        return;
    if (curHTTP.callbackPos == 0x00u)
        curHTTP.callbackPos = (PTR_BASE) DDNSClient.Password.szRAM;
    curHTTP.callbackPos = (PTR_BASE) TCPPutString(sktHTTP, (BYTE*) (PTR_BASE) curHTTP.callbackPos);
    if (*(BYTE*) (PTR_BASE) curHTTP.callbackPos == '\0')
        curHTTP.callbackPos = 0x00;
#endif
}

void
HTTPPrint_ddns_host(void)
{
#if defined(STACK_USE_DYNAMICDNS_CLIENT)
    if (DDNSClient.ROMPointers.Host || !DDNSClient.Host.szRAM)
        return;
    if (curHTTP.callbackPos == 0x00u)
        curHTTP.callbackPos = (PTR_BASE) DDNSClient.Host.szRAM;
    curHTTP.callbackPos = (PTR_BASE) TCPPutString(sktHTTP, (BYTE*) (PTR_BASE) curHTTP.callbackPos);
    if (*(BYTE*) (PTR_BASE) curHTTP.callbackPos == '\0')
        curHTTP.callbackPos = 0x00;
#endif
}

extern ROM char * ROM ddnsServiceHosts[];

void
HTTPPrint_ddns_service(WORD i)
{
#if defined(STACK_USE_DYNAMICDNS_CLIENT)
    if (!DDNSClient.ROMPointers.UpdateServer || !DDNSClient.UpdateServer.szROM)
        return;
    if ((ROM char*) DDNSClient.UpdateServer.szROM == ddnsServiceHosts[i])
        TCPPutROMString(sktHTTP, (ROM BYTE*) "selected");
#endif
}

void
HTTPPrint_ddns_status(void)
{
#if defined(STACK_USE_DYNAMICDNS_CLIENT)
    DDNS_STATUS s;
    s = DDNSGetLastStatus();
    if (s == DDNS_STATUS_GOOD || s == DDNS_STATUS_UNCHANGED || s == DDNS_STATUS_NOCHG)
        TCPPutROMString(sktHTTP, (ROM BYTE*) "ok");
    else if (s == DDNS_STATUS_UNKNOWN)
        TCPPutROMString(sktHTTP, (ROM BYTE*) "unk");
    else
        TCPPutROMString(sktHTTP, (ROM BYTE*) "fail");
#else
    TCPPutROMString(sktHTTP, (ROM BYTE*) "fail");
#endif
}

void
HTTPPrint_ddns_status_msg(void)
{
    if (TCPIsPutReady(sktHTTP) < 75u)
    {
        curHTTP.callbackPos = 0x01;
        return;
    }

#if defined(STACK_USE_DYNAMICDNS_CLIENT)
    switch (DDNSGetLastStatus())
    {
        case DDNS_STATUS_GOOD:
        case DDNS_STATUS_NOCHG:
            TCPPutROMString(sktHTTP, (ROM BYTE*) "The last update was successful.");
            break;
        case DDNS_STATUS_UNCHANGED:
            TCPPutROMString(sktHTTP, (ROM BYTE*) "The IP has not changed since the last update.");
            break;
        case DDNS_STATUS_UPDATE_ERROR:
        case DDNS_STATUS_CHECKIP_ERROR:
            TCPPutROMString(sktHTTP, (ROM BYTE*) "Could not communicate with DDNS server.");
            break;
        case DDNS_STATUS_INVALID:
            TCPPutROMString(sktHTTP, (ROM BYTE*) "The current configuration is not valid.");
            break;
        case DDNS_STATUS_UNKNOWN:
            TCPPutROMString(sktHTTP, (ROM BYTE*) "The Dynamic DNS client is pending an update.");
            break;
        default:
            TCPPutROMString(sktHTTP, (ROM BYTE*) "An error occurred during the update.<br />The DDNS Client is suspended.");
            break;
    }
#else
    TCPPutROMString(sktHTTP, (ROM BYTE*) "The Dynamic DNS Client is not enabled.");
#endif

    curHTTP.callbackPos = 0x00;
}

#endif
void
HTTPPrint_status_ok(void)
{
    if (lastSuccess)
        TCPPutROMString(sktHTTP, (ROM BYTE*) "block");
    else
        TCPPutROMString(sktHTTP, (ROM BYTE*) "none");
    lastSuccess = FALSE;
}

void
HTTPPrint_status_fail(void)
{
    if (lastFailure != NULL)
        TCPPutROMString(sktHTTP, (ROM BYTE*) "block");
    else
        TCPPutROMString(sktHTTP, (ROM BYTE*) "none");

}

void
HTTPPrint_status_msg(void)
{
    if (lastFailure != NULL)
        TCPPutROMString(sktHTTP, (ROM BYTE*) lastFailure);
}

void
HTTPPrint_M_TO(void)
{
    TCPPutString(sktHTTP, (BYTE*) WX.Mail.SendTo);
}

void
HTTPPrint_M_SRV(void)
{
    TCPPutString(sktHTTP, (BYTE*) WX.Mail.Server);
}

void
HTTPPrint_M_USR(void)
{
    TCPPutString(sktHTTP, (BYTE*) WX.Mail.User_name);
}
void
HTTPPrint_M_PWD(void)
{
    TCPPutString(sktHTTP, (BYTE*) WX.Mail.password);
}
void
HTTPPrint_M_PRT(void)
{
    BYTE temp[8];
    stoa_dec((char*) temp, WX.Mail.port, 0);
    TCPPutString(sktHTTP, temp);
}

void
HTTPPrint_ST_USR(void)
{
    TCPPutString(sktHTTP, (BYTE*) WX.Station.User_name);
}
void
HTTPPrint_ST_PWD(void)
{
    TCPPutString(sktHTTP, (BYTE*) WX.Station.password);
}
void HTTPPrint_smtps_en(void) {
#if defined(STACK_USE_SSL_CLIENT)
    TCPPutROMString(sktHTTP, (ROM BYTE*) "inline");
#else
    TCPPutROMString(sktHTTP, (ROM BYTE*) "none");
#endif
}
#endif //defined(STACK_USE_HTTP2_SERVER)







