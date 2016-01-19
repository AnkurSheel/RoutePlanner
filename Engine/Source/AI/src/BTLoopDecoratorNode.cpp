#include "stdafx.h"
#include "BTLoopDecoratorNode.h"

using namespace AI;

//  ********************************************************************************************************************
AI::cBTLoopDecoratorNode::cBTLoopDecoratorNode()
	: m_Count(0)
{

}

//  ********************************************************************************************************************
cBTLoopDecoratorNode::~cBTLoopDecoratorNode()
{

}

//  ********************************************************************************************************************
void cBTLoopDecoratorNode::VOnInitialize(void * pOwner)
{
	m_Count = 0;
	cBTDecoratorNode::VOnInitialize(pOwner);
}

//  ********************************************************************************************************************
BT_STATUS::Enum cBTLoopDecoratorNode::VOnUpdate(void * pOwner)
{
	BT_STATUS::Enum result = BT_STATUS::Invalid;
	SP_ASSERT(m_Initialized).SetCustomMessage("Trying to execute without calling Initialize");
	SP_ASSERT(m_pChild != NULL).SetCustomMessage("Decorator should have 1 child");

	if (!m_Initialized || m_pChild == NULL)
	{
		return result;
	}

	if (m_pChild != NULL)
	{
		result = m_pChild->Tick(pOwner);
		if (result == BT_STATUS::Success)
		{
			m_Count++;
			if (m_Repeats.IsInvalid() || m_Count == m_Repeats.GetValue())
			{
				VOnInitialize(pOwner);
				return BT_STATUS::Success;
			}
			else
			{
				return BT_STATUS::Running;
			}
		}
	}
	return result;
}
