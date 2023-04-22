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
		m_Data(InData),
		m_Sprite(sf::Sprite()),
		m_WorldRef(nullptr)
	{
	}

	GameObject::GameObject(GameDataRef InData, sf::Vector2f InPosition, b2World* InWorldRef)
		:
		_Components(std::vector<ObjectComponent*>()),
		m_Data(InData),
		m_Sprite(sf::Sprite()),
		m_WorldRef(InWorldRef)
	{
		m_Sprite.setPosition(InPosition);
	}

	GameObject::GameObject(sf::Vector2f InPosition, GameDataRef InData, std::string TextureName, std::string SpritePath)
		:
		_Components(std::vector<ObjectComponent*>()),
		m_Data(InData),
		m_Sprite(sf::Sprite())
	{
		m_Sprite.setPosition(InPosition);
		m_Data->assetManager.LoadTexture(TextureName, SpritePath);

		m_Sprite.setTexture(m_Data->assetManager.GetTexture(TextureName));

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


	void GameObject::Draw()
	{
		//for (ObjectComponent* Component : _Components)
		//{
		//	Component->Draw();
		//}
		m_Data->GameWindow.draw(m_Sprite);
	}

	void GameObject::Hit()
	{

	}
}
