#pragma once

#include "Game.h"

#include "tmxlite/Map.hpp"

#include "box2d.h"

#include "SFMLOrthogonalLayer.hpp"

class Level
{
public:
	Level(ZEngine::GameDataRef data, b2World* worldRef);
	~Level();


	void Init(ZEngine::GameDataRef _data, b2World* worldRef);
	void Update(float dT);
	void Draw();

	void ClearUnitPhysics();
	void ClearLevel();

	const tmx::Map& LoadLevelFromTMX(std::string InFilePath);

	//void SpikeAgents();


	void RegenLevel();


	//std::vector<Obstacle*> GetObstacles() { return _obstacles; }



private:

	ZEngine::GameDataRef _data;
	b2World* _worldRef;

	//std::vector<Tile*> _tiles;
	std::vector<b2Body*> _physicsBodies;

	//std::vector<Obstacle*> _obstacles;

	std::vector<MapLayer*> _mapLayers;
	std::vector<tmx::Object> _objects;

	void BuildLevelFromTMX(const tmx::Map& InLoadedMap);

	void BuildPhysicsFromCollisionLayer(tmx::ObjectGroup inObjectLayer);
	void BuildObjectsFromObjectLayer(tmx::ObjectGroup inObjectLayer);
};

