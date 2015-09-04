#include "Audio.h"
#include "../core/ErrorHandler.h"
#include "../core/ResourceManager.h"

using namespace audio;

Audio::Audio(std::string fileName, core::ResourceManager* resourceManager) : _maxPlayerCount(3), _playerCount(1)
{
	core::AudioData* tempAudioAsset = resourceManager->loadAudio(fileName);
	s2d_assert( (tempAudioAsset != nullptr) );
	_player.push_back(new AudioPlayer(tempAudioAsset));
	AudioInitializer::getInstance()->initAudioPlayer(_player[0]);
}

Audio::~Audio()
{
	for (int i = 0; i < _playerCount; i++)
		delete _player[i];
}

bool Audio::play()
{
	AudioPlayer* tempPointer = getAvailable();
	
	if (tempPointer != nullptr)
	{
		tempPointer->setPlayState(SL_PLAYSTATE_PLAYING);
		return true;
	}
	else
		return false;
}

void Audio::stop()
{
	for (int i = 0; i < _playerCount; i++)
		_player[i]->setPlayState(SL_PLAYSTATE_STOPPED);
}

void Audio::pause()
{
	for (int i = 0; i < _playerCount; i++)
		_player[i]->setPlayState(SL_PLAYSTATE_PAUSED);
}

void Audio::setVolume(float volumeLevel)
{
	for (int i = 0; i < _playerCount; i++)
		_player[i]->setVolume(volumeLevel);
}

void Audio::setLooping(bool isEnabled)
{
	for (int i = 0; i < _playerCount; i++)
		_player[i]->setLooping(isEnabled);
}

void Audio::setMaxPlayerCount(unsigned newMaxCount)
{
	if (newMaxCount < _maxPlayerCount)
	{
		for (int i = 0; i < _playerCount; i++)
		{
			_player[i]->setPlayState(SL_PLAYSTATE_STOPPED);
		}

		s2d_info(("Removing AudioPlayers. Possible loss of data!"));

		for (int i = newMaxCount - 1; i < _playerCount; i++)
		{
			delete _player[i];
			_player.erase(_player.begin() + i);
			_playerCount--;
		}
	}

	_maxPlayerCount = newMaxCount;
}

AudioPlayer* Audio::getAvailable()
{
	for (int i = 0; i < _playerCount; i++)
	{
		SLuint32 temp = _player.at(i)->getPlayState();
		if ( temp == SL_PLAYSTATE_STOPPED )
			return _player[i];
	}

	if (_playerCount < _maxPlayerCount)
	{
		_playerCount++;
		_player.push_back(new AudioPlayer(_player[0]));
		AudioInitializer::getInstance()->initAudioPlayer(_player[_playerCount - 1]);

		return _player[_playerCount-1];
	}
	else
		return nullptr;
}