#include "ResourceBar.h"

#include "Definitions.h"

namespace ZEngine
{
	ResourceBar::ResourceBar(GameDataRef data, std::string filepath, std::string texName, sf::Vector2f pos) :
		_data(data),
		_texName(texName),
		_centralised(false),
		_scaleFactor(1.0f)
	{
		_data->assetManager.LoadTexture(_texName + "_BG", filepath + "_Background.png");
		_data->assetManager.LoadTexture(_texName + "_FG", filepath + "_Foreground.png");

		_background.setTexture(_data->assetManager.GetTexture(texName + "_BG"));
		_foreground.setTexture(_data->assetManager.GetTexture(texName + "_FG"));

		Move(pos);
	}

	ResourceBar::~ResourceBar()
	{
	}

	void ResourceBar::Update(float dT)
	{
	}

	void ResourceBar::Draw()
	{
		_data->GameWindow.draw(_background);
		_data->GameWindow.draw(_foreground);
	}

	void ResourceBar::Move(sf::Vector2f pos)
	{
		_background.setPosition(pos);

		if (_centralised)
			_foreground.setPosition(pos.x - (_background.getLocalBounds().width * _scaleFactor / 2), pos.y - _background.getLocalBounds().height / 2);
		else
			_foreground.setPosition(pos);
	}

	void ResourceBar::ResizeForeground(float per)
	{
		_foreground.setScale(_data->assetManager.GetTexture(_texName + "_FG").getSize().x * (per / 100.0f) * _scaleFactor, 1.0f);
	}

	void ResourceBar::ReScaleWidth(float sf)
	{
		_background.setScale(sf, _background.getScale().y);
		_scaleFactor = sf;
	}

	void ResourceBar::Centralise()
	{
		_background.setOrigin(_background.getLocalBounds().width / 2, _background.getLocalBounds().height / 2);
		_centralised = true;
	}
}