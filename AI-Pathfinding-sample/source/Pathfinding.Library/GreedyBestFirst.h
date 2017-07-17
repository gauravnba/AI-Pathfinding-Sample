#pragma once

#include "IPathFinder.h"

namespace AI
{
	namespace PathFinding
	{
		class GreedyBestFirst final : public Library::IPathFinder
		{
		public:

			GreedyBestFirst() = default;
			~GreedyBestFirst() = default;

			GreedyBestFirst(const GreedyBestFirst&) = delete;
			GreedyBestFirst(GreedyBestFirst&&) = delete;
			GreedyBestFirst& operator=(const GreedyBestFirst&) = delete;
			GreedyBestFirst& operator=(GreedyBestFirst&&) = delete;

			std::deque<std::shared_ptr<Library::Node>> FindPath(std::shared_ptr<Library::Node> start,
				std::shared_ptr<Library::Node> end,
				std::set<std::shared_ptr<Library::Node>>& closedSet) override;
		};
	}
}