#pragma once

#include "Animation.h"

#include "ObjectComponent.h"

namespace ZEngine
{
	class AnimationComponent
		:
		public ObjectComponent
	{
	public:
		AnimationComponent(sf::Sprite* spritePtr, GameDataRef data);
		~AnimationComponent();
		
		virtual void Update(float dT) override;

		virtual void AddAnimation(std::string name, std::string path, float animLength, bool loop); //Adds an animation to the system.
		virtual void SetAnimation(std::string name); //Sets the current animation.
		virtual void Play();

		bool Complete() { return _curAnim->Complete; }

		std::string GetCurrentAnim();

		sf::IntRect m_FrameRect = sf::IntRect(0, 0, 64, 40);
		sf::Vector2f m_FrameOrigin = sf::Vector2f(32, 20);
	private:
		std::vector<Animation*> _anims;
		Animation* _curAnim = nullptr;

		sf::Sprite* m_Sprite;
	};
}

