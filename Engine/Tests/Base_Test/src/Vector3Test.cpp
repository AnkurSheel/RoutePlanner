#include "stdafx.h"
#include "Vector3.h"

using namespace Base;

class Vector3Test : public ::testing::Test
{
protected:
	cVector3 vec;
	cVector3 vec1;
	cVector3 vec2;

	void SetUp()
	{
		vec1 = cVector3(4.0f, 3.0f, 7.0f);
		vec2 = cVector3(-4.0f, 5.0f, -4.0f);
	}

	void TearDown()
	{
	}
};

TEST_F(Vector3Test, Constructors)
{
	EXPECT_FLOAT_EQ(0.0f, vec.x);
	EXPECT_FLOAT_EQ(0.0f, vec.y);
	EXPECT_FLOAT_EQ(0.0f, vec.z);

	EXPECT_FLOAT_EQ(4.0f, vec1.x);
	EXPECT_FLOAT_EQ(3.0f, vec1.y);
	EXPECT_FLOAT_EQ(7.0f, vec1.z);

	EXPECT_FLOAT_EQ(-4.0f, vec2.x);
	EXPECT_FLOAT_EQ(5.0f, vec2.y);
	EXPECT_FLOAT_EQ(-4.0f, vec2.z);

	float arr[3] = {2, 3, 5};
	cVector3 vec3(arr);
	EXPECT_FLOAT_EQ(2.0f, vec3.v[0]);
	EXPECT_FLOAT_EQ(3.0f, vec3.v[1]);
	EXPECT_FLOAT_EQ(5.0f, vec3.v[2]);
}

TEST_F(Vector3Test, isZero)
{
	EXPECT_TRUE(vec.IsZero());
	EXPECT_FALSE(vec1.IsZero());
	EXPECT_FALSE(vec2.IsZero());
}

TEST_F(Vector3Test, Length)
{
	EXPECT_NEAR(0.0f, vec.Length(), 0.1f);
	EXPECT_NEAR(8.6f, vec1.Length(), 0.1f);
	EXPECT_NEAR(7.54f, vec2.Length(), 0.1f);
}

TEST_F(Vector3Test, LengthSquared)
{
	EXPECT_FLOAT_EQ(0.0f, vec.LengthSquared());
	EXPECT_FLOAT_EQ(74.0f, vec1.LengthSquared());
	EXPECT_FLOAT_EQ(57.0f, vec2.LengthSquared());
}

TEST_F(Vector3Test, Normalize)
{
	vec.Normalize();
	EXPECT_FLOAT_EQ(0.0f, vec.x);
	EXPECT_FLOAT_EQ(0.0f, vec.y);
	EXPECT_FLOAT_EQ(0.0f, vec.z);

	vec1.Normalize();
	EXPECT_NEAR(0.46f, vec1.x, 0.1f);
	EXPECT_NEAR(0.34f, vec1.y, 0.1f);
	EXPECT_NEAR(0.81f, vec1.z, 0.1f);

	vec2.Normalize();
	EXPECT_NEAR(-0.52f, vec2.x, 0.1f);
	EXPECT_NEAR(0.66f, vec2.y, 0.1f);
	EXPECT_NEAR(-0.52f, vec2.z, 0.1f);
}

TEST_F(Vector3Test, Dot)
{
	EXPECT_NEAR(0.0f, vec.Dot(vec1), 0.1f);
	EXPECT_NEAR(0.0f, vec.Dot(vec2), 0.1f);
	EXPECT_NEAR(0.0f, vec1.Dot(vec), 0.1f);
	EXPECT_NEAR(74.0f, vec1.Dot(vec1), 0.1f);
	EXPECT_NEAR(-29.0f, vec1.Dot(vec2), 0.1f);
	EXPECT_NEAR(0.0f, vec2.Dot(vec), 0.1f);
	EXPECT_NEAR(-29.0f, vec2.Dot(vec1), 0.1f);
	EXPECT_NEAR(57.0f, vec2.Dot(vec2), 0.1f);
}

