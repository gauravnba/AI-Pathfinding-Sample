#include "pch.h"

#include <string>
#include "Main.h"

#include "BreadthFirst.h"
#include "GreedyBestFirst.h"
#include "Dijkstra.h"

using namespace std;
using namespace Library;
using namespace AI::PathFinding;

namespace AI
{
	Main::Main(const string& gridFile) :
		mGridFile(gridFile)
	{
	}

	void Main::Run()
	{
		bool repeat = true;
		while (repeat)
		{
			mGraph = GridHelper::LoadGridFromFile(mGridFile);
			GridHelper::PrintGridFromGraph(mGraph);

			Point start, end;
			SetStartAndEndPoints(start, end);

			BreadthFirst breadthFirstSearch;
			cout << "\n******************************** Breadth First Search ********************************\n" << endl;
			UpdateGraphWithPath(start, end, breadthFirstSearch);

			GreedyBestFirst greedyBestFirst;
			cout << "\n******************************** Greedy Best First Search ********************************\n" << endl;
			UpdateGraphWithPath(start, end, greedyBestFirst);

			Dijkstra dijkstra;
			cout << "\n******************************** Dijkstra Shortest Path Search ********************************\n" << endl;
			UpdateGraphWithPath(start, end, dijkstra);

			AStar aStar;
			cout << "\n******************************** A* Shortest Path Search ********************************\n" << endl;
			UpdateGraphWithPath(start, end, aStar);

			cout << "\n******************************** Another round? (y) ********************************" <<endl;
			string temp;
			cin >> temp;
			if (temp != "y")
			{
				repeat = false;
			}
		}
	}

	inline void Main::SetStartAndEndPoints(Point& start, Point& end)
	{
		string input;
		bool isValid = true;

		// Get value of start point and check if it is valid or not. Move on if it is.
		while (isValid)
		{
			cout << "Enter start point (x,y): ";
			cin >> input;
			start = GetPointFromString(input);
			if (mGraph.Contains(start) && (mGraph.At(start)->Type() == NodeType::Normal))
			{
				mGraph.At(start)->SetType(NodeType::Start);
				isValid = false;
			}
			else
			{
				cout << "**Please enter a valid point**" << endl;
			}
		}

		// Get value of end point and check if it is valid or not. Move on if it is.
		isValid = true;
		while (isValid)
		{
			cout << "Enter end point (x,y): ";
			cin >> input;
			end = GetPointFromString(input);
			if (mGraph.Contains(end) && (mGraph.At(end)->Type() == NodeType::Normal))
			{
				mGraph.At(end)->SetType(NodeType::End);
				isValid = false;
			}
			else
			{
				cout << "*Please enter a valid point**" << endl;
			}
		}
	}

	inline Point Main::GetPointFromString(const string& input)
	{
		uint32_t x = stoi(input.substr(input.find(",") - 1));
		uint32_t y = stoi(input.substr(input.find(",") + 1, input.size()-1));
		return Point(x, y);
	}

	void Main::UpdateGraphWithPath(const Point & start, const Point & end, IPathFinder& algorithm)
	{
		set<shared_ptr<Node>> closedSet;
		StopWatch stopWatch;

		stopWatch.Start();
		auto path = algorithm.FindPath(mGraph.At(start), mGraph.At(end), closedSet);
		stopWatch.Stop();
		auto elapsedTime = stopWatch.Elapsed();

		if (path.empty())
		{
			cout << "No path can be found." << endl;
			return;
		}

		for (auto node : path)
		{
			node->SetType(NodeType::Path);
		}

		GridHelper::PrintGridFromGraph(mGraph);
		cout << "\nTime taken: " << elapsedTime.count() << " microseconds" << endl;
		cout << "Nodes traversed: " << closedSet.size() << endl;
	}
}