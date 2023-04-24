#include "Game.h"

#include "GameState_Splash.h"

namespace ZEngine
{

	Game::Game(int width, int height, std::string title)
	{
		_data->GameWindow.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Titlebar);

		_data->stateMachine.AddState(StateRef(new GameState_Splash(this->_data)), true);

		this->Run();
	}


	Game::~Game()
	{
	}

	void Game::Run()
	{
		float newTime, frameTime;

		float currentTime = this->_clock.getElapsedTime().asSeconds();

		float accumulator = 0.0f;

		while (this->_data->GameWindow.isOpen())
		{
			this->_data->stateMachine.ProcessStateChanges();

			newTime = this->_clock.getElapsedTime().asSeconds();

			frameTime = newTime - currentTime;

			if (frameTime > 0.25f)
			{
				frameTime = 0.25f;
			}

			currentTime = newTime;
			accumulator += frameTime;

			while (accumulator >= this->m_TargetDeltaTime)
			{
				frameTime = fmin(accumulator, this->m_TargetDeltaTime);
				this->_data->stateMachine.GetActiveState()->PollEvents();

				this->_data->stateMachine.GetActiveState()->Update(m_TargetDeltaTime);

				accumulator -= frameTime;
			}

			//interp = accumulator / this->m_TargetDeltaTime;
			this->_data->stateMachine.GetActiveState()->Draw();
		}
	}

}