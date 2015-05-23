#include "SpriteAnimation.h"
#include "GL\glew.h"


//SpriteAnimation::SpriteAnimation(void)
//{
//}

SpriteAnimation::SpriteAnimation(const std::string &meshName, int row, int col):
Mesh(meshName),
m_row(row),
m_col(col),
m_currentTime(0),
m_currentFrame(0),
m_playCount(0)
{
	m_anim = NULL;
}


SpriteAnimation::~SpriteAnimation(void)
{
	if(m_anim)
		delete m_anim;
}

void SpriteAnimation::Update(double dt)
{
	if (m_anim)//If anything happens
	{
		//Animate time increment by delta time
		this->m_currentTime += dt;

		int numFrame = Math::Max(1, m_anim->endFrame - m_anim->startFrame + 1);

		//numFrame is set to Max value between (1, endFrame - startFrame + 1))
	/*	this->m_currentFrame = (this->m_anim->endFrame - this->m_anim->startFrame + 1);
		if (this->m_currentFrame < 1)
		{
			this->m_currentFrame = 1;
		}*/

		//frameTime = animTime/ numFrame
		float frameTime = this->m_anim->animTime/ numFrame;

		m_currentTime = Math::Min(m_anim->endFrame, static_cast<int>(m_anim->startFrame + (m_currentTime/frameTime)));

		//m_currentFrame is set to the minimum value between(endFrame, (startFrame + (m_currentTime/ frameTime))) 
		/*this->m_currentFrame = (this->m_anim->startFrame + this->m_currentTime / this->m_anim->animTime);
		if(this->m_currentFrame > this->m_anim->endFrame)
		{
			this->m_currentFrame = this->m_anim->endFrame;
		}*/

		//If m_currentTime is greater than animTime. Set animation to end
		if (this->m_currentTime > this->m_anim->animTime)
		{
			this->m_anim->ended = true;
			if (this->m_playCount + 1 < this->m_anim->repeatCount || this->m_anim->repeatCount == 0)
			{
				this->m_playCount ++;
				m_currentTime = 0;
				this->m_currentFrame = this->m_anim->startFrame;
			}
		}

		/*
		if m_playCount + 1 is less than repeatCount or repeatCount == 0
		Then increment m_playCount
		Reset m_currentTime
		set m_currentFrame = startFrame
		*/
	}
}

void SpriteAnimation::Render()
{
	Mesh::Render(m_currentFrame * m_col, m_col);
}