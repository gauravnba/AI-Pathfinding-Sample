#pragma once

#include "Graph.h"

namespace AI
{
	class Main final
	{
	public:
		Main() = delete;
		Main(const std::string& gridFileName);

		Main(const Main&) = delete;
		Main(Main&&) = delete;
		Main& operator=(const Main&) = delete;
		Main& operator=(Main&&) = delete;

		~Main() = default;

		void Run();

	private:
		void SetStartAndEndPoints(Library::Point& start, Library::Point& end);
		Library::Point GetPointFromString(const std::string& input);
		void UpdateGraphWithPath(const Library::Point& start, const Library::Point& end, Library::IPathFinder& algorithm);

		Library::Graph mGraph;
		std::string mGridFile;
	};
}