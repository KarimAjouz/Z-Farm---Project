#include "ShopGunScale.h"

#include "Definitions.h"

ShopGunScale::ShopGunScale(std::string name, std::vector<BalanceSheet::gunStatProduct>* scaleData, ZEngine::GameDataRef data, sf::Vector2f pos, int* zombits, int start) :
	_name(name),
	_scaleData(scaleData),
	_data(data),
	_pos(pos),
	_zombits(zombits),
	_index(start),
	_tierSprites(),
	_lArrow("<", data, pos, sf::Color::Black, SCALE_BUTTON_FOLDER_FILEPATH, "Scale Button"),
	_rArrow(">", data, sf::Vector2f(pos.x + 200.0f, pos.y), sf::Color::Black, SCALE_BUTTON_FOLDER_FILEPATH, "Scale Button")
{
	std::string fPath = SCALE_BUTTON_FOLDER_FILEPATH;
	_data->assetManager.LoadFont("Scale Font", fPath + "Font.ttf");

	_scaleText.setFont(_data->assetManager.GetFont("Scale Font"));
	_scaleText.setPosition(sf::Vector2f(_pos.x + 100.0f, _pos.y));
	_scaleText.setFillColor(sf::Color::Black);
	_scaleText.setString(_name + ": " + std::to_string(_scaleData->at(_index).value));
	_scaleText.setScale(0.6f, 0.6f);
	_scaleText.setOrigin(_scaleText.getLocalBounds().width / 2, _scaleText.getLocalBounds().height / 2);

	_costText.setFont(_data->assetManager.GetFont("Scale Font"));
	_costText.setPosition(sf::Vector2f(_pos.x + 300.0f, _pos.y));
	_costText.setFillColor(sf::Color::Black);

	if (_index == _scaleData->size() - 1)
		_costText.setString("Cost: Maxed Out");
	else
		_costText.setString("Cost: " + std::to_string(_scaleData->at(_index + 1).cost));

	_costText.setOrigin(_costText.getLocalBounds().width / 2, _costText.getLocalBounds().height / 2);

	_data->assetManager.LoadTexture("Unpurchased Tier", UNPURCHASED_TIER_FILEPATH);
	_data->assetManager.LoadTexture("Purchased Tier", PURCHASED_TIER_FILEPATH);

	for (int i = 0; i < _scaleData->size(); i++)
	{
		sf::Sprite s;
		s.setPosition(pos.x + 50 + (10 * i), pos.y - 20.0f);

		if(i >= start)
			s.setTexture(_data->assetManager.GetTexture("Purchased Tier"));
		else
			s.setTexture(_data->assetManager.GetTexture("Unpurchased Tier"));

		_tierSprites.push_back(s);
	}
}

ShopGunScale::~ShopGunScale()
{
}

void ShopGunScale::Update(float dT)
{
	if (TestLeft())
		LeftAction();

	if (TestRight())
		RightAction();

	_lArrow.Update(dT);
	_rArrow.Update(dT);

}

void ShopGunScale::Draw()
{
	_lArrow.Draw();
	_rArrow.Draw();

	_data->window.draw(_scaleText);
	_data->window.draw(_costText);

	for (int i = 0; i < _tierSprites.size(); i++)
	{
		_data->window.draw(_tierSprites.at(i));
	}
}

void ShopGunScale::LeftAction()
{
	if (_index > 0)
	{
		_tierSprites.at(_index).setTexture(_data->assetManager.GetTexture("Unpurchased Tier"));

		*_zombits += _scaleData->at(_index).refund;
		_index--;

		_costText.setString("Cost: " + std::to_string(_scaleData->at(_index + 1).cost));

		_scaleText.setString(_name + ": " + std::to_string(_scaleData->at(_index).value));
	}
}

void ShopGunScale::RightAction()
{
	if(_index < _scaleData->size() - 1)
	{
		if (*_zombits >= _scaleData->at(_index + 1).cost)
		{
			_index++;
			*_zombits -= _scaleData->at(_index).cost;


			_tierSprites.at(_index).setTexture(_data->assetManager.GetTexture("Purchased Tier"));

			if(_index < _scaleData->size() - 1)
				_costText.setString("Cost: " + std::to_string(_scaleData->at(_index + 1).cost));
			else
				_costText.setString("Cost: Maxed Out");


			_scaleText.setString(_name + ": " + std::to_string(_scaleData->at(_index).value));
		}
	}
}

bool ShopGunScale::TestLeft()
{
	if (_lArrow.Active)
		return true;

	return false;
}

bool ShopGunScale::TestRight()
{
	if (_rArrow.Active)
		return true;

	return false;
}

int ShopGunScale::GetValue()
{
	return _scaleData->at(_index).value;
}

int ShopGunScale::GetIndex()
{
	return _index;
}