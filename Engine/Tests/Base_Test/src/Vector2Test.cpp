#include "stdafx.h"
#include "Vector2.h"

using namespace Base;

class Vector2Test : public ::testing::Test
{
protected:
	cVector2 vec;
	cVector2 vec1;
	cVector2 vec2;

	void SetUp()
	{
		vec1 = cVector2(4.f, 3.f);
		vec2 = cVector2(-4.f, 3.f);
	}

	void TearDown()
	{
	}
};

TEST_F(Vector2Test, Constructors)
{
	EXPECT_FLOAT_EQ(0.0f, vec.x);
	EXPECT_FLOAT_EQ(0.0f, vec.y);

	EXPECT_FLOAT_EQ(4.0f, vec1.x);
	EXPECT_FLOAT_EQ(3.0f, vec1.y);

	EXPECT_FLOAT_EQ(-4.0f, vec2.x);
	EXPECT_FLOAT_EQ(3.0f, vec2.y);

	float arr[2] = {2, 3};
	cVector2 vec3(arr);
	EXPECT_FLOAT_EQ(2.0f, vec3.v[0]);
	EXPECT_FLOAT_EQ(3.0f, vec3.v[1]);
}

TEST_F(Vector2Test, isZero)
{
	EXPECT_TRUE(vec.IsZero());
	EXPECT_FALSE(vec1.IsZero());
	EXPECT_FALSE(vec2.IsZero());
}

TEST_F(Vector2Test, Length)
{
	EXPECT_FLOAT_EQ(0.0f, vec.Length());
	EXPECT_FLOAT_EQ(5.0f, vec1.Length());
	EXPECT_FLOAT_EQ(5.0f, vec2.Length());
}

TEST_F(Vector2Test, LengthSquared)
{
	EXPECT_FLOAT_EQ(0.0f, vec.LengthSquared());
	EXPECT_FLOAT_EQ(25.0f, vec1.LengthSquared());
	EXPECT_FLOAT_EQ(25.0f, vec2.LengthSquared());
}

TEST_F(Vector2Test, Normalize)
{
	vec.Normalize();
	EXPECT_FLOAT_EQ(0.0f, vec.x);
	EXPECT_FLOAT_EQ(0.0f, vec.y);

	vec1.Normalize();
	EXPECT_FLOAT_EQ(0.8f, vec1.x);
	EXPECT_FLOAT_EQ(0.6f, vec1.y);

	vec2.Normalize();
	EXPECT_FLOAT_EQ(-0.8f, vec2.x);
	EXPECT_FLOAT_EQ(0.6f, vec2.y);
}

TEST_F(Vector2Test, PerpendicularAboutXAxis)
{
	cVector2 perp = vec.PerpendicularAboutXAxis();
	EXPECT_FLOAT_EQ(0.0f, perp.x);
	EXPECT_FLOAT_EQ(0.0f, perp.y);

	perp = vec1.PerpendicularAboutXAxis();
	EXPECT_FLOAT_EQ(3.0f, perp.x);
	EXPECT_FLOAT_EQ(-4.0f, perp.y);

	perp = vec2.PerpendicularAboutXAxis();
	EXPECT_FLOAT_EQ(3.0f, perp.x);
	EXPECT_FLOAT_EQ(4.0f, perp.y);
}

TEST_F(Vector2Test, PerpendicularAboutYAxis)
{
	cVector2 perp = vec.PerpendicularAboutYAxis();
	EXPECT_FLOAT_EQ(0.0f, perp.x);
	EXPECT_FLOAT_EQ(0.0f, perp.y);

	perp = vec1.PerpendicularAboutYAxis();
	EXPECT_FLOAT_EQ(-3.0f, perp.x);
	EXPECT_FLOAT_EQ(4.0f, perp.y);

	perp = vec2.PerpendicularAboutYAxis();
	EXPECT_FLOAT_EQ(-3.0f, perp.x);
	EXPECT_FLOAT_EQ(-4.0f, perp.y);
}

