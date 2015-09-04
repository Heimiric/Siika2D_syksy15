#include "AudioPlayer.h"
#include "../core/ErrorHandler.h"

using namespace audio;

AudioPlayer::AudioPlayer(AudioPlayer* pointer)
{
	_audioAsset = pointer->_audioAsset;
}

AudioPlayer::~AudioPlayer()
{
	if (_audioPlayerObj != nullptr)
	{
		(*_audioPlayerObj)->Destroy(_audioPlayerObj);

		_audioPlayerObj = nullptr;
		_audioPlayerPlay = nullptr;
		_audioPlayerSeek = nullptr;
		_audioPlayerVol = nullptr;
	}
}

SLuint32 AudioPlayer::getPlayState()
{
	SLuint32 tempReturnValue;
	_result = (*_audioPlayerPlay)->GetPlayState(_audioPlayerPlay, &tempReturnValue);
	s2d_assert(_result == SL_RESULT_SUCCESS);

	return tempReturnValue;
}

void AudioPlayer::setPlayState(SLuint32 state)
{
	if(_audioPlayerPlay != nullptr)
	{
		_result = (*_audioPlayerPlay)->SetPlayState(_audioPlayerPlay, state);
		s2d_assert(_result == SL_RESULT_SUCCESS);
	}
}

void AudioPlayer::setLooping(bool isEnabled)
{
	_result = (*_audioPlayerSeek)->SetLoop(_audioPlayerSeek, isEnabled ? SL_BOOLEAN_TRUE : SL_BOOLEAN_FALSE, 0, SL_TIME_UNKNOWN);
	s2d_assert(_result == SL_RESULT_SUCCESS);
}

void AudioPlayer::setVolume(float volPercentage)
{
	SLmillibel tempVol;
	_result = (*_audioPlayerVol)->GetMaxVolumeLevel(_audioPlayerVol, &tempVol);

	tempVol *= 0.01 * volPercentage;

	_result = (*_audioPlayerVol)->SetVolumeLevel(_audioPlayerVol, tempVol);
	s2d_assert(_result == SL_RESULT_SUCCESS);
}