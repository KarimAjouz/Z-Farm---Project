#pragma once

#include "Game.h"
#include "Timer.h"

/// <summary>
/// A framework-level class that handles a single animation loop.
/// </summary>

namespace ZEngine
{
	class Animation
	{
	public:
		Animation(float animLength, bool loop, ZEngine::GameDataRef data, std::string name, std::string path, sf::IntRect frameRect, sf::Sprite* spriteRef, sf::Vector2f origin);
		~Animation();

		void Update(float dT);

		void Play();
		void Pause();
		void Resume();
		void Restart();
		void Stop();
		void End();

		sf::Vector2f _origin;

		bool Complete;
		std::string Name;
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