TEST_F(Vector3Test, Cross)
{
	cVector3 cross = vec.Cross(vec1);
	EXPECT_FLOAT_EQ(0.0f, cross.x);
	EXPECT_FLOAT_EQ(0.0f, cross.y);
	EXPECT_FLOAT_EQ(0.0f, cross.z);

	cross = vec.Cross(vec2);
	EXPECT_FLOAT_EQ(0.0f, cross.x);
	EXPECT_FLOAT_EQ(0.0f, cross.y);
	EXPECT_FLOAT_EQ(0.0f, cross.z);

	cross = vec1.Cross(vec);
	EXPECT_FLOAT_EQ(0.0f, cross.x);
	EXPECT_FLOAT_EQ(0.0f, cross.y);
	EXPECT_FLOAT_EQ(0.0f, cross.z);

	cross = vec1.Cross(vec1);
	EXPECT_FLOAT_EQ(0.0f, cross.x);
	EXPECT_FLOAT_EQ(0.0f, cross.y);
	EXPECT_FLOAT_EQ(0.0f, cross.z);

	cross = vec1.Cross(vec2);
	EXPECT_FLOAT_EQ(-47.0f, cross.x);
	EXPECT_FLOAT_EQ(-12.0f, cross.y);
	EXPECT_FLOAT_EQ(32.0f, cross.z);

	cross = vec2.Cross(vec);
	EXPECT_FLOAT_EQ(0.0f, cross.x);
	EXPECT_FLOAT_EQ(0.0f, cross.y);
	EXPECT_FLOAT_EQ(0.0f, cross.z);

	cross = vec2.Cross(vec1);
	EXPECT_FLOAT_EQ(47.0f, cross.x);
	EXPECT_FLOAT_EQ(12.0f, cross.y);
	EXPECT_FLOAT_EQ(-32.0f, cross.z);

	cross = vec2.Cross(vec2);
	EXPECT_FLOAT_EQ(0.0f, cross.x);
	EXPECT_FLOAT_EQ(0.0f, cross.y);
	EXPECT_FLOAT_EQ(0.0f, cross.z);

}

TEST_F(Vector3Test, Distance)
{
	EXPECT_NEAR(8.6f, vec.Distance(vec1), 0.1f);
	EXPECT_NEAR(7.5f, vec.Distance(vec2), 0.1f);
	EXPECT_NEAR(8.6f, vec1.Distance(vec), 0.1f);
	EXPECT_NEAR(13.7f, vec1.Distance(vec2), 0.1f);
	EXPECT_NEAR(7.5f, vec2.Distance(vec), 0.1f);
	EXPECT_NEAR(13.7f, vec2.Distance(vec1), 0.1f);
}

TEST_F(Vector3Test, DistanceSquared)
{
	EXPECT_FLOAT_EQ(74.0f, vec.DistanceSquared(vec1));
	EXPECT_FLOAT_EQ(57.0f, vec.DistanceSquared(vec2));
	EXPECT_FLOAT_EQ(74.0f, vec1.DistanceSquared(vec));
	EXPECT_FLOAT_EQ(189.0f, vec1.DistanceSquared(vec2));
	EXPECT_FLOAT_EQ(57.0f, vec2.DistanceSquared(vec));
	EXPECT_FLOAT_EQ(189.0f, vec2.DistanceSquared(vec1));
}

TEST_F(Vector3Test, AbsTo)
{
	vec.AbsTo();
	EXPECT_FLOAT_EQ(0.0f, vec.x);
	EXPECT_FLOAT_EQ(0.0f, vec.y);
	EXPECT_FLOAT_EQ(0.0f, vec.z);
	
	vec1.AbsTo();
	EXPECT_FLOAT_EQ(4.0f, vec1.x);
	EXPECT_FLOAT_EQ(3.0f, vec1.y);
	EXPECT_FLOAT_EQ(7.0f, vec1.z);
	
	vec2.AbsTo();
	EXPECT_FLOAT_EQ(4.0f, vec2.x);
	EXPECT_FLOAT_EQ(5.0f, vec2.y);
	EXPECT_FLOAT_EQ(4.0f, vec2.z);
}

TEST_F(Vector3Test, GetReverse)
{
	cVector3 reverse = vec.GetReverse();
	EXPECT_FLOAT_EQ(0.0f, reverse.x);
	EXPECT_FLOAT_EQ(0.0f, reverse.y);
	EXPECT_FLOAT_EQ(0.0f, reverse.z);

	reverse = vec1.GetReverse();
	EXPECT_FLOAT_EQ(-4.0f, reverse.x);
	EXPECT_FLOAT_EQ(-3.0f, reverse.y);
	EXPECT_FLOAT_EQ(-7.0f, reverse.z);

	reverse = vec2.GetReverse();
	EXPECT_FLOAT_EQ(4.0f, reverse.x);
	EXPECT_FLOAT_EQ(-5.0f, reverse.y);
	EXPECT_FLOAT_EQ(4.0f, reverse.z);
}

TEST_F(Vector3Test, NegTo)
{
	vec.NegTo();
	EXPECT_FLOAT_EQ(0.0f, vec.x);
	EXPECT_FLOAT_EQ(0.0f, vec.y);
	EXPECT_FLOAT_EQ(0.0f, vec.z);

	vec1.NegTo();
	EXPECT_FLOAT_EQ(-4.0f, vec1.x);
	EXPECT_FLOAT_EQ(-3.0f, vec1.y);
	EXPECT_FLOAT_EQ(-7.0f, vec1.z);

	vec2.NegTo();
	EXPECT_FLOAT_EQ(4.0f, vec2.x);
	EXPECT_FLOAT_EQ(-5.0f, vec2.y);
	EXPECT_FLOAT_EQ(4.0f, vec2.z);
}

