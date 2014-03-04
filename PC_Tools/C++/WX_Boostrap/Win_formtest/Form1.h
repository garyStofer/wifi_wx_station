// $Id$
#pragma once

#include "Cp2104.h"


namespace Win_formtest {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace std;
	
	delegate void MyCallback(System::String ^str);	

	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)	// Constructor
		{
			System::Object^ nl;
			System::EventArgs^ nle;
	
			InitializeComponent();
 
			btnConn_Click(nl,nle);
			callback = gcnew MyCallback(this, &Form1::print_str);


		}

	public: 


	private: MyCallback ^callback;



		/// Deconstructor
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			try 
			{
				this->serialPort1->Close();
			}
			catch (Exception^ e)
			{
				this->toolStripStatusLabel1->Text = e->Message;
			}
			if (components)
			{
				delete components;
			}
		}

	
	private: System::IO::Ports::SerialPort^  serialPort1;
	private: System::Windows::Forms::Button^  btnConn;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::ComponentModel::IContainer^  components;
	private: System::Windows::Forms::StatusStrip^  statusStrip1;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel1;
	private: System::Windows::Forms::TextBox^  txtb_SSID;
	private: System::Windows::Forms::TextBox^  txtbx_PWD;
	private: System::Windows::Forms::Label^  lblSSID;
	private: System::Windows::Forms::Label^  lblPWD;
	private: System::Windows::Forms::CheckBox^  chk_WPA;
	private: System::Windows::Forms::Button^  btn_mon;
	private: System::Windows::Forms::Button^  btnProg;





	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->serialPort1 = (gcnew System::IO::Ports::SerialPort(this->components));
			this->btnConn = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			this->toolStripStatusLabel1 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->btnProg = (gcnew System::Windows::Forms::Button());
			this->txtb_SSID = (gcnew System::Windows::Forms::TextBox());
			this->txtbx_PWD = (gcnew System::Windows::Forms::TextBox());
			this->lblSSID = (gcnew System::Windows::Forms::Label());
			this->lblPWD = (gcnew System::Windows::Forms::Label());
			this->chk_WPA = (gcnew System::Windows::Forms::CheckBox());
			this->btn_mon = (gcnew System::Windows::Forms::Button());
			this->statusStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// serialPort1
			// 
			this->serialPort1->BaudRate = 38400;
			this->serialPort1->DiscardNull = true;
			this->serialPort1->ReadTimeout = 1000;
			this->serialPort1->ReceivedBytesThreshold = 5;
			// 
			// btnConn
			// 
			this->btnConn->Location = System::Drawing::Point(41, 134);
			this->btnConn->Name = L"btnConn";
			this->btnConn->Size = System::Drawing::Size(94, 23);
			this->btnConn->TabIndex = 0;
			this->btnConn->Text = L"Detect";
			this->btnConn->UseVisualStyleBackColor = true;
			this->btnConn->Click += gcnew System::EventHandler(this, &Form1::btnConn_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(12, 172);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textBox1->Size = System::Drawing::Size(449, 155);
			this->textBox1->TabIndex = 1;
			// 
			// statusStrip1
			// 
			this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->toolStripStatusLabel1});
			this->statusStrip1->Location = System::Drawing::Point(0, 350);
			this->statusStrip1->Name = L"statusStrip1";
			this->statusStrip1->Size = System::Drawing::Size(475, 22);
			this->statusStrip1->TabIndex = 2;
			// 
			// toolStripStatusLabel1
			// 
			this->toolStripStatusLabel1->Name = L"toolStripStatusLabel1";
			this->toolStripStatusLabel1->Size = System::Drawing::Size(16, 17);
			this->toolStripStatusLabel1->Text = L"   ";
			// 
			// btnProg
			// 
			this->btnProg->Enabled = false;
			this->btnProg->Location = System::Drawing::Point(201, 134);
			this->btnProg->Name = L"btnProg";
			this->btnProg->Size = System::Drawing::Size(80, 23);
			this->btnProg->TabIndex = 3;
			this->btnProg->Text = L"Program";
			this->btnProg->UseVisualStyleBackColor = true;
			this->btnProg->Click += gcnew System::EventHandler(this, &Form1::btnProg_Click);
			// 
			// txtb_SSID
			// 
			this->txtb_SSID->Location = System::Drawing::Point(139, 20);
			this->txtb_SSID->MaxLength = 32;
			this->txtb_SSID->Name = L"txtb_SSID";
			this->txtb_SSID->Size = System::Drawing::Size(224, 20);
			this->txtb_SSID->TabIndex = 4;
			this->txtb_SSID->TextChanged += gcnew System::EventHandler(this, &Form1::txtb_SSID_TextChanged);
			// 
			// txtbx_PWD
			// 
			this->txtbx_PWD->Location = System::Drawing::Point(139, 73);
			this->txtbx_PWD->MaxLength = 64;
			this->txtbx_PWD->Name = L"txtbx_PWD";
			this->txtbx_PWD->Size = System::Drawing::Size(224, 20);
			this->txtbx_PWD->TabIndex = 5;
			this->txtbx_PWD->TextChanged += gcnew System::EventHandler(this, &Form1::txtbx_PWD_TextChanged);
			// 
			// lblSSID
			// 
			this->lblSSID->AutoSize = true;
			this->lblSSID->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->lblSSID->Location = System::Drawing::Point(38, 20);
			this->lblSSID->Name = L"lblSSID";
			this->lblSSID->Size = System::Drawing::Size(47, 16);
			this->lblSSID->TabIndex = 6;
			this->lblSSID->Text = L"SSID:";
			// 
			// lblPWD
			// 
			this->lblPWD->AutoSize = true;
			this->lblPWD->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->lblPWD->Location = System::Drawing::Point(38, 73);
			this->lblPWD->Name = L"lblPWD";
			this->lblPWD->Size = System::Drawing::Size(80, 16);
			this->lblPWD->TabIndex = 7;
			this->lblPWD->Text = L"Password:";
			// 
			// chk_WPA
			// 
			this->chk_WPA->AutoSize = true;
			this->chk_WPA->Checked = true;
			this->chk_WPA->CheckState = System::Windows::Forms::CheckState::Checked;
			this->chk_WPA->Location = System::Drawing::Point(139, 50);
			this->chk_WPA->Name = L"chk_WPA";
			this->chk_WPA->Size = System::Drawing::Size(109, 17);
			this->chk_WPA->TabIndex = 9;
			this->chk_WPA->Text = L"Use WPA/WPA2";
			this->chk_WPA->UseVisualStyleBackColor = true;
			this->chk_WPA->CheckedChanged += gcnew System::EventHandler(this, &Form1::chk_WPA_CheckedChanged);
			// 
			// btn_mon
			// 
			this->btn_mon->Location = System::Drawing::Point(338, 134);
			this->btn_mon->Name = L"btn_mon";
			this->btn_mon->Size = System::Drawing::Size(75, 23);
			this->btn_mon->TabIndex = 10;
			this->btn_mon->Text = L"Monitor";
			this->btn_mon->UseVisualStyleBackColor = true;
			this->btn_mon->Click += gcnew System::EventHandler(this, &Form1::btn_mon_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(475, 372);
			this->Controls->Add(this->btn_mon);
			this->Controls->Add(this->chk_WPA);
			this->Controls->Add(this->lblPWD);
			this->Controls->Add(this->lblSSID);
			this->Controls->Add(this->txtbx_PWD);
			this->Controls->Add(this->txtb_SSID);
			this->Controls->Add(this->btnProg);
			this->Controls->Add(this->statusStrip1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->btnConn);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"Form1";
			this->Text = L"Wunder-Weather-Station Bootstrap";
			this->statusStrip1->ResumeLayout(false);
			this->statusStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private:  void print_str( System::String ^str)
	{	
		this->textBox1->AppendText(str);
	}

	private: void enable_Program_btn( void )
	{
		if ( this->serialPort1->IsOpen )
		{	
			if (this->txtb_SSID->TextLength >1)
			{
				if( this->chk_WPA->Checked == false )  
					this->btnProg->Enabled = true;
				else
				{
					if ( this->txtbx_PWD->TextLength > 1 )
						this->btnProg->Enabled = true;
					else
						this->btnProg->Enabled = false;
				}
			}
			else
				this->btnProg->Enabled = false;

		}
		else
			this->btnProg->Enabled = false;

	}

// Event handlers from here on down

	private: System::Void btnConn_Click(System::Object^  sender, System::EventArgs^  e)
	{	
		String^ S ="COM";
		int i ;
		Cp2104 cp;
		
		this->btnConn->Enabled = false;
		if (this->serialPort1->IsOpen )		// Can still be open from previous call 
		{
			try 
			{
				this->serialPort1->Close();
			}
			catch (Exception^ e)
			{
				this->toolStripStatusLabel1->Text = e->Message;
			}
		}	 
		
		try 
		{
			i = cp.GetCp2104_COM_num();
		}
		catch (Exception^ e)
		{
			this->toolStripStatusLabel1->Text = e->Message;
		}

		if ( i > 0 )
		{
			S += i;
			
			this->serialPort1->PortName = S;

			try 
			{
				this->serialPort1->Open();
			}
			catch (Exception^ e)
			{
				this->toolStripStatusLabel1->Text = e->Message;
			}
			this->toolStripStatusLabel1->Text ="Wunder-Weather-Station is detected at " + S; 
			this->textBox1->Text = this->toolStripStatusLabel1->Text;
			
			if ( this->serialPort1->IsOpen)
			{
				enable_Program_btn();
				this->btn_mon->Enabled = true;
			}
		}
		else 
		{
			this->toolStripStatusLabel1->Text = "Wunder-Weather-Station is not found.";
			this->textBox1->Text = this->toolStripStatusLabel1->Text;
			this->textBox1->AppendText("\r\n");
			this->textBox1->AppendText("Is it plugged in? Is the USB device driver installed ?");
			this->btnProg->Enabled = false;
			this->btn_mon->Enabled = false;
		}
		this->btnConn->Enabled = true;
	}

	private: System::Void btnProg_Click(System::Object^  sender, System::EventArgs^  e) 
	{
			bool conn = false;
			String^ message;
			this->btnConn->Enabled = false;
			this->btnProg->Enabled = false;
			this->btn_mon->Enabled = false;
	
			
			if ( ! this->serialPort1->IsOpen )
			{
				this->toolStripStatusLabel1->Text = "COM port is not detected yet -- Click Detect first";
				this->textBox1->Text = this->toolStripStatusLabel1->Text;
				this->btnConn->Enabled = true;
				return;
			}

			this->toolStripStatusLabel1->Text = "Connecting to Station configuration utility..." ;

			this->serialPort1->DiscardInBuffer();
			
			this->serialPort1->Write("?");
			
			for (int i=0 ; i<5; i++ )
			{
				try
				{
					message = this->serialPort1->ReadLine(); 
				}
				catch( TimeoutException^ )
				{
					break;
				}
				
				if ( message->Contains("WiFi  &  TCP-IP configuration utility" )) // Do not alter this text -- This is the key to know that we are connected
				{
					conn = true;
					break;
				}

			}
			
			
		
			if (conn)
			{
				this->toolStripStatusLabel1->Text = "Connected";
				this->textBox1->Text = this->toolStripStatusLabel1->Text;
				this->serialPort1->DiscardInBuffer();
				this->serialPort1->Write("1");			// Set SSID
				this->serialPort1->ReadByte();			// Wait for a response from the board i.e. "Enter SSID:"
         		this->serialPort1->WriteLine(this->txtb_SSID->Text); // This prompts an other menu draw
				Sleep(250);											 // Wait out the menu beeing displayed
				this->serialPort1->DiscardInBuffer();

				if ( this->chk_WPA->Checked )
				{	
					this->serialPort1->DiscardInBuffer();
					this->serialPort1->Write("2");			// Set Passphrase
					this->serialPort1->ReadByte();			// Wait for a response from the board i.e. "Enter Passphrase:"
					this->serialPort1->WriteLine(this->txtbx_PWD->Text);// This prompts an other menu draw
					Sleep(250);								// Wait out the menu beeing displayed
					this->serialPort1->DiscardInBuffer();

				}
				else
				{
					//  turn off wifi security if it was left on from earlier -- Without having to reboot factory defaults						
					this->serialPort1->Write("0");			// Clears WPA/WPA2 mode -- 
					this->serialPort1->ReadByte();			// Wait for a response
					Sleep(250);								// Wait out the menu beeing displayed
					this->serialPort1->DiscardInBuffer();
				}

				this->serialPort1->Write("S");			// This saves the parameters and reboots the device
				
				this->textBox1->Text = "SSID and Password set!\r\n";
				for (int i =0 ; i<66; i++ )
				{
					try
					{
						message = this->serialPort1->ReadLine(); 
					}
					catch( TimeoutException^ )
					{
						continue;
					}
					if ( message->Length >1)
					{
						this->textBox1->AppendText(message);
						this->textBox1->AppendText("\r\n");
					}
					if (message->Contains("Nist"))
					{
						break;
					}
				}

				this->toolStripStatusLabel1->Text = " WAIT 1 MINUTE for WiFi to establish!";
				this->textBox1->AppendText("\r\n\r\n When the green LED blinks at 1 second interval WiFi connection is established!");

			}
			else
			{
				this->toolStripStatusLabel1->Text = "Failed to connect: press+hold S1, press+release RESET, then release S1.";
				this->textBox1->Text ="Failed to connect!\r\n\r\n";
				this->textBox1->AppendText("Do the following:\r\n\r\n");
				this->textBox1->AppendText("1.)  Press and hold the S1 button on the station.\r\n");
				this->textBox1->AppendText("2.)  Press the Reset button momentarily.\r\n");
				this->textBox1->AppendText("3.)  Release button S1.\r\n");
				this->textBox1->AppendText("4.)  Then click Program again.\r\n");  		
			
			}

			enable_Program_btn( );
			this->btnConn->Enabled = true;
			this->btn_mon->Enabled = true;

			
	 }

	private: System::Void txtb_SSID_TextChanged(System::Object^  sender, System::EventArgs^  e) 
	{
		enable_Program_btn();
	}


	private: System::Void txtbx_PWD_TextChanged(System::Object^  sender, System::EventArgs^  e) 
	{
		enable_Program_btn();
	}


	private: System::Void btn_mon_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		if (this->btnConn->Enabled == true)
		{
 			this->serialPort1->DataReceived += gcnew System::IO::Ports::SerialDataReceivedEventHandler(this, &Form1::serialPort1_DataReceived);
			this->btnConn->Enabled = false;
			this->btnProg->Enabled = false;
			this->btn_mon->Text =" Stop ";
			this->serialPort1->DiscardInBuffer();
			this->textBox1->Text="";
		}
		else
		{
			// This removes the event handler from the serial port
			this->serialPort1->DataReceived -= gcnew System::IO::Ports::SerialDataReceivedEventHandler(this, &Form1::serialPort1_DataReceived);
			this->btnConn->Enabled = true;
			enable_Program_btn( );
			this->btn_mon->Text ="Monitor";
		}
	}


	private: System::Void serialPort1_DataReceived(System::Object^  sender, System::IO::Ports::SerialDataReceivedEventArgs^  e) 
	{	
		String ^ message;

		message = this->serialPort1->ReadExisting();
		this->BeginInvoke(callback,message);

	}


	private: System::Void chk_WPA_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
	{
		enable_Program_btn( );

		if ( this->chk_WPA->Checked )
			this->txtbx_PWD->Enabled = true;	
		else 
			this->txtbx_PWD->Enabled = false;

	}
}; // end class 
} // End Namespace 

