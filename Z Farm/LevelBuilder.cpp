#include "LevelBuilder.h"
#include "Definitions.h"


#include <fstream>
#include <iostream>

LevelBuilder::LevelBuilder(ZEngine::GameDataRef data, Room* roomRef) :
	_data(data),
	_curSelectedTexture(),
	_roomRef(roomRef)
{
	_data->assetManager.LoadTexture("Tiles", TILE_PATH);
	_curSelectedTexture.setTexture(_data->assetManager.GetTexture("Tiles"));
	_curSelectedTexture.setTextureRect(_texRect);

	_curTextureOutline.setSize(sf::Vector2f(_texRect.width + 2, _texRect.height + 2));
	_curTextureOutline.setOutlineColor(sf::Color::Magenta);
	_curTextureOutline.setFillColor(sf::Color::Transparent);
	_curTextureOutline.setOutlineThickness(1);

	_hoveredTile.setSize(sf::Vector2f(_texRect.width + 2, _texRect.height + 2));
	_hoveredTile.setOutlineThickness(1);
	_hoveredTile.setOrigin(16, 16);
	_hoveredTile.setOutlineColor(sf::Color::Green);
	_hoveredTile.setFillColor(sf::Color::Transparent);
	_hoveredTile.setScale(2.0f, 2.0f);
}

LevelBuilder::~LevelBuilder()
{
}

void LevelBuilder::Scroll(int dir)
{
	if (dir == 1)
		_texRect.left += 32;
	else if (dir == -1)
		_texRect.left -= 32;

	_texRect.top = ((_texRect.left / _data->assetManager.GetTexture("Tiles").getSize().x) * 32 % _data->assetManager.GetTexture("Tiles").getSize().y);
	
	sf::IntRect temp = sf::IntRect(_texRect.left % _data->assetManager.GetTexture("Tiles").getSize().x, _texRect.top, 32, 32);

	_curSelectedTexture.setTextureRect(temp);
}

void LevelBuilder::Update(float dT)
{
	sf::Vector2i mousePos = sf::Vector2i(sf::Mouse::getPosition(_data->window));
	_curTextureOutline.setPosition(sf::Vector2f(mousePos.x, mousePos.y - 34.0f));
	_curSelectedTexture.setPosition(sf::Vector2f(mousePos.x, mousePos.y - 33.0f));
	_hoveredTile.setPosition(sf::Vector2f((mousePos.x / 64 * 64 + 30), (mousePos.y / 64 * 64) + 30));

	


}

void LevelBuilder::Draw()
{
	_data->window.draw(_hoveredTile);
	_data->window.draw(_curSelectedTexture);
	_data->window.draw(_curTextureOutline);
}

void LevelBuilder::AddTile()
{
	sf::Vector2i tilePos = sf::Vector2i(sf::Mouse::getPosition(_data->window) / 64);
	_roomRef->AddTile(tilePos.x, tilePos.y, _texRect.left % _data->assetManager.GetTexture("Tiles").getSize().x, _texRect.top);

}

void LevelBuilder::RemoveTile()
{
	sf::Vector2i tilePos = sf::Vector2i(sf::Mouse::getPosition(_data->window) / 64);
	_roomRef->RemoveTile(tilePos.x, tilePos.y);
}

void LevelBuilder::ReplaceTile()
{
	RemoveTile();
	AddTile();
}

void LevelBuilder::SaveLevel()
{
	std::string lName;

	std::cout << "Level Name: ";
	std::cin >> lName;
	std::cout << std::endl;

	if (CheckForLevel(lName))
	{
		std::string overwrite;

		std::cout << "Are you sure you want to overrite level: " << lName << " ? (Y/N): ";
		std::cin >> overwrite;
		std::cout << std::endl;

		if (overwrite != "Y")
		{
			std::cout << "Save Cancelled" << std::endl;
			return;
		}
	}

	std::string filePath = LEVEL_PATH + lName + ".txt";

	std::ofstream output;
	output.open(filePath, std::ofstream::out | std::ofstream::trunc);



	if (output.is_open())
	{
		std::vector<std::vector<sf::Vector2i>> map = _roomRef->GetMap();

		for (int y = 0; y < map.size(); y++)
		{
			for (int x = 0; x < map[0].size(); x++)
			{
				std::string numX = std::to_string(map[y][x].x);
				std::string numY = std::to_string(map[y][x].y);

				if (numX.size() == 1)
					numX = "0" + numX;
				if (numY.size() == 1)
					numY = "0" + numY;

				output << numX << "/" << numY;

				if (x != map[0].size() - 1)
					output << ", ";
			}
			output << "\n";
		}
	}
}

void LevelBuilder::LoadLevel()
{
	std::string lName;

	std::cout << "Level to load Name: ";
	std::cin >> lName;
	std::cout << std::endl;

	if (CheckForLevel(lName))
	{
		std::vector<std::vector<sf::Vector2i>> map = _roomRef->GetMap();

		std::string filePath = LEVEL_PATH + lName;
		std::ifstream input(filePath + ".txt");

		std::string line;

		if (input.is_open())
		{
			int y = 0;
			while (getline(input, line))
			{
				for (int i = 0; i < line.size(); i += 7)
				{
					int xTile = std::stoi(line.substr(i, 2));
					int yTile = std::stoi(line.substr(i + 3, 2));

					map[y][i / 7] = sf::Vector2i(xTile, yTile);
				}
				y++;
			}
		}

		_roomRef->SetMap(map);
		_roomRef->BuildLevel();
	}
	else
	{
		std::cout << "LOAD ABORTED. Could not find level with Name: " << lName <<std::endl;
	}
}

bool LevelBuilder::CheckForLevel(std::string levelName)
{
	std::string filePath = LEVEL_PATH + levelName;
	std::ifstream input;
	input.open(filePath + ".txt");
	if (input.is_open())
		return true;

	return false;
}