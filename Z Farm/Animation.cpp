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
		Complete(false),
		Name(name),
		_origin(origin)
	{
		//Loads in and sets the texture and the correct frame of animation.
		_data->assetManager.LoadTexture(name, path);
		_spritePtr->setTexture(_data->assetManager.GetTexture(name));
		_spritePtr->setTextureRect(frameRect);

		//Calculate the number of frames and set the time interval.
		_numFrames = _data->assetManager.GetTexture(name).getSize().x / frameRect.width;
		_interval = animLength / _numFrames;
		_segmentTimer.SetTimer(_interval);
	}

	Animation::~Animation()
	{

	}

	void Animation::Update(float dT)
	{
		//If this animation segment is complete...
		if (_segmentTimer.Complete())
		{
			//Check if we are at the final frame and need to loop or not. Otherwise, jump to the next frame.
			if (_index == _numFrames - 1 && _looping)
				Restart();
			else if (_index == _numFrames - 1 && !_looping)
				End();
			else
				NextFrame();
		}
	}

	/// <summary>
	/// Plays this animation.
	/// </summary>
	void Animation::Play()
	{
		_spritePtr->setTexture(_data->assetManager.GetTexture(Name));
		_spritePtr->setTextureRect(_frameRect);

		_spritePtr->setOrigin(_origin);

		_playing = true;
		Complete = false;

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

	//Jumps to the next frame of the animation.
	void Animation::NextFrame()
	{
		_index++;
		sf::IntRect temp;
		SetFrame();
		_segmentTimer.Start();
	}

	//Sets the current frame to the correct frame of animation.
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
		Complete = true;
	}
}