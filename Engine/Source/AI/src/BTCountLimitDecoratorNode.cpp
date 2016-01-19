#include "stdafx.h"
#include "BTCountLimitDecoratorNode.h"

using namespace AI;

//  ********************************************************************************************************************
cBTCountLimitDecoratorNode::cBTCountLimitDecoratorNode()
: m_Count(0)
, m_Limit(0)
, m_AllowReinitialize(true)
{

}

//  ********************************************************************************************************************
cBTCountLimitDecoratorNode::~cBTCountLimitDecoratorNode()
{

}

//  ********************************************************************************************************************
void cBTCountLimitDecoratorNode::VOnInitialize(void * pOwner)
{
	if (!m_Initialized || ( m_AllowReinitialize && m_Count == m_Limit))
	{
		m_Count = 0;
		cBTDecoratorNode::VOnInitialize(pOwner);
	}
}

//  ********************************************************************************************************************
BT_STATUS::Enum cBTCountLimitDecoratorNode::VOnUpdate(void * pOwner)
{
	BT_STATUS::Enum result = BT_STATUS::Invalid;
	SP_ASSERT(m_Initialized).SetCustomMessage("Trying to execute without calling Initialize");
	SP_ASSERT(m_pChild != NULL).SetCustomMessage("Decorator should have 1 child");

	if (!m_Initialized || m_pChild == NULL)
	{
		return result;
	}

	if (m_Count == m_Limit)
	{
		return BT_STATUS::Failure;
	}
	else
	{
		result = m_pChild->Tick(pOwner);
		if (result == BT_STATUS::Success || result == BT_STATUS::Failure)
		{
			m_Count++;
			cBTDecoratorNode::VOnInitialize(pOwner);
		}
	}
	return result;
}
