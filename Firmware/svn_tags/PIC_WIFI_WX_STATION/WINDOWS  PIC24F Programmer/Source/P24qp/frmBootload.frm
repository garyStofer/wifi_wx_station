VERSION 5.00
Object = "{831FDD16-0C5C-11D2-A9FC-0000F8754DA1}#2.0#0"; "MSCOMCTL.OCX"
Object = "{F9043C88-F6F2-101A-A3C9-08002B2F49FB}#1.2#0"; "comdlg32.ocx"
Begin VB.Form frmBootload 
   Caption         =   "PIC24F Quick Programmer"
   ClientHeight    =   1620
   ClientLeft      =   165
   ClientTop       =   450
   ClientWidth     =   4875
   Icon            =   "frmBootload.frx":0000
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   ScaleHeight     =   1620
   ScaleWidth      =   4875
   StartUpPosition =   3  'Windows Default
   Begin VB.CheckBox cDataEE 
      Caption         =   "Data EE"
      Height          =   255
      Left            =   120
      TabIndex        =   5
      Top             =   840
      Width           =   3975
   End
   Begin VB.CheckBox cConfig 
      Caption         =   "Configuration Bits (Warning: Config bits not verified)"
      Height          =   255
      Left            =   120
      TabIndex        =   4
      Top             =   1080
      Width           =   3975
   End
   Begin VB.CheckBox cProgMem 
      Caption         =   "Program Memory"
      Height          =   255
      Left            =   120
      TabIndex        =   3
      Top             =   360
      Width           =   3975
   End
   Begin VB.CheckBox cFlashConfig 
      Caption         =   "Preserve Flash Configuration Words on Erase"
      Height          =   255
      Left            =   360
      TabIndex        =   2
      Top             =   600
      Width           =   3975
   End
   Begin MSComDlg.CommonDialog CommonDialog1 
      Left            =   240
      Top             =   1440
      _ExtentX        =   847
      _ExtentY        =   847
      _Version        =   393216
   End
   Begin MSComctlLib.ImageList ImageList2 
      Left            =   840
      Top             =   1440
      _ExtentX        =   1005
      _ExtentY        =   1005
      BackColor       =   -2147483643
      ImageWidth      =   16
      ImageHeight     =   16
      MaskColor       =   16711935
      _Version        =   393216
      BeginProperty Images {2C247F25-8591-11D1-B16A-00C0F0283628} 
         NumListImages   =   10
         BeginProperty ListImage1 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmBootload.frx":030A
            Key             =   ""
         EndProperty
         BeginProperty ListImage2 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmBootload.frx":065E
            Key             =   ""
         EndProperty
         BeginProperty ListImage3 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmBootload.frx":09B2
            Key             =   ""
         EndProperty
         BeginProperty ListImage4 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmBootload.frx":0D06
            Key             =   ""
         EndProperty
         BeginProperty ListImage5 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmBootload.frx":105A
            Key             =   ""
         EndProperty
         BeginProperty ListImage6 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmBootload.frx":13AE
            Key             =   ""
         EndProperty
         BeginProperty ListImage7 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmBootload.frx":1702
            Key             =   ""
         EndProperty
         BeginProperty ListImage8 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmBootload.frx":1A56
            Key             =   ""
         EndProperty
         BeginProperty ListImage9 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmBootload.frx":1DAA
            Key             =   ""
         EndProperty
         BeginProperty ListImage10 {2C247F27-8591-11D1-B16A-00C0F0283628} 
            Picture         =   "frmBootload.frx":20FE
            Key             =   ""
         EndProperty
      EndProperty
   End
   Begin MSComctlLib.Toolbar Toolbar1 
      Align           =   1  'Align Top
      Height          =   360
      Left            =   0
      TabIndex        =   1
      Top             =   0
      Width           =   4875
      _ExtentX        =   8599
      _ExtentY        =   635
      ButtonWidth     =   609
      ButtonHeight    =   582
      AllowCustomize  =   0   'False
      Appearance      =   1
      Style           =   1
      ImageList       =   "ImageList2"
      _Version        =   393216
      BeginProperty Buttons {66833FE8-8583-11D1-B16A-00C0F0283628} 
         NumButtons      =   14
         BeginProperty Button1 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Open"
            Object.ToolTipText     =   "Open HEX File"
            ImageIndex      =   1
         EndProperty
         BeginProperty Button2 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Save"
            Object.ToolTipText     =   "Save HEX File"
            ImageIndex      =   2
         EndProperty
         BeginProperty Button3 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Style           =   3
         EndProperty
         BeginProperty Button4 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Clear"
            Object.ToolTipText     =   "Clear Memory"
            ImageIndex      =   3
         EndProperty
         BeginProperty Button5 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "View"
            Object.ToolTipText     =   "View Memory"
            ImageIndex      =   4
         EndProperty
         BeginProperty Button6 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Style           =   3
         EndProperty
         BeginProperty Button7 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Abort"
            Object.ToolTipText     =   "Abort Operation"
            ImageIndex      =   5
         EndProperty
         BeginProperty Button8 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Style           =   3
         EndProperty
         BeginProperty Button9 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Connect"
            Object.ToolTipText     =   "Connect to Device"
            ImageIndex      =   6
            Style           =   1
         EndProperty
         BeginProperty Button10 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Read"
            Object.ToolTipText     =   "Read Device"
            ImageIndex      =   7
         EndProperty
         BeginProperty Button11 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Write"
            Object.ToolTipText     =   "Write Device"
            ImageIndex      =   8
         EndProperty
         BeginProperty Button12 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Erase"
            Object.ToolTipText     =   "Erase Device"
            ImageIndex      =   9
         EndProperty
         BeginProperty Button13 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Style           =   3
         EndProperty
         BeginProperty Button14 {66833FEA-8583-11D1-B16A-00C0F0283628} 
            Key             =   "Run"
            Object.ToolTipText     =   "Normal Execution Mode"
            ImageIndex      =   10
         EndProperty
      EndProperty
   End
   Begin MSComctlLib.StatusBar StatusBar1 
      Align           =   2  'Align Bottom
      Height          =   255
      Left            =   0
      TabIndex        =   0
      Top             =   1365
      Width           =   4875
      _ExtentX        =   8599
      _ExtentY        =   450
      _Version        =   393216
      BeginProperty Panels {8E3867A5-8586-11D1-B16A-00C0F0283628} 
         NumPanels       =   5
         BeginProperty Panel1 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            AutoSize        =   1
            Object.Width           =   3995
            MinWidth        =   1058
            Text            =   "Status"
            TextSave        =   "Status"
            Key             =   "PStatus"
            Object.ToolTipText     =   "Right click for memory read/write settings."
         EndProperty
         BeginProperty Panel2 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            Alignment       =   1
            AutoSize        =   2
            Object.Width           =   556
            MinWidth        =   529
            Text            =   "NA"
            TextSave        =   "NA"
            Key             =   "FirmVer"
            Object.ToolTipText     =   "Firmware version."
         EndProperty
         BeginProperty Panel3 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            Alignment       =   1
            AutoSize        =   2
            Object.Width           =   1693
            MinWidth        =   706
            Text            =   "UNKNOWN"
            TextSave        =   "UNKNOWN"
            Object.ToolTipText     =   "PIC device, right click to select."
         EndProperty
         BeginProperty Panel4 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            Alignment       =   1
            AutoSize        =   2
            Object.Width           =   953
            MinWidth        =   706
            Text            =   "COM1"
            TextSave        =   "COM1"
            Key             =   "CommPort"
            Object.ToolTipText     =   "Right click to change COM port."
         EndProperty
         BeginProperty Panel5 {8E3867AB-8586-11D1-B16A-00C0F0283628} 
            Alignment       =   1
            AutoSize        =   2
            Object.Width           =   794
            MinWidth        =   706
            Text            =   "9600"
            TextSave        =   "9600"
            Key             =   "BitRate"
            Object.ToolTipText     =   "Right click to set bit rate."
         EndProperty
      EndProperty
   End
   Begin VB.Menu M_PortSettings 
      Caption         =   "PortSettings"
      Visible         =   0   'False
      Begin VB.Menu M_FPPort 
         Caption         =   "COM1"
         Checked         =   -1  'True
         Index           =   1
      End
      Begin VB.Menu M_FPPort 
         Caption         =   "COM2"
         Index           =   2
      End
      Begin VB.Menu M_FPPort 
         Caption         =   "COM3"
         Index           =   3
      End
      Begin VB.Menu M_FPPort 
         Caption         =   "COM4"
         Index           =   4
      End
      Begin VB.Menu M_FPPort 
         Caption         =   "COM5"
         Index           =   5
      End
      Begin VB.Menu M_FPPort 
         Caption         =   "COM6"
         Index           =   6
      End
      Begin VB.Menu M_FPPort 
         Caption         =   "COM7"
         Index           =   7
      End
      Begin VB.Menu M_FPPort 
         Caption         =   "COM8"
         Index           =   8
      End
      Begin VB.Menu M_FPPort 
         Caption         =   "COM9"
         Index           =   9
      End
      Begin VB.Menu M_FPPort 
         Caption         =   "Other..."
         Index           =   10
      End
   End
   Begin VB.Menu M_BitRateSettings 
      Caption         =   "BitRatetSettings"
      Visible         =   0   'False
      Begin VB.Menu M_FPBaud 
         Caption         =   "1200"
         Index           =   1
      End
      Begin VB.Menu M_FPBaud 
         Caption         =   "2400"
         Index           =   2
      End
      Begin VB.Menu M_FPBaud 
         Caption         =   "4800"
         Index           =   3
      End
      Begin VB.Menu M_FPBaud 
         Caption         =   "9600"
         Checked         =   -1  'True
         Index           =   4
      End
      Begin VB.Menu M_FPBaud 
         Caption         =   "19200"
         Index           =   5
      End
      Begin VB.Menu M_FPBaud 
         Caption         =   "38400"
         Index           =   6
      End
      Begin VB.Menu M_FPBaud 
         Caption         =   "57600"
         Index           =   7
      End
      Begin VB.Menu M_FPBaud 
         Caption         =   "115200"
         Index           =   8
      End
   End
   Begin VB.Menu M_Program 
      Caption         =   "Program"
      Visible         =   0   'False
      Begin VB.Menu M_PDevSelector 
         Caption         =   "Device Selector"
      End
      Begin VB.Menu space104 
         Caption         =   "-"
      End
      Begin VB.Menu M_MemAccess 
         Caption         =   "FLASH"
         Index           =   1
      End
      Begin VB.Menu M_MemAccess 
         Caption         =   "EEDATA"
         Index           =   2
      End
      Begin VB.Menu M_MemAccess 
         Caption         =   "CONFIG"
         Index           =   3
      End
      Begin VB.Menu space102 
         Caption         =   "-"
      End
      Begin VB.Menu M_PSendCfg 
         Caption         =   "Send Config"
      End
      Begin VB.Menu space101 
         Caption         =   "-"
      End
      Begin VB.Menu M_About 
         Caption         =   "About"
      End
   End
