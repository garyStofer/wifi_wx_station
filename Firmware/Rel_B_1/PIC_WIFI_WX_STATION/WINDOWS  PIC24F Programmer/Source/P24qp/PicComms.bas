Attribute VB_Name = "PicComms"
Public Declare Function SendPacket Lib "PICBOOT.dll" (ByVal hComPort As Long, PacketData As Byte, ByVal NumOfBytes As Integer) As Integer
Public Declare Function GetPacket Lib "PICBOOT.dll" (ByVal hComPort As Long, PacketData As Byte, ByVal NumOfBytesLim As Integer) As Integer
Public Declare Function OpenPIC Lib "PICBOOT.dll" (ByVal ComPort As String, ByVal BitRate As Long, ByVal ReadTimeOut As Long) As Long
Public Declare Function ClosePIC Lib "PICBOOT.dll" (ByVal hComPort As Long) As Integer
Public Declare Function SendGetPacket Lib "PICBOOT.dll" (ByVal hComPort As Long, PacketData As Byte, ByVal NumOfBytes As Integer, ByVal NumOfBytesLim As Integer, ByVal NumOfRetrys As Integer) As Integer
Public Declare Function ReadPIC Lib "PICBOOT.dll" (ByVal hComPort As Long, LPpic As PIC, MemData As Byte) As Integer
Public Declare Function WritePIC Lib "PICBOOT.dll" (ByVal hComPort As Long, LPpic As PIC, MemData As Byte) As Integer
Public Declare Function VerifyPIC Lib "PICBOOT.dll" (ByVal hComPort As Long, LPpic As PIC, MemData As Byte) As Integer
Public Declare Function ErasePIC Lib "PICBOOT.dll" (ByVal hComPort As Long, ByVal PICAddr As Long, ByVal nBlock As Byte, ByVal nRetry As Byte) As Integer

Public Type PIC                 'structure used in communications DLL
    BootCmd As Byte
    BootDatLen As Integer
    BootAddr As Long
    BytesPerBlock As Integer
    BytesPerAddr As Byte
    MaxRetrys As Integer
    DeviceType As Integer
    
End Type

Public Type PICBOOT
    PortHandle As Long          'port info
    BitRate As Long
    CommPort As String
    CommTimeOut As Long
    
    MaxPacketSize As Integer
    MaxRetry As Integer

    DeviceMode As Byte          'Auto or manual
    DeviceType As Byte          'PIC16 or PIC18
    DeviceName As String        'device info
    DeviceCode As String
    
    DeviceWrtBlock As Integer      'byte per block
    DeviceRdBlock As Integer
    DeviceErsBlock As Integer
    DevBytesPerAddr As Byte
    ResetVector As String

    DebugLevel As Long
    
    InFileName As String        'file and path for load operation
    OutFileName As String       'file and path for save operation

    ProgMemFile As String       'Data files
    EEDataFile As String
    ConfigFile As String
    EditorFile As String
    ErrorLogFile As String

    AESEnable As Boolean

    ProgMemAddrH As Long        'Mem address limits (inclusive)
    ProgMemAddrL As Long
    EEDataAddrH As Long
    EEDataAddrL As Long
    ConfigAddrH As Long
    ConfigAddrL As Long
    BootLoadAddrH As Long
    BootLoadAddrL As Long
    UserResetVector As Long
    BootDelayAddr As Long
End Type


Public PicBootS As PICBOOT
Public bpic As PIC

Public MyFlag As Byte
Public DataPacket(256) As Byte
Public TimeOutFlag As Byte
Public AbortFlag As Byte







