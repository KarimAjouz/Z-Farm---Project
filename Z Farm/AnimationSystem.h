#pragma once

#include "Animation.h"
namespace ZEngine
{
	class AnimationSystem
	{
	public:
		AnimationSystem(sf::Sprite* spritePtr, GameDataRef data);
		~AnimationSystem();
		
		void Update(float dT);

		void AddAnimation(std::string name, std::string path, float animLength, bool loop,  sf::IntRect frameRect, sf::Vector2f origin); //Adds an animation to the system.
		void SetAnimation(std::string name); //Sets the current animation.
		void Play();

		std::string GetCurrentAnim() { return _curAnim->Name; }
	private:
		std::vector<Animation*> _anims;
		Animation* _curAnim;

		ZEngine::GameDataRef _data;
		sf::Sprite* _spritePtr;
	};
}