End
Attribute VB_Name = "frmBootload"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False


Const STATUS_NOT_CON As String = "Not connected..."
Const STATUS_CONNECTING As String = "Connecting..."
Const STATUS_DEVICE_FOUND As String = " detected..."
Const STATUS_DATA_FILE_NOT_FOUND As String = "Data file not found..."
Const STATUS_FAILED_TO_OPEN_PORT As String = "Failed to open port..."
Const STATUS_NO_VERSION_INFO As String = "No firmware version available..."
Const STATUS_FOUND_DEVICE As String = "Device found..."
Const STATUS_NO_DEVICE As String = "Unable to connect to device..."
Const STATUS_READ_FAILURE As String = "Failed to read device..."
Const STATUS_WRITE_FAILURE As String = "Failed to write device..."
Const STATUS_ABORT As String = "Operation aborted..."
Const STATUS_FINISHED As String = "Finished operation..."
Const STATUS_VERIFY_ERROR As String = "Verify error received..."
Const STATUS_RUNMODE_SET As String = "Run mode is set..."
Const STATUS_HEX_FORMAT As String = "HEX file not padded properly..."
Const STATUS_HEX_IMPORTED As String = "HEX file imported..."
Const STATUS_INVALID_HEX As String = "Invalid HEX file..."
Const STATUS_HEX_EXPORTED As String = "HEX file exported..."
Const STATUS_VERIFYOK_ERROR As String = "Verify Ok command failed..."


