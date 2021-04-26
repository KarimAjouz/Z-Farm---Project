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
	_levelBuilder(_data, &_world, _level, &_player),
	_testSword(_data, &_world, &_player),
	_level(new Level(_data, &_world))
{
	ZEngine::Utilities::SeedRandom();

	

	CreateGround(_world, 0, SCREEN_HEIGHT - 10);
	_world.SetContactListener(&_contactListener);
	_debugDraw.SetFlags(b2Draw::e_shapeBit);
	_world.SetDebugDraw(&_debugDraw);

	sf::View view;
	view.setSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	view.setCenter(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	
	_data->window.setView(view);
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
			case sf::Keyboard::O:
				_debugMode = !_debugMode;
				break;
			case sf::Keyboard::L:
				_building = !_building;

				if (_building == false)
				{
					_level->RegenLevel();
					_player.SetView();
				}
				break;
			case sf::Keyboard::M:
				if (_building)
					_levelBuilder.SaveLevel();
				break;
			case sf::Keyboard::N:
				if (_building)
					_levelBuilder.LoadLevel();
				break;
			case sf::Keyboard::Up:
				if (_building)
				{
					sf::View tempView = _data->window.getView();
					tempView.setCenter(sf::Vector2f(tempView.getCenter().x, tempView.getCenter().y - 10.0f));
					_data->window.setView(tempView);
				}
				break;
			case sf::Keyboard::Down:
				if (_building)
				{
					sf::View tempView = _data->window.getView();
					tempView.setCenter(sf::Vector2f(tempView.getCenter().x, tempView.getCenter().y + 10.0f));
					_data->window.setView(tempView);
				}
				break;
			case sf::Keyboard::Left:
				if (_building)
				{
					sf::View tempView = _data->window.getView();
					tempView.setCenter(sf::Vector2f(tempView.getCenter().x - 10.0f, tempView.getCenter().y));
					_data->window.setView(tempView);
				}
				break;
			case sf::Keyboard::Right:
				if (_building)
				{
					sf::View tempView = _data->window.getView();
					tempView.setCenter(sf::Vector2f(tempView.getCenter().x + 10.0f, tempView.getCenter().y));
					_data->window.setView(tempView);
				}
				break;
			}
			break;
		case sf::Event::MouseButtonReleased:
			if (_building && e.mouseButton.button == sf::Mouse::Button::Left)
				_levelBuilder.MouseRelease();
			if (_building && e.mouseButton.button == sf::Mouse::Button::Right)
				_levelBuilder.OpenSelector();

			if (!_building && e.mouseButton.button == sf::Mouse::Button::Left)
				_player.Stab();
			break;
		case sf::Event::MouseWheelScrolled:
			if (e.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
				_levelBuilder.Scroll(e.mouseWheelScroll.delta);

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
		if(_building)
			_levelBuilder.Update(dT);
		else
		{
			_level->Update(dT);
			_player.Update(dT);
			LerpView(dT);

			_testSword.Update(dT);

			_world.Step(dT, 8, 3);

		}

	}
}

/// <summary>
/// Draws all of the Gameplay entities.
/// </summary>
/// <param name="dT"></param>
void GameState_Gameplay::Draw()
{
	_data->window.clear();

	_level->Draw();
	_player.Draw();
	_testSword.Draw();


	if(_debugMode)
		_world.DebugDraw();


	if (_building)
		_levelBuilder.Draw();

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
	delete _level;
	_data->window.close();
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
	sf::View view = _data->window.getView();
	sf::Vector2f newCenter = view.getCenter();
	newCenter = ZEngine::Utilities::Lerp(newCenter, _viewTarget, dT);
	view.setCenter(newCenter);
	_data->window.setView(view);
}
