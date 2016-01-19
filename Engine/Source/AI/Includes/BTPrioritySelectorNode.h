//  *******************************************************************************************************************
//  BTPrioritySelector   version:  1.0   Ankur Sheel  date: 2014/12/19
//  *******************************************************************************************************************
// 
//  *******************************************************************************************************************
#ifndef __BTPRIORITYSELECTOR_H__
#define __BTPRIORITYSELECTOR_H__

#include "AIDefines.h"
#include "BTBaseSelectorNode.h"

namespace AI
{
	class cBTNodeFactory;
}

namespace AI
{

	class cBTPrioritySelectorNode
	: public cBTBaseSelectorNode
	{
	public:
		~cBTPrioritySelectorNode();

	private:
		AI_API cBTPrioritySelectorNode();
		void VCalculateNextChildIndex();
		bool VDone();

		friend class cBTNodeFactory;
	};
}
#endif  // __BTPRIORITYSELECTOR_H__
