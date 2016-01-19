//  *******************************************************************************************************************
//  BTParallelNode   version:  1.0   Ankur Sheel  date: 2014/12/10
//  *******************************************************************************************************************
// 
//  *******************************************************************************************************************
#ifndef __BTPARALLELNODE_H__
#define __BTPARALLELNODE_H__
#include "AIDefines.h"
#include "BTCompositeNode.h"

namespace AI
{
	class cBTParallelNode
		: public cBTCompositeNode
	{
		DEFINE_NODE_PROPERTY(cBTParallelNode, BT_POLICY::Enum, SuccessPolicy)
		DEFINE_NODE_PROPERTY(cBTParallelNode, BT_POLICY::Enum, FailurePolicy)

	public:
		AI_API cBTParallelNode();
		~cBTParallelNode();
		void VOnInitialize(void * pOwner);
		BT_STATUS::Enum VOnUpdate(void * pOwner);
		void VOnTerminate(const BT_STATUS::Enum status);

	private:
		bool  m_Initialized;
		std::vector<BT_STATUS::Enum> m_ChildrenStatus;
	};
}
#endif  // __BTPARALLELNODE_H__
