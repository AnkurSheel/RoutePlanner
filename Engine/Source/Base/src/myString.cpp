#include "stdafx.h"
#include "myString.h"
#include "Optional.h"
#include <ctype.h>

using namespace Base;

cString cString::EmptyString;

//  *******************************************************************************************************************
cString::cString()
{
}

//  *******************************************************************************************************************
cString::cString(const char * s)
{
	if (s != NULL)
	{
		m_str = s;
	}
}

//  *******************************************************************************************************************
cString::cString(std::string const & s)
: m_str(s)
{
}

//  *******************************************************************************************************************
cString::cString(const cString & other)
: m_str(other.m_str)
{
}

//  *******************************************************************************************************************
cString & cString::operator=(const cString & other)
{
	m_str = other.m_str;
	return *this;
}

//  *******************************************************************************************************************
void cString::operator+=(const cString & str)
{
	m_str.append(str.GetData());
}

//  *******************************************************************************************************************
bool cString::operator < (const cString & str) const
{
	return m_str.compare(str.m_str) < 0;
}

//  *******************************************************************************************************************
bool cString::operator == (const cString & str) const 
{
	return m_str.compare(str.m_str) == 0;
}

//  *******************************************************************************************************************
const char cString::operator[](const unsigned int index) const
{
	if(index < GetLength())
	{
		return m_str[index];
	}
	return '\0';
}

//  *******************************************************************************************************************
char cString::operator[](const unsigned int index)
{
	if(index < GetLength())
	{
		return m_str[index];
	}
	return '\0';
}

//  *******************************************************************************************************************
cString cString::GetSubString(const int startIndex, const int endIndex) const
{
	if (startIndex > endIndex || startIndex < 0 || endIndex > GetLength())
	{
		return "";
	}

	return m_str.substr(startIndex, (endIndex - startIndex) + 1);
}

//  *******************************************************************************************************************
tOptional<int> cString::FindIndex(const char character, const int offset) const
{
	if (IsEmpty())
	{
		return tOptional<int>();
	}

	tOptional<int> val;

	std::string::size_type pos = m_str.find(character, offset);
	if(pos == std::string::npos)
	{
		val.clear();
	}
	else
	{
		val = pos;
	}
	return val;
}

//  *******************************************************************************************************************
tOptional<int> cString::FindFirstOfAny(const cString & characters, const int offset) const
{
	if (IsEmpty())
	{
		return tOptional<int>();
	}

	tOptional<int> val;

	std::string::size_type pos = m_str.find_first_of(characters.GetData(), offset);
	if(pos == std::string::npos)
	{
		val.clear();
	}
	else
	{
		val = pos;
	}

	return val;
}

//  *******************************************************************************************************************
tOptional<int> cString::FindFirstNotOfAny(const cString & characters, const int offset) const
{
	if (IsEmpty())
	{
		return tOptional<int>();
	}

	tOptional<int> val;

	std::string::size_type pos = m_str.find_first_not_of(characters.GetData(), offset);
	if(pos == std::string::npos)
	{
		val.clear();
	}
	else
	{
		val = pos;
	}

	return val;
}

//  *******************************************************************************************************************
tOptional<int> cString::FindLastOfAny(const cString & characters, const int lastIndex) const
{
	if (IsEmpty())
	{
		return tOptional<int>();
	}

	tOptional<int> val;

	std::string::size_type pos = m_str.find_last_of(characters.GetData(), lastIndex);
	if(pos == std::string::npos)
	{
		val.clear();
	}
	else
	{
		val = pos;
	}

	return val;
}

//  *******************************************************************************************************************
tOptional<int> cString::FindLastNotOfAny(const cString & characters, const int lastIndex) const
{
	if (IsEmpty())
	{
		return tOptional<int>();
	}

	tOptional<int> val;

	std::string::size_type pos = m_str.find_last_not_of(characters.GetData(), lastIndex);
	if(pos == std::string::npos)
	{
		val.clear();
	}
	else
	{
		val = pos;
	}

	return val;
}

//  ********************************************************************************************************************
int cString::Compare(const cString & str) const
{
	return m_str.compare(str.m_str);
}

//  *******************************************************************************************************************
int cString::CompareInsensitive(const cString & str) const
{
	return _stricmp(GetData(), str.GetData());
}

//  *******************************************************************************************************************
void cString::TrimLeft()
{
	const cString delims(" \t");
	tOptional<int> endIndex;

	endIndex = FindFirstNotOfAny(delims, 0);
	if(endIndex.IsInvalid())
	{
		m_str.clear();
	}
	else if(endIndex.GetValue() > 0)
	{
		tOptional<int> begIndex;

		begIndex = FindFirstOfAny(delims, 0);
		if(begIndex.IsValid())
		{
			m_str = m_str.substr(endIndex.GetValue(), (m_str.length() - endIndex.GetValue()));
		}
	}
}

