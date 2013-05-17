/********************************************************************
*
* PIC24F Serial Bootloader
*
*********************************************************************
* FileName:		boot.c
* Dependencies: memory.c, config.h, GenericTypeDefs.h 
* Processor:	PIC24F Family
* Compiler:		C30 v3.00 or later
* Company:		Microchip Technology, Inc.
*
* Software License Agreement:
*
* The software supplied herewith by Microchip Technology Incorporated
* (the “Company”) for its PICmicro® Microcontroller is intended and
* supplied to you, the Company’s customer, for use solely and
* exclusively on Microchip PICmicro Microcontroller products. The
* software is owned by the Company and/or its supplier, and is
* protected under applicable copyright laws. All rights are reserved.
* Any use in violation of the foregoing restrictions may subject the
* user to criminal sanctions under applicable laws, as well as to
* civil liability for the breach of the terms and conditions of this
* license.
*
* THIS SOFTWARE IS PROVIDED IN AN “AS IS” CONDITION. NO WARRANTIES,
* WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
* TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FrOR A
* PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
* IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
* CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
*
* 
* File Description:
*
* Bootloader for PIC24F devices compatable with AN851 communication protocol
* Based on PIC24F UART bootloader and PIC16/18 AN851 bootloader
*
*
* Change History:
*
* Author      	Revision #      Date        Comment
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* Brant Ivey	1.00   			1-17-2008	Initial release of AN1157
* Brant Ivey    1.02            11-17-2008  Updated 'K' device support
*                                           Added extra configuration options
********************************************************************/

//Includes *******************************
#include "config.h"
//****************************************


//Globals ********************************
WORD responseBytes;		//number of bytes in command response
DWORD_VAL sourceAddr;	//general purpose address variable
DWORD_VAL userReset;	//user code reset vector
DWORD_VAL userTimeout; 	//bootloader entry timeout value
WORD userResetRead;		//bool - for relocating user reset vector

//Variables for storing runaway code protection keys
#ifdef USE_RUNAWAY_PROTECT
volatile WORD writeKey1 = 0xFFFF;
volatile WORD writeKey2 = 0x5555;
volatile WORD keyTest1 = 0x0000;
volatile WORD keyTest2 = 0xAAAA;
#endif

//Transmit/Recieve Buffer
BYTE buffer[MAX_PACKET_SIZE+1];
//****************************************

//Configuration bits *********************
/*
*	These configuration settings are not required for proper 
*	bootloader operation and can be modified as desired.  
*
*	Refer to AN1157 troubleshooting for configuration suggestions
*/
#ifndef DEV_HAS_CONFIG_BITS
    #ifdef DEV_HAS_USB
    _CONFIG1(JTAGEN_OFF & GWRP_OFF & ICS_PGx2 & FWDTEN_OFF)
    _CONFIG2(POSCMOD_HS & FNOSC_PRIPLL & PLLDIV_DIV2 & PLL_96MHZ_ON)
    #else
    _CONFIG1(JTAGEN_OFF & GWRP_OFF & ICS_PGx2 & FWDTEN_OFF)
    _CONFIG2(POSCMOD_NONE & FNOSC_PRIPLL)
    #endif
#else
    _FOSCSEL(FNOSC_PRIPLL)
    _FOSC(POSCFREQ_MS & POSCMOD_XT)
    _FWDT(FWDTEN_OFF)
    _FICD(ICS_PGx3)
#endif
//****************************************


