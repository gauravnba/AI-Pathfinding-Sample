#include "pch.h"
#include "BreadthFirst.h"

using namespace std;
using namespace Library;

namespace AI
{
	namespace PathFinding
	{
		deque<shared_ptr<Node>> BreadthFirst::FindPath(shared_ptr<Node> start, shared_ptr<Node> end, set<shared_ptr<Node>>& closedSet)
		{
			deque<shared_ptr<Node>> frontier;
			deque<shared_ptr<Node>> path;
			bool foundEnd = false;

			frontier.push_front(start);

			// Traverse each node in the graph.
			do
			{
				shared_ptr<Node> currentParent = frontier.back();
				frontier.pop_back();

				for (auto weak_node : currentParent->Neighbors())
				{
					auto node = weak_node.lock();

					if (node->Type() == NodeType::End)
					{
						node->SetParent(currentParent);
						foundEnd = true;
						break;
					}
					// If the node hasn't been traversed and isn't a wall.
					if (node->Type() == NodeType::Normal)
					{
						frontier.push_front(node);
						node->SetType(NodeType::Traversed);

						// Enter node into closedSet
						node->SetParent(currentParent);
						closedSet.insert(node);
					}
				}
			} while (!frontier.empty() && !foundEnd);

			// Build the path to return
			auto currentNode = end->Parent().lock();
			while (currentNode != start)
			{
				path.push_front(currentNode);
				currentNode = currentNode->Parent().lock();
			}
			return path;
		}
	}
}