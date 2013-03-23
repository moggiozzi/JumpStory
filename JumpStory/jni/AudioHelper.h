#ifndef AUDIO_HELPER_H_
#define AUDIO_HELPER_H_

#include "Global.h"
#include <map>
#include <string>
#ifdef __ANDROID__
// for native audio
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
typedef std::map<int,SLObjectItf> Sounds;
#elif _WIN32
#include "Sound.h"
typedef std::map<int,Sound*> Sounds;
#endif

class AudioHelper{
  static bool isInit;
	static Sounds sounds;
  static int lastSoundId;
#ifdef __ANDROID__
 	// engine interfaces
	static SLObjectItf engineObject;
	static SLEngineItf engineEngine;
	// output mix interfaces
	static SLObjectItf outputMixObject;
	static AAssetManager *assetManager;
	static SLObjectItf createAssetAudioPlayer(const char * fileName);
#elif _WIN32
  static Sound *getSound(int soundId);
#endif

public:
#ifdef __ANDROID__
  static bool init(ANativeActivity* activity);
#elif _WIN32
  static bool init();
#endif
  static bool destroy();
  static bool open(const char *file, int& soundId, bool isStreamed = true);
  static void play(int soundId, bool isLoop = false);
  static void stop(int soundId);
  static void update();
};

#endif