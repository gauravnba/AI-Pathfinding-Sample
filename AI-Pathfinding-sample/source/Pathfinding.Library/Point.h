#pragma once

#include <cstdint>

namespace Library
{
	struct Point final
	{
		explicit Point(const std::int32_t x = 0, const std::int32_t y = 0);

		bool operator<(const Point& rhs) const;

		std::int32_t X;
		std::int32_t Y;
	};
}

#include "Point.inl"