TEST_F(Vector2Test, Dot)
{
	EXPECT_FLOAT_EQ(0.0f, vec.Dot(vec1));
	EXPECT_FLOAT_EQ(0.0f, vec.Dot(vec2));
	EXPECT_FLOAT_EQ(0.0f, vec1.Dot(vec));
	EXPECT_FLOAT_EQ(25.0f, vec1.Dot(vec1));
	EXPECT_FLOAT_EQ(-7.0f, vec1.Dot(vec2));
	EXPECT_FLOAT_EQ(0.0f, vec2.Dot(vec));
	EXPECT_FLOAT_EQ(-7.0f, vec2.Dot(vec1));
	EXPECT_FLOAT_EQ(25.0f, vec2.Dot(vec2));
}

TEST_F(Vector2Test, Distance)
{
	EXPECT_FLOAT_EQ(5.0f, vec.Distance(vec1));
	EXPECT_FLOAT_EQ(5.0f, vec.Distance(vec2));
	EXPECT_FLOAT_EQ(5.0f, vec1.Distance(vec));
	EXPECT_FLOAT_EQ(8.0f, vec1.Distance(vec2));
	EXPECT_FLOAT_EQ(5.0f, vec2.Distance(vec));
	EXPECT_FLOAT_EQ(8.0f, vec2.Distance(vec1));
}

TEST_F(Vector2Test, DistanceSquared)
{
	EXPECT_FLOAT_EQ(25.0f, vec.DistanceSquared(vec1));
	EXPECT_FLOAT_EQ(25.0f, vec.DistanceSquared(vec2));
	EXPECT_FLOAT_EQ(25.0f, vec1.DistanceSquared(vec));
	EXPECT_FLOAT_EQ(64.0f, vec1.DistanceSquared(vec2));
	EXPECT_FLOAT_EQ(25.0f, vec2.DistanceSquared(vec));
	EXPECT_FLOAT_EQ(64.0f, vec2.DistanceSquared(vec1));
}

TEST_F(Vector2Test, Reflect)
{
	cVector2 axis(1.0f, 0.0f);

	vec.Reflect(axis);
	EXPECT_FLOAT_EQ(0.0f, vec.x);
	EXPECT_FLOAT_EQ(0.0f, vec.y);

	vec1.Reflect(axis);
	EXPECT_FLOAT_EQ(-4.0f, vec1.x);
	EXPECT_FLOAT_EQ(3.0f, vec1.y);

	vec2.Reflect(axis);
	EXPECT_FLOAT_EQ(4.0f, vec2.x);
	EXPECT_FLOAT_EQ(3.0f, vec2.y);

	axis = cVector2(1.0f, 1.0f);

	vec.Reflect(axis);
	EXPECT_FLOAT_EQ(0.0f, vec.x);
	EXPECT_FLOAT_EQ(0.0f, vec.y);

	vec1.Reflect(axis);
	EXPECT_FLOAT_EQ(-3.0f, vec1.x);
	EXPECT_FLOAT_EQ(4.0f, vec1.y);

	vec2.Reflect(axis);
	EXPECT_FLOAT_EQ(-3.0f, vec2.x);
	EXPECT_FLOAT_EQ(-4.0f, vec2.y);
}


TEST_F(Vector2Test, GetReverse)
{
	cVector2 reverse = vec.GetReverse();
	EXPECT_FLOAT_EQ(0.0f, reverse.x);
	EXPECT_FLOAT_EQ(0.0f, reverse.y);

	reverse = vec1.GetReverse();
	EXPECT_FLOAT_EQ(-4.0f, reverse.x);
	EXPECT_FLOAT_EQ(-3.0f, reverse.y);

	reverse = vec2.GetReverse();
	EXPECT_FLOAT_EQ(4.0f, reverse.x);
	EXPECT_FLOAT_EQ(-3.0f, reverse.y);
}

TEST_F(Vector2Test, AbsTo)
{
	vec.AbsTo();
	EXPECT_FLOAT_EQ(0.0f, vec.x);
	EXPECT_FLOAT_EQ(0.0f, vec.y);

	vec1.AbsTo();
	EXPECT_FLOAT_EQ(4.0f, vec1.x);
	EXPECT_FLOAT_EQ(3.0f, vec1.y);

	vec2.AbsTo();
	EXPECT_FLOAT_EQ(4.0f, vec2.x);
	EXPECT_FLOAT_EQ(3.0f, vec2.y);
}