/********************************************************************
* Function: 	int main()
*
* Precondition: None.
*
* Input: 		None.
*
* Output:		None.
*
* Side Effects:	Enables 32-bit Timer2/3.  Enables UART.
*
* Overview: 	Initialization of program and main loop.
*			
* Note:		 	None.
********************************************************************/
int main()
{
	DWORD_VAL delay;

	//Setup bootloader entry delay
	sourceAddr.Val = DELAY_TIME_ADDR;	//bootloader timer address
	delay.Val = ReadLatch(sourceAddr.word.HW, sourceAddr.word.LW); //read BL timeout
	
	//Setup user reset vector
	sourceAddr.Val = USER_PROG_RESET;
	userReset.Val = ReadLatch(sourceAddr.word.HW, sourceAddr.word.LW);

	//Prevent bootloader lockout - if no user reset vector, reset to BL start
	if(userReset.Val == 0xFFFFFF){
		userReset.Val = BOOT_ADDR_LOW;	
	}
	userResetRead = 0;


	//If timeout is zero, check reset state.
	if(delay.v[0] == 0){

		//If device is returning from reset, BL is disabled call user code
		//otherwise assume the BL was called from use code and enter BL
		if(RCON & 0xFED3){
			//If bootloader disabled, go to user code
			ResetDevice(userReset.Val); 
		}else{
			delay.Val = 0xFF;
		}
	}


	T2CONbits.TON = 0;
	T2CONbits.T32 = 1; // Setup Timer 2/3 as 32 bit timer incrementing every clock
	IFS0bits.T3IF = 0; // Clear the Timer3 Interrupt Flag 
	IEC0bits.T3IE = 0; // Disable Timer3 Interrupt Service Routine 

	//Enable timer if not in always-BL mode
	if((delay.Val & 0x000000FF) != 0xFF){
		//Convert seconds into timer count value 
		delay.Val = ((DWORD)(FCY)) * ((DWORD)(delay.v[0])); 

		PR3 = delay.word.HW; //setup timer timeout value
		PR2 = delay.word.LW;

		TMR2 = 0;
		TMR3 = 0;
		T2CONbits.TON=1;  //enable timer
	}


	//If using a part with PPS, map the UART I/O
	#ifdef DEV_HAS_PPS
		ioMap();
	#endif

	
	//Configure UART pins to be digital I/O.
	#ifdef UTX_ANA
		UTX_ANA = 1;
	#endif
	#ifdef URX_ANA
		URX_ANA = 1;
	#endif


	// SETUP UART COMMS: No parity, one stop bit, autobaud, polled
	UxMODEbits.UARTEN = 1;		//enable uart
    #ifdef USE_AUTOBAUD
	    UxMODEbits.ABAUD = 1;		//use autobaud
    #else
        UxBRG = BAUDRATEREG;
    #endif
	#ifdef USE_HI_SPEED_BRG
		UxMODEbits.BRGH = 1;	//use high speed mode
	#endif
	UxSTA = 0x0400;  //Enable TX

	while(1){

		#ifdef USE_RUNAWAY_PROTECT
			writeKey1 = 0xFFFF;	// Modify keys to ensure proper program flow
			writeKey2 = 0x5555;
		#endif

		GetCommand();		//Get full AN851 command from UART

		#ifdef USE_RUNAWAY_PROTECT
			writeKey1 += 10;	// Modify keys to ensure proper program flow
			writeKey2 += 42;
		#endif

		HandleCommand();	//Handle the command

		PutResponse(responseBytes);		//Respond to sent command

	}//end while(1)

}//end main(void)




/********************************************************************
* Function: 	void GetCommand()
*
* Precondition: UART Setup
*
* Input: 		None.
*
* Output:		None.
*
* Side Effects:	None.
*
* Overview: 	Polls the UART to recieve a complete AN851 command.
*			 	Fills buffer[1024] with recieved data.
*			
* Note:		 	None.
********************************************************************/
void GetCommand(){

	BYTE RXByte;
	BYTE checksum;
	WORD dataCount;

	while(1){

#ifndef USE_AUTOBAUD
        GetChar(&RXByte);   //Get first STX
        if(RXByte == STX){ 
#else
        AutoBaud();			//Get first STX and calculate baud rate
		RXByte = UxRXREG;	//Dummy read
#endif

		T2CONbits.TON = 0;  //disable timer - data received

		GetChar(&RXByte);	//Read second byte
		if(RXByte == STX){	//2 STX, beginning of data
		
			checksum = 0;	//reset data and checksum
			dataCount = 0;

			while(dataCount <= MAX_PACKET_SIZE+1){	//maximum num bytes
				GetChar(&RXByte);		
				switch(RXByte){   
					case STX: 			//Start over if STX
						checksum = 0;
						dataCount = 0;
						break;

					case ETX:			//End of packet if ETX
						checksum = ~checksum +1; //test checksum
						Nop();
						if(checksum == 0) return;	//return if OK
						dataCount = 0xFFFF;	//otherwise restart
						break;

					case DLE:			//If DLE, treat next as data
						GetChar(&RXByte);
					default:			//get data, put in buffer
						checksum += RXByte;
						buffer[dataCount++] = RXByte;
						break;

				}//end switch(RXByte)
			}//end while(byteCount <= 1024)
		}//end if(RXByte == STX)

        #ifndef USE_AUTOBAUD
        }//end if(RXByte == STX)
        #endif
	}//end while(1)				
		
}//end GetCommand()




