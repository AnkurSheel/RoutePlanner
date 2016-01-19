#include "stdafx.h"
#include "MockBTNode.h"

using namespace testing;

//  *******************************************************************************************************************
cMockBTNode::cMockBTNode() 
	: m_InitializeCalled(0)
	, m_UpdateCalled(0)
	, m_TerminateCalled(0)
{

}
//  *******************************************************************************************************************
void cMockBTNode::DelegateToFake()
{
	ON_CALL(*this, VOnInitialize(_))
		.WillByDefault(Invoke(this, &cMockBTNode::Enter));
	ON_CALL(*this, VOnUpdate(_))
		.WillByDefault(Invoke(this, &cMockBTNode::Execute));
	ON_CALL(*this, VOnTerminate(_))
		.WillByDefault(Invoke(this, &cMockBTNode::Exit));
}

//  *******************************************************************************************************************
void cMockBTNode::Enter(void * pOwner)
{
	++m_InitializeCalled;
	m_ReturnStatus = BT_STATUS::Running;
}

//  *******************************************************************************************************************
BT_STATUS::Enum cMockBTNode::Execute(void * pOwner)
{
	++m_UpdateCalled;
	return m_ReturnStatus;
}
//  *******************************************************************************************************************
void cMockBTNode::Exit(const BT_STATUS::Enum status)
{
	++m_TerminateCalled;
	m_TerminateStatus = status;
}
