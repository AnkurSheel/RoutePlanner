#include "stdafx.h"
#include "BTParallelNode.h"

using namespace AI;
using namespace Base;

//  ********************************************************************************************************************
cBTParallelNode::cBTParallelNode()
	: m_Initialized(false)
	, m_SuccessPolicy(BT_POLICY::RequireAll)
	, m_FailurePolicy(BT_POLICY::RequireOne)
{
}

//  ********************************************************************************************************************
cBTParallelNode::~cBTParallelNode()
{

}

//  ********************************************************************************************************************
void cBTParallelNode::VOnInitialize(void * pOwner)
{
	m_ChildrenStatus.clear();
	m_ChildrenStatus.reserve(m_Children.size());
	for(int i=0; i< m_Children.size(); i++)
	{
		//BTNodeStrongPtr pChild = m_Children[i];
		//SP_ASSERT(pChild != NULL).SetCustomMessage("Something went wrong, Child was NULL");
		//if (pChild != NULL)
		//{
		//	pChild->VOnEnter(pOwner);
		//}
		m_ChildrenStatus.push_back(BT_STATUS::Running);
	}
	SP_ASSERT(m_Children.size() == m_ChildrenStatus.size())(m_Children.size())(m_ChildrenStatus.size())("Size of children and status does not match");
	m_Initialized = true;
}

//  ********************************************************************************************************************
BT_STATUS::Enum cBTParallelNode::VOnUpdate(void * pOwner)
{
	SP_ASSERT(m_Initialized).SetCustomMessage("Trying to execute without calling Initialize");
	SP_ASSERT(m_Children.size() > 0).SetCustomMessage("Sequence should have atleast 1 child");
	if (!m_Initialized || m_Children.size() == 0)
	{
		return BT_STATUS::Invalid;
	}

	for(int i = 0; i< m_Children.size(); i++)
	{
		BTNodeStrongPtr pChild = m_Children[i];
		if (pChild != NULL)
		{
			if (m_ChildrenStatus[i] == BT_STATUS::Running)
			{
				BT_STATUS::Enum result = pChild->Tick(pOwner);
				m_ChildrenStatus[i] = result;
				if (result == BT_STATUS::Invalid)
				{
					return BT_STATUS::Invalid;
				}
				else if (result == BT_STATUS::Failure && m_FailurePolicy == BT_POLICY::RequireOne)
				{
					return BT_STATUS::Failure;
				}
			}
		}
	}

	bool sawSuccess = false;
	bool sawAllFails = true;
	bool sawAllSuccess = true;
	for(int i=0; i< m_ChildrenStatus.size(); i++)
	{
		if (m_ChildrenStatus[i] == BT_STATUS::Success)
		{
			if (m_SuccessPolicy == BT_POLICY::RequireOne && m_FailurePolicy != BT_POLICY::RequireOne)
			{
				return BT_STATUS::Success;
			}
			sawSuccess = true;
			sawAllFails = false;
			m_ChildrenStatus[i] = BT_STATUS::Running;
		}
		else if (m_ChildrenStatus[i] == BT_STATUS::Failure)
		{
			sawAllSuccess = false;
		}
		else if (m_ChildrenStatus[i] == BT_STATUS::Running)
		{
			sawAllFails = false;
			sawAllSuccess = false;
			if (m_SuccessPolicy == BT_POLICY::RequireAll && m_FailurePolicy == BT_POLICY::RequireAll)
			{
				return BT_STATUS::Running;
			}
		}
	}
	if (sawAllFails && m_FailurePolicy == BT_POLICY::RequireAll)
	{
		return BT_STATUS::Failure;
	}
	else if(sawAllSuccess && m_SuccessPolicy == BT_POLICY::RequireAll)
	{
		return BT_STATUS::Success;
	}
	return BT_STATUS::Running;
}

//  *******************************************************************************************************************
void cBTParallelNode::VOnTerminate( const BT_STATUS::Enum status )
{
	for (auto iter = m_Children.begin(); iter != m_Children.end(); iter++)
	{
		BTNodeStrongPtr pChild = *iter;
		if (pChild->IsRunning())
		{
			pChild->Abort();
		}
	}
}
