using System;
using System.Collections.Generic;
using System.Text;
using System.IO;
using System.Runtime.InteropServices;
using System.IO.Ports;
using System.Threading;


namespace Pic_BL
{
    public  delegate void d_Evnthandler(System.String s, int i);    // Forward decleration for what the event handler needs to look like 

    public class ProgramPIC
    {
        public /* event*/ d_Evnthandler SendMsgTo;   // this is a refereense to said eventhandler(s) which is going to be set to event handler(s) by the client of the class

        //Packet control characters
        const byte STX    = 0x55;	//0x55 for Autobaud
        const byte ETX	=	4;
        const byte DLE	=	5;

        //Error conditions
        const int ERROR_GEN_READWRITE	=-1;
        const int ERROR_READ_TIMEOUT	=-2;
        const int ERROR_READ_LIMIT		=-3;
        const int ERROR_BAD_CHKSUM		=-4;
        const int ERROR_RETRY_LIMIT		=-5;
        const int ERROR_INVALID_COMMAND	=-6;
        const int ERROR_BLOCK_TOO_SMALL	=-7;
        const int ERROR_PACKET_TOO_BIG	=-8;
        const int ERROR_OFF_BOUNDRY		=-9;
        const int ERROR_BPA_TOO_SMALL	=-10;
        const int ERROR_BPA_TOO_BIG		=-11;	
        const int ERROR_VERIFY_FAILED	=-12;
        const int ERROR_OFF_BOUNDRY2	=-13;
        const int ERROR_VERIFY_EXT_LEN = -113;

        //Limits
        const int MAX_PACKET			=261;

        //Bootloader commands
        const byte COMMAND_READVER		= 0;
        const byte COMMAND_READPM		= 1;
        const byte COMMAND_WRITEPM		= 2;
        const byte COMMAND_ERASEPM		= 3;
        const byte COMMAND_READEE		= 4;
        const byte COMMAND_WRITEEE		= 5;
        const byte COMMAND_READCFG		= 6;
        const byte COMMAND_WRITECFG	    = 7;
        const byte COMMAND_VERIFYOK     = 8;

        public string SerialPortName;

        public bool AbortRequest;

        [StructLayoutAttribute(LayoutKind.Explicit, Size = 16)]
        private struct _PIC
        {
            [FieldOffsetAttribute(0)]
            public byte BootCmd;
            [FieldOffsetAttribute(2)]
            public ushort BootDatLen;		//Number of bytes to read/write
            [FieldOffsetAttribute(4)]
            public uint BootAddr;			//24 bit memory address (Prog or EE)
            [FieldOffsetAttribute(8)]
            public ushort BytesPerBlock;		//Number of bytes in a command block (page, row, instruction, etc)
            [FieldOffsetAttribute(10)]
            public byte BytesPerAddr;		//Number of bytes per address
            [FieldOffsetAttribute(12)]
            public ushort MaxRetrys;			//Number of retries before failure
            [FieldOffsetAttribute(14)]
            public ushort DeviceType;		//Unknown = 0, PIC24F = 1, PIC24FJ = 2
        };
        private struct _HEXDATA
        {
            public ulong address;
            public int datLen;
            public String data;
        }

        private  struct PICBOOT
        {
            public int PortHandle;
            public uint CommTimeOut;

            public int MaxPacketSize;
            public ushort MaxRetry;

            public byte DeviceMode;
            public byte DeviceType;
            public string DeviceName;
            public string DeviceCode;

            public int DeviceWrtBlock;
            public int DeviceRdBlock;
            public int DeviceErsBlock;
            public byte DevBytesPerAddr;
            public string ResetVector;

            public long DebugLevel;

            public string IniFile;
            public string ProgMemFile;
            public string EEDataFile;
            public string ConfigFile;
            public string ErrorLogFile;

            public bool AESEnable;

            public long ProgMemAddrH;
            public long ProgMemAddrL;
            public long EEDataAddrH;
            public long EEDataAddrL;
            public long ConfigAddrH;
            public long ConfigAddrL;
            public long UserResetVector;
            public long BootDelayAddr;
        }
        [DllImport("kernel32")]
        private static extern long WritePrivateProfileString(string section, string key, string val, string filePath);

        [DllImport("kernel32")]
        private static extern int GetPrivateProfileString(string section, string key, string def, StringBuilder retVal, int size, string filePath);

        private  PICBOOT PicBootS;

        const string STATUS_NO_VERSION_INFO = "No firmware version available...";
        const int LOWER_BYTE_MASK = 255;

        const int LOWER_WORD_MASK = 65535;
        const int ROW_START_MASK = 16776960;
        const int UPPER_BYTE_MASK2 = 33488896;
        const int FULL_ADDRESS_MASK = 33554431;
  string appPath;
        SerialPort serialPort;
        List<byte> verifyOutList;
        List<byte> verifyInList;
        
    
        // CONSTRUCTOR
        public ProgramPIC()
        {
            verifyOutList = new List<byte>();
            verifyInList = new List<byte>();
            ReadSettings();
            PicBootS.AESEnable = false;
        }

        // a function to send progress report messages back to the GUI client via a delegate/event
        private void DoUpdateProgress( string s)
        {
            if (SendMsgTo != null)
            {
                SendMsgTo(s, 0);
            }
        }
        private void DoUpdateProgress(string s, int i)
        {
            if (SendMsgTo != null)
            {
                SendMsgTo(s, i);
            }
        }

