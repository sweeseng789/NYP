#include "Sound.h"
#include <iostream>
#include <irrKlang.h>

#pragma comment (lib, "irrKlang.lib")
using namespace irrklang;

//ISoundEngine *sound = createIrrKlangDevice(ESOD_AUTO_DETECT, ESEO_MULTI_THREADED | ESEO_LOAD_PLUGINS | ESEO_USE_3D_BUFFERS);
//ISoundEngine * sound2 = createIrrKlangDevice();

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
	sound2->play3D("../IrrKlang/media/BeamMagnum.mp3", vec3df(0, 0, 0), false);
}