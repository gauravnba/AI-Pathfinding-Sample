#pragma once

#include "IPathFinder.h"

namespace AI
{
	namespace PathFinding
	{
		class BreadthFirst final : public Library::IPathFinder
		{
		public:
			BreadthFirst() = default;
			~BreadthFirst() = default;

			BreadthFirst(const BreadthFirst&) = delete;
			BreadthFirst(BreadthFirst&&) = delete;
			BreadthFirst& operator=(const BreadthFirst&) = delete;
			BreadthFirst& operator=(BreadthFirst&&) = delete;

			std::deque<std::shared_ptr<Library::Node>> FindPath(std::shared_ptr<Library::Node> start, 
				std::shared_ptr<Library::Node> end, 
				std::set<std::shared_ptr<Library::Node>>& closedSet) override;
		};
	}
}