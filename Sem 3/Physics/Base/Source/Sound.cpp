#include "Sound.h"
#include <irrKlang.h>

#pragma comment (lib, "irrKlang.lib")
using namespace irrklang;
ISoundEngine *sound = createIrrKlangDevice(ESOD_AUTO_DETECT, ESEO_MULTI_THREADED | ESEO_LOAD_PLUGINS | ESEO_USE_3D_BUFFERS);

Sound::Sound()
{
}


Sound::~Sound()
{
}

void Sound::playCollidingSound()
{
	sound->play3D("../irrKlang/media/Collision_Pool.mp3", vec3df(0, 0, 0), false);
}

void Sound::playCollidingSound_Wall()
{
	sound->play3D("../irrKlang/media/Collision_Wall.mp3", vec3df(0, 0, 0), false);
}

void Sound::playWinningSound()
{
	sound->play3D("../irrKlang/media/Winning.mp3", vec3df(0, 0, 0), false);
}

void Sound::playBooing()
{
	sound->play3D("../irrKlang/media/Booing.mp3", vec3df(0, 0, 0), false);
}