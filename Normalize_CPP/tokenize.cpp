#include <string>
#include <vector>
#include "tokenize.h"

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