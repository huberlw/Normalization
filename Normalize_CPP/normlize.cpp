#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#define NOMINMAX
#include <Windows.h>
#include "normalize.h"
#include "userInput.h"

void normal(std::vector<std::string> array, double* allNum, int* remove, int col)
{
	size_t size = array.size();
	size_t nonNumeric = 0;

	bool done = false;
	bool cont = false;
	int keepRows = -1;

	double sum = 0;

	for (int i = 0; i < size; i++)
	{
		try
		{
			double n = stod(array.at(i));
			allNum[i] = n;
			sum += n;
		}
		catch (std::invalid_argument e)
		{
			if (!done)
			{
				char buff[100];
				sprintf_s(buff, "Non-numeric value found in column %d", col);
				std::cout << buff;
				System::String^ message = gcnew System::String(buff);
				
				if (System::Windows::Forms::MessageBox::Show(message, "Should column be normalized?",
					System::Windows::Forms::MessageBoxButtons::YesNo) == System::Windows::Forms::DialogResult::Yes)
				{
					cont = true;
					done = true;
				}
				else
				{
					done = true;
					cont = false;
				}		
			}

			if (cont)
			{
				if (keepRows == -1)
				{
					if (System::Windows::Forms::MessageBox::Show("Should the Invalid Rows be kept?",
						"Keep Rows?",
						System::Windows::Forms::MessageBoxButtons::YesNo) == System::Windows::Forms::DialogResult::Yes)
					{
						keepRows = 1;
					}
					else
					{
						keepRows = 2;
					}
				}

				allNum[i] = NAN;
				nonNumeric++;

				if (keepRows == 2)
					remove[i] = 1;
			}
			else
			{
				bool keep = false;
				
				char buff[100];
				sprintf_s(buff, "Should column %d be kept?", col);
				std::cout << buff;
				System::String^ message = gcnew System::String(buff);
				
				if (System::Windows::Forms::MessageBox::Show(message, "Keep Column?",
					System::Windows::Forms::MessageBoxButtons::YesNo) == System::Windows::Forms::DialogResult::Yes)
				{
					keep = true;
				}

				if (keep)
					allNum[0] = -1;
				else
					allNum[0] = -2;

				return;
			}
		}
	}

	size_t realSize = size - nonNumeric;

	double mean = sum / realSize;
	double sd = 0;

	double max = std::numeric_limits<double>::lowest();
	double min = std::numeric_limits<double>::max();


	for (int i = 0; i < size; i++)
	{
		if (isnan(allNum[i]) == 0)
		{
			double temp = pow((allNum[i] - mean), 2);
			sd += temp;
		}
	}

	sd /= realSize;
	sd = sqrt(sd);

	// if sd < 0.1 then ui input for range, then sd gets range/2
	if (sd < 0.01)
	{
		System::Windows::Forms::MessageBox::Show("Standard deviation is less than 0.01. Please manually enter a minimum and maximum. The standard deviation will get (max - min) / 2","Error");
		
		double minSD;
		double maxSD;
		bool loop = true;
		
		std::string str = "Enter a minimum";

		while (loop)
		{
			NormalizeCPP::userInput^ popup = gcnew NormalizeCPP::userInput(str);
			popup->ShowDialog();

			double temp = popup->getInput();

			if (isnan(temp) == 0)
			{
				minSD = temp;
				loop = false;
			}
			else
			{
				System::Windows::Forms::MessageBox::Show("Invalid input.", "Error");
			}
		}

		loop = true;
		str = "Enter a maximum";

		while (loop)
		{
			NormalizeCPP::userInput^ popup = gcnew NormalizeCPP::userInput(str);
			popup->ShowDialog();

			double temp = popup->getInput();

			if (isnan(temp) == 0)
			{
				maxSD = temp;
				loop = false;
			}
			else
			{
				System::Windows::Forms::MessageBox::Show("Invalid input.", "Error");
			}
		}

		if (minSD >= maxSD)
		{
			char buff[100];
			sprintf_s(buff, "Minimum is not less than maximum.\nNo longer normalizing column %d.", col);
			std::cout << buff;
			System::String^ message = gcnew System::String(buff);
			
			System::Windows::Forms::MessageBox::Show(message, "Error");

			allNum[0] = -1;

			return;
		}

		sd = (maxSD - minSD) / 2;
	}

	if (sd == 0)
	{
		char buff[100];
		sprintf_s(buff, "Standard Deviation is 0: error division by zero.\nNo longer normalizing column %d.", col);
		std::cout << buff;
		System::String^ message = gcnew System::String(buff);

		System::Windows::Forms::MessageBox::Show(message, "Error");

		allNum[0] = -1;

		return;
	}


	for (int i = 0; i < size; i++)
	{
		if (isnan(allNum[i]) == 0)
		{
			allNum[i] = (allNum[i] - mean) / sd;

			if (allNum[i] > max) max = allNum[i];
			if (allNum[i] < min) min = allNum[i];
		}
	}

	double div = max - min;

	// if div = 0 then ui input for min and max or 0.5 default
	if (div != 0)
	{
		for (int i = 0; i < size; i++)
		{
			if (isnan(allNum[i]) == 0)
			{
				allNum[i] = (allNum[i] - min) / div;
				allNum[i] = round(allNum[i] * 1000.0) / 1000.0;
			}
		}
	}
	else
	{
		bool manual = false;

		if (System::Windows::Forms::MessageBox::Show("Min and Max values are equal. Would you like to manually enter min and max? If no, all values will be defaulted to 0.5.",
			"Error",
			System::Windows::Forms::MessageBoxButtons::YesNo) == System::Windows::Forms::DialogResult::Yes)
		{
			manual = true;
		}

		if (manual)
		{
			std::string str = "Enter a minimum";
			bool loop = true;

			while (loop)
			{
				NormalizeCPP::userInput^ popup = gcnew NormalizeCPP::userInput(str);
				popup->ShowDialog();

				double temp = popup->getInput();

				if (isnan(temp) == 0)
				{
					min = temp;
					loop = false;
				}
				else
				{
					System::Windows::Forms::MessageBox::Show("Invalid input.", "Error");
				}
			}

			loop = true;
			str = "Enter a maximum";

			while (loop)
			{
				NormalizeCPP::userInput^ popup = gcnew NormalizeCPP::userInput(str);
				popup->ShowDialog();

				double temp = popup->getInput();

				if (isnan(temp) == 0)
				{
					max = temp;
					loop = false;
				}
				else
				{
					System::Windows::Forms::MessageBox::Show("Invalid input.", "Error");
				}
			}

			if (min >= max)
			{
				char buff[100];
				sprintf_s(buff, "Minimum is not less than maximum.\nNo longer normalizing column %d.", col);
				std::cout << buff;
				System::String^ message = gcnew System::String(buff);

				System::Windows::Forms::MessageBox::Show(message, "Error");

				allNum[0] = -1;

				return;
			}

			div = max - min;

			for (int i = 0; i < size; i++)
			{
				if (isnan(allNum[i]) == 0)
				{
					if (allNum[i] < min)
					{
						char buff[100];
						sprintf_s(buff, "Choosen min is greater than standardized data in column %d row %d.\nNo longer normalizing column %d.", col, i + 1, col);
						std::cout << buff;
						System::String^ message = gcnew System::String(buff);

						System::Windows::Forms::MessageBox::Show(message, "Error");

						allNum[0] = -1;

						return;
					}
					else if (allNum[i] > max)
					{
						char buff[100];
						sprintf_s(buff, "Choosen max is greater than standardized data in column %d row %d.\nNo longer normalizing column %d.", col, i + 1, col);
						std::cout << buff;
						System::String^ message = gcnew System::String(buff);

						System::Windows::Forms::MessageBox::Show(message, "Error");

						allNum[0] = -1;

						return;
					}

					allNum[i] = (allNum[i] - min) / div;
					allNum[i] = round(allNum[i] * 1000.0) / 1000.0;
				}
			}
		}
		else
		{
			for (int i = 0; i < size; i++)
			{
				if (isnan(allNum[i]) == 0)
					allNum[i] = 0.5;
			}
		}
	}
}