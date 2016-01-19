#include "stdafx.h"
#include "BTPrioritySelectorNode.h"

using namespace AI;
using namespace Base;

//  ********************************************************************************************************************
cBTPrioritySelectorNode::cBTPrioritySelectorNode()
{
}

//  ********************************************************************************************************************
cBTPrioritySelectorNode::~cBTPrioritySelectorNode()
{
}

//  ********************************************************************************************************************
void cBTPrioritySelectorNode::VCalculateNextChildIndex()
{
	m_CurrentChildIndex++;
}

//  ********************************************************************************************************************
bool cBTPrioritySelectorNode::VDone()
{
	return m_CurrentChildIndex == m_Children.size();
}