/********************************************************************
* Function: 	void HandleCommand()
*
* Precondition: data in buffer
*
* Input: 		None.
*
* Output:		None.
*
* Side Effects:	None.
*
* Overview: 	Handles commands received from host
*			
* Note:		 	None.
********************************************************************/
void HandleCommand()
{
	
	BYTE Command;
	BYTE length;

	//variables used in EE and CONFIG read/writes
	#if (defined(DEV_HAS_EEPROM) || defined(DEV_HAS_CONFIG_BITS))	
		WORD i=0;
		WORD_VAL temp;
		WORD bytesRead = 0;	
	#endif

	Command = buffer[0];	//get command from buffer
	length = buffer[1];		//get data length from buffer

	//RESET Command
	if(length == 0x00){
        UxMODEbits.UARTEN = 0;  //Disable UART
		ResetDevice(userReset.Val);
	}

	//get 24-bit address from buffer
	sourceAddr.v[0] = buffer[2];		
	sourceAddr.v[1] = buffer[3];
	sourceAddr.v[2] = buffer[4];
	sourceAddr.v[3] = 0;

	#ifdef USE_RUNAWAY_PROTECT
	writeKey1 |= (WORD)sourceAddr.Val;	// Modify keys to ensure proper program flow
	writeKey2 =  writeKey2 << 1;
	#endif

	//Handle Commands		
	switch(Command)
	{
		case RD_VER:						//Read version	
			buffer[2] = MINOR_VERSION;
			buffer[3] = MAJOR_VERSION;

			responseBytes = 4; //set length of reply
			break;
		
		case RD_FLASH:						//Read flash memory
			ReadPM(length, sourceAddr); 

				responseBytes = length*PM_INSTR_SIZE + 5; //set length of reply    									  
			break;
		
		case WT_FLASH:						//Write flash memory

			#ifdef USE_RUNAWAY_PROTECT
				writeKey1 -= length;	// Modify keys to ensure proper program flow
				writeKey2 += Command;		
			#endif

			WritePM(length, sourceAddr);	

			responseBytes = 1; //set length of reply
 			break;

		case ER_FLASH:						//Erase flash memory

			#ifdef USE_RUNAWAY_PROTECT
				writeKey1 += length;	// Modify keys to ensure proper program flow
				writeKey2 -= Command;
			#endif

			ErasePM(length, sourceAddr);	

			responseBytes = 1; //set length of reply
			break;
	
		#ifdef DEV_HAS_EEPROM
		case RD_EEDATA:						//Read EEPROM
			//if device has onboard EEPROM, allow EE reads

			//Read length words of EEPROM
			while(i < length*2){
				temp.Val = ReadLatch(sourceAddr.word.HW, 
									 sourceAddr.word.LW);
				buffer[5+i++] = temp.v[0];
				buffer[5+i++] = temp.v[1];
				sourceAddr.Val += 2;
			}

			responseBytes = length*2 + 5; //set length of reply
			break;
		
		case WT_EEDATA:						//Write EEPROM
        
			#ifdef USE_RUNAWAY_PROTECT
				writeKey1 -= length;	// Modify keys to ensure proper program flow
				writeKey2 += Command;		
			#endif
            
			//Write length words of EEPROM
			while(i < length*2){
				temp.byte.LB = buffer[5+i++];  //load data to write
				temp.byte.HB = buffer[5+i++];
	
				WriteLatch(sourceAddr.word.HW,sourceAddr.word.LW,
						   0, temp.Val);  //write data to latch

				#ifdef USE_RUNAWAY_PROTECT
					writeKey1++;
					writeKey2--;

					//setup program flow protection test keys
					keyTest1 =	(((0x0009 | (WORD)(sourceAddr.Val-i)) -
								length) + i/2) - 5;
					keyTest2 =  (((0x557F << 1) + WT_EEDATA) - i/2) + 6;

					//initiate write sequence
					WriteMem(EE_WORD_WRITE);

					writeKey1 += 5; // Modify keys to ensure proper program flow
					writeKey2 -= 6;	
				#else
					//initiate write sequence bypasssing runaway protection
					WriteMem(EE_WORD_WRITE);  
				#endif
				
				sourceAddr.Val +=2;
			}
			

			responseBytes = 1; //set length of reply
			break;
		#endif

		#ifdef DEV_HAS_CONFIG_BITS
		case RD_CONFIG:						//Read config memory

			//Read length bytes from config memory
			while(bytesRead < length)
			{
				//read flash
				temp.Val = ReadLatch(sourceAddr.word.HW, sourceAddr.word.LW);

				buffer[bytesRead+5] = temp.v[0];   	//put read data onto buffer
		
				bytesRead++; 

				sourceAddr.Val += 2;  //increment addr by 2
			}

			responseBytes = length + 5;

			break;
		case WT_CONFIG:						//Write Config mem

            //Write length  bytes of config memory
			while(i < length){
				temp.byte.LB = buffer[5+i++];  //load data to write
				temp.byte.HB = 0;
    
				#ifdef USE_RUNAWAY_PROTECT
   					writeKey1++;
   					writeKey2--;
                #endif
        	
                //Make sure that config write is inside implemented configuration space
                if(sourceAddr.Val >= CONFIG_START && sourceAddr.Val <= CONFIG_END)
                {
				
                    TBLPAG = sourceAddr.byte.UB;
                    __builtin_tblwtl(sourceAddr.word.LW,temp.Val);
    			
                    #ifdef USE_RUNAWAY_PROTECT
    					//setup program flow protection test keys
    					keyTest1 =	(((0x0009 | (WORD)(sourceAddr.Val-i*2)) -
    								length) + i) - 5;
    					keyTest2 =  (((0x557F << 1) + WT_CONFIG) - i) + 6;
    
    					//initiate write sequence
    					WriteMem(CONFIG_WORD_WRITE);
    
    					writeKey1 += 5; // Modify keys to ensure proper program flow
    					writeKey2 -= 6;	
    				#else
    					//initiate write sequence bypasssing runaway protection
    					WriteMem(CONFIG_WORD_WRITE);  
    				#endif

                }//end if(sourceAddr.Val...)

				sourceAddr.Val +=2;
			}//end while(i < length)

			responseBytes = 1; //set length of reply
			break;
		#endif
		case VERIFY_OK:

			#ifdef USE_RUNAWAY_PROTECT
				writeKey1 -= 1;		// Modify keys to ensure proper program flow
				writeKey2 += Command;		
			#endif

			WriteTimeout();
		
			responseBytes = 1; //set length of reply
			break;

		default:
			break;
	}// end switch(Command)
}//end HandleCommand()




