#include "stdafx.h"
#include "myString.h"
#include "Optional.h"
#include <vector>

using namespace Base;

static cString longString() { return "abcdefghijklmnopqrstuvwxyz0123456789"; }

class StringTest : public ::testing::Test
{
protected:
	cString str;
	cString str1;
	cString str2;

	void SetUp()
	{
		str1 = cString(" Ankur is the best the ");
		str2 = cString("Ankur");
	}

	void TearDown()
	{

	}
};

TEST_F(StringTest, Constructors)
{
	cString s;
	EXPECT_STREQ("", s.GetData());

	cString s1("abc");
	EXPECT_STREQ("abc", s1.GetData());

	cString s11(cString("abc"));
	EXPECT_STREQ("abc", s11.GetData());

	cString s2(longString().GetData());
	EXPECT_STREQ(longString().GetData(), s2.GetData());

	cString s22(longString());
	EXPECT_STREQ(longString().GetData(), s22.GetData());

	cString s3(std::string("abc"));
	EXPECT_STREQ("abc", s3.GetData());
}

TEST_F(StringTest, GetData)
{
	EXPECT_STREQ("", str.GetData());
	EXPECT_STREQ(" Ankur is the best the ", str1.GetData());
}

TEST_F(StringTest, IsEmpty)
{
	EXPECT_EQ(true, str.IsEmpty());
	EXPECT_EQ(false, str1.IsEmpty());
}

TEST_F(StringTest, GetLength)
{
	cString str3 = " is the best";
	cString str5 = longString();

	EXPECT_EQ(0, str.GetLength());
	EXPECT_EQ(23, str1.GetLength());
	EXPECT_EQ(12, str3.GetLength());
	EXPECT_EQ(36, str5.GetLength());
}

TEST_F(StringTest, GetSubString)
{
	EXPECT_STREQ("", str.GetSubString(-1, 0).GetData());
	EXPECT_STREQ("", str.GetSubString(0, 1).GetData());

	EXPECT_STREQ("", str1.GetSubString(0,36).GetData());
	EXPECT_STREQ(" Ankur", str1.GetSubString(0,5).GetData());
	EXPECT_STREQ(" An", str1.GetSubString(0,2).GetData());
	EXPECT_STREQ(" Ankur is the best the ", str1.GetSubString(0,str1.GetLength()).GetData());

	EXPECT_STREQ("the be", str1.GetSubString(10,15).GetData());
	EXPECT_STREQ(" the best the ", str1.GetSubString(9,str1.GetLength()).GetData());
}

TEST_F(StringTest, FindIndex)
{
	tOptional<int> val;
	val = str.FindIndex('a', 0);
	EXPECT_FALSE(val.IsValid());

	val = str1.FindIndex('e', 0);
	EXPECT_EQ(12, val.GetValue());
	val = str1.FindIndex('e', 13);
	EXPECT_EQ(15,val.GetValue());
	val = str1.FindIndex('e', 25);
	EXPECT_TRUE(val.IsInvalid());
	val = str1.FindIndex('q', 0);
	EXPECT_TRUE(val.IsInvalid());
}

TEST_F(StringTest, FindFirstOfAny)
{
	tOptional<int> val;
	val = str.FindFirstOfAny("a", 0);
	EXPECT_FALSE(val.IsValid());

	val = str1.FindFirstOfAny("teb", 0);
	EXPECT_EQ(10,val.GetValue());
	val = str1.FindFirstOfAny("bq", 11);
	EXPECT_EQ(14, val.GetValue());
	val = str1.FindFirstOfAny("lzq", 0);
	EXPECT_TRUE(val.IsInvalid());
}

TEST_F(StringTest, FindFirstNotOfAny)
{
	tOptional<int> val;
	val = str.FindFirstNotOfAny("a", 0);
	EXPECT_FALSE(val.IsValid());

	val = str1.FindFirstNotOfAny(" An", 0);
	EXPECT_EQ(3, val.GetValue());
	val = str1.FindFirstNotOfAny("be", 14);
	EXPECT_EQ(16, val.GetValue());
	val = str1.FindFirstNotOfAny("Ankur istheb", 0);
	EXPECT_TRUE(val.IsInvalid());
}

