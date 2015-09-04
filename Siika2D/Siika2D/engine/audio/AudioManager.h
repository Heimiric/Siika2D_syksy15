#pragma once

#include "Audio.h"

namespace audio
{
	/**
		Audio objects are created in AudioManager.
		Keeps track of created audio objects.
	*/
	class AudioManager
	{
	public:
		/**
			Constructor.
			Takes a reference to ResourceMananager as a parameter.
		*/
		AudioManager(core::ResourceManager* resourceManager);
		~AudioManager();

		/**
			Creates new audio object from .ogg file or returns an existing one.
			Audio is loaded with ResourceManager.
		*/
		Audio* createAudio(std::string filename);
	private:
		core::ResourceManager* _resourceManager;
		std::map<std::string, Audio*> _createdAudio;

	};
}