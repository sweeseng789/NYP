#ifndef SPRITE_ANIMATION_H
#define SPRITE_ANIMATION_H

#include "Mesh.h"
#include "Vector3.h"
#include "Vertex.h"

struct Animation
{
	Animation() {}

	void Set(int startFrame, int endFrame, int repeat, float time)
	{
		this->startFrame = startFrame;
		this->endFrame = endFrame;
		this->repeatCount = repeat;
		this->animTime = time;
	}

	int startFrame;
	int endFrame;
	int repeatCount;
	float animTime;
	bool ended;
};

class SpriteAnimation : public Mesh
{
public:
	SpriteAnimation(const std::string &meshName, int row, int col);
	//SpriteAnimation(void);
	~SpriteAnimation(void);

	void Update(double dt);
	void Render();

	int m_row;
	int m_col;

	float m_currentTime;
	int m_currentFrame;
	int m_playCount;
	Animation * m_anim;
};

#endif