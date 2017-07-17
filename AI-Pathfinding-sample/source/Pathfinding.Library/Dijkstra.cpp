#include "pch.h"
#include "Dijkstra.h"

using namespace std;
using namespace Library;

namespace AI
{
	namespace PathFinding
	{
		deque<shared_ptr<Node>> Dijkstra::FindPath(shared_ptr<Node> start, shared_ptr<Node> end, set<shared_ptr<Node>>& closedSet)
		{
			return AStar::FindPath(start, end, closedSet, [](const Point& a, const Point& b)
			{
				UNREFERENCED_PARAMETER(a);
				UNREFERENCED_PARAMETER(b);
				return 0.0f;
			});
		}
	}
}