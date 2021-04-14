#pragma once
#include "Pickup.h"
class SwordPickup : Pickup 
{
public:
	SwordPickup(ZEngine::GameDataRef data, b2World* _worldRef, Player* _playerRef);
	~SwordPickup();

	void Update(float dT);
	void Draw();


private:

	bool _collected = false;

	ZEngine::GameDataRef _data;
	b2World* _worldRef;
	Player* _playerRef;

	float _t = 0.0f;

	float _spinOffset = 0.0f;
	float _hoverOffset = 0.0f;

	float _spinMultiplier = 1.0f;
	float _hoverMultiplier = 1.0f;
	float _hoverAmount = 0.5f;

	void Hover(float dT);
	void InitPhysics();
	void TestCollision();
};

