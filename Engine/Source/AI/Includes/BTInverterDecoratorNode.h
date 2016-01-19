//  *******************************************************************************************************************
//  BTInverterDecoratorNode   version:  1.0   Ankur Sheel  date: 2014/12/31
//  *******************************************************************************************************************
// 
//  *******************************************************************************************************************
#ifndef __BTINVERTERDECORATORNODE_H__
#define __BTINVERTERDECORATORNODE_H__

#include "BTDecoratorNode.h"

namespace AI
{
	class cBTInverterDecoratorNode
	: public cBTDecoratorNode
	{
	public:
		~cBTInverterDecoratorNode();
		BT_STATUS::Enum VOnUpdate(void * pOwner);

	private:
		AI_API cBTInverterDecoratorNode();

		friend class cBTNodeFactory;
	};
} 
#endif  // __BTINVERTERDECORATORNODE_H__

