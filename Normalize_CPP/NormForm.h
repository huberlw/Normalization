#pragma once

#include "output.h"
#include <msclr\marshal_cppstd.h>

namespace NormalizeCPP {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for NormForm
	/// </summary>
	public ref class NormForm : public System::Windows::Forms::Form
	{
	public:
		NormForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~NormForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::CheckBox^ checkID;
	private: System::Windows::Forms::CheckBox^ checkLabels;
	private: System::Windows::Forms::Button^ submitButton;
	private: System::Windows::Forms::Label^ answer;
	private: System::Windows::Forms::Label^ label1;

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
			this->checkID = (gcnew System::Windows::Forms::CheckBox());
			this->checkLabels = (gcnew System::Windows::Forms::CheckBox());
			this->submitButton = (gcnew System::Windows::Forms::Button());
			this->answer = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// checkID
			// 
			this->checkID->AutoSize = true;
			this->checkID->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->checkID->Location = System::Drawing::Point(20, 89);
			this->checkID->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->checkID->Name = L"checkID";
			this->checkID->Size = System::Drawing::Size(299, 33);
			this->checkID->TabIndex = 0;
			this->checkID->Text = L"Is the first column for ID\?";
			this->checkID->UseVisualStyleBackColor = true;
			this->checkID->CheckedChanged += gcnew System::EventHandler(this, &NormForm::checkBox1_CheckedChanged);
			// 
			// checkLabels
			// 
			this->checkLabels->AutoSize = true;
			this->checkLabels->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->checkLabels->Location = System::Drawing::Point(20, 145);
			this->checkLabels->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->checkLabels->Name = L"checkLabels";
			this->checkLabels->Size = System::Drawing::Size(303, 33);
			this->checkLabels->TabIndex = 1;
			this->checkLabels->Text = L"Is the first row for labels\?";
			this->checkLabels->UseVisualStyleBackColor = true;
			this->checkLabels->CheckedChanged += gcnew System::EventHandler(this, &NormForm::checkBox2_CheckedChanged);
			// 
			// submitButton
			// 
			this->submitButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->submitButton->Location = System::Drawing::Point(19, 211);
			this->submitButton->Margin = System::Windows::Forms::Padding(4, 5, 4, 5);
			this->submitButton->Name = L"submitButton";
			this->submitButton->Size = System::Drawing::Size(286, 100);
			this->submitButton->TabIndex = 6;
			this->submitButton->Text = L"Open File";
			this->submitButton->UseVisualStyleBackColor = true;
			this->submitButton->Click += gcnew System::EventHandler(this, &NormForm::submitButton_Click);
			// 
			// answer
			// 
			this->answer->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->answer->AutoSize = true;
			this->answer->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->answer->Location = System::Drawing::Point(13, 331);
			this->answer->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->answer->Name = L"answer";
			this->answer->Size = System::Drawing::Size(88, 37);
			this->answer->TabIndex = 7;
			this->answer->Text = L"temp";
			this->answer->Click += gcnew System::EventHandler(this, &NormForm::label2_Click_1);
			// 
			// label1
			// 
			this->label1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(12, 24);
			this->label1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(411, 37);
			this->label1->TabIndex = 8;
			this->label1->Text = L"Open File to normalize data";
			this->label1->Click += gcnew System::EventHandler(this, &NormForm::label1_Click_1);
			// 
			// NormForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(436, 384);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->answer);
			this->Controls->Add(this->submitButton);
			this->Controls->Add(this->checkLabels);
			this->Controls->Add(this->checkID);
			this->Name = L"NormForm";
			this->Text = L"NormForm";
			this->Load += gcnew System::EventHandler(this, &NormForm::NormForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();
			this->CenterToScreen();
		}
#pragma endregion
		private: System::Void NormForm_Load(System::Object^ sender, System::EventArgs^ e) {
			this->answer->Text = "";
		}
		private: System::Void submitButton_Click(System::Object^ sender, System::EventArgs^ e) {
			this->answer->Text = "";

			String^ csvPath;
			OpenFileDialog^ ofd = gcnew OpenFileDialog;

			ofd->Filter = "Text Files (*.data, *.csv, *.txt, *.text)|*.data; *.csv; *.txt; *.text"; // we can add this later if needed (needs error handling if so) |All Files (*.*)|*.*";
			ofd->FilterIndex = 1;
			ofd->RestoreDirectory = true;

			if (ofd->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			{
				csvPath = ofd->FileName;

				if (csvPath == nullptr) return;
			}
			
			bool ID = this->checkID->Checked;
			bool labels = this->checkLabels->Checked;
			
			std::string path;
			
			try
			{
				path = msclr::interop::marshal_as<std::string>(csvPath);
			}
			catch (System::ArgumentNullException^ e)
			{
				return;
			}

			std::string str = output(path, ID, labels);

			String^ isDone = gcnew String(str.c_str());
			this->answer->Text = isDone;
		}
		private: System::Void label2_Click_1(System::Object^ sender, System::EventArgs^ e) {}
		private: System::Void label1_Click_1(System::Object^ sender, System::EventArgs^ e) {}
		private: System::Void checkBox1_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {}
		private: System::Void checkBox2_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {}
	};
}