TEST_F(Vector2Test, MajorAxis)
{
	cVector2 majorAxis = vec.MajorAxis();
	EXPECT_FLOAT_EQ(0.0f, majorAxis.x);
	EXPECT_FLOAT_EQ(0.0f, majorAxis.y);

	majorAxis = vec1.MajorAxis();
	EXPECT_FLOAT_EQ(1.0f, majorAxis.x);
	EXPECT_FLOAT_EQ(0.0f, majorAxis.y);

	majorAxis = vec2.MajorAxis();
	EXPECT_FLOAT_EQ(-1.0f, majorAxis.x);
	EXPECT_FLOAT_EQ(0.0f, majorAxis.y);

	cVector2 vec3(3.0f, 4.0f);
	majorAxis = vec3.MajorAxis();
	EXPECT_FLOAT_EQ(0.0f, majorAxis.x);
	EXPECT_FLOAT_EQ(1.0f, majorAxis.y);

	cVector2 vec4(3.0f, -4.0f);
	majorAxis = vec4.MajorAxis();
	EXPECT_FLOAT_EQ(0.0f, majorAxis.x);
	EXPECT_FLOAT_EQ(-1.0f, majorAxis.y);
}

TEST_F(Vector2Test, MinorAxis)
{
	cVector2 minorAxis= vec.MinorAxis();
	EXPECT_FLOAT_EQ(0.0f, minorAxis.x);
	EXPECT_FLOAT_EQ(0.0f, minorAxis.y);

	minorAxis = vec1.MinorAxis();
	EXPECT_FLOAT_EQ(0.0f, minorAxis.x);
	EXPECT_FLOAT_EQ(1.0f, minorAxis.y);

	minorAxis = vec2.MinorAxis();
	EXPECT_FLOAT_EQ(0.0f, minorAxis.x);
	EXPECT_FLOAT_EQ(1.0f, minorAxis.y);

	cVector2 vec3(3.0f, 4.0f);
	minorAxis = vec3.MinorAxis();
	EXPECT_FLOAT_EQ(1.0f, minorAxis.x);
	EXPECT_FLOAT_EQ(0.0f, minorAxis.y);

	cVector2 vec4(3.0f, -4.0f);
	minorAxis = vec4.MinorAxis();
	EXPECT_FLOAT_EQ(1.0f, minorAxis.x);
	EXPECT_FLOAT_EQ(0.0f, minorAxis.y);
}

TEST_F(Vector2Test, NegTo)
{
	vec.NegTo();
	EXPECT_FLOAT_EQ(0.0f, vec.x);
	EXPECT_FLOAT_EQ(0.0f, vec.y);

	vec1.NegTo();
	EXPECT_FLOAT_EQ(-4.0f, vec1.x);
	EXPECT_FLOAT_EQ(-3.0f, vec1.y);

	vec2.NegTo();
	EXPECT_FLOAT_EQ(4.0f, vec2.x);
	EXPECT_FLOAT_EQ(-3.0f, vec2.y);
}

TEST_F(Vector2Test, operatorPlusEqual)
{
	cVector2 testVec = vec;
	testVec += vec1;
	EXPECT_FLOAT_EQ(4.0f, testVec.x);
	EXPECT_FLOAT_EQ(3.0f, testVec.y);

	testVec = vec;
	testVec += vec2;
	EXPECT_FLOAT_EQ(-4.0f, testVec.x);
	EXPECT_FLOAT_EQ(3.0f, testVec.y);

	testVec = vec1;
	testVec += vec;
	EXPECT_FLOAT_EQ(4.0f, testVec.x);
	EXPECT_FLOAT_EQ(3.0f, testVec.y);

	testVec = vec1;
	testVec += vec2;
	EXPECT_FLOAT_EQ(0.0f, testVec.x);
	EXPECT_FLOAT_EQ(6.0f, testVec.y);

	testVec = vec2;
	testVec += vec;
	EXPECT_FLOAT_EQ(-4.0f, testVec.x);
	EXPECT_FLOAT_EQ(3.0f, testVec.y);

	testVec = vec2;
	testVec += vec1;
	EXPECT_FLOAT_EQ(0.0f, testVec.x);
	EXPECT_FLOAT_EQ(6.0f, testVec.y);
}

