//  *******************************************************************************************************************
//  MessageDispatchManager   version:  1.0   Ankur Sheel  date: 2012/07/31
//  *******************************************************************************************************************
// 
//  *******************************************************************************************************************
#ifndef MESSAGEDISPATCHMANAGER_HXX__
#define MESSAGEDISPATCHMANAGER_HXX__

#include "GameBaseDefines.h"

namespace GameBase
{
	class IMessageDispatchManager
	{
	public:
		virtual ~IMessageDispatchManager(){}
		virtual void VDispatchMessage(const double delay, const int senderID, const int recieverID, const unsigned msgId, shared_ptr<void> pExtraInfo) = 0;
		virtual void VOnUpdate() = 0;
		static void CreateAsService();
	};
}
#endif // MessageDispatchManager_hxx__
