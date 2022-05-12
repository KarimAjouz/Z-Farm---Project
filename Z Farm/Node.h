#pragma once

#include "SFML/Graphics.hpp"
#include <vector>
#include "Tile.h"


class Node
{
public:
	struct reached
	{
		bool b = false;
	};

	enum class Type
	{
		none,
		leftPlatform,
		rightPlatform,
		platform,
		soloPlatform
	};

	Node(sf::Vector2f pos);
	Node(sf::Vector2f pos, int inIndex, Type inType);
	~Node();

	struct Edge
	{
		enum class Type
		{
			walk,
			drop,
			jump
		};

		sf::Vector2f destinationCoords = sf::Vector2f(0.f, 0.f);
		int cost = 0;
		Type type;
		JumpTrajectory JumpTrajectory;

	};

	std::vector<Edge> edges = std::vector<Edge>();

	sf::CircleShape nodeArea;

	sf::Vector2f GetNodeLocation() { return nodeArea.getPosition(); }

	void GenerateNodeList(std::vector<Node*>* nodeMap, std::vector<Tile> tiles);

	int platformIndex;
	Type type = Type::none;

	void SetupNode(std::vector<Node*>* inNodeList, std::vector<Tile> tiles);

	std::map<int, reached> platformsReached;

private:
	

	bool CheckSpaceIsClear(sf::Vector2f pos, std::vector<Tile> tiles);
	
};

