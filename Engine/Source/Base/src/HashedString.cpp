//  *******************************************************************************************************************
//  HashedString   version:  1.0   Ankur Sheel  date: 2012/12/26
//  *******************************************************************************************************************
// 
//  *******************************************************************************************************************
#include "stdafx.h"
#include "HashedString.h"

using namespace Base;

//  *******************************************************************************************************************
cHashedString::cHashedString()
: m_Checksum(0)
{
}

//  *******************************************************************************************************************
cHashedString::cHashedString(const cString & str)
: m_String(str)
, m_Checksum(CalculateChecksum(str))
{
}

//  ********************************************************************************************************************
cHashedString::cHashedString(const cHashedString & other)
: m_Checksum(other.m_Checksum)
, m_String(other.m_String)
{
}

//  ********************************************************************************************************************
cHashedString & cHashedString::operator= (const cHashedString & other)
{
	m_String = other.m_String;
	m_Checksum = other.m_Checksum;
	return *this;

}

//  *******************************************************************************************************************
unsigned long cHashedString::CalculateChecksum(const cString & str)
{
	if(str.IsEmpty())
	{
		return 0;
	}

	// largest prime smaller than 65536
	unsigned long MOD_ADLER = 65521L;
	
  // MAX is the largest n such that 255n(n+1)/2 + (n+1)(BASE-1) <= 2^32-1
  unsigned int MAX_LENGTH = 5522;

	unsigned int s1 = 1;
	unsigned int s2 = 0;
  
  unsigned int length = str.GetLength();

  while(length > 0)
  {
    int k = length < MAX_LENGTH ? length : MAX_LENGTH;
    length -= k;
    for(int index = 0; index < k; index++)
    {
      s1 = (s1 + (str[index] & 0xFF)) % MOD_ADLER;
      s2 = (s2 + s1) % MOD_ADLER;
    }
  }

	return ((s2 << 16) | s1);
}

//  ********************************************************************************************************************
bool cHashedString::operator==(cHashedString const & other) const
{
	if(m_Checksum != 0)
	{
		bool r = (m_Checksum == other.m_Checksum);
		return r;
	}
	return false;
}
