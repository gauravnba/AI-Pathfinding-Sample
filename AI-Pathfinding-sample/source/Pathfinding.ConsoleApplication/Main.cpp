#include "pch.h"

#include <string>
#include "Main.h"
#include "IPathFinder.h"
#include "BreadthFirst.h"

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
		mGraph = GridHelper::LoadGridFromFile(mGridFile);
		GridHelper::PrintGridFromGraph(mGraph);

		Point start, end;
		SetStartAndEndPoints(start, end);

		BreadthFirst breadthFirstSearch;
		cout << "\nBreadth First Search\n" << endl;
		UpdateGraphWithPath(start, end, breadthFirstSearch);
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
			if (mGraph.At(start)->Type() != NodeType::Wall)
			{
				mGraph.At(start)->SetType(NodeType::Start);
				isValid = false;
			}
			else
			{
				cout << "**Point cannot be on the wall. Please enter a valid point**" << endl;
			}
		}

		// Get value of end point and check if it is valid or not. Move on if it is.
		isValid = true;
		while (isValid)
		{
			cout << "Enter end point (x,y): ";
			cin >> input;
			end = GetPointFromString(input);
			if (mGraph.At(end)->Type() != NodeType::Wall)
			{
				mGraph.At(end)->SetType(NodeType::End);
				isValid = false;
			}
			else
			{
				cout << "**Point cannot be on the wall. Please enter a valid point**" << endl;
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

		for (auto node : path)
		{
			node->SetType(NodeType::Path);
		}

		GridHelper::PrintGridFromGraph(mGraph);
		cout << "\nTime taken: " << elapsedTime.count() << " microseconds" << endl;
		cout << "Nodes traversed: " << closedSet.size() << endl;

		closedSet.size();
	}
}
