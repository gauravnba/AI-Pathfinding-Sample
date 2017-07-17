#pragma once

#include "AStar.h"

namespace AI
{
	namespace PathFinding
	{
		class Dijkstra final : public AStar
		{
		public:
			Dijkstra() = default;
			~Dijkstra() = default;

			Dijkstra(const Dijkstra&) = delete;
			Dijkstra(Dijkstra&&) = delete;
			Dijkstra& operator=(const Dijkstra&) = delete;
			Dijkstra& operator=(Dijkstra&&) = delete;

			std::deque<std::shared_ptr<Library::Node>> FindPath(std::shared_ptr<Library::Node> start,
				std::shared_ptr<Library::Node> end,
				std::set<std::shared_ptr<Library::Node>>& closedSet) override;
		};
	}
}