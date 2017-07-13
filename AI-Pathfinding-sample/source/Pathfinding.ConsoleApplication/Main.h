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
		Library::Graph mGraph;
		std::string mGridFile;
	};
}