/********************************************************************
* Function: 	void PutResponse()
*
* Precondition: UART Setup, data in buffer
*
* Input: 		None.
*
* Output:		None.
*
* Side Effects:	None.
*
* Overview: 	Transmits responseBytes bytes of data from buffer 
				with UART as a response to received command.
*
* Note:		 	None.
********************************************************************/
void PutResponse(WORD responseLen)
{
	WORD i;
	BYTE data;
	BYTE checksum;

	UxSTAbits.UTXEN = 1;	//make sure TX is enabled

	PutChar(STX);			//Put 2 STX characters
	PutChar(STX);

	//Output buffer as response packet
	checksum = 0;
	for(i = 0; i < responseLen; i++){
		asm("clrwdt");		//looping code so clear WDT

		data = buffer[i];	//get data from response buffer
		checksum += data;	//accumulate checksum

		//if control character, stuff DLE
		if(data == STX || data == ETX || data == DLE){
			PutChar(DLE);
		}

		PutChar(data);  	//send data
	}

	checksum = ~checksum + 1;	//keep track of checksum

	//if control character, stuff DLE
	if(checksum == STX || checksum == ETX || checksum == DLE){
		PutChar(DLE);
	}

	PutChar(checksum);		//put checksum
	PutChar(ETX);			//put End of text

	while(!UxSTAbits.TRMT);	//wait for transmit to finish
}//end PutResponse()




/********************************************************************
* Function: 	void PutChar(BYTE Char)
*
* Precondition: UART Setup
*
* Input: 		Char - Character to transmit
*
* Output: 		None
*
* Side Effects:	Puts character into destination pointed to by ptrChar.
*
* Overview: 	Transmits a character on UART2. 
*	 			Waits for an empty spot in TXREG FIFO.
*
* Note:		 	None
********************************************************************/
void PutChar(BYTE txChar)
{
	while(UxSTAbits.UTXBF);	//wait for FIFO space
	UxTXREG = txChar;	//put character onto UART FIFO to transmit
}//end PutChar(BYTE Char)




/********************************************************************
* Function:        void GetChar(BYTE * ptrChar)
*
* PreCondition:    UART Setup
*
* Input:		ptrChar - pointer to character received
*
* Output:		
*
* Side Effects:	Puts character into destination pointed to by ptrChar.
*				Clear WDT
*
* Overview:		Receives a character from UART2.  
*
* Note:			None
********************************************************************/
void GetChar(BYTE * ptrChar)
{
	BYTE dummy;
	while(1)
	{	
		asm("clrwdt");					//looping code, so clear WDT
	
		//check for receive errors
		if((UxSTA & 0x000E) != 0x0000)
		{
			dummy = UxRXREG; 			//dummy read to clear FERR/PERR
			UxSTAbits.OERR = 0;			//clear OERR to keep receiving
		}

		//get the data
		if(UxSTAbits.URXDA == 1)
		{
			* ptrChar = UxRXREG;		//get data from UART RX FIFO
			break;
		}

        #ifndef USE_AUTOBAUD
		//if timer expired, jump to user code
		if(IFS0bits.T3IF == 1){
			ResetDevice(userReset.Val);
		}
        #endif
	}//end while(1)
}//end GetChar(BYTE *ptrChar)




