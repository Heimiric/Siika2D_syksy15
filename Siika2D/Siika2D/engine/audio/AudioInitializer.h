#pragma once

#include "AudioPlayer.h"

namespace audio
{
	/**
		Initializes OpenSL and audio player.
	*/
	class AudioInitializer
	{
	public:
		static AudioInitializer* getInstance();

		/**
			Initialize OpenSL data structures and AudioPlayer
		*/
		void initAudioPlayer(AudioPlayer* player);
		
	private:
		
		/**
			Create and initialize OpenSL engine, engineObject and OpenSL outputMix object.
		*/
		void createEngine();

		AudioInitializer();
		~AudioInitializer();		

		SLresult _result;

		SLObjectItf _engineObj;
		SLEngineItf _engine;

		SLObjectItf _outputMixObj;
		SLVolumeItf _outputMixVol;

		static AudioInitializer* _instance;
	};
}