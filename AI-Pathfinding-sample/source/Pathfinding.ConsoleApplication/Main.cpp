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
	}
}