TEST_F(Vector3Test, MajorAxis)
{
	cVector3 majorAxis = vec.MajorAxis();
	EXPECT_FLOAT_EQ(0.0f, majorAxis.x);
	EXPECT_FLOAT_EQ(0.0f, majorAxis.y);
	EXPECT_FLOAT_EQ(0.0f, majorAxis.z);

	majorAxis = vec1.MajorAxis();
	EXPECT_FLOAT_EQ(0.0f, majorAxis.x);
	EXPECT_FLOAT_EQ(0.0f, majorAxis.y);
	EXPECT_FLOAT_EQ(1.0f, majorAxis.z);

	majorAxis = vec2.MajorAxis();
	EXPECT_FLOAT_EQ(0.0f, majorAxis.x);
	EXPECT_FLOAT_EQ(1.0f, majorAxis.y);
	EXPECT_FLOAT_EQ(0.0f, majorAxis.z);

	cVector3 vec3(-4.1f, 4.0f, -2.0f);
	majorAxis = vec3.MajorAxis();
	EXPECT_FLOAT_EQ(-1.0f, majorAxis.x);
	EXPECT_FLOAT_EQ(0.0f, majorAxis.y);
	EXPECT_FLOAT_EQ(0.0f, majorAxis.z);
}
//
TEST_F(Vector3Test, MinorAxis)
{
	cVector3 minorAxis= vec.MinorAxis();
	EXPECT_FLOAT_EQ(0.0f, minorAxis.x);
	EXPECT_FLOAT_EQ(0.0f, minorAxis.y);
	EXPECT_FLOAT_EQ(0.0f, minorAxis.z);

	minorAxis = vec1.MinorAxis();
	EXPECT_FLOAT_EQ(0.0f, minorAxis.x);
	EXPECT_FLOAT_EQ(1.0f, minorAxis.y);
	EXPECT_FLOAT_EQ(0.0f, minorAxis.z);

	minorAxis = vec2.MinorAxis();
	EXPECT_FLOAT_EQ(-1.0f, minorAxis.x);
	EXPECT_FLOAT_EQ(0.0f, minorAxis.y);
	EXPECT_FLOAT_EQ(0.0f, minorAxis.z);

	cVector3 vec3(-3.9f, 4.0f, -2.0f);
	minorAxis = vec3.MinorAxis();
	EXPECT_FLOAT_EQ(0.0f, minorAxis.x);
	EXPECT_FLOAT_EQ(0.0f, minorAxis.y);
	EXPECT_FLOAT_EQ(-1.0f, minorAxis.z);

	vec3 = cVector3(4.0f, 4.0f, 2.0f);
	minorAxis = vec3.MinorAxis();
	EXPECT_FLOAT_EQ(0.0f, minorAxis.x);
	EXPECT_FLOAT_EQ(0.0f, minorAxis.y);
	EXPECT_FLOAT_EQ(1.0f, minorAxis.z);

	vec3 = cVector3(4.0f, 4.0f, 4.0f);
	minorAxis = vec3.MinorAxis();
	EXPECT_FLOAT_EQ(0.0f, minorAxis.x);
	EXPECT_FLOAT_EQ(0.0f, minorAxis.y);
	EXPECT_FLOAT_EQ(0.0f, minorAxis.z);
}

TEST_F(Vector3Test, operatorPlusEqual)
{
	cVector3 testVec = vec;
	testVec += vec1;
	EXPECT_FLOAT_EQ(4.0f, testVec.x);
	EXPECT_FLOAT_EQ(3.0f, testVec.y);
	EXPECT_FLOAT_EQ(7.0f, testVec.z);

	testVec = vec;
	testVec += vec2;
	EXPECT_FLOAT_EQ(-4.0f, testVec.x);
	EXPECT_FLOAT_EQ(5.0f, testVec.y);
	EXPECT_FLOAT_EQ(-4.0f, testVec.z);

	testVec = vec1;
	testVec += vec;
	EXPECT_FLOAT_EQ(4.0f, testVec.x);
	EXPECT_FLOAT_EQ(3.0f, testVec.y);
	EXPECT_FLOAT_EQ(7.0f, testVec.z);

	testVec = vec1;
	testVec += vec2;
	EXPECT_FLOAT_EQ(0.0f, testVec.x);
	EXPECT_FLOAT_EQ(8.0f, testVec.y);
	EXPECT_FLOAT_EQ(3.0f, testVec.z);

	testVec = vec2;
	testVec += vec;
	EXPECT_FLOAT_EQ(-4.0f, testVec.x);
	EXPECT_FLOAT_EQ(5.0f, testVec.y);
	EXPECT_FLOAT_EQ(-4.0f, testVec.z);

	testVec = vec2;
	testVec += vec1;
	EXPECT_FLOAT_EQ(0.0f, testVec.x);
	EXPECT_FLOAT_EQ(8.0f, testVec.y);
	EXPECT_FLOAT_EQ(3.0f, testVec.z);
}

