#include "pch.h"

#include <string>
#include "Main.h"

using namespace std;
using namespace Library;

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

		SetStartAndEndPoints();
		GridHelper::PrintGridFromGraph(mGraph);
	}

	inline void Main::SetStartAndEndPoints()
	{
		string input;
		cout << "Enter start point (x,y): ";
		cin >> input;
		mGraph.At(GetPointFromString(input))->SetType(NodeType::Start);

		cout << "Enter end point (x,y): ";
		cin >> input;
		mGraph.At(GetPointFromString(input))->SetType(NodeType::End);
	}

	inline Point Main::GetPointFromString(const string& input)
	{
		uint32_t x = stoi(input.substr(input.find(",") - 1));
		uint32_t y = stoi(input.substr(input.find(",") + 1, input.size()-1));
		return Point(x, y);
	}
}