/********************************************************************
* Function:     void ReadPM(WORD length, DWORD_VAL sourceAddr)
*
* PreCondition: None
*
* Input:		length		- number of instructions to read
*				sourceAddr 	- address to read from
*
* Output:		None
*
* Side Effects:	Puts read instructions into buffer.
*
* Overview:		Reads from program memory, stores data into buffer. 
*
* Note:			None
********************************************************************/
void ReadPM(WORD length, DWORD_VAL sourceAddr)
{
	WORD bytesRead = 0;
	DWORD_VAL temp;

	//Read length instructions from flash
	while(bytesRead < length*PM_INSTR_SIZE)
	{
		//read flash
		temp.Val = ReadLatch(sourceAddr.word.HW, sourceAddr.word.LW);

		buffer[bytesRead+5] = temp.v[0];   	//put read data onto 
		buffer[bytesRead+6] = temp.v[1];	//response buffer
		buffer[bytesRead+7] = temp.v[2];
		buffer[bytesRead+8] = temp.v[3];
	
		//4 bytes per instruction: low word, high byte, phantom byte
		bytesRead+=PM_INSTR_SIZE; 

		sourceAddr.Val = sourceAddr.Val + 2;  //increment addr by 2
	}//end while(bytesRead < length*PM_INSTR_SIZE)
}//end ReadPM(WORD length, DWORD_VAL sourceAddr)




/********************************************************************
* Function:     void WritePM(WORD length, DWORD_VAL sourceAddr)
*
* PreCondition: Page containing rows to write should be erased.
*
* Input:		length		- number of rows to write
*				sourceAddr 	- row aligned address to write to
*
* Output:		None.
*
* Side Effects:	None.
*
* Overview:		Writes number of rows indicated from buffer into
*				flash memory
*
* Note:			None
********************************************************************/
void WritePM(WORD length, DWORD_VAL sourceAddr)
{
	WORD bytesWritten;
	DWORD_VAL data;
	#ifdef USE_RUNAWAY_PROTECT
	WORD temp = (WORD)sourceAddr.Val;
	#endif

	bytesWritten = 0;	//first 5 buffer locations are cmd,len,addr	
	
	//write length rows to flash
	while((bytesWritten) < length*PM_ROW_SIZE)
	{
		asm("clrwdt");

		//get data to write from buffer
		data.v[0] = buffer[bytesWritten+5];
		data.v[1] = buffer[bytesWritten+6];
		data.v[2] = buffer[bytesWritten+7];
		data.v[3] = buffer[bytesWritten+8];

		//4 bytes per instruction: low word, high byte, phantom byte
		bytesWritten+=PM_INSTR_SIZE;

		//Flash configuration word handling
		#ifndef DEV_HAS_CONFIG_BITS
			//Mask of bit 15 of CW1 to ensure it is programmed as 0
			//as noted in PIC24FJ datasheets
			if(sourceAddr.Val == CONFIG_END){
				data.Val &= 0x007FFF;
			}
		#endif

		//Protect the bootloader & reset vector
		#ifdef USE_BOOT_PROTECT
			//protect BL reset & get user reset
			if(sourceAddr.Val == 0x0){
				//get user app reset vector lo word
				userReset.Val = data.Val & 0xFFFF;

				//program low word of BL reset
				data.Val = 0x040000 + (0xFFFF & BOOT_ADDR_LOW);

				userResetRead = 1;
			}
			if(sourceAddr.Val == 0x2){
				//get user app reset vector hi byte	
				userReset.Val += (DWORD)(data.Val & 0x00FF)<<16;			
			
				//program high byte of BL reset
				data.Val = ((DWORD)(BOOT_ADDR_LOW & 0xFF0000))>>16;

				userResetRead = 1;
			}
		#else
			//get user app reset vector lo word
			if(sourceAddr.Val == 0x0){
				userReset.Val = data.Val & 0xFFFF;					

				userResetRead = 1;
			}

			//get user app reset vector	hi byte
			if(sourceAddr.Val == 0x2) {
				userReset.Val |= ((DWORD)(data.Val & 0x00FF))<<16;	

				userResetRead = 1;
			}
		#endif


		//put information from reset vector in user reset vector location
		if(sourceAddr.Val == USER_PROG_RESET){
			if(userResetRead){  //has reset vector been grabbed from location 0x0?
				//if yes, use that reset vector
				data.Val = userReset.Val;	
			}else{
				//if no, use the user's indicated reset vector
				userReset.Val = data.Val;
			}
		}

		//If address is delay timer location, store data and write empty word
		if(sourceAddr.Val == DELAY_TIME_ADDR){
			userTimeout.Val = data.Val;
			data.Val = 0xFFFFFF;
		}
	
		#ifdef USE_BOOT_PROTECT			//do not erase bootloader & reset vector
			if(sourceAddr.Val < BOOT_ADDR_LOW || sourceAddr.Val > BOOT_ADDR_HI){
		#endif
		
		#ifdef USE_CONFIGWORD_PROTECT	//do not erase last page
			if(sourceAddr.Val < (CONFIG_START & 0xFFFC00)){
		#endif

		#ifdef USE_VECTOR_PROTECT		//do not erase first page
			//if(sourceAddr.Val >= PM_PAGE_SIZE/2){
			if(sourceAddr.Val >= VECTOR_SECTION){
		#endif
		


		//write data into latches
   		WriteLatch(sourceAddr.word.HW, sourceAddr.word.LW, 
					data.word.HW, data.word.LW);


		#ifdef USE_VECTOR_PROTECT	
			}//end vectors protect
		#endif

		#ifdef USE_CONFIGWORD_PROTECT
			}//end config protect
		#endif

		#ifdef USE_BOOT_PROTECT
			}//end bootloader protect
		#endif


		#ifdef USE_RUNAWAY_PROTECT
			writeKey1 += 4;			// Modify keys to ensure proper program flow
			writeKey2 -= 4;
		#endif


		//write to flash memory if complete row is finished
		if((bytesWritten % PM_ROW_SIZE) == 0)
		{

			#ifdef USE_RUNAWAY_PROTECT
				//setup program flow protection test keys
				keyTest1 =  (0x0009 | temp) - length + bytesWritten - 5;
				keyTest2 =  (((0x557F << 1) + WT_FLASH) - bytesWritten) + 6;
			#endif


			#ifdef USE_BOOT_PROTECT			//Protect the bootloader & reset vector
				if((sourceAddr.Val < BOOT_ADDR_LOW || sourceAddr.Val > BOOT_ADDR_HI)){
			#endif

			#ifdef USE_CONFIGWORD_PROTECT	//do not erase last page
				if(sourceAddr.Val < (CONFIG_START & 0xFFFC00)){
			#endif
	
			#ifdef USE_VECTOR_PROTECT		//do not erase first page
				if(sourceAddr.Val >= VECTOR_SECTION){
			#endif
	

			//execute write sequence
			WriteMem(PM_ROW_WRITE);	

			#ifdef USE_RUNAWAY_PROTECT
				writeKey1 += 5; // Modify keys to ensure proper program flow
				writeKey2 -= 6;
			#endif


			#ifdef USE_VECTOR_PROTECT	
				}//end vectors protect
			#endif
	
			#ifdef USE_CONFIGWORD_PROTECT
				}//end config protect
			#endif	

			#ifdef USE_BOOT_PROTECT
				}//end boot protect
			#endif

		}

		sourceAddr.Val = sourceAddr.Val + 2;  //increment addr by 2
	}//end while((bytesWritten-5) < length*PM_ROW_SIZE)
}//end WritePM(WORD length, DWORD_VAL sourceAddr)




