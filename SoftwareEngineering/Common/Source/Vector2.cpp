#include "Vector2.h"
#include <cmath>
#include "MyMath.h"

Vector2::Vector2( float a, float b )
{
}

Vector2::Vector2( const Vector2 &rhs )
{
}

void Vector2::Set( float a, float b )
{
	x = a;
	y = b;
}

Vector2 Vector2::operator+( const Vector2& rhs ) const
{
	return Vector2(x + rhs.x, y + rhs.y);
}

Vector2 Vector2::operator-( const Vector2& rhs ) const
{
	return Vector2(x - rhs.x, y - rhs.y);
}

Vector2 Vector2::operator-( void ) const
{
	return Vector2(-x, -y);
}

Vector2 Vector2::operator*( float scalar ) const
{
	return Vector2(scalar * x, scalar * y);
}

float Vector2::Length( void ) const
{
	return sqrt(x * x + y * y);
}

float Vector2::Dot( const Vector2& rhs ) const
{
	return x * rhs.x + y * rhs.y;
}

Vector2 Vector2::Normalized( void ) 
{
	return Vector2(-y, +x);
}
