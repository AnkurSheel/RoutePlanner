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

void ReadWaypointData(WaypointDataMap &waypoints, std::vector<cString>& waypointNames);


//  *******************************************************************************************************************
int main()
{

	WaypointDataMap waypoints;
	std::vector<cString> waypointNames;
	ITimer * pTimer = ITimer::CreateTimer();
	pTimer->VStartTimer();

	int hour, min, sec;



	ReadWaypointData(waypoints, waypointNames);
	pTimer->VStopTimer();
	Base::GetTimeAsHHMMSS(pTimer->VGetRunningTime(), hour, min, sec);;
	::OutputDebugString(cStringUtilities::MakeFormatted("Time to read in data: %02d:%02d:%02d\n", hour, min, sec).GetData());
	cGeneticAlgorithm algo(5000, 100, 0.90f, 0.20f, 10000);

	pTimer->VReset();
	pTimer->VStartTimer();
	algo.RunGeneticAlgorithmType1(waypoints, waypointNames);
	pTimer->VStopTimer();
	Base::GetTimeAsHHMMSS(pTimer->VGetRunningTime(), hour, min, sec);;
	::OutputDebugString(cStringUtilities::MakeFormatted("Time to RunGeneticAlgorithmType1: %02d:%02d:%02d\n", hour, min, sec).GetData());

	pTimer->VReset();
	pTimer->VStartTimer();
	algo.RunGeneticAlgorithmType2(waypoints, waypointNames);
	pTimer->VStopTimer();
	Base::GetTimeAsHHMMSS(pTimer->VGetRunningTime(), hour, min, sec);;
	::OutputDebugString(cStringUtilities::MakeFormatted("Time to RunGeneticAlgorithmType2: %02d:%02d:%02d\n", hour, min, sec).GetData());

	pTimer->VReset();
	algo.RunGeneticAlgorithmType3(waypoints, waypointNames);
	pTimer->VOnUpdate();
	Base::GetTimeAsHHMMSS(pTimer->VGetRunningTime(), hour, min, sec);;
	::OutputDebugString(cStringUtilities::MakeFormatted("Time to RunGeneticAlgorithmType3: %02d:%02d:%02d\n", hour, min, sec).GetData());

	//_CrtDumpMemoryLeaks()

	SafeDelete(&pTimer);
	cServiceLocator::Destroy();
	getch();
	return 0;
}


//  *******************************************************************************************************************
void ReadWaypointData(WaypointDataMap &waypoints, std::vector<cString>& waypointNames)
{
	IFileIO* m_pFile = IFileIO::CreateFileIO();
	if(m_pFile->VOpenFile("my-waypoints-dist-dur.csv", std::ios_base::in))
	{
		m_pFile->VReadLine(); // disregard 1st line

		std::vector<cString> tokens;
		WaypointData data1;
		WaypointData data2;
		cString m_Buffer = m_pFile->VReadLine();

		while(!m_pFile->VIsEOF() || !m_Buffer.IsEmpty())
		{
			tokens.clear();
			m_Buffer.Tokenize("\t", tokens);
			data1.m_Waypoint1 = tokens[0];
			data1.m_Waypoint2 = tokens[1];
			data1.m_Distance = tokens[2].ToInt().GetValue();
			data1.m_Duration = tokens[3].ToInt().GetValue();

			data2.m_Waypoint1 = tokens[1];
			data2.m_Waypoint2 = tokens[0];
			data2.m_Distance = tokens[2].ToInt().GetValue();
			data2.m_Duration = tokens[3].ToInt().GetValue();

			waypoints.insert(std::pair<unsigned long, WaypointData>(cHashedString::CalculateChecksum(data1.m_Waypoint1 + data1.m_Waypoint2), data1));
			waypoints.insert(std::pair<unsigned long, WaypointData>(cHashedString::CalculateChecksum(data2.m_Waypoint1 + data2.m_Waypoint2), data2));

			m_Buffer = m_pFile->VReadLine();
			if (find(waypointNames.begin(), waypointNames.end(), tokens[0]) == waypointNames.end())
			{
				waypointNames.push_back(tokens[0]);
			}

		}
		m_pFile->VCloseFile();
		SafeDelete(&m_pFile);
	}
}
