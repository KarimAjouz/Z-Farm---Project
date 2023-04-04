#include "GameState_Gameplay.h"
#include "Definitions.h"
#include "BalanceSheet.h"
#include "Utilities.h"
#include "PhysicsComponent.h"
#include "PlayerState.h"

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
	_level(new Level(_data, &_world)),
	_debugText()
{
	ZEngine::Utilities::SeedRandom();

	_player.SetInputManagerState(this);
	

	CreateGround(_world, 0, SCREEN_HEIGHT - 10);
	_world.SetContactListener(&_contactListener);
	_debugDraw.SetFlags(b2Draw::e_shapeBit | b2Draw::e_jointBit);
	_world.SetDebugDraw(&_debugDraw);

	sf::View view;
	view.setSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	view.setCenter(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	
	_data->GameWindow.setView(view);
	_data->assetManager.LoadFont("DebugFont", DEBUG_FONT_PATH);
	_debugText.setFont(_data->assetManager.GetFont("DebugFont"));
	_debugText.setFillColor(sf::Color::Magenta);
	_debugText.setOutlineColor(sf::Color::Black);
	_debugText.setOutlineThickness(2.0f);
	_debugText.setPosition(0.0f, 0.0f);
	_debugText.setCharacterSize(16.0f);

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

	_runningDelta = dT;
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



	int fps = 1.0f / _runningDelta;

	_debugText.setString(
		"FPS: " + std::to_string(fps) + "\n" + 
		"PlayerState: " + _player.GetTraversalState()->GetStateName() + "\n" +
		"Input X: " + std::to_string(_player.GetInputAxis().x)
		);

	_data->GameWindow.draw(_debugText);
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
	BodyDef.position = b2Vec2(x / 30, y / 30);
	BodyDef.type = b2_staticBody;
	b2Body* Body = world.CreateBody(&BodyDef);

	b2PolygonShape Shape;
	Shape.SetAsBox((0 / 2) / 30, (0 / 2) / 30); // Creates a box shape. Divide your desired width and height by 2.
	b2FixtureDef FixtureDef;
	FixtureDef.density = 0.f;  // Sets the density of the body
	FixtureDef.shape = &Shape; // Sets the shape
	b2Fixture* fixture = Body->CreateFixture(&FixtureDef); // Apply the fixture definition
	fixture->GetUserData().pointer = static_cast<int>(ECollisionTag::level); //Tag the ground as 1
	
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
}/*

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
}*/