Const MODE_NOT_CONNECTED As Integer = 0
Const MODE_CONNECTED_IDLE As Integer = 1
Const MODE_WORKING As Integer = 2
Const MODE_DONE As Integer = 3

Const PANEL_STATUS As Integer = 1
Const PANEL_FWVER As Integer = 2
Const PANEL_DEVICE As Integer = 3
Const PANEL_PORT As Integer = 4
Const PANEL_BITRATE As Integer = 5


'Flag used for a
Dim PanelClicked As Integer
Dim HideToolFlag As Byte




Private Sub cConfig_Click()
    M_MemAccess(3).Checked = cConfig.Value
End Sub

Private Sub cDataEE_Click()
    M_MemAccess(2).Checked = cDataEE.Value
End Sub

Private Sub cProgMem_Click()
    M_MemAccess(1).Checked = cProgMem.Value
    If PicBootS.DeviceType = 2 Then
        cFlashConfig.Enabled = cProgMem.Value
    End If
End Sub

Private Sub M_PDevSelector_Click()
    DisconnectDev

    dSelectDevice.Cm_DevList.ListIndex = 0
    dSelectDevice.Show vbModal, frmBootload
End Sub


Private Sub M_PSendCfg_Click()
    dWriteFuses.Show vbModal, frmBootload
End Sub




Private Sub StatusBar1_MouseUp(Button As Integer, Shift As Integer, x As Single, y As Single)
    If Button = 2 Then
        If PanelClicked = 1 Then
            PopupMenu M_Program, vbPopupMenuRightButton
        End If
    
        If PanelClicked = 3 Then
            M_PDevSelector_Click
        End If
    
        If PanelClicked = 4 Then
            PopupMenu M_PortSettings, vbPopupMenuRightButton
        End If
    
        If PanelClicked = 5 Then
            PopupMenu M_BitRateSettings, vbPopupMenuRightButton
        End If
    End If
End Sub

Private Sub StatusBar1_PanelClick(ByVal Panel As Panel)
    PanelClicked = Panel.Index
End Sub




'******************************************************************************
'Main Form related functions
'******************************************************************************
Private Sub Form_Load()

    On Error GoTo ErrorHandler

    'Set the size
    Me.Height = Toolbar1.Height + StatusBar1.Height + cFlashConfig.Height * 4 + 400
    Me.Width = Toolbar1.Width + 1000
                
    SetDisplayMode MODE_NOT_CONNECTED
    
    PicBootS.ProgMemFile = GetSetting("PIC24FBOOT", "progmem")
    PicBootS.EEDataFile = GetSetting("PIC24FBOOT", "eedata")
    PicBootS.ConfigFile = GetSetting("PIC24FBOOT", "config")
    PicBootS.ErrorLogFile = GetSetting("PIC24FBOOT", "errorlog")
    PicBootS.CommTimeOut = Val(GetSetting("PIC24FBOOT", "CommTimeOut"))
    PicBootS.DebugLevel = Val(GetSetting("PIC24FBOOT", "debuglevel"))
    PicBootS.DeviceMode = Val(GetSetting("PIC24FBOOT", "devicemode"))
    PicBootS.MaxRetry = Val(GetSetting("PIC24FBOOT", "maxretry"))
    PicBootS.EditorFile = GetSetting("PIC24FBOOT", "editor")
    PicBootS.UserResetVector = CLng("&H" & "0" & GetSetting("PIC24FBOOT", "userresetvector"))
    PicBootS.BootDelayAddr = CLng("&H" & "0" & GetSetting("PIC24FBOOT", "bootdelay"))
    '***MODIFIED FOR AES: Read AES setting out of .ini file to see if encryption is enabled
    PicBootS.AESEnable = CBool(GetSetting("PIC24FBOOT", "AESEnable"))

    '***MODIFIED FOR AES: When using encryption QP must know bootloader location in case it falls
    'inside an otherwise valid 16-byte block.
    If PicBootS.AESEnable Then
        PicBootS.BootLoadAddrH = CLng("&H" & "0" & GetSetting("PIC24FBOOT", "bootaddrhi"))
        PicBootS.BootLoadAddrL = CLng("&H" & "0" & GetSetting("PIC24FBOOT", "bootaddrlo"))
    End If
    If CInt(GetSetting("PIC24FBOOT", "selectdevwin")) Then
        dSelectDevice.Cm_DevList.ListIndex = 0
        dSelectDevice.Show vbModal, frmBootload
    End If
        
    PicBootS.ProgMemAddrH = &H200
    PicBootS.ProgMemAddrL = &H200
    PicBootS.EEDataAddrH = 0
    PicBootS.EEDataAddrL = 0
    PicBootS.ConfigAddrH = &H300000
    PicBootS.ConfigAddrL = &H300000
    
       
    MyIndex = GetSetting("PIC24FBOOT", "portindex")
    M_FPPort_Click (CInt(MyIndex))
    MyIndex = GetSetting("PIC24FBOOT", "bitrateindex")
    M_FPBaud_Click (CInt(MyIndex))
    
    StatusBar1.Panels(PANEL_STATUS).Text = STATUS_NOT_CON
    
    cFlashConfig.Enabled = False
    
    Exit Sub
    
ErrorHandler:
    
    StatusBar1.Panels(PANEL_STATUS).Text = "Core error:  " & Err.Description
    Err.Clear
End Sub


Private Sub Form_Unload(Cancel As Integer)
    'Close port if open
    If PicBootS.PortHandle > 0 Then
        ClosePIC (PicBootS.PortHandle)
        PicBootS.PortHandle = 0
    End If

    'Kill Fuse configurator
    Unload dWriteFuses
