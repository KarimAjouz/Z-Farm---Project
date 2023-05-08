#include "ObjectComponent.h"
#include <SFML/Graphics.hpp>

namespace ZEngine
{
	ObjectComponent::ObjectComponent(GameDataRef InData)
		:
		m_Data(InData)
	{
		Init();
	}

	ObjectComponent::~ObjectComponent()
	{
	}

	void ObjectComponent::Init()
	{
	}

	void ObjectComponent::Update(float dT)
	{
	}

	void ObjectComponent::Draw(sf::RenderWindow* InWindow)
	{
		//InWindow->draw(m_Sprite);
	}
}