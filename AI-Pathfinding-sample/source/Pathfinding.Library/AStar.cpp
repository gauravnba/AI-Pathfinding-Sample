#include "pch.h"
#include "AStar.h"
#include "Utility.h"

using namespace std;
using namespace Library;

namespace AI
{
	namespace PathFinding
	{
		const float AStar::TraversalCost = 1.0f;

		deque<shared_ptr<Node>> AStar::FindPath(shared_ptr<Node> start, shared_ptr<Node> end, set<shared_ptr<Node>>& closedSet)
		{
			return FindPath(start, end, closedSet, [](const Point& a, const Point& b)
			{
				return static_cast<float>(((a.X - b.X) + (a.Y - b.Y)));
			});
		}

		deque<shared_ptr<Node>> AStar::FindPath(shared_ptr<Node> start, shared_ptr<Node> end, set<shared_ptr<Node>>& closedSet, function<float(const Point&, const Point&)> heuristicFunction)
		{
			set<shared_ptr<Node>> openSet;
			auto currentNode = start;
			closedSet.insert(currentNode);
			float costSoFar = 0.0f;

			do
			{
				// For each neighbour, set the TotalCosts.
				for (auto neighbour : currentNode->Neighbours())
				{
					auto node = neighbour.lock();
					if (closedSet.find(node) != closedSet.end())
					{
						continue;
					}

					// Update the cost of the path so far. Then update the total cost of the node by selective traversal.
					costSoFar = costSoFar + TraversalCost;
					if (openSet.find(node) != openSet.end())
					{
						if (costSoFar < node->PathCost())
						{
							node->SetParent(currentNode);
							node->SetPathCost(costSoFar);
						}
					}
					else
					{
						node->SetHeuristic(heuristicFunction(end->Location(), node->Location()));
						node->SetParent(currentNode);
						node->SetPathCost(costSoFar);
						openSet.insert(node);
					}
				}

				if (openSet.empty())
				{
					break;
				}

				// currentNode is the node with the lowest heuristic
				currentNode = *min_element(openSet.begin(), openSet.end(),
					[](const shared_ptr<Node> a, const shared_ptr<Node> b)
				{
					return (a->TotalCost() < b->TotalCost());
				});

				openSet.erase(openSet.find(currentNode));
				closedSet.insert(currentNode);

				if (currentNode->Type() == NodeType::Normal)
				{
					currentNode->SetType(NodeType::Traversed);
				}
			} while (currentNode != end);

			return BuildPath(start, end);
		}
	}
}