TEST_F(StringTest, FindLastOfAny)
{
	tOptional<int> val;
	val = str.FindLastOfAny("a", str.GetLength());
	EXPECT_FALSE(val.IsValid());

	val = str1.FindLastOfAny("teb", str1.GetLength());
	EXPECT_EQ(21, val.GetValue());
	val = str1.FindLastOfAny("At", 13);
	EXPECT_EQ(10, val.GetValue());
	val = str1.FindLastOfAny("lzq", str1.GetLength());
	EXPECT_TRUE(val.IsInvalid());
}

TEST_F(StringTest, FindLastNotOfAny)
{
	tOptional<int> val;
	val = str.FindLastNotOfAny("a", str.GetLength());
	EXPECT_FALSE(val.IsValid());

	val = str1.FindLastNotOfAny(" besth", str1.GetLength());
	EXPECT_EQ(7, val.GetValue());
	val = str1.FindLastNotOfAny(" besth", 12);
	EXPECT_EQ(7, val.GetValue());
	val = str1.FindLastNotOfAny("Ankur istheb", str1.GetLength());
	EXPECT_TRUE(val.IsInvalid());
}

TEST_F(StringTest, OperatorLess)
{
	EXPECT_FALSE(str < "");
	EXPECT_TRUE(str < "a");

	EXPECT_TRUE(str2 < "ZAnkur");
	EXPECT_TRUE(str2 < "anKUr");
	EXPECT_FALSE(str2 < " Ankur");

	cString str3("Ankur 5");
	EXPECT_FALSE(str3 < "Ankur 5");
	EXPECT_TRUE(str3 < "ZanKUr 5");
	EXPECT_FALSE(str3 < " Ankur 5");
}

TEST_F(StringTest, OperatorEqual)
{
	EXPECT_TRUE(str == "");
	EXPECT_FALSE(str == "a");

	EXPECT_TRUE(str2 == "Ankur");
	EXPECT_FALSE(str2 == "anKUr");
	EXPECT_FALSE(str2 == " Ankur");

	cString str3("Ankur 5");
	EXPECT_TRUE(str3 == "Ankur 5");
	EXPECT_FALSE(str3 == "anKUr 5");
	EXPECT_FALSE(str3 == " Ankur 5");
}

TEST_F(StringTest, Compare)
{
	EXPECT_EQ(0, str.Compare(""));
	EXPECT_GT(0, str.Compare("a"));

	EXPECT_EQ(0, str2.Compare("Ankur"));
	EXPECT_GT(0, str2.Compare("anKUr"));
	EXPECT_LT(0, str2.Compare(" Ankur"));

	cString str3("Ankur 5");
	EXPECT_EQ(0, str3.Compare("Ankur 5"));
	EXPECT_GT(0, str3.Compare("anKUr 5"));
	EXPECT_LT(0, str3.Compare(" Ankur 5"));
}

TEST_F(StringTest, CompareInsensitive)
{
	EXPECT_EQ(0, str.CompareInsensitive(""));
	EXPECT_GT(0, str.CompareInsensitive("a"));

	EXPECT_EQ(0, str2.CompareInsensitive("Ankur"));
	EXPECT_EQ(0, str2.CompareInsensitive("anKUr"));
	EXPECT_LT(0, str2.CompareInsensitive(" Ankur"));

	cString str3("Ankur 5");
	EXPECT_EQ(0, str3.CompareInsensitive("Ankur 5"));
	EXPECT_EQ(0, str3.CompareInsensitive("anKUr 5"));
	EXPECT_LT(0, str3.CompareInsensitive(" Ankur 5"));
}

TEST_F(StringTest, TrimLeft)
{
	str.TrimLeft();
	EXPECT_STREQ("", str.GetData());

	str1.TrimLeft();
	EXPECT_STREQ("Ankur is the best the ",str1.GetData());

	cString str3("    Ankur   ");
	str3.TrimLeft();
	EXPECT_STREQ("Ankur   ", str3.GetData());
}

