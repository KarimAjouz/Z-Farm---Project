#include "Level.h"
#include "AlarmPig.h"


Level::Level(ZEngine::GameDataRef data, b2World* worldRef) :
	_data(data),
	_worldRef(worldRef)
{

}

Level::~Level()
{

}

void Level::Init(ZEngine::GameDataRef data, b2World* worldRef)
{
	//_data = data;
	//_worldRef = worldRef;
	//rooms.push_back(Room(data, worldRef, sf::Vector2f(0.0f, 0.0f)));

	//for (int i = 0; i < rooms.size(); i++)
	//{
	//	rooms[i].BuildLevel();
	//}


	//activeRoom = &rooms[0];
}

void Level::Update(float dT)
{
	for (int i = 0; i < rooms.size(); i++)
	{
		rooms[i].Update(dT);
	}
}

void Level::Draw()
{
	for (int i = 0; i < rooms.size(); i++)
		rooms[i].DrawTiles();

	for (int i = 0; i < rooms.size(); i++)
		rooms[i].DrawObstacles();

	for (int i = 0; i < rooms.size(); i++)
		rooms[i].DrawAgents();

	for (int i = 0; i < rooms.size(); i++)
		rooms[i].Draw();
}

void Level::ClearUnitPhysics()
{
	for (int i = 0; i < rooms.size(); i++)
	{
		for (int j = 0; j < rooms[i].agents.size(); j++)
		{
			_worldRef->DestroyBody(rooms[i].agents.at(j)->body);
		}
	}
}

void Level::SpikeAgents()
{
	for (int a = 0; a < activeRoom->agents.size(); a++)
	{
		for (int p = 0; p < activeRoom->obstacles.size(); p++)
		{
			if (activeRoom->obstacles.at(p)->type == Obstacle::Type::spike)
			{
				if (activeRoom->agents.at(a)->hitbox.getGlobalBounds().intersects(activeRoom->obstacles.at(p)->hitbox.getGlobalBounds()))
					activeRoom->agents.at(a)->Hit(activeRoom->obstacles.at(p)->sprite.getPosition());
			}
		}
	}
}

void Level::ClearLevel()
{
	for (int i = 0; i < rooms.size(); i++)
		rooms.pop_back();

	rooms.clear();
}

void Level::RegenLevel()
{
	for (int i = 0; i < rooms.size(); i++)
		rooms[i].BuildLevel();
}