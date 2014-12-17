#ifndef SCENE_H
#define SCENE_H

/****************************************************************************/
/*!
\file	Scene.h
\author Ong Swee Seng
\brief Scene.h is used to create other Scene classes, it is a an abstract class by itself
*/
/****************************************************************************/

/******************************************************************************/
/*!
		Class Scene:
\brief	Provides methods to create other Scene classes, it is a an abstract class by itself
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