TEST_F(Vector2Test, operatorMinusEqual)
{
	cVector2 testVec = vec;
	testVec -= vec1;
	EXPECT_FLOAT_EQ(-4.0f, testVec.x);
	EXPECT_FLOAT_EQ(-3.0f, testVec.y);

	testVec = vec;
	testVec -= vec2;
	EXPECT_FLOAT_EQ(4.0f, testVec.x);
	EXPECT_FLOAT_EQ(-3.0f, testVec.y);

	testVec = vec1;
	testVec -= vec;
	EXPECT_FLOAT_EQ(4.0f, testVec.x);
	EXPECT_FLOAT_EQ(3.0f, testVec.y);

	testVec = vec1;
	testVec -= vec2;
	EXPECT_FLOAT_EQ(8.0f, testVec.x);
	EXPECT_FLOAT_EQ(0.0f, testVec.y);

	testVec = vec2;
	testVec -= vec;
	EXPECT_FLOAT_EQ(-4.0f, testVec.x);
	EXPECT_FLOAT_EQ(3.0f, testVec.y);

	testVec = vec2;
	testVec -= vec1;
	EXPECT_FLOAT_EQ(-8.0f, testVec.x);
	EXPECT_FLOAT_EQ(0.0f, testVec.y);
}

TEST_F(Vector2Test, operatorMultiplyEqualVector)
{
	cVector2 testVec = vec;
	testVec *= vec1;
	EXPECT_FLOAT_EQ(0.0f, testVec.x);
	EXPECT_FLOAT_EQ(0.0f, testVec.y);

	testVec = vec;
	testVec *= vec2;
	EXPECT_FLOAT_EQ(0.0f, testVec.x);
	EXPECT_FLOAT_EQ(0.0f, testVec.y);

	testVec = vec1;
	testVec *= vec;
	EXPECT_FLOAT_EQ(0.0f, testVec.x);
	EXPECT_FLOAT_EQ(0.0f, testVec.y);

	testVec = vec1;
	testVec *= vec2;
	EXPECT_FLOAT_EQ(-16.0f, testVec.x);
	EXPECT_FLOAT_EQ(9.0f, testVec.y);

	testVec = vec2;
	testVec *= vec;
	EXPECT_FLOAT_EQ(0.0f, testVec.x);
	EXPECT_FLOAT_EQ(0.0f, testVec.y);

	testVec = vec2;
	testVec *= vec1;
	EXPECT_FLOAT_EQ(-16.0f, testVec.x);
	EXPECT_FLOAT_EQ(9.0f, testVec.y);
}

TEST_F(Vector2Test, operatorMultiplyEqualScalar)
{
	cVector2 testVec = vec;
	testVec *= 10.0f;
	EXPECT_FLOAT_EQ(0.0f, testVec.x);
	EXPECT_FLOAT_EQ(0.0f, testVec.y);

	testVec = vec;
	testVec *= -10.0f;
	EXPECT_FLOAT_EQ(0.0f, testVec.x);
	EXPECT_FLOAT_EQ(0.0f, testVec.y);

	testVec = vec1;
	testVec *= 10.0f;
	EXPECT_FLOAT_EQ(40.0f, testVec.x);
	EXPECT_FLOAT_EQ(30.0f, testVec.y);

	testVec = vec1;
	testVec *= -10.0f;
	EXPECT_FLOAT_EQ(-40.0f, testVec.x);
	EXPECT_FLOAT_EQ(-30.0f, testVec.y);

	testVec = vec2;
	testVec *= 10.0f;
	EXPECT_FLOAT_EQ(-40.0f, testVec.x);
	EXPECT_FLOAT_EQ(30.0f, testVec.y);

	testVec = vec2;
	testVec *= -10.0f;
	EXPECT_FLOAT_EQ(40.0f, testVec.x);
	EXPECT_FLOAT_EQ(-30.0f, testVec.y);
}

