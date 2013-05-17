
/******************************************************************************\
*	PIC24F Serial Bootloader Communications Handler (header file)
*	original code by Ross M. Fosler
*   updated for PIC24F by Brant Ivey
*	Microchip Technology Incorporated
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
\******************************************************************************/



//Packet control characters
#define STX    85	//0x55 for Autobaud
#define ETX		4
#define DLE		5

//Error conditions
#define ERROR_GEN_READWRITE		-1
#define	ERROR_READ_TIMEOUT		-2
#define ERROR_READ_LIMIT		-3
#define	ERROR_BAD_CHKSUM		-4
#define	ERROR_RETRY_LIMIT		-5
#define ERROR_INVALID_COMMAND	-6
#define ERROR_BLOCK_TOO_SMALL	-7
#define ERROR_PACKET_TOO_BIG	-8
#define ERROR_OFF_BOUNDRY		-9
#define ERROR_BPA_TOO_SMALL		-10
#define ERROR_BPA_TOO_BIG		-11	
#define ERROR_VERIFY_FAILED		-12
#define ERROR_OFF_BOUNDRY2		-13

//Limits
#define MAX_PACKET			261

//Bootloader commands
#define COMMAND_READVER		0
#define COMMAND_READPM		1
#define COMMAND_WRITEPM		2
#define COMMAND_ERASEPM		3
#define COMMAND_READEE		4
#define COMMAND_WRITEEE		5
#define COMMAND_READCFG		6
#define COMMAND_WRITECFG	7
#define COMMAND_VERIFYOK	8


//PIC structure used for some functions
typedef struct _PIC {
	BYTE BootCmd;
	WORD BootDatLen;		//Number of bytes to read/write
	DWORD BootAddr;			//24 bit memory address (Prog or EE)
	WORD BytesPerBlock;		//Number of bytes in a command block (page, row, instruction, etc)
	BYTE BytesPerAddr;		//Number of bytes per address
	WORD MaxRetrys;			//Number of retries before failure
	WORD DeviceType;		//Unknown = 0, PIC24F = 1, PIC24FJ = 2
} PIC;


//Prototypes
HANDLE APIENTRY OpenPIC(LPSTR ComPort, DWORD BitRate, DWORD ReadTimeOut);
INT APIENTRY ClosePIC(HANDLE hComPort);
INT APIENTRY GetPacket(HANDLE hComPort, BYTE PacketData[], WORD ByteLimit);
INT APIENTRY SendPacket(HANDLE hComPort, BYTE PacketData[], WORD NumOfBytes);
INT APIENTRY SendGetPacket(HANDLE hComPort, BYTE PacketData[], WORD SendNumOfBytes, WORD RecvByteLimit, WORD NumOfRetrys);
INT APIENTRY ReadPIC(HANDLE hComPort, PIC *pic, BYTE PacketData[]);
INT APIENTRY WritePIC(HANDLE hComPort, PIC *pic, BYTE PacketData[]);
INT APIENTRY ErasePIC(HANDLE hComPort, DWORD PICAddr, BYTE nBlock, BYTE nRetry);
INT APIENTRY VerifyPIC(HANDLE hComPort, PIC *pic, BYTE PacketData[]);


