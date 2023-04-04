//#pragma once
//#include "Node.h"
//
//class NavMap
//{
//public:
//	NavMap();
//	~NavMap();
//
//	struct Platform
//	{
//		std::vector<Node*> nodes;
//
//		int platformIndex;
//
//		std::map<int, float> platformsReachedToCostMap;
//
//		Platform()
//		{
//			nodes = std::vector<Node*>();
//			platformIndex = -1;
//		}
//	};
//
//
//	void GenerateNavMap(std::vector<Tile>* InTiles);
//
//	std::vector<Platform> GetMap() { return _map; };
//
//	void ClearMap();
//
//	void GenerateEdges(std::vector<Tile>* inTiles);
//
//	Node* GetNodeAtLocation(sf::Vector2f pos);
//
//
//	Node* GetNodeColWithRect(sf::RectangleShape InRect);
//
//
//private:
//
//
//
//	std::vector<Platform> _map;
//
//	sf::Vector2f CalculateDropEdgePos(sf::Vector2f inPos);
//
//	bool DoesPointCollideWithLevel(sf::Vector2f InPos, std::vector<Tile>* InTiles, JumpTrajectory InJump, Node* InCurNode);
//
//	bool DoesRectCollideWithLevel(sf::RectangleShape InRect, std::vector<Tile>* InTiles, JumpTrajectory InJump, Node* InCurNode, bool inIsDirUp);
//
//	bool IsJumpCostCheapestPlatformJump(int InStartingPlatformIndex, int InEndingPlatformIndex, float InJumpCost, int& InOutEdgeIndex, int& InOutExpensiveNodeIndex);
//
//};
//
