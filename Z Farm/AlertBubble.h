//#pragma once
//
//#include <SFML/Graphics.hpp>
//#include "AnimationComponent.h"
//
//
//class AlertBubble
//{
//public:
//	AlertBubble(ZEngine::GameDataRef data);
//	~AlertBubble();
//
//	void Update(float dT, sf::Vector2f pos);
//	void Draw();
//
//	bool UpdateState(bool seePlayer, ZEngine::Timer* questionTimer);
//
//	void QuestionIn();
//	void AlertIn();
//	void QuestionOut();
//	void AlertOut();
//
//	sf::Sprite sprite;
//	AnimationComponent animSys;
//
//	enum class AlertState
//	{
//		passive,
//		question,
//		alerted,
//		alert
//	};
//
//	AlertState alertState = AlertState::passive;
//
//private:
//	ZEngine::GameDataRef _data;
//
//
//
//
//	void InitAnimations();
//};
//
