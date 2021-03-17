#pragma once

#include "Game.h"
#include "Timer.h"

namespace ZEngine
{
	class Animation
	{
	public:
		Animation(float animLength, bool loop, ZEngine::GameDataRef data, std::string name, std::string path, sf::IntRect frameRect, sf::Sprite* spriteRef);
		~Animation();

		void Update(float dT);

		void Play();
		void Pause();
		void Resume();
		void Restart();
		void Stop();
		void End();

		bool complete;
		std::string animName;
	private:
		sf::Sprite* _spritePtr;
		Timer _segmentTimer;
		ZEngine::GameDataRef _data;

		sf::IntRect _frameRect;

		bool _playing;
		bool _looping;

		int _numFrames;
		int _index;
		float _interval;

		void NextFrame();

		void SetFrame();

	};

};
