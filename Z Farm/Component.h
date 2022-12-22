#pragma once

namespace ZEngine
{
	class Component
	{
	public:
		Component();
		~Component();

		virtual void Init();

		virtual void Update(float dT);
	};
}