        private long CLngHex(string p)
        {
            bool good;
            long result;
            result = 0;
            good = long.TryParse(p, System.Globalization.NumberStyles.AllowHexSpecifier, null, out result);
            return result;
        }
        private long Val(string p)
        {
            bool good;
            long result;

            result = 0;
            good = long.TryParse(p, out result);
            return result;
        }
        private string Dec2Hex(byte[] data, int pos)
        {
            string result;
            result = "";
            result = data[pos].ToString("X02");
            return result;
        }
        private string ReadDeviceID(ushort maxr)
        {
            byte[] DevID;
            int RetStat;
            _PIC picb;
            string result = "";

            DevID = new byte[10];
            DevID[0] = 0;
            DevID[1] = 0;

            picb = new _PIC();
            picb.BootCmd = 1;
            picb.BootDatLen = 4;
            picb.BootAddr = 0xFF0000;
            picb.BytesPerBlock = 4;
            picb.BytesPerAddr = 2;
            picb.MaxRetrys = maxr;
            RetStat = ReadPIC(ref picb, DevID);

            if (RetStat <= 0)
            {
                result = "0";
            }
            else
            {
                result = ((DevID[1] * 256) + DevID[0]).ToString();
            }

            return result;
        }
        private string ReadVersion()
        {
            byte[] DevID;
            int RetStat;
            string result = "";

            DevID = new byte[20];
            DevID[0] = 0;
            DevID[1] = 2;
            RetStat = SendGetPacket(DevID, 2, 10, 1);
            if (RetStat <= 0)
            {
                result = "";
            }
            else
            {
                result = "v" + DevID[3].ToString() + "." + DevID[2];
            }
            return result;
        }
        private int ValidateHEXFile(string InHEXFile)
        {
            int Checksum;
            string InFileLine;
            int DataCount;
            int AddrCode;
            long address;
            string DataByte;
            int result = 1;
            StreamReader sr = null;
            try
            {
                sr = new StreamReader(InHEXFile);
                if (sr.EndOfStream == true)
                {
                    result = -1;
                }
                else
                {
                    while (sr.EndOfStream != true)
                    {
                        InFileLine = sr.ReadLine();
                        DataByte = " ";
                        if (InFileLine.Length > 0)
                        {
                            DataByte = InFileLine.Substring(0, 1);
                        }
                        if (DataByte == ":")
                        {
                            AddrCode = (int)CLngHex(InFileLine.Substring(7, 2));
                            DataCount = (int)CLngHex(InFileLine.Substring(1, 2));
                            address = CLngHex(InFileLine.Substring(3, 4)) & LOWER_WORD_MASK;


                            Checksum = 0;
                            for (int i = 0; i < (DataCount + 5); i++)
                            {
                                Checksum = Checksum + (int)CLngHex(InFileLine.Substring((2 * i) + 1, 2));
                            }
                            if ((Checksum & 0xff) != 0)
                            {
                                result = -3;
                                break;
                            }
                        }
                        else
                        {
                            result = -4;
                            break;
                        }
                        if (AddrCode == 1)
                        {
                            break;
                        }
                        if (sr.EndOfStream == true)
                        {
                            result = -5;
                            break;
                        }
                    }
                }
                sr.Close();
            }
            catch (Exception allEx)
            {

                DoUpdateProgress(allEx.Message);
                result = -6;
            }
            return result;
        }
        private int EraseRangeDevMem(ulong AddrL, ulong AddrH)
        {
            int RetStat;
            ulong currAddr;
            int nBlocks;

            currAddr = AddrL;

            DoUpdateProgress("Erasing....");
            while (currAddr < (AddrH + 1))
            {
                nBlocks = (int)((AddrH - AddrL + 1) * (ulong)PicBootS.DevBytesPerAddr / (ulong)PicBootS.DeviceErsBlock);
                if (nBlocks > 255)
                {
                    nBlocks = 255;
                }

                // 'Go get some data
                RetStat = ErasePIC((uint)currAddr, (byte)nBlocks, 5);

                if (RetStat < 0)
                {
                    return RetStat;
                }

                currAddr += (ulong)((PicBootS.DeviceErsBlock / PicBootS.DevBytesPerAddr) * nBlocks);

                DoUpdateProgress("Erasing = " + currAddr.ToString("X06"));

            }
            RetStat = 1;
            return RetStat;
        }


