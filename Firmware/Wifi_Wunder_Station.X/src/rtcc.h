
#ifndef RTCC_H
#define RTCC_H

#define mRTCCbcd2bin(bcd) (10*(bcd>>4)+(bcd&0x0f))
#define mRTCCbin2bcd(bin) (((bin/10)<<4)|(bin%10))

// Union to access rtcc registers
// Note: all RTCC registers are in BCD format I.e the 18th hour is expressed as 0x18
//       Year is based on year 2000
typedef union tagRTCC
{
    struct{
            unsigned char sec;
            unsigned char min;
            unsigned char hr;
            unsigned char wkd;
            unsigned char day;
            unsigned char mth;
            unsigned char yr;
            unsigned char nil;
    };
    struct {
            unsigned int prt00;
            unsigned int prt01;
            unsigned int prt10;
            unsigned int prt11;
    };
} BCD_RTCC;

extern BCD_RTCC _RTC_time;

extern void RTC_Init(void);    // configures the oscialltor to clock the RTC


extern BCD_RTCC * RTC_Read_BCD_Time(void); // reads RTC and stores BCD time in global _RTC_time
extern char * RTC_Convert_BCD_Date_to_String (BCD_RTCC * t);
extern char * RTC_Convert_BCD_Timer_to_String(BCD_RTCC * t);
extern void RTC_CalculateWeekDay( BCD_RTCC *t);  // Calculate the day of the week for century 2000
extern void RTC_Set_BCD_time( BCD_RTCC * t);        // RTC BCD time structure



#endif