/********************************************************************
* Function:     void ErasePM(WORD length, DWORD_VAL sourceAddr)
*
* PreCondition: 
*
* Input:		length		- number of pages to erase
*				sourceAddr 	- page aligned address to erase
*
* Output:		None.
*
* Side Effects:	None.
*
* Overview:		Erases number of pages from flash memory
*
* Note:			None
********************************************************************/
void ErasePM(WORD length, DWORD_VAL sourceAddr)
{
	WORD i=0;
	#ifdef USE_RUNAWAY_PROTECT
	WORD temp = (WORD)sourceAddr.Val;
	#endif

	while(i<length){

		i++;
	
		#ifdef USE_RUNAWAY_PROTECT
			writeKey1++;	// Modify keys to ensure proper program flow
			writeKey2--;
		#endif


		//if protection enabled, protect BL and reset vector
		#ifdef USE_BOOT_PROTECT		
			if(sourceAddr.Val < BOOT_ADDR_LOW ||	//do not erase bootloader
	   	   	   sourceAddr.Val > BOOT_ADDR_HI){
		#endif

		#ifdef USE_CONFIGWORD_PROTECT		//do not erase last page
			if(sourceAddr.Val < (CONFIG_START & 0xFFFC00)){
		#endif

		#ifdef USE_VECTOR_PROTECT			//do not erase first page
			if(sourceAddr.Val >= VECTOR_SECTION){
		#endif

		
		#ifdef USE_RUNAWAY_PROTECT
			//setup program flow protection test keys
			keyTest1 = (0x0009 | temp) + length + i + 7;
			keyTest2 = (0x557F << 1) - ER_FLASH - i + 3;
		#endif


		//perform erase
		Erase(sourceAddr.word.HW, sourceAddr.word.LW, PM_PAGE_ERASE);


		#ifdef USE_RUNAWAY_PROTECT
			writeKey1 -= 7;	// Modify keys to ensure proper program flow
			writeKey2 -= 3;
		#endif



		#ifdef USE_VECTOR_PROTECT	
			}//end vectors protect

		#elif  defined(USE_BOOT_PROTECT) || defined(USE_RESET_SAVE)
			//Replace the bootloader reset vector
			DWORD_VAL blResetAddr;

			if(sourceAddr.Val < PM_PAGE_SIZE/2){
	
				//Replace BL reset vector at 0x00 and 0x02 if erased
				blResetAddr.Val = 0;
	
				#ifdef USE_RUNAWAY_PROTECT
					//setup program flow protection test keys
					keyTest1 = (0x0009 | temp) + length + i;
					keyTest2 = (0x557F << 1) - ER_FLASH - i;
				#endif
				
				replaceBLReset(blResetAddr);

			}
		#endif

		#ifdef USE_CONFIGWORD_PROTECT
			}//end config protect
		#endif

		#ifdef USE_BOOT_PROTECT
			}//end bootloader protect
		#endif


		sourceAddr.Val += PM_PAGE_SIZE/2;	//increment by a page

	}//end while(i<length)
}//end ErasePM




