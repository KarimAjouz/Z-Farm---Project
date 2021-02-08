#include "ResourceBar.h"

#include "Definitions.h"

namespace ZEngine
{


	ResourceBar::ResourceBar(GameDataRef data, std::string filepath, std::string texName, sf::Vector2f pos) :
		_data(data),
		_texName(texName)
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
		_data->window.draw(_background);
		_data->window.draw(_foreground);
	}

	void ResourceBar::Move(sf::Vector2f pos)
	{
		_background.setPosition(pos);
		_foreground.setPosition(pos);
	}

	void ResourceBar::ResizeForeground(float per)
	{
		_foreground.setScale(_data->assetManager.GetTexture(_texName + "_FG").getSize().x * (per / 100.0f), 1.0f);
	}

}