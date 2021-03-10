#pragma once

#include "Menu_Scale.h"
#include "BalanceSheet.h"

class ShopGunScale : public ZEngine::Menu_Scale
{
public:

	ShopGunScale(std::string name, std::vector<BalanceSheet::gunStatProduct>* scaleData, ZEngine::GameDataRef data, sf::Vector2f pos, int* zombits, int start);


	~ShopGunScale();

	void Update(float dT);
	void Draw();

	int GetValue();

	int GetIndex();


protected:
	ZEngine::GameDataRef _data;
	std::string _name;

	int* _zombits;

	sf::Text _scaleText;
	sf::Text _costText;

	sf::Vector2f _pos;


	std::vector<BalanceSheet::gunStatProduct>* _scaleData;
	int _index;





	bool TestRight();
	bool TestLeft();
	void LeftAction();
	void RightAction();

	ZEngine::Button _lArrow;
	ZEngine::Button _rArrow;

	std::vector<sf::Sprite> _tierSprites;

};

