#pragma once
#include "Vertex.h"
#include "Vector3.h"

class CText
{
public:
	CText(Vector3 pos);
	~CText();

	void Update(const double &dt, const Vector3 &mousePos);

private:
	Vector3 pos;
	Color color;

	static Color OnClick;
	static Color NotOnClick;
};