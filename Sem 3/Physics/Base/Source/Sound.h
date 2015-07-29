#pragma once

class Sound
{
public:
	Sound();
	~Sound();

	static void playCollidingSound();
	static void playCollidingSound_Wall();
	static void playWinningSound();
	static void playBooing();
};

