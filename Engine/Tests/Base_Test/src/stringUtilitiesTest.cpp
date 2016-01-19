#include "stdafx.h"
#include "myString.h"
#include "StringUtilities.h"
#include <vector>

using namespace Base;

class StringUtilitiesTest : public ::testing::Test
{
protected:

	void SetUp()
	{
	}

	void TearDown()
	{

	}
};

TEST_F(StringUtilitiesTest, MakeFormatted)
{
	cString s = cStringUtilities::MakeFormatted("abc %d %c", 5, 'a');
	EXPECT_STREQ("abc 5 a", s.GetData());

	cString s1 = cStringUtilities::MakeFormatted("abc");
	EXPECT_STREQ("abc", s1.GetData());

	cString s2 = cStringUtilities::MakeFormatted("");
	EXPECT_STREQ("", s2.GetData());
}

TEST_F(StringUtilitiesTest, GetInLowerCase)
{
	cString str = cStringUtilities::GetInLowerCase("Ankur IS the bEsT, #1 ISnt hE");
	EXPECT_STREQ("ankur is the best, #1 isnt he" , str.GetData());
}

TEST_F(StringUtilitiesTest, CalendarTimeToString)
{
	time_t  timev = 1410214900;
	cString str = cStringUtilities::CalendarTimeToString(timev);
	EXPECT_STREQ("Tue Sep 09 10:21:40 2014" , str.GetData());
}

TEST_F(StringUtilitiesTest, ConcatOperator)
{
	cString str1 ="Ankur";
	cString str2 = "is";

	cString str3 = str1 + str2;
	EXPECT_STREQ("Ankuris", str3.GetData());

	str3 = "Ankur1" + str2;
	EXPECT_STREQ("Ankur1is", str3.GetData());

	str3 = str1 + "123";
	EXPECT_STREQ("Ankur123", str3.GetData());
}