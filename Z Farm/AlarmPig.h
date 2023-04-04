//#pragma once
//
//#include "Enemy.h"
//#include "AnimationComponent.h"
//
//
//class AlarmPig : public Enemy
//{
//public:
//	AlarmPig(ZEngine::GameDataRef data, b2World* worldRef, sf::Vector2f pos);
//	~AlarmPig();
//
//	void Update(float dT);
//	void Draw();
//
//	void Hit();
//	void Hit(sf::Vector2f playerPos);
//private:
//	ZEngine::GameDataRef _data;
//
//	enum class State
//	{
//		idle,
//		hit,
//		alarmed
//	};
//
//	State _state;
//
//	void UpdateAnimations();
//	void UpdateState();
//
//
//	ZEngine::AnimationComponent _animSys;
//	void DestroyPig();
//
//	void InitAnimations();
//	void InitPhysics(sf::Vector2f pos);
//
//};
//
