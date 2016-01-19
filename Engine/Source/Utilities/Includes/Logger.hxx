//  *******************************************************************************************************************
//  Logger   version:  1.0   Ankur Sheel  date: 2011/02/16
//  *******************************************************************************************************************
// 
//  *******************************************************************************************************************
#ifndef __LOGGER_HXX__
#define __LOGGER_HXX__

#include "UtilitiesDefines.h"
#include "SpAssertLogger.hxx"
#include "SpAssertFwd.h"

namespace Base
{
	class cString;
}

namespace Utilities
{
	struct LogType 
	: Base::AssertLevels
	{
		enum
		{
			EVENT=80,
			GAME_MESSAGE=90,
		};
	};

	///////////////////////////////////////////////////////////////////////////
	/// @brief Interface for Logging
	///
	/// 
	///////////////////////////////////////////////////////////////////////////
	class ILogger
	: public Base::ISpAssertLogger
	{
	public:
		virtual ~ILogger(){}
		////////////////////////////////////////////////////////////////////////
		/// Initializes the logger. XML Log file is always created.
		///
		///
		////////////////////////////////////////////////////////////////////////
		UTILITIES_API virtual void VInitialize() = 0;
		////////////////////////////////////////////////////////////////////////
		/// Sets the log options
		///
		/// @param[in] bShowConsole True if we want to log to a console window. 
		/// @param[in] bLogToText True if we want to log to a text file. 
		/// @param[in] bLogToXML True if we want to log to a XML file. 
		/// @param[in] uiPriorityLevel The minimum level that must be logged
		///
		////////////////////////////////////////////////////////////////////////
		UTILITIES_API virtual void VSetLogOptions(const bool bShowConsole, const bool bLogToText, const bool bLogToXML,
		const unsigned int uiPriorityLevel) = 0;

		UTILITIES_API static std::tr1::shared_ptr<ILogger> CreateLogger();
	};
}
#endif  // __LOGGER_HXX__