/********************************************************************
* Function:     void WriteTimeout()
*
* PreCondition: The programmed data should be verified prior to calling
* 				this funtion.
*
* Input:		None.
*
* Output:		None.
*
* Side Effects:	None.
*
* Overview:		This function writes the stored value of the bootloader
*				timeout delay to memory.  This function should only
*				be called after sucessful verification of the programmed
*				data to prevent possible bootloader lockout
*
* Note:			None
********************************************************************/
void WriteTimeout()
{
	#ifdef USE_RUNAWAY_PROTECT
	WORD temp = (WORD)sourceAddr.Val;
	#endif


	//Write timeout value to memory
	#ifdef DEV_HAS_WORD_WRITE
		//write data into latches
   		WriteLatch((DELAY_TIME_ADDR & 0xFF0000)>>16, 
				   (DELAY_TIME_ADDR & 0x00FFFF), 
				   userTimeout.word.HW, userTimeout.word.LW);
	#else
		DWORD_VAL address;
		WORD bytesWritten;

		bytesWritten = 0;
		address.Val = DELAY_TIME_ADDR & (0x1000000 - PM_ROW_SIZE/2);
		
		//Program booloader entry delay to finalize bootloading
		//Load 0xFFFFFF into all other words in row to prevent corruption
		while(bytesWritten < PM_ROW_SIZE){
			
			if(address.Val == DELAY_TIME_ADDR){			
				WriteLatch(address.word.HW, address.word.LW,
							userTimeout.word.HW,userTimeout.word.LW);
			}else{
				WriteLatch(address.word.HW, address.word.LW,
							0xFFFF,0xFFFF);
			}

			address.Val += 2;
			bytesWritten +=4;
		}		
	#endif


	#ifdef USE_RUNAWAY_PROTECT
		//setup program flow protection test keys
		keyTest1 =  (0x0009 | temp) - 1 - 5;
		keyTest2 =  ((0x557F << 1) + VERIFY_OK) + 6;
	#endif


	//Perform write to enable BL timeout
	#ifdef DEV_HAS_WORD_WRITE
		//execute write sequence
		WriteMem(PM_WORD_WRITE);	
	#else
		//execute write sequence
		WriteMem(PM_ROW_WRITE);	
	#endif



	#ifdef USE_RUNAWAY_PROTECT
		writeKey1 += 5; // Modify keys to ensure proper program flow
		writeKey2 -= 6;
	#endif


}//end WriteTimeout




