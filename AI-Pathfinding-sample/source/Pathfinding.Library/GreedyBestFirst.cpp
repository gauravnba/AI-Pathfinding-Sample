#include "pch.h"
#include "GreedyBestFirst.h"
#include "Utility.h"
#include <algorithm>

using namespace std;
using namespace Library;

namespace AI
{
	namespace PathFinding
	{
		deque<shared_ptr<Node>> GreedyBestFirst::FindPath(shared_ptr<Node> start, shared_ptr<Node> end, set<shared_ptr<Node>>& closedSet)
		{
			set<shared_ptr<Node>> openSet;
			auto currentNode = start;
			closedSet.insert(currentNode);

			do
			{
				// For each neighbour, set the heuristic.
				for (auto neighbour : currentNode->Neighbours())
				{
					auto node = neighbour.lock();
					if (closedSet.find(node) != closedSet.end())
					{
						continue;
					}
					else
					{
						node->SetParent(currentNode);
						if (openSet.find(node) == openSet.end())
						{
							node->SetHeuristic(Utility::ManhattanDistance(end->Location(), node->Location()));
							openSet.insert(node);

							// Set node to traversed.
							if (node->Type() == NodeType::Normal)
							{
								node->SetType(NodeType::Traversed);
							}
						}
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
					return (a->Heuristic() < b->Heuristic());
				});

				openSet.erase(openSet.find(currentNode));
				closedSet.insert(currentNode);
			} while (currentNode != end);

			return BuildPath(start, end);
		}
	}
}