#include "stdafx.h"
#include "StringUtilities.h"
#include <time.h>

using namespace Base;

//  *******************************************************************************************************************
cString cStringUtilities::MakeFormatted(const char * const inpFmt, ...)
{
	va_list arglist;
	va_start(arglist, inpFmt);

	int resultingStringSize = vsnprintf(NULL, 0, inpFmt, arglist);
	char* pBuffer = DEBUG_NEW char[resultingStringSize+1];
	vsnprintf(pBuffer, resultingStringSize + 1, inpFmt, arglist);
	cString str(pBuffer);
	va_end(arglist);
	SafeDeleteArray(&pBuffer);
	return str;
}

//  *******************************************************************************************************************
cString cStringUtilities::GetInLowerCase(const cString & str)
{
	std::string lowerCase = str.GetData();
	std::transform(lowerCase.begin(), lowerCase.end(), lowerCase.begin(), ::tolower);
	return lowerCase;
}

//  *******************************************************************************************************************
cString cStringUtilities::CalendarTimeToString(time_t time)
{
	char str[26];
	ctime_s(str, 26, &time);
	str[24] = '\0'; // remove the '/n' from the time string
	return str;
}

//  *******************************************************************************************************************
cString Base::operator + (const cString & lhs, const cString & rhs)
{
	cString str = lhs;
	str += rhs;
	return str;
}

//  *******************************************************************************************************************
cString Base::operator + (const char * lhs, const cString & rhs)
{
	cString str = lhs;
	str += rhs;
	return str;
}

//  *******************************************************************************************************************
cString Base::operator + (const cString & lhs, const char* rhs)
{
	cString str = lhs;
	str += rhs;
	return str;
}

//  *******************************************************************************************************************
std::ostream& Base::operator << (std::ostream& os, const cString & str)
{
	os << str.GetData();
	return os;
}