TEST_F(Vector3Test, operatorMinusEqual)
{
	cVector3 testVec = vec;
	testVec -= vec1;
	EXPECT_FLOAT_EQ(-4.0f, testVec.x);
	EXPECT_FLOAT_EQ(-3.0f, testVec.y);
	EXPECT_FLOAT_EQ(-7.0f, testVec.z);

	testVec = vec;
	testVec -= vec2;
	EXPECT_FLOAT_EQ(4.0f, testVec.x);
	EXPECT_FLOAT_EQ(-5.0f, testVec.y);
	EXPECT_FLOAT_EQ(4.0f, testVec.z);

	testVec = vec1;
	testVec -= vec;
	EXPECT_FLOAT_EQ(4.0f, testVec.x);
	EXPECT_FLOAT_EQ(3.0f, testVec.y);
	EXPECT_FLOAT_EQ(7.0f, testVec.z);

	testVec = vec1;
	testVec -= vec2;
	EXPECT_FLOAT_EQ(8.0f, testVec.x);
	EXPECT_FLOAT_EQ(-2.0f, testVec.y);
	EXPECT_FLOAT_EQ(11.0f, testVec.z);

	testVec = vec2;
	testVec -= vec;
	EXPECT_FLOAT_EQ(-4.0f, testVec.x);
	EXPECT_FLOAT_EQ(5.0f, testVec.y);
	EXPECT_FLOAT_EQ(-4.0f, testVec.z);

	testVec = vec2;
	testVec -= vec1;
	EXPECT_FLOAT_EQ(-8.0f, testVec.x);
	EXPECT_FLOAT_EQ(2.0f, testVec.y);
	EXPECT_FLOAT_EQ(-11.0f, testVec.z);
}

TEST_F(Vector3Test, operatorMultiplyEqualVector)
{
	cVector3 testVec = vec;
	testVec *= vec1;
	EXPECT_FLOAT_EQ(0.0f, testVec.x);
	EXPECT_FLOAT_EQ(0.0f, testVec.y);
	EXPECT_FLOAT_EQ(0.0f, testVec.z);

	testVec = vec;
	testVec *= vec2;
	EXPECT_FLOAT_EQ(0.0f, testVec.x);
	EXPECT_FLOAT_EQ(0.0f, testVec.y);
	EXPECT_FLOAT_EQ(0.0f, testVec.z);

	testVec = vec1;
	testVec *= vec;
	EXPECT_FLOAT_EQ(0.0f, testVec.x);
	EXPECT_FLOAT_EQ(0.0f, testVec.y);
	EXPECT_FLOAT_EQ(0.0f, testVec.z);

	testVec = vec1;
	testVec *= vec2;
	EXPECT_FLOAT_EQ(-16.0f, testVec.x);
	EXPECT_FLOAT_EQ(15.0f, testVec.y);
	EXPECT_FLOAT_EQ(-28.0f, testVec.z);

	testVec = vec2;
	testVec *= vec;
	EXPECT_FLOAT_EQ(0.0f, testVec.x);
	EXPECT_FLOAT_EQ(0.0f, testVec.y);
	EXPECT_FLOAT_EQ(0.0f, testVec.z);

	testVec = vec2;
	testVec *= vec1;
	EXPECT_FLOAT_EQ(-16.0f, testVec.x);
	EXPECT_FLOAT_EQ(15.0f, testVec.y);
	EXPECT_FLOAT_EQ(-28.0f, testVec.z);
}

