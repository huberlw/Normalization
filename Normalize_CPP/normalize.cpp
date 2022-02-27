#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <limits>
#include <cmath>
using namespace std;

bool tokenize(string str, vector<string>& array)
{
	string delim = ",";
	size_t pos = 0;
	bool empty = true;

	while ((pos = str.find(delim)) != string::npos)
	{
		string token = str.substr(0, pos);
		if (token[0] == 'ï' && token[1] == '»' && token[2] == '¿')
			token.erase(0, 3);

		array.push_back(token);
		str.erase(0, pos + delim.length());

		empty = false;
	}
	if (str.length() > 0)
	{
		array.push_back(str);
		empty = false;
	}


	return empty;
}

void normal(vector<string> array, double* allNum)
{
	size_t size = array.size();

	double sum = 0;

	try
	{
		for (int i = 0; i < size; i++)
		{
			double n = stod(array.at(i));
			allNum[i] = n;
			sum += n;
		}
	}
	catch (exception e)
	{
		allNum[0] = -1;
		return;
	}

	double mean = sum / size;
	double sd = 0;

	double max = numeric_limits<double>::lowest();
	double min = numeric_limits<double>::max();

	for (int i = 0; i < size; i++)
	{
		double temp = pow((allNum[i] - mean), 2);
		sd += temp;
	}

	sd /= size;
	sd = sqrt(sd);

	for (int i = 0; i < size; i++)
	{
		allNum[i] = (allNum[i] - mean) / sd;

		if (allNum[i] > max) max = allNum[i];
		if (allNum[i] < min) min = allNum[i];
	}

	double div = max - min;

	if (div != 0)
	{
		for (int i = 0; i < size; i++)
		{
			allNum[i] = (allNum[i] - min) / div;
			allNum[i] = round(allNum[i] * 1000.0) / 1000.0;
		}

	}
	else
	{
		for (int i = 0; i < size; i++)
			allNum[i] = 0;
	}

}

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

	cout << "Is the first row for labels? (Y/N)" << endl;
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
		cout << "File not found";
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
		cout << "File is empty" << endl;
		return 0;
	}

	else
		size = cols[0].size();


	double** normData = new double* [len];

	for (int i = 0; i < len; i++)
		normData[i] = new double[size];

	string** stringData = new string * [len];

	for (int i = 0; i < len; i++)
		stringData[i] = new string[size];

	for (int i = 0; i < len; i++)
	{
		if (!id)
			normal(cols[i], normData[i]);
		else
		{
			stringData[i] = &cols[i][0];
			normData[i][0] = -1;
			id = false;
		}

		if (normData[i][0] == -1)
			stringData[i] = &cols[i][0];
	}

	ofstream wFile;
	wFile.open("normalized.csv");

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
		for (int j = 0; j < len; j++)
		{
			if (normData[j][0] == -1)
			{
				if (j != len - 1)
					wFile << stringData[j][i] << ", ";
				else
					wFile << stringData[j][i] << endl;
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

	cout << "Normalization complete" << endl;
}