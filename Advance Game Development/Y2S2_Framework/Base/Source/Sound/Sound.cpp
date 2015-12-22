#include "Sound.h"
#include <iostream>
#include <irrKlang.h>

#pragma comment (lib, "irrKlang.lib")
using namespace irrklang;

//ISoundEngine *sound = createIrrKlangDevice(ESOD_AUTO_DETECT, ESEO_MULTI_THREADED | ESEO_LOAD_PLUGINS | ESEO_USE_3D_BUFFERS);
//ISoundEngine * sound2 = createIrrKlangDevice();

static irrklang::ISoundEngine* sound1 = createIrrKlangDevice();
static irrklang::ISoundEngine* sound2 = createIrrKlangDevice();

Sound::Sound()
{
}


Sound::~Sound()
{
}

void Sound::playCollidingSound()
{
	//sound->play3D("../irrKlang/media/Collision_Pool.mp3", vec3df(0, 0, 0), false);
}

void Sound::playBeamMagnum()
{
	/*double soundVolume = sound2->getSoundVolume();
	sound2->setSoundVolume(1.f);*/
	//sound2->setAllSoundsPaused();
	sound2->play3D("../IrrKlang/media/BeamMagnum.mp3", vec3df(0, 0, 0), false);
	//sound2->setSoundVolume(soundVolume);
}

void Sound::playBackground()
{
	//double soundVolume = sound2->getSoundVolume();
	sound1->setSoundVolume(0.2);
	sound1->play3D("../IrrKlang/media/background.mp3", vec3df(0, 0, 0), true);
	//sound2->setSoundVolume(0.2);
}