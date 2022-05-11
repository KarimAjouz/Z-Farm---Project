#pragma once
#include "Node.h"

class NavMap
{
public:
	NavMap();
	~NavMap();

	struct reached
	{
		bool b = false;
	};

	struct Platform
	{
		std::map<int, reached> platformsReached;
		std::vector<Node*> nodes;

		Platform()
		{
			platformsReached = {};
			nodes = std::vector<Node*>();
		}
	};

	void GenerateNavMap(std::vector<Tile>* InTiles);

	std::vector<Platform> GetMap() { return _map; };

	void ClearMap();

	void GenerateEdges(std::vector<Tile>* inTiles);


private:



	std::vector<Platform> _map;

	sf::Vector2f CalculateDropEdgePos(sf::Vector2f inPos);
	Node* GetNodeAtLocation(sf::Vector2f pos);


};

