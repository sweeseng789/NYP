#ifndef SCENE_H
#define SCENE_H

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