#include "NormForm.h"

using namespace System;
using namespace System::Windows::Forms;

[System::STAThread]
void main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	NormalizeCPP::NormForm form;
	Application::Run(% form);
}