        private int WriteRangeDevMem(int BlockSize, byte BytsPerAddr, byte BCom, String InFile)
        {
            byte[] OutData = new byte[261 * 2];
            int RetStat;
            int ProgressInd =1;
            float progress_bar;
            String FileLine;
            _PIC picA = new _PIC();
            int i, j;

            bool VerifyFlag = true;

      
            // 'Setup data file creation
            StreamReader a = new StreamReader(appPath + "\\" + InFile);
 
            picA.BootDatLen = (ushort)BlockSize;
       

            i = 0;
            while (a.EndOfStream != true)
            {
                if (AbortRequest)
                {
                    RetStat = -999;
                    DoUpdateProgress("Aborting...");
                    goto AbortExit;
                }

                FileLine = a.ReadLine();
                
                picA.BootCmd = BCom;
                picA.BytesPerAddr = BytsPerAddr;
                picA.BytesPerBlock = (ushort)BlockSize;
                picA.MaxRetrys = PicBootS.MaxRetry;
                picA.DeviceType = PicBootS.DeviceType;

 #region  Code for EEprom and Configuration bits --
                /* 'Check command type - handle PM write as full row, dataEE by line
                If BCom = 5 Then   'Data EE
                    picA.BootAddr = (CLng(Val("&H" & Mid(FileLine, 1, 6) & "&")) And FULL_ADDRESS_MASK) \ BytsPerAddr
                    
                    i = 0
                    j = 0
                    TmpStr = Mid(FileLine, i * 3 + 8, 2)
                    Do While TmpStr <> ""
                        If PicBootS.AESEnable Then
                            
                            '***MODIFIED FOR AES: Must send upper unused 2 bytes because it is used during encryption/decrypt
                            OutData(j) = CByte(Val("&H" & TmpStr))
                            j = j + 1
                        
                        Else
                            
                            'Data EE only implements 16 bits, don't send upper 2 bytes
                            If (((i + 2) Mod 4) = 0) Or (((i + 1) Mod 4) = 0) Then
                                'Do not use upper 2 bytes of data
                            Else
                                OutData(j) = CByte(Val("&H" & TmpStr))
                                j = j + 1
                            End If
                            
                        End If
                            
                        i = i + 1
                        TmpStr = Mid(FileLine, i * 3 + 8, 2)
                    Loop
                    
                    picA.BootDatLen = j
                    
                ElseIf BCom = 7 Then   'Config fuses
                    
                    picA.BootAddr = (CLng(Val("&H" & Mid(FileLine, 1, 7) & "&")) And FULL_ADDRESS_MASK) \ BytsPerAddr
                    
                    i = 0
                    j = 0
                    TmpStr = Mid(FileLine, i * 3 + 9, 2)
                    Do While TmpStr <> ""
               
               
                       If PicBootS.AESEnable Then
                            
                            '***MODIFIED FOR AES: Must send upper unused 3 bytes because it is used during encryption/decrypt
                            OutData(j) = CByte(Val("&H" & TmpStr))
                            j = j + 1
                        
                        Else
                                
                            'Config only implements 8 bits, don't send upper 3 bytes
                            If (((i + 3) Mod 4) = 0) Or (((i + 2) Mod 4) = 0) Or (((i + 1) Mod 4) = 0) Then
                                'Do not use upper 3 bytes of data
                            Else
                                OutData(j) = CByte(Val("&H" & TmpStr))
                                j = j + 1
                            End If
                        End If
                        
                        i = i + 1
                        TmpStr = Mid(FileLine, i * 3 + 9, 2)
                    Loop
                    
                    picA.BootDatLen = j
                */
 #endregion

                if ((BCom != 5) && (BCom != 7))//                'Program Memory
                {
                    if (i == 0)
                    {
                        picA.BootDatLen = (ushort)BlockSize;
                        picA.BootAddr = (uint)(CLngHex(FileLine.Substring(0, 6)) & FULL_ADDRESS_MASK) / BytsPerAddr; // 'word addressed
                    }

                    j = 0;
                    while (j < 16)
                    {
                        OutData[i] = (byte)(CLngHex(FileLine.Substring(j * 3 + 7, 2)));

                        i = i + 1;
                        j = j + 1;
                    }

                }

                if ((BCom != 2) || ((i % picA.BootDatLen) == 0))
                {

                    progress_bar = (float)(picA.BootAddr + picA.BytesPerBlock / picA.BytesPerAddr) / (float)PicBootS.ProgMemAddrH * 1000;
                    if (progress_bar < 1)      // Round up for less than 1% so that the DoUpdateProgress displasy on the progress bar and not on the list window
                        progress_bar = 1;

                    DoUpdateProgress("Writing: " + picA.BootAddr.ToString("X"), (int)progress_bar);

                    // 'Write row/line
                    RetStat = WritePIC(ref picA, OutData);
                    if (RetStat < 0)
                    {
                        DoUpdateProgress("Writing failed at:" + picA.BootAddr.ToString("X"));
                        goto AbortExit;
                    }


                    // 'Verify written row/line
                    RetStat = VerifyPIC(picA, OutData);
                    if (RetStat < 0)
                    {
                        DoUpdateProgress("Verify failed at:" + picA.BootAddr.ToString("X"));
                        if (RetStat == -12)
                        {
                            ProgressInd = -101;
                            VerifyFlag = false;
                        }
                        else
                        {
                            goto AbortExit;
                        }
                    }
                    else
                    {
                        ProgressInd = 1;
                    }


                    i = 0;
                
                }

            }

            if (VerifyFlag == false)
            {
                RetStat = -101;
            }
            else
            {
                RetStat = ProgressInd;
            }
AbortExit:
            a.Close();
            return RetStat;
        }