TEST_F(Vector3Test, operatorMultiplyEqualScalar)
{
	cVector3 testVec = vec;
	testVec *= 10.0f;
	EXPECT_FLOAT_EQ(0.0f, testVec.x);
	EXPECT_FLOAT_EQ(0.0f, testVec.y);
	EXPECT_FLOAT_EQ(0.0f, testVec.z);

	testVec = vec;
	testVec *= -10.0f;
	EXPECT_FLOAT_EQ(0.0f, testVec.x);
	EXPECT_FLOAT_EQ(0.0f, testVec.y);
	EXPECT_FLOAT_EQ(0.0f, testVec.z);

	testVec = vec1;
	testVec *= 10.0f;
	EXPECT_FLOAT_EQ(40.0f, testVec.x);
	EXPECT_FLOAT_EQ(30.0f, testVec.y);
	EXPECT_FLOAT_EQ(70.0f, testVec.z);

	testVec = vec1;
	testVec *= -10.0f;
	EXPECT_FLOAT_EQ(-40.0f, testVec.x);
	EXPECT_FLOAT_EQ(-30.0f, testVec.y);
	EXPECT_FLOAT_EQ(-70.0f, testVec.z);

	testVec = vec2;
	testVec *= 10.0f;
	EXPECT_FLOAT_EQ(-40.0f, testVec.x);
	EXPECT_FLOAT_EQ(50.0f, testVec.y);
	EXPECT_FLOAT_EQ(-40.0f, testVec.z);

	testVec = vec2;
	testVec *= -10.0f;
	EXPECT_FLOAT_EQ(40.0f, testVec.x);
	EXPECT_FLOAT_EQ(-50.0f, testVec.y);
	EXPECT_FLOAT_EQ(40.0f, testVec.z);
}

TEST_F(Vector3Test, operatorDivideEqualScalar)
{
	cVector3 testVec = vec;
	testVec /= 10.0f;
	EXPECT_FLOAT_EQ(0.0f, testVec.x);
	EXPECT_FLOAT_EQ(0.0f, testVec.y);
	EXPECT_FLOAT_EQ(0.0f, testVec.z);

	testVec = vec;
	testVec /= -10.0f;
	EXPECT_FLOAT_EQ(0.0f, testVec.x);
	EXPECT_FLOAT_EQ(0.0f, testVec.y);
	EXPECT_FLOAT_EQ(0.0f, testVec.z);

	testVec = vec1;
	testVec /= 10.0f;
	EXPECT_FLOAT_EQ(0.4f, testVec.x);
	EXPECT_FLOAT_EQ(0.3f, testVec.y);
	EXPECT_FLOAT_EQ(0.7f, testVec.z);

	testVec = vec1;
	testVec /= -10.0f;
	EXPECT_FLOAT_EQ(-0.4f, testVec.x);
	EXPECT_FLOAT_EQ(-0.3f, testVec.y);
	EXPECT_FLOAT_EQ(-0.7f, testVec.z);

	testVec = vec2;
	testVec /= 10.0f;
	EXPECT_FLOAT_EQ(-0.4f, testVec.x);
	EXPECT_FLOAT_EQ(0.5f, testVec.y);
	EXPECT_FLOAT_EQ(-0.4f, testVec.z);

	testVec = vec2;
	testVec /= -10.0f;
	EXPECT_FLOAT_EQ(0.4f, testVec.x);
	EXPECT_FLOAT_EQ(-0.5f, testVec.y);
	EXPECT_FLOAT_EQ(0.4f, testVec.z);
}

TEST_F(Vector3Test, OperatorEqual)
{
	EXPECT_TRUE(vec == vec);
	EXPECT_FALSE(vec == vec1);
	EXPECT_FALSE(vec == vec2);
	EXPECT_FALSE(vec1 == vec);
	EXPECT_TRUE(vec1 == vec1);
	EXPECT_FALSE(vec1 == vec2);
	EXPECT_FALSE(vec2 == vec);
	EXPECT_FALSE(vec2 == vec1);
	EXPECT_TRUE(vec2 == vec2);

	cVector3 vec3(4.0f, 3.0f, 7.0f);
	EXPECT_TRUE(vec1 == vec3);
	EXPECT_TRUE(vec3 == vec1);

	cVector3 vec4(vec2);
	EXPECT_TRUE(vec2 == vec4);
	EXPECT_TRUE(vec4 == vec2);
}

TEST_F(Vector3Test, OperatorNotEqual)
{
	EXPECT_FALSE(vec != vec);
	EXPECT_TRUE(vec != vec1);
	EXPECT_TRUE(vec != vec2);
	EXPECT_TRUE(vec1 != vec);
	EXPECT_FALSE(vec1 != vec1);
	EXPECT_TRUE(vec1 != vec2);
	EXPECT_TRUE(vec2 != vec);
	EXPECT_TRUE(vec2 != vec1);
	EXPECT_FALSE(vec2 != vec2);

	cVector3 vec3(4.0f, 3.0f, 7.0f);
	EXPECT_FALSE(vec1 != vec3);
	EXPECT_FALSE(vec3 != vec1);

	cVector3 vec4(vec2);
	EXPECT_FALSE(vec2 != vec4);
	EXPECT_FALSE(vec4 != vec2);
}
//
TEST_F(Vector3Test, OperatorIndex)
{
	EXPECT_FLOAT_EQ(0.0f, vec[0]);
	EXPECT_FLOAT_EQ(0.0f, vec[1]);
	EXPECT_FLOAT_EQ(0.0f, vec[2]);

	EXPECT_FLOAT_EQ(4.0f, vec1[0]);
	EXPECT_FLOAT_EQ(3.0f, vec1[1]);
	EXPECT_FLOAT_EQ(7.0f, vec1[2]);

	EXPECT_FLOAT_EQ(-4.0f, vec2[0]);
	EXPECT_FLOAT_EQ(5.0f, vec2[1]);
	EXPECT_FLOAT_EQ(-4.0f, vec2[2]); 
}

