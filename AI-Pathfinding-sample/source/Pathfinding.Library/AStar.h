#pragma once

#include "IPathFinder.h"

namespace AI
{
	namespace PathFinding
	{
		class AStar : public Library::IPathFinder
		{
		public:
			AStar() = default;
			~AStar() = default;

			AStar(const AStar&) = delete;
			AStar(AStar&&) = delete;
			AStar& operator=(const AStar&) = delete;
			AStar& operator=(AStar&&) = delete;

			std::deque<std::shared_ptr<Library::Node>> FindPath(std::shared_ptr<Library::Node> start,
				std::shared_ptr<Library::Node> end,
				std::set<std::shared_ptr<Library::Node>>& closedSet) override;

		protected:
			std::deque<std::shared_ptr<Library::Node>> FindPath(std::shared_ptr<Library::Node> start,
				std::shared_ptr<Library::Node> end,
				std::set<std::shared_ptr<Library::Node>>& closedSet,
				std::function<float(const Library::Point&, const Library::Point&)> heuristicFunction);

		private:
			static const float TraversalCost;
		};
	}
}