// ********************************************************************************************************************
//  Main   version:  1.0   Ankur Sheel  date: 2013/04/02
// ********************************************************************************************************************
//  purpose:	
// ********************************************************************************************************************
#ifndef Main_h__
#define Main_h__

struct WaypointData
{
	struct DistanceTimeData
	{
		Base::cHashedString m_ToWaypoint;
		unsigned long m_Distance;
		unsigned long m_Duration;
	};
	typedef std::map<unsigned long, DistanceTimeData> DistanceTimeMap;

	Base::cHashedString m_WaypointName;
	DistanceTimeMap m_DistanceTimeMap;
};

typedef std::map<unsigned long, WaypointData> WaypointDataMap;
#endif // Main_h__
