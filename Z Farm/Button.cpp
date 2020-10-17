#pragma once
#include "Button.h"
#include "GameState_Splash.h"

#include <iostream>

namespace ZEngine
{
	Button::Button(std::string text, GameDataRef data, sf::Vector2f pos, sf::Color textColour, Type t) :
		_data(data),
		_textColour(textColour),
		_type(t)
	{
		sprite.setPosition(pos);
		_text.setString(text);
		_text.setFillColor(textColour);
		_text.setPosition(pos);
	}

	Button::~Button()
	{

	}

	void Button::Init()
	{

		sprite.setTexture(_data->assetManager.GetTexture("Button Default"));

		sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);

		_text.setFont(_data->assetManager.GetFont("Button Font"));

		_text.setOrigin(_text.getLocalBounds().width / 2, _text.getLocalBounds().height / 2);
	}

	void Button::Update(float dT)
	{
		sf::IntRect rect(
			sprite.getPosition().x - sprite.getGlobalBounds().width / 2,
			sprite.getPosition().y - sprite.getGlobalBounds().height / 2, 
			sprite.getGlobalBounds().width, 
			sprite.getGlobalBounds().height);

		if (rect.contains(sf::Mouse::getPosition(_data->window)) && !Engaged)
		{
			SetHovered();
		}
		else if (rect.contains(sf::Mouse::getPosition(_data->window)) && Engaged)
		{
			SetClicked();
		}
		else
		{
			SetDefault();
		}
	}

	void Button::Activate()
	{
		switch (_type)
		{
		case Type::quit:
			_data->window.close();
			break;
		}
	}

	void Button::Draw(float dT)
	{
		_data->window.draw(sprite);
		_data->window.draw(_text);
	}

	void Button::SetDefault()
	{
		sprite.setTexture(_data->assetManager.GetTexture("Button Default"));
	}

	void Button::SetHovered()
	{
		sprite.setTexture(_data->assetManager.GetTexture("Button Hovered"));
	}

	void Button::SetClicked()
	{
		sprite.setTexture(_data->assetManager.GetTexture("Button Clicked"));
	}

}