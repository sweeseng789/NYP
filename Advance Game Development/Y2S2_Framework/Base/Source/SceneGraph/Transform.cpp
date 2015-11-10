#include "Transform.h"

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#include <windows.h> // Header File For Windows
#include <gl\gl.h> // Header File For The OpenGL32 Library
#include <gl\glu.h> // Header File For The GLu32 Library

CTransform::CTransform(void) :
	s_Orientation(NULL)
{
	Mtx.SetToZero();
	Mtx.SetToIdentity();
	Update_Mtx.SetToZero();
	Update_Mtx.SetToIdentity();
	rotationDir.SetZero();
	rotationDir_Offset.SetZero();
	angle = NULL;
}

CTransform::CTransform( const float dx, const float dy, const float dz )
{
	Mtx.SetToTranslation( dx, dy, dz );
}

CTransform::~CTransform(void)
{
}

void CTransform::PreRendering()
{
	//glPushMatrix();
	//glMultMatrixf(Mtx.a);
}

void CTransform::Draw(void)
{
}

void CTransform::PostRendering()
{
	glPopMatrix();
}

void CTransform::SetTranslate( const float dx, const float dy, const float dz  )
{
	Mtx44 TempMtx;
	TempMtx.SetToTranslation( dx, dy, dz );

	Mtx = Mtx * TempMtx;
}

void CTransform::SetRotate( const float angle, const float rx, const float ry, const float rz  )
{
	/*Mtx44 TempMtx;
	TempMtx.SetToRotation( angle, rx, ry, rz );
	
	Mtx44 MtxBackToOrigin;

	MtxBackToOrigin.a[ 12 ] = -Mtx.a[ 12 ];
	MtxBackToOrigin.a[ 13 ] = -Mtx.a[ 13 ];
	MtxBackToOrigin.a[ 14 ] = -Mtx.a[ 14 ];

	Mtx44 MtxBackToPosition;
	MtxBackToPosition.a[ 12 ] = Mtx.a[ 12 ];
	MtxBackToPosition.a[ 13 ] = Mtx.a[ 13 ];
	MtxBackToPosition.a[ 14 ] = Mtx.a[ 14 ];

	Mtx = Mtx * MtxBackToOrigin;
	Mtx = Mtx * TempMtx;
	Mtx = Mtx * MtxBackToPosition;*/

	this->angle = angle;
	rotationDir.x = rx;
	rotationDir.y = ry;
	rotationDir.z = rz;
}

void CTransform::setRotationOrientation(const float angleOrienation, const float rx, const float ry, const float rz)
{
	/*this->angleOrientation = angleOrienation;
	rotationDir_Orientation.x = rx;
	rotationDir_Orientation.y = ry;
	rotationDir_Orientation.z = rz;*/

	ORIENTATION newOrientation;
	newOrientation.angle = angleOrienation;
	newOrientation.rotateDir = Vector3(rx, ry, rz);

	s_Orientation.push_back(newOrientation);
}

void CTransform::SetRotate2(const float angle, const float rx, const float ry, const float rz, const float offset_x, const float offset_y, const float offset_z)
{
	this->angle = angle;

	rotationDir.x = rx;
	rotationDir.y = ry;
	rotationDir.z = rz;

	rotationDir_Offset.x = offset_x;
	rotationDir_Offset.y = offset_y;
	rotationDir_Offset.z = offset_z;
}

void CTransform::SetScale( const float sx, const float sy, const float sz  )
{
	//Mtx.SetToScale( sx, sy, sz );
	Mtx44 temp;
	temp.SetToScale(sx, sy, sz);

	Mtx = Mtx * temp;
}

void CTransform::GetTranslation( float& x, float& y, float& z )
{
	x = Mtx.a[ 12 ];
	y = Mtx.a[ 13 ];
	z = Mtx.a[ 14 ];
}

void CTransform::GetScale(float& x, float& y, float& z)
{
	x = Mtx.a[0];
	y = Mtx.a[5];
	z = Mtx.a[10];
}

void CTransform::GetRotation(double &angle, float &x, float &y, float &z)
{
	angle = this->angle;

	x = rotationDir.x;
	y = rotationDir.y;
	z = rotationDir.z;
}

void CTransform::GetRotation2(double &angle, float &x, float &y, float &z, float &offset_x, float &offset_y, float &offset_z)
{
	angle = this->angle;

	x = rotationDir.x;
	y = rotationDir.y;
	z = rotationDir.z;

	offset_x = rotationDir_Offset.x;
	offset_y = rotationDir_Offset.y;
	offset_z = rotationDir_Offset.z;
}

std::vector<CTransform::ORIENTATION> CTransform::getOrientation()
{
	return s_Orientation;
}


// Get the transformation matrix
Mtx44 CTransform::GetTransform(void)
{
	return Mtx;
}