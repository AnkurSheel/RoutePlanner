#include "stdafx.h"
#include "HashedString.h"

using namespace Base;

class HashedStringTest : public ::testing::Test
{
protected:

	void SetUp()
	{
	}

	void TearDown()
	{
	}
};

TEST_F(HashedStringTest, Constructors)
{
  cHashedString testString("Wikipedia");
  EXPECT_EQ(300286872, testString.GetHash());

  cHashedString testString1(testString);
  EXPECT_EQ(300286872, testString1.GetHash());
}

TEST_F(HashedStringTest, CalculateChecksum)
{
  unsigned long hash = cHashedString::CalculateChecksum("Wikipedia");
  EXPECT_EQ(300286872, hash);
}

TEST_F(HashedStringTest, Equal)
{
  cHashedString test;
  cHashedString testString("Wikipedia");
  cHashedString testString1("Wikipedia");
  cHashedString testString2(testString);
  cHashedString testString3("wikipedia");

  EXPECT_FALSE(test== testString1);
  EXPECT_TRUE(testString == testString1);
  EXPECT_TRUE(testString == testString2);
  EXPECT_TRUE(testString1 == testString1);
  EXPECT_FALSE(testString == testString3);
}
