#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"


class ShopWedge
{
public:
	ShopWedge(ZEngine::GameDataRef data, float rotation);
	~ShopWedge();

	void Update(); 
	void Draw();

	void PurchaseTier();
	void CapTier();


private:
	sf::Sprite _baseSprite;
	sf::Sprite _capSprite;
	sf::Sprite _tierSprite;

	float _rotation;
	
	ZEngine::GameDataRef _data;
};

