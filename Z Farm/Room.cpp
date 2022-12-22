#include "Room.h"
#include "Box.h"
#include "Baldy.h"

/// <summary>
/// Basic constructor. Builds a room at the base coordinates.
/// </summary>
Room::Room(ZEngine::GameDataRef data, b2World* worldRef) :
	_data(data),
	_worldRef(worldRef)
{
	_map = GenEmptyMap();
	BuildLevel();
	showNav = false;
}

/// <summary>
/// Constructor, builds a room at the correct offset to the world.
/// </summary>
/// <param name="roomMap"> A 2D vector of intVec2s that designates the map of the room. </param>
/// <param name="roomOffset"> A floatVec2 that designates the offset from 0, 0 that the room is at. </param>
Room::Room(ZEngine::GameDataRef data, b2World* worldRef, sf::Vector2f offset) :
	_data(data),
	_worldRef(worldRef),
	roomOffset(offset)
{
	_map = GenEmptyMap();
	BuildLevel();
	roomShape.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	roomShape.setPosition(sf::Vector2f(tiles[0].sprite.getPosition().x - 32.0f, tiles[0].sprite.getPosition().y - 32.0f));
	roomShape.setFillColor(sf::Color::Transparent);
	roomShape.setOutlineColor(sf::Color::Blue);
	roomShape.setOutlineThickness(5.0f);
	showNav = false;


	BuildPhyics();
}

Room::~Room()
{
	for (int i = 0; i < _navMap.GetMap().size(); i++)
	{
		for (int j = 0; j < _navMap.GetMap()[i].nodes.size(); j++)
		{
			delete _navMap.GetMap()[i].nodes.at(j);
		}
	}
}

void Room::Update(float dT)
{
	for (int i = 0; i < agents.size(); i++)
		agents.at(i)->Update(dT);

	for (int i = 0; i < obstacles.size(); i++)
		obstacles.at(i)->Update(dT);

	RemoveDeadEntities();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C))
		showNav = !showNav;
}

void Room::Draw()
{
	if (showNav)
	{
		for (int i = 0; i < _navMap.GetMap().size(); i++)
		{
			for (int j = 0; j < _navMap.GetMap()[i].nodes.size(); j++)
			{
				Node* node = _navMap.GetMap()[i].nodes.at(j);
				_data->window.draw(node->nodeArea);

				for (int k = 0; k < node->edges.size(); k++)
				{
					if (node->edges[k].type == Node::Edge::Type::walk || node->edges[k].type == Node::Edge::Type::drop)
					{
						sf::ConvexShape line;

						line.setPointCount(4);

						line.setPoint(0, node->nodeArea.getPosition());
						line.setPoint(1, node->edges[k].destinationCoords);
						line.setPoint(2, node->edges[k].destinationCoords);
						line.setPoint(3, node->nodeArea.getPosition());

						line.setOutlineThickness(2.0f);

						line.setOutlineColor(sf::Color::Black);
						_data->window.draw(line);
					}
					else if (node->edges[k].type == Node::Edge::Type::jump)
					{
						sf::CircleShape circle;
						for (int posIndex = 0; posIndex < node->edges[k].JumpTrajectory.pointsArray.size(); posIndex++)
						{
							circle.setPosition(node->edges[k].JumpTrajectory.pointsArray[posIndex]);

							if (posIndex == 0)
							{
								circle.setRadius(8.0f);
								circle.setFillColor(sf::Color::Green);
							}
							else if (posIndex == node->edges[k].JumpTrajectory.pointsArray.size() - 1)
							{
								circle.setRadius(2.0f);
								circle.setFillColor(sf::Color::Cyan);
							}
							else
							{
								circle.setRadius(2.0f);
								circle.setFillColor(sf::Color::Red);
							}
							circle.setOrigin(circle.getRadius(), circle.getRadius());
							_data->window.draw(circle);
						}
					}

				}
			}
		}
	}
}

/// <summary>
/// Cleares all the loaded tiles before creating a new set of tiles for the room.
/// </summary>
void Room::BuildLevel()
{
	// Clear all of the tile physics.
	for (int i = 0; i < tiles.size(); i++)
	{
		tiles[i].RemovePhysics();
	}

	// Get rid of the tiles in the room.
	tiles.clear();

	//Generate a new set of tiles for the room.
	for (int y = 0; y < _map.size(); y++)
	{
		for (int x = 0; x < _map[y].size(); x++)
		{
			bool col = _map[y][x].collision;
			if (col)
				int meme = 0;
			tiles.push_back(GenTile(_map[y][x].tileSheetCoords, x, y, col));
		}
	}

	//Generate navNodes for the room.
	_navMap.GenerateNavMap(&tiles);
}

std::vector<std::vector<RoomTileData>> Room::GenEmptyMap()
{
	std::vector<std::vector<RoomTileData>> outMap;
	int rows = SCREEN_HEIGHT / TILE_SIZE;
	int collumns = SCREEN_WIDTH / TILE_SIZE;

	for (int row = 0; row < rows; row++)
	{
		std::vector<RoomTileData> mapRow;
		for (int collumn = 0; collumn < collumns; collumn++)
		{
			RoomTileData tileData = RoomTileData();
			mapRow.push_back(tileData);
		}
		outMap.push_back(mapRow);
	}
	return outMap;
}


void Room::DrawTiles()
{
	for (int i = 0; i < tiles.size(); i++)
		tiles.at(i).Draw();
}

void Room::DrawAgents()
{
	for (int i = 0; i < agents.size(); i++)
		agents.at(i)->Draw();
}

