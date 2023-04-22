#include "InputManager.h"

#include "GameState_Gameplay.h"
#include "Player.h"


InputManager::InputManager(Player* InPlayer, GameState_Gameplay* InGameplayState)
	:
	m_Player(InPlayer),
	m_GameplayState(InGameplayState)
{
}


InputManager::~InputManager()
{
}


bool InputManager::IsSpriteClicked(sf::Sprite object, sf::RenderWindow& InWIndow)
{
	sf::IntRect rect(object.getPosition().x - object.getGlobalBounds().width / 2, object.getPosition().y - object.getGlobalBounds().height / 2, object.getGlobalBounds().width, object.getGlobalBounds().height);

	if (rect.contains(sf::Mouse::getPosition(InWIndow)) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		return true;
	}

	return false;
}

bool InputManager::IsSpriteReleased(sf::Sprite object, sf::RenderWindow& InWIndow)
{
	sf::IntRect rect(object.getPosition().x - object.getGlobalBounds().width / 2, object.getPosition().y - object.getGlobalBounds().height / 2, object.getGlobalBounds().width, object.getGlobalBounds().height);

	if (rect.contains(sf::Mouse::getPosition(InWIndow)) && !sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		return true;
	}

	return false;
}


sf::Vector2i InputManager::GetMousePosition(sf::RenderWindow& InWIndow)
{
	return sf::Mouse::getPosition(InWIndow);
}

void InputManager::HandleInputEvents(sf::RenderWindow& InWIndow)
{
	InWIndow.setKeyRepeatEnabled(false);
	std::vector<sf::Event>* GameInputEvents = new std::vector<sf::Event>();
	//std::vector<sf::Event>* PlayerInputEvents;
	sf::Event event;

	PollInputAxis();

	while (InWIndow.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			switch(event.key.code)
			{
			default:
				std::cout << "KeyPressed: " << event.key.code << std::endl;
				GameInputEvents->push_back(event);
				break;
			}
		break;
		case sf::Event::KeyReleased:
			switch (event.key.code)
			{
			default:
				GameInputEvents->push_back(event);
				break;
			}
			break;
		case sf::Event::MouseButtonPressed:
			switch (event.key.code)
			{
			default:
				std::cout << "MouseButtonPressed: " << event.key.code << std::endl;
				GameInputEvents->push_back(event);
				break;
			}
			break;
		case sf::Event::MouseButtonReleased:
			switch (event.key.code)
			{
			default:
				std::cout << "MouseButtonReleased: " << event.key.code << std::endl;
				GameInputEvents->push_back(event);
				break;
			}
			break;
		default:
			//GameInputEvents->push_back(event);
			break;
		}

	}
	InWIndow.setKeyRepeatEnabled(true);

	HandleGamestateInputs(GameInputEvents);
	HandlePlayerInputs(GameInputEvents);

	SetInputAxis(m_InputAxis);
}

void InputManager::HandleGamestateInputs(std::vector<sf::Event>* InEventQueue)
{
	for (int eventIndex = 0; eventIndex < InEventQueue->size(); eventIndex++)
	{
		sf::Event Event = InEventQueue->at(eventIndex);
		switch (Event.type)
		{
		case sf::Event::KeyPressed:
			switch (Event.key.code)
			{
			case sf::Keyboard::Escape:
				m_GameplayState->Exit();

				InEventQueue->erase(InEventQueue->begin() + eventIndex);
				break;
			case sf::Keyboard::P:

				if (m_GameplayState->IsPaused())
					m_GameplayState->Resume();
				else
					m_GameplayState->Pause();

				InEventQueue->erase(InEventQueue->begin() + eventIndex);
				break;
			case sf::Keyboard::O:
				m_GameplayState->ToggleDebugMode();

				InEventQueue->erase(InEventQueue->begin() + eventIndex);
				break;
			default:
				break;
			}
			break;
		case sf::Event::Closed:
			m_GameplayState->Exit();
			
			InEventQueue->erase(InEventQueue->begin() + eventIndex);
			break;
		default:
			break;
		}
	}
}

void InputManager::HandlePlayerInputs(std::vector<sf::Event>* InEventQueue)
{
	for (int eventIndex = 0; eventIndex < InEventQueue->size(); eventIndex++)
	{
		sf::Event Event = InEventQueue->at(eventIndex);

		m_Player->HandleInput(&Event);
		InEventQueue->erase(InEventQueue->begin() + eventIndex);
	}


	//for (int eventIndex = 0; eventIndex < InEventQueue->size(); eventIndex++)
	//{
	//	sf::Event* event = InEventQueue->at(eventIndex);
	//	switch (event->type)
	//	{
	//	case sf::Event::KeyPressed:
	//		switch (event->key.code)
	//		{
	//		case sf::Keyboard::Space:
	//			m_Player->Jump();
	//			InEventQueue->erase(InEventQueue->begin() + eventIndex);
	//			break;
	//		case sf::Keyboard::F:
	//			m_Player->Interact();
	//			InEventQueue->erase(InEventQueue->begin() + eventIndex);
	//			break;

	//		// Begin WSAD Pressed
	//		case sf::Keyboard::W:
	//			m_InputAxis.y += 1;
	//			InEventQueue->erase(InEventQueue->begin() + eventIndex);
	//			break;
	//		case sf::Keyboard::S:
	//			m_InputAxis.y += -1;
	//			InEventQueue->erase(InEventQueue->begin() + eventIndex);
	//			break;
	//		case sf::Keyboard::D:
	//			m_InputAxis.x += 1;
	//			InEventQueue->erase(InEventQueue->begin() + eventIndex);
	//			break;
	//		case sf::Keyboard::A:
	//			m_InputAxis.x += -1;
	//			InEventQueue->erase(InEventQueue->begin() + eventIndex);
	//			break;
	//		// End WSAD Pressed
	//		}
	//		break;
	//	case sf::Event::KeyReleased:
	//		switch (event->key.code)
	//		{
	//		// Begin WSAD Released
	//		case sf::Keyboard::W:
	//			m_InputAxis.y -= 1;
	//			InEventQueue->erase(InEventQueue->begin() + eventIndex);
	//			break;
	//		case sf::Keyboard::S:
	//			m_InputAxis.y -= -1;
	//			InEventQueue->erase(InEventQueue->begin() + eventIndex);
	//			break;
	//		case sf::Keyboard::D:
	//			m_InputAxis.x -= 1;
	//			InEventQueue->erase(InEventQueue->begin() + eventIndex);
	//			break;
	//		case sf::Keyboard::A:
	//			m_InputAxis.x -= -1;
	//			InEventQueue->erase(InEventQueue->begin() + eventIndex);
	//			break;
	//		// End WSAD Released
	//		}
	//		break;
	//	}
	//}
}

void InputManager::PollInputAxis()
{
	m_InputAxis = sf::Vector2f(0.0f, 0.0f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_InputAxis.x -= 1.0f;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_InputAxis.x += 1.0f;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		m_InputAxis.y += 1.0f;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_InputAxis.y -= 1.0f;
	}
	SetInputAxis(m_InputAxis);
}