TEST_F(Vector2Test, operatorDivideEqualScalar)
{
	cVector2 testVec = vec;
	testVec /= 10.0f;
	EXPECT_FLOAT_EQ(0.0f, testVec.x);
	EXPECT_FLOAT_EQ(0.0f, testVec.y);

	testVec = vec;
	testVec /= -10.0f;
	EXPECT_FLOAT_EQ(0.0f, testVec.x);
	EXPECT_FLOAT_EQ(0.0f, testVec.y);

	testVec = vec1;
	testVec /= 10.0f;
	EXPECT_FLOAT_EQ(0.4f, testVec.x);
	EXPECT_FLOAT_EQ(0.3f, testVec.y);

	testVec = vec1;
	testVec /= -10.0f;
	EXPECT_FLOAT_EQ(-0.4f, testVec.x);
	EXPECT_FLOAT_EQ(-0.3f, testVec.y);

	testVec = vec2;
	testVec /= 10.0f;
	EXPECT_FLOAT_EQ(-0.4f, testVec.x);
	EXPECT_FLOAT_EQ(0.3f, testVec.y);

	testVec = vec2;
	testVec /= -10.0f;
	EXPECT_FLOAT_EQ(0.4f, testVec.x);
	EXPECT_FLOAT_EQ(-0.3f, testVec.y);
}

TEST_F(Vector2Test, OperatorEqual)
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

	cVector2 vec3(4.0f, 3.0f);
	EXPECT_TRUE(vec1 == vec3);
	EXPECT_TRUE(vec3 == vec1);

	cVector2 vec4(vec2);
	EXPECT_TRUE(vec2 == vec4);
	EXPECT_TRUE(vec4 == vec2);
}

TEST_F(Vector2Test, OperatorNotEqual)
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

	cVector2 vec3(4.0f, 3.0f);
	EXPECT_FALSE(vec1 != vec3);
	EXPECT_FALSE(vec3 != vec1);

	cVector2 vec4(vec2);
	EXPECT_FALSE(vec2 != vec4);
	EXPECT_FALSE(vec4 != vec2);
}

TEST_F(Vector2Test, OperatorIndex)
{
	EXPECT_FLOAT_EQ(0.0f, vec[0]);
	EXPECT_FLOAT_EQ(0.0f, vec[1]);

	EXPECT_FLOAT_EQ(4.0f, vec1[0]);
	EXPECT_FLOAT_EQ(3.0f, vec1[1]);

	EXPECT_FLOAT_EQ(-4.0f, vec2[0]);
	EXPECT_FLOAT_EQ(3.0f, vec2[1]);
}

TEST_F(Vector2Test, DISABLED_DeathTestOperatorIndex)
{
	EXPECT_EXIT(vec[-1], ::testing::ExitedWithCode(0), "Assertion failed: index >= 0 && index < 2");
	EXPECT_EXIT(vec[2], ::testing::ExitedWithCode(0), "Assertion failed: index >= 0 && index < 2");
}

TEST_F(Vector2Test, MakeVectorFromAngle)
{
	vec = cVector2::MakeVectorFromAngle(0);
	EXPECT_NEAR(1.0f, vec.x, 0.1f);
	EXPECT_NEAR(0.0f, vec.y, 0.1f);

	vec = cVector2::MakeVectorFromAngle(45);
	EXPECT_NEAR(0.7f, vec.x, 0.1f);
	EXPECT_NEAR(0.7f, vec.y, 0.1f);

	vec = cVector2::MakeVectorFromAngle(90);
	EXPECT_NEAR(0.0f, vec.x, 0.1f);
	EXPECT_NEAR(1.0f, vec.y, 0.1f);

	vec = cVector2::MakeVectorFromAngle(225);
	EXPECT_NEAR(-0.7f, vec.x, 0.1f);
	EXPECT_NEAR(-0.7f, vec.y, 0.1f);
}

