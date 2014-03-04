// $Id$
#pragma once
	using namespace std;
#define ERROR_PORT_NUM -1
ref class Cp2104
{
public:
	Cp2104(void);
	int	
	GetCp2104_COM_num (void );

private:
	wstring 
	ctow(const char* src);

	int 
	GetPortNum(WORD Vid, WORD Pid, char* ser);

};
