#include "pch.h"

#include "Main.h"

using namespace AI;

int main(int argc, char* argv[])
{
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);
	
	Main game("Grid.grid");
	game.Run();

	return 0;
}