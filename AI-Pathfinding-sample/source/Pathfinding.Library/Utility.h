#pragma once

#include <vector>
#include <string>

namespace Library
{
	struct Point;

	class Utility final
	{
	public:
		static std::vector<std::string> SplitString(const std::string& input, char delimeter);
		static float ManhattanDistance(const Point& a, const Point& b);
	};
}