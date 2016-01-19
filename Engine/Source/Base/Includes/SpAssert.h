//  *******************************************************************************************************************
//  Assert   version:  1.0   Ankur Sheel  date: 2014/10/10
//  *******************************************************************************************************************
// http://www.drdobbs.com/assertions/184403861
//  *******************************************************************************************************************
#ifndef __SP_ASSERT_H__
#define __SP_ASSERT_H__

#include <sstream>
#include "BaseDefines.h"
#include "myString.h"
#include "Macros.h"
#include "SpAssertFwd.h"

#define SP_LOG_(level, priority, message) Base::cSpAssert::Make(level, message, true).AddContext("file", SP_FILE)\
	.AddContext("line", TOSTRING(SP_LINE))\
	.AddContext("function", SP_FUNCTION_NAME)\
	.AddContext("priority", TOSTRING(priority))\
	.SMART_ASSERT_A

#define SP_LOG(priority, message) SP_LOG_(Base::AssertLevels::LEVEL_INFO, priority, message)
#define SP_LOG_CUSTOM(level, priority, message) SP_LOG_(level, priority, message)

#define SP_ASSERT_1(level, expr) \
	if ((expr)); \
	else \
	Base::cSpAssert::Make(level, TOSTRING(expr), false).AddContext("file", SP_FILE)\
	.AddContext("line", TOSTRING(SP_LINE))\
	.AddContext("function", SP_FUNCTION_NAME)\
	.SMART_ASSERT_A

#define SP_ASSERT_(level, expr) SP_ASSERT_1(level, expr)

#ifdef SPASSERT_DEBUG_MODE
	#define SP_ASSERT(expr) SP_ASSERT_(Base::AssertLevels::LEVEL_DEBUG, expr)
	#define SP_ASSERT_WARNING(expr) SP_ASSERT_(Base::AssertLevels::LEVEL_WARNING, expr)
	#define SP_ASSERT_DEBUG(expr) SP_ASSERT_(Base::AssertLevels::LEVEL_DEBUG, expr)
	#define SP_ASSERT_ERROR(expr) SP_ASSERT_(Base::AssertLevels::LEVEL_ERROR, expr)
	#define SP_ASSERT_FATAL(expr) SP_ASSERT_(Base::AssertLevels::LEVEL_FATAL, expr)
	#define SP_ASSERT_CUSTOM(level, expr) SP_ASSERT_(level, expr)
#else
	#define SP_ASSERT(expr) SP_ASSERT_(Base::AssertLevels::LEVEL_DEBUG, true)
	#define SP_ASSERT_WARNING(expr) SP_ASSERT_(Base::AssertLevels::LEVEL_WARNING, true)
	#define SP_ASSERT_DEBUG(expr) SP_ASSERT_(Base::AssertLevels::LEVEL_DEBUG, true)
	#define SP_ASSERT_ERROR(expr) SP_ASSERT_(Base::AssertLevels::LEVEL_ERROR, expr)
	#define SP_ASSERT_FATAL(expr) SP_ASSERT_(Base::AssertLevels::LEVEL_FATAL, expr)
	#define SP_ASSERT_CUSTOM(level, expr) SP_ASSERT_(level, true)
#endif

#define SMART_ASSERT_A(x) SMART_ASSERT_OP(x, B)
#define SMART_ASSERT_B(x) SMART_ASSERT_OP(x, A)
#define SMART_ASSERT_OP(x, next) \
	SMART_ASSERT_A.AddValue(TOSTRING(x), (x)).SMART_ASSERT_ ## next

namespace Base
{
	class ISpAssertContext;
	class ISpAssertSettings;
}

namespace Base
{
	class cSpAssert
	{
	public:
		BASE_API cSpAssert(int level, const cString & expr, const bool onlyLog);
		cSpAssert(const cSpAssert & other);
		BASE_API ~cSpAssert();
		BASE_API cSpAssert & AddContext(const cString & key, const cString & value);
		BASE_API cSpAssert & SetCustomMessage(const cString & message);

		template <class Type>
		cSpAssert & AddValue(const cString & variableName, Type value);

		BASE_API static cSpAssert Make(int level, const cString & expr, const bool onlyLog);

	private:
		void Handle() const;

		void DefaultHandle() const;

	public:
		// helpers, in order to be able to compile the code
		cSpAssert & SMART_ASSERT_A;
		cSpAssert & SMART_ASSERT_B;

	protected:
		ISpAssertContext *m_pContext;
		bool m_bOnlyLog;

	private:
	};

	//  ********************************************************************************************************************
	template <class Type>
	cSpAssert & cSpAssert::AddValue(const cString & variableName, Type value)
	{
		if (m_pContext != NULL)
		{
			std::stringstream my_stream;
			if (value  == 0)
			{
				my_stream << "null";
			}
			else
			{
				my_stream << value;
			}
			if (m_pContext != NULL)
			{
				m_pContext->VAddVariableValues(variableName, my_stream.str());
			}
		}
		return *this;
	}
}
#endif  // __SP_ASSERT_H__
