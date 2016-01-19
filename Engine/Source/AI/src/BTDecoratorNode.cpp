#include "stdafx.h"
#include "BTDecoratorNode.h"

using namespace AI;
using namespace Base;
//  ********************************************************************************************************************
cBTDecoratorNode::cBTDecoratorNode()
	: m_pChild(NULL)
	, m_Initialized(false)
{

}

//  ********************************************************************************************************************
cBTDecoratorNode::~cBTDecoratorNode()
{

}

//  ********************************************************************************************************************
void cBTDecoratorNode::VOnInitialize(void * pOwner)
{
	//SP_ASSERT(m_pChild != NULL).SetCustomMessage("Something went wrong, Child was NULL");
	//if (m_pChild != NULL)
	//{
	//	m_pChild->VOnEnter(pOwner);
		m_Initialized = true;
	//}
}

//  ********************************************************************************************************************
BT_STATUS::Enum cBTDecoratorNode::VOnUpdate(void * pOwner)
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
	}
	return result;
}
