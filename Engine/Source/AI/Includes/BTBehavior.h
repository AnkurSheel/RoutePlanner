//  *******************************************************************************************************************
//  BTNode   version:  1.0   Ankur Sheel  date: 2014/12/09
//  *******************************************************************************************************************
// 
//  *******************************************************************************************************************
#ifndef __BTNODE_H__
#define __BTNODE_H__

#include "AIDefines.h"
#include "BTFwd.h"

namespace AI
{
	class cBTBehavior
		: public std::enable_shared_from_this<cBTBehavior>
	{
	public:
		AI_API virtual ~cBTBehavior();
		BTNodeWeakPtr GetParent() const { return m_pParent; }
		void SetParent(BTNodeStrongPtr val) { m_pParent = val; }
		AI_API BT_STATUS::Enum Tick(void * pOwner);
		void Abort();
		bool IsRunning() { return m_ReturnStatus == BT_STATUS::Running; }
    virtual void VReset() { m_ReturnStatus = BT_STATUS::Invalid; }

		template <class ANCESTOR> 
		shared_ptr<ANCESTOR> FindAncestor();

	protected:
		AI_API cBTBehavior();
		AI_API virtual void VOnInitialize(void * pOwner);
		virtual BT_STATUS::Enum VOnUpdate(void * pOwner){ return BT_STATUS::Invalid; }
		AI_API virtual void VOnTerminate(const BT_STATUS::Enum status);

	protected:
		BTNodeWeakPtr m_pParent;
		BT_STATUS::Enum m_ReturnStatus;
		BT_STATUS::Enum m_TerminateStatus;

		friend class cBTNodeFactory;
	};

	//  ********************************************************************************************************************
	template <class ANCESTOR>
	shared_ptr<ANCESTOR> cBTBehavior::FindAncestor()
	{
		BTNodeStrongPtr pNode = MakeStrongPtr(m_pParent);
		if (pNode != NULL)
		{
			shared_ptr<T> pAncestor = NULL;
			while (pNode != NULL &&  pAncestor == NULL)
			{
				pAncestor = dynamic_pointer_cast<T>(pNode);
				pNode = pNode->getParent();
			}
			return pAncestor;
		}
	}
}
#endif  // __BTNODE_H__