TEST_F(StringTest, TrimRight)
{
	str.TrimRight();
	EXPECT_STREQ("", str.GetData());

	str1.TrimRight();
	EXPECT_STREQ(" Ankur is the best the", str1.GetData());

	cString str3(" Ankur      \n");
	str3.TrimRight();
	EXPECT_STREQ(" Ankur", str3.GetData());
}

TEST_F(StringTest, TrimBoth)
{
	str.TrimBoth();
	EXPECT_STREQ("", str.GetData());

	str1.TrimBoth();
	EXPECT_STREQ("Ankur is the best the", str1.GetData());
}

TEST_F(StringTest, InsertNOP)
{
	str.Insert(-1, "a");
	EXPECT_STREQ("", str.GetData());

	str.Insert(5, "a");
	EXPECT_STREQ("", str.GetData());

	str2.Insert(-1, "an");
	EXPECT_STREQ("Ankur", str2.GetData());

	str2.Insert(7, "an");
	EXPECT_STREQ("Ankur", str2.GetData());
}

TEST_F(StringTest, InsertAtBeginning)
{
	str.Insert(0, "ankur");
	EXPECT_STREQ("ankur", str.GetData());

	str2.Insert(0, "an ");
	EXPECT_STREQ("an Ankur", str2.GetData());
}

TEST_F(StringTest, InsertAtEnd)
{
	str2.Insert(5, "an");
	EXPECT_STREQ("Ankuran", str2.GetData());
}

TEST_F(StringTest, InsertInMiddle)
{
	str2.Insert(2, "an");
	EXPECT_STREQ("Anankur", str2.GetData());
}

TEST_F(StringTest, RemoveNOP)
{
	str.Remove(-1, 1);
	EXPECT_STREQ("", str.GetData());

	str.Remove(5, 1);
	EXPECT_STREQ("", str.GetData());

	str2.Remove(-1, 1);
	EXPECT_STREQ("Ankur", str2.GetData());

	str2.Remove(7, 1);
	EXPECT_STREQ("Ankur", str2.GetData());

	str2.Remove(5, 3);
	EXPECT_STREQ("Ankur", str2.GetData());

}

TEST_F(StringTest, RemoveFromBeginning)
{
	str2.Remove(0, 0);
	EXPECT_STREQ("Ankur", str2.GetData());

	str2.Remove(0, 2);
	EXPECT_STREQ("kur", str2.GetData());

	cString str3("Ankur");
	str3.Remove(0,7);
	EXPECT_STREQ("", str3.GetData());
}

TEST_F(StringTest, RemoveInMiddle)
{
	str2.Remove(2, 0);
	EXPECT_STREQ("Ankur", str2.GetData());

	str2.Remove(2, 2);
	EXPECT_STREQ("Anr", str2.GetData());

	cString str3("Ankur");
	str3.Remove(2,7);
	EXPECT_STREQ("An", str3.GetData());
}

TEST_F(StringTest, Tokenize)
{
	std::vector<cString> parts;
	str.Tokenize(" ", parts);
	EXPECT_EQ(0, parts.size());

	parts.clear();
	str1.Tokenize(" ", parts);
	EXPECT_EQ(5, parts.size());
	EXPECT_STREQ("Ankur", parts[0].GetData());
	EXPECT_STREQ("is", parts[1].GetData());
	EXPECT_STREQ("the", parts[2].GetData());
	EXPECT_STREQ("best", parts[3].GetData());
	EXPECT_STREQ("the", parts[4].GetData());

	parts.clear();
	str1.Tokenize(" eA", parts);
	EXPECT_EQ(6, parts.size());
	EXPECT_STREQ("nkur", parts[0].GetData());
	EXPECT_STREQ("is", parts[1].GetData());
	EXPECT_STREQ("th", parts[2].GetData());
	EXPECT_STREQ("b", parts[3].GetData());
	EXPECT_STREQ("st", parts[4].GetData());
	EXPECT_STREQ("th", parts[5].GetData());
}

