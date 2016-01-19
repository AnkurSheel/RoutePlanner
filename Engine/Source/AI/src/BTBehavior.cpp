#include "stdafx.h"
#include <BTBehavior.h>

using namespace AI;
using namespace Base;

//  ********************************************************************************************************************
cBTBehavior::cBTBehavior()
	: m_ReturnStatus(BT_STATUS::Invalid)
	, m_TerminateStatus(BT_STATUS::Invalid)
{

}

//  ********************************************************************************************************************
cBTBehavior::~cBTBehavior()
{

}

//  ********************************************************************************************************************
void cBTBehavior::VOnInitialize(void * pOwner)
{
	SP_ASSERT(false).SetCustomMessage("The method or operation is not implemented.");
}

//  ********************************************************************************************************************
BT_STATUS::Enum cBTBehavior::Tick(void * pOwner)
{
	if (m_ReturnStatus == BT_STATUS::Invalid)
	{
		VOnInitialize(pOwner);
	}

	m_ReturnStatus = VOnUpdate(pOwner);
	if (m_ReturnStatus != BT_STATUS::Running)
	{
		VOnTerminate(m_ReturnStatus);
	}
	return m_ReturnStatus;
}

//  ********************************************************************************************************************
void cBTBehavior::VOnTerminate(const BT_STATUS::Enum status)
{
	m_TerminateStatus = status;
}

//  *******************************************************************************************************************
void AI::cBTBehavior::Abort()
{
	VOnTerminate(BT_STATUS::Aborted);
	m_ReturnStatus = BT_STATUS::Aborted;
}