TEST_F(Vector2Test, Lerp)
{
	cVector2 vec3 = cVector2::Lerp(vec, vec1, 0.0f);
	EXPECT_NEAR(vec.x, vec3.x, 0.1f);
	EXPECT_NEAR(vec.y, vec3.y, 0.1f);

	vec3 = cVector2::Lerp(vec, vec1, 0.25f);
	EXPECT_NEAR(1.0f, vec3.x, 0.1f);
	EXPECT_NEAR(0.75, vec3.y, 0.1f);

	vec3 = cVector2::Lerp(vec, vec1, 0.5f);
	EXPECT_NEAR(2.0f, vec3.x, 0.1f);
	EXPECT_NEAR(1.5f, vec3.y, 0.1f);

	vec3 = cVector2::Lerp(vec, vec1, 1.0f);
	EXPECT_NEAR(vec1.x, vec3.x, 0.1f);
	EXPECT_NEAR(vec1.y, vec3.y, 0.1f);

	vec3 = cVector2::Lerp(vec1, vec2, 0.0f);
	EXPECT_NEAR(vec1.x, vec3.x, 0.1f);
	EXPECT_NEAR(vec1.y, vec3.y, 0.1f);

	vec3 = cVector2::Lerp(vec1, vec2, 0.25f);
	EXPECT_NEAR(2.0f, vec3.x, 0.1f);
	EXPECT_NEAR(3.0f, vec3.y, 0.1f);

	vec3 = cVector2::Lerp(vec1, vec2, 0.5f);
	EXPECT_NEAR(0.0f, vec3.x, 0.1f);
	EXPECT_NEAR(3.0f, vec3.y, 0.1f);

	vec3 = cVector2::Lerp(vec1, vec2, 1.0f);
	EXPECT_NEAR(vec2.x, vec3.x, 0.1f);
	EXPECT_NEAR(vec2.y, vec3.y, 0.1f);

	vec3 = cVector2::Lerp(vec1, vec2, -0.01f);
	EXPECT_NEAR(vec1.x, vec3.x, 0.1f);
	EXPECT_NEAR(vec1.y, vec3.y, 0.1f);

	vec3 = cVector2::Lerp(vec1, vec2, 1.01f);
	EXPECT_NEAR(vec2.x, vec3.x, 0.1f);
	EXPECT_NEAR(vec2.y, vec3.y, 0.1f);
}


TEST_F(Vector2Test, operatorMultiplyScalarVector)
{
	cVector2 testVec = vec * 10.0f;
	EXPECT_FLOAT_EQ(0.0f, testVec.x);
	EXPECT_FLOAT_EQ(0.0f, testVec.y);

	testVec = vec * -10.0f;
	EXPECT_FLOAT_EQ(0.0f, testVec.x);
	EXPECT_FLOAT_EQ(0.0f, testVec.y);

	testVec = vec1 * 10.0f;
	EXPECT_FLOAT_EQ(40.0f, testVec.x);
	EXPECT_FLOAT_EQ(30.0f, testVec.y);

	testVec = vec1 * -10.0f;
	EXPECT_FLOAT_EQ(-40.0f, testVec.x);
	EXPECT_FLOAT_EQ(-30.0f, testVec.y);

	testVec = vec2 * 10.0f;
	EXPECT_FLOAT_EQ(-40.0f, testVec.x);
	EXPECT_FLOAT_EQ(30.0f, testVec.y);

	testVec = vec2 * -10.0f;
	EXPECT_FLOAT_EQ(40.0f, testVec.x);
	EXPECT_FLOAT_EQ(-30.0f, testVec.y);
}

TEST_F(Vector2Test, operatorMultiplyVectorScalar)
{
	cVector2 testVec = 10.0f * vec;
	EXPECT_FLOAT_EQ(0.0f, testVec.x);
	EXPECT_FLOAT_EQ(0.0f, testVec.y);

	testVec = -10.0f * vec;
	EXPECT_FLOAT_EQ(0.0f, testVec.x);
	EXPECT_FLOAT_EQ(0.0f, testVec.y);

	testVec = 10.0f * vec1;
	EXPECT_FLOAT_EQ(40.0f, testVec.x);
	EXPECT_FLOAT_EQ(30.0f, testVec.y);

	testVec = -10.0f * vec1;
	EXPECT_FLOAT_EQ(-40.0f, testVec.x);
	EXPECT_FLOAT_EQ(-30.0f, testVec.y);

	testVec = 10.0f * vec2;
	EXPECT_FLOAT_EQ(-40.0f, testVec.x);
	EXPECT_FLOAT_EQ(30.0f, testVec.y);

	testVec = -10.0f * vec2;
	EXPECT_FLOAT_EQ(40.0f, testVec.x);
	EXPECT_FLOAT_EQ(-30.0f, testVec.y);
}

