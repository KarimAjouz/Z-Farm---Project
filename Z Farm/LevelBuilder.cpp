#include "LevelBuilder.h"
#include "Definitions.h"
#include "AlarmPig.h"
#include "Baldy.h"
#include "Box.h"


#include <fstream>
#include <iostream>


/// <summary>
/// Creates the level builder, with relevant SFML shapes for rendering tile selection/placement.
/// </summary>
LevelBuilder::LevelBuilder(ZEngine::GameDataRef data, b2World* worldRef, Level* levelRef, Player* playerRef) :
	_data(data),
	_curSelectedTexture(),
	_levelRef(levelRef),
	_worldRef(worldRef),
	_tilePicker(_data),
	_playerRef(playerRef)
{
	_data->assetManager.LoadTexture("Tiles", TILE_PATH);
	_data->assetManager.LoadTexture("Units", UNITS_PATH);
	_curSelectedTexture.setTexture(_data->assetManager.GetTexture("Tiles"));
	_curSelectedTexture.setTextureRect(_texRect);

	_curTextureOutline.setSize(sf::Vector2f(_texRect.width + 2, _texRect.height + 2));
	_curTextureOutline.setOutlineColor(sf::Color::Magenta);
	_curTextureOutline.setFillColor(sf::Color::Transparent);
	_curTextureOutline.setOutlineThickness(1);

	_hoveredTile.setTexture(_curSelectedTexture.getTexture());
	_hoveredTile.setTextureRect(_texRect);
	_hoveredTile.setSize(sf::Vector2f(_texRect.width + 2, _texRect.height + 2));
	_hoveredTile.setOutlineThickness(1);
	_hoveredTile.setOrigin(16, 16);
	_hoveredTile.setOutlineColor(sf::Color::Green);
	
	sf::Color hoverColor = sf::Color(255, 255, 255, 100.0f);
	_hoveredTile.setFillColor(hoverColor);
	_hoveredTile.setScale(2.0f, 2.0f);

	_newRoomSelector.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	_newRoomSelector.setFillColor(sf::Color::Transparent);
	_newRoomSelector.setOutlineColor(sf::Color::Blue);
	_newRoomSelector.setOutlineThickness(5.0f);
	LoadLevel("Default");
}

LevelBuilder::~LevelBuilder()
{
}

/// <summary>
/// Scrolls the selected tile.
/// </summary>
/// <param name="dir"> The scroll direction. </param>
void LevelBuilder::Scroll(int dir)
{
	sf::View view = _data->window.getView();



	if (dir == 1)
	{
		view.setSize(view.getSize() * 1.2f);
		_curSelectedTexture.setScale(_curSelectedTexture.getScale() * 1.2f);
		_curTextureOutline.setScale(_curTextureOutline.getScale() * 1.2f);
	}
	else if (dir == -1)
	{
		view.setSize(view.getSize() / 1.2f);
		_curSelectedTexture.setScale(_curSelectedTexture.getScale() / 1.2f);
		_curTextureOutline.setScale(_curTextureOutline.getScale() / 1.2f);
	}

	_data->window.setView(view);
}

void LevelBuilder::Update(float dT)
{
	TestMouseHover();

	_tilePicker.Update(dT);
}

void LevelBuilder::Draw()
{
	_data->window.draw(_hoveredTile);
	_data->window.draw(_newRoomSelector);

	_tilePicker.Draw();
}

