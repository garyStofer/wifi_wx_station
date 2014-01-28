Attribute VB_Name = "FileAccess"
Private Declare Function GetPrivateProfileString Lib "kernel32" Alias "GetPrivateProfileStringA" (ByVal lpApplicationName As String, ByVal lpKeyName As Any, ByVal lpDefault As String, ByVal lpReturnedString As String, ByVal nSize As Long, ByVal lpFileName As String) As Long
Private Declare Function WritePrivateProfileString Lib "kernel32" Alias "WritePrivateProfileStringA" (ByVal lpApplicationName As String, ByVal lpKeyName As Any, ByVal lpString As Any, ByVal lpFileName As String) As Long
Public Const LOWER_BYTE_MASK = 255
Public Const LOWER_WORD_MASK = 65535
Public Const FULL_ADDRESS_MASK = 33554431
Public Const UPPER_BYTE_MASK = 16711680
Public Const ROW_START_MASK = 16776960
Public Const HEX_LINE_MASK = 16777200
Public Const UPPER_BYTE_MASK2 = 33488896

Public Type HEXDATA
    address As Long
    datLen As Integer
    data As String
End Type


Public Function GetSetting(INISection As String, INIKey As String) As String
    Dim MyString As String
    
    MyString = "                                                      "
    RetStat = GetPrivateProfileString(INISection, INIKey, "", MyString, 20, VB.App.Path & "\" & VB.App.EXEName & ".INI") '   "\P1618QP.INI")
    GetSetting = Mid(MyString, 1, InStr(1, MyString, Chr(0), vbBinaryCompare) - 1)
End Function



Public Function SetSetting(MySetting As String, INISection As String, INIKey As String) As Long
    SetSetting = WritePrivateProfileString(INISection, INIKey, MySetting, VB.App.Path & "\" & VB.App.EXEName & ".INI") ' "\P1618QP.INI")
End Function



Public Function ExportP24HEXFile(OutHEXFile As String) As Integer
    Dim Checksum As Long
    Dim address As Long
    Dim OldAddress As Long
    Dim FileLine As String
    Dim OutFileLine As String

    
    Set fs = CreateObject("Scripting.FileSystemObject")
    Set OutFile = fs.CreateTextFile(OutHEXFile, True)
    Set PMIn = fs.OpenTextFile(VB.App.Path & "\" & PicBootS.ProgMemFile, 1, False, 0)
    Set EEIn = fs.OpenTextFile(VB.App.Path & "\" & PicBootS.EEDataFile, 1, False, 0)
    Set CFGIn = fs.OpenTextFile(VB.App.Path & "\" & PicBootS.ConfigFile, 1, False, 0)

    address = &HFFFFFF
    Do While PMIn.AtEndOfStream <> True
        FileLine = PMIn.ReadLine
        OldAddress = address
        
        address = Val("&H" & Mid(FileLine, 1, 6)) And FULL_ADDRESS_MASK
        
        If (address And UPPER_BYTE_MASK) <> (OldAddress And UPPER_BYTE_MASK) Then
            OutFileLine = ":0200000400" & UCase(Dec2Hex((address And UPPER_BYTE_MASK) \ 65536, 2))
            Checksum = 0
            For i = 0 To 5
                Checksum = Checksum + Val("&H" & Mid(OutFileLine, (i * 2) + 2, 2) & "&")
            Next i
            OutFileLine = OutFileLine & Dec2Hex((256 - (Checksum And 255)) And 255, 2)
            OutFile.WriteLine (OutFileLine)
        End If
        
        OutFileLine = ":10" & UCase(Dec2Hex(address And LOWER_WORD_MASK, 4) & "00")
        For i = 0 To 15
            OutFileLine = OutFileLine & UCase(Mid(FileLine, (i * 3) + 8, 2))
        Next i
        
        Checksum = 0
        For i = 0 To 19
            Checksum = Checksum + Val("&H" & Mid(OutFileLine, (i * 2) + 2, 2))
        Next i
        
        OutFileLine = OutFileLine & UCase(Dec2Hex((256 - (Checksum And 255)) And 255, 2))
        OutFile.WriteLine (OutFileLine)
    Loop
          
    Do While EEIn.AtEndOfStream <> True
        FileLine = EEIn.ReadLine
        OldAddress = address
        
        address = (Val("&H" & Mid(FileLine, 1, 6)) And FULL_ADDRESS_MASK)
        
        If (address And UPPER_BYTE_MASK) <> (OldAddress And UPPER_BYTE_MASK) Then
            OutFileLine = ":0200000400" & Dec2Hex((address And UPPER_BYTE_MASK) \ 65536, 2)
            Checksum = 0
            For i = 0 To 5
                Checksum = Checksum + Val("&H" & Mid(OutFileLine, (i * 2) + 2, 2))
            Next i
            OutFileLine = OutFileLine & Dec2Hex((256 - (Checksum And 255)) And 255, 2)
            OutFile.WriteLine (OutFileLine)
        End If
        
        OutFileLine = ":10" & Dec2Hex(address And LOWER_WORD_MASK, 4) & "00"
        For i = 0 To 15
            OutFileLine = OutFileLine & Mid(FileLine, (i * 3) + 8, 2)
        Next i
        
        Checksum = 0
        For i = 0 To 19
            Checksum = Checksum + Val("&H" & Mid(OutFileLine, (i * 2) + 2, 2) & "&")
        Next i
        
        OutFileLine = OutFileLine & Dec2Hex((256 - (Checksum And 255)) And 255, 2)
        OutFile.WriteLine (OutFileLine)
    Loop

    Do While CFGIn.AtEndOfStream <> True
        FileLine = CFGIn.ReadLine
        OldAddress = address
        
        address = Val("&H" & Mid(FileLine, 1, 7)) And FULL_ADDRESS_MASK
        
        If (address And UPPER_BYTE_MASK2) <> (OldAddress And UPPER_BYTE_MASK2) Then
            OutFileLine = ":02000004" & Dec2Hex((address And UPPER_BYTE_MASK2) \ 65536, 4)
            Checksum = 0
            For i = 0 To 5
                Checksum = Checksum + Val("&H" & Mid(OutFileLine, (i * 2) + 2, 2) & "&")
            Next i
            OutFileLine = OutFileLine & Dec2Hex((256 - (Checksum And 255)) And 255, 2)
            OutFile.WriteLine (OutFileLine)
        End If
        
        '***MODIFIED FOR AES - CONFIG LINES HAVE FULL 16-BYTE PADDING WHEN ENCRYPTED
        If PicBootS.AESEnable Then
            OutFileLine = ":10" & Dec2Hex(address And LOWER_WORD_MASK, 4) & "00"
        Else
            OutFileLine = ":04" & Dec2Hex(address And LOWER_WORD_MASK, 4) & "00"
        End If
            
        For i = 0 To 15
            OutFileLine = OutFileLine & Mid(FileLine, (i * 3) + 9, 2)
        Next i
        
        Checksum = 0
        For i = 0 To 19
            Checksum = Checksum + Val("&H" & Mid(OutFileLine, (i * 2) + 2, 2) & "&")
        Next i
        
        OutFileLine = OutFileLine & Dec2Hex((256 - (Checksum And 255)) And 255, 2)
        OutFile.WriteLine (OutFileLine)
    Loop
    

    OutFile.WriteLine (":00000001FF")


    OutFile.Close
    PMIn.Close
    EEIn.Close
    CFGIn.Close
End Function





Function ValidateHEXFile(InHEXFile As String) As Integer
    Dim Checksum As Integer
    Dim InFileLine As String
    Dim DataCount As Integer
    Dim AddrCode As Integer
    Dim address As Long
    Dim DataByte As Integer
        
    On Error GoTo ErrorHandler
    
        
    Set fs = CreateObject("Scripting.FileSystemObject")
    ChDir VB.App.Path
    Set InFile = fs.OpenTextFile(InHEXFile, 1, False, 0)
    
    'Check for an empty file
    If InFile.AtEndOfStream = True Then
        ValidateHEXFile = -1
        InFile.Close
        Exit Function
    End If
    
    'Validate the file before using it
    Do While InFile.AtEndOfStream <> True
        InFileLine = InFile.ReadLine
        
        AddrCode = 0
        If Mid(InFileLine, 1, 1) = "" Then
            DataByte = Asc(" ")
        Else
            DataByte = Asc(Mid(InFileLine, 1, 1))
        End If
        
        'check the line
        Select Case DataByte
            Case Asc(":")
                AddrCode = Val("&H" & Mid(InFileLine, 8, 2))
                DataCount = Val("&H" & Mid(InFileLine, 2, 2))
                address = Val("&H" & Mid(InFileLine, 4, 4)) And LOWER_WORD_MASK

            
                Checksum = 0
                For i = 0 To DataCount + 4
                    Checksum = Checksum + Val("&H" & Mid(InFileLine, (2 * i) + 2, 2))
                Next i
            
                If (Checksum And 255) <> 0 Then
                    ValidateHEXFile = -3
                    InFile.Close
                    Exit Function
                End If
            Case Asc(" "), Asc(vbTab), Asc(vbCr), Asc(vbLf)
            Case Else
                ValidateHEXFile = -4
                InFile.Close
                Exit Function
        End Select
        
        If AddrCode = 1 Then
            Exit Do
        End If
        
        If InFile.AtEndOfStream = True Then
            ValidateHEXFile = -5
            InFile.Close
            Exit Function
        End If
    Loop
    
    If ValidateHEXFile <> -2 Then
        ValidateHEXFile = 1
    End If
    
    InFile.Close
    Exit Function
    
ErrorHandler:
    Err.Clear
    ValidateHEXFile = -6
    InFile.Close
End Function



Function ConvertHEX(InHEXFile As String, OutHEXFile As String) As Integer
    Dim BufferData(256) As Byte
    Dim BufferCount As Integer
    Dim Checksum As Integer
    Dim InFileLine As String
    Dim OutFileLine As String
    Dim DataString As String
    Dim DataCount As Integer
    Dim DataCode As Integer
    Dim address As Integer
    Dim HighAddress As Long
    Dim DataStr As String
    Dim NewAddr As Long

    'Open file objects
    Set fs = CreateObject("Scripting.FileSystemObject")
    ChDir VB.App.Path
    Set InFile = fs.OpenTextFile(InHEXFile, 1, False, 0)
    Set OutFile = fs.CreateTextFile(OutHEXFile, True)


    Do While InFile.AtEndOfStream <> True
        InFileLine = InFile.ReadLine
        
        If Mid(InFileLine, 1, 1) = ":" Then
            DataCount = Val("&H" & Mid(InFileLine, 2, 2))
            DataCode = Val("&H" & Mid(InFileLine, 8, 2))
            address = Val("&H" & Mid(InFileLine, 4, 4)) And LOWER_WORD_MASK
            DataStr = Mid(InFileLine, 10, DataCount * 2)
            
            
            Select Case DataCode
                Case 0
                    For i = 0 To DataCount - 1
                        BufferData(i) = Val("&H" & Mid(DataStr, (i * 2) + 1, 2))
                    Next i
                    
                
                Case 1
                    Exit Do
                Case 4
                    HighAddress = Val("&H" & DataStr)
            
            End Select
        End If
    
    
    Loop


    InFile.Close
    OutFile.Close
End Function



Public Function ImportP24HEXFile(InHEXFile As String) As Integer
    
    Dim LineAddrHigh As Long
    Dim LineDataCount As Byte
    Dim LineAddr As Long
    Dim LineCode As Byte
    
    Dim fileArray() As String
    Dim tempStr As String
    Dim fileIndex As Long
    Dim hexArray() As HEXDATA
    Dim RowData(255) As Byte
    Dim RowIndex As Integer
    Dim j As Integer
    Dim i As Integer
    Dim emptyRow As Boolean
    Dim OutLine As String
          
    Dim OverflowArray(16) As Byte
    Dim OverflowLen As Byte

    'Examine the HEX file for incompatability
    ImportP24HEXFile = ValidateHEXFile(InHEXFile)
    If ImportP24HEXFile < 0 Then
        MsgBox (ImportP24HEXFile)
        Exit Function
    End If
    
    'Create files for each memory type & open input hex file
    Set fs = CreateObject("Scripting.FileSystemObject")
    Set InFile = fs.OpenTextFile(InHEXFile, 1, False, 0)
    Set PMOut = fs.CreateTextFile(VB.App.Path & "\" & PicBootS.ProgMemFile, True)
    Set EEOut = fs.CreateTextFile(VB.App.Path & "\" & PicBootS.EEDataFile, True)
    Set CFGOut = fs.CreateTextFile(VB.App.Path & "\" & PicBootS.ConfigFile, True)

    'Read in hex file & create array of file lines then close file
    tempStr = InFile.ReadAll()
    fileArray = Split(Left(tempStr, Len(tempStr) - 2), vbCrLf) 'remove last CrLf
    InFile.Close
    
    'Create array of hex data from input file strings
    ReDim hexArray(UBound(fileArray)) As HEXDATA
    j = 0
    For i = 0 To UBound(fileArray)
        DoEvents
            
        LineDataCount = Val("&H" & Mid(fileArray(i), 2, 2))
        LineAddr = Val("&H" & Mid(fileArray(i), 4, 4) & "&") And LOWER_WORD_MASK
        LineCode = Val("&H" & Mid(fileArray(i), 8, 2))
        LineData = Mid(fileArray(i), 10, (LineDataCount * 2))
        
        Select Case LineCode
            Case 0  'data
                hexArray(j).address = (LineAddrHigh * 65536) + (LineAddr And LOWER_WORD_MASK)
                hexArray(j).data = Mid(fileArray(i), 10, (LineDataCount * 2))
                hexArray(j).datLen = LineDataCount
                
                j = j + 1
            Case 1  'eof
                Exit For
            Case 4  'extended address
                LineAddrHigh = (Val("&H" & Mid(fileArray(i), 10, 4) & "&") And LOWER_WORD_MASK)
        End Select
    Next i
    
    'Resize hex data array to save memory
    ReDim Preserve hexArray(j - 1) As HEXDATA
    
    'Sort hex data array by address
    QuickSortHex hexArray, LBound(hexArray), UBound(hexArray)
    
    'Init data array with 0xFF (init phantom byte to 0)
    For j = 0 To 255
        If ((j + 1) Mod 4 = 0) Then
            RowData(j) = 0
        Else
            RowData(j) = 255
        End If
    Next j

    'Loop through hex data writing it to appropriate file
    i = 0
    RowStartAddr = hexArray(1).address And ROW_START_MASK
    emptyRow = True
    Do While i < UBound(hexArray) + 1
        DoEvents
          
        LineAddrHigh = (hexArray(i).address And UPPER_BYTE_MASK2) / 65536
        Select Case LineAddrHigh
            Case 0 To 253           ' regular program memory
                
                'Is all of current data in new row?
                If (hexArray(i).address - RowStartAddr) > (255) Then
                
                    'Next data is in new Row, so write old row to file if not empty
                    OutAddr = RowStartAddr
                    j = 0
                    If Not emptyRow Then
                        Do While j < 256
                            
                            'Built a formatted line of data
                            If j Mod 16 = 0 Then
                                OutLine = Dec2Hex(OutAddr, 6) & " "
                            End If
                            
                            OutLine = OutLine & Dec2Hex(RowData(j), 2) & " "
                            OutAddr = OutAddr + 1
                            j = j + 1
                                                        
                            If j Mod 16 = 0 And j <> 0 Then
                                PMOut.WriteLine (OutLine)
                            End If
                        Loop
                        
                        emptyRow = True
                    End If
                    
                    'start new row
                    RowStartAddr = hexArray(i).address And ROW_START_MASK
                    For j = 0 To 255
                        If ((j + 1) Mod 4 = 0) Then
                            RowData(j) = 0
                        Else
                            RowData(j) = 255
                        End If
                    Next j
                    
                    'initialize row with overflow of last line, if any
                    For j = 0 To OverflowLen - 1
                        RowData(j) = OverflowArray(j)
                            
                        'If non-erased data is present, row is not empty
                        If (j + 1) Mod 4 <> 0 Then
                            If OverflowArray(j) <> 255 Then
                                emptyRow = False
                            End If
                        End If
                    Next j
                    
                    OverflowLen = 0

                End If
                
                'Is a portion of current data in new row?
                If (hexArray(i).address + hexArray(i).datLen - RowStartAddr) > 255 Then

                    'Store data in temporary array to use in next row
                    OverflowLen = (LOWER_BYTE_MASK And hexArray(i).address) + hexArray(i).datLen - 256
                    hexArray(i).datLen = hexArray(i).datLen - OverflowLen
                    
                    For j = 0 To OverflowLen - 1
                        OverflowArray(j) = Val("&H" & Mid(hexArray(i).data, j * 2 + 1 + hexArray(i).datLen * 2, 2))
                    Next j
                    
                End If
                
                
                'get current data
                RowIndex = hexArray(i).address And LOWER_BYTE_MASK
                For j = 0 To hexArray(i).datLen - 1
                    RowData(RowIndex) = Val("&H" & Mid(hexArray(i).data, j * 2 + 1, 2))
                    RowIndex = RowIndex + 1
                    
                    'If non-erased data is present, row is not empty
                    If (j + 1) Mod 4 <> 0 Then
                        If Val("&H" & Mid(hexArray(i).data, j * 2 + 1, 2)) <> 255 Then
                            emptyRow = False
                        End If
                    End If
                Next j
                
               
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
                
                EEOut.WriteLine (OutLine)
                    
                    
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
                
                CFGOut.WriteLine (OutLine)
                
                   
        End Select
        
        i = i + 1
                 
    Loop
    
    'Write last row of PM if it isn't empty
    OutAddr = RowStartAddr
    j = 0
    If Not emptyRow Then
        Do While j < 256
            
            'Built a formatted line of data
            If j Mod 16 = 0 Then
                OutLine = Dec2Hex(OutAddr, 6) & " "
            End If
            
            OutLine = OutLine & Dec2Hex(RowData(j), 2) & " "
            OutAddr = OutAddr + 1
            j = j + 1
                                        
            If j Mod 16 = 0 And j <> 0 Then
                PMOut.WriteLine (OutLine)
            End If
        Loop
        
    End If
                    
    PMOut.Close
    EEOut.Close
    CFGOut.Close
    
End Function

Public Sub QuickSortHex(hexArray() As HEXDATA, inLow As Long, inHi As Long)
      
   Dim pivot   As String
   Dim tmpSwap As HEXDATA
   Dim tmpLow  As Long
   Dim tmpHi   As Long
    
   tmpLow = inLow
   tmpHi = inHi
   
   pivot = hexArray((inLow + inHi) \ 2).address
  
   While (tmpLow <= tmpHi)
      While (hexArray(tmpLow).address < pivot And tmpLow < inHi)
         tmpLow = tmpLow + 1
      Wend
      
      While (pivot < hexArray(tmpHi).address And tmpHi > inLow)
         tmpHi = tmpHi - 1
      Wend

      If (tmpLow <= tmpHi) Then
         tmpSwap = hexArray(tmpLow)
         hexArray(tmpLow) = hexArray(tmpHi)
         hexArray(tmpHi) = tmpSwap
         tmpLow = tmpLow + 1
         tmpHi = tmpHi - 1
      End If
   
   Wend
  
   If (inLow < tmpHi) Then QuickSortHex hexArray, inLow, tmpHi
   If (tmpLow < inHi) Then QuickSortHex hexArray, tmpLow, inHi
  
End Sub
