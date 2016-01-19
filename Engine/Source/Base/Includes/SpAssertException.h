//  *******************************************************************************************************************
//  SpAssertError   version:  1.0   Ankur Sheel  date: 2014/11/18
//  *******************************************************************************************************************
// 
//  *******************************************************************************************************************
#ifndef __SPASSERTERROR_H__
#define __SPASSERTERROR_H__

namespace Base
{
	struct cSpAssertException
	: public std::exception 
	{
		cSpAssertException(const ISpAssertContext * const pContext);
		~cSpAssertException();
		const char * what() const;

	private:
		const ISpAssertContext * const m_pContext;
	};
}
#endif  // __SPASSERTERROR_H__
