#include "TCPIPConfig.h"

#if defined(STACK_USE_SMTP_CLIENT)

#include "TCPIP Stack/TCPIP.h"
#include "Main.h"
#include "WX_perm_data.h"
#define  MAIL_DEADTIME 60       // seconds to wait until we can send an other mail

static enum {
    MAIL_HOME = 0,
    MAIL_BEGIN,
    MAIL_SMTP_FINISHING,
    MAIL_DONE
} MailState = MAIL_HOME;
static DWORD WaitTime;

static BYTE RAMStringBody[120];
static unsigned short Alarms = 0;

//A mechanism by which the alarm can be triggert and the alarm message can be defined

void SMTP_trigger_mail(char * message) {
    // Copy message into static buffer for mail sending
    if (MailState == MAIL_HOME) {
        strncpy((char*) RAMStringBody, message, sizeof (RAMStringBody));
        MailState++;
    }
}

void SMTP_set_alarm(unsigned short alarm_no) {
    Alarms = alarm_no;
}

void SMTP_Mail_alarm(void) {
    // Send an email once
    // the entier message body and all parameters must  be in RAM for the duration the
    // message is beeing sent
    WORD SMTP_error;
    char temp[6];

    switch (MailState) {
        case MAIL_HOME:

            if (Alarms) {
                strcpy((char*) RAMStringBody, "Alarm # ");
                if (Alarms & 1 << 1)
                    strcat((char*) RAMStringBody, "1 (SV2:7),");
                if (Alarms & 1 << 2)
                    strcat((char*) RAMStringBody, "2 (SV2:8),");
                if (Alarms & 1 << 3)
                    strcat((char*) RAMStringBody, "3 (SV2:9,");
                if (Alarms & 1 << 4)
                    strcat((char*) RAMStringBody, "4 (SV2:10),");

                RAMStringBody[strlen((char *) RAMStringBody) - 1] = ' '; // remove trailing coma
                strcat((char*) RAMStringBody, "is active!\n\r");
                Alarms = 0;
                MailState++;
            }
            break;

        case MAIL_BEGIN:
            if (SMTPBeginUsage()) {
                // Note that these strings must stay allocated in
                // memory until SMTPIsBusy() returns FALSE.  To
                // guarantee that the C compiler does not reuse this
                // memory, you must allocate the strings as static.

                // To
                SMTPClient.To.szRAM = (BYTE *) WX.Mail.SendTo;

                // From
                //SMTPClient.From.szROM = (ROM BYTE*)"<noreply@noname.name>";
                //SMTPClient.From.szROM = (ROM BYTE*)"\"WX_Station\" <no-reply@noname.name>";
                //SMTPClient.ROMPointers.From = 1;
                // Because of antispam measures we need a valid e-mail address to send mail from, or at least a valid, not black-listed domain"
                // Since amy "made-up" From-email-address might get black listed in the future I'm using the To-email address also here as well.
                // since it always should be perfectly legal to send mail to yourself
                SMTPClient.From.szRAM = (BYTE *) WX.Mail.SendTo; // Using the Send To as SendFrom to use a valid e-mail address


                // Subject
                //SMTPClient.Subject.szROM = (ROM BYTE*)"WX Station Alarm";
                SMTPClient.Subject.szRAM = (BYTE *) WX.Wunder.StationID;
                //SMTPClient.ROMPointers.Subject = 1;

                // Body
                SMTPClient.Body.szRAM = RAMStringBody;

                // Server items -- Must use a mail server that is not tied to a IP addressfrom the ISP (like astound, comcast etc)
                SMTPClient.Server.szRAM = (BYTE *) WX.Mail.Server; // SMTP server address
                SMTPClient.ServerPort = WX.Mail.port;
                //   SMTPClient.ROMPointers.Server = 1;

                // only needed if username/passowrd is required by the mail server used
                SMTPClient.Username.szRAM = (BYTE *) WX.Mail.User_name;
                //SMTPClient.ROMPointers.Username = 1;

                SMTPClient.Password.szRAM = (BYTE *) WX.Mail.password;
                //  SMTPClient.ROMPointers.Password = 1;

                SMTPSendMail();
                MailState++;
            }
            break;

        case MAIL_SMTP_FINISHING:
            if (!SMTPIsBusy())
            { // Finished sending mail
                MailState++;
                WaitTime = TickGet();
               if ( (SMTP_error = SMTPEndUsage()) != 0)
               {
                   putrsUART("SMTP Error: ");
                   stoa_dec(temp, SMTP_error, 0);
                   putsUART( temp );
                   putrsUART("\n\r");
               }

               
            }
            break;

        case MAIL_DONE:
            if (TickGet() > (WaitTime + MAIL_DEADTIME * TICK_SECOND)) // plus a dead time
            {
                MailState = MAIL_HOME;
            }
            break;
    }
}

