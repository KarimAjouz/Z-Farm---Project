//#pragma once
//
//#include "SFML/Graphics.hpp"
//#include <vector>
//#include "Tile.h"
//
//
//class Node
//{
//public:
//	struct reached
//	{
//		bool b = false;
//	};
//
//	enum class Type
//	{
//		none,
//		leftPlatform,
//		rightPlatform,
//		platform,
//		soloPlatform
//	};
//
//	Node();
//	Node(sf::Vector2f pos);
//	Node(sf::Vector2f pos, int inIndex, Type inType);
//	~Node();
//
//	struct Edge
//	{
//		enum class Type
//		{
//			walk,
//			drop,
//			jump,
//			invalid
//		};
//
//		sf::Vector2f destinationCoords = sf::Vector2f(0.f, 0.f);
//		int cost = 0;
//		Type type = Type::invalid;
//		JumpTrajectory JumpTrajectory;
//
//		bool operator == (Edge const& obj)
//		{
//			if (destinationCoords != obj.destinationCoords)
//				return false;
//
//			if (cost != obj.cost)
//				return false;
//
//			if (type != obj.type)
//				return false;
//
//			if (JumpTrajectory.startVel != obj.JumpTrajectory.startVel)
//				return false;
//
//			return true;
//
//		}
//
//		bool operator != (Edge const& obj)
//		{
//			if (destinationCoords != obj.destinationCoords)
//				return true;
//
//			if (cost != obj.cost)
//				return true;
//
//			if (type != obj.type)
//				return true;
//
//			if (JumpTrajectory.startVel != obj.JumpTrajectory.startVel)
//				return true;
//
//			return false;
//
//		}
//	};
//
//	std::vector<Edge> edges = std::vector<Edge>();
//
//	sf::CircleShape nodeArea;
//
//	sf::Vector2f GetNodeLocation() { return nodeArea.getPosition(); }
//
//	void GenerateNodeList(std::vector<Node*>* nodeMap, std::vector<Tile> tiles);
//
//	int platformIndex;
//	Type type = Type::none;
//
//	void SetupNode(std::vector<Node*>* inNodeList, std::vector<Tile> tiles);
//
//	std::map<int, reached> platformsReached;
//
//	bool operator== (const Node& obj)
//	{
//		if (obj.type == type && obj.nodeArea.getPosition() == nodeArea.getPosition())
//			return true;
//		
//		return false;
//	}
//
//	bool operator!= (const Node& obj)
//	{
//		if (obj.type == type && obj.nodeArea.getPosition() == nodeArea.getPosition())
//			return false;
//
//		return true;
//	}
//
//private:
//	
//
//	bool CheckSpaceIsClear(sf::Vector2f pos, std::vector<Tile> tiles);
//	
//};
//
