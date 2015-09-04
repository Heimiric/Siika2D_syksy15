#include "AudioManager.h"

using namespace audio;

AudioManager::AudioManager(core::ResourceManager* resourceManager)
{
	_resourceManager = resourceManager;
}


AudioManager::~AudioManager()
{

}

Audio* AudioManager::createAudio(std::string filename)
{
	std::map<std::string, Audio*>::iterator it = _createdAudio.find(filename);
	if (it != _createdAudio.end())
		return it->second;
	else
	{
		Audio* audio = new Audio(filename, _resourceManager);

		_createdAudio.insert(std::make_pair(filename, audio));

		return _createdAudio.at(filename);
	}
}