#include "stdafx.h"
#include "Vector2.h"

using namespace Base;

const cVector2 cVector2::Zero(0.0f, 0.0f);

//  *******************************************************************************************************************
cVector2::cVector2()
	: x(0)
	, y(0)
{
}

//  *******************************************************************************************************************
cVector2::cVector2(const float X, const float Y)
	: x(X)
	, y(Y)
{
}

//  ********************************************************************************************************************
cVector2::cVector2(float arr[])
{
	v[0] = arr[0];
	v[1] = arr[1];
}

//  *******************************************************************************************************************
cVector2::cVector2(POINT pt)
	: x(pt.x)
	, y(pt.y)
{
}

//  *******************************************************************************************************************
float cVector2::Length() const
{
	return sqrt(LengthSquared());
}

//  *******************************************************************************************************************
float cVector2::LengthSquared() const
{
	return (x * x + y * y);
}

//  *******************************************************************************************************************
void cVector2::Normalize()
{
	float length = Length();

	if (length > EpsilonFloat)
	{
		x /= length;
		y /= length;
	}
}

//  *******************************************************************************************************************
float cVector2::Dot(const cVector2 & inVec) const
{
	return x * inVec.x + y * inVec.y;
}

//  *******************************************************************************************************************
float cVector2::Distance(const cVector2 & inVec) const
{
	return sqrt(DistanceSquared(inVec));
}

//  *******************************************************************************************************************
float cVector2::DistanceSquared(const cVector2 & inVec) const
{
	float ySeparation = inVec.y - y;
	float xSeparation = inVec.x - x;

	return (ySeparation * ySeparation + xSeparation * xSeparation);
}

//  *******************************************************************************************************************
void cVector2::Reflect(cVector2 axis)
{
	axis.Normalize();
	*this -= 2.0f * this->Dot(axis) * axis;
}

//  ********************************************************************************************************************
void cVector2::AbsTo() 
{
	x = abs(x);
	y = abs(y);
}

//  ********************************************************************************************************************
cVector2 cVector2::MajorAxis() const
{
	float absX = abs(x);
	float absY = abs(y);

	if(absX > absY)
	{
		float signX = static_cast<float>(Sign(x));
		return cVector2(signX, 0);
	}
	else if (absY > absX)
	{
		float signY = static_cast<float>(Sign(y));
		return cVector2(0, signY);
	}

	return cVector2::Zero;
}

//  ********************************************************************************************************************
cVector2 cVector2::MinorAxis() const
{
	float absX = abs(x);
	float absY = abs(y);

	if(absX < absY)
	{
		float signX = static_cast<float>(Sign(x));
		return cVector2(signX, 0);
	}
	else if (absY < absX)
	{
		float signY = static_cast<float>(Sign(y));
		return cVector2(0, signY);
	}

	return cVector2::Zero;
}

//  ********************************************************************************************************************
void cVector2::NegTo() 
{
	x = -x;
	y = -y;
}

//  ********************************************************************************************************************
const cVector2 & cVector2::operator += (const cVector2 & inVec)
{
	x += inVec.x;
	y += inVec.y;

	return *this;
}

//  ********************************************************************************************************************
const cVector2 & cVector2::operator -= (const cVector2 & inVec)
{
	x -= inVec.x;
	y -= inVec.y;

	return *this;
}

//  ********************************************************************************************************************
const cVector2 & cVector2::operator *= (const cVector2 & inVec)
{
	x *= inVec.x;
	y *= inVec.y;

	return *this;
}

//  ********************************************************************************************************************
const cVector2 & cVector2::operator *= (const float Val)
{
	x *= Val;
	y *= Val;

	return *this;
}

//  ********************************************************************************************************************
const cVector2 & cVector2::operator /= (const float Val)
{
	x /= Val;
	y /= Val;

	return *this;
}

//  ********************************************************************************************************************
float & cVector2::operator[](const unsigned int index)
{
	assert(index >= 0 && index < 2);
	return *((&x) + index);
}

//  ********************************************************************************************************************
const float cVector2::operator [] (const unsigned int index) const
{
	assert(index >= 0 && index < 2);
	return *((&x) + index);
}

//  ********************************************************************************************************************
cVector2 cVector2::MakeVectorFromAngle(const float AngleInDegrees)
{
	cVector2 Dir;
	float rad = DegtoRad(AngleInDegrees);
	Dir.x = cos(rad);
	Dir.y = sin(rad);
	return Dir;
}

//  *******************************************************************************************************************
cVector2 cVector2::Lerp(const cVector2 & start, const cVector2 & end, float lerpFactor)
{
	Clamp<float>(lerpFactor, 0.0f, 1.0f);
	return Interpolate<cVector2>(start, end, lerpFactor);
}

//  ********************************************************************************************************************
std::ostream & Base::operator<<(std::ostream &out, const cVector2 & v)
{
	out << v.x << " : " << v.y;
	return out;
}
