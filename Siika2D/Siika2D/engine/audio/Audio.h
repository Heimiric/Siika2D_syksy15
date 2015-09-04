#pragma once

#include "AudioInitializer.h"
#include "AudioPlayer.h"
#include <string>
#include <vector>

namespace audio
{
	/**
		This is a class for playing audio. 
	*/
	class Audio
	{
	public:
		
		Audio(std::string fileName, core::ResourceManager* resourceManager);
		Audio(){};
		~Audio();

		/**
			Starts a player.
			Returns false if there are no available audio players.
			Use this to play created sound.
		*/
		bool play();
		/**
			Stops all the instances of this Audio object.
			Next time playing will start from the beginning.
		*/
		void stop();
		/**
			Pauses all the players of this Audio object.
			Next time playing will continue from the same point.
		*/
		void pause();
		
		/**
			Sets the volume to given value.
			Give volumeLevel as percentage.
		*/
		void setVolume(float volumeLevel);
		/**
			Sets looping to given value.
			'isEnabled = true' enables looping. Audio loops after calling Play().
			'isEnabled = false' disables looping.
		*/
		void setLooping(bool isEnabled);

		/**
			MaxPlayerCount default = 3
			MaxPlayerCount defines how many instances of this Audio object
			can be played at once. 
		*/
		void setMaxPlayerCount(unsigned newMaxCount);
		
	private:

		AudioPlayer* getAvailable();

		std::vector<AudioPlayer*> _player;

		unsigned _playerCount;
		unsigned _maxPlayerCount;
	};
}