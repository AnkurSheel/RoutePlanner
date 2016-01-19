#include "stdafx.h"

class cNonCopyableChild
: public Base::cNonCopyable
{

};

class cNonCopyableTest 
: public ::testing::Test
{
protected:

	void SetUp()
	{
	}

	void TearDown()
	{
	}
};

TEST_F(cNonCopyableTest, ShouldNotCompile)
{
	cNonCopyableChild c;
	//cNonCopyableChild c1(c);
	//cNonCopyableChild c2 = c;
}
