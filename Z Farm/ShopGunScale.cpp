#include "ShopGunScale.h"

#include "Definitions.h"

ShopGunScale::ShopGunScale(std::string name, int min, int max, int interval, int currentVal, sf::Vector2f pos, ZEngine::GameDataRef data, int starterCost, int costIncreaseFactor, int* zombits) :
	_data(data),
	_cost(starterCost),
	_costIncrease(costIncreaseFactor),
	_name(name),
	_min(min),
	_max(max),
	_interval(interval),
	_currentVal(currentVal),
	_pos(pos),
	_steps((max - min) / interval),
	_lArrow("<", data, pos, sf::Color::Black, SCALE_BUTTON_FOLDER_FILEPATH, "Scale Button"),
	_rArrow(">", data, sf::Vector2f(pos.x + 200.0f, pos.y), sf::Color::Black, SCALE_BUTTON_FOLDER_FILEPATH, "Scale Button"),
	_zombits(zombits)
{
	std::string fPath = SCALE_BUTTON_FOLDER_FILEPATH;
	_data->assetManager.LoadFont("Scale Font", fPath + "Font.ttf");

	_scaleText.setFont(_data->assetManager.GetFont("Scale Font"));
	_scaleText.setPosition(sf::Vector2f(_pos.x + 100.0f, _pos.y));
	_scaleText.setFillColor(sf::Color::Black);
	_scaleText.setString(_name + ": " + std::to_string(_currentVal));
	_scaleText.setOrigin(_scaleText.getLocalBounds().width / 2, _scaleText.getLocalBounds().height / 2);

	_costText.setFont(_data->assetManager.GetFont("Scale Font"));
	_costText.setPosition(sf::Vector2f(_pos.x + 300.0f, _pos.y));
	_costText.setFillColor(sf::Color::Black);
	_costText.setString("Cost: " + std::to_string(_cost));
	_costText.setOrigin(_costText.getLocalBounds().width / 2, _costText.getLocalBounds().height / 2);
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
}

void ShopGunScale::LeftAction()
{
	if (_currentVal > _min)
	{
		*_zombits += _cost;
		_cost -= _costIncrease;

		_currentVal -= _interval;


		_costText.setString("Cost: " + std::to_string(_cost));
		_costText.setOrigin(_costText.getLocalBounds().width / 2, _costText.getLocalBounds().height / 2);

		_scaleText.setString(_name + ": " + std::to_string(_currentVal));
		_scaleText.setOrigin(_scaleText.getLocalBounds().width / 2, _scaleText.getLocalBounds().height / 2);
	}
}

void ShopGunScale::RightAction()
{
	if(*_zombits > _cost && _currentVal < _max)
	{
		*_zombits -= _cost;
		_cost += _costIncrease;

		_currentVal += _interval;


		_costText.setString("Cost: " + std::to_string(_cost));
		_costText.setOrigin(_costText.getLocalBounds().width / 2, _costText.getLocalBounds().height / 2);

		_scaleText.setString(_name + ": " + std::to_string(_currentVal));
		_scaleText.setOrigin(_scaleText.getLocalBounds().width / 2, _scaleText.getLocalBounds().height / 2);
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
	return _currentVal;
}