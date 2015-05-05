/******************************************************************************/
/*!
\file	Scene.h
\author Ong Swee Seng, Lazarus Tan , Princeton Chew , Adela Quek
\par	email: 142128G@mymail.nyp.edu.sg
\brief
Scene Class
*/
/******************************************************************************/
#ifndef SCENE_H
#define SCENE_H
/******************************************************************************/
/*!
	Class Scene:
\brief
Defines what scene to run. Rendering, what happens every frame and exiting of scene
*/
/******************************************************************************/
class Scene
{
public:
	Scene() {}
	~Scene() {}

	virtual void Init() = 0;
	virtual void Update(double dt) = 0;
	virtual void Render() = 0;
	virtual void Exit() = 0;
};

#endif