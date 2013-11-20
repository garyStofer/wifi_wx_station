#pragma once

#include "Cp2104.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Threading;
using namespace std;
using namespace Pic_BL;

namespace WX_BootloaderGUI {


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
	private: ProgramPIC ^PgmPic;
	private: Thread ^thrd1; 
	private: String ^serialPortName;
	private: System::Windows::Forms::ToolStripProgressBar^  toolStripProgressBar1;
	private: System::Windows::Forms::ToolStripStatusLabel^  toolStripStatusLabel1;
	private: System::Windows::Forms::OpenFileDialog^  InputFileDlg;
	private: System::Windows::Forms::Button^  btn_Abort;
	private: System::Windows::Forms::Button^  btnConn;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::ComponentModel::IContainer^  components;
	private: System::Windows::Forms::StatusStrip^  statusStrip1;
	private: System::Windows::Forms::Button^  btnProg;
	private: System::Windows::Forms::Button^  btn_import;

	

	public:
		Form1(void)	// Constructor
		{
			InitializeComponent();
		}

	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) 
		 {
			System::Object^ nl;
			System::EventArgs^ nle; 			
			btnConn_Click(nl,nle);		 // force a click 

			this->toolStripProgressBar1->Value = 0;

			PgmPic = gcnew ProgramPIC();
			PgmPic->SendMsgTo += gcnew Pic_BL::d_Evnthandler(this,&WX_BootloaderGUI::Form1::OnProgressUpdate1);
			

		 }
	
		/// Deconstructor
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	

	void OnProgressUpdate1( System::String^ str, int i)
	{	
		if (this->InvokeRequired)		// Is the caller on the Main (GUI) thread ?
		{                               // No, Use Invoke to re-issue the call on the "this" thread  
			this->Invoke(gcnew Pic_BL::d_Evnthandler(this,&WX_BootloaderGUI::Form1::OnProgressUpdate1), str, i);
		}
		else 
		{
			if ( i == 0)
				textBox1->AppendText( str + "\r\n");
			else if ( i < 0 )
			{
				if (i == -999)	 //Signalling programmer thread end
				{
					this->btnConn->Enabled = true;
					this->btn_import->Enabled = true;
					this->btnProg->Enabled = true;
					this->btn_Abort->Enabled = false;
				} 
				toolStripStatusLabel1->Text = str;
			}		
			else 
			{
				toolStripStatusLabel1->Text = str;
				if ( i <= toolStripProgressBar1->Maximum )
					toolStripProgressBar1->Value = i;
			}
		}
			
	}
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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->btnConn = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			this->toolStripProgressBar1 = (gcnew System::Windows::Forms::ToolStripProgressBar());
			this->toolStripStatusLabel1 = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->btnProg = (gcnew System::Windows::Forms::Button());
			this->btn_import = (gcnew System::Windows::Forms::Button());
			this->btn_Abort = (gcnew System::Windows::Forms::Button());
			this->InputFileDlg = (gcnew System::Windows::Forms::OpenFileDialog());
			this->statusStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// btnConn
			// 
			this->btnConn->Location = System::Drawing::Point(12, 12);
			this->btnConn->Name = L"btnConn";
			this->btnConn->Size = System::Drawing::Size(94, 23);
			this->btnConn->TabIndex = 0;
			this->btnConn->Text = L"Locate Device";
			this->btnConn->UseVisualStyleBackColor = true;
			this->btnConn->Click += gcnew System::EventHandler(this, &Form1::btnConn_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(12, 52);
			this->textBox1->Multiline = true;
			this->textBox1->Name = L"textBox1";
			this->textBox1->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->textBox1->Size = System::Drawing::Size(449, 212);
			this->textBox1->TabIndex = 1;
			// 
			// statusStrip1
			// 
			this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {this->toolStripProgressBar1, 
				this->toolStripStatusLabel1});
			this->statusStrip1->Location = System::Drawing::Point(0, 276);
			this->statusStrip1->Name = L"statusStrip1";
			this->statusStrip1->Size = System::Drawing::Size(475, 22);
			this->statusStrip1->SizingGrip = false;
			this->statusStrip1->TabIndex = 2;
			// 
			// toolStripProgressBar1
			// 
			this->toolStripProgressBar1->Margin = System::Windows::Forms::Padding(10, 3, 5, 3);
			this->toolStripProgressBar1->Maximum = 1000;
			this->toolStripProgressBar1->Name = L"toolStripProgressBar1";
			this->toolStripProgressBar1->Size = System::Drawing::Size(200, 16);
			this->toolStripProgressBar1->Step = 1;
			this->toolStripProgressBar1->Style = System::Windows::Forms::ProgressBarStyle::Continuous;
			this->toolStripProgressBar1->Value = 555;
			// 
			// toolStripStatusLabel1
			// 
			this->toolStripStatusLabel1->Name = L"toolStripStatusLabel1";
			this->toolStripStatusLabel1->Size = System::Drawing::Size(109, 17);
			this->toolStripStatusLabel1->Text = L"toolStripStatusLabel1";
			// 
			// btnProg
			// 
			this->btnProg->Enabled = false;
			this->btnProg->Location = System::Drawing::Point(220, 12);
			this->btnProg->Name = L"btnProg";
			this->btnProg->Size = System::Drawing::Size(109, 23);
			this->btnProg->TabIndex = 3;
			this->btnProg->Text = L"Program Flash";
			this->btnProg->UseVisualStyleBackColor = true;
			this->btnProg->Click += gcnew System::EventHandler(this, &Form1::btnProg_Click);
			// 
			// btn_import
			// 
			this->btn_import->Location = System::Drawing::Point(112, 12);
			this->btn_import->Name = L"btn_import";
			this->btn_import->Size = System::Drawing::Size(102, 23);
			this->btn_import->TabIndex = 11;
			this->btn_import->Text = L"Import HEX";
			this->btn_import->UseVisualStyleBackColor = true;
			this->btn_import->Click += gcnew System::EventHandler(this, &Form1::btn_import_Click);
			// 
			// btn_Abort
			// 
			this->btn_Abort->Enabled = false;
			this->btn_Abort->Location = System::Drawing::Point(367, 12);
			this->btn_Abort->Name = L"btn_Abort";
			this->btn_Abort->Size = System::Drawing::Size(94, 23);
			this->btn_Abort->TabIndex = 12;
			this->btn_Abort->Text = L"ABORT";
			this->btn_Abort->UseVisualStyleBackColor = true;
			this->btn_Abort->Click += gcnew System::EventHandler(this, &Form1::btn_Abort_Click);
			// 
			// InputFileDlg
			// 
			this->InputFileDlg->DefaultExt = L"hex";
			this->InputFileDlg->Filter = L"Intel Hex File|*.hex";
			this->InputFileDlg->RestoreDirectory = true;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(475, 298);
			this->Controls->Add(this->btn_Abort);
			this->Controls->Add(this->btnConn);
			this->Controls->Add(this->btn_import);
			this->Controls->Add(this->btnProg);
			this->Controls->Add(this->statusStrip1);
			this->Controls->Add(this->textBox1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"Form1";
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
			this->Text = L"WWXS Bootloader";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->statusStrip1->ResumeLayout(false);
			this->statusStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


// Event handlers from here on down

	private: void btnConn_Click(System::Object^  sender, System::EventArgs^  e)
	{	
		String^ S ="COM";
		int i ;

		Cp2104  ^cp = gcnew Cp2104();
		
		this->btnConn->Enabled = false;
		this->toolStripProgressBar1->Value =0;
	 
		
		try 
		{
			i = cp->GetCp2104_COM_num();
		}
		catch (Exception^ e)
		{
// TODO ??  cause an exit of the program in case the DLL's are missing

			this->toolStripStatusLabel1->Text = e->Message;
			this->textBox1->Text = this->toolStripStatusLabel1->Text;
			return;
		}

		if ( i > 0 )
		{
			S += i;
			
			this->serialPortName = S;
			this->textBox1->Text = "";
			this->toolStripStatusLabel1->Text = "Wunder-Weather-Station is found at: " + S  ;
			this->textBox1->AppendText( this->toolStripStatusLabel1->Text +"\r\n");
			this->btnProg->Enabled = true;

		}
		else 
		{
		
			this->textBox1->Text = "";
			this->toolStripStatusLabel1->Text = "Wunder-Weather-Station is NOT found!";
			this->textBox1->AppendText( this->toolStripStatusLabel1->Text +"\r\n");
			this->textBox1->AppendText("Is it plugged in? Is the USB device driver installed?\r\n");
			this->btnProg->Enabled = false;

		}
		this->btnConn->Enabled = true;
	}

	private: System::Void btnProg_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		this->toolStripProgressBar1->Value =0;
		PgmPic->SerialPortName = this->serialPortName;

		// prevent any action while the programming thread is running 
		this->btnConn->Enabled = false;
		this->btn_import->Enabled = false;
		this->btnProg->Enabled = false;
		this->btn_Abort->Enabled = true;
		
		thrd1 = gcnew Thread(gcnew ThreadStart(PgmPic, &Pic_BL::ProgramPIC::doProgram));
		thrd1->Name ="PicProgrammer thread";
		
		thrd1->Start();
		
	}


	private: System::Void btn_import_Click(System::Object^  sender, System::EventArgs^  e) 
	 {
		this->InputFileDlg->ShowDialog();
		PgmPic->ImportP24HEXFile( this->InputFileDlg->FileName);

	 }



private: System::Void btn_Abort_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 // The Upload part of doProgram checks this flag and exits if set from here
			 
			 PgmPic->AbortRequest = true;	//
		 }
}; // end class 
} // End Namespace 