TEST_F(Vector3Test, DISABLED_DeathTestOperatorIndex)
{
	EXPECT_EXIT(vec[-1], ::testing::ExitedWithCode(0), "Assertion failed: index >= 0 && index < 3");
	EXPECT_EXIT(vec[3], ::testing::ExitedWithCode(0), "Assertion failed: index >= 0 && index < 3");
}

TEST_F(Vector3Test, Lerp)
{
	cVector3 vec3 = cVector3::Lerp(vec, vec1, 0.0f);
	EXPECT_NEAR(vec.x, vec3.x, 0.1f);
	EXPECT_NEAR(vec.y, vec3.y, 0.1f);
	EXPECT_NEAR(vec.z, vec3.z, 0.1f);

	vec3 = cVector3::Lerp(vec, vec1, 0.25f);
	EXPECT_NEAR(1.0f, vec3.x, 0.1f);
	EXPECT_NEAR(0.75f, vec3.y, 0.1f);
	EXPECT_NEAR(1.75f, vec3.z, 0.1f);

	vec3 = cVector3::Lerp(vec, vec1, 0.5f);
	EXPECT_NEAR(2.0f, vec3.x, 0.1f);
	EXPECT_NEAR(1.5f, vec3.y, 0.1f);
	EXPECT_NEAR(3.5f, vec3.z, 0.1f);

	vec3 = cVector3::Lerp(vec, vec1, 1.0f);
	EXPECT_NEAR(vec1.x, vec3.x, 0.1f);
	EXPECT_NEAR(vec1.y, vec3.y, 0.1f);
	EXPECT_NEAR(vec1.z, vec3.z, 0.1f);

	vec3 = cVector3::Lerp(vec1, vec2, 0.0f);
	EXPECT_NEAR(vec1.x, vec3.x, 0.1f);
	EXPECT_NEAR(vec1.y, vec3.y, 0.1f);
	EXPECT_NEAR(vec1.z, vec3.z, 0.1f);

	vec3 = cVector3::Lerp(vec1, vec2, 0.25f);
	EXPECT_NEAR(2.0f, vec3.x, 0.1f);
	EXPECT_NEAR(3.5f, vec3.y, 0.1f);
	EXPECT_NEAR(4.25f, vec3.z, 0.1f);

	vec3 = cVector3::Lerp(vec1, vec2, 0.5f);
	EXPECT_NEAR(0.0f, vec3.x, 0.1f);
	EXPECT_NEAR(4.0f, vec3.y, 0.1f);
	EXPECT_NEAR(1.5f, vec3.z, 0.1f);

	vec3 = cVector3::Lerp(vec1, vec2, 1.0f);
	EXPECT_NEAR(vec2.x, vec3.x, 0.1f);
	EXPECT_NEAR(vec2.y, vec3.y, 0.1f);
	EXPECT_NEAR(vec2.z, vec3.z, 0.1f);

	vec3 = cVector3::Lerp(vec1, vec2, -0.01f);
	EXPECT_NEAR(vec1.x, vec3.x, 0.1f);
	EXPECT_NEAR(vec1.y, vec3.y, 0.1f);
	EXPECT_NEAR(vec1.z, vec3.z, 0.1f);

	vec3 = cVector3::Lerp(vec1, vec2, 1.01f);
	EXPECT_NEAR(vec2.x, vec3.x, 0.1f);
	EXPECT_NEAR(vec2.y, vec3.y, 0.1f);
	EXPECT_NEAR(vec2.z, vec3.z, 0.1f);
}
//
TEST_F(Vector3Test, operatorMultiplyScalarVector)
{
	cVector3 testVec = vec * 10.0f;
	EXPECT_FLOAT_EQ(0.0f, testVec.x);
	EXPECT_FLOAT_EQ(0.0f, testVec.y);
	EXPECT_FLOAT_EQ(0.0f, testVec.z);

	testVec = vec * -10.0f;
	EXPECT_FLOAT_EQ(0.0f, testVec.x);
	EXPECT_FLOAT_EQ(0.0f, testVec.y);
	EXPECT_FLOAT_EQ(0.0f, testVec.z);

	testVec = vec1 * 10.0f;
	EXPECT_FLOAT_EQ(40.0f, testVec.x);
	EXPECT_FLOAT_EQ(30.0f, testVec.y);
	EXPECT_FLOAT_EQ(70.0f, testVec.z);

	testVec = vec1 * -10.0f;
	EXPECT_FLOAT_EQ(-40.0f, testVec.x);
	EXPECT_FLOAT_EQ(-30.0f, testVec.y);
	EXPECT_FLOAT_EQ(-70.0f, testVec.z);

	testVec = vec2 * 10.0f;
	EXPECT_FLOAT_EQ(-40.0f, testVec.x);
	EXPECT_FLOAT_EQ(50.0f, testVec.y);
	EXPECT_FLOAT_EQ(-40.0f, testVec.z);

	testVec = vec2 * -10.0f;
	EXPECT_FLOAT_EQ(40.0f, testVec.x);
	EXPECT_FLOAT_EQ(-50.0f, testVec.y);
	EXPECT_FLOAT_EQ(40.0f, testVec.z);
}
//
TEST_F(Vector3Test, operatorMultiplyVectorScalar)
{
	cVector3 testVec = 10.0f * vec;
	EXPECT_FLOAT_EQ(0.0f, testVec.x);
	EXPECT_FLOAT_EQ(0.0f, testVec.y);
	EXPECT_FLOAT_EQ(0.0f, testVec.z);
	
	testVec = -10.0f * vec;
	EXPECT_FLOAT_EQ(0.0f, testVec.x);
	EXPECT_FLOAT_EQ(0.0f, testVec.y);
	EXPECT_FLOAT_EQ(0.0f, testVec.z);

	testVec = 10.0f * vec1;
	EXPECT_FLOAT_EQ(40.0f, testVec.x);
	EXPECT_FLOAT_EQ(30.0f, testVec.y);
	EXPECT_FLOAT_EQ(70.0f, testVec.z);

	testVec = -10.0f * vec1;
	EXPECT_FLOAT_EQ(-40.0f, testVec.x);
	EXPECT_FLOAT_EQ(-30.0f, testVec.y);
	EXPECT_FLOAT_EQ(-70.0f, testVec.z);

	testVec = 10.0f * vec2;
	EXPECT_FLOAT_EQ(-40.0f, testVec.x);
	EXPECT_FLOAT_EQ(50.0f, testVec.y);
	EXPECT_FLOAT_EQ(-40.0f, testVec.z);

	testVec = -10.0f * vec2;
	EXPECT_FLOAT_EQ(40.0f, testVec.x);
	EXPECT_FLOAT_EQ(-50.0f, testVec.y);
	EXPECT_FLOAT_EQ(40.0f, testVec.z);
}

