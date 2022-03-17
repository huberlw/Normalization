#include <iostream>
#include <string>
#include <vector>
#include "normalize.h"

using namespace std;

void normal(vector<string> array, double* allNum, int* remove, int col)
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
		catch (invalid_argument e)
		{
			if (!done)
				cout << "\nNon-numeric value found in column " << col << ".\nShould column be normalized? (Y / N)" << endl;

			while (!done)
			{
				string temp;

				cin >> temp;

				if (temp.compare("Y") == 0 || temp.compare("y") == 0)
				{
					cont = true;
					done = true;
				}
				else if (temp.compare("N") == 0 || temp.compare("n") == 0)
					done = true;
				else
					cout << "\nPlease enter a (Y/N).\nShould column be normalized? (Y/N)" << endl;
			}

			if (cont)
			{
				while (keepRows == -1)
				{
					cout << "\nWould you like to keep the invalid rows? (Y / N)" << endl;
				
					done = false;

					while (!done)
					{
						string temp;

						cin >> temp;

						if (temp.compare("Y") == 0 || temp.compare("y") == 0)
						{
							keepRows = 1;
							done = true;
						}
						else if (temp.compare("N") == 0 || temp.compare("n") == 0)
						{
							keepRows = 2;
							done = true;
						}
						else
							cout << "\nPlease enter a (Y/N).\nWould you like to keep the invalid rows? (Y / N)" << endl;
					}
				}
				
				allNum[i] = NAN;
				nonNumeric++;

				if (keepRows == 2)
					remove[i] = 1;
			}
			else
			{
				done = false;
				bool keep = false;

				cout << "\nShould column " << col << " be kept or deleted?\nEnter 'Y' for keep and 'N' for delete. (Y/N)" << endl;

				while (!done)
				{
					string temp;

					cin >> temp;

					if (temp.compare("Y") == 0 || temp.compare("y") == 0)
					{
						keep = true;
						done = true;
					}
					else if (temp.compare("N") == 0 || temp.compare("n") == 0)
						done = true;
					else
						cout << "\nPlease enter a (Y/N).\nShould column be normalized? (Y/N)" << endl;
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

	double max = numeric_limits<double>::lowest();
	double min = numeric_limits<double>::max();


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
		double minSD;
		double maxSD;

		cout << "\nThe standard deviation for column " << col << " is " << sd << ". This is very small.\nPlease enter a minimum and maximum. The standard deviation will be ((maximum - minimum) / 2)." << endl;

		cout << "\nPlease enter a numerical value for min." << endl;

		while (!(cin >> minSD))
		{
			cin.clear();
			cin.ignore(numeric_limits<double>::max(), '\n');
			cout << "\nInvalid Input: please enter a numerical value." << endl;
		}

		cin.ignore(numeric_limits<double>::max(), '\n');
		cout << "\nPlease enter a numerical value for max." << endl;

		while (!(cin >> maxSD) || maxSD <= minSD)
		{
			cin.clear();
			cin.ignore(numeric_limits<double>::max(), '\n');

			if (maxSD <= minSD)
				cout << "\nInvalid Input: please enter a numerical value larger than min." << endl;
			else
				cout << "\nInvalid Input: please enter a numerical value." << endl;
		}

		sd = (maxSD - minSD) / 2;
	}

	if (sd == 0)
	{
		cout << "\nStandard Deviation is 0: error division by zero." << endl;
		cout << "No longer normalizing column " << col << endl;

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
		cout << "\nMin and Max values in column " << col << " are equal.\nWould you like to manually enter min and max? If no, all values will be defaulted to 0.5. (Y / N)" << endl;

		bool done = false;
		bool manual = false;

		while (!done)
		{
			string temp;

			cin >> temp;

			if (temp.compare("Y") == 0 || temp.compare("y") == 0)
			{
				manual = true;
				done = true;
			}
			else if (temp.compare("N") == 0 || temp.compare("n") == 0)
				done = true;
			else
				cout << "\nPlease enter a (Y/N).\nWould you like to manually enter min and max? If no, all values will be defaulted to 0.5. (Y / N)" << endl;
		}

		if (manual)
		{
			cout << "\nPlease enter a numerical value for min." << endl;

			while (!(cin >> min))
			{
				cin.clear();
				cin.ignore(numeric_limits<double>::max(), '\n');
				cout << "\nInvalid Input: please enter a numerical value." << endl;
			}

			cin.ignore(numeric_limits<double>::max(), '\n');
			cout << "\nPlease enter a numerical value for max." << endl;

			while (!(cin >> max) || max <= min)
			{
				cin.clear();
				cin.ignore(numeric_limits<double>::max(), '\n');

				if (max <= min)
					cout << "\nInvalid Input: please enter a numerical value larger than min." << endl;
				else
					cout << "\nInvalid Input: please enter a numerical value." << endl;
			}

			div = max - min;

			for (int i = 0; i < size; i++)
			{
				if (isnan(allNum[i]) == 0)
				{
					if (allNum[i] < min)
					{
						cout << "\nChoosen min is greater than standardized data in col " << col << " row " << i + 1 << endl;
						cout << "No longer normalizing column " << col << endl;

						allNum[0] = -1;

						return;
					}
					else if (allNum[i] > max)
					{
						cout << "\nChoosen max is lesser than standardized data in col " << col << " row " << i + 1 << endl;
						cout << "No longer normalizing column " << col << endl;

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