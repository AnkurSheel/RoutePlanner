#include "stdafx.h"
#include "BTCompositeNode.h"

using namespace AI;
using namespace Base;

//  ********************************************************************************************************************
cBTCompositeNode::cBTCompositeNode()
{

}

//  ********************************************************************************************************************
cBTCompositeNode::~cBTCompositeNode()
{
	for (auto iter = m_Children.begin(); iter!= m_Children.end(); iter++)
	{
		(*iter).reset();
	}
	m_Children.clear();
}

//  ********************************************************************************************************************
void cBTCompositeNode::VRemoveChild(BTNodeWeakPtr pChild)
{
	BTNodeStrongPtr pChildStrongPtr = MakeStrongPtr(pChild);
	if (pChildStrongPtr)
	{
		//m_Children.remove(pChildStrongPtr);
		for (auto iter = m_Children.begin(); iter != m_Children.end(); iter++)
		{
			if ((*iter) == pChildStrongPtr)
			{
				pChildStrongPtr->SetParent(NULL);
				m_Children.erase(iter);
				break;
			}
		}
	}
}

//  ********************************************************************************************************************
void cBTCompositeNode::VRemoveChildren()
{
	m_Children.clear();
}

//  ********************************************************************************************************************
BTNodeWeakPtr cBTCompositeNode::GetChildAt(int index)
{
	SP_ASSERT(index < m_Children.size())(index)(m_Children.size()).SetCustomMessage("Invalid Index");
	return m_Children[index];
}

//  *******************************************************************************************************************
void cBTCompositeNode::VReset()
{
	m_ReturnStatus = BT_STATUS::Invalid;
	for (auto iter = m_Children.begin(); iter != m_Children.end(); iter++)
	{
		(*iter)->VReset();
	}
}
