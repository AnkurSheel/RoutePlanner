// *****************************************************************************
//  EntityMovedEventData version:  1.0   Ankur Sheel  date: 2013/07/25
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef EntityMovedEventData_h__
#define EntityMovedEventData_h__

#include "BaseEventData.h"
#include "vector3.h"

namespace GameBase
{
	class cEntityMovedEventData
		: public cBaseEventData
	{
	public:
		cEntityMovedEventData();
		cEntityMovedEventData(const Base::cVector3 & position, const int actorID);
		~cEntityMovedEventData();
		unsigned long VGetHashedID() const { return m_Name.GetHash(); }
		virtual Base::cString VGetName() const { return m_Name.GetString(); }
		int GetActorID() const { return m_ActorID; }
		Base::cVector3 GetPosition() const { return m_Position; }

	public:
		static Base::cHashedString m_Name;

	private:
		Base::cVector3	m_Position;
		int				m_ActorID;
	};
}
#endif //EntityMovedEventData_h__