#include "AudioInitializer.h"
#include "../core/ErrorHandler.h"

using namespace audio;

AudioInitializer* AudioInitializer::_instance = nullptr;

void AudioPlayerCallback(SLPlayItf playerObject, void* context, SLuint32 event)
{
	s2d_info(("AudioPlayer callback called."));

	if (event == SL_PLAYEVENT_HEADATEND)
	{
		s2d_info(("AudioPlayer callback event: SL_PLAYEVENT_HEADATED."));
		(*playerObject)->SetPlayState(playerObject, SL_PLAYSTATE_STOPPED);
	}
}

AudioInitializer* AudioInitializer::getInstance()
{
	if (_instance == nullptr)
		_instance = new AudioInitializer();

	return _instance;
}

void AudioInitializer::initAudioPlayer(AudioPlayer* player)
{
	SLDataLocator_AndroidFD locator = { SL_DATALOCATOR_ANDROIDFD, player->getAudioAsset()->fileDescriptor, player->getAudioAsset()->start, player->getAudioAsset()->length };
	SLDataFormat_MIME format = { SL_DATAFORMAT_MIME, nullptr, SL_CONTAINERTYPE_UNSPECIFIED };
	SLDataSource audioSrc = { &locator, &format };

	SLDataLocator_OutputMix tempOutmix = { SL_DATALOCATOR_OUTPUTMIX, _outputMixObj };
	SLDataSink tempAudioSink = { &tempOutmix, nullptr };

	const SLInterfaceID tempIds[3] = { SL_IID_PLAY, SL_IID_SEEK, SL_IID_VOLUME };
	const SLboolean tempReq[3] = { SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE };

	_result = (*_engine)->CreateAudioPlayer(_engine, &player->_audioPlayerObj, &audioSrc, &tempAudioSink, 3, tempIds, tempReq);
	s2d_assert(_result == SL_RESULT_SUCCESS);

	_result = (*player->_audioPlayerObj)->Realize(player->_audioPlayerObj, SL_BOOLEAN_FALSE);
	s2d_assert(_result == SL_RESULT_SUCCESS);

	_result = (*player->_audioPlayerObj)->GetInterface(player->_audioPlayerObj, SL_IID_PLAY, &player->_audioPlayerPlay);
	s2d_assert(_result == SL_RESULT_SUCCESS);

	_result = (*player->_audioPlayerObj)->GetInterface(player->_audioPlayerObj, SL_IID_SEEK, &player->_audioPlayerSeek);
	s2d_assert(_result == SL_RESULT_SUCCESS);

	_result = (*player->_audioPlayerObj)->GetInterface(player->_audioPlayerObj, SL_IID_VOLUME, &player->_audioPlayerVol);
	s2d_assert(_result == SL_RESULT_SUCCESS);

	_result = (*player->_audioPlayerPlay)->RegisterCallback(player->_audioPlayerPlay, AudioPlayerCallback, NULL);
	s2d_assert(_result == SL_RESULT_SUCCESS);

	_result = (*player->_audioPlayerPlay)->SetCallbackEventsMask(player->_audioPlayerPlay, SL_PLAYEVENT_HEADATEND);
	s2d_assert(_result == SL_RESULT_SUCCESS);

}

void AudioInitializer::createEngine()
{
	_result = slCreateEngine(&_engineObj, 0, nullptr, 0, nullptr, nullptr);
	s2d_assert(_result == SL_RESULT_SUCCESS);

	_result = (*_engineObj)->Realize(_engineObj, SL_BOOLEAN_FALSE);
	s2d_assert(_result == SL_RESULT_SUCCESS);

	_result = (*_engineObj)->GetInterface(_engineObj, SL_IID_ENGINE, &_engine);
	s2d_assert(_result == SL_RESULT_SUCCESS);

	_result = (*_engine)->CreateOutputMix(_engine, &_outputMixObj, 0, NULL, NULL);
	s2d_assert(_result == SL_RESULT_SUCCESS);

	_result = (*_outputMixObj)->Realize(_outputMixObj, SL_BOOLEAN_FALSE);
	s2d_assert(_result == SL_RESULT_SUCCESS);
}

AudioInitializer::AudioInitializer()
{
	createEngine();
}

AudioInitializer::~AudioInitializer()
{
	if (_outputMixObj != nullptr)
	{
		(*_outputMixObj)->Destroy(_outputMixObj);

		_outputMixObj = nullptr;
		_outputMixVol = nullptr;
	}

	if(_engineObj != nullptr)
	{
		(*_engineObj)->Destroy(_engineObj);

		_engineObj = nullptr;
		_engine = nullptr;
	}
}