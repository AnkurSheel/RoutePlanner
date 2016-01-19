//  *******************************************************************************************************************
//  BTConditional   version:  1.0   Ankur Sheel  date: 2014/12/29
//  *******************************************************************************************************************
// 
//  *******************************************************************************************************************
#ifndef __BTCONDITIONAL_H__
#define __BTCONDITIONAL_H__

#include "BTBehavior.h"

namespace AI
{
	namespace ConditionalOperators
	{
		enum Enum
		{
			LessThan,
			GreaterThan,
			LessOrEqual,
			GreaterOrEqual,
			Equal,
			NotEqual
		};
	}

	template <class DATA, class CLASS>
	class cBTConditionalNode
		: public cBTBehavior
	{
	public:
		typedef DATA (CLASS::* Getter)() const;

		DEFINE_NODE_PROPERTY(cBTConditionalNode, weak_ptr<CLASS>, Holder);
		DEFINE_NODE_PROPERTY(cBTConditionalNode, Getter, Function);
		DEFINE_NODE_PROPERTY(cBTConditionalNode, DATA, Value);
		DEFINE_NODE_PROPERTY(cBTConditionalNode, ConditionalOperators::Enum, TestType);

	public:
		~cBTConditionalNode(){};
		BT_STATUS::Enum VOnUpdate(void * pOwner);

	private:
		cBTConditionalNode()
			: m_TestType(ConditionalOperators::Equal)
		{
		}

	private:
		friend class cBTNodeFactory;

	};

	//  ********************************************************************************************************************
	template <class DATA, class CLASS>
	BT_STATUS::Enum cBTConditionalNode<DATA, CLASS>::VOnUpdate(void * pOwner)
	{
		if (m_Holder.expired())
		{
			return BT_STATUS::Failure;
		}
		shared_ptr<CLASS> pHolder = MakeStrongPtr(m_Holder);

		bool status = false;
		switch(m_TestType)
		{
		case ConditionalOperators::Equal:
			status = ((pHolder.get()->*m_Function)() == m_Value);
			break;
		case ConditionalOperators::NotEqual:
			status = ((pHolder.get()->*m_Function)() != m_Value);
			break;
		case ConditionalOperators::LessThan:
			status = ((pHolder.get()->*m_Function)() < m_Value);
			break;
		case  ConditionalOperators::LessOrEqual:
			status = ((pHolder.get()->*m_Function)() <= m_Value);
			break;
		case ConditionalOperators::GreaterThan:
			status = ((pHolder.get()->*m_Function)() > m_Value);
			break;
		case ConditionalOperators::GreaterOrEqual:
			status = ((pHolder.get()->*m_Function)() >= m_Value);
			break;
		};

		if (status)
		{
			return BT_STATUS::Success;
		}
		else
		{
			return BT_STATUS::Failure;
		}
	}

	template <class CLASS>
	class cBTConditionalNode<float, CLASS>
		: public cBTBehavior
	{
	public:
		typedef float (CLASS::* Getter)() const;

		DEFINE_NODE_PROPERTY(cBTConditionalNode, weak_ptr<CLASS>, Holder)
			DEFINE_NODE_PROPERTY(cBTConditionalNode, Getter, Function)
			DEFINE_NODE_PROPERTY(cBTConditionalNode, float, Value)
			DEFINE_NODE_PROPERTY(cBTConditionalNode, ConditionalOperators::Enum, TestType)

	public:
		~cBTConditionalNode(){};
		BT_STATUS::Enum VOnUpdate(void * pOwner);

	private:
		cBTConditionalNode()
			: m_TestType(ConditionalOperators::Equal)
		{
		}

	private:
		friend class cBTNodeFactory;

	};

	//  ********************************************************************************************************************
	template <class CLASS>
	BT_STATUS::Enum cBTConditionalNode<float, CLASS>::VOnUpdate(void * pOwner)
	{
		if (m_Holder.expired())
		{
			return BT_STATUS::Failure;
		}
		shared_ptr<CLASS> pHolder = MakeStrongPtr(m_Holder);

		bool status = false;
		float value = 0.0f;
		switch(m_TestType)
		{
		case ConditionalOperators::Equal:
			status = isEqual((pHolder.get()->*m_Function)(), m_Value);
			break;
		case ConditionalOperators::NotEqual:
			status = !isEqual((pHolder.get()->*m_Function)(), m_Value);
			break;
		case ConditionalOperators::LessThan:
			status = (m_Value - (pHolder.get()->*m_Function)() > EpsilonFloat);
			break;
		case  ConditionalOperators::LessOrEqual:
			value = (m_Value - (pHolder.get()->*m_Function)());
			status = isEqual(value, 0.0f) || (value > EpsilonFloat);
			break;
		case ConditionalOperators::GreaterThan:
			status = (((pHolder.get()->*m_Function)() - m_Value) > EpsilonFloat);
			break;
		case ConditionalOperators::GreaterOrEqual:
			value = (pHolder.get()->*m_Function)() - m_Value;
			status = isEqual(value, 0.0f) || (value >= EpsilonFloat);
			break;
		};

		if (status)
		{
			return BT_STATUS::Success;
		}
		else
		{
			return BT_STATUS::Failure;
		}
	}
}
#endif  // __BTCONDITIONAL_H__
