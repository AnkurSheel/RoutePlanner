//  *******************************************************************************************************************
//  SpAssertLogger   version:  1.0   Ankur Sheel  date: 2014/11/03
//  *******************************************************************************************************************
// 
//  *******************************************************************************************************************
#ifndef __SPASSERTLOGGER_HXX__
#define __SPASSERTLOGGER_HXX__

namespace Base
{
	class ISpAssertContext;
}

namespace Base
{
	class ISpAssertLogger
	{
	public:
		~ISpAssertLogger(){}
		virtual void VInitialize() = 0;
		virtual void VLog(const ISpAssertContext * const pContext) = 0;
	};
}
#endif  // __SPASSERTLOGGER_HXX__
