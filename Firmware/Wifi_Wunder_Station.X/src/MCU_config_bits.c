#include "Compiler.h"
#include <p24Fxxxx.h>

#if defined(__PIC24FJ128GA008__)
 int CONFIG2 __attribute__((space(prog), address(0x157FC))) = 0xF9DF ;
//_CONFIG2(
//    POSCMOD_NONE &       // Primary Oscillator Select (Primary oscillator disabled)
//    OSCIOFNC_ON &        // Primary Oscillator Output Function (OSC2/CLKO/RC15 functions as port I/O (RC15))
//    FCKSM_CSDCMD &       // Clock Switching and Monitor (Clock switching and Fail-Safe Clock Monitor are disabled)
//    FNOSC_FRCPLL &       // Oscillator Select (Fast RC Oscillator with PLL module (FRCPLL))
//    IESO_ON              // Internal External Switch Over Mode (IESO mode (Two-Speed Start-up) enabled)
//);
 int CONFIG1 __attribute__((space(prog), address(0x157FE))) = 0x3F7F ;
//_CONFIG1(
//    WDTPS_PS32768 &      // Watchdog Timer Postscaler (1:32,768)
//    FWPSA_PR128 &        // WDT Prescaler (Prescaler ratio of 1:128)
//    WINDIS_ON &          // Watchdog Timer Window (Standard Watchdog Timer enabled,(Windowed-mode is disabled))
//    FWDTEN_OFF &         // Watchdog Timer Enable (Watchdog Timer is disabled)
//    ICS_PGx2 &           // Comm Channel Select (Emulator/debugger uses EMUC2/EMUD2)
//    GWRP_OFF &           // General Code Segment Write Protect (Writes to program memory are allowed)
//    GCP_OFF &            // General Code Segment Code Protect (Code protection is disabled)
//    JTAGEN_OFF           // JTAG Port Enable (JTAG port is disabled)
//);
 #elif defined(__PIC24FJ256GA108__)
// PIC24FJ256GA108 Configuration Bit Settings
 int CONFIG3 __attribute__((space(prog), address(0x2ABFA))) = 0xFFFF ;
//_CONFIG3(
//    WPFP_WPFP511 &       // Write Protection Flash Page Segment Boundary (Highest Page (same as page 170))
//    WPDIS_WPDIS &        // Segment Write Protection Disable bit (Segmented code protection disabled)
//    WPCFG_WPCFGDIS &     // Configuration Word Code Page Protection Select bit (Last page(at the top of program memory) and Flash configuration words are not protected)
//    WPEND_WPENDMEM       // Segment Write Protection End Page Select bit (Write Protect from WPFP to the last page of memory)
//);
 int CONFIG2 __attribute__((space(prog), address(0x2ABFC))) = 0xF11F ;
//_CONFIG2(
//    POSCMOD_NONE &       // Primary Oscillator Select (Primary oscillator disabled)
//    IOL1WAY_ON &         // IOLOCK One-Way Set Enable bit (Write RP Registers Once)
//    OSCIOFNC_ON &        // Primary Oscillator Output Function (OSCO functions as port I/O (RC15))
//    FCKSM_CSECME &       // Clock Switching and Monitor (Both Clock switching and Fail-safe Clock Monitor are enabled)
//    FNOSC_FRCPLL &       // Oscillator Select (Fast RC oscillator with Postscaler and PLL module (FRCPLL))
//    IESO_ON              // Internal External Switch Over Mode (IESO mode (Two-speed start-up) enabled)
//);
 int CONFIG1 __attribute__((space(prog), address(0x2ABFE))) = 0x3E7F ;
//_CONFIG1(
//    WDTPS_PS32768 &      // Watchdog Timer Postscaler (1:32,768)
//    FWPSA_PR128 &        // WDT Prescaler (Prescaler ratio of 1:128)
//    WINDIS_OFF &         // Watchdog Timer Window (Standard Watchdog Timer is enabled,(Windowed-mode is disabled))
//    FWDTEN_OFF &         // Watchdog Timer Enable (Watchdog Timer is disabled)
//    ICS_PGx2 &           // Comm Channel Select (Emulator functions are shared with PGEC2/PGED2)
//    GWRP_OFF &           // General Code Segment Write Protect (Writes to program memory are allowed)
//    GCP_OFF &            // General Code Segment Code Protect (Code protection is disabled)
//    JTAGEN_OFF           // JTAG Port Enable (JTAG port is disabled)
//);


        #else
            #error "Wrong MCU architecture for product"
	#endif

