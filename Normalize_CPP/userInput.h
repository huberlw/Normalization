#pragma once
#include <string>
#include <iostream>
#include <msclr\marshal_cppstd.h>

namespace NormalizeCPP {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for userInput
	/// </summary>
	public ref class userInput : public System::Windows::Forms::Form
	{
	public:
		userInput(std::string str)
		{
			InitializeComponent(str);
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~userInput()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ uInput;
	private: System::Windows::Forms::TextBox^ userInputed;
	protected:

	private: System::Windows::Forms::Button^ submitButton;
	private: double inputed;

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
		void InitializeComponent(std::string str)
		{
			this->uInput = (gcnew System::Windows::Forms::Label());
			this->userInputed = (gcnew System::Windows::Forms::TextBox());
			this->submitButton = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// uInput
			// 
			this->uInput->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->uInput->AutoSize = true;
			this->uInput->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->uInput->Location = System::Drawing::Point(12, 9);
			this->uInput->Name = L"uInput";
			this->uInput->Size = System::Drawing::Size(49, 20);
			this->uInput->TabIndex = 0;
			String^ str2 = gcnew String(str.c_str());
			this->uInput->Text = str2;
			// 
			// userInputed
			// 
			this->userInputed->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->userInputed->Location = System::Drawing::Point(12, 32);
			this->userInputed->Name = L"userInputed";
			this->userInputed->Size = System::Drawing::Size(164, 20);
			this->userInputed->TabIndex = 1;
			// 
			// submitButton
			// 
			this->submitButton->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->submitButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->submitButton->Location = System::Drawing::Point(36, 64);
			this->submitButton->Name = L"submitButton";
			this->submitButton->Size = System::Drawing::Size(115, 49);
			this->submitButton->TabIndex = 2;
			this->submitButton->Text = L"Submit";
			this->submitButton->UseVisualStyleBackColor = true;
			this->submitButton->Click += gcnew System::EventHandler(this, &userInput::submitButton_Click_1);
			// 
			// userInput
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(300, 150);
			this->Controls->Add(this->submitButton);
			this->Controls->Add(this->userInputed);
			this->Controls->Add(this->uInput);
			this->Name = L"userInput";
			this->Text = L"userInput";
			this->Load += gcnew System::EventHandler(this, &userInput::userInput_Load);
			this->ResumeLayout(false);
			this->PerformLayout();
			this->CenterToScreen();

		}
#pragma endregion
		public: double getInput() {
			return inputed;
		}
		private: System::Void submitButton_Click_1(System::Object^ sender, System::EventArgs^ e) {
			String^ ui = this->userInputed->Text;

			std::string str = msclr::interop::marshal_as<std::string>(ui);

			try
			{
				inputed = stod(str);
			}
			catch (std::invalid_argument e)
			{
				inputed = NAN;
			}

			this->Close();
		}
		private: System::Void userInput_Load(System::Object^ sender, System::EventArgs^ e) {}
	};
}
