//#pragma once
//
//#include "Definitions.h"
//#include "Game.h"
//
//#include <box2d.h>
//
//class Tile
//{
//public:
//	Tile(ZEngine::GameDataRef data, b2World* worldRef, std::string name, std::string path, bool collision, sf::Vector2f pos, sf::IntRect frameRect);
//	~Tile();
//
//	void Update(float dT);
//	void Draw();
//
//	void GenPhysics(b2World* worldRef, sf::IntRect frameRect);
//	void RemovePhysics();
//
//	sf::Sprite sprite;
//
//
//	CollisionTag collisionTag = CollisionTag::def;
//private:
//	ZEngine::GameDataRef _data;
//
//	b2Body* tileBody = nullptr;
//
//
//
//
//};
//