/*********************************************************************
* Function:     void AutoBaud()
*
* PreCondition: UART Setup
*
* Input:		None.
*
* Output:		None.
*
* Side Effects:	Resets WDT.  
*
* Overview:		Sets autobaud mode and waits for completion.
*
* Note:			Contains code to handle UART errata issues for
				PIC24FJ128 family parts, A2 and A3 revs.
********************************************************************/
void AutoBaud()
{
	BYTE dummy;
	UxMODEbits.ABAUD = 1;		//set autobaud mode

	while(UxMODEbits.ABAUD)		//wait for sync character 0x55
	{
		asm("clrwdt");			//looping code so clear WDT

		//if timer expired, jump to user code
		if(IFS0bits.T3IF == 1){
			ResetDevice(userReset.Val);
		}

		if(UxSTAbits.OERR) UxSTAbits.OERR = 0;
		if(UxSTAbits.URXDA) dummy = UxRXREG;
	}

	//Workarounds for autobaud errata in some silicon revisions
	#ifdef USE_WORKAROUNDS
		//Workaround for autobaud innaccuracy
		if(UxBRG == 0xD) UxBRG--;
		if(UxBRG == 0x1A) UxBRG--;
		if(UxBRG == 0x09) UxBRG--;
	
		#ifdef USE_HI_SPEED_BRG
			//Workarounds for ABAUD incompatability w/ BRGH = 1
			UxBRG = (UxBRG+1)*4 -1;
			if(UxBRG == 0x13) UxBRG=0x11;		
			if(UxBRG == 0x1B) UxBRG=0x19;	
			if(UxBRG == 0x08) UxBRG=0x22;

			//Workaround for Odd BRG recieve error when BRGH = 1		
			if (UxBRG & 0x0001)	UxBRG++;  
		#endif
	#endif

}//end AutoBaud()




#ifdef DEV_HAS_PPS
/*********************************************************************
* Function:     void ioMap()
*
* PreCondition: None.
*
* Input:		None.
*
* Output:		None.
*
* Side Effects:	Locks IOLOCK bit.
*
* Overview:		Maps UART IO for communications on PPS devices.  
*
* Note:			None.
********************************************************************/
void ioMap()
{

	//Clear the IOLOCK bit
	__builtin_write_OSCCONL(OSCCON & 0xFFBF);

	//INPUTS **********************
    PPS_URX_REG = PPS_URX_PIN; 	//UxRX = RP19

	//OUTPUTS *********************
	PPS_UTX_PIN = UxTX_IO; //RP25 = UxTX   

	//Lock the IOLOCK bit so that the IO is not accedentally changed.
	__builtin_write_OSCCONL(OSCCON | 0x0040);

}//end ioMap()
#endif



#if defined(USE_BOOT_PROTECT) || defined(USE_RESET_SAVE)
/*********************************************************************
* Function:     void replaceBLReset(DWORD_VAL sourceAddr)
*
* PreCondition: None.
*
* Input:		sourceAddr - the address to begin writing reset vector
*
* Output:		None.
*
* Side Effects:	None.
*
* Overview:		Writes bootloader reset vector to input memory location
*
* Note:			None.
********************************************************************/
void replaceBLReset(DWORD_VAL sourceAddr)
{
	DWORD_VAL data;	
	#ifndef DEV_HAS_WORD_WRITE
		WORD i;
	#endif
	#ifdef USE_RUNAWAY_PROTECT
		WORD tempkey1;
		WORD tempkey2;

		tempkey1 = keyTest1;
		tempkey2 = keyTest2;
	#endif


	//get BL reset vector low word and write
	data.Val = 0x040000 + (0xFFFF & BOOT_ADDR_LOW);
	WriteLatch(sourceAddr.word.HW, sourceAddr.word.LW, data.word.HW, data.word.LW);


	//Write low word back to memory on word write capable devices
	#ifdef DEV_HAS_WORD_WRITE
		#ifdef USE_RUNAWAY_PROTECT
			writeKey1 += 5; // Modify keys to ensure proper program flow
			writeKey2 -= 6;
		#endif

		//perform BL reset vector word write bypassing flow protect
		WriteMem(PM_WORD_WRITE);		
	#endif


	//get BL reset vector high byte and write
	data.Val = ((DWORD)(BOOT_ADDR_LOW & 0xFF0000))>>16;
	WriteLatch(sourceAddr.word.HW,sourceAddr.word.LW+2,data.word.HW,data.word.LW);


	#ifdef USE_RUNAWAY_PROTECT
		keyTest1 = tempkey1;
		keyTest2 = tempkey2;
	#endif

	//Write high byte back to memory on word write capable devices
	#ifdef DEV_HAS_WORD_WRITE
		#ifdef USE_RUNAWAY_PROTECT
			writeKey1 += 5; // Modify keys to ensure proper program flow
			writeKey2 -= 6;
		#endif

		//perform BL reset vector word write
		WriteMem(PM_WORD_WRITE);

	//Otherwise initialize row of memory to F's and write row containing reset
	#else

		for(i = 4; i < (PM_ROW_SIZE/PM_INSTR_SIZE*2); i+=2){
			WriteLatch(sourceAddr.word.HW,sourceAddr.word.LW+i,0xFFFF,0xFFFF);
		}

		#ifdef USE_RUNAWAY_PROTECT
			writeKey1 += 5; // Modify keys to ensure proper program flow
			writeKey2 -= 6;
		#endif

		//perform BL reset vector word write
		WriteMem(PM_ROW_WRITE);

	#endif

}//end replaceBLReset()
#endif