Function ReadRangeDevMem(RdAddrL As Long, RdAddrH As Long, BytsPerAddr As Byte, BCom As Byte, OutFile As String) As Integer
    ReDim InData(1024) As Byte
    Dim RetStat As Integer
    Dim FileLine As String
    Dim BootDatLen As Integer
    Dim BootAddr As Long
    Dim picA As PIC
    
    'Setup data file creation
    Set fs = CreateObject("Scripting.FileSystemObject")
    Set a = fs.CreateTextFile(VB.App.Path & "\" & OutFile, True)
    
    'Translate to HEX file byte address
    AddrL = RdAddrL * 2
    AddrH = RdAddrH * 2
    
    AbortFlag = 1
    BootAddr = AddrL

            
    Do While BootAddr < (AddrH)
    
        DoEvents
        
        'check for an abort
        If AbortFlag = 0 Then
            ReadRangeDevMem = -100
            Exit Function
        End If
    
        'limit the packet size
        If (AddrH + 2) - BootAddr > ((PicBootS.MaxPacketSize - 5)) Then
            picA.BootDatLen = (PicBootS.MaxPacketSize - 5)
        Else
            picA.BootDatLen = (AddrH + 2) - BootAddr
        End If
               
        picA.BootAddr = BootAddr / 2
        picA.BootCmd = BCom
        picA.BytesPerAddr = BytsPerAddr

        '***MODIFIED FOR AES - WHEN USING EE AND CONFIG WITH ENCRYPTION, BLOCK SIZE CHANGES
        'DUE TO EXTRA PHANTOM BYTES
        If PicBootS.AESEnable Then
            Select Case picA.BootCmd
                Case 4
                    picA.BytesPerBlock = 2
                Case 6
                    picA.BytesPerBlock = 1
                Case Else
                    picA.BytesPerBlock = PicBootS.DeviceRdBlock
            End Select
        Else
            picA.BytesPerBlock = PicBootS.DeviceRdBlock
        End If
        picA.MaxRetrys = PicBootS.MaxRetry
        picA.DeviceType = PicBootS.DeviceType
        
        RetStat = ReadPIC(PicBootS.PortHandle, picA, InData(0))
        If RetStat < 0 Then
            ReadRangeDevMem = RetStat
            Exit Function
        End If
        
        
        'Format the data
        For i = 0 To RetStat - 1
    
            Select Case BCom
                Case 4   'Data EE
                    
                    If BootAddr Mod 16 = 0 Then
                        FileLine = Dec2Hex(BootAddr, 6)
                    End If
                    
                    FileLine = FileLine & " " & Dec2Hex(CLng(InData(i)), 2)
                    BootAddr = BootAddr + 1
                    
                    '***MODIFIED FOR AES - Must read 2 phantom bytes from device
                    'as they are used for HEX encyrpt/decrypt
                    If Not PicBootS.AESEnable Then
                    
                        'Pad in 2 extra bytes as 0 for HEX file (32 bit addresses)
                        If (i + 1) Mod 2 = 0 Then
                            FileLine = FileLine & " 00 00"
                            BootAddr = BootAddr + 2
                        End If
                    End If
                    
                    If BootAddr Mod 16 = 0 Then
                        a.WriteLine (FileLine)
                    End If
    
                Case 6    'Config
                    
                    If PicBootS.AESEnable Then
                        
                        '***MODIFIED FOR AES - Must read all 4 from device
                        'as they are used for HEX encyrpt/decrypt
                                        
                        If BootAddr Mod 16 = 0 Then
                            FileLine = Dec2Hex(BootAddr, 7)
                        End If
                        
                        FileLine = FileLine & " " & Dec2Hex(CLng(InData(i)), 2)
                        BootAddr = BootAddr + 1
                        
                        If BootAddr Mod 16 = 0 Then
                            a.WriteLine (FileLine)
                        End If
                        
                    Else
                    
                        'Read 1 byte and pad in 3 extra bytes as 0 for HEX file (32 bit addresses)
                        FileLine = Dec2Hex(BootAddr, 7)
                        FileLine = FileLine & " " & Dec2Hex(CLng(InData(i)), 2) & " 00 00 00"
                        BootAddr = BootAddr + 4
                        a.WriteLine (FileLine)
                        
                    End If

                Case Else  'Prog Mem
                    
                    If BootAddr Mod 16 = 0 Then
                        FileLine = Dec2Hex(BootAddr, 6)
                    End If
                    
                    FileLine = FileLine & " " & Dec2Hex(CLng(InData(i)), 2)
                    BootAddr = BootAddr + 1
                    
                    If BootAddr Mod 16 = 0 Then
                        a.WriteLine (FileLine)
                    End If
            End Select

        Next i
       
        frmBootload.StatusBar1.Panels(1).Text = "Reading: " & Hex(BootAddr / 2)
    
    Loop
    ReadRangeDevMem = 1
    a.Close
End Function


Function WriteRangeDevMem(BlockSize As Integer, BytsPerAddr As Byte, BCom As Byte, InFile As String) As Integer
    ReDim OutData(256) As Byte
    Dim RetStat As Integer
    Dim ProgressInd As Integer
    Dim FileLine As String
    Dim picA As PIC
    Dim OldBootAddr As Long
    Dim ReadNext As Boolean
    Dim FirstLine As Boolean
    Dim i As Integer
    Dim LinesLeft As Integer
    Dim BytesLeft As Integer
    Dim tempBootAddr As Long
    Dim VerifyFlag As Boolean
    Dim TmpStr As String

    ReadNext = True
    FirstLine = True
    i = 0
    LinesLeft = BlockSize / 16
    
    'Setup data file creation
    Set fs = CreateObject("Scripting.FileSystemObject")
    Set a = fs.OpenTextFile(VB.App.Path & "\" & InFile, 1, False, 0)
    Set b = fs.CreateTextFile(PicBootS.ErrorLogFile, True)
    b.Close
            
    AbortFlag = 1
    ProgressInd = 1
    
    VerifyFlag = True

    Do While a.AtEndOfStream <> True
        DoEvents

        FileLine = a.ReadLine


        'check for an abort
        If AbortFlag = 0 Then
            If ProgressInd = -101 Then
                Exit Do
            End If
            
            ProgressInd = -100
            Exit Do
        End If
           

        picA.BootCmd = BCom
        picA.BytesPerAddr = BytsPerAddr
        picA.BytesPerBlock = BlockSize
        picA.MaxRetrys = PicBootS.MaxRetry
        picA.DeviceType = PicBootS.DeviceType
        
        'Check command type - handle PM write as full row, dataEE by line
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

        Else                'Program Memory

            If i = 0 Then
                picA.BootDatLen = BlockSize
                picA.BootAddr = (CLng(Val("&H" & Mid(FileLine, 1, 6) & "&")) And FULL_ADDRESS_MASK) / BytsPerAddr 'word addressed

            End If
            
            j = 0
            Do While j < 16

                OutData(i) = CByte(Val("&H" & Mid(FileLine, j * 3 + 8, 2)))
                
                i = i + 1
                j = j + 1
            Loop

        End If
        

        
        If BCom <> 2 Or (i Mod picA.BootDatLen = 0) Then
            
       
            'Write row/line
            RetStat = WritePIC(PicBootS.PortHandle, picA, OutData(0))
            If RetStat < 0 Then
                WriteRangeDevMem = RetStat
                Exit Function
            End If
                                           
            'Verify written row/line
            RetStat = VerifyWrite(picA, OutData)
            If RetStat < 0 Then
                If RetStat = -12 Then
                    ProgressInd = -101
                    VerifyFlag = False
                Else
                            
                    WriteRangeDevMem = RetStat
                    Exit Function
                End If
            Else
                ProgressInd = 1
            End If
            
            
            i = 0
            
            frmBootload.StatusBar1.Panels(1).Text = "Writing: " & Hex(picA.BootAddr)
        End If

    Loop
    
    If VerifyFlag = False Then
        WriteRangeDevMem = -101
    Else
        WriteRangeDevMem = ProgressInd
    End If
    
    a.Close
End Function


Function VerifyWrite(picV As PIC, outArray() As Byte) As Integer
    Dim RetStat As Integer
    Dim inArray(256) As Byte
    Dim BootAddr As Long
    Dim VerifyFlag As Boolean
    Dim OutLine As String
           
    'Setup data file creation
    Set fs = CreateObject("Scripting.FileSystemObject")
    Set b = fs.OpenTextFile(VB.App.Path & "\" & PicBootS.ErrorLogFile, 8, False, 0)
    
           
    'read written data froom pic
    picV.BootCmd = picV.BootCmd - 1 'read out using read command of same memory type
    
    If (picV.BootCmd = 1) Then
        picV.BytesPerBlock = PicBootS.DeviceRdBlock
    End If    
    
    RetStat = ReadPIC(PicBootS.PortHandle, picV, inArray(0))
    
    BootAddr = picV.BootAddr
    
    'error if read fails
    If RetStat < 0 Then
        VerifyWrite = RetStat
        Exit Function
    End If
    
    VerifyFlag = True
    
    i = 0
    'verify written data
    Do While i < RetStat
        If picV.BootCmd = 1 Then
            If (inArray(i) <> outArray(i) Or _
                inArray(i + 1) <> outArray(i + 1) Or _
                inArray(i + 2) <> outArray(i + 2) Or _
                inArray(i + 3) <> outArray(i + 3)) Then
                
                If PicBootS.AESEnable Then
                    Select Case BootAddr
                    'Device reset vector, user reset vector, and delay address are ignored because
                    'bootloader will intentionally write different values in these locations than what may be
                    'specified in the .hex file causing erroneous varification errors.
                    Case 0
                        'ignore reset vector
                    Case 2
                        'ignore reset vector
                    Case 4
                    Case 6
                        'AES COMPATABILITY - must ignore entire 16 byte block containing reset vector
                    Case PicBootS.UserResetVector
                        'ignore user's reset vector
                    Case ((PicBootS.UserResetVector And 16777200) + 2)
                    Case ((PicBootS.UserResetVector And 16777200) + 4)
                    Case ((PicBootS.UserResetVector And 16777200) + 6)
                        'AES COMPATABILITY - must ignore entire 16 byte block containing user reset vector
                    Case PicBootS.BootDelayAddr
                        'ignore boot delay address
                    Case ((PicBootS.BootDelayAddr And 16777200) + 2)
                    Case ((PicBootS.BootDelayAddr And 16777200) + 4)
                    Case ((PicBootS.BootDelayAddr And 16777200) + 6)
                        'AES COMPATABILITY - must ignore entire 16 byte block containing boot delay addr
                    Case Else
                        'AES COMPATABILITY - must ignore bootloader locations
                        If (BootAddr < PicBootS.BootLoadAddrL Or BootAddr > PicBootS.BootLoadAddrH) Then
                            'otherwise, verify error
                            b.WriteLine ("Verify Error at 0x" & Hex(BootAddr) & " should be: 0x" _
                                        & (Hex(CLng(outArray(i + 3)) * Hex(16777216) + CLng(outArray(i + 2)) * 65536 _
                                        + CLng(outArray(i + 1)) * 256 + CLng(outArray(i)))) & " but read: 0x" _
                                        & (Hex(CLng(inArray(i + 3)) * Hex(16777216) + CLng(inArray(i + 2)) * 65536 + _
                                        CLng(inArray(i + 1)) * 256 + CLng(inArray(i)))))
                                    
                            VerifyFlag = False
                            
                        End If
                    End Select
                Else
                    
                    Select Case BootAddr
                    'Device reset vector, user reset vector, and delay address are ignored because
                    'bootloader will intentionally write different values in these locations than what may be
                    'specified in the .hex file causing erroneous varification errors.
                    Case 0
                        'ignore reset vector
                    Case 2
                        'ignore reset vector
                    Case PicBootS.UserResetVector
                        'ignore user's reset vector
                    Case PicBootS.BootDelayAddr
                        'ignore boot delay address
                    Case Else
                        'otherwise, verify error
                        b.WriteLine ("Verify Error at 0x" & Hex(BootAddr) & " should be: 0x" _
                                    & (Hex(CLng(outArray(i + 3)) * Hex(16777216) + CLng(outArray(i + 2)) * 65536 _
                                    + CLng(outArray(i + 1)) * 256 + CLng(outArray(i)))) & " but read: 0x" _
                                    & (Hex(CLng(inArray(i + 3)) * Hex(16777216) + CLng(inArray(i + 2)) * 65536 + _
                                    CLng(inArray(i + 1)) * 256 + CLng(inArray(i)))))
                        
                        VerifyFlag = False
    
                    End Select
                End If
                
            End If
            
            i = i + 4
        ElseIf picV.BootCmd = 4 Then
            
            If PicBootS.AESEnable Then
                If (inArray(i) <> outArray(i) Or _
                    inArray(i + 1) <> outArray(i + 1) Or _
                    inArray(i + 2) <> outArray(i + 2) Or _
                    inArray(i + 3) <> outArray(i + 3)) Then
                    
                    b.WriteLine ("Verify Error at 0x" & Hex(BootAddr) & " should be: 0x" _
                                & (Hex(CLng(outArray(i + 3)) * Hex(16777216) + CLng(outArray(i + 2)) * 65536 _
                                + CLng(outArray(i + 1)) * 256 + CLng(outArray(i)))) & " but read: 0x" _
                                & (Hex(CLng(inArray(i + 3)) * Hex(16777216) + CLng(inArray(i + 2)) * 65536 + _
                                CLng(inArray(i + 1)) * 256 + CLng(inArray(i)))))
                                
                    VerifyFlag = False
                    
                End If
            
                i = i + 4
            Else
                If (inArray(i) <> outArray(i) Or _
                    inArray(i + 1) <> outArray(i + 1)) Then
                
                    b.WriteLine ("Verify Error at 0x" & Hex(BootAddr) & " should be: 0x" _
                                & Hex(CLng(outArray(i + 1)) * 256 + CLng(outArray(i))) & " but read: 0x" _
                                & Hex(CLng(inArray(i + 1)) * 256 + CLng(inArray(i))))
                                                    
                    VerifyFlag = False
                End If
                
                i = i + 2
            End If
        
        Else
            'Note: Config bits cannot be verified, as unimplemented bits are unknown and read as 0
            i = i + 1
        End If
        
        BootAddr = BootAddr + 2
        
    Loop
    
    b.Close
    
    If VerifyFlag = False Then
        VerifyWrite = -12
    Else
        VerifyWrite = RetStat
    End If
            
End Function


Function EraseRangeDevMem(AddrL As Long, AddrH As Long) As Integer
    Dim RetStat As Integer
    Dim BootAddr As Long
    Dim nBlocks As Byte
    
    AbortFlag = 1
    BootAddr = AddrL
            
    frmBootload.StatusBar1.Panels(1).Text = "Erasing..."
            
    Do While BootAddr < (AddrH + 1)
    
        DoEvents
        
        'check for an abort
        If AbortFlag = 0 Then
            EraseRangeDevMem = -100
            Exit Function
        End If

        nBlocks = (AddrH - AddrL + 1) * PicBootS.DevBytesPerAddr / PicBootS.DeviceErsBlock
        If nBlocks > 255 Then
            nBlocks = 255
        End If
        
        'Go get some data
        RetStat = ErasePIC(PicBootS.PortHandle, BootAddr, nBlocks, 5)
        
        If RetStat < 0 Then
            EraseRangeDevMem = RetStat
            Exit Function
        End If
                  
        BootAddr = BootAddr + ((PicBootS.DeviceErsBlock / PicBootS.DevBytesPerAddr) * nBlocks)
        
        frmBootload.StatusBar1.Panels(1).Text = "Erasing: " & Hex(BootAddr)
    
    Loop
    
    EraseRangeDevMem = 1

End Function


Function WriteConfig(CfgAddr As Long, CfgData As Byte) As Integer
    ReDim InData(10) As Byte

    InData(0) = 7 'command
    InData(1) = 1

    InData(2) = CByte((CfgAddr) And 255)
    InData(3) = CByte(((CfgAddr) And 65280) \ 256)
    InData(4) = CByte(((CfgAddr) And 16711680) \ 65536)
    InData(5) = CfgData

    RetStat = SendGetPacket(PicBootS.PortHandle, InData(0), 6, 255, 1)
    If RetStat < 0 Then
        WriteConfig = RetStat
        Exit Function
    End If

    frmBootload.StatusBar1.Panels(1).Text = "Writing CONFIG: " & Hex(CfgAddr)
    WriteConfig = 1
End Function


Function ReadConfig(CfgAddr As Long) As Integer
    ReDim InData(10) As Byte

    InData(0) = 6 'command
    InData(1) = 1

    InData(2) = CByte((CfgAddr) And 255)
    InData(3) = CByte(((CfgAddr) And 65280) \ 256)
    InData(4) = CByte(((CfgAddr) And 16711680) \ 65536)

    RetStat = SendGetPacket(PicBootS.PortHandle, InData(0), 5, 255, 1)
    If RetStat < 0 Then
        ReadConfig = RetStat
        Exit Function
    End If

    frmBootload.StatusBar1.Panels(1).Text = "Reading CONFIG: " & Hex(CfgAddr)
    ReadConfig = InData(5)
End Function




Function ReadVersion() As String
    ReDim DevID(10) As Byte
    Dim RetStat As Integer
    
    DoEvents

    DevID(0) = 0
    DevID(1) = 2
    RetStat = SendGetPacket(PicBootS.PortHandle, DevID(0), 2, 10, 1)
    
    If RetStat <= 0 Then
        ReadVersion = Empty
    Else
        ReadVersion = "v" & DevID(3) & "." & DevID(2)
    End If
    
End Function



Function ReadDeviceID() As String
    ReDim DevID(10) As Byte
    Dim RetStat As Integer
    Dim picb As PIC
    
    DevID(0) = 0
    DevID(1) = 0

    picb.BootAddr = &HFF0000
    picb.BootCmd = 1
    picb.BytesPerBlock = 4
    picb.BytesPerAddr = 2
    picb.BootDatLen = 4
    picb.MaxRetrys = PicBootS.MaxRetry
    RetStat = ReadPIC(PicBootS.PortHandle, picb, DevID(0))

    If RetStat <= 0 Then
        ReadDeviceID = "0"
    Else
        ReadDeviceID = CStr((DevID(1) * 256) + DevID(0))
    End If
    
End Function



Function GotoRunMode() As Integer
    ReDim DevID(10) As Byte
    Dim RetStat As Integer
    Dim picb As PIC

    DevID(0) = 0
    DevID(1) = 0
    RetStat = SendPacket(PicBootS.PortHandle, DevID(0), 2)
    
End Function





Function Dec2Bin(MyByte As Byte) As String
    Dim CurrentData As Integer
    Dim OldData As Integer
    
    Dec2Bin = ""
    OldData = MyByte
    
    For i = 7 To 0 Step -1
     
        CurrentData = OldData - (2 ^ i)
        If CurrentData < 0 Then
            Dec2Bin = Dec2Bin & "0"
        Else
            OldData = CurrentData
            Dec2Bin = Dec2Bin & "1"
        End If
    
    Next i
    
End Function


Function Dec2Hex(MyInteger As Variant, MyWidth As Variant) As String
    Dim TempWork As String
    Dim TempWidth As Long
    Dim tempInt As Long

    TempWidth = CLng(MyWidth)
    tempInt = CLng(MyInteger)
    
    TempWork = Hex(tempInt)
    
    If Len(TempWork) > TempWidth Then
        Dec2Hex = Mid(TempWork, Len(TempWork) - TempWidth, TempWidth)
        Exit Function
    End If
    
    Do Until Len(TempWork) = TempWidth
        TempWork = "0" & TempWork
    Loop
    
    Dec2Hex = TempWork
End Function