        private string GetSetting(string INISection, string INIKey)
        {
            string result;
            result = "";
            int RetStat;
            StringBuilder temp = new StringBuilder(255);
            RetStat = GetPrivateProfileString(INISection, INIKey, "", temp, 20, PicBootS.IniFile);
            result = temp.ToString();
            return result;
        }
        private void ReadSettings()
        {
            string f;
            appPath = Environment.CurrentDirectory;
           // f = Path.GetFileNameWithoutExtension(System.Reflection.Assembly.GetExecutingAssembly().Location);
            // MessageBox.Show(Environment.CurrentDirectory + "\\" + f + ".ini");
            f = "PIC_BL";
            PicBootS.IniFile = appPath + "\\" + f + ".ini";
// TODO: Need a check here to see of the ini file exists -- otherwise all the folloeing GetSettings are going to be empty
// One could check for RetStat in GetSettings  to see if  settings are read. 

            PicBootS.ProgMemFile = GetSetting("PIC24FBOOT", "progmem");
            PicBootS.EEDataFile = GetSetting("PIC24FBOOT", "eedata");
            PicBootS.ConfigFile = GetSetting("PIC24FBOOT", "config");
            PicBootS.ErrorLogFile = GetSetting("PIC24FBOOT", "errorlog");
            PicBootS.CommTimeOut = (uint)Val(GetSetting("PIC24FBOOT", "CommTimeOut"));
            PicBootS.DebugLevel = Val(GetSetting("PIC24FBOOT", "debuglevel"));
            PicBootS.DeviceMode = (byte)Val(GetSetting("PIC24FBOOT", "devicemode"));
            PicBootS.MaxRetry = (ushort)Val(GetSetting("PIC24FBOOT", "maxretry"));
    
            PicBootS.UserResetVector = CLngHex(GetSetting("PIC24FBOOT", "userresetvector"));
            PicBootS.BootDelayAddr = CLngHex(GetSetting("PIC24FBOOT", "bootdelay"));
            
            PicBootS.ProgMemAddrH = 0x200;
            PicBootS.ProgMemAddrL = 0x200;
            PicBootS.EEDataAddrH = 0;
            PicBootS.EEDataAddrL = 0;
            PicBootS.ConfigAddrH = 0x300000;
            PicBootS.ConfigAddrL = 0x300000;

            PicBootS.PortHandle = 0;
        }
        public void EraseDeviceFlash()
        {
            ulong ProgMemAddrH = (ulong)PicBootS.ProgMemAddrH;
// Protecting upper most page from erasure/programming 
// ----------------------------------------------------

// If Config byte is left at erased state then BL can't ever program anything .. Catch 22!

// The PIC side of the BL has an option set to prevent erase and program of the topmost page of Flash memory which 
// contain the configuration words. 

// This works as long as the application never grows into the last page of code sapce, becuause the BL can not program anything in the last erase page.   
// Allow the BL code to erase all the memory could lead to a bricked device if a reset or powercycle occurs in between the erase
// of the last page and the programming of the new config words.
// A third option is to let the Bootloader application (this code) decide if the last page should be protected from erasure.
// Doing it in the application allows for options given to the user accepting the risk and therefore allows the entiere flash range to be 
// programmed still. If the upper 2K of the Flash space change the user will see verification erros and can then opt to erase the top page,
// accepting the risk of loosing the device if he interrupts power during the process
// In order for this to work the BL and the application need to share the the same values for the Config words, so that there are no verification
//errors during the normal course of programming


            // ProgMemAddrH is a WORD address  this prevents the upper 2Kbyte of the address space to be erased
            // This could be a users choice -- for now be safe and simply don't erase the top
            ProgMemAddrH = ProgMemAddrH - 0x400;  // To protect the upper most page from beeing erased and reprogrammed 
            int r = EraseRangeDevMem((ulong)PicBootS.ProgMemAddrL, ProgMemAddrH);
            if (r > 0)
            {
                DoUpdateProgress("Erased  OK");
            }
            else
            {
                DoUpdateProgress("Erased = " + r.ToString());
            }

        }
        public int ImportP24HEXFile(string InHEXFile)
        {
            int result = 0;
            StreamReader InFile = null;
            StreamWriter PMOut = null;
        //    StreamWriter EEOut = null;
        //    StreamWriter CFGOut = null;
            String tempStr;
            List<String> fileArray = new List<string>();
            
            SortedDictionary<ulong, _HEXDATA> hexArray = new SortedDictionary<ulong, _HEXDATA>();
            List<_HEXDATA> ta = new List<_HEXDATA>();

            _HEXDATA oneline;
            ulong LineAddrHigh, RowStartAddr;
            byte LineDataCount;
            ulong LineAddr;
            byte LineCode;
            String LineData;
            byte[] RowData = new byte[256];
            bool emptyRow;
            int i, j;
            byte[] OverflowArray = new byte[17];
            byte OverflowLen;
            ulong OutAddr;
            String OutLine = "";
            int RowIndex;
            OverflowLen = 0;

            DoUpdateProgress("Importing Hex File...");

            result = ValidateHEXFile(InHEXFile);
            if (result < 0)
            {
                return result;
            }

            try
            {
                InFile = new StreamReader(InHEXFile);
                PMOut = new StreamWriter(appPath + "\\" + PicBootS.ProgMemFile);
              //  EEOut = new StreamWriter(appPath + "\\" + PicBootS.EEDataFile);
              //  CFGOut = new StreamWriter(appPath + "\\" + PicBootS.ConfigFile);
                while ((tempStr = InFile.ReadLine()) != null)
                {
                    fileArray.Add(tempStr);
                }
                j = 0;
                LineAddrHigh = 0;
                foreach (string line in fileArray)
                {
                    LineDataCount = (byte)CLngHex(line.Substring(1, 2));
                    LineAddr = (ulong)CLngHex(line.Substring(3, 4)) & LOWER_WORD_MASK;
                    LineCode = (byte)CLngHex(line.Substring(7, 2));
                    LineData = line.Substring(9, (LineDataCount * 2));
                    if (LineCode == 0)
                    {
                        oneline = new _HEXDATA();
                        oneline.address = (LineAddrHigh * 65536) + (LineAddr & LOWER_WORD_MASK);
                        oneline.data = LineData;
                        oneline.datLen = LineDataCount;
                        hexArray.Add(oneline.address, oneline);
                    }
                    else if (LineCode == 1)
                    {
                        break;
                    }
                    else if (LineCode == 4)
                    {
                        LineAddrHigh = (ulong)CLngHex(line.Substring(9, 4)) & LOWER_WORD_MASK;
                    }
                }
                for (j = 0; j < 256; j++)
                {
                    if (((j + 1) % 4) == 0)
                    {
                        RowData[j] = 0;
                    }
                    else
                    {
                        RowData[j] = 255;
                    }
                }
                i = 0;

                ta.AddRange(hexArray.Values);
                RowStartAddr = ta[0].address & ROW_START_MASK;
                emptyRow = true;

                while (i < ta.Count)
                {
                    LineAddrHigh = (ta[i].address & UPPER_BYTE_MASK2) / 65536;
                    if ((LineAddrHigh >= 0) && (LineAddrHigh <= 253))
                    {
                        //Is all of current data in new row?
                        if ((ta[i].address - RowStartAddr) > 255)
                        {

                            //'Next data is in new Row, so write old row to file if not empty
                            OutAddr = RowStartAddr;
                            j = 0;
                            if (emptyRow == false)
                            {
                                while (j < 256)
                                {
                                    // 'Built a formatted line of data
                                    if ((j % 16) == 0)
                                    {
                                        OutLine = OutAddr.ToString("X06") + " ";
                                    }
                                    OutLine = OutLine + Dec2Hex(RowData, j) + " ";
                                    OutAddr = OutAddr + 1;
                                    j = j + 1;

                                    if (((j % 16) == 0) && (j != 0))
                                    {
                                        PMOut.WriteLine(OutLine);
                                    }
                                }
                                emptyRow = true;
                            }

                            // 'start new row
                            RowStartAddr = ta[i].address & ROW_START_MASK;
                            for (j = 0; j < 256; j++)
                            {
                                if (((j + 1) % 4) == 0)
                                {
                                    RowData[j] = 0;
                                }
                                else
                                {
                                    RowData[j] = 255;
                                }
                            }

                            // 'initialize row with overflow of last line, if any
                            for (j = 0; j < OverflowLen; j++)
                            {
                                RowData[j] = OverflowArray[j];

                                // 'If non-erased data is present, row is not empty
                                if (((j + 1) % 4) != 0)
                                {
                                    if (OverflowArray[j] != 255)
                                    {
                                        emptyRow = false;
                                    }
                                }
                            }
                            OverflowLen = 0;

                        }
                        // 'Is a portion of current data in new row?
                        if ((ta[i].address + (ulong)ta[i].datLen - RowStartAddr) > 255)
                        {
                            _HEXDATA ha;
                            // 'Store data in temporary array to use in next row
                            OverflowLen = (byte)((LOWER_BYTE_MASK & ta[i].address) + (ulong)ta[i].datLen - 256);
                            ha = ta[i];
                            ha.datLen = ha.datLen - OverflowLen;
                            // ta[i].datLen = ta[i].datLen - OverflowLen;
                            ta[i] = ha;
                            for (j = 0; j < OverflowLen; j++)
                            {
                                OverflowArray[j] = (byte)CLngHex(ta[i].data.Substring(j * 2 + ta[i].datLen * 2, 2));
                            }

                        }


                        // 'get current data
                        RowIndex = (int)(ta[i].address & LOWER_BYTE_MASK);
                        for (j = 0; j < ta[i].datLen; j++)
                        {
                            RowData[RowIndex] = (byte)CLngHex(ta[i].data.Substring(j * 2, 2));
                            RowIndex = RowIndex + 1;

                            // 'If non-erased data is present, row is not empty
                            if (((j + 1) % 4) != 0)
                            {
                                if (CLngHex(ta[i].data.Substring(j * 2, 2)) != 255)
                                {
                                    emptyRow = false;
                                }
                            }
                        }
                    }
                    else if ((LineAddrHigh == 254) || (LineAddrHigh == 255))
                    {
                        /*
                     Case 254 To 255         ' EEDATA memory
                                            
                         'Built a formatted line of data
                         OutLine = Dec2Hex(hexArray(i).address, 6) & " "
                
                         j = 1
                         TmpStr = Mid(hexArray(i).data, j, 2)
                         Do While TmpStr <> ""
                             OutLine = OutLine & TmpStr & " "
                             TmpStr = Mid(hexArray(i).data, j * 2 + 1, 2)
                
                             j = j + 1
                         Loop
                
                         EEOut.WriteLine (OutLine)*/
                    }
                    else if (LineAddrHigh == 496)
                    {
                        /*
                Case 496                ' config memory
            
                    'Built a formatted line of data
                    OutLine = Dec2Hex(hexArray(i).address, 7) & " "
                
                    j = 1
                    TmpStr = Mid(hexArray(i).data, j, 2)
                    Do While TmpStr <> ""
                        OutLine = OutLine & TmpStr & " "
                        TmpStr = Mid(hexArray(i).data, j * 2 + 1, 2)
                
                        j = j + 1
                    Loop
                
                    CFGOut.WriteLine (OutLine)*/
                    }
                    i = i + 1;
                }
                OutAddr = RowStartAddr;
                j = 0;
                if (emptyRow == false)
                {
                    while (j < 256)
                    {
                        // 'Built a formatted line of data
                        if ((j % 16) == 0)
                        {
                            OutLine = OutAddr.ToString("X06") + " ";
                        }
                        OutLine = OutLine + Dec2Hex(RowData, j) + " ";
                        OutAddr = OutAddr + 1;
                        j = j + 1;

                        if (((j % 16) == 0) && (j != 0))
                        {
                            PMOut.WriteLine(OutLine);
                        }
                    }
                }
            }
            catch (Exception allEx)
            {
                DoUpdateProgress(allEx.Message);
                result = -1000;
            }

            InFile.Close();
            PMOut.Close();
           // EEOut.Close();
           // CFGOut.Close();
            if (result <= 0)
            {
                DoUpdateProgress("Import failed = " + result.ToString());
            }
            else
            {
                DoUpdateProgress("Import = OK");
                DoUpdateProgress("Import complete", -1);
            }
            return result;
        }


