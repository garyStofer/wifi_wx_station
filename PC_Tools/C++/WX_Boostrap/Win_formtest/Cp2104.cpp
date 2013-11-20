#include "StdAfx.h"
#include "Cp2104.h"

Cp2104::Cp2104(void)
{
}

wstring 
Cp2104::ctow(const char* src)
{
	return wstring(src, src + strlen(src));
}

int 
Cp2104::GetPortNum(WORD Vid, WORD Pid, char* ser)
{
	//Variables used for Registry access
	HKEY tmpKey, tmpSubKey, tmpPortKey;
	wstring portKeyString;
	wchar_t tmp[10];
	DWORD valtype;
	wchar_t* portString;
	
	DWORD length = 100;
	portString = new wchar_t[101];
	

	//Set portnum to -1, so if there is an error we will
	//know by returning a negative port value
	int portNum = ERROR_PORT_NUM;

	//  Open keys to get to the key where the port number is located. This key is:
	if (ERROR_SUCCESS == RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\", 0, KEY_READ, &tmpKey))
	{
		if (ERROR_SUCCESS == RegOpenKeyW(tmpKey, L"Enum\\USB\\", &tmpSubKey))
		{
			//The portkey string should look like this
			//"Vid_XXXX&Pid_XXXX\XXXX" where the XXXX's are Vid, Pid and serial string
			portKeyString = L"Vid_";
			_itow_s((int)Vid, tmp, 10, 16);
			portKeyString += tmp;

			portKeyString += L"&Pid_";
			_itow_s((int)Pid, tmp, 10, 16);
			portKeyString += tmp;

			portKeyString += L"\\";
			portKeyString += ctow(ser);
			portKeyString += L"\\Device Parameters\\";
			

			//If the portkey string is in the registry, then go ahead and open the portname
			if (ERROR_SUCCESS == RegOpenKeyExW(tmpSubKey, portKeyString.c_str(), 0, KEY_READ, &tmpPortKey))
			{
				// CP2101/2/3/4
				// This will only work for single interface devices i.e. CP2104
				if (ERROR_SUCCESS == RegQueryValueExW(tmpPortKey, L"PortName", NULL, &valtype, (unsigned char *)portString, &length))
				{
					// When we obtain this key, it will be in string format of
					// "COMXX" where XX is the port. Simply make the first three
					// elements of the string 0, and call the atoi function to obtain
					// the number of the port.
					portString[0] = portString[1] = portString[2] ='0';
					portNum = _wtoi(portString);
				}
		
				//Make sure to close all open keys for cleanup
				RegCloseKey(tmpPortKey);
			}

			RegCloseKey(tmpSubKey);
		}
		RegCloseKey(tmpKey);
	}
	RegCloseKey(HKEY_LOCAL_MACHINE);

	delete portString;

	// Return the number of the port the device is connected too
	return portNum;
}


int
Cp2104::GetCp2104_COM_num (void )
{	
	HANDLE	hUSBDevice;
	DWORD   NumDevices;
	BYTE	PartNum =-1;
	WORD	Pid =0;
	WORD	Vid =0;
	BYTE	len;
	int		port_num = ERROR_PORT_NUM;
	CP210x_SERIAL_STRING serialNum="";
	CP210x_SERIAL_STRING ManufacturerString ="";
	CP210x_SERIAL_STRING ProductString="";
	
	
	if  ( CP210x_GetNumDevices(&NumDevices) == CP210x_SUCCESS )
	{
		for(unsigned int n=0; n < NumDevices; n++)
		{
			//repeated checking for CP210x_SUCCESS is done because of possible surprise removal of the device
			if (  CP210x_Open(n, &hUSBDevice) == CP210x_SUCCESS )
			{
				CP210x_GetPartNumber(hUSBDevice, &PartNum);			// expect 0x04 .. ie. CP2104
				CP210x_GetDeviceVid(hUSBDevice, &Vid);				// expect 0x10c4 .. ie Silicon labs 
				CP210x_GetDevicePid(hUSBDevice, &Pid);				// expect 0xea60 .. ie USB to UART Bridge
				if ( CP210x_GetDeviceSerialNumber(hUSBDevice, serialNum, &len) == CP210x_SUCCESS )
				{
					for( int i=0; i<len; i++)	// replace spaces with "_"
					{
						if (serialNum[i] == 0x20)
							serialNum[i] = '_';
					}
				}
					
				CP210x_GetDeviceManufacturerString(hUSBDevice,ManufacturerString,&len,TRUE); //	expect "Silicon Labs"
				CP210x_GetDeviceProductString(hUSBDevice,ProductString,&len,TRUE);			// expect "CP2104 USB to UART Bridge Controller"
			

				// First Silabs device that matches VID, Pid and partnumber is assumed to be the weather station device
				// Could extend to include the product string, but that would require to program each CP2104 beforehand
				if ( Vid ==0x10c4 && Pid == 0xea60 && PartNum == 0x4 )
				{
					port_num =  GetPortNum(Vid, Pid,  serialNum);
					//Issue Reset and place the device in Config mode
					CP210xRT_WriteLatch(hUSBDevice,CP210x_GPIO_1 , 0);			// S1 Low
					CP210xRT_WriteLatch(hUSBDevice,CP210x_GPIO_0 , 0);			// Reset Low
					Sleep(100);
					CP210xRT_WriteLatch(hUSBDevice,CP210x_GPIO_0 , CP210x_GPIO_0);	// Release Reset
					Sleep(500);
					CP210xRT_WriteLatch(hUSBDevice,CP210x_GPIO_1 , CP210x_GPIO_1);	// Release S1

					// Device is now in Config mode
				}

			}
		}
		CP210x_Close( hUSBDevice);
	}

	return port_num;
}