//  *******************************************************************************************************************
void cString::TrimRight()
{
	const cString delims(" \t\r\n");
	tOptional<int> endIndex;

	endIndex = FindLastNotOfAny(delims, GetLength());
	if(endIndex.IsInvalid())
	{
		m_str.clear();
	}
	else
	{
		m_str = m_str.substr(0, endIndex.GetValue() + 1);
	}
}

//  *******************************************************************************************************************
void cString::TrimBoth()
{
	if (IsEmpty())
	{
		return;
	}
	TrimLeft();
	TrimRight();
}

//  *******************************************************************************************************************
void cString::Insert(const int index, const cString & text)
{
	if (index >= 0 && index <= GetLength())
	{
		m_str.insert(index, text.GetData());
	}
}

//  *******************************************************************************************************************
void cString::Remove(const int index, const int quantity)
{
	if (index >= 0 && index <= GetLength() && quantity > 0)
	{
		m_str.erase(index, quantity);
	}
}

//  *******************************************************************************************************************
void cString::Tokenize(const cString & delimiters, std::vector<cString> & parts) const
{
	if (IsEmpty() || delimiters.GetLength() == 0)
	{
		return;
	}
	int iStartIndex = 0;

	tOptional<int> nextIndex;
	while (iStartIndex < GetLength())
	{
		nextIndex = FindFirstOfAny(delimiters, iStartIndex);
		if (nextIndex.IsInvalid())
		{
			nextIndex = GetLength();
		}
		if (iStartIndex != nextIndex.GetValue())
		{
			parts.push_back(GetSubString(iStartIndex, nextIndex.GetValue() - 1));
		}
		iStartIndex = nextIndex.GetValue() + 1;
	}
}

//  *******************************************************************************************************************
tOptional<int> cString::ToInt() const
{
	tOptional<int> value = 0;
	int len = m_str.length();
	if(len == 0)
	{
		value.clear();
		return value;
	}

	int startIndex = 0;
	bool bNegative = false;

	if(m_str[0] == '-')
	{
		startIndex++;
		bNegative = true;
	}
	int intVal = m_str[startIndex++] - '0';
	for(int i = startIndex; i < len; i++)
	{
		char ch = m_str[i];
		if(ch < '0' || ch > '9')
		{
			value.clear();
			return value;
		}
		intVal = (intVal * 10)+ ((ch - '0'));
		if (intVal < 0) // overflow
		{
			value.clear();
			return value;
		}
	}

	if(bNegative)
	{
		intVal = -intVal;
	}
	value = intVal;
	return value;
}

//  *******************************************************************************************************************
tOptional<float> cString::ToFloat() const
{
	tOptional<float> value = 0;
	int len = m_str.length();
	if(len == 0)
	{
		value.clear();
		return value;
	}

	int startIndex = 0;
	bool bNegative = false;

	if(m_str[0] == '-')
	{
		startIndex++;
		bNegative = true;
	}

	float integerPart = m_str[startIndex++] - '0';

	int index = startIndex;
	for(; index < len; index++)
	{
		char ch = m_str[index];
		if(ch < '0' || ch > '9')
		{
			if(ch == '.')
			{
				index++;
				break;
			}
			else
			{
				value.clear();
				return value;
			}
		}
		integerPart = (integerPart * 10)+ ((ch - '0'));
	}
	float decimalPart = 0.0f;

	float decimalDigit = 0.1f;
	for(; index < len; index++)
	{
		char ch = m_str[index];
		if(ch < '0' || ch > '9')
		{
			value.clear();
			return value;
		}
		decimalPart = decimalPart + ((ch - '0') * decimalDigit);
		decimalDigit *= 0.1f;
	}
	decimalPart += integerPart; 
	if(bNegative)
	{
		decimalPart = -decimalPart;
	}
	value = decimalPart;
	return value;
}

//  *******************************************************************************************************************
tOptional<bool> cString::ToBool() const
{
	tOptional<bool> val;

	if(_stricmp(m_str.data(), "true") == 0 || _stricmp(m_str.data(), "yes") == 0
			|| _stricmp(m_str.data(), "1") == 0)
	{
		val = true;
	}
	else if(_stricmp(m_str.data(), "false") == 0 || _stricmp(m_str.data(), "no") == 0
			|| _stricmp(m_str.data(), "0") == 0)
	{
		val = false;
	}
	else
	{
		val.clear();
	}
	return val;
}

//  ********************************************************************************************************************
BASE_API std::ostream & operator <<(std::ostream &out, const cString & str)
{
	out << str.GetData();
	return out;
}
