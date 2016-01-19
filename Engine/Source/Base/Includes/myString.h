//  *******************************************************************************************************************
//  myString   version:  1.0   Ankur Sheel  date: 2011/03/08
//  *******************************************************************************************************************
// 
//  *******************************************************************************************************************
#ifndef myString_h__
#define myString_h__

#include "BaseDefines.h"
#include <string>
#include <iostream>
#include <vector>

namespace Base
{
	template<class T>
	class tOptional;
}

namespace Base
{
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @brief String class 
	///
	/// 
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class cString
	{
	public:
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Constructor
		///
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		BASE_API cString();
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Constructor
		///
		/// @param[in] s The char array to be used for initialization
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		BASE_API cString(const char * s);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Constructor
		///
		/// @param[in] s The string to be used for initialization
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		BASE_API cString(std::string const & s);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Copy Constructor
		///
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		BASE_API cString(const cString & str); // ankur - move to private when changing back to char * instead of string
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Assignment Operator
		///
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		BASE_API cString & operator=(const cString & str);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Adds the passed in string to the current string
		///
		/// @param[in] str The string to be added to this string
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		BASE_API void operator +=(const cString & str);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Returns true if the current string is less than the passed in string
		///
		/// @param[in] str The string to be compared to this string
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		BASE_API bool operator <(const cString & str) const;
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Returns true if the current string is equal to the passed in string
		///
		/// @param[in] str The string to be compared to this string
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		BASE_API bool operator ==(const cString & str) const;
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Returns the character at the specified index in the string. Returns
		/// null, if the index is greater than the length of the string.
		///
		/// @param[in] index The index of the position of the element to be
		/// accessed
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		BASE_API const char operator[](const unsigned int index) const;
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Returns the character at the specified index in the string. Returns
		/// null, if the index is greater than the length of the string.
		///
		/// @param[in] index The index of the position of the element to be
		/// accessed
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		BASE_API char operator[](const unsigned int index);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Returns the contents of a string as a C-style, null-terminated string.
		///
		/// @return The contents of a string as a C-style, null-terminated string.
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		BASE_API const char * const GetData() const { return m_str.c_str(); }
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Returns True if the string is empty.
		///
		/// @return True if the string is empty
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		BASE_API bool IsEmpty() const { return m_str.empty(); }
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Returns the length of the string
		///
		/// @return The length of the string
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		BASE_API unsigned int GetLength() const {return m_str.length(); }
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Returns the substring of the string from uiStartIndex to uiEndIndex.
		/// uiStartIndex anduiEndIndex are between 0 and string length
		///
		/// @param[in] startIndex The start index for the substring.
		/// @param[in] endIndex The end index for the substring.
		/// @return The substring of the string starting from startIndex to endIndex.
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		BASE_API cString GetSubString(const int startIndex, const int endIndex) const;
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Searches the string for the first occurrence of a character starting
		/// from an offset.
		///
		/// @param[in] chChar The character to be found
		/// @param[in] iOffset The index to start the search from
		/// @return The index of the character when successful. Invalid optional  otherwise 
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		BASE_API Base::tOptional<int> FindIndex(const char chararcter, const int offset) const;
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Searches the string for the first occurrence of any of the passed in characters starting from an offset.
		///
		/// @param[in] characters The characters for which the function is to search
		/// @param[in] offset The index to start the search from
		/// @return The index of the first character that is found when successful.
		/// Invalid optional otherwise 
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		BASE_API Base::tOptional<int> FindFirstOfAny(const cString & characters, const int offset) const;
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Searches the string for the first character thats is any of the passed in characters starting from an offset.
		///
		/// @param[in] characters The characters for which the function is to search
		/// @param[in] offset The index to start the search from
		/// @return The index of the first character that is found when successful. Invalid optional otherwise 
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		BASE_API Base::tOptional<int> FindFirstNotOfAny(const cString & characters, const int offset) const;
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Searches the string for the last occurrence of any of the passed in characters before the offset.
		///
		/// @param[in] characters The characters for which the function is to search.
		/// @param[in] lastIndex The index at which the search should end.
		/// @return The index of the last character that is found when successful. Invalid optional otherwise.
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		BASE_API Base::tOptional<int> FindLastOfAny(const cString & characters, const int lastIndex) const;
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Searches the string for the last character thats is not any of the passed in characters before the offset.
		///
		/// @param[in] characters The characters for which the function is to search
		/// @param[in] lastIndex The index at which the search should end
		/// @return The index of the last character that is found when successful. Invalid optional otherwise 
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		BASE_API Base::tOptional<int> FindLastNotOfAny(const cString & characters, const int lastIndex) const;
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Case Sensitive comparison of current string with passed in string
		///
		/// @param[in] str The string to be compared
		/// @return value < 0 this string is less than str
		/// value = 0 this string is identical to str
		/// value > 0 this string is greater than str
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		BASE_API int Compare(const cString & str) const;
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Case Insensitive comparison of current string with passed in string
		///
		/// @param[in] str The string to be compared
		/// @return value < 0 this string is less than str
		/// value = 0 this string is identical to str
		/// value > 0 this string is greater than str
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		BASE_API int CompareInsensitive(const cString & str) const;
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Removes whitespace characters from the beginning of the string
		///
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		BASE_API void TrimLeft();
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Removes whitespace and EOL characters from the end of the string
		///
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		BASE_API void TrimRight();
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Removes whitespace and EOL characters from the begining and end of
		/// the string
		///
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		BASE_API void TrimBoth();
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Inserts a string at a specified index
		///
		/// @param[in] index The index at which the string is to be added
		/// @param[in] text The string which is to be added
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		BASE_API void Insert(const int index, const cString & text);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Removes specified number of characters from a specified index
		///
		/// @param[in] index The index from which the characters are to be
		/// removed
		/// @param[in] quantity The number of characters to be removed
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		BASE_API void Remove(const int index, const int quantity);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Tokenizes the string based on any of the delimiters
		///
		/// @param[in] delimiters The delimiters based on which the string will be tokenized
		/// @param[out] parts The tokenized strings
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		BASE_API void Tokenize(const Base::cString & delimiters, std::vector<Base::cString> & parts) const;
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Converts the string to an int value
		///
		/// @return The int value of this string if the conversion is successful.
		/// Invalid optional otherwise 
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		BASE_API Base::tOptional<int> ToInt() const;
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Converts the string to a float value
		///
		/// @return The float value of this string if the conversion is successful.
		/// Invalid optional otherwise 
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		BASE_API Base::tOptional<float> ToFloat() const;
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Converts the string to a bool value
		///
		/// @return The bool value of this string if the conversion is successful.
		/// Invalid optional otherwise 
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		BASE_API Base::tOptional<bool> ToBool() const;
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Writes a string to the output stream
		///
		/// @param[in] os The output stream being written to
		/// @param[in] str The string to be written
		/// @return Writes the value of the specified string to the output stream
		///
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		friend BASE_API std::ostream & operator<< (std::ostream &out, const cString & str);

	public:
		BASE_API static cString EmptyString;

	private:
		std::string m_str;
	};
}
#endif // myString_h__