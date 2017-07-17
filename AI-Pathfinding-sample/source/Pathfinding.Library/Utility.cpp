#include "pch.h"
#include "Utility.h"
#include "Point.h"

using namespace std;

namespace Library
{
	vector<string> Utility::SplitString(const string& input, char delimeter)
	{
		vector<string> outputStrings;
		stringstream inputStream(input);
		string outputString;

		while (getline(inputStream, outputString, delimeter))
		{
			outputStrings.push_back(outputString);
		}

		return outputStrings;
	}

	float Utility::ManhattanDistance(const Point& a, const Point& b)
	{
		return static_cast<float>(((a.X - b.X) + (a.Y - b.Y)));
	}
}