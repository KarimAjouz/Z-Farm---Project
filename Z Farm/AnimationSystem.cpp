#include "AnimationSystem.h"

namespace ZEngine
{

	AnimationSystem::AnimationSystem(sf::Sprite* spritePtr, GameDataRef data) :
		_spritePtr(spritePtr),
		_data(data)
	{
	}

	AnimationSystem::~AnimationSystem()
	{
	}

	void AnimationSystem::Update(float dT)
	{
		_curAnim->Update(dT);
	}

	void AnimationSystem::AddAnimation(std::string name, std::string path, float animLength, bool loop, sf::IntRect frameRect, sf::Vector2f origin)
	{
		_anims.push_back(new Animation(animLength, loop, _data, name, path, frameRect, _spritePtr, origin));
	}

	void AnimationSystem::SetAnimation(std::string name)
	{
		for (int i = 0; i < _anims.size(); i++)
		{
			if (_anims.at(i)->Name == name)
			{
				_curAnim = _anims.at(i);
			}
		}
	}

	void AnimationSystem::Play()
	{
		_curAnim->Play();
	}

}