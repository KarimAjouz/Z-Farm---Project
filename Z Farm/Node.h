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
		Node* node;
		int cost;
	};

	std::vector<Edge> edges;

	sf::CircleShape nodeArea;

	sf::Vector2f GetNodeLocation() { return nodeArea.getPosition(); }

	void GenerateNodeList(std::vector<Node>* nodeMap, std::vector<Tile> tiles);

private:
	
	Edge MakeEdge(Node* node, int cost);
};