        public int UploadNew()
        {
            byte[] command = new byte[MAX_PACKET + 7];
            int RetStat;
                      
            DoUpdateProgress("Uploading...");
            
            if (WriteRangeDevMem(PicBootS.DeviceWrtBlock, PicBootS.DevBytesPerAddr, 2, PicBootS.ProgMemFile) != 1)
            {
                DoUpdateProgress("Upload BAD");
                return -1;
            }

            DoUpdateProgress("Upload OK");
            
            command[0] = 8; //'command

            RetStat = SendGetPacket(command, 1, 255, 5);

            if (RetStat >= 0)
            {
                DoUpdateProgress("Verify OK");
            }
            else
            {
                DoUpdateProgress("Verify = " + RetStat.ToString());
            }

            return RetStat;
        }
        public bool IsImported(string InFile)
        {
 
            try
            {
               StreamReader a = new StreamReader(appPath + "\\" + InFile);
               a.Close();

            }
            catch (Exception allEx)
            {
                DoUpdateProgress("No firmware has been imported yet!");
                DoUpdateProgress("Import hex file first!", -999);
                return false;
            }
            return true;
        }

        public void doProgram ( )
        {
            AbortRequest = false;

            // Check for imported progamming file
            if (!IsImported(PicBootS.ProgMemFile))
            {                
                return;
            }
          


            DoUpdateProgress("Connecting to PIC...");
            ClosePIC();
            
            if (ConnectToPIC(SerialPortName, 57600) > 0)
            {
                EraseDeviceFlash();
                if (AbortRequest)
                {
                    DoUpdateProgress("Aborting...", -999);
                    return;
                }

                UploadNew();
                DoUpdateProgress("Done", -999);     // -999  signals the end of the thread

                ClosePIC();
            }
        }


//----------------------------------------------------------------------------------------------------------------------------------
// From here on down member function that deal with the PIC directly  -- Should be it's own class -- Was picboot.dll more or less
        public int ConnectToPIC(String comport, int baud)
        {
            int RetStat;
            byte[] DevID;

            DevID = new byte[257];

            RetStat = 1;

            if (PicBootS.PortHandle <= 0)
            {
                PicBootS.PortHandle = OpenPIC(comport, baud,(int)PicBootS.CommTimeOut);
            }
            if (PicBootS.PortHandle <= 0)
            {
                RetStat = -1;
                return RetStat;
            }

            PicBootS.DeviceCode = ReadDeviceID(PicBootS.MaxRetry);

            if (PicBootS.DeviceCode == "0")
            {
                DoUpdateProgress("Can not read device ID");
                DoUpdateProgress("Can not read device ID", -999);
                RetStat = -2;
                return RetStat;
            }

            PicBootS.DeviceName = GetSetting("DEVICELIST", PicBootS.DeviceCode);

            if (PicBootS.DeviceName == "")
            {
                PicBootS.DeviceName = GetSetting("DEVICELIST", "");
            }
            String s = ReadVersion();

            if (s == "")
            {
                RetStat = -3;
                DoUpdateProgress(STATUS_NO_VERSION_INFO);
                return RetStat;
            }
            else
            {
                DoUpdateProgress("Version=" + s);
            }
            PicBootS.ProgMemAddrL = CLngHex(GetSetting(PicBootS.DeviceName, "pmrangelow"));
            PicBootS.ProgMemAddrH = CLngHex(GetSetting(PicBootS.DeviceName, "pmrangehigh"));
            PicBootS.EEDataAddrL = CLngHex(GetSetting(PicBootS.DeviceName, "eerangelow"));
            PicBootS.EEDataAddrH = CLngHex(GetSetting(PicBootS.DeviceName, "eerangehigh"));
            PicBootS.ConfigAddrL = CLngHex(GetSetting(PicBootS.DeviceName, "cfgrangelow"));
            PicBootS.ConfigAddrH = CLngHex(GetSetting(PicBootS.DeviceName, "cfgrangehigh"));

            if (GetSetting(PicBootS.DeviceName, "userresetvector") != "")
            {
                PicBootS.UserResetVector = CLngHex(GetSetting(PicBootS.DeviceName, "userresetvector"));
            }
            if (GetSetting(PicBootS.DeviceName, "bootdelay") != "")
            {
                PicBootS.BootDelayAddr = CLngHex(GetSetting(PicBootS.DeviceName, "bootdelay"));
            }

            PicBootS.DevBytesPerAddr = (byte)Val(GetSetting(PicBootS.DeviceName, "bytesperaddr"));
            PicBootS.MaxPacketSize = (int)Val(GetSetting(PicBootS.DeviceName, "maxpacketsize"));
            PicBootS.DeviceErsBlock = (int)Val(GetSetting(PicBootS.DeviceName, "eraseblock"));
            PicBootS.DeviceRdBlock = (int)Val(GetSetting(PicBootS.DeviceName, "readblock"));
            PicBootS.DeviceWrtBlock = (int)Val(GetSetting(PicBootS.DeviceName, "writeblock"));
            PicBootS.DeviceType = (byte)Val(GetSetting(PicBootS.DeviceName, "devicetype"));

            if (PicBootS.AESEnable == false)
            {
                DevID[0] = 1;
                DevID[1] = 2;
                DevID[2] = 0;
                DevID[3] = 0;
                DevID[4] = 0;

                RetStat = SendGetPacket(DevID, 5, 255, 5);
                if (RetStat < 0)
                {
                }
                else
                {
                    PicBootS.ResetVector = "";
                    for (int i = 0; i < 8; i++)
                    {
                        PicBootS.ResetVector = PicBootS.ResetVector + Dec2Hex(DevID, i + 5) + " ";
                    }
                }
            }
            DoUpdateProgress("DeviceID=" + PicBootS.DeviceName);
            return RetStat;
        }
        private int OpenPIC(String COMport, int Baud,int ReadTimeOut)
        {
            int result = -1;
            // Get a handle to the port.
            try
            {
                serialPort = new SerialPort(COMport, Baud, Parity.None, 8);
                serialPort.ReadTimeout = ReadTimeOut;
                serialPort.Open();
                result = 1;
                DoUpdateProgress("Com port opened.");
            }
            catch (Exception allEx)
            {
                DoUpdateProgress(allEx.Message);
            }
            return result;
        }
        public void ClosePIC()
        {
            if ((serialPort != null) && (serialPort.IsOpen == true))
            {
                PicBootS.PortHandle = 0;
                serialPort.Close();
            }
        }
        private int GetPacket(ref byte[] PacketData, uint ByteLimit)
        {
            int PacketCount = 0;
            uint Checksum = 0;
            byte DataByte;
            byte Flags = 2;
            bool StartOfPacket;
            StartOfPacket = true;
            int MaxStart = 1000;
            //Scan for a start condition
            while (Flags > 0)
            {
                if (StartOfPacket == true)
                {
                    while (Flags > 0)
                    {
                        try
                        {
                            DataByte = (byte)serialPort.ReadByte();
                            MaxStart--;
                            if (MaxStart == 0)
                            {
                                return ERROR_READ_TIMEOUT;
                            }
                        }
                        catch (TimeoutException tex)
                        {
                            DoUpdateProgress(tex.Message);
                            return ERROR_READ_TIMEOUT;
                        }
                        catch (InvalidOperationException ioEx)
                        {
                            DoUpdateProgress(ioEx.Message);
                            return ERROR_GEN_READWRITE;
                        }

                        if (DataByte == STX) Flags--;
                        else Flags = 2;
                    }
                    PacketCount = 0;
                    Flags = 1;
                    StartOfPacket = false;
                }
                try
                {
                    DataByte = (byte)serialPort.ReadByte();
                }
                catch (TimeoutException tex)
                {
                    DoUpdateProgress(tex.Message);
                    return ERROR_READ_TIMEOUT;
                }
                catch (InvalidOperationException ioEx)
                {
                    DoUpdateProgress(ioEx.Message);
                    return ERROR_GEN_READWRITE;
                }

                switch (DataByte)
                {
                    case STX:
                        {
                            StartOfPacket = true;
                            continue;
                        }
                    case ETX:
                        {
                            Flags = 0;
                            continue;
                        }
                    case DLE:
                        {
                            try
                            {
                                DataByte = (byte)serialPort.ReadByte();
                            }
                            catch (TimeoutException tex)
                            {
                                DoUpdateProgress(tex.Message);
                                return ERROR_READ_TIMEOUT;
                            }
                            catch (InvalidOperationException ioEx)
                            {
                                DoUpdateProgress(ioEx.Message);
                                return ERROR_GEN_READWRITE;
                            }
                        }
                        break;
                }
                if (PacketCount > ByteLimit) return ERROR_READ_LIMIT;
                PacketData[PacketCount] = DataByte;
                Checksum = Checksum + (uint)DataByte;
                PacketCount++;
            }

            //Test the checksum
            DataByte = (byte)(((~(Checksum)) + 1) & 255);
            if (DataByte != 0) return ERROR_BAD_CHKSUM;

            return PacketCount;
        }
        private int SendPacket(byte[] PacketData, ushort NumOfBytes)
        {
            int PacketCount;
            byte CheckSum = 0;
            int i;
            byte[] OutData = new byte[MAX_PACKET * 2]; // times two because of potential for bytestuffing every single data byte with esc char


            //Send the start condition
            i = 0;
            OutData[i++] = STX; // Add the start condition twice
            OutData[i++] = STX;

            //Send the packet data and stuff byte if necessary
            for (CheckSum = 0, PacketCount = 0; PacketCount < NumOfBytes; PacketCount++)
            {
                switch (PacketData[PacketCount])
                {
                    case STX:
                    case ETX:
                    case DLE:
                        {
                            OutData[i++] = DLE; // Stuff Data escape byte
                            break;
                        }
                }

                OutData[i++] = PacketData[PacketCount];         // Add data byte
                CheckSum += (byte)PacketData[PacketCount];      // sum up the 8 bit checksum 
            }

            //Calculate the negative checksum ( 2's compliemnt)
            CheckSum = (byte)-CheckSum;

            // Escape the checksum byte if needed
            switch (CheckSum)
            {
                case STX:
                case ETX:
                case DLE:
                    {

                        OutData[i++] = DLE; // Stuff the data escape character
                        break;
                    }
            }

            OutData[i++] = CheckSum;   // Add the checksum 
            OutData[i++] = ETX;        // Add the stop condition

            // output the entire protocol packet 
            try
            {
                serialPort.Write(OutData, 0, i);

                int j;
                for (j = 0; j < i; j++)
                {
                    verifyOutList.Add(OutData[j]);
                }

            }
            catch (Exception allEx)
            {
                DoUpdateProgress(allEx.Message);
                PacketCount = ERROR_GEN_READWRITE;
            }

            return PacketCount;
        }
        private int SendGetPacket(byte[] PacketData, ushort SendNumOfBytes, ushort RecvByteLimit, ushort NumOfRetrys)
        {
            int RetStatus;
            int RetryCount;

            RetryCount = NumOfRetrys;

            while (true)
            {
                if (RetryCount == 0) return ERROR_RETRY_LIMIT;
                RetryCount--;

                RetStatus = SendPacket(PacketData, SendNumOfBytes);
                if (RetStatus < 0) return RetStatus;

                RetStatus = GetPacket(ref PacketData, RecvByteLimit);
                if ((RetStatus != ERROR_READ_TIMEOUT) && (RetStatus != ERROR_BAD_CHKSUM))
                {
                    break;
                }
            }

            return RetStatus;
        }
        private int ReadPIC(ref _PIC pic, byte[] PacketData)
        {
            byte[] InData = new byte[MAX_PACKET * 2];		//Allocate for one packet
            int RetStatus;
            int DatCount;
            int DatCount2 = 0;

            switch (pic.BootCmd)
            {
                case COMMAND_READPM:
                case COMMAND_READEE:
                case COMMAND_READCFG:
                    break;
                default: return ERROR_INVALID_COMMAND;
            }

            //Limit to 1 to 3 bytes per addr
            if (pic.BytesPerAddr == 0) return ERROR_BPA_TOO_SMALL;
            if (pic.BytesPerAddr > 3) return ERROR_BPA_TOO_BIG;

            //if(pic->BytesPerBlock < pic->BytesPerAddr) return ERROR_BLOCK_TOO_SMALL;
            if (pic.BootDatLen / pic.BytesPerBlock > MAX_PACKET) return ERROR_PACKET_TOO_BIG;

            //Build header
            InData[0] = pic.BootCmd;
            InData[1] = (byte)(pic.BootDatLen / pic.BytesPerBlock);
            InData[2] = (byte)(pic.BootAddr & 0xFF);
            InData[3] = (byte)((pic.BootAddr & 0xFF00) / 0x100);
            InData[4] = (byte)((pic.BootAddr & 0xFF0000) / 0x10000);

            RetStatus = SendGetPacket(InData, 5, MAX_PACKET, pic.MaxRetrys);

            if (RetStatus < 0) return RetStatus;

            for (DatCount = 5; DatCount < RetStatus - 1; DatCount++)
            {
                PacketData[DatCount2] = InData[DatCount];
                DatCount2++;
            }

            return DatCount2;
        }
        private int WritePIC(ref _PIC pic, byte[] PacketData)
        {
            byte[] OutData = new byte[MAX_PACKET + 7];		//Allocate for one packet
            int RetStatus;
            int DatCount;
            int DatCount2;

            switch (pic.BootCmd)
            {
                case COMMAND_WRITEPM:
                case COMMAND_WRITEEE:
                case COMMAND_WRITECFG:
                    break;
                default: return ERROR_INVALID_COMMAND;
            }

            //Limit to 1 to 3 bytes per addr
            if (pic.BytesPerAddr == 0) return ERROR_BPA_TOO_SMALL;
            if (pic.BytesPerAddr > 3) return ERROR_BPA_TOO_BIG;

            //if(pic->BytesPerBlock < pic->BytesPerAddr) return ERROR_BLOCK_TOO_SMALL;
            if (pic.BootDatLen / pic.BytesPerBlock > MAX_PACKET - 6) return ERROR_PACKET_TOO_BIG;

            if ((pic.BootAddr * pic.BytesPerAddr % pic.BytesPerBlock) > 0) return ERROR_OFF_BOUNDRY;
            if ((pic.BootDatLen % pic.BytesPerBlock) > 0) return ERROR_OFF_BOUNDRY2;

            //Build header
            OutData[0] = pic.BootCmd;
            OutData[1] = (byte)(pic.BootDatLen / pic.BytesPerBlock);
            OutData[2] = (byte)(pic.BootAddr & 0xFF);
            OutData[3] = (byte)((pic.BootAddr & 0xFF00) / 0x100);
            OutData[4] = (byte)((pic.BootAddr & 0xFF0000) / 0x10000);

            DatCount = 5;
            for (DatCount2 = 0; DatCount2 < pic.BootDatLen; DatCount2++)
            {
                OutData[DatCount] = PacketData[DatCount2];
                DatCount++;
            }

            RetStatus = SendGetPacket(OutData, (ushort)DatCount, MAX_PACKET, pic.MaxRetrys);

            if (RetStatus < 0) return RetStatus;

            return DatCount2;
        }

