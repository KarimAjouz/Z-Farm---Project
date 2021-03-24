#pragma once

#include "Definitions.h"
#include "Game.h"

#include <box2d.h>

class Tile
{
public:
	Tile(ZEngine::GameDataRef data, b2World* worldRef, std::string name, std::string path, bool collision, sf::Vector2f pos, sf::IntRect frameRect);
	~Tile();

	void Update(float dT);
	void Draw();

	void GenPhysics(b2World* worldRef, sf::IntRect frameRect);
	void RemovePhysics();

private:
	ZEngine::GameDataRef _data;
	CollisionTag _collisionTag = CollisionTag::def;

	b2Body* tileBody = nullptr;

	sf::RectangleShape debugRect;
	sf::Sprite _sprite;



};
