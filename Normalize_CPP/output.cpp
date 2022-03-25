#include "output.h"
#include "userInput.h"

using namespace std;

string output(string path, bool id, bool label)
{
	string line;
	vector<string> labels;

	ifstream file(path);

	if (!file) return "File not found.";

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

	if (cols == NULL) return "File is empty.";

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

	bool hide = false;

	if (System::Windows::Forms::MessageBox::Show("Is there a column that should not be normalized?",
		"Normalize",
		System::Windows::Forms::MessageBoxButtons::YesNo) == System::Windows::Forms::DialogResult::Yes)
	{
		hide = true;
	}

	while (hide)
	{
		stringstream ss;
		ss << "Enter column between 1 and " << len;
		
		NormalizeCPP::userInput^ popup = gcnew NormalizeCPP::userInput(ss.str());
		popup->ShowDialog();

		int temp = popup->getInput();

		if (temp < 1 || temp > len)
			System::Windows::Forms::MessageBox::Show("Invalid input.", "Error");
		else
		{

			normData[temp - 1][0] = -1;

			if (System::Windows::Forms::MessageBox::Show("Is there another column that should not be normalized?",
				"",
				System::Windows::Forms::MessageBoxButtons::YesNo) == System::Windows::Forms::DialogResult::No)
			{
				hide = false;
			}
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

	string end;

	cin.ignore();
	getline(cin, end);

	return "Normalization complete.";
}