#include "Animation.h"

namespace ZEngine
{
	Animation::Animation(float animLength, bool loop, ZEngine::GameDataRef data, std::string name, std::string path, sf::IntRect frameRect, sf::Sprite* spriteRef, sf::Vector2f origin) :
		_segmentTimer(animLength, true),
		_looping(loop),
		_data(data),
		_spritePtr(spriteRef),
		_index(0),
		_numFrames(0),
		_interval(0),
		_playing(false),
		_frameRect(frameRect),
		complete(false),
		animName(name),
		_origin(origin)
	{
		_data->assetManager.LoadTexture(name, path);
		_spritePtr->setTexture(_data->assetManager.GetTexture(name));
		_spritePtr->setTextureRect(frameRect);

		_numFrames = _data->assetManager.GetTexture(name).getSize().x / frameRect.width;
		_interval = animLength / _numFrames;

		_segmentTimer.SetTimer(_interval);
	}

	Animation::~Animation()
	{

	}

	void Animation::Update(float dT)
	{
		if (_segmentTimer.Complete())
		{
			if (_index == _numFrames - 1 && _looping)
				Restart();
			else if (_index == _numFrames - 1 && !_looping)
				End();
			else
				NextFrame();
		}
	}

	void Animation::Play()
	{
		_spritePtr->setTexture(_data->assetManager.GetTexture(animName));
		_spritePtr->setTextureRect(_frameRect);

		_spritePtr->setOrigin(_origin);

		_playing = true;
		complete = false;



		Restart();
	}

	void Animation::Restart()
	{
		_index = 0;
		_playing = true;

		SetFrame();
		_segmentTimer.Start();
	}

	void Animation::Pause()
	{
		_playing = false;
		_segmentTimer.Pause();
	}

	void Animation::Resume()
	{
		_playing = true;
		_segmentTimer.Resume();
	}

	void Animation::Stop()
	{
		_playing = false;
		_index = 0;
		_segmentTimer.Pause();
	}

	void Animation::NextFrame()
	{
		_index++;
		sf::IntRect temp;
		SetFrame();
		_segmentTimer.Start();
	}

	void Animation::SetFrame()
	{
		sf::IntRect temp;
		temp = _frameRect;
		temp.left = _index * _frameRect.width;
		_spritePtr->setTextureRect(temp);
	}

	void Animation::End()
	{
		Stop();
		complete = true;
	}
}