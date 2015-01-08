/*
 * File:  Main.h
 * Author: gary
 *
 * Created on September 27, 2012, 11:25 AM
 */
#ifndef _MAINDEMO_H
#define _MAINDEMO_H


void DoUARTConfig(void);


// An actual function defined in MainDemo.c for displaying the current IP 
// address on the UART and/or LCD.
void DisplayIPValue(IP_ADDR IPVal);

// Reporting Soil moisture under the solar check mark for now
// #define using_Solar_for_soil_wetness
#endif // _MAINDEMO_H
