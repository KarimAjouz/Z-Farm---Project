#include "AssetManager.h"
#include <iostream>

namespace ZEngine
{

	AssetManager::AssetManager()
	{
	}


	AssetManager::~AssetManager()
	{
	}


	void AssetManager::LoadTexture(std::string name, std::string filePath)
	{
		if (_textures.count(name) == 0)
		{
			sf::Texture tex;

			if (tex.loadFromFile(filePath))
				this->_textures[name] = tex;
			else
				throw std::runtime_error("AssetManager::LoadTexture - Failed to load " + name + " at filepath " + filePath);
		}

	}

	sf::Texture & AssetManager::GetTexture(std::string name)
	{
		if (_textures.count(name) == 1)
			return this->_textures.at(name);
		else
		{
			std::cout << "AssetManager::GetTexture - Failed to get " << name << std::endl;
			throw std::runtime_error("AssetManager::GetTexture - Failed to get " + name);
		}
	}


	void AssetManager::LoadFont(std::string name, std::string filePath)
	{
		sf::Font font;

		if (_fonts.count(name) == 0)
		{
			if (font.loadFromFile(filePath))
				this->_fonts[name] = font;
			else
				throw std::runtime_error("AssetManager::LoadFont - Failed to load " + name + " at filepath " + filePath);
		}
	}

	sf::Font & AssetManager::GetFont(std::string name)
	{
		if (_fonts.count(name) == 1)
			return this->_fonts.at(name);
		else
			throw std::runtime_error("AssetManager::GetFont - Failed to get " + name);


	}
}