TEST_F(Vector3Test, operatorDivideVectorScalar)
{
	cVector3 testVec = vec / 10.0f;
	EXPECT_FLOAT_EQ(0.0f, testVec.x);
	EXPECT_FLOAT_EQ(0.0f, testVec.y);
	EXPECT_FLOAT_EQ(0.0f, testVec.z);

	testVec = vec / -10.0f;
	EXPECT_FLOAT_EQ(0.0f, testVec.x);
	EXPECT_FLOAT_EQ(0.0f, testVec.y);
	EXPECT_FLOAT_EQ(0.0f, testVec.z);

	testVec = vec1 / 10.0f;
	EXPECT_FLOAT_EQ(0.4f, testVec.x);
	EXPECT_FLOAT_EQ(0.3f, testVec.y);
	EXPECT_FLOAT_EQ(0.7f, testVec.z);

	testVec = vec1 / -10.0f;
	EXPECT_FLOAT_EQ(-0.4f, testVec.x);
	EXPECT_FLOAT_EQ(-0.3f, testVec.y);
	EXPECT_FLOAT_EQ(-0.7f, testVec.z);

	testVec = vec2 / 10.0f;
	EXPECT_FLOAT_EQ(-0.4f, testVec.x);
	EXPECT_FLOAT_EQ(0.5f, testVec.y);
	EXPECT_FLOAT_EQ(-0.4f, testVec.z);

	testVec = vec2 / -10.0f;
	EXPECT_FLOAT_EQ(0.4f, testVec.x);
	EXPECT_FLOAT_EQ(-0.5f, testVec.y);
	EXPECT_FLOAT_EQ(0.4f, testVec.z);
}

