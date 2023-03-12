#include "Level.h"
#include "AlarmPig.h"
#include "Box.h"

#include <tmxlite/ObjectGroup.hpp>
#include <SFML/System/Time.hpp>


Level::Level(ZEngine::GameDataRef data, b2World* worldRef) :
	_data(data),
	_worldRef(worldRef)
{
	Init(_data, _worldRef);
}

Level::~Level()
{
	for (int i = 0; i < _physicsBodies.size(); i++)
	{
		_physicsBodies.pop_back();
	}

	for (int i = 0; i < _obstacles.size(); i++)
	{
		_obstacles.pop_back();
	}
}

void Level::Init(ZEngine::GameDataRef data, b2World* worldRef)
{
	_data = data;
	_worldRef = worldRef;

	tmx::Map loadedMap;

	loadedMap.load("Content/LevelData/TiledMaps/Template.tmx");

	BuildLevelFromTMX(loadedMap);
	
}

void Level::Update(float dT)
{
	sf::Time time = sf::seconds(dT);
	for (int i = 0; i < _mapLayers.size(); i++)
	{
		_mapLayers[i]->update(time);
	}

	for (int i = 0; i < _obstacles.size(); i++)
	{
		_obstacles[i]->Update(dT);
	}
}

void Level::Draw()
{ 
	for (int i = 0; i < _mapLayers.size(); i++)
	{
		_data->GameWindow.draw(*_mapLayers[i]);
	}

	for (int i = 0; i < _obstacles.size(); i++)
	{
		_obstacles[i]->Draw();
	}
}

void Level::ClearUnitPhysics()
{
}

void Level::ClearLevel()
{
	for (int i = 0; i < _tiles.size(); i++)
	{
		delete _tiles[i];
		_tiles.pop_back();
	}
	for (int i = 0; i < _physicsBodies.size(); i++)
	{
		_physicsBodies.pop_back();
	}
}

void Level::BuildLevelFromTMX(const tmx::Map& InLoadedMap)
{
	const auto& layers = InLoadedMap.getLayers();
	int tileLayerNumber = 0;
	for (const auto& layer : layers)
	{
		_mapLayers.push_back(new MapLayer(InLoadedMap, tileLayerNumber));
		tileLayerNumber++;

		if (layer->getType() == tmx::Layer::Type::Object)
		{
			const auto& objectLayer = layer->getLayerAs<tmx::ObjectGroup>();
			if (objectLayer.getName() == std::string("CollisionLayer"))
			{
				BuildPhysicsFromCollisionLayer(objectLayer);
			}
			else if (objectLayer.getName() == std::string("ObjectLayer"))
			{
				BuildObjectsFromObjectLayer(objectLayer);
			}
		}
	}
}

void Level::BuildPhysicsFromCollisionLayer(tmx::ObjectGroup inObjectLayer)
{
	const auto& objects = inObjectLayer.getObjects();
	for (const auto& object : objects)
	{
		b2BodyDef worldCollisionDef;
		worldCollisionDef.position = b2Vec2((object.getPosition().x + (object.getAABB().width / 2)) / SCALE, (object.getPosition().y + (object.getAABB().height / 2)) / SCALE);
		worldCollisionDef.type = b2_kinematicBody;
		b2Body* collisionBody = _worldRef->CreateBody(&worldCollisionDef);
		collisionBody->GetUserData().pointer = static_cast<int>(CollisionTag::tile);

		b2PolygonShape polygonShape;
		polygonShape.SetAsBox((object.getAABB().width / 2) / SCALE, (object.getAABB().height / 2) / SCALE, b2Vec2(0.0f, 0.0f), 0.0f);
		CollisionTag collisionTag = CollisionTag::level;

		b2FixtureDef myFixtureDef;
		myFixtureDef.density = 1.0f;
		myFixtureDef.friction = 1.0f;
		myFixtureDef.restitution = 0.1f;
		myFixtureDef.shape = &polygonShape;
		b2Fixture* fixture = collisionBody->CreateFixture(&myFixtureDef);
		fixture->GetUserData().pointer = static_cast<int>(collisionTag);
	}
}

void Level::BuildObjectsFromObjectLayer(tmx::ObjectGroup inObjectLayer)
{
	const auto& objects = inObjectLayer.getObjects();
	for (const auto& object : objects)
	{
		for (tmx::Property objProperty : object.getProperties())
		{
			std::string propName = objProperty.getName();

			if (propName == "ObjectID")
			{
				int ObjID = objProperty.getIntValue();
				Box* box = nullptr;
				sf::Vector2f boxPos = sf::Vector2f();

				switch (ObjID)
				{
				case 0:
					std::cout << "Spawning a box: " << std::endl;

					boxPos.x = object.getPosition().x + (object.getAABB().width / 2);
					boxPos.y = object.getPosition().y + (object.getAABB().height / 2);
					box = new Box(_data, _worldRef, boxPos);

					_obstacles.push_back(box);

					break;
				default:
					std::cout << "Warning: Level::BuildObjectsFromObjectLayer --> ObjID: " << std::to_string(ObjID) << " is an INVALID ObjID" << std::endl;
					break;
				}
			}
		}
	}
}

void Level::RegenLevel()
{
}