TEST_F(Vector2Test, operatorDivideVectorScalar)
{
	cVector2 testVec = vec / 10.0f;
	EXPECT_FLOAT_EQ(0.0f, testVec.x);
	EXPECT_FLOAT_EQ(0.0f, testVec.y);

	testVec = vec / -10.0f;
	EXPECT_FLOAT_EQ(0.0f, testVec.x);
	EXPECT_FLOAT_EQ(0.0f, testVec.y);

	testVec = vec1 / 10.0f;
	EXPECT_FLOAT_EQ(0.4f, testVec.x);
	EXPECT_FLOAT_EQ(0.3f, testVec.y);

	testVec = vec1 / -10.0f;
	EXPECT_FLOAT_EQ(-0.4f, testVec.x);
	EXPECT_FLOAT_EQ(-0.3f, testVec.y);

	testVec = vec2 / 10.0f;
	EXPECT_FLOAT_EQ(-0.4f, testVec.x);
	EXPECT_FLOAT_EQ(0.3f, testVec.y);

	testVec = vec2 / -10.0f;
	EXPECT_FLOAT_EQ(0.4f, testVec.x);
	EXPECT_FLOAT_EQ(-0.3f, testVec.y);
}

TEST_F(Vector2Test, operatorMinus)
{
	cVector2 testVec = vec - vec1;
	EXPECT_FLOAT_EQ(-4.0f, testVec.x);
	EXPECT_FLOAT_EQ(-3.0f, testVec.y);

	testVec = vec - vec2;
	EXPECT_FLOAT_EQ(4.0f, testVec.x);
	EXPECT_FLOAT_EQ(-3.0f, testVec.y);

	testVec = vec1 - vec;
	EXPECT_FLOAT_EQ(4.0f, testVec.x);
	EXPECT_FLOAT_EQ(3.0f, testVec.y);

	testVec = vec1 - vec2;
	EXPECT_FLOAT_EQ(8.0f, testVec.x);
	EXPECT_FLOAT_EQ(0.0f, testVec.y);

	testVec = vec2 - vec;
	EXPECT_FLOAT_EQ(-4.0f, testVec.x);
	EXPECT_FLOAT_EQ(3.0f, testVec.y);

	testVec = vec2 - vec1;
	EXPECT_FLOAT_EQ(-8.0f, testVec.x);
	EXPECT_FLOAT_EQ(0.0f, testVec.y);
}

TEST_F(Vector2Test, operatorPlus)
{
	cVector2 testVec = vec + vec1;
	EXPECT_FLOAT_EQ(4.0f, testVec.x);
	EXPECT_FLOAT_EQ(3.0f, testVec.y);

	testVec = vec + vec2;
	EXPECT_FLOAT_EQ(-4.0f, testVec.x);
	EXPECT_FLOAT_EQ(3.0f, testVec.y);

	testVec = vec1 + vec;
	EXPECT_FLOAT_EQ(4.0f, testVec.x);
	EXPECT_FLOAT_EQ(3.0f, testVec.y);

	testVec = vec1 + vec2;
	EXPECT_FLOAT_EQ(0.0f, testVec.x);
	EXPECT_FLOAT_EQ(6.0f, testVec.y);

	testVec = vec2 + vec;
	EXPECT_FLOAT_EQ(-4.0f, testVec.x);
	EXPECT_FLOAT_EQ(3.0f, testVec.y);

	testVec = vec2 + vec1;
	EXPECT_FLOAT_EQ(0.0f, testVec.x);
	EXPECT_FLOAT_EQ(6.0f, testVec.y);
}

TEST_F(Vector2Test, operatorMultiplyVectorVector)
{
	cVector2 testVec = vec * vec1;
	EXPECT_FLOAT_EQ(0.0f, testVec.x);
	EXPECT_FLOAT_EQ(0.0f, testVec.y);

	testVec = vec * vec2;
	EXPECT_FLOAT_EQ(0.0f, testVec.x);
	EXPECT_FLOAT_EQ(0.0f, testVec.y);

	testVec = vec1 * vec;
	EXPECT_FLOAT_EQ(0.0f, testVec.x);
	EXPECT_FLOAT_EQ(0.0f, testVec.y);

	testVec = vec1 * vec2;
	EXPECT_FLOAT_EQ(-16.0f, testVec.x);
	EXPECT_FLOAT_EQ(9.0f, testVec.y);

	testVec = vec2 * vec;
	EXPECT_FLOAT_EQ(0.0f, testVec.x);
	EXPECT_FLOAT_EQ(0.0f, testVec.y);

	testVec = vec2 * vec1;
	EXPECT_FLOAT_EQ(-16.0f, testVec.x);
	EXPECT_FLOAT_EQ(9.0f, testVec.y);
}