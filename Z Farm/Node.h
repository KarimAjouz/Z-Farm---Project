#pragma once

#include "SFML/Graphics.hpp"
#include <vector>
#include "Tile.h"


class Node
{
public:
	Node(sf::Vector2f pos);
	~Node();

	struct Edge
	{
		Node* node = nullptr;
		int cost = 0;
		Edge(Node* n, int c)
		{
			node = n;
			cost = c;
		}
	};

	std::vector<Edge> edges = std::vector<Edge>();

	sf::CircleShape nodeArea;

	sf::Vector2f GetNodeLocation() { return nodeArea.getPosition(); }

	void GenerateNodeList(std::vector<Node*>* nodeMap, std::vector<Tile> tiles);

private:
	

	bool CheckSpaceIsClear(sf::Vector2f pos, std::vector<Tile> tiles);
	Node* GetNodeAtLocation(sf::Vector2f pos, std::vector<Node*>* nodeMap);
};

