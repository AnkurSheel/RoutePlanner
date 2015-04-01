#include "stdafx.h"
#include "Main.h"
#include "vld.h"
#include "FileIO.hxx"
#include "Optional.h"
#include "GeneticAlgorithm.h"
#include "ServiceLocator.h"
#include "Logger.hxx"
#include "SpAssertSettings.hxx"
#include "conio.h"
#include "Timer.hxx"
#include "iostream"

using namespace Base;
using namespace Utilities;
using namespace std;

//// ***************************************************************
//-// Checks for memory leaks
//  -// ***************************************************************
//  -void CheckForMemoryLeaks() 
//  -{
//    -#ifdef	_DEBUG
//      -	// Get Current flag
//      -	int flag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) ; 
//    -
//      -	// Turn on leak-checking bit
//      -	flag |= (_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF) ; 
//    -
//      -	// Set flag to the new value
//      -	_CrtSetDbgFlag(flag) ; 
//    -#endif	_DEBUG
//      -}

void ReadWaypointData(WaypointDataMap &waypoints, std::vector<cHashedString>& waypointNames);
void AddtoWaypointMapData(WaypointDataMap &waypoints, const cHashedString &fromWaypoint, const cHashedString &toWaypoint, const unsigned long distance, const unsigned long duration);


//  *******************************************************************************************************************
int main()
{
	WaypointDataMap waypoints;
	std::vector<cHashedString> waypointNames;
	ITimer * pTimer = ITimer::CreateTimer();
	pTimer->VStartTimer();

	int hour, min, sec;

	ReadWaypointData(waypoints, waypointNames);
	pTimer->VStopTimer();
	Base::GetTimeAsHHMMSS(pTimer->VGetRunningTime(), hour, min, sec);
	::OutputDebugString(cStringUtilities::MakeFormatted("Time to read in data: %02d:%02d:%02d\n", hour, min, sec).GetData());
	cGeneticAlgorithm algo(5000, 100, 0.90f, 0.20f, 10000);
	algo.SetWayPointNames(waypointNames);

	pTimer->VReset();
	pTimer->VStartTimer();
	algo.RunGeneticAlgorithmType1(waypoints);
	pTimer->VStopTimer();
	Base::GetTimeAsHHMMSS(pTimer->VGetRunningTime(), hour, min, sec);
	::OutputDebugString(cStringUtilities::MakeFormatted("Time to RunGeneticAlgorithmType1: %02d:%02d:%02d\n", hour, min, sec).GetData());

	pTimer->VReset();
	pTimer->VStartTimer();
	algo.RunGeneticAlgorithmType2(waypoints);
	pTimer->VStopTimer();
	Base::GetTimeAsHHMMSS(pTimer->VGetRunningTime(), hour, min, sec);
	::OutputDebugString(cStringUtilities::MakeFormatted("Time to RunGeneticAlgorithmType2: %02d:%02d:%02d\n", hour, min, sec).GetData());

	pTimer->VReset();
	pTimer->VStartTimer();
	algo.RunGeneticAlgorithmType3(waypoints);
	pTimer->VStopTimer();
	Base::GetTimeAsHHMMSS(pTimer->VGetRunningTime(), hour, min, sec);
	::OutputDebugString(cStringUtilities::MakeFormatted("Time to RunGeneticAlgorithmType3: %02d:%02d:%02d\n", hour, min, sec).GetData());

	//_CrtDumpMemoryLeaks()

	SafeDelete(&pTimer);
	cServiceLocator::Destroy();
	getch();
	return 0;
}

//  *******************************************************************************************************************
void AddtoWaypointMapData(WaypointDataMap &waypoints, const cHashedString &fromWaypoint, const cHashedString &toWaypoint, const unsigned long distance, const unsigned long duration)
{
	WaypointData data1;

	auto iter = waypoints.find(fromWaypoint.GetHash());
	if (iter == waypoints.end())
	{
		data1.m_WaypointName = cHashedString(fromWaypoint);
		waypoints.insert(std::pair<unsigned long, WaypointData>(data1.m_WaypointName.GetHash(), data1));
	}
	else
	{
		data1 = iter->second;
	}

	WaypointData::DistanceTimeData dtData;
	auto iter1= data1.m_DistanceTimeMap.find(toWaypoint.GetHash());
	SP_ASSERT_ERROR(iter1 == data1.m_DistanceTimeMap.end())(data1.m_WaypointName.GetString())(toWaypoint.GetString()).SetCustomMessage("Duplicate Entry Found for Distance Time Map");
	if (iter1 == data1.m_DistanceTimeMap.end())
	{
		dtData.m_ToWaypoint = toWaypoint;
		dtData.m_Distance = distance;
		dtData.m_Duration = duration;
		data1.m_DistanceTimeMap.insert(std::pair<unsigned long, WaypointData::DistanceTimeData>(dtData.m_ToWaypoint.GetHash(), dtData));
	}
	else
	{
		int a = 5;
	}
	waypoints[data1.m_WaypointName.GetHash()] = data1;
}

//  *******************************************************************************************************************
void ReadWaypointData(WaypointDataMap &waypoints, std::vector<cHashedString>& waypointNames)
{
	IFileIO* m_pFile = IFileIO::CreateFileIO();
	if(m_pFile->VOpenFile("my-waypoints-dist-dur.csv", std::ios_base::in))
	{
		m_pFile->VReadLine(); // disregard 1st line

		std::vector<cString> tokens;
		WaypointData data2;
		cString m_Buffer = m_pFile->VReadLine();

		while(!m_pFile->VIsEOF() || !m_Buffer.IsEmpty())
		{
			tokens.clear();
			m_Buffer.Tokenize("\t", tokens);

			cHashedString waypointName1(tokens[0]);
			cHashedString waypointName2(tokens[1]);
			unsigned long distance = tokens[2].ToInt().GetValue();
			unsigned long duration = tokens[3].ToInt().GetValue();

			AddtoWaypointMapData(waypoints, waypointName1, waypointName2, distance, duration);
			AddtoWaypointMapData(waypoints, waypointName2, waypointName1, distance, duration);

			m_Buffer = m_pFile->VReadLine();
			cHashedString name = cHashedString(tokens[0]);
			if (find(waypointNames.begin(), waypointNames.end(), name) == waypointNames.end())
			{
				waypointNames.push_back(name);
			}

		}
		m_pFile->VCloseFile();
		SafeDelete(&m_pFile);
	}
}
