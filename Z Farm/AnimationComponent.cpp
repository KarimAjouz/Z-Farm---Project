#include "AnimationComponent.h"

namespace ZEngine
{
	AnimationComponent::AnimationComponent(sf::Sprite* InSprite, GameDataRef InData) :
		ObjectComponent(InData),
		m_Sprite(InSprite)
	{

	}

	AnimationComponent::~AnimationComponent()
	{
	}

	void AnimationComponent::Update(float dT)
	{
		if(_curAnim != nullptr)
			_curAnim->Update(dT);
	}

	void AnimationComponent::AddAnimation(std::string name, std::string path, float animLength, bool loop)
	{
		_anims.push_back(new Animation(animLength, loop, m_Data, name, path, m_FrameRect, m_Sprite, m_FrameOrigin));
	}

	void AnimationComponent::SetAnimation(std::string name)
	{
		for (int i = 0; i < _anims.size(); i++)
		{
			if (_anims.at(i)->Name == name)
			{
				_curAnim = _anims.at(i);
			}
		}
	}

	void AnimationComponent::Play()
	{
		_curAnim->Play();
	}

	std::string AnimationComponent::GetCurrentAnim()
	{
		if (_curAnim == nullptr)
			return "NONE";

		return _curAnim->Name;
	}

}