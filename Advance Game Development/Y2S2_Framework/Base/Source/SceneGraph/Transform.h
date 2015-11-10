#pragma once
#include "node.h"
#include "Mtx44.h"
#include "MatrixStack.h"
#include <vector>

class CSceneNode;

class CTransform :
	public CNode
{
public:
	struct ORIENTATION
	{
		float angle = 0;
		Vector3 rotateDir = Vector3(0, 0, 0);
	};

	CTransform(void);
	CTransform( const float dx, const float dy, const float dz  );
	~CTransform(void);

	void PreRendering();
	void Draw(void);
	void PostRendering();

	void SetTranslate( const float dx, const float dy, const float dz  );
	void SetRotate( const float angle, const float rx, const float ry, const float rz  );
	void SetRotate2( const float angle, const float rx, const float ry, const float rz, 
					 const float offset_x, const float offset_y, const float offset_z );
	void setRotationOrientation(const float angleOrienation, const float rx, const float ry, const float rz);
	void SetScale( const float sx, const float sy, const float sz  );
//	void ApplyTransform( Matrix4x4 newMTX );
	void GetTranslation( float& x, float& y, float& z );
	void GetScale(float& x, float& y, float& z);
	void GetRotation(double &angle, float &x, float &y, float &z);
	void GetRotation2(double &angle, float &x, float &y, float &z, float &offset_x, float &offset_y, float &offset_z);

	std::vector<ORIENTATION> getOrientation();
	// Get the transformation matrix
	Mtx44 GetTransform(void);

private:
	Mtx44 Mtx, Update_Mtx;
	Vector3 rotationDir, rotationDir_Offset;
	float angle;

	std::vector<ORIENTATION> s_Orientation;
};
