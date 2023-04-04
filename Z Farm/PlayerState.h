#pragma once
#include "SFML/Graphics.hpp"


#include <vector>

class Player;

class PlayerState
{
public:
	virtual ~PlayerState() {}
	virtual PlayerState* HandleInput(Player& InPlayer, sf::Event* InputEvent);
	virtual void Update(float dT, Player& InPlayer);

	virtual void Enter(Player& InPlayer);
	virtual void Exit(Player& InPlayer);

	std::string GetStateName() { return m_StateName; }
protected:
	std::string m_StateName = "UNDEFINED";
};

