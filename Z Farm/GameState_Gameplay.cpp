#include "GameState_Gameplay.h"
#include "Definitions.h"
#include "BalanceSheet.h"
#include "Utilities.h"


#include <cmath>

#include "GameState_Shop.h"

#include <iostream>


/// <summary>
/// Creates the Gameplay Gamestate.
/// </summary>
/// <param name="data"></param>
GameState_Gameplay::GameState_Gameplay(ZEngine::GameDataRef data) :
	_data(data),
	balanceSheet(BalanceSheet()),
	_saveManager(SaveDataManager()),
	_player(sf::Vector2f(400.0f, 300.0f), data, &balanceSheet, &_world),
	_paused(false),
	_gravity(0.0f, 9.8f),
	_world(_gravity)
{
	ZEngine::Utilities::SeedRandom();

	CreateGround(_world, 0, SCREEN_HEIGHT - 10);

}


GameState_Gameplay::~GameState_Gameplay()
{
}

void GameState_Gameplay::Init()
{
}

/// <summary>
/// Handles Input Events.
/// </summary>
void GameState_Gameplay::PollEvents()
{
	sf::Event e;
	while (_data->window.pollEvent(e))
	{
		switch (e.type)
		{
		case sf::Event::KeyPressed:
			switch (e.key.code)
			{
			case sf::Keyboard::Escape:
				Exit();
				break;
			case sf::Keyboard::P:
				if (_paused)
					Resume();
				else
					Pause();
				break;
			}
			break;
		case sf::Event::MouseButtonReleased:

			break;
		case sf::Event::Closed:
			Exit();
			break;
		}
	}
}


/// <summary>
/// Updates all of the Gameplay entities.
/// </summary>
/// <param name="dT"></param>
void GameState_Gameplay::Update(float dT)
{
	if (!_paused)
	{
		_player.Update(dT);

		_world.Step(dT, 8, 3);
	}
}

/// <summary>
/// Draws all of the Gameplay entities.
/// </summary>
/// <param name="dT"></param>
void GameState_Gameplay::Draw()
{
	_data->window.clear();

	_player.Draw();

	_data->window.display();
}

void GameState_Gameplay::Pause()
{
	_paused = true;
}

void GameState_Gameplay::Resume()
{
	_paused = false;
}

/// <summary>
/// Exits the game, clearing loaded memory.
/// </summary>
void GameState_Gameplay::Exit()
{
	_data->window.close();
}


void GameState_Gameplay::CreateGround(b2World& world, float x, float y)
{
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(x / SCALE, y / SCALE);
	BodyDef.type = b2_staticBody;
	b2Body* Body = world.CreateBody(&BodyDef);

	b2PolygonShape Shape;
	Shape.SetAsBox((1600.f / 2) / SCALE, (16.f / 2) / SCALE); // Creates a box shape. Divide your desired width and height by 2.
	b2FixtureDef FixtureDef;
	FixtureDef.density = 0.f;  // Sets the density of the body
	FixtureDef.shape = &Shape; // Sets the shape
	Body->CreateFixture(&FixtureDef); // Apply the fixture definition
}