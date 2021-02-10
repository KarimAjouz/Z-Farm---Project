#include "Menu_Scale.h"

#include "Definitions.h"

namespace ZEngine
{
	Menu_Scale::Menu_Scale()
	{
	}

	Menu_Scale::Menu_Scale(std::string name, int min, int max, int interval, int currentVal, sf::Vector2f pos, GameDataRef data) :
		_name(name),
		_min(min),
		_max(max),
		_interval(interval),
		_currentVal(currentVal),
		_pos(pos),
		_data(data),
		_lArrow("<", data, pos, sf::Color::Black, SCALE_BUTTON_FOLDER_FILEPATH, "Scale Button"),
		_rArrow(">", data, sf::Vector2f(pos.x + 200.0f, pos.y), sf::Color::Black, SCALE_BUTTON_FOLDER_FILEPATH, "Scale Button"),
		_steps((max - min) / interval)
	{
		std::string fPath = SCALE_BUTTON_FOLDER_FILEPATH;
		_data->assetManager.LoadFont("Scale Font", fPath + "Font.ttf");

		_scaleText.setFont(_data->assetManager.GetFont("Scale Font"));
		_scaleText.setPosition(sf::Vector2f(_pos.x + 100.0f, _pos.y));
		_scaleText.setFillColor(sf::Color::Black);
		_scaleText.setString(_name + ": " + std::to_string(_currentVal));
	}

	Menu_Scale::~Menu_Scale()
	{

	}

	void Menu_Scale::Update(float dT) 
	{
		if (TestLeft())
			LeftAction();

		if (TestRight())
			RightAction();

		_lArrow.Update(dT);
		_rArrow.Update(dT);

		_scaleText.setString(_name + ": " + std::to_string(_currentVal));
		_scaleText.setOrigin(_scaleText.getLocalBounds().width / 2, _scaleText.getLocalBounds().height / 2);
	}

	void Menu_Scale::Draw()
	{
		_lArrow.Draw();
		_rArrow.Draw();

		_data->window.draw(_scaleText);
	}
	
	int Menu_Scale::GetValue()
	{
		return _currentVal;
	}

	bool Menu_Scale::TestLeft()
	{
		if (_lArrow.Active)
			return true;

		return false;
	}

	bool Menu_Scale::TestRight()
	{
		if (_rArrow.Active)
			return true;

		return false;
	}

	void Menu_Scale::LeftAction()
	{
		if(_currentVal > _min)
			_currentVal -= _interval;
	}

	void Menu_Scale::RightAction()
	{
		if (_currentVal < _max)
			_currentVal += _interval;
	}
}