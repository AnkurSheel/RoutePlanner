#include "stdafx.h"
#include "Vector3.h"

using namespace Base;

const cVector3 cVector3::Zero(0.0f, 0.0f, 0.0f);
const cVector3 cVector3::One(1.0f, 1.0f, 1.0f);

//  *******************************************************************************************************************
cVector3::cVector3()
: x(0)
, y(0)
, z(0)
{
}

//  *******************************************************************************************************************
cVector3::cVector3(const float X, const float Y, const float Z)
: x(X)
, y(Y)
, z(Z)
{
}

//  ********************************************************************************************************************
cVector3::cVector3(float arr[])
{
	v[0] = arr[0];
	v[1] = arr[1];
	v[2] = arr[2];
}

//  *******************************************************************************************************************
float cVector3::Length() const
{
	return sqrt(LengthSquared());
}

//  *******************************************************************************************************************
float cVector3::LengthSquared() const
{
	return (x * x + y * y + z * z);
}

//  *******************************************************************************************************************
void cVector3::Normalize()
{
	float length = Length();

	if (length > EpsilonFloat)
	{
		x /= length;
		y /= length;
		z /= length;
	}
}

//  *******************************************************************************************************************
float cVector3::Dot(const cVector3 & inVec) const
{
	return x * inVec.x + y * inVec.y + z * inVec.z;
}

//  *******************************************************************************************************************
cVector3 cVector3::Cross(const cVector3 & inVec) const
{
	return cVector3(y * inVec.z - z * inVec.y, z * inVec.x - x * inVec.z, x * inVec.y - y * inVec.x);
}

//  *******************************************************************************************************************
float cVector3::Distance(const cVector3 & inVec) const
{
	return sqrt(DistanceSquared(inVec));
}

//  *******************************************************************************************************************
float cVector3::DistanceSquared(const cVector3 & inVec) const
{
	float xSeparation = inVec.x - x;
	float ySeparation = inVec.y - y;
	float zSeparation = inVec.z - z;

	return xSeparation * xSeparation + ySeparation * ySeparation + zSeparation * zSeparation;
}

//  *******************************************************************************************************************
void cVector3::AbsTo() 
{
	x = abs(x);
	y = abs(y);
	z = abs(z);
}

//  *******************************************************************************************************************
void cVector3::NegTo() 
{
	x = -x;
	y = -y;
	z = -z;
}

//  *******************************************************************************************************************
cVector3 cVector3::MajorAxis() const
{
	float absX = abs(x);
	float absY = abs(y);
	float absZ = abs(z);

	if(absX > absY)
	{
		if(absX > absZ)
		{
			float signX = static_cast<float>(Sign(x));
			return cVector3(signX, 0, 0);
		}
		else if(absX < absZ)
		{
			float signZ = static_cast<float>(Sign(z));
			return cVector3(0,0,signZ);
		}
	}
	else
	{
		if(absY > absZ)
		{
			float signY = static_cast<float>(Sign(y));
			return cVector3(0, signY, 0);
		}
		else if(absY < absZ)
		{
			float signZ = static_cast<float>(Sign(z));
			return cVector3(0, 0, signZ);
		}
	}

	return cVector3::Zero;
}

//  *******************************************************************************************************************
cVector3 cVector3::MinorAxis() const
{
	float absX = abs(x);
	float absY = abs(y);
	float absZ = abs(z);

	if(absX < absY)
	{
		if(absZ < absX)
		{
			float signZ = static_cast<float>(Sign(z));
			return cVector3(0.0f, 0.0f ,signZ);
		}
		else
		{
			float signX = static_cast<float>(Sign(x));
			return cVector3(signX, 0, 0);
		}
	}
	else
	{
		if(absY < absZ)
		{
			float signY = static_cast<float>(Sign(y));
			return cVector3(0, signY, 0);
		}
		else if(absY > absZ)
		{
			float signZ = static_cast<float>(Sign(z));
			return cVector3(0, 0, signZ);
		}
	}
	return cVector3::Zero;
}

//  *******************************************************************************************************************
const cVector3 & cVector3::operator += (const cVector3 & inVec)
{
	x += inVec.x;
	y += inVec.y;
	z += inVec.z;

	return *this;
}

//  *******************************************************************************************************************
const cVector3 & cVector3::operator -= (const cVector3 & inVec)
{
	x -= inVec.x;
	y -= inVec.y;
	z -= inVec.z;
	return *this;
}

//  *******************************************************************************************************************
const cVector3 & cVector3::operator *= (const cVector3 & inVec)
{
	x *= inVec.x;
	y *= inVec.y;
	z *= inVec.z;

	return *this;
}

//  *******************************************************************************************************************
const cVector3 & cVector3::operator *= (const float Val)
{
	x *= Val;
	y *= Val;
	z *= Val;
	return *this;
}

//  *******************************************************************************************************************
const cVector3 & cVector3::operator /= (const float Val)
{
	x /= Val;
	y /= Val;
	z /= Val;
	return *this;
}

//  *******************************************************************************************************************
cVector3 cVector3::Lerp(const cVector3 & start, const cVector3 & end, float lerpFactor)
{
	Clamp<float>(lerpFactor, 0.0f, 1.0f);
	return Interpolate<cVector3>(start, end, lerpFactor);
}

//  *******************************************************************************************************************
float & cVector3::operator [] (const unsigned int index)
{
	assert(index >= 0 && index < 3);
	return *((&x) + index);
}

//  *******************************************************************************************************************
const float cVector3::operator [] (const unsigned int index) const
{
	assert(index >= 0 && index < 3);
	return *((&x) + index);
}
