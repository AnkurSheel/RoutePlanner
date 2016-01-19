//  *******************************************************************************************************************
//  PrintTextNode   version:  1.0   Ankur Sheel  date: 2014/12/10
//  *******************************************************************************************************************
// 
//  *******************************************************************************************************************
#ifndef __PRINTTEXTNODE_H__
#define __PRINTTEXTNODE_H__

#include "BTBehavior.h"

class cPrintTextNode
	: public AI::cBTBehavior
{
	DEFINE_NODE_PROPERTY(cPrintTextNode, Base::cString, Text)

public:
	cPrintTextNode();
	~cPrintTextNode();
	void VOnInitialize(void * pOwner);
	AI::BT_STATUS::Enum VOnUpdate(void * pOwner);
};
#endif  // __PRINTTEXTNODE_H__
