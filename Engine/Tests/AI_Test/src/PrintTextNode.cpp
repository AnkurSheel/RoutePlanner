#include "stdafx.h"
#include "PrintTextNode.h"

using namespace AI;
using namespace Base;

//  ********************************************************************************************************************
cPrintTextNode::cPrintTextNode()
{
}

//  ********************************************************************************************************************
cPrintTextNode::~cPrintTextNode()
{
}

//  ********************************************************************************************************************
void cPrintTextNode::VOnInitialize(void * pOwner)
{

}

//  ********************************************************************************************************************
BT_STATUS::Enum cPrintTextNode::VOnUpdate(void * pOwner)
{
	std::cout << m_Text << std::endl;
	return BT_STATUS::Success;
}
