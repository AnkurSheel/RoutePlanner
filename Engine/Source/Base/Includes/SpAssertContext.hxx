//  *******************************************************************************************************************
//  SpAssertContext   version:  1.0   Ankur Sheel  date: 2014/10/23
//  *******************************************************************************************************************
// 
//  *******************************************************************************************************************
#ifndef __SPASSERTCONTEXT_HXX__
#define __SPASSERTCONTEXT_HXX__

namespace Base
{
	struct stVariables 
	{
		stVariables(const cString & VariableName, const cString & VariableValue)
		: m_VariableValue(VariableValue)
		, m_VariableName(VariableName)
		{
		}

		cString m_VariableValue;
		cString m_VariableName;
	};

	class ISpAssertContext
	{
	public:
		typedef std::vector<stVariables> VariablesArray;

	public:
		virtual ~ISpAssertContext() {}
		virtual void VAddContextValue(const cString & key, const cString & value) = 0;
		//BASE_API const cString & GetContextValue(const cString & key) const;
		virtual const cString & VGetFileName() const = 0;
		virtual int VGetLineNumber() const = 0;
		virtual const cString & VGetFunctionName() const = 0;
		virtual int VGetPriority() const = 0;

		virtual const VariablesArray & VGetVariablesArray() const = 0;
		virtual const cString & VGetCustomMessage() const = 0;
		virtual void VSetCustomMessage(cString message) = 0;
		virtual int VGetDebugLevel() const = 0;
		virtual void VSetDebugLevel(int level) = 0;
		virtual const Base::cString & VGetExpression() const = 0;
		virtual void VSetExpression(const cString & expr) = 0;

		virtual void VAddVariableValues(const cString & variableName, const cString & variableValue) = 0;

		BASE_API static ISpAssertContext * const Create();
		BASE_API static ISpAssertContext * const Duplicate(const ISpAssertContext * const pContext);
	};
} 
#endif  // __SPASSERTCONTEXT_HXX__
