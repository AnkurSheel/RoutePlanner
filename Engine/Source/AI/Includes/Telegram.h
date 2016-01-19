// ***************************************************************
//  Telegram   version:  1.0   Ankur Sheel  date: 05/23/2008
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef Telegram_h__
#define Telegram_h__

#include <math.h>

namespace AI
{
	struct Telegram
	{
		unsigned int m_SenderID;
		unsigned int m_ReceiverID;
		unsigned int m_MsgID;
		double m_DispatchTime;
		std::tr1::shared_ptr<void> m_pExtraInfo;

		Telegram()
		: m_SenderID(0)
		, m_ReceiverID(0)
		, m_MsgID(0) 
		, m_DispatchTime(-1)
		, m_pExtraInfo(NULL)
		{
		}
		
		Telegram(unsigned int senderID, unsigned int receiverID, unsigned int msgID, double dispatchTime, shared_ptr<void> pExtraInfo)
		: m_SenderID(senderID)
		, m_ReceiverID(receiverID)
		, m_MsgID(msgID)
		, m_DispatchTime(dispatchTime)
		, m_pExtraInfo(pExtraInfo)
		{
		}
	};

	const double SmallestDelay = 0.25;

	inline bool operator==(const Telegram &t1, const Telegram &t2)
	{
		return ( (t1.m_SenderID == t2.m_SenderID)
			&& (t1.m_ReceiverID == t2.m_ReceiverID)
			&& (t1.m_MsgID == t2.m_MsgID)
			&& fabs(t1.m_DispatchTime - t2.m_DispatchTime) < SmallestDelay);
	}

	inline bool operator<(const Telegram &t1, const Telegram &t2)
	{
		if (t1 == t2)
		{
			return false;
		}

		else
		{
			return  (t1.m_DispatchTime < t2.m_DispatchTime);
		}
	}
}
#endif // Telegram_h__