TEST_F(Vector3Test, operatorMinus)
{
	cVector3 testVec = vec - vec1;
	EXPECT_FLOAT_EQ(-4.0f, testVec.x);
	EXPECT_FLOAT_EQ(-3.0f, testVec.y);
	EXPECT_FLOAT_EQ(-7.0f, testVec.z);

	testVec = vec - vec2;
	EXPECT_FLOAT_EQ(4.0f, testVec.x);
	EXPECT_FLOAT_EQ(-5.0f, testVec.y);
	EXPECT_FLOAT_EQ(4.0f, testVec.z);

	testVec = vec1 - vec;
	EXPECT_FLOAT_EQ(4.0f, testVec.x);
	EXPECT_FLOAT_EQ(3.0f, testVec.y);
	EXPECT_FLOAT_EQ(7.0f, testVec.z);

	testVec = vec1 - vec2;
	EXPECT_FLOAT_EQ(8.0f, testVec.x);
	EXPECT_FLOAT_EQ(-2.0f, testVec.y);
	EXPECT_FLOAT_EQ(11.0f, testVec.z);

	testVec = vec2 - vec;
	EXPECT_FLOAT_EQ(-4.0f, testVec.x);
	EXPECT_FLOAT_EQ(5.0f, testVec.y);
	EXPECT_FLOAT_EQ(-4.0f, testVec.z);

	testVec = vec2 - vec1;
	EXPECT_FLOAT_EQ(-8.0f, testVec.x);
	EXPECT_FLOAT_EQ(2.0f, testVec.y);
	EXPECT_FLOAT_EQ(-11.0f, testVec.z);
}

TEST_F(Vector3Test, operatorPlus)
{
	cVector3 testVec = vec + vec1;
	EXPECT_FLOAT_EQ(4.0f, testVec.x);
	EXPECT_FLOAT_EQ(3.0f, testVec.y);
	EXPECT_FLOAT_EQ(7.0f, testVec.z);

	testVec = vec + vec2;
	EXPECT_FLOAT_EQ(-4.0f, testVec.x);
	EXPECT_FLOAT_EQ(5.0f, testVec.y);
	EXPECT_FLOAT_EQ(-4.0f, testVec.z);

	testVec = vec1 + vec;
	EXPECT_FLOAT_EQ(4.0f, testVec.x);
	EXPECT_FLOAT_EQ(3.0f, testVec.y);
	EXPECT_FLOAT_EQ(7.0f, testVec.z);

	testVec = vec1 + vec2;
	EXPECT_FLOAT_EQ(0.0f, testVec.x);
	EXPECT_FLOAT_EQ(8.0f, testVec.y);
	EXPECT_FLOAT_EQ(3.0f, testVec.z);

	testVec = vec2 + vec;
	EXPECT_FLOAT_EQ(-4.0f, testVec.x);
	EXPECT_FLOAT_EQ(5.0f, testVec.y);
	EXPECT_FLOAT_EQ(-4.0f, testVec.z);

	testVec = vec2 + vec1;
	EXPECT_FLOAT_EQ(0.0f, testVec.x);
	EXPECT_FLOAT_EQ(8.0f, testVec.y);
	EXPECT_FLOAT_EQ(3.0f, testVec.z);

}

TEST_F(Vector3Test, operatorMultiplyVectorVector)
{
	cVector3 testVec = vec * vec1;
	EXPECT_FLOAT_EQ(0.0f, testVec.x);
	EXPECT_FLOAT_EQ(0.0f, testVec.y);
	EXPECT_FLOAT_EQ(0.0f, testVec.z);

	testVec = vec * vec2;
	EXPECT_FLOAT_EQ(0.0f, testVec.x);
	EXPECT_FLOAT_EQ(0.0f, testVec.y);
	EXPECT_FLOAT_EQ(0.0f, testVec.z);

	testVec = vec1 * vec;
	EXPECT_FLOAT_EQ(0.0f, testVec.x);
	EXPECT_FLOAT_EQ(0.0f, testVec.y);
	EXPECT_FLOAT_EQ(0.0f, testVec.z);

	testVec = vec1 * vec2;
	EXPECT_FLOAT_EQ(-16.0f, testVec.x);
	EXPECT_FLOAT_EQ(15.0f, testVec.y);
	EXPECT_FLOAT_EQ(-28.0f, testVec.z);

	testVec = vec2 * vec;
	EXPECT_FLOAT_EQ(0.0f, testVec.x);
	EXPECT_FLOAT_EQ(0.0f, testVec.y);
	EXPECT_FLOAT_EQ(0.0f, testVec.z);

	testVec = vec2 * vec1;
	EXPECT_FLOAT_EQ(-16.0f, testVec.x);
	EXPECT_FLOAT_EQ(15.0f, testVec.y);
	EXPECT_FLOAT_EQ(-28.0f, testVec.z);
}
