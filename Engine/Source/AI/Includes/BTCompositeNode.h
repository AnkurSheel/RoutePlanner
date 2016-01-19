//  *******************************************************************************************************************
//  BTCompositeNode   version:  1.0   Ankur Sheel  date: 2014/12/09
//  *******************************************************************************************************************
// 
//  *******************************************************************************************************************
#ifndef __BTCOMPOSITENODE_H__
#define __BTCOMPOSITENODE_H__

#include "BTBehavior.h"

namespace AI
{
	class cBTCompositeNode
		: public cBTBehavior
	{
	public:
		virtual ~cBTCompositeNode();
		virtual void VRemoveChild(BTNodeWeakPtr pChild);
		virtual void VRemoveChildren();
		int GetChildCount() const { return m_Children.size(); }
		AI_API BTNodeWeakPtr GetChildAt(int index);
		void VReset() OVERRIDE;

		template<class T>
		shared_ptr<T> AddChild(BTNodeWeakPtr pChild);

	protected:
		cBTCompositeNode();

	protected:
		BTNodes m_Children;
	};

	//  ***************************************************************************************************************
	template<class PARENT>
	shared_ptr<PARENT> cBTCompositeNode::AddChild(BTNodeWeakPtr pChild)
	{
		BTNodeStrongPtr pChildStrongPtr = MakeStrongPtr(pChild);
		BTNodeStrongPtr pThisPtr = shared_from_this();
		if (pChildStrongPtr)
		{
			m_Children.push_back(pChildStrongPtr);
			pChildStrongPtr->SetParent(pThisPtr);
		}
		return dynamic_pointer_cast<PARENT>(pThisPtr);
	}
}
#endif  // __BTCOMPOSITENODE_H__
