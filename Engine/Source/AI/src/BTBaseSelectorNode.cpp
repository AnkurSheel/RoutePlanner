#include "stdafx.h"
#include "BTBaseSelectorNode.h"

using namespace AI;
using namespace Base;


//  *******************************************************************************************************************
cBTBaseSelectorNode::cBTBaseSelectorNode()
	: m_CurrentChildIndex(-1)
{

}

//  ********************************************************************************************************************
cBTBaseSelectorNode::~cBTBaseSelectorNode()
{

}

//  ********************************************************************************************************************
void cBTBaseSelectorNode::VOnInitialize(void * pOwner)
{
	VCalculateNextChildIndex();
}

//  ********************************************************************************************************************
BT_STATUS::Enum cBTBaseSelectorNode::VOnUpdate(void * pOwner)
{
	SP_ASSERT(m_CurrentChildIndex >= m_Children.size())(m_CurrentChildIndex).SetCustomMessage("Trying to execute without calling Initialize");
	SP_ASSERT(m_Children.size() > 0).SetCustomMessage("Priority Node should have atleast 1 child");
	if (m_Children.size() == 0 || m_CurrentChildIndex >= m_Children.size())
	{
		return BT_STATUS::Invalid;
	}

	BTNodeStrongPtr pChild = MakeStrongPtr(GetChildAt(m_CurrentChildIndex));
	SP_ASSERT(pChild != NULL)(m_CurrentChildIndex).SetCustomMessage("Something went wrong, Child was NULL");
	if (pChild != NULL)
	{
		m_ReturnStatus = pChild->Tick(pOwner);
		if (m_ReturnStatus == BT_STATUS::Failure)
		{
			VCalculateNextChildIndex();
			if (VDone())
			{
				VOnInitialize(pOwner);
			}
			else
			{
				m_ReturnStatus = BT_STATUS::Running;
			}
		}
		else if (m_ReturnStatus == BT_STATUS::Success)
		{
			VOnInitialize(pOwner);
		}
	}
	return m_ReturnStatus;
}
