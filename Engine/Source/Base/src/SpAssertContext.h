//  *******************************************************************************************************************
//  SpAssertContext   version:  1.0   Ankur Sheel  date: 2014/10/10
//  *******************************************************************************************************************
// 
//  *******************************************************************************************************************
#ifndef __SPASSERTCONTEXT_H__
#define __SPASSERTCONTEXT_H__

#include <map>
#include "SpAssertContext.hxx"

namespace Base
{
	class cSpAssertContext 
	: public ISpAssertContext
	{
		typedef std::map<cString, cString> ContextMap;

	public:
		~cSpAssertContext();
		void VAddContextValue(const cString & key, const cString & value);
		const cString & GetContextValue(const cString & key) const;
		const cString & VGetFileName() const;
		const cString & VGetFunctionName() const;
		int VGetLineNumber() const;
		int VGetPriority() const;
		const VariablesArray & VGetVariablesArray() const { return m_Variables; }
		const cString & VGetCustomMessage() const { return m_CustomMessage; }
		void VSetCustomMessage(cString message) { m_CustomMessage = message; }
		int VGetDebugLevel() const { return m_DebugLevel; }
		void VSetDebugLevel(int level) { m_DebugLevel = level; }
		const Base::cString & VGetExpression() const { return m_Expression; }
		void VSetExpression(const cString & expr) { m_Expression = expr; }

		void VAddVariableValues(const cString & variableName, const cString & variableValue) { m_Variables.push_back(stVariables(variableName, variableValue)); }

	private:
		cSpAssertContext();

	private:
		ContextMap m_ContextCollection;
		VariablesArray m_Variables;
		cString m_Expression;
		cString m_CustomMessage;
		int m_DebugLevel;

		friend static ISpAssertContext* const ISpAssertContext::Create();
		friend static ISpAssertContext * const Duplicate(const ISpAssertContext * const pContext);

	};

	inline bool operator < (const cSpAssertContext & first, const cSpAssertContext & second)
	{
		int n = first.VGetFileName().Compare(second.VGetFileName());
		if (n != 0)
		{
			return n < 0;
		}
		else
		{
			return first.VGetLineNumber() < second.VGetLineNumber();
		}
	}
}
#endif  // __SPASSERTCONTEXT_H__
