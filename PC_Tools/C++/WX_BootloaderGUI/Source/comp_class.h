#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Diagnostics;


namespace Win_formtest {

	/// <summary>
	/// Summary for comp_class
	/// </summary>
	public ref class comp_class :  public System::ComponentModel::Component
	{
	public:
		comp_class(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}
		comp_class(System::ComponentModel::IContainer ^container)
		{
			/// <summary>
			/// Required for Windows.Forms Class Composition Designer support
			/// </summary>

			container->Add(this);
			InitializeComponent();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~comp_class()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			components = gcnew System::ComponentModel::Container();
		}
#pragma endregion
	};
}
