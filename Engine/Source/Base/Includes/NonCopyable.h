// *****************************************************************************
//  NonCopyable   version:  1.0   Ankur Sheel  date: 2011/12/20
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#ifndef NonCopyable_h__
#define NonCopyable_h__

namespace Base
{
	///////////////////////////////////////////////////////////////////////////
	/// @brief Base Class which prevents copying of classes dervied from it
	///
	/// 
	///////////////////////////////////////////////////////////////////////////
	class cNonCopyable
	{
	public:
		virtual ~cNonCopyable(){}
	
	protected:
		cNonCopyable(){}
	
	private:
		cNonCopyable(const cNonCopyable&);
		cNonCopyable& operator =(const cNonCopyable&);
	};
}
#endif // NonCopyable_h__