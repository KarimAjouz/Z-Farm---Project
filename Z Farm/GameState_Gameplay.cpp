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
	_player(sf::Vector2f(400.0f, 300.0f), data, &balanceSheet, &_world, &_viewTarget, _level),
	_paused(false),
	_gravity(0.0f, 9.8f),
	_world(_gravity),
	_contactListener(&_player, _level),
	_debugDraw(data),
	_testSword(_data, &_world, &_player),
	_level(new Level(_data, &_world))
{
	ZEngine::Utilities::SeedRandom();

	

	CreateGround(_world, 0, SCREEN_HEIGHT - 10);
	_world.SetContactListener(&_contactListener);
	_debugDraw.SetFlags(b2Draw::e_shapeBit | b2Draw::e_jointBit);
	_world.SetDebugDraw(&_debugDraw);

	sf::View view;
	view.setSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	view.setCenter(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	
	_data->GameWindow.setView(view);
}


GameState_Gameplay::~GameState_Gameplay()
{
	delete _level;
}

void GameState_Gameplay::Init()
{
}

/// <summary>
/// Handles Input Events.
/// </summary>
void GameState_Gameplay::PollEvents()
{
	
	HandleKeyboardInputs();

}


/// <summary>
/// Updates all of the Gameplay entities.
/// </summary>
/// <param name="dT"></param>
void GameState_Gameplay::Update(float dT)
{
	if (!_paused)
	{
		_level->Update(dT);
		_player.Update(dT);
		LerpView(dT);

		_testSword.Update(dT);

		physicsAccumulator += dT;
		while (physicsAccumulator >= 1.0f / 60.0f)
		{
			_world.Step(1.0f / 60.0f, 8, 3);
			physicsAccumulator -= 1.0f / 60.0f;
		}

	}
}

/// <summary>
/// Draws all of the Gameplay entities.
/// </summary>
/// <param name="dT"></param>
void GameState_Gameplay::Draw()
{
	_data->GameWindow.clear();

	_level->Draw();
	_player.Draw();
	_testSword.Draw();


	if(_debugMode)
		_world.DebugDraw();

	_data->GameWindow.display();
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
	delete _level;
	_data->GameWindow.close();
}


void GameState_Gameplay::CreateGround(b2World& world, float x, float y)
{
	b2BodyDef BodyDef;
	BodyDef.position = b2Vec2(x / SCALE, y / SCALE);
	BodyDef.type = b2_staticBody;
	b2Body* Body = world.CreateBody(&BodyDef);

	b2PolygonShape Shape;
	Shape.SetAsBox((0 / 2) / SCALE, (0 / 2) / SCALE); // Creates a box shape. Divide your desired width and height by 2.
	b2FixtureDef FixtureDef;
	FixtureDef.density = 0.f;  // Sets the density of the body
	FixtureDef.shape = &Shape; // Sets the shape
	b2Fixture* fixture = Body->CreateFixture(&FixtureDef); // Apply the fixture definition
	fixture->GetUserData().pointer = static_cast<int>(CollisionTag::level); //Tag the ground as 1
	
}

void GameState_Gameplay::LerpView(float dT)
{
	sf::View view = _data->GameWindow.getView();
	sf::Vector2f newCenter = view.getCenter();

	float viewDist = ZEngine::Utilities::GetVectorMagnitudeSquared(_viewTarget - newCenter);
	if (viewDist < 100.0f && viewDist != 0.0f)
	{
		newCenter = _viewTarget;
		view.setCenter(newCenter);
		_data->GameWindow.setView(view);
		return;
	}

	newCenter = ZEngine::Utilities::Lerp(newCenter, _viewTarget, dT);
	view.setCenter(newCenter);
	_data->GameWindow.setView(view);
}

void GameState_Gameplay::HandleKeyboardInputs()
{
	std::vector<sf::Event> GameplayInputEvents;

	sf::Event event;

	while (_data->GameWindow.pollEvent(event))
	{

		switch (event.type)
		{
		case sf::Event::KeyPressed:
			switch (event.key.code)
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
			case sf::Keyboard::O:
				_debugMode = !_debugMode;
				break;
			default:
				GameplayInputEvents.push_back(event);
				break;
			}
			break;
		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Button::Left)
				_player.Stab();
			else
				GameplayInputEvents.push_back(event);
			break;
		case sf::Event::Closed:
			Exit();
			break;
		default:
			GameplayInputEvents.push_back(event);
			break;
		}
	}
	_player.SetInputsForPolling(GameplayInputEvents);
}