// Example for long message
/*
void SMTPDemo(void)
{
        // Send an email once if someone pushes BUTTON2 and BUTTON3 simultaneously
        // This is a multi-part message example, where the message
        // body is dynamically generated and need not fit in RAM.
        // LED1 will be used as a busy indicator
        // LED2 will be used as a mail sent successfully indicator
        static enum
        {
                MAIL_HOME = 0,
                MAIL_BEGIN,
                MAIL_PUT_DATA,
                MAIL_PUT_DATA2,
                MAIL_SMTP_FINISHING,
                MAIL_DONE
        } MailState = MAIL_HOME;
        static BYTE *MemPtr;
        static DWORD WaitTime;
	     
        switch(MailState)
        {
                case MAIL_HOME:
                    if((BUTTON2_IO == 0u) && (BUTTON3_IO == 0u))
                        {
                                // Start sending an email
                                LED1_IO = 1;
                                MailState++;
                                LED2_IO = 0;
                        }
                        break;
		
                case MAIL_BEGIN:
                        if(SMTPBeginUsage())
                        {
                                // Note that these strings must stay allocated in
                                // memory until SMTPIsBusy() returns FALSE.  To
                                // guarantee that the C compiler does not reuse this
                                // memory, you must allocate the strings as static.

                                static BYTE RAMStringTo[] = "joe@picsaregood.com";
                                //static BYTE RAMStringCC[] = "foo@picsaregood.com, \"Jane Smith\" <jane.smith@picsaregood.com>";
		
                                SMTPClient.Server.szROM = "mail";	// SMTP server address
                                SMTPClient.ROMPointers.Server = 1;
                                //SMTPClient.Username.szROM = (ROM BYTE*)"mchpboard";
                                //SMTPClient.ROMPointers.Username = 1;
                                //SMTPClient.Password.szROM = (ROM BYTE*)"secretpassword";
                                //SMTPClient.ROMPointers.Password = 1;
                                SMTPClient.To.szRAM = RAMStringTo;
                                //SMTPClient.CC.szRAM = RAMStringCC;
                                SMTPClient.From.szROM = (ROM BYTE*)"\"SMTP Service\" <mchpboard@picsaregood.com>";
                                SMTPClient.ROMPointers.From = 1;
                                SMTPClient.Subject.szROM = (ROM BYTE*)"Hello world!  SMTP Test.";
                                SMTPClient.ROMPointers.Subject = 1;
                                SMTPSendMail();
                                MailState++;
                        }
                        break;
		
                case MAIL_PUT_DATA:
                        // Check to see if a failure occured
                        if(!SMTPIsBusy())
                        {
                                // Finished sending mail
                                LED1_IO = 0;
                                MailState = MAIL_DONE;
                                WaitTime = TickGet();
                                LED2_IO = (SMTPEndUsage() == SMTP_SUCCESS);
                                break;
                        }
		
                        if(SMTPIsPutReady() >= 121u)
                        {
                                SMTPPutROMString((ROM BYTE*)"Hello!\r\n\r\nThis mail was automatically generated by Microchip TCP/IP Stack " TCPIP_STACK_VERSION ".\r\n\r\nThe following is a snapshot of RAM:\r\n");
                                SMTPFlush();
				
                                MemPtr = 0x0000;
                                MailState++;
                        }
                        break;
		
                case MAIL_PUT_DATA2:
                        // Check to see if a failure occured
                        if(!SMTPIsBusy())
                        {
                                // Finished sending mail
                                LED1_IO = 0;
                                MailState = MAIL_DONE;
                                WaitTime = TickGet();
                                LED2_IO = (SMTPEndUsage() == SMTP_SUCCESS);
                                break;
                        }
		
                        if(SMTPIsPutReady() >= 75u)
                        {
                                BYTE i, c;
                                WORD_VAL w;
		
                                // Write line address
                                w.Val = (WORD)MemPtr;
                                SMTPPut(btohexa_high(w.v[1]));
                                SMTPPut(btohexa_low(w.v[1]));
                                SMTPPut(btohexa_high(w.v[0]));
                                SMTPPut(btohexa_low(w.v[0]));
                                SMTPPut(' ');
		
                                // Write data bytes in hex
                                for(i = 0; i < 16u; i++)
                                {
                                        SMTPPut(' ');
                                        #if defined(__C32__)		// PIC32 has memory protection, so you can't just read from any old address
                                                c = 'R';
                                                MemPtr++;
                                        #else
                                                c = *MemPtr++;
                                        #endif
                                        SMTPPut(btohexa_high(c));
                                        SMTPPut(btohexa_low(c));
                                        if(i == 7u)
                                                SMTPPut(' ');
                                }
		
                                SMTPPut(' ');
                                SMTPPut(' ');
		
                                // Write data bytes in ASCII
                                MemPtr -= 16;
                                for(i = 0; i < 16u; i++)
                                {
                                        #if defined(__C32__)		// PIC32 has memory protection, so you can't just read from any old address
                                                c = 'R';
                                                MemPtr++;
                                        #else
                                                c = *MemPtr++;
                                        #endif
                                        if(c < ' ' || c > '~')
                                                c = '.';
                                        SMTPPut(c);
		
                                        if(i == 7u)
                                                SMTPPut(' ');
                                }
		
                                SMTPPut('\r');
                                SMTPPut('\n');
                                SMTPFlush();
		
                                // Make sure not to read from memory above address 0x0E7F.
                                // Doing so would disrupt volatile pointers, ERDPT, FSR0, FSR1, FSR2, etc.
                                if((WORD)MemPtr >= 0xE7Fu)
                                {
                                        SMTPPutDone();
                                        MailState++;
                                }
                        }
                        break;
		
                case MAIL_SMTP_FINISHING:
                        // Check to see if we are done communicating with the SMTP server
                        if(!SMTPIsBusy())
                        {
                                // Finished sending mail
                                LED1_IO = 0;
                                MailState = MAIL_DONE;
                                WaitTime = TickGet();
                                LED2_IO = (SMTPEndUsage() == SMTP_SUCCESS);
                        }
                        break;
		
                case MAIL_DONE:
                        // Wait for the user to release BUTTON2 or BUTTON3 for at
                        // least 1 second to pass before allowing another
                        // email to be sent.  This is merely to prevent
                        // accidental flooding of email boxes while
                        // developing code.  Your application may wish to
                        // remove this.
                        if(BUTTON2_IO || BUTTON3_IO)
                        {
                                if(TickGet() - WaitTime > TICK_SECOND)
                                        MailState = MAIL_HOME;
                        }
                        break;
        }
}
 */
#endif //#if defined(STACK_USE_SMTP_CLIENT)