TEST_F(StringTest, ToInt)
{
	tOptional<int> val;
	str.ToInt();
	EXPECT_TRUE(val.IsInvalid());

	val = str1.ToInt();
	EXPECT_TRUE(val.IsInvalid());

	cString str3 = "-100as";
	val = str3.ToInt();
	EXPECT_TRUE(val.IsInvalid());

	str3 = "-646464646464";
	val = str3.ToInt();
	EXPECT_TRUE(val.IsInvalid());

	str3 = "-2147483647";
	val = str3.ToInt();
	EXPECT_EQ(-2147483647, val.GetValue());

	str3 = "-2147483648";
	val = str3.ToInt();
	EXPECT_TRUE(val.IsInvalid());

	str3 = "-100";
	val = str3.ToInt();
	EXPECT_EQ(-100, val.GetValue());

	str3 = "1s00";
	val = str3.ToInt();
	EXPECT_TRUE(val.IsInvalid());

	str3 = "646464646464";
	val = str3.ToInt();
	EXPECT_TRUE(val.IsInvalid());

	str3 = "2147483647";
	val = str3.ToInt();
	EXPECT_EQ(2147483647, val.GetValue());

	str3 = "2147483648";
	val = str3.ToInt();
	EXPECT_TRUE(val.IsInvalid());

	str3 = "100";
	val = str3.ToInt();
	EXPECT_EQ(100, val.GetValue());
}

TEST_F(StringTest, ToFloat)
{
	tOptional<float> val;
	str.ToFloat();
	EXPECT_TRUE(val.IsInvalid());

	val = str1.ToFloat();
	EXPECT_TRUE(val.IsInvalid());

	cString str3 = "-100as";
	val = str3.ToFloat();
	EXPECT_TRUE(val.IsInvalid());

	str3 = "-646464646464";
	val = str3.ToFloat();
	EXPECT_FLOAT_EQ(-646464646464.0f, val.GetValue());

	str3 = "-10000.05172121";
	val = str3.ToFloat();
	EXPECT_FLOAT_EQ(-10000.05172121f, val.GetValue());

	str3 = "1s00";
	val = str3.ToFloat();
	EXPECT_TRUE(val.IsInvalid());

	str3 = "646464646464";
	val = str3.ToFloat();
	EXPECT_FLOAT_EQ(646464646464.0f, val.GetValue());

	str3 = "10000.05172121";
	val = str3.ToFloat();
	EXPECT_FLOAT_EQ(10000.05172121f, val.GetValue());
}

TEST_F(StringTest, ToBool)
{
	tOptional<bool> val;
	str.ToBool();
	EXPECT_TRUE(val.IsInvalid());

	val = str1.ToBool();
	EXPECT_TRUE(val.IsInvalid());

	cString str3 = "-100as";
	val = str3.ToBool();
	EXPECT_TRUE(val.IsInvalid());

	str3 = "-1";
	val = str3.ToBool();
	EXPECT_TRUE(val.IsInvalid());

	str3 = "2";
	val = str3.ToBool();
	EXPECT_TRUE(val.IsInvalid());

	str3 = "10";
	val = str3.ToBool();
	EXPECT_TRUE(val.IsInvalid());

	str3 = "01";
	val = str3.ToBool();
	EXPECT_TRUE(val.IsInvalid());

	str3 = "trUe";
	val = str3.ToBool();
	EXPECT_TRUE(val.GetValue());

	str3 = "TrUe";
	val = str3.ToBool();
	EXPECT_TRUE(val.GetValue());

	str3 = "Yes";
	val = str3.ToBool();
	EXPECT_TRUE(val.GetValue());

	str3 = "yES";
	val = str3.ToBool();
	EXPECT_TRUE(val.GetValue());

	str3 = "1";
	val = str3.ToBool();
	EXPECT_TRUE(val.GetValue());

	str3 = "FaLse";
	val = str3.ToBool();
	EXPECT_FALSE(val.GetValue());

	str3 = "falSE";
	val = str3.ToBool();
	EXPECT_FALSE(val.GetValue());

	str3 = "No";
	val = str3.ToBool();
	EXPECT_FALSE(val.GetValue());

	str3 = "nO";
	val = str3.ToBool();
	EXPECT_FALSE(val.GetValue());

	str3 = "0";
	val = str3.ToBool();
	EXPECT_FALSE(val.GetValue());
}
