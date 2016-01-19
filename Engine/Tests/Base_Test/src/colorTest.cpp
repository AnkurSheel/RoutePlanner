#include "stdafx.h"
#include "Color.h"

using namespace Base;

class ColorTest : public ::testing::Test
{
	void SetUp()
	{
	}

	void TearDown()
	{
	}
};

TEST_F(ColorTest, Constructors)
{
	cColor color = cColor(0.5f, 0.5f, 0.5f, 0.5f);
	EXPECT_EQ(128, color.m_Red);
	EXPECT_EQ(128, color.m_Blue);
	EXPECT_EQ(128, color.m_Green);
	EXPECT_EQ(128, color.m_Alpha);
}

TEST_F(ColorTest, GetColorComponentsInFloat)
{
	float red, green, blue, alpha;

	cColor color = cColor::BLACK;
	color.GetColorComponentsInFloat(red, blue, green, alpha);
	EXPECT_NEAR(0, red, 0.1f);
	EXPECT_NEAR(0, blue, 0.1f);
	EXPECT_NEAR(0, green, 0.1f);
	EXPECT_NEAR(1, alpha, 0.1f);

	color = cColor::WHITE;
	color.GetColorComponentsInFloat(red, blue, green, alpha);
	EXPECT_NEAR(1, red, 0.1f);
	EXPECT_NEAR(1, blue, 0.1f);
	EXPECT_NEAR(1, green, 0.1f);
	EXPECT_NEAR(1, alpha, 0.1f);

	color = cColor(128, 128, 128, 128);
	color.GetColorComponentsInFloat(red, blue, green, alpha);
	EXPECT_NEAR(0.5f, red, 0.1f);
	EXPECT_NEAR(0.5f, blue, 0.1f);
	EXPECT_NEAR(0.5f, green, 0.1f);
	EXPECT_NEAR(0.5f, alpha, 0.1f);
}
