/* 
 * File:   App_cfg.h
 * Author: gary
 *
 * Created on September 27, 2012, 11:25 AM
 */

#ifndef APP_CFG_H
#define	APP_CFG_H
#include "TCPIP Stack/TCPIP.h"
#ifdef	__cplusplus
extern "C" {
#endif

// Define a header structure for validating the AppConfig data structure in EEPROM/Flash
typedef struct
{
	unsigned short wConfigurationLength;	// Number of bytes saved in EEPROM/Flash (sizeof(APP_CONFIG))
	unsigned short wOriginalChecksum;	// Checksum of the original AppConfig defaults as loaded from ROM (to detect when to wipe the EEPROM/Flash record of AppConfig due to a stack change, such as when switching from Ethernet to Wi-Fi)
	unsigned short wCurrentChecksum;	// Checksum of the current EEPROM/Flash data.  This protects against using corrupt values if power failure occurs while writing them and helps detect coding errors in which some other task writes to the EEPROM in the AppConfig area.
} NVM_VALIDATION_STRUCT;

extern APP_CONFIG AppConfig;

extern void InvalidateAppConfig( void);
extern void InitAppConfig(void) ;
extern void SaveAppConfig(const APP_CONFIG *ptrAppConfig) ;

#ifdef	__cplusplus
}
#endif

#endif	/* APP_CFG_H */

