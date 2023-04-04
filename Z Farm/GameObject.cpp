#include "GameObject.h"

#include "ObjectComponent.h"

namespace ZEngine
{
	GameObject::GameObject()
	{

	}

	GameObject::GameObject(GameDataRef InData)
		:
		_Components(std::vector<ObjectComponent*>()),
		m_data(InData),
		m_Sprite(sf::Sprite())
	{
	}

	GameObject::GameObject(sf::Vector2f InPosition, GameDataRef InData)
		:
		_Components(std::vector<ObjectComponent*>()),
		m_data(InData),
		m_Sprite(sf::Sprite())
	{
		m_Sprite.setPosition(InPosition);
	}

	GameObject::GameObject(sf::Vector2f InPosition, GameDataRef InData, std::string TextureName, std::string SpritePath)
		:
		_Components(std::vector<ObjectComponent*>()),
		m_data(InData),
		m_Sprite(sf::Sprite())
	{
		m_Sprite.setPosition(InPosition);
		m_data->assetManager.LoadTexture(TextureName, SpritePath);

		m_Sprite.setTexture(m_data->assetManager.GetTexture(TextureName));

	}

	GameObject::~GameObject()
	{
		for (ObjectComponent* Component : _Components)
		{
			Component->~ObjectComponent();
		}
	}
	void GameObject::Update(float dT)
	{
		for (ObjectComponent* Component : _Components)
		{
			Component->Update(dT);
		}
	}


	void GameObject::Draw(sf::RenderWindow* InWindow)
	{
		InWindow->draw(m_Sprite);
		for (ObjectComponent* Component : _Components)
		{
			Component->Draw(InWindow);
		}
	}
}
