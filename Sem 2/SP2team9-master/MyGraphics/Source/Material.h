/******************************************************************************/
/*!
\file	Material.h
\author Ong Swee Seng, Lazarus Tan , Princeton Chew , Adela Quek
\par	email: 142128G@mymail.nyp.edu.sg
\brief
Material Struct
*/
/******************************************************************************/
#ifndef MATERIAL_H
#define MATERIAL_H
/******************************************************************************/
/*!
	Struct hitBox:
\brief
Defines the component.(Color)
*/
/******************************************************************************/
struct Component
{
	float r, g, b;

	Component(float r = 0.1f, float g = 0.1f, float b = 0.1f)
	{
		Set(r,g,b);
	}

	void Set(float r, float g, float b)
	{
		this->r = r; 
		this->g = g; 
		this->b = b;
	}

};
/******************************************************************************/
/*!
	Struct hitBox:
\brief
Defines the material (Ambient,Diffuse and shininess)
*/
/******************************************************************************/
struct Material
{
	Component kAmbient;
	Component kDiffuse;
	Component kSpecular;
	float kShininess;

	Material()
	{
	}
};

#endif