void Room::DrawObstacles()
{
	for (int i = 0; i < obstacles.size(); i++)
		obstacles.at(i)->Draw();
}

/// <summary>
/// Creates a tile with the correct UV coordinates at the correct place in the game world.
/// </summary>
/// <param name="uv"> The texture coordintates in the tilesheet. </param>
/// <param name="x"> The x position of the tile in the room. </param>
/// <param name="y"> The y position of the tile in the room. </param>
/// <returns></returns>
Tile Room::GenTile(sf::Vector2i uv, int x, int y, bool collision)
{
	//Builds a tile at the correct location.
	if (collision)
	{
		return Tile(_data, _worldRef, "colTiles", TILE_COL_PATH, collision, //Assigns basic tile data.
			sf::Vector2f(roomOffset.x + (x * TILE_SIZE) + TILE_SIZE / 2, roomOffset.y + (y * TILE_SIZE) + TILE_SIZE / 2), //Sets the position of the tile, including the offset for the whole room.
			sf::IntRect(uv.x * 32, uv.y * 32, 32, 32)); //Sets the UV coords in the sprite sheet.
	}
	else if (!collision)
	{
		return Tile(_data, _worldRef, "bgTiles", TILE_BG_PATH, collision, //Assigns basic tile data.
			sf::Vector2f(roomOffset.x + (x * TILE_SIZE) + TILE_SIZE / 2, roomOffset.y + (y * TILE_SIZE) + TILE_SIZE / 2), //Sets the position of the tile, including the offset for the whole room.
			sf::IntRect(uv.x * 32, uv.y * 32, 32, 32)); //Sets the UV coords in the sprite sheet.
	}
}

/// <summary>
/// Removes the tile at the grid location (x, y)
/// </summary>
/// <param name="x"> The x location on the level grid (NOTE: NOT SCREEN SPACE) </param>
/// <param name="y"> The y location on the level grid (NOTE: NOT SCREEN SPACE) </param>
void Room::RemoveTile(int x, int y)
{
	sf::Vector2f newPos = sf::Vector2f((x * TILE_SIZE) + TILE_SIZE / 2, (y * TILE_SIZE) + TILE_SIZE / 2);

	int collumns = (SCREEN_WIDTH / (TILE_SIZE * TILE_SCALE));
	int rows = (SCREEN_HEIGHT / (TILE_SIZE * TILE_SCALE));

	x = x % collumns;
	y = y % rows;

	tiles.at(x + (collumns * y)).RemovePhysics();
	tiles.at(x + (collumns * y)) = Tile(_data, _worldRef, "bgTiles", TILE_BG_PATH, false, newPos, sf::IntRect(352, 256, 32, 32));
	_map[y][x] = RoomTileData(sf::Vector2i(352/32, 256/32), false);
}


/// <summary>
/// Adds a tile with specific UV coords at a location.
/// </summary>
/// <param name="x"> The x location on the level grid (NOTE: NOT SCREEN SPACE) </param>
/// <param name="y"> The y location on the level grid (NOTE: NOT SCREEN SPACE) </param>
/// <param name="xUV"> The x UV coords of the texture we are drawing. </param>
/// <param name="yUV"> The y UV coords of the texture we are drawing. </param>
void Room::AddTile(int x, int y, int xUV, int yUV, bool col)
{
	sf::Vector2f newPos = sf::Vector2f((x * TILE_SIZE) + TILE_SIZE / 2, (y * TILE_SIZE) + TILE_SIZE / 2);

	int collumns = (SCREEN_WIDTH / (TILE_SIZE * TILE_SCALE));
	int rows = (SCREEN_HEIGHT / (TILE_SIZE * TILE_SCALE));

	x = x % collumns;
	y = y % rows;
	std::string filePath = col ? TILE_COL_PATH : TILE_BG_PATH;
	std::string tileType = col ? "colTiles" : "bgTiles";

	tiles.at(x + (collumns * y)) = Tile(_data, _worldRef, tileType, filePath, col, newPos + roomOffset, sf::IntRect(xUV, yUV, TILE_SIZE, TILE_SIZE));
	_map[y][x] = RoomTileData(sf::Vector2i(xUV / 32, yUV / 32), col);
}

void Room::BuildPhyics()
{
	b2BodyDef bodyDef;
	bodyDef.position = b2Vec2(roomOffset.x / SCALE, roomOffset.y / SCALE);
	bodyDef.type = b2_staticBody;
	b2Body* body = _worldRef->CreateBody(&bodyDef);
	body->SetFixedRotation(true);

	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(SCREEN_WIDTH / 2 / SCALE, SCREEN_HEIGHT / 2 / SCALE, b2Vec2(SCREEN_WIDTH / 2 / SCALE, SCREEN_HEIGHT / 2 / SCALE), 0);

	b2FixtureDef fixtureDef;
	fixtureDef.density = 1.0f;

	fixtureDef.shape = &polygonShape;
	fixtureDef.isSensor = true;

	b2Fixture* roomSensorFixture = body->CreateFixture(&fixtureDef);
	roomSensorFixture->GetUserData().pointer = static_cast<int>(CollisionTag::room);
}

void Room::RemoveDeadEntities()
{
	for (int i = 0; i < agents.size(); i++)
	{
		if (agents.at(i)->isMarked)
		{
			//_worldRef->DestroyBody(agents.at(i)->body);
			Agent* a = agents.at(i);
			delete a;
			agents.erase(agents.begin() + i);
		}
	}
}