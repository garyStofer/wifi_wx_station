#ifndef TCPIPCONFIG_STUB_H
#define TCPIPCONFIG_STUB_H

// These definitions are set in the MPLAB Project settings.  If you are starting
// a new project, you should start by modifying one of the pre-existing .mcp 
// files.  To modify the macro used, in MPLAB IDE, click on Project -> Build 
// Options... -> Project -> MPLAB XXX C Compiler -> Preprocessor Macros -> 
// Add.... Note that you may also have to add this macro to the assembler 
// (MPLAB XXX Assembler tab).
#if		defined(CFG_INCLUDE_PICDN2_ETH97)
			#if defined(CFG_INCLUDE_TCP_200_PERF)
				#include "Configs/TCPIP ETH97 TCP_200_PERF.h"
			#elif defined(CFG_INCLUDE_TCP_2000_PERF)
				#include "Configs/TCPIP ETH97 TCP_2000_PERF.h"
			#elif defined(CFG_INCLUDE_UDP_PERF)
				#include "Configs/TCPIP ETH97 UDP_PERF.h"
			#else
				#include "Configs/TCPIP ETH97.h"
			#endif
#elif	defined(CFG_INCLUDE_PICDN2_ENC28) || \
		defined(CFG_INCLUDE_PIC18EX_ENC28) || \
		defined(CFG_INCLUDE_EX16_ENC28)
			#if defined(CFG_INCLUDE_TCP_200_PERF)
				#include "Configs/TCPIP ENC28 TCP_200_PERF.h"
			#elif defined(CFG_INCLUDE_TCP_2000_PERF)
				#include "Configs/TCPIP ENC28 TCP_2000_PERF.h"
			#elif defined(CFG_INCLUDE_UDP_PERF)
				#include "Configs/TCPIP ENC28 UDP_PERF.h"
			#else
				#include "Configs/TCPIP ENC28.h"
			#endif
#elif	defined(CFG_INCLUDE_PICDN2_ENC624) || \
		defined(CFG_INCLUDE_PIC18EX_ENC624) || \
		defined(CFG_INCLUDE_EX16_ENC624) || \
		defined(CFG_INCLUDE_EX16_ENC624_PSP5_I) || \
		defined(CFG_INCLUDE_EX16_ENC624_PSP5_IB) || \
		defined(CFG_INCLUDE_EX16_ENC624_PSP9)
			#if defined(CFG_INCLUDE_TCP_200_PERF)
				#include "Configs/TCPIP ENC624 TCP_200_PERF.h"
			#elif defined(CFG_INCLUDE_TCP_2000_PERF)
				#include "Configs/TCPIP ENC624 TCP_2000_PERF.h"
			#elif defined(CFG_INCLUDE_TCP_8000_PERF)
				#include "Configs/TCPIP ENC624 TCP_8000_PERF.h"
			#elif defined(CFG_INCLUDE_UDP_PERF)
				#include "Configs/TCPIP ENC624 UDP_PERF.h"
			#else
				#include "Configs/TCPIP ENC624.h"
			#endif
#elif	defined(CFG_INCLUDE_PICDN2_MRF24WB) || defined(CFG_INCLUDE_PICDN2_MRF24WG)           || \
		defined(CFG_INCLUDE_PIC18EX_MRF24WB) || defined(CFG_INCLUDE_PIC18EX_MRF24WG) || \
		defined(CFG_INCLUDE_EX16_MRF24WB) || defined(CFG_INCLUDE_EX16_MRF24WG) ||\
                defined(CFG_INCLUDE_WX_WUNDER)
			#if defined(CFG_INCLUDE_TCP_200_PERF)
				#include "Configs/TCPIP MRF24W TCP_200_PERF.h"
			#elif defined(CFG_INCLUDE_TCP_2000_PERF)
				#include "Configs/TCPIP MRF24W TCP_2000_PERF.h"
			#elif defined(CFG_INCLUDE_TCP_8000_PERF)
				#include "Configs/TCPIP MRF24W TCP_8000_PERF.h"
			#elif defined(CFG_INCLUDE_UDP_PERF)
				#include "Configs/TCPIP MRF24W UDP_PERF.h"
			#else
				#include "Configs/TCPIP MRF24W.h"
			#endif
#elif	defined(CFG_INCLUDE_DA210_BRD_ENC28)
			#include "Configs/TCPIP ENC28 DA210_BRD.h"
#elif	defined(CFG_INCLUDE_DA210_BRD_ENC624) || \
		defined(CFG_INCLUDE_DA210_BRD_ENC624_PSP5_IB)
			#include "Configs/TCPIP ENC624 DA210_BRD.h"
#elif	defined(CFG_INCLUDE_DA210_BRD_MRF24WB) || defined(CFG_INCLUDE_DA210_BRD_MRF24WG)
			#include "Configs/TCPIP MRF24W DA210_BRD.h"
#elif	defined(CFG_INCLUDE_PIC32_ETH_SK_ETH795)
			#if defined(CFG_INCLUDE_TCP_200_PERF)
				#include "Configs/TCPIP ETH795 TCP_200_PERF.h"
			#elif defined(CFG_INCLUDE_TCP_2000_PERF)
				#include "Configs/TCPIP ETH795 TCP_2000_PERF.h"
			#elif defined(CFG_INCLUDE_TCP_8000_PERF)
				#include "Configs/TCPIP ETH795 TCP_8000_PERF.h"
			#elif defined(CFG_INCLUDE_UDP_PERF)
				#include "Configs/TCPIP ETH795 UDP_PERF.h"
			#else
				#include "Configs/TCPIP ETH795.h"
			#endif
#elif	defined(CFG_INCLUDE_PIC32_GP_SK_ENC28) || \
		defined(CFG_INCLUDE_PIC32_USB_SK_ENC28)
			#include "Configs/TCPIP ENC28 PIC32_SK.h"
#elif	defined(CFG_INCLUDE_PIC32_GP_SK_ENC624) || \
		defined(CFG_INCLUDE_PIC32_GP_SK_ENC624_PSP5_I) || \
		defined(CFG_INCLUDE_PIC32_GP_SK_ENC624_PSP9) || \
		defined(CFG_INCLUDE_PIC32_USB_SK_ENC624) || \
		defined(CFG_INCLUDE_PIC32_USB_SK_ENC624_PSP5_I) || \
		defined(CFG_INCLUDE_PIC32_USB_SK_ENC624_PSP9)
			#include "Configs/TCPIP ENC624 PIC32_SK.h"
#elif	defined(CFG_INCLUDE_PIC32_GP_SK_MRF24WB) || defined(CFG_INCLUDE_PIC32_GP_SK_MRF24WG) || \
		defined(CFG_INCLUDE_PIC32_USB_SK_MRF24WB) || defined(CFG_INCLUDE_PIC32_USB_SK_MRF24WG)
			#include "Configs/TCPIP MRF24W PIC32_SK.h"
#elif   defined(CFG_INCLUDE_DSPIC33E_SK_ENC624)||\
		defined(CFG_INCLUDE_DSPIC33E_SK_ENC624_PSP5_I)
			#include "Configs/TCPIP ENC624 dsPIC33E_SK.h"
#elif   defined(CFG_INCLUDE_DSPIC33E_SK_MRF24WB) || defined(CFG_INCLUDE_DSPIC33E_SK_MRF24WG)
			#include "Configs/TCPIP MRF24W dsPIC33E_SK.h"
#else
			#error Missing project macro definition to select proper TCPIPConfig.h
#endif


#endif
