//  *******************************************************************************************************************
//  EntityInitializedEventData version:  1.0   Ankur Sheel  date: 2013/07/25
//  *******************************************************************************************************************
//  purpose:	
//  *******************************************************************************************************************
#ifndef EntityInitializedEventData_h__
#define EntityInitializedEventData_h__

#include "BaseEventData.h"
#include "vector3.h"

namespace GameBase
{
	class cEntityInitializedEventData
		: public cBaseEventData
	{
	public:
		cEntityInitializedEventData();
		cEntityInitializedEventData(const Base::cVector3 & position, const Base::cVector3 & rotation,
			const Base::cVector3 & size, const bool ReInitializing,	const int actorID);
		~cEntityInitializedEventData();
		unsigned long VGetHashedID() const { return m_Name.GetHash(); }
		virtual Base::cString VGetName() const { return m_Name.GetString(); }
		int GetActorID() const { return m_ActorID; }
		Base::cVector3 GetPosition() const { return m_Position; }
		Base::cVector3 GetRotation() const { return m_Rotation; }
		Base::cVector3 GetSize() const { return m_Size; }
		bool IsReInitializing() const { return m_ReInitializing; }
	public:
		static Base::cHashedString m_Name;

	private:
		Base::cVector3	m_Position;
		Base::cVector3	m_Rotation;
		Base::cVector3	m_Size;
		int				m_ActorID;
		bool			m_ReInitializing;
	};
}
#endif //EntityInitializedEventData_h__