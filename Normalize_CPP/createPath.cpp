#include <string>
#include "createPath.h"

using namespace std;

// creates path for output file
string createPath(string path)
{
	size_t pos = path.find_last_of("/\\");
	string normalize = path.substr(0, pos);

	normalize.append("/normalized.csv");

	return normalize;
}
