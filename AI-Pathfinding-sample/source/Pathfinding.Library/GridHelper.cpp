#include "pch.h"

#include <iostream>
#include "Node.h"
#include "GridHelper.h"
#include "Utility.h"

using namespace std;

namespace Library
{
	const map<NodeType, string> GridHelper::mNodeRepresentation = {
		{ NodeType::Normal, "-" },
		{ NodeType::Wall, "|" },
		{ NodeType::Start, "S" },
		{ NodeType::End, "E" },
		{ NodeType::Path, "X" },
		{ NodeType::Traversed, "*" }
	};

	Graph GridHelper::LoadGridFromFile(const string& filename)
	{
		int32_t gridWidth, gridHeight;

		return LoadGridFromFile(filename, gridWidth, gridHeight);
	}

	Graph GridHelper::LoadGridFromFile(const string& filename, int32_t& gridWidth, int32_t& gridHeight)
	{
		const Point NeighbourOffsets[] = { Point(-1, 0), Point(1, 0), Point(0, -1), Point(0, 1) };

		ifstream inputFile(filename);
		if (inputFile.bad())
		{
			throw exception("Could not open file.");
		}

		// Read grid representation from file
		vector<vector<NodeType>> rawGrid;
		gridWidth = -1;
		while (inputFile.good())
		{
			string line;
			getline(inputFile, line);
			auto nodes = Utility::SplitString(line, ' ');
			if (gridWidth == -1)
			{
				gridWidth = static_cast<int32_t>(nodes.size());
			}
			else if (gridWidth != static_cast<int32_t>(nodes.size()))
			{
				throw new exception("Grid width must be uniform.");
			}

			vector<NodeType> row(gridWidth);
			for (int32_t i = 0; i < gridWidth; i++)
			{
				int nodeTypeValue = atoi(nodes[i].c_str());
				row[i] = static_cast<NodeType>(nodeTypeValue);
			}

			rawGrid.push_back(row);
		}

		inputFile.close();

		// Build grid from file representation
		gridHeight = static_cast<int32_t>(rawGrid.size());
		Graph graph;
		for (int y = 0; y < gridHeight; y++)
		{
			for (int x = 0; x < gridWidth; x++)
			{
				graph.AddNode(make_shared<Node>(Point(x, y), rawGrid[y][x]));
			}
		}

		// Assign adjacent nodes
		for (int y = 0; y < gridHeight; y++)
		{
			for (int x = 0; x < gridWidth; x++)
			{
				shared_ptr<Node> node = graph.At(x, y);

				for (const Point& offset : NeighbourOffsets)
				{
					Point location(node->Location().X + offset.X, node->Location().Y + offset.Y);
					if (IsValidGridLocation(location, gridWidth, gridHeight))
					{
						shared_ptr<Node> neighbour = graph.At(location);
						if (neighbour->Type() != NodeType::Wall)
						{
							node->Neighbours().push_back(neighbour);
						}
					}
				}
			}
		}

		graph.SetEndPoint(Point(gridHeight, gridWidth));

		return graph;
	}

	void GridHelper::PrintGridFromGraph(Graph& graph)
	{
		Point currentPoint;

		for(; currentPoint.Y < graph.EndPoint().Y; ++currentPoint.Y)
		{
			for (; currentPoint.X < graph.EndPoint().X; ++currentPoint.X)
			{
				cout << mNodeRepresentation.at(graph.At(currentPoint)->Type()) << " ";

				// Reset the node to Normal, if it's a Traversed node or a Path.
				if (graph.At(currentPoint)->Type() == NodeType::Path || graph.At(currentPoint)->Type() == NodeType::Traversed)
				{
					graph.At(currentPoint)->SetType(NodeType::Normal);
				}
			}
			cout << endl;
			currentPoint.X = 0;
		}
		cout << endl;
	}

	bool GridHelper::IsValidGridLocation(const Point& location, int maxWidth, int maxLength)
	{
		return (location.X >= 0 && location.X < maxWidth) && (location.Y >= 0 && location.Y < maxLength);
	}
}