#include "Room.h"

/// <summary>
/// Basic constructor. Builds a room at the base coordinates.
/// </summary>
Room::Room(ZEngine::GameDataRef data, b2World* worldRef) :
	_data(data),
	_worldRef(worldRef)
{
	BuildLevel();
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
	BuildLevel();
	roomShape.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	roomShape.setPosition(sf::Vector2f(tiles[0].sprite.getPosition().x - 32.0f, tiles[0].sprite.getPosition().y - 32.0f));
	roomShape.setFillColor(sf::Color::Transparent);
	roomShape.setOutlineColor(sf::Color::Blue);
	roomShape.setOutlineThickness(5.0f);


	obstacles.push_back(new Spike(_data, _worldRef, sf::Vector2f(640, 640 - 128)));

	BuildPhyics();
}

Room::~Room()
{

}

void Room::Update(float dT)
{
	for (int i = 0; i < agents.size(); i++)
		agents.at(i)->Update(dT);

	for (int i = 0; i < obstacles.size(); i++)
		obstacles.at(i)->Update(dT);

	RemoveDeadEntities();
}

void Room::Draw()
{
	for (int i = 0; i < tiles.size(); i++)
		tiles.at(i).Draw();

	for (int i = 0; i < agents.size(); i++)
		agents.at(i)->Draw();

	for (int i = 0; i < obstacles.size(); i++)
		obstacles.at(i)->Draw();

}

/// <summary>
/// Cleares all the loaded tiles before creating a new set of tiles for the room.
/// </summary>
void Room::BuildLevel()
{
	for (int i = 0; i < tiles.size(); i++)
	{
		tiles[i].RemovePhysics();
	}

	tiles.clear();

	for (int y = 0; y < _map.size(); y++)
	{
		for (int x = 0; x < _map[y].size(); x++)
		{
			tiles.push_back(GenTiles(_map[y][x], x, y));
		}
	}
}

/// <summary>
/// Creates a tile with the correct UV coordinates at the correct place in the game world.
/// </summary>
/// <param name="uv"> The texture coordintates in the tilesheet. </param>
/// <param name="x"> The x position of the tile in the room. </param>
/// <param name="y"> The y position of the tile in the room. </param>
/// <returns></returns>
Tile Room::GenTiles(sf::Vector2i uv, int x, int y)
{
	bool collision = true;

	if (uv.y * 32 >= 160 || (uv.x * 32 == 32 && uv.y * 32 == 32))
		collision = false;

	//Builds a tile at the correct location.
	Tile tile = Tile(_data, _worldRef, "Tiles", TILE_PATH, collision, //Assigns basic tile data.
		sf::Vector2f(roomOffset.x + (x * 64) + 32, roomOffset.y + (y * 64) + 32), //Sets the position of the tile, including the offset for the whole room.
		sf::IntRect(uv.x * 32, uv.y * 32, 32, 32)); //Sets the UV coords in the sprite sheet.

	return tile;
}

/// <summary>
/// Removes the tile at the grid location (x, y)
/// </summary>
/// <param name="x"> The x location on the level grid (NOTE: NOT SCREEN SPACE) </param>
/// <param name="y"> The y location on the level grid (NOTE: NOT SCREEN SPACE) </param>
void Room::RemoveTile(int x, int y)
{
	sf::Vector2f newPos = sf::Vector2f((x * 64) + 32, (y * 64) + 32);
	x = x % 15;
	y = y % 10;

	tiles.at(x + (15 * y)).RemovePhysics();
	tiles.at(x + (15 * y)) = Tile(_data, _worldRef, "Tiles", TILE_PATH, false, newPos, sf::IntRect(352, 256, 32, 32));
	_map[y][x] = sf::Vector2i(352/32, 256/32);
}


/// <summary>
/// Adds a tile with specific UV coords at a location.
/// </summary>
/// <param name="x"> The x location on the level grid (NOTE: NOT SCREEN SPACE) </param>
/// <param name="y"> The y location on the level grid (NOTE: NOT SCREEN SPACE) </param>
/// <param name="xUV"> The x UV coords of the texture we are drawing. </param>
/// <param name="yUV"> The y UV coords of the texture we are drawing. </param>
void Room::AddTile(int x, int y, int xUV, int yUV)
{
	bool collision = true;

	sf::Vector2f newPos = sf::Vector2f((x * 64) + 32, (y * 64) + 32);
	x = x % 15;
	y = y % 10;

	if (yUV >= 160 || (xUV == 32 && yUV == 32))
		collision = false;

	tiles.at(x + (15 * y)) = Tile(_data, _worldRef, "Tiles", TILE_PATH, collision, newPos + roomOffset, sf::IntRect(xUV, yUV, 32, 32));
	_map[y][x] = sf::Vector2i(xUV / 32, yUV / 32);
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
			agents.erase(agents.begin() + i);
	}
}