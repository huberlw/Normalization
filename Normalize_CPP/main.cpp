#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <limits>
#include <cmath>
#include "tokenize.h"
#include "createPath.h"
#include "normalize.h"

using namespace std;

int main()
{
	string path;
	string line;

	cout << "Enter csv file path: ";
	getline(cin, path);

	cout << "\nIs the first column for ID? (Y/N)" << endl;

	bool done = false;
	bool id = false;

	while (!done)
	{
		string temp;

		cin >> temp;

		if (temp.compare("Y") == 0 || temp.compare("y") == 0)
		{
			id = true;
			done = true;
		}
		else if (temp.compare("N") == 0 || temp.compare("n") == 0)
			done = true;
		else
			cout << "\nPlease enter a (Y/N).\nIs the first column for ID? (Y/N)" << endl;
	}

	cout << "\nIs the first row for labels? (Y/N)" << endl;
	done = false;

	bool label = false;
	vector<string> labels;

	while (!done)
	{
		string temp;

		cin >> temp;

		if (temp.compare("Y") == 0 || temp.compare("y") == 0)
		{
			label = true;
			done = true;
		}
		else if (temp.compare("N") == 0 || temp.compare("n") == 0)
			done = true;
		else
			cout << "\nPlease enter a (Y/N).\nIs the first row for labels? (Y/N)" << endl;
	}

	ifstream file(path);
	if (!file)
	{
		cout << "File not found. Press 'Enter' to exit.";

		string end;

		cin.ignore();
		getline(cin, end);

		return -1;
	}

	if (label && getline(file, line))
		tokenize(line, labels);

	vector<string>* cols = NULL;

	bool first = true;
	size_t len = 0;

	while (getline(file, line))
	{
		vector<string> row;

		bool empty = tokenize(line, row);

		if (empty) continue;

		if (first)
		{
			len = row.size();

			cols = new vector<string>[len];

			for (int i = 0; i < len; i++)
				cols[i].push_back(row.at(i));

			first = false;
			continue;
		}

		for (int i = 0; i < len; i++)
			cols[i].push_back(row.at(i));
	}

	size_t size;
	if (cols == NULL)
	{
		cout << "File is empty. Press 'Enter' to exit." << endl;

		string end;

		cin.ignore();
		getline(cin, end);

		return 0;
	}

	else
		size = cols[0].size();

	// created 2d arrays
	double** normData = new double* [len];

	for (int i = 0; i < len; i++)
		normData[i] = new double[size];

	string** stringData = new string * [len];

	for (int i = 0; i < len; i++)
		stringData[i] = new string[size];

	int* remove = new int[size];

	for (int i = 0; i < size; i++)
		remove[i] = 0;
		
	cout << "\nIs there a column that should not be normalized? (Y/N)" << endl;

	done = false;
	bool hide = false;

	while (!done)
	{
		string temp;

		cin >> temp;

		if (temp.compare("Y") == 0 || temp.compare("y") == 0)
		{
			hide = true;
			done = true;
		}
		else if (temp.compare("N") == 0 || temp.compare("n") == 0)
			done = true;
		else
		{
			cout << "\nPlease enter a (Y/N).\nIs there a column that should not be normalized? (Y/N)" << endl;
			continue;
		}

		if (hide)
		{
			cout << "\nEnter the column number that should not be normalized. Columns range from 1 to " << len << endl;

			int temp;

			while (!(cin >> temp) || temp < 1 || temp > len)
			{
				cin.clear();
				cin.ignore(numeric_limits<double>::max(), '\n');

				if (temp < 0 || temp > len - 1)
					cout << "\nInvalid Input: please enter a valid column number.\nColumns range from 1 to " << len << endl;
				else
					cout << "\nInvalid Input: please enter a numerical value." << endl;
			}

			cin.ignore(numeric_limits<double>::max(), '\n');

			normData[temp - 1][0] = -1;

			hide = false;
			done = false;

			cout << "\nIs there another column that should not be normalized? (Y/N)" << endl;
		}
	}

	for (int i = 0; i < len; i++)
	{
		if (normData[i][0] == -1)
		{
			stringData[i] = &cols[i][0];
			continue;
		}
		
		if (!id)
			normal(cols[i], normData[i], remove, (i + 1));
		else
		{
			stringData[i] = &cols[i][0];
			normData[i][0] = -1;
			id = false;
		}

		if (normData[i][0] == -1)
			stringData[i] = &cols[i][0];
	}

	string normalized = createPath(path);
	
	ofstream wFile;
	wFile.open(normalized);

	if (label)
	{
		for (int i = 0; i < labels.size(); i++)
		{
			if (i != labels.size() - 1)
				wFile << labels.at(i) << ", ";
			else
				wFile << labels.at(i) << endl;
		}
	}

	for (int i = 0; i < size; i++)
	{
		if (remove[i] == 1)
			continue;
		for (int j = 0; j < len; j++)
		{
			if (normData[j][0] == -1)
			{
				if (j != len - 1)
					wFile << stringData[j][i] << ", ";
				else
					wFile << stringData[j][i] << endl;
			}
			else if (normData[j][0] == -2)
			{
				if (j != len - 1)
					continue;
				else
					wFile << endl;
			}
			else if (isnan(normData[j][i]))
			{
				if (j != len - 1)
					wFile << "NaN" << ", ";
				else
					wFile << "NaN" << endl;
			}
			else
			{
				if (j != len - 1)
					wFile << normData[j][i] << ", ";
				else
					wFile << normData[j][i] << endl;
			}
		}
	}

	wFile.close();

	cout << "\nNormalization complete.\nA normalized csv file has been created in the same directory as the original file.\nFile name: normalized.csv\n\nPress 'Enter' to exit." << endl;

	string end;
	
	cin.ignore();
	getline(cin, end);

	return 1;
}