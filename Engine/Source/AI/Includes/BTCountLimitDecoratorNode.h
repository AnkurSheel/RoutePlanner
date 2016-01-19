//  *******************************************************************************************************************
//  BTCountLimitNode   version:  1.0   Ankur Sheel  date: 2014/12/31
//  *******************************************************************************************************************
// 
//  *******************************************************************************************************************
#ifndef __BTCOUNTLIMITNODE_H__
#define __BTCOUNTLIMITNODE_H__

#include "BTDecoratorNode.h"

namespace AI
{
	class cBTCountLimitDecoratorNode
	: public cBTDecoratorNode
	{
		DEFINE_NODE_PROPERTY(cBTCountLimitDecoratorNode, int, Limit)
		DEFINE_NODE_PROPERTY(cBTCountLimitDecoratorNode, bool, AllowReinitialize)

	public:
		~cBTCountLimitDecoratorNode();
		void VOnInitialize(void * pOwner);
		BT_STATUS::Enum VOnUpdate(void * pOwner);

	private:
		AI_API cBTCountLimitDecoratorNode();

	private:
		int m_Count;

		friend class cBTNodeFactory;
	};
}
#endif  // __BTCOUNTLIMITNODE_H__