        private int ErasePIC(uint PICAddr, byte nBlock, byte nRetry)
        {
            byte[] InData = new byte[MAX_PACKET + 5];		//Allocate for one packet
            int RetStatus;


            //Build header
            InData[0] = COMMAND_ERASEPM;
            InData[1] = nBlock;
            InData[2] = (byte)(PICAddr & 0xFF);
            InData[3] = (byte)((PICAddr & 0xFF00) / 0x100);
            InData[4] = (byte)((PICAddr & 0xFF0000) / 0x10000);

            RetStatus = SendGetPacket(InData, 5, MAX_PACKET, nRetry);

            if (RetStatus < 0) return RetStatus;

            return InData[1];
        }

        private int VerifyPIC(_PIC picV, byte[] outArray)
        {
            int RetStat;
            byte[] inArray = new byte[262];
            long BootAddr;
            bool VerifyFlag;
            int i;
            StreamWriter b = new StreamWriter(appPath + "\\" + PicBootS.ErrorLogFile, true);


            // 'read written data froom pic
            picV.BootCmd = (byte)(picV.BootCmd - 1);  // 'read out using read command of same memory type

            if (picV.BootCmd == 1)
            {
                picV.BytesPerBlock = (ushort)PicBootS.DeviceRdBlock;
            }

            RetStat = ReadPIC(ref picV, inArray);

            BootAddr = picV.BootAddr;

            // 'error if read fails
            if (RetStat < 0)
            {
                b.Close();
                return RetStat;
            }

            VerifyFlag = true;

            i = 0;
            // 'verify written data
            while (i < RetStat)
            {
                if (picV.BootCmd == 1)
                {
                    if ((inArray[i] != outArray[i]) ||
                        (inArray[i + 1] != outArray[i + 1]) ||
                        (inArray[i + 2] != outArray[i + 2]) ||
                        (inArray[i + 3] != outArray[i + 3]))
                    {
                        //'Device reset vector, user reset vector, and delay address are ignored because
                        // 'bootloader will intentionally write different values in these locations than what may be
                        //'specified in the .hex file causing erroneous varification errors.

                        if (BootAddr == 0)
                        {
                            //                                'ignore reset vector
                        }
                        else if (BootAddr == 2)
                        {
                            //                                'ignore reset vector
                        }
                        else if (BootAddr == PicBootS.UserResetVector)
                        {
                            //       'ignore user's reset vector
                        }
                        else if (BootAddr == PicBootS.BootDelayAddr)
                        {
                            // 'ignore boot delay address
                        }
                        else
                        {
                            //                                'otherwise, verify error
                            String line;
                            uint pa, pb;
                            pa = (((uint)outArray[i + 3]) << 24) | (((uint)outArray[i + 2]) << 16) | (((uint)outArray[i + 1]) << 8) | (((uint)outArray[i + 0]) << 0);
                            pb = (((uint)inArray[i + 3]) << 24) | (((uint)inArray[i + 2]) << 16) | (((uint)inArray[i + 1]) << 8) | (((uint)inArray[i + 0]) << 0);

                            line = "Verify Error at 0x" + BootAddr.ToString("X08") + " should be: 0x";
                            line += pa.ToString("X08") + " but read: 0x" + pb.ToString("X08");
                            b.WriteLine(line);
                            VerifyFlag = false;
                        }
                    }
                    i = i + 4;
                }
                BootAddr = BootAddr + 2;
            }

            b.Close();

            if (VerifyFlag == false)
            {
                RetStat = -12;
            }
            return RetStat;
        }

    }
   
    class TestApp
    {

        static void Main(string[] args)
        {
            int BaudRate = 57600;
 

            ProgramPIC p = new ProgramPIC();
            System.Environment.ExitCode = 2;
            p.ImportP24HEXFile("c:\\temp\\production.hex");
            
            if (p.ConnectToPIC("COM7", BaudRate) > 0)
            {
                System.Environment.ExitCode = 1;
                     
                p.EraseDeviceFlash();
                p.UploadNew();

                p.ClosePIC();
            }
         
            
             Console.ReadKey();
            
        }
    }
    
}