End Sub


Private Sub Form_Resize()

    On Error GoTo ErrorHandler
   
    If Me.Height < 2000 Then
        Me.Height = 2000
    End If
    If Me.Width < 5500 Then
        Me.Width = 5500
    End If
    
    Exit Sub
ErrorHandler:
    Err.Clear

End Sub
'******************************************************************************



Private Sub ConnectToPIC()
    Dim TempReturn As String
    Dim RetStat As Integer
    Dim picb As PIC
    Dim DevID(20) As Byte
        
    On Error GoTo ErrorHandler

    
    If PicBootS.PortHandle <= 0 Then
        PicBootS.PortHandle = OpenPIC(PicBootS.CommPort, PicBootS.BitRate, PicBootS.CommTimeOut)
    End If
    If PicBootS.PortHandle < 0 Then
        StatusBar1.Panels(PANEL_STATUS) = STATUS_FAILED_TO_OPEN_PORT
        Toolbar1.Buttons(9).Value = tbrUnpressed
        Exit Sub
    End If
    
    StatusBar1.Panels(PANEL_STATUS).Text = STATUS_CONNECTING
    
    'Read associated device name
    If PicBootS.DeviceMode = 0 Then 'manual or automatic
        
        PicBootS.DeviceCode = ReadDeviceID
        
        If PicBootS.DeviceCode = 0 Then
            StatusBar1.Panels(PANEL_STATUS) = STATUS_NO_DEVICE
            SetDisplayMode MODE_NOT_CONNECTED
            Exit Sub
        End If
        
        PicBootS.DeviceName = GetSetting("DEVICELIST", PicBootS.DeviceCode)
        
        If PicBootS.DeviceName = "" Then
            PicBootS.DeviceName = GetSetting("DEVICELIST", 0) 'PICUNKNOWN
        End If
        
    End If
    
    
    'Get firmware version
    StatusBar1.Panels(PANEL_FWVER) = ReadVersion
    If StatusBar1.Panels(PANEL_FWVER) = Empty Then
        StatusBar1.Panels(PANEL_STATUS) = STATUS_NO_VERSION_INFO
    End If


    'Read in the memory ranges
    PicBootS.ProgMemAddrL = CLng("&H" & "0" & GetSetting(PicBootS.DeviceName, "pmrangelow"))
    PicBootS.ProgMemAddrH = CLng("&H" & "0" & GetSetting(PicBootS.DeviceName, "pmrangehigh"))
    PicBootS.EEDataAddrL = CLng("&H" & "0" & GetSetting(PicBootS.DeviceName, "eerangelow"))
    PicBootS.EEDataAddrH = CLng("&H" & "0" & GetSetting(PicBootS.DeviceName, "eerangehigh"))
    PicBootS.ConfigAddrL = CLng("&H" & "0" & GetSetting(PicBootS.DeviceName, "cfgrangelow"))
    PicBootS.ConfigAddrH = CLng("&H" & "0" & GetSetting(PicBootS.DeviceName, "cfgrangehigh"))
   
    'Grab device specific UserResetVector and BootDelay locations if defined, otherwise use PIC24FBOOT defaults
    If GetSetting(PicBootS.DeviceName, "userresetvector") <> "" Then
        PicBootS.UserResetVector = CLng("&H" & "0" & GetSetting(PicBootS.DeviceName, "userresetvector"))
    End If
    If GetSetting(PicBootS.DeviceName, "bootdelay") <> "" Then
        PicBootS.BootDelayAddr = CLng("&H" & "0" & GetSetting(PicBootS.DeviceName, "bootdelay"))
    End If
      
    PicBootS.DevBytesPerAddr = Val(GetSetting(PicBootS.DeviceName, "bytesperaddr"))
    PicBootS.MaxPacketSize = Val(GetSetting(PicBootS.DeviceName, "maxpacketsize"))
    PicBootS.DeviceErsBlock = Val(GetSetting(PicBootS.DeviceName, "eraseblock"))
    PicBootS.DeviceRdBlock = Val(GetSetting(PicBootS.DeviceName, "readblock"))
    PicBootS.DeviceWrtBlock = Val(GetSetting(PicBootS.DeviceName, "writeblock"))
    PicBootS.DeviceType = Val(GetSetting(PicBootS.DeviceName, "devicetype"))
    

    '*** AES MODIFICATIONS: Cannot read reset vector due to encryption.
    '*** Bootloader must protect its own reset vector
    If PicBootS.AESEnable = False Then
        'Read in bootloader reset vector
        'read boot reset vector before erasing
        DevID(0) = 1 'command
        DevID(1) = 2

        DevID(2) = 0
        DevID(3) = 0
        DevID(4) = 0
        
        'Go get some data
        RetStat = SendGetPacket(PicBootS.PortHandle, DevID(0), 5, 255, 5)
        If RetStat < 0 Then
            frmBootload.StatusBar1.Panels(1).Text = "Reset Vector not read"
        Else
            PicBootS.ResetVector = ""
            For i = 0 To 7
                PicBootS.ResetVector = PicBootS.ResetVector & Dec2Hex(DevID(i + 5), 2) & " "
            Next i
        End If
        
    End If
    
    If PicBootS.DeviceType = 2 Then 'If PIC24FJ device w/ flash config words
        cFlashConfig.Enabled = True
        cFlashConfig.Value = 1
    End If

       
    'Read in the config bytes
    dWriteFuses.C_ConfigBytes.Clear
    For i = PicBootS.ConfigAddrL To PicBootS.ConfigAddrH
        TempReturn = GetSetting(PicBootS.DeviceName, Dec2Hex(CLng(i), 6))
        If StrComp(TempReturn, "") <> 0 Then
            dWriteFuses.C_ConfigBytes.AddItem TempReturn
            dWriteFuses.C_ConfigBytes.ItemData(MyCount) = i
            MyCount = MyCount + 1
        End If
    Next i
    
    StatusBar1.Panels(PANEL_DEVICE) = PicBootS.DeviceName
    StatusBar1.Panels(PANEL_STATUS) = STATUS_FOUND_DEVICE

    SetDisplayMode MODE_CONNECTED_IDLE
    
    Exit Sub

