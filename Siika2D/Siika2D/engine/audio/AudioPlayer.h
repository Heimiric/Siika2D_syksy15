#pragma once

#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include <string>
#include "../core/ResourceManager.h"

namespace audio
{ 
	/**
		Class to wrap OpenSL audio functionality.
		For playing sounds use Audio class.
	*/
	class AudioPlayer 
	{
		friend class AudioInitializer;

	public:
		AudioPlayer(core::AudioData* audioAsset){ _audioAsset = audioAsset; }
		AudioPlayer(AudioPlayer* pointer);
		~AudioPlayer();

		/**
			Returns current play state of the audio clip
			1 = SL_PLAYSTATE_STOPPED
			2 = SL_PLAYSTATE_PAUSED
			3 = SL_PLAYSTATE_PLAYING
		*/
		SLuint32 getPlayState();

		/**
			Set current play state.
		*/
		void setPlayState(SLuint32 state);

		/**
			Sets looping to given value.
			'isEnabled = true' enables looping. Audio loops after calling Play().
			'isEnabled = false' disables looping.
		*/
		void setLooping(bool isEnabled); 

		/**
			Sets the volume to given value.
			VolumeLevel as percentage.
		*/
		void setVolume(float volPercentage);

		/**
			Returns AudioData struct. AudioData is defined in ResourceManager.h
		*/
		core::AudioData* getAudioAsset(){ return _audioAsset; }

	private:
		SLObjectItf _audioPlayerObj;
		SLPlayItf _audioPlayerPlay;
		SLSeekItf _audioPlayerSeek;
		SLVolumeItf _audioPlayerVol;

		SLresult _result;

		core::AudioData* _audioAsset;
	};
}