#pragma once

#include "Menu_Scale.h"

class ShopGunScale : public ZEngine::Menu_Scale
{
public:

	ShopGunScale(std::string name, int min, int max, int interval, int currentVal, sf::Vector2f pos, ZEngine::GameDataRef data, int starterCost, int costIncreaseFactor, int* zombits);
	~ShopGunScale();

	void Update(float dT);
	void Draw();

	int GetValue();


protected:
	ZEngine::GameDataRef _data;

	int* _zombits;

	int   _cost;
	float _costIncrease;

	sf::Text _scaleText;
	sf::Text _costText;

	std::string _name;
	int _min;
	int _max;
	int _interval;
	int _currentVal;

	sf::Vector2f _pos;


	int _steps;

	bool TestRight();
	bool TestLeft();
	void LeftAction();
	void RightAction();

	ZEngine::Button _lArrow;
	ZEngine::Button _rArrow;

};

