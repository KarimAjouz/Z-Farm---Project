#pragma once
#include "Node.h"

class NavMap
{
public:
	NavMap();
	~NavMap();

	struct Platform
	{
		std::vector<Node*> nodes;

		Platform()
		{
			nodes = std::vector<Node*>();
		}
	};

	void GenerateNavMap(std::vector<Tile>* InTiles);

	std::vector<Platform> GetMap() { return _map; };

	void ClearMap();

	void GenerateEdges(std::vector<Tile>* inTiles);

	Node* GetNodeAtLocation(sf::Vector2f pos);

private:



	std::vector<Platform> _map;

	sf::Vector2f CalculateDropEdgePos(sf::Vector2f inPos);


};

