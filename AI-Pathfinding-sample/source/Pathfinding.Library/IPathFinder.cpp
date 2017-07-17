#include "pch.h"
#include "IPathFinder.h"

using namespace std;

namespace Library
{
	deque<shared_ptr<Node>> IPathFinder::FindPath(shared_ptr<Node> start, shared_ptr<Node> end)
	{
		set<shared_ptr<Node>> closedSet;
		return FindPath(start, end, closedSet);
	}

	deque<shared_ptr<Node>> IPathFinder::BuildPath(shared_ptr<Node> start, shared_ptr<Node> end)
	{
		deque<shared_ptr<Node>> path;

		if (end->Parent().lock() == nullptr)
		{
			return path;
		}

		auto currentNode = end->Parent().lock();
		while (currentNode != start)
		{
			path.push_front(currentNode);
			currentNode = currentNode->Parent().lock();
		}
		return path;
	}
}