#pragma once
#include "Button.h"
#include "GameState_Splash.h"
#include "Definitions.h"

#include <iostream>

namespace ZEngine
{
	Button::Button() :
		Engaged(false),
		Active(false)
	{

	}

	Button::Button(std::string text, GameDataRef data, sf::Vector2f pos, sf::Color textColour, std::string filePath, std::string fileName) :
		_data(data),
		_textColour(textColour),
		Engaged(false),
		Active(false),
		_fileName(fileName)
	{
		_data->assetManager.LoadTexture(_fileName + " Default", filePath + "Default.png");
		_data->assetManager.LoadTexture(_fileName + " Hovered", filePath + "Hovered.png");
		_data->assetManager.LoadTexture(_fileName + " Clicked", filePath + "Clicked.png");
		_data->assetManager.LoadFont(	_fileName + " Font",	   filePath + "Font.ttf");

		sprite.setPosition(pos);
		_text.setString(text);
		_text.setFillColor(textColour);
		_text.setPosition(pos);

		sprite.setTexture(_data->assetManager.GetTexture(_fileName + " Default"));

		sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);

		_text.setFont(_data->assetManager.GetFont(_fileName + " Font"));

		_text.setOrigin(_text.getLocalBounds().width / 2, _text.getLocalBounds().height / 2);
	}

	Button::~Button()
	{

	}

	void Button::Init()
	{


	}

	void Button::Update(float dT)
	{
		Active = false;

		sf::IntRect rect(
			sprite.getPosition().x - sprite.getGlobalBounds().width / 2,
			sprite.getPosition().y - sprite.getGlobalBounds().height / 2, 
			sprite.getGlobalBounds().width, 
			sprite.getGlobalBounds().height);

		if (rect.contains(sf::Mouse::getPosition(_data->window)) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			Engaged = true;
		
		if (Engaged && !rect.contains(sf::Mouse::getPosition(_data->window)))
			Engaged = false;

		if (rect.contains(sf::Mouse::getPosition(_data->window)) && !sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && Engaged)
			Activate();

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
		Active = true;
		Engaged = false;
	}

	void Button::Draw()
	{
		_data->window.draw(sprite);
		_data->window.draw(_text);
	}

	void Button::SetDefault()
	{
		sprite.setTexture(_data->assetManager.GetTexture(_fileName + " Default"));
	}

	void Button::SetHovered()
	{
		sprite.setTexture(_data->assetManager.GetTexture(_fileName + " Hovered"));
	}

	void Button::SetClicked()
	{
		sprite.setTexture(_data->assetManager.GetTexture(_fileName + " Clicked"));
	}

}