void LevelBuilder::MouseRelease()
{
	if (!_tilePicker.active)
	{
		switch (_tilePicker.state)
		{
			case TilePicker::State::shipTiles:
				if (_inRoom)
					ReplaceTile();
				else
					NewRoom();
				break;
			case TilePicker::State::units:
				if (_inRoom)
					AddUnit(_entityType);
				else
					NewRoom();
				break;
			case TilePicker::State::obstacles:
				if (_inRoom)
					AddObstacle(_entityType);
				else
					NewRoom();
				break;
			case TilePicker::State::props:
				//if (_inRoom)
				//	AddUnit();
				//else
				//	NewRoom();
				break;
		}
	}
	else if (_tilePicker.active)
	{
		TilePicker::SelectorItem item = _tilePicker.GetSelectorItem();;
		switch (_tilePicker.state)
		{
			case TilePicker::State::shipTiles:
				_texRect = _tilePicker.GetTileRect();
				_curSelectedTexture.setTexture(_data->assetManager.GetTexture("Tiles"));
				_hoveredTile.setScale(2.0f, 2.0f);
				SetMouseGridLock(true);
				break;
			case TilePicker::State::units:
				_texRect = item.rect.getTextureRect();
				_curSelectedTexture.setTexture(*item.texture);
				_hoveredTile.setScale(1.0f, 1.0f);
				_entityType = item.type;
				SetMouseGridLock(false);
				break;
			case TilePicker::State::obstacles:
				_texRect = item.rect.getTextureRect();
				_curSelectedTexture.setTexture(*item.texture);
				_entityType = item.type;

				switch (_entityType)
				{
					case static_cast<int>(Obstacle::Type::box) :
						SetMouseGridLock(false);
						_hoveredTile.setScale(1.0f, 1.0f);
						break;
					case static_cast<int>(Obstacle::Type::spike) :
						SetMouseGridLock(true);
						_hoveredTile.setScale(2.0f, 2.0f);
						break;
				}

				break;
		}



		_curSelectedTexture.setTextureRect(_texRect);
		_hoveredTile.setTexture(_curSelectedTexture.getTexture());
		_hoveredTile.setTextureRect(_texRect);

	}
}

void LevelBuilder::NewRoom()
{
	sf::Vector2f mousePositionInView = _data->window.mapPixelToCoords(static_cast<sf::Vector2i>(sf::Mouse::getPosition(_data->window)));

	sf::Vector2f newRoomPos = sf::Vector2f(
		mousePositionInView.x - (std::fmodf(mousePositionInView.x, SCREEN_WIDTH)),
		mousePositionInView.y - (std::fmodf(mousePositionInView.y, SCREEN_HEIGHT)));

	if (mousePositionInView.x < 0)
		newRoomPos.x -= SCREEN_WIDTH;
	if (mousePositionInView.y < 0)
		newRoomPos.y -= SCREEN_HEIGHT;

	_levelRef->rooms.push_back(Room(_data, _worldRef, newRoomPos));
	_levelRef->rooms[_levelRef->rooms.size() - 1].BuildLevel();

	_playerRef->SetView();
}

/// <summary>
/// Adds a tile at the mouse location.
/// </summary>
void LevelBuilder::AddTile()
{
	sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(_data->window));
	sf::Vector2f mousePositionInView = _data->window.mapPixelToCoords(static_cast<sf::Vector2i>(mousePos));

	for (int i = 0; i < _levelRef->rooms.size(); i++)
	{
		if (_levelRef->rooms[i].roomShape.getGlobalBounds().contains(mousePositionInView))
		{
			sf::Vector2i tilePos = sf::Vector2i(mousePositionInView - _levelRef->rooms[i].roomOffset) / 64;
			_levelRef->rooms[i].AddTile(tilePos.x, tilePos.y, _texRect.left % _data->assetManager.GetTexture("Tiles").getSize().x, _texRect.top);
		}
	}


}


/// <summary>
/// Removes the tile at the current mouse location.
/// </summary>
void LevelBuilder::RemoveTile()
{
	sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(_data->window));
	sf::Vector2f mousePositionInView = _data->window.mapPixelToCoords(static_cast<sf::Vector2i>(mousePos));

	for (int i = 0; i < _levelRef->rooms.size(); i++)
	{
		if (_levelRef->rooms[i].roomShape.getGlobalBounds().contains(mousePositionInView))
		{
			sf::Vector2i tilePos = sf::Vector2i(mousePositionInView - _levelRef->rooms[i].roomOffset) / 64;
			_levelRef->rooms[i].RemoveTile(tilePos.x, tilePos.y);
		}
	}
}

/// <summary>
/// Replaces the tile at the current mouse position.
/// </summary>
void LevelBuilder::ReplaceTile()
{
	RemoveTile();
	AddTile();
}

/// <summary>
/// Saves the currently built level to the disk. Each tile is saved as it's UV coordinates on the tilesheet.
/// </summary>
void LevelBuilder::SaveLevel()
{
	// The filename to save the level to.
	std::string lName;
	std::cout << "Level Name: ";
	std::cin >> lName;
	std::cout << std::endl;

	// Handles any potential overrite issues.
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


	// Save the data.
	if (output.is_open())
	{
		for (int i = 0; i < _levelRef->rooms.size(); i++)
		{
			// Get the current room.
			std::vector<std::vector<sf::Vector2i>> map = _levelRef->rooms[i].GetMap();

			sf::Vector2f roomOffset = _levelRef->rooms[i].roomOffset;

			output << "Offset: " << std::to_string(roomOffset.x) << "/" << std::to_string(roomOffset.y) << "\n";

			// For every tile coord in the map...
			for (int y = 0; y < map.size(); y++)
			{
				for (int x = 0; x < map[0].size(); x++)
				{
					// ...Get the data from the tile in the map at (x, y)...
					std::string numX = std::to_string(map[y][x].x);
					std::string numY = std::to_string(map[y][x].y);

					if (numX.size() == 1)
						numX = "0" + numX;
					if (numY.size() == 1)
						numY = "0" + numY;

					//Put the data in the txt file.

					output << numX << "/" << numY;

					if (x != map[0].size() - 1)
						output << ", ";
				}

				//When we finish a row of tiles, go to the next row.
				output << "\n";
			}

			for (int a = 0; a < _levelRef->rooms[i].agents.size(); a++)
			{
				Agent* agent = _levelRef->rooms[i].agents.at(a);
				std::string agentType = std::to_string(static_cast<int>(agent->type));
				std::string xPos = std::to_string(agent->sprite.getPosition().x);
				std::string yPos = std::to_string(agent->sprite.getPosition().y);
				std::string flipped = std::to_string(static_cast<int>(agent->isFlipped));

				output << "AGENT: " << agentType << ", (" << xPos << "/" << yPos << "), " << flipped << "\n";

				delete agent;
			}

			for (int a = 0; a < _levelRef->rooms[i].obstacles.size(); a++)
			{
				Obstacle* obs = _levelRef->rooms[i].obstacles.at(a);
				std::string obsType = std::to_string(static_cast<int>(obs->type));
				std::string xPos = std::to_string(obs->sprite.getPosition().x);
				std::string yPos = std::to_string(obs->sprite.getPosition().y);

				output << "OBSTACLE: " << obsType << ", (" << xPos << "/" << yPos << "), " << "\n";

				delete obs;
			}

			output << "\n" << "-------END OF ROOM-------" << "\n";
		}
	}
}

/// <summary>
/// Loads a level in from a text file.
/// </summary>
void LevelBuilder::LoadLevel()
{
	std::string lName;

	// Ask (in console) for the level to loads name.
	std::cout << "Level to load Name: ";
	std::cin >> lName;
	std::cout << std::endl;


	// If there's a level with that name....
	if (CheckForLevel(lName))
	{
		// build a copy of the current map.
		std::vector<std::vector<sf::Vector2i>> map = _levelRef->rooms[0].GetMap();

		std::string filePath = LEVEL_PATH + lName;
		std::ifstream input(filePath + ".txt");

		std::string line;

		sf::Vector2f roomOffset = sf::Vector2f();

		std::vector<Agent*> levelAgents;
		std::vector<Obstacle*> levelObstacles;


		_levelRef->ClearUnitPhysics();
		_levelRef->ClearLevel();

		//Set the tiles in the map copy to the correct coordinates. 
		if (input.is_open())
		{
			int y = 0;

			while (getline(input, line))
			{
				if (line.substr(0, 6) == "Offset")
				{
					std::string num = line.substr(8, line.length() - 8);

					size_t separator = num.find('/');

					roomOffset.x = stof(num.substr(0, separator));
					roomOffset.y = stof(num.substr(separator + 1));;

				}
				else if (line == "-------END OF ROOM-------")
				{
					Room r = Room(Room(_data, _worldRef, roomOffset));
					r.SetMap(map);
					r.agents = levelAgents;
					r.obstacles = levelObstacles;
					_levelRef->rooms.push_back(r);
					y = 0;

					levelAgents.clear();
					levelObstacles.clear();
				}
				else if (line.substr(0, 5) == "AGENT")
				{
					Agent::Type type;
					sf::Vector2f pos;
					bool flipped = false;

					size_t sep1 = line.find(':') + 2;
					size_t sep2 = line.find('(') + 1;


					type = static_cast<Agent::Type>(std::stoi(line.substr(sep1, 1)));

					sep1 = line.find('/');

					pos.x = static_cast<float>(std::stof(line.substr(sep2, sep1 - sep2)));

					sep2 = line.find(')');


					pos.y = static_cast<float>(std::stof(line.substr(sep1 + 1, sep2 - sep1)));

					sep2 += 2;

					std::string flippedString = line.substr(sep2 + 1);

					flipped = static_cast<bool>(std::stoi(flippedString));

					switch (type)
					{
						case Agent::Type::alarmPig:
							AlarmPig* newAgent = new AlarmPig(_data, _worldRef, pos);
							
							if (flipped)
								newAgent->FlipSprite();

							levelAgents.push_back(newAgent);
							break;
					}
				}
				else if (line.substr(0, 8) == "OBSTACLE")
				{
					Obstacle::Type type;
					sf::Vector2f pos;

					size_t sep1 = line.find(':') + 2;
					size_t sep2 = line.find('(') + 1;


					type = static_cast<Obstacle::Type>(std::stoi(line.substr(sep1, 1)));

					sep1 = line.find('/');

					pos.x = static_cast<float>(std::stof(line.substr(sep2, sep1 - sep2)));

					sep2 = line.find(')');


					pos.y = static_cast<float>(std::stof(line.substr(sep1 + 1, sep2 - sep1)));
					pos.y -= 52.0f;

					sep2 += 2;

					std::string flippedString = line.substr(sep2 + 1);

					switch (type)
					{
					case Obstacle::Type::spike:
						Spike* newSpike = new Spike(_data, _worldRef, pos);

						levelObstacles.push_back(newSpike);
						break;
					}
				}
				else
				{
					for (int i = 0; i < line.size(); i += 7)
					{
						std::string temp = line.substr(i, 2);
						int xTile = std::stoi(line.substr(i, 2));
						int yTile = std::stoi(line.substr(i + 3, 2));

						map[y][i / 7] = sf::Vector2i(xTile, yTile);
					}
					y++;

				}
			}

			for (int i = 0; i < _levelRef->rooms.size(); i++)
				_levelRef->rooms[i].BuildLevel();

		}

		_playerRef->SetView();
	}
	else
	{
		std::cout << "LOAD ABORTED. Could not find level with Name: " << lName <<std::endl;
	}
}

/// <summary>
/// Load Level from a sting.
/// </summary>
void LevelBuilder::LoadLevel(std::string name)
{
	std::string lName = name;

	// If there's a level with that name....
	if (CheckForLevel(lName))
	{
		// build a copy of the current map.
		std::vector<std::vector<sf::Vector2i>> map = _levelRef->emptyRoom;

		std::string filePath = LEVEL_PATH + lName;
		std::ifstream input(filePath + ".txt");

		std::string line;

		sf::Vector2f roomOffset = sf::Vector2f();

		std::vector<Agent*> levelAgents;
		std::vector<Obstacle*> levelObstacles;



		_levelRef->ClearUnitPhysics();
		_levelRef->ClearLevel();

		//Set the tiles in the map copy to the correct coordinates. 
		if (input.is_open())
		{

			int y = 0;

			while (getline(input, line))
			{
				if (line.substr(0, 6) == "Offset")
				{
					std::string num = line.substr(8, line.length() - 8);

					size_t separator = num.find('/');

					roomOffset.x = stof(num.substr(0, separator));
					roomOffset.y = stof(num.substr(separator + 1));;

				}
				else if (line == "-------END OF ROOM-------")
				{
					Room r = Room(Room(_data, _worldRef, roomOffset));
					r.SetMap(map);
					r.agents = levelAgents;
					r.obstacles = levelObstacles;
					_levelRef->rooms.push_back(r);
					y = 0;

					levelAgents.clear();
					levelObstacles.clear();
				}
				else if (line.substr(0, 5) == "AGENT")
				{
					Agent::Type type;
					sf::Vector2f pos;
					bool flipped = false;

					size_t sep1 = line.find(':') + 2;
					size_t sep2 = line.find('(') + 1;


					type = static_cast<Agent::Type>(std::stoi(line.substr(sep1, 1)));

					sep1 = line.find('/');

					pos.x = static_cast<float>(std::stof(line.substr(sep2, sep1 - sep2)));

					sep2 = line.find(')');


					pos.y = static_cast<float>(std::stof(line.substr(sep1 + 1, sep2 - sep1)));

					sep2 += 2;

					std::string flippedString = line.substr(sep2 + 1);

					flipped = static_cast<bool>(std::stoi(flippedString));

					switch (type)
					{
					case Agent::Type::alarmPig:
						AlarmPig* newAgent = new AlarmPig(_data, _worldRef, pos);

						if (flipped)
							newAgent->FlipSprite();

						levelAgents.push_back(newAgent);
						break;
					}
				}
				else if (line.substr(0, 8) == "OBSTACLE")
				{
					Obstacle::Type type;
					sf::Vector2f pos;

					size_t sep1 = line.find(':') + 2;
					size_t sep2 = line.find('(') + 1;


					type = static_cast<Obstacle::Type>(std::stoi(line.substr(sep1, 1)));

					sep1 = line.find('/');

					pos.x = static_cast<float>(std::stof(line.substr(sep2, sep1 - sep2)));

					sep2 = line.find(')');


					pos.y = static_cast<float>(std::stof(line.substr(sep1 + 1, sep2 - sep1)));
					pos.y -= 52.0f;

					sep2 += 2;

					std::string flippedString = line.substr(sep2 + 1);

					switch (type)
					{
						case Obstacle::Type::spike:
							Spike* newSpike = new Spike(_data, _worldRef, pos);

							levelObstacles.push_back(newSpike);
							break;
					}
				}
				else
				{
					for (int i = 0; i < line.size(); i += 7)
					{
						std::string temp = line.substr(i, 2);
						int xTile = std::stoi(line.substr(i, 2));
						int yTile = std::stoi(line.substr(i + 3, 2));

						map[y][i / 7] = sf::Vector2i(xTile, yTile);
					}
					y++;

				}
			}

			for (int i = 0; i < _levelRef->rooms.size(); i++)
				_levelRef->rooms[i].BuildLevel();

		}
		_playerRef->SetView();
		_levelRef->rooms[0].agents.push_back(new Baldy(_data, _worldRef, sf::Vector2f(100, 500), &_levelRef->rooms[0]));
	}
	else
	{
		std::cout << "LOAD ABORTED. Could not find level with Name: " << lName << std::endl;
	}
}

/// <summary>
/// Returns true if a level with the supplied name is found in the levelData folder.
/// </summary>
/// <param name="levelName"> The name of the level to search for. </param>
/// <returns> True if a level file is found, false if not. </returns>
bool LevelBuilder::CheckForLevel(std::string levelName)
{
	std::string filePath = LEVEL_PATH + levelName;
	std::ifstream input;
	input.open(filePath + ".txt");
	if (input.is_open())
		return true;

	return false;
}

void LevelBuilder::TestMouseHover()
{
	sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(_data->window));
	sf::Vector2f mousePositionInView = _data->window.mapPixelToCoords(static_cast<sf::Vector2i>(mousePos));
	_inRoom = false;

	for (int i = 0; i < _levelRef->rooms.size(); i++)
	{
		if (_levelRef->rooms[i].roomShape.getGlobalBounds().contains(mousePositionInView))
		{
			for (int j = 0; j < _levelRef->rooms[i].tiles.size(); j++)
			{
				if (_levelRef->rooms[i].tiles[j].sprite.getGlobalBounds().contains(mousePositionInView))
				{

					if (!_mouseLocked)
						_hoveredTile.setPosition(mousePositionInView);
					else
						_hoveredTile.setPosition(_levelRef->rooms[i].tiles[j].sprite.getPosition());
				}
			}
			_inRoom = true;
		}
	}

	if (!_inRoom)
	{
		sf::Vector2f newRoomPos = sf::Vector2f(
			mousePositionInView.x - (std::fmodf(mousePositionInView.x, SCREEN_WIDTH)), 
			mousePositionInView.y - (std::fmodf(mousePositionInView.y, SCREEN_HEIGHT)));

		if (mousePositionInView.x < 0)
			newRoomPos.x -= SCREEN_WIDTH;
		if (mousePositionInView.y < 0)
			newRoomPos.y -= SCREEN_HEIGHT;

		_newRoomSelector.setPosition(newRoomPos);
		_newRoomSelector.setOutlineThickness(5.0f);

		_curSelectedTexture.setScale(0.0f, 0.0f);
		_curTextureOutline.setScale(0.0f, 0.0f);
		_hoveredTile.setScale(0.0f, 0.0f);
	}
	else
	{
		_newRoomSelector.setOutlineThickness(0.0f);
		_curSelectedTexture.setScale(1.0f, 1.0f);
		_curTextureOutline.setScale(1.0f, 1.0f);
	}

	_curTextureOutline.setPosition(_data->window.mapPixelToCoords(static_cast<sf::Vector2i>(sf::Vector2f(mousePos.x, mousePos.y - 34.0f))));
	_curSelectedTexture.setPosition(_data->window.mapPixelToCoords(static_cast<sf::Vector2i>(sf::Vector2f(mousePos.x, mousePos.y - 33.0f))));
}

void LevelBuilder::OpenSelector()
{
	_tilePicker.Activate();
}

void LevelBuilder::AddUnit(int type)
{
	Room* r = &_levelRef->rooms[0];
	for (int i = 0; i < _levelRef->rooms.size(); i++)
	{
		if (_levelRef->rooms[i].roomShape.getGlobalBounds().contains(_data->window.mapPixelToCoords(static_cast<sf::Vector2i>(sf::Mouse::getPosition(_data->window)))))
			r = &_levelRef->rooms[i];
	}

	r->agents.push_back(new AlarmPig(_data, _worldRef, sf::Vector2f(_data->window.mapPixelToCoords(static_cast<sf::Vector2i>(sf::Mouse::getPosition(_data->window))))));
}

void LevelBuilder::AddObstacle(int type)
{
	Room* r = &_levelRef->rooms[0];
	sf::Vector2f mousePosInView = _data->window.mapPixelToCoords(static_cast<sf::Vector2i>(sf::Mouse::getPosition(_data->window)));
	for (int i = 0; i < _levelRef->rooms.size(); i++)
	{
		if (_levelRef->rooms[i].roomShape.getGlobalBounds().contains(mousePosInView))
			r = &_levelRef->rooms[i];
	}
	sf::Vector2f objectPos = _hoveredTile.getPosition();

	switch (type)
	{
		case static_cast<int>(Obstacle::Type::spike) :
			objectPos.y -= 32.0f;
			r->obstacles.push_back(new Spike(_data, _worldRef, objectPos));
			break;
		case static_cast<int>(Obstacle::Type::box) :
			r->obstacles.push_back(new Box(_data, _worldRef, objectPos));
			break;
	}
}

void LevelBuilder::SetMouseGridLock(bool isLock)
{
	_mouseLocked = isLock;
}