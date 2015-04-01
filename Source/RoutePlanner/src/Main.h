// ********************************************************************************************************************
//  Main   version:  1.0   Ankur Sheel  date: 2013/04/02
// ********************************************************************************************************************
//  purpose:	
// ********************************************************************************************************************
#ifndef Main_h__
#define Main_h__

struct WaypointData
{
	Base::cString m_Waypoint1;
	Base::cString m_Waypoint2;
	int m_Distance;
	int m_Duration;
};

typedef std::map<unsigned long, WaypointData> WaypointDataMap;
#endif // Main_h__