'Handle some errors
ErrorHandler:
    If Err.Description = STATUS_FAILED_TO_OPEN_PORT Then
        
    End If
    StatusBar1.Panels(PANEL_STATUS).Text = "Core error:  " & Err.Description
    Err.Clear
End Sub



Private Sub M_About_Click()
    frmAbout.Show vbModal, frmBootload
End Sub





'******************************************************************************
'Data file related functions
'******************************************************************************
Private Sub EraseDataFiles()
    
    Open VB.App.Path & "\" & PicBootS.ProgMemFile For Output As #1
    Close #1
    
    Open VB.App.Path & "\" & PicBootS.EEDataFile For Output As #1
    Close #1

    Open VB.App.Path & "\" & PicBootS.ConfigFile For Output As #1
    Close #1
End Sub


Private Sub ViewDataFiles()
    
    If M_MemAccess(1).Checked = True Then
        test = Shell(PicBootS.EditorFile & " " & VB.App.Path & "\" & PicBootS.ProgMemFile, vbNormalFocus)
    End If
    
    If M_MemAccess(2).Checked = True Then
        test = Shell(PicBootS.EditorFile & " " & VB.App.Path & "\" & PicBootS.EEDataFile, vbNormalFocus)
    End If
    
    If M_MemAccess(3).Checked = True Then
        test = Shell(PicBootS.EditorFile & " " & VB.App.Path & "\" & PicBootS.ConfigFile, vbNormalFocus)
    End If

End Sub
'******************************************************************************







'******************************************************************************
'Port related setting functions
'******************************************************************************
Private Sub M_FPBaud_Click(Index As Integer)
    
    DisconnectDev
    
    M_FPBaud(1).Checked = Not CBool(Index Xor 1)
    M_FPBaud(2).Checked = Not CBool(Index Xor 2)
    M_FPBaud(3).Checked = Not CBool(Index Xor 3)
    M_FPBaud(4).Checked = Not CBool(Index Xor 4)
    M_FPBaud(5).Checked = Not CBool(Index Xor 5)
    M_FPBaud(6).Checked = Not CBool(Index Xor 6)
    M_FPBaud(7).Checked = Not CBool(Index Xor 7)
    M_FPBaud(8).Checked = Not CBool(Index Xor 8)
    
    PicBootS.BitRate = CLng(M_FPBaud(Index).Caption)
    
    StatusBar1.Panels(PANEL_BITRATE) = M_FPBaud(Index).Caption
    
    SetDisplayMode MODE_NOT_CONNECTED
            
End Sub


Private Sub M_FPPort_Click(Index As Integer)
        
    Dim tempStr As String
        
    DisconnectDev
            
    M_FPPort(1).Checked = Not CBool(Index Xor 1)
    M_FPPort(2).Checked = Not CBool(Index Xor 2)
    M_FPPort(3).Checked = Not CBool(Index Xor 3)
    M_FPPort(4).Checked = Not CBool(Index Xor 4)
    M_FPPort(5).Checked = Not CBool(Index Xor 5)
    M_FPPort(6).Checked = Not CBool(Index Xor 6)
    M_FPPort(7).Checked = Not CBool(Index Xor 7)
    M_FPPort(8).Checked = Not CBool(Index Xor 8)
    M_FPPort(9).Checked = Not CBool(Index Xor 9)
    M_FPPort(10).Checked = Not CBool(Index Xor 10)
    
    If Index < 10 Then
        PicBootS.CommPort = "\\.\" & M_FPPort(Index).Caption
        StatusBar1.Panels(PANEL_PORT) = M_FPPort(Index).Caption
    Else
        tempStr = InputBox("Enter Port Name (e.g. COM10)", "Enter Custom Port", Mid(PicBootS.CommPort, 5))
        If tempStr = "" Then
            MsgBox ("Invalid Entry")
        Else
            PicBootS.CommPort = "\\.\" & tempStr
            StatusBar1.Panels(PANEL_PORT) = tempStr
        End If
    End If
     
    
     
    SetDisplayMode MODE_NOT_CONNECTED
        
End Sub
'******************************************************************************




Private Sub M_MemAccess_Click(Index As Integer)
    If M_MemAccess(Index).Checked = True Then
        M_MemAccess(Index).Checked = False
                    
        Select Case Index
            Case 1
                cProgMem.Value = 0
            Case 2
                cDataEE.Value = 0
            Case 3
                cConfig.Value = 0
        End Select
    Else
        M_MemAccess(Index).Checked = True
                    
        Select Case Index
            Case 1
                cProgMem.Value = 1
            Case 2
                cDataEE.Value = 1
            Case 3
                cConfig.Value = 1
        End Select

    End If


    
End Sub









'******************************************************************************
'Toolbar related functions
'******************************************************************************
Private Sub Toolbar1_ButtonClick(ByVal Button As MSComctlLib.Button)
    Dim sFile As String
    Dim ProgMemAddrH As Long
    Dim command(5) As Byte
    Dim writeFail As Boolean

    Select Case Button.Key
        Case "Open"
                
            With CommonDialog1
                .DialogTitle = "Open HEX File"
                .CancelError = False
                .Flags = cdlOFNHideReadOnly
                .Filter = "INHEX32 Files (*.HEX)|*.HEX|All Files (*.*)|*.*"
                .ShowOpen
                If Len(.FileName) = 0 Then
                    Exit Sub
                End If
            
                PicBootS.InFileName = .FileName
                .FileName = ""
            End With


            RetStat = ImportP24HEXFile(PicBootS.InFileName)


            If RetStat = -2 Then
                StatusBar1.Panels(PANEL_STATUS).Text = STATUS_HEX_FORMAT
            Else
                If RetStat > 0 Then
                    StatusBar1.Panels(PANEL_STATUS).Text = STATUS_HEX_IMPORTED
                Else
                    StatusBar1.Panels(PANEL_STATUS).Text = STATUS_INVALID_HEX
                End If
            End If
            
        Case "Save"
            With CommonDialog1
                .DialogTitle = "Save HEX File"
                .CancelError = False
                .Flags = cdlOFNHideReadOnly
                .Filter = "INHEX32 Files (*.HEX)|*.HEX|All Files (*.*)|*.*"
                .ShowSave
                If Len(.FileName) = 0 Then
                    Exit Sub
                End If
                PicBootS.OutFileName = .FileName
                .FileName = ""
            End With


            ExportP24HEXFile PicBootS.OutFileName


            StatusBar1.Panels(PANEL_STATUS).Text = STATUS_HEX_EXPORTED
        
        
        Case "Clear"
            EraseDataFiles
            
        Case "View"
            ViewDataFiles
            
        Case "Abort"
            AbortFlag = 0
            
        Case "Connect"
            If Toolbar1.Buttons(9).Value = tbrUnpressed Then
                DisconnectDev
            Else
                ConnectToPIC
            End If
            
        Case "Read"
            frmBootload.MousePointer = 13
            SetDisplayMode MODE_WORKING
            
            'read program memory
            If M_MemAccess(1).Checked = True Then
                Select Case ReadRangeDevMem(PicBootS.ProgMemAddrL, PicBootS.ProgMemAddrH, PicBootS.DevBytesPerAddr, 1, PicBootS.ProgMemFile)
                    Case -100
                        StatusBar1.Panels(PANEL_STATUS).Text = STATUS_ABORT
                        SetDisplayMode MODE_DONE
                        frmBootload.MousePointer = 0
                        Exit Sub
                    Case 1
                        StatusBar1.Panels(PANEL_STATUS).Text = STATUS_FINISHED
                    Case Else
                        StatusBar1.Panels(PANEL_STATUS).Text = STATUS_READ_FAILURE
                End Select
            End If
                
            'read eedata
            If M_MemAccess(2).Checked = True Then
                Select Case ReadRangeDevMem(PicBootS.EEDataAddrL, PicBootS.EEDataAddrH, PicBootS.DevBytesPerAddr, 4, PicBootS.EEDataFile)
                    Case -100
                        StatusBar1.Panels(PANEL_STATUS).Text = STATUS_ABORT
                        SetDisplayMode MODE_DONE
                        frmBootload.MousePointer = 0
                        Exit Sub
                    Case 1
                        StatusBar1.Panels(PANEL_STATUS).Text = STATUS_FINISHED
                    Case Else
                        StatusBar1.Panels(PANEL_STATUS).Text = STATUS_READ_FAILURE
                End Select
            End If
            
            'read config
            If M_MemAccess(3).Checked = True Then
                Select Case ReadRangeDevMem(PicBootS.ConfigAddrL, PicBootS.ConfigAddrH, PicBootS.DevBytesPerAddr, 6, PicBootS.ConfigFile)
                    Case -100
                        StatusBar1.Panels(PANEL_STATUS).Text = STATUS_ABORT
                        SetDisplayMode MODE_DONE
                        frmBootload.MousePointer = 0
                        Exit Sub
                    Case 1
                        StatusBar1.Panels(PANEL_STATUS).Text = STATUS_FINISHED
                    Case Else
                        StatusBar1.Panels(PANEL_STATUS).Text = STATUS_READ_FAILURE
                End Select
            End If
 
                 
            SetDisplayMode MODE_DONE
            frmBootload.MousePointer = 0
        
            
        Case "Write"
            frmBootload.MousePointer = 13
            SetDisplayMode MODE_WORKING
            
            writeFail = False
            
            If M_MemAccess(1).Checked = True Then
                Select Case WriteRangeDevMem(PicBootS.DeviceWrtBlock, PicBootS.DevBytesPerAddr, 2, PicBootS.ProgMemFile)
                    Case -100
                        StatusBar1.Panels(PANEL_STATUS).Text = STATUS_ABORT
                        SetDisplayMode MODE_DONE
                        frmBootload.MousePointer = 0
                        writeFail = True
                        Exit Sub
                    Case -101
                        StatusBar1.Panels(PANEL_STATUS).Text = STATUS_VERIFY_ERROR
                        SetDisplayMode MODE_DONE
                        frmBootload.MousePointer = 0
                        test = Shell(PicBootS.EditorFile & " " & VB.App.Path & "\" & PicBootS.ErrorLogFile, vbNormalFocus)
                        writeFail = True
                        Exit Sub
                    Case 1
                        StatusBar1.Panels(PANEL_STATUS).Text = STATUS_FINISHED
           
                    Case Else
                        StatusBar1.Panels(PANEL_STATUS).Text = STATUS_WRITE_FAILURE
                        writeFail = True
                End Select
            End If
            
            If M_MemAccess(2).Checked = True Then
                Select Case WriteRangeDevMem(2, PicBootS.DevBytesPerAddr, 5, PicBootS.EEDataFile)
                    Case -100
                        StatusBar1.Panels(PANEL_STATUS).Text = STATUS_ABORT
                        SetDisplayMode MODE_DONE
                        frmBootload.MousePointer = 0
                        writeFail = True
                        Exit Sub
                    Case -101
                        StatusBar1.Panels(PANEL_STATUS).Text = STATUS_VERIFY_ERROR
                        SetDisplayMode MODE_DONE
                        frmBootload.MousePointer = 0
                        test = Shell(PicBootS.EditorFile & " " & VB.App.Path & "\" & PicBootS.ErrorLogFile, vbNormalFocus)
                        writeFail = True
                        Exit Sub
                    Case 1
                        StatusBar1.Panels(PANEL_STATUS).Text = STATUS_FINISHED
                    Case Else
                        StatusBar1.Panels(PANEL_STATUS).Text = STATUS_WRITE_FAILURE
                        writeFail = True
                End Select
            End If
            
            If M_MemAccess(3).Checked = True Then
                Select Case WriteRangeDevMem(1, PicBootS.DevBytesPerAddr, 7, PicBootS.ConfigFile)
                    Case -100
                        StatusBar1.Panels(PANEL_STATUS).Text = STATUS_ABORT
                        SetDisplayMode MODE_DONE
                        frmBootload.MousePointer = 0
                        writeFail = True
                        Exit Sub
                    Case -101
                        StatusBar1.Panels(PANEL_STATUS).Text = STATUS_VERIFY_ERROR
                        SetDisplayMode MODE_DONE
                        frmBootload.MousePointer = 0
                        test = Shell(PicBootS.EditorFile & " " & VB.App.Path & "\" & PicBootS.ErrorLogFile, vbNormalFocus)
                        writeFail = True
                        Exit Sub
                    Case 1
                        StatusBar1.Panels(PANEL_STATUS).Text = STATUS_FINISHED
                    Case Else
                        StatusBar1.Panels(PANEL_STATUS).Text = STATUS_WRITE_FAILURE
                        writeFail = True
                End Select
            End If
            
            'Send VerifyOk Command to indicate bootloading finised successfully
            If writeFail = False Then
                 
                command(0) = 8 'command
                
                RetStat = SendGetPacket(PicBootS.PortHandle, command(0), 1, 255, 5)
                If RetStat < 0 Then
                    StatusBar1.Panels(PANEL_STATUS).Text = STATUS_VERIFYOK_ERROR
                End If
            End If
            
            
            SetDisplayMode MODE_DONE
            frmBootload.MousePointer = 0
        
            
        Case "Erase"
            frmBootload.MousePointer = 13
            SetDisplayMode MODE_WORKING
            
            If M_MemAccess(1).Checked = True Then
                
                ProgMemAddrH = PicBootS.ProgMemAddrH
            
                'Don't erase last page on PIC24FJ devices if box is checked
                If cFlashConfig.Value = 1 Then
                    ProgMemAddrH = ProgMemAddrH - 1024
                End If
                
                Select Case EraseRangeDevMem(PicBootS.ProgMemAddrL, ProgMemAddrH)
                Case -100
                        StatusBar1.Panels(PANEL_STATUS).Text = STATUS_ABORT
                        SetDisplayMode MODE_DONE
                        frmBootload.MousePointer = 0
                        Exit Sub
                    Case 1
                        StatusBar1.Panels(PANEL_STATUS).Text = STATUS_FINISHED
                    Case Else
                        StatusBar1.Panels(PANEL_STATUS).Text = STATUS_WRITE_FAILURE
                End Select
            End If
                   
            SetDisplayMode MODE_DONE
            frmBootload.MousePointer = 0
                
        Case "Run"
            
            MyButtons = MsgBox("Disabling the bootloader will lock out boot mode. Be sure to have re-entry" & vbCrLf & "code within your firmware to use the bootloader in the future." & vbCrLf & vbCrLf & "Do you want to continue?", vbYesNo, "Disable Bootloader...")
            If MyButtons = vbNo Then   ' User chose Yes.
                Exit Sub   ' Perform some action.
            End If
            
            GotoRunMode
            DisconnectDev
            StatusBar1.Panels(PANEL_STATUS).Text = STATUS_RUNMODE_SET
            
    End Select
End Sub




Private Sub Toolbar1_MouseUp(Button As Integer, Shift As Integer, x As Single, y As Single)
    If Button = 2 Then
        MsConFlag = 2
        PopupMenu M_Program, vbPopupMenuRightButton
    End If
End Sub

'******************************************************************************



Private Sub DisconnectDev()

    AbortFlag = 0
    DoEvents

    'close the port
    If PicBootS.PortHandle > 0 Then
        ClosePIC (PicBootS.PortHandle)
        PicBootS.PortHandle = -1
    End If
    
    Toolbar1.Buttons(9).Value = tbrUnpressed
    StatusBar1.Panels(PANEL_STATUS).Text = STATUS_NOT_CON
    StatusBar1.Panels(PANEL_FWVER).Text = " "
    StatusBar1.Panels(PANEL_DEVICE).Text = " "

    cFlashConfig.Enabled = False

    SetDisplayMode (MODE_NOT_CONNECTED)

End Sub



Private Sub SetDisplayMode(DspMode As Integer)
    
    Select Case DspMode
        
        Case MODE_CONNECTED_IDLE
            Toolbar1.Buttons(1).Enabled = True
            Toolbar1.Buttons(2).Enabled = True
            Toolbar1.Buttons(4).Enabled = True
            Toolbar1.Buttons(5).Enabled = True
            Toolbar1.Buttons(10).Enabled = True
            Toolbar1.Buttons(11).Enabled = True
            Toolbar1.Buttons(12).Enabled = True
            Toolbar1.Buttons(14).Enabled = True
            Toolbar1.Buttons(9).Value = tbrPressed
            
            If PicBootS.DeviceType = 0 Then
                'Unknown
                M_MemAccess(1).Visible = True
                M_MemAccess(2).Visible = False
                M_MemAccess(3).Visible = False
                M_MemAccess(1).Checked = False
                M_MemAccess(2).Checked = False
                M_MemAccess(3).Checked = False
                Toolbar1.Buttons(12).Enabled = False
                M_PSendCfg.Visible = False
                space101.Visible = False
                cDataEE.Enabled = False
                cDataEE.Value = 0
                cConfig.Enabled = False
                cConfig.Value = 0
                cFlashConfig.Enabled = False
                cFlashConfig.Value = 0
                
            ElseIf PicBootS.DeviceType = 1 Then
                'PIC24F
                M_MemAccess(1).Visible = True
                M_MemAccess(2).Visible = True
                M_MemAccess(3).Visible = True
                M_MemAccess(1).Checked = True
                M_MemAccess(2).Checked = True
                M_MemAccess(3).Checked = False
                M_PSendCfg.Visible = True
                cProgMem.Enabled = True
                cProgMem.Value = 1
                cDataEE.Enabled = True
                cDataEE.Value = 1
                cConfig.Enabled = True
                cConfig.Value = 0
                cFlashConfig.Enabled = False
                cFlashConfig.Value = 0
                
            ElseIf PicBootS.DeviceType = 2 Then
                'PIC24FJ
                M_MemAccess(1).Visible = True
                M_MemAccess(2).Visible = False
                M_MemAccess(3).Visible = False
                M_MemAccess(1).Checked = True
                M_MemAccess(2).Checked = False
                M_MemAccess(3).Checked = False
                M_PSendCfg.Visible = False
                cProgMem.Enabled = True
                cProgMem.Value = 1
                cDataEE.Enabled = False
                cDataEE.Value = 0
                cConfig.Enabled = False
                cConfig.Value = 0
                cFlashConfig.Enabled = True
                cFlashConfig.Value = 1
                
            End If

        Case MODE_WORKING
            
            Toolbar1.Buttons(7).Enabled = True
            Toolbar1.Buttons(1).Enabled = False
            Toolbar1.Buttons(2).Enabled = False
            Toolbar1.Buttons(4).Enabled = False
            Toolbar1.Buttons(5).Enabled = False
            Toolbar1.Buttons(9).Value = tbrPressed
            Toolbar1.Buttons(10).Enabled = False
            Toolbar1.Buttons(11).Enabled = False
            Toolbar1.Buttons(12).Enabled = False
            Toolbar1.Buttons(14).Enabled = False
            
            For i = 1 To M_FPPort.Count
                M_FPPort(i).Enabled = False
            Next i
            
            For i = 1 To M_FPBaud.Count
                M_FPBaud(i).Enabled = False
            Next i
            
            For i = 1 To M_MemAccess.Count
                M_MemAccess(i).Enabled = False
            Next i
            
            cProgMem.Enabled = False
            cDataEE.Enabled = False
            cConfig.Enabled = False
            cFlashConfig.Enabled = False
            M_PSendCfg.Visible = False
            
            
        Case MODE_DONE
            Toolbar1.Buttons(7).Enabled = True
            Toolbar1.Buttons(1).Enabled = True
            Toolbar1.Buttons(2).Enabled = True
            Toolbar1.Buttons(4).Enabled = True
            Toolbar1.Buttons(5).Enabled = True
            Toolbar1.Buttons(9).Value = tbrPressed
            Toolbar1.Buttons(10).Enabled = True
            Toolbar1.Buttons(11).Enabled = True
            Toolbar1.Buttons(12).Enabled = True
            Toolbar1.Buttons(14).Enabled = True
            
            For i = 1 To M_FPPort.Count
                M_FPPort(i).Enabled = True
            Next i
            
            For i = 1 To M_FPBaud.Count
                M_FPBaud(i).Enabled = True
            Next i
            
            For i = 1 To M_MemAccess.Count
                M_MemAccess(i).Enabled = True
            Next i
            
            If PicBootS.DeviceType = 0 Then
                'Unknown
                M_MemAccess(1).Visible = True
                M_MemAccess(2).Visible = False
                M_MemAccess(3).Visible = False
                Toolbar1.Buttons(12).Enabled = False
                M_PSendCfg.Visible = False
                space101.Visible = False
                cDataEE.Enabled = False
                cConfig.Enabled = False
                cFlashConfig.Enabled = False
                
            ElseIf PicBootS.DeviceType = 1 Then
                'PIC24F
                M_MemAccess(1).Visible = True
                M_MemAccess(2).Visible = True
                M_MemAccess(3).Visible = True
                M_PSendCfg.Visible = True
                cProgMem.Enabled = True
                cDataEE.Enabled = True
                cConfig.Enabled = True
                cFlashConfig.Enabled = False
                
            ElseIf PicBootS.DeviceType = 2 Then
                'PIC24FJ
                M_MemAccess(1).Visible = True
                M_MemAccess(2).Visible = False
                M_MemAccess(3).Visible = False
                M_PSendCfg.Visible = False
                cProgMem.Enabled = True
                cDataEE.Enabled = False
                cConfig.Enabled = False
                cFlashConfig.Enabled = True
                
            End If
                        
                        
        Case MODE_NOT_CONNECTED
        
            Toolbar1.Buttons(1).Enabled = False
            Toolbar1.Buttons(2).Enabled = False
            Toolbar1.Buttons(10).Enabled = False
            Toolbar1.Buttons(11).Enabled = False
            Toolbar1.Buttons(12).Enabled = False
            Toolbar1.Buttons(14).Enabled = False
            Toolbar1.Buttons(9).Value = tbrUnpressed
            
            M_PSendCfg.Visible = False
            space101.Visible = False
            M_Program.Enabled = False
            
            For i = 1 To M_MemAccess.Count
                M_MemAccess(i).Checked = False
            Next i
            
            cProgMem.Value = 0
            cDataEE.Value = 0
            cConfig.Value = 0
            cFlashConfig.Value = False
            
            cProgMem.Enabled = False
            cDataEE.Enabled = False
            cConfig.Enabled = False
            cFlashConfig.Enabled = False
        
        Case Else
        
            Toolbar1.Buttons(1).Enabled = False
            Toolbar1.Buttons(2).Enabled = False
            Toolbar1.Buttons(4).Enabled = True
            Toolbar1.Buttons(5).Enabled = True
            Toolbar1.Buttons(7).Enabled = False
            Toolbar1.Buttons(9).Enabled = True
            Toolbar1.Buttons(9).Value = tbrUnpressed
            Toolbar1.Buttons(10).Enabled = False
            Toolbar1.Buttons(11).Enabled = False
            Toolbar1.Buttons(12).Enabled = False
            Toolbar1.Buttons(14).Enabled = False
            
            For i = 0 To M_FPPort.Count
                M_FPPort(i).Enabled = True
            Next i
            
            For i = 0 To M_FPBaud.Count
                M_FPBaud(i).Enabled = True
            Next i
            
            For i = 0 To M_MemAccess.Count
                M_MemAccess(i).Enabled = True
            Next i
            
            cProgMem.Enabled = True
            cDataEE.Enabled = True
            cConfig.Enabled = True
            cFlashConfig.Enabled = True
            
            M_PSendCfg.Visible = False
            space101.Visible = False
           

    End Select
 
End Sub



