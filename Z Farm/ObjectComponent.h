#pragma once
#include "Game.h"
#include "Component.h"

namespace ZEngine
{
	class ObjectComponent
	{
	public:
		ObjectComponent(GameDataRef InData);

		virtual ~ObjectComponent();

		virtual void Init();

		virtual void Update(float dT);

		virtual void Draw(sf::RenderWindow* InWindow);

	protected:

		GameDataRef m_Data;
	};
}
