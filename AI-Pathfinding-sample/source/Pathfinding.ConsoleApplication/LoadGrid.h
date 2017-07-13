#pragma once

namespace std
{
	class string;
}

namespace AI
{
	class LoadGrid
	{
	public:
		static void LoadAndDisplayGrid(const std::string& filePath);
	};
}