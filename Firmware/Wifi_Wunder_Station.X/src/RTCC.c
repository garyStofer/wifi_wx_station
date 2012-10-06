/*****************************************************************************
 *
 * Real Time Clock Calender For PIC24F ffamily
 *
 *****************************************************************************/

#include "Hardwareprofile.h"
#include "rtcc.h"
// #include "string.h"

BCD_RTCC _RTC_time;     // Global that holds the last read time read from the device

/*****************************************************************************
 * Arrays: _time_str and _date_str
 *
 * Overview: These arrays contain the time and date strings. 
 * RTCCProcessEvents updates them.
 *
 *****************************************************************************/
static char time_str[17] = "                "; // "Sat 10:01:15    "
static char date_str[17] = "                "; // "Sep 30, 2005    "


static void
RTC_Unlock(void)
{
    // code from section 29 of pc24F Family reference file 39696b.pdf
    // The manual does not otherwise specify to send the NVMKEy unlock sequence,
    // except by giving the following example code

    asm ("disi	#5"); // Disable interrupts for 5+1 instructions
    asm ("MOV #NVMKEY, W1"); //move the address of NVMKEY into W1
    asm ("MOV #0x55, W2");
    asm ("MOV W2, [W1]"); //start 55/AA sequence
    asm ("MOV #0xAA, W3");
    asm ("MOV W3, [W1]");
    asm ("BSET RCFGCAL, #13"); // set the RTCWREN bit -- RTCC registers are now writable
}

static void
RTC_Lock(void)
{
    RCFGCALbits.RTCWREN = 0;
}

/*****************************************************************************/
void RTC_Init(void)    // configures the oscialltor to clock the RTC
{
    // Enables the SOSC for RTCC operation with unlocking sequene, basically OSCCONbits.SOSCEN =1;
    asm("mov #OSCCON,W1");
    asm("mov.b	#0x02, W0");
    asm("mov.b	#0x46, W2");
    asm("mov.b	#0x57, W3");
    asm("mov.b	W2, [W1]");
    asm("mov.b	W3, [W1]");
    asm("mov.b	W0, [W1]");

}


/*****************************************************************************/
BCD_RTCC *
RTC_Read_BCD_Time(void)
{
    if (!RCFGCALbits.RTCEN)     // Clock not enabled --
        return NULL;

    while (_RTCSYNC) // in case a rollover is in process wait until complete
    {
        ;
    }
    do // Read the RTC values and check at the end if a rollover occured during the read
    {
        _RTCPTR = 3;
        _RTC_time.prt11 = RTCVAL;
        _RTC_time.prt10 = RTCVAL;
        _RTC_time.prt01 = RTCVAL;
        _RTC_time.prt00 = RTCVAL;
    } while (_RTCSYNC);

    return & _RTC_time;
}

/*********************************************************************************************/
char *
RTC_Convert_BCD_Date_to_String (BCD_RTCC * t)
{
    switch (t->mth)     // since months are from 1-12 no BCD to bin conversion  nescessary
    {
        default:
        case 0x01:
            date_str[0] = 'J';
            date_str[1] = 'a';
            date_str[2] = 'n';
            break;
        case 0x02:
            date_str[0] = 'F';
            date_str[1] = 'e';
            date_str[2] = 'b';
            break;
        case 0x03:
            date_str[0] = 'M';
            date_str[1] = 'a';
            date_str[2] = 'r';
            break;
        case 0x04:
            date_str[0] = 'A';
            date_str[1] = 'p';
            date_str[2] = 'r';
            break;
        case 0x05:
            date_str[0] = 'M';
            date_str[1] = 'a';
            date_str[2] = 'y';
            break;
        case 0x06:
            date_str[0] = 'J';
            date_str[1] = 'u';
            date_str[2] = 'n';
            break;
        case 0x07:
            date_str[0] = 'J';
            date_str[1] = 'u';
            date_str[2] = 'l';
            break;
        case 0x08:
            date_str[0] = 'A';
            date_str[1] = 'u';
            date_str[2] = 'g';
            break;
        case 0x09:
            date_str[0] = 'S';
            date_str[1] = 'e';
            date_str[2] = 'p';
            break;
        case 0x10:
            date_str[0] = 'O';
            date_str[1] = 'c';
            date_str[2] = 't';
            break;
        case 0x11:
            date_str[0] = 'N';
            date_str[1] = 'o';
            date_str[2] = 'v';
            break;
        case 0x12:
            date_str[0] = 'D';
            date_str[1] = 'e';
            date_str[2] = 'c';
            break;
    }

    date_str[3] = ' ';
    date_str[6] = ',';
    date_str[7] = ' ';
    date_str[8] = '2';
    date_str[9] = '0';

    date_str[4] = (t->day >> 4) + '0';
    date_str[5] = (t->day & 0xF) + '0';

    date_str[10] = (t->yr >> 4) + '0';
    date_str[11] = (t->yr & 0xF) + '0';
    return date_str;
};

/*******************************************************************************************/
char *
RTC_Convert_BCD_Time_to_String(BCD_RTCC * t)
{
    switch (t->wkd)
    {
        default:
        case 0x00:
            time_str[0] = 'S';
            time_str[1] = 'u';
            time_str[2] = 'n';
            break;
        case 0x01:
            time_str[0] = 'M';
            time_str[1] = 'o';
            time_str[2] = 'n';
            break;
        case 0x02:
            time_str[0] = 'T';
            time_str[1] = 'u';
            time_str[2] = 'e';
            break;
        case 0x03:
            time_str[0] = 'W';
            time_str[1] = 'e';
            time_str[2] = 'd';
            break;
        case 0x04:
            time_str[0] = 'T';
            time_str[1] = 'h';
            time_str[2] = 'u';
            break;
        case 0x05:
            time_str[0] = 'F';
            time_str[1] = 'r';
            time_str[2] = 'i';
            break;
        case 0x06:
            time_str[0] = 'S';
            time_str[1] = 'a';
            time_str[2] = 't';
            break;
    }

    time_str[3] = ' ';
    time_str[6] = ':';
    time_str[9] = ':';

    time_str[4] = (t->hr >> 4) + '0';
    time_str[5] = (t->hr & 0xF) + '0';

    time_str[7] = (t->min >> 4) + '0';
    time_str[8] = (t->min & 0xF) + '0';

    time_str[10] = (t->sec >> 4) + '0';
    time_str[11] = (t->sec & 0xF) + '0';

    time_str[12] = ' ';
    time_str[13] = 'G';
    time_str[14] = 'M';
    time_str[15] = 'T';

    return time_str;

}


/*****************************************************************************
 * Function: RTCCCalculateWeekDay
 *
 * Preconditions: Valid values of day, month and year must be presented in
 * _time_chk structure.
 *
 * Overview: The function reads day, month and year from _time_chk and
 * calculates week day. Than It writes result into _time_chk. To write
 * the structure into clock RTCCSet must be called.
 *
 * Input: _time_chk with valid values of day, month and year.
 *
 * Output: Zero based week day in bcd form
 *
 *****************************************************************************/
void
RTC_CalculateWeekDay( BCD_RTCC *t)  // Calculate the day of the week for century 2000
{
    const char MonthOffset[] =
            //jan feb mar apr may jun jul aug sep oct nov dec
    {0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5};
    unsigned Year;
    unsigned Month;
    unsigned Day;
    unsigned Offset;
    // calculate week day
    Year = mRTCCbcd2bin(t->yr);
    Month = mRTCCbcd2bin(t->mth);
    Day = mRTCCbcd2bin(t->day);

    // 2000s century offset = 6 +
    // every year 365%7 = 1 day shift +
    // every leap year adds 1 day
    Offset = 6 + Year + Year / 4;
    // Add month offset from table
    Offset += MonthOffset[Month - 1];
    // Add day
    Offset += Day;

    // If it's a leap year and before March there's no additional day yet
    if ((Year % 4) == 0)
        if (Month < 3)
            Offset -= 1;

    // Week day is
    Offset %= 7;
    t->wkd = mRTCCbin2bcd(Offset);
}


 /*****************************************************************************/
void RTC_Set_BCD_time( BCD_RTCC * t)        // RTC BCD time structure
{
    RTC_CalculateWeekDay( t );
    RTC_Unlock(); // Unlock the RTCC so we can write
    RCFGCALbits.RTCEN = 0; // Stop the clock from running should it be running already
    // Set the time
    _RTCPTR = 3;
    RTCVAL = t->prt11;
    RTCVAL = t->prt10;
    RTCVAL = t->prt01;
    RTCVAL = t->prt00;

    RCFGCALbits.RTCEN = 1; // Start the clock to run

    RTC_Lock(); // Lock the RTCC from beeing written

}

