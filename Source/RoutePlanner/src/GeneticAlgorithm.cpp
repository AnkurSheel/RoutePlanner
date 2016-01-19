// http://nbviewer.ipython.org/github/rhiever/Data-Analysis-and-Machine-Learning-Projects/blob/master/optimal-road-trip/Computing%20the%20optimal%20road%20trip%20across%20the%20U.S..ipynb

#include "stdafx.h"
#include "GeneticAlgorithm.h"
#include <ctime>
#include "algorithm"
#include "RandomGenerator.hxx"
#include "FileIO.hxx"

using namespace Base;
using namespace std;
using namespace Utilities;

//	*******************************************************************************************************************
stGenome::stGenome()
	: m_Fitness(0.0f)
	, hash(0)
{
}

//	*******************************************************************************************************************
cGeneticAlgorithm::cGeneticAlgorithm(const stGAProperties& properties)
	: m_Properties(properties)
	, m_TotalFitnessOfPopulation(0.0f)
	, m_pRandomGenerator(IRandomGenerator::CreateRandomGenerator())
{
	if (properties.m_Seed == 0)
	{
		m_pRandomGenerator->VRandomize();
	}
	else 
	{
		m_pRandomGenerator->VSetRandomSeed(properties.m_Seed);
	}
	m_Population.reserve(properties.m_PopulationSize);
}

//	*******************************************************************************************************************
cGeneticAlgorithm::~cGeneticAlgorithm()
{
	SafeDelete(&m_pRandomGenerator);
}

//	*******************************************************************************************************************
void cGeneticAlgorithm::RunGeneticAlgorithmType1()
{
	m_Population.clear();
	CreateRandomPopulation();

	GenomeList newPopulation;
	newPopulation.reserve(m_Properties.m_PopulationSize);
	stGenome father;

	int parentsToUse = static_cast<int>(sqrt(static_cast<float>(m_Properties.m_PopulationSize)));
	for (int generation = 1; generation < m_Properties.m_NumberOfGenerations; generation++)
	{
		m_TotalFitnessOfPopulation = 0.0f;
		
		std::sort(m_Population.begin(), m_Population.end());
		newPopulation.clear();
		if (generation % 1000 == 0 || generation==1)
		{
			PrintCurrentPopulation(generation);
			GenerateHtml("RouteType1");
		}
		for (int i=0; i < parentsToUse; i++)
		{
			AddGenome(newPopulation, m_Population[i]);
		}
		int populationIndex = 0;

		for (int i = parentsToUse; i < m_Properties.m_PopulationSize; i++)
		{
			father = m_Population[populationIndex++];

			if(populationIndex == parentsToUse)
			{
				populationIndex = 0;
			}
			ShuffleMutation(father);
			Mutate(father);
			AddGenome(newPopulation, father);
		}
		m_Population.swap(newPopulation);
	}
	PrintCurrentPopulation(m_Properties.m_NumberOfGenerations);
	GenerateHtml("RouteType1");
}

//	*******************************************************************************************************************
void cGeneticAlgorithm::RunGeneticAlgorithmType2()
{
	m_Population.clear();
	CreateRandomPopulation();

	stGenome father;
	stGenome mother;

	int parentsToUse = static_cast<int>(sqrt(static_cast<float>(m_Properties.m_PopulationSize)));
	for (int generation = 1; generation < m_Properties.m_NumberOfGenerations; generation++)
	{
		m_TotalFitnessOfPopulation = 0.0f;
		std::sort(m_Population.begin(), m_Population.end());
		if (generation % 1000 == 0 || generation==1)
		{
			PrintCurrentPopulation(generation);
			GenerateHtml("RouteType2");
		}
		int populationIndex = 0;
		for (int i = parentsToUse + 1; i < m_Properties.m_PopulationSize; i++)
		{
			father = m_Population[populationIndex++];

			if(populationIndex == parentsToUse)
			{
				populationIndex = 0;
			}
			ShuffleMutation(father);
			Mutate(father);
			ReplaceGenome(i, father);
		}
	}
	PrintCurrentPopulation(m_Properties.m_NumberOfGenerations);
	GenerateHtml("RouteType2");
}

//	*******************************************************************************************************************
void cGeneticAlgorithm::RunGeneticAlgorithmType3()
{
	m_Population.clear();
	CreateRandomPopulation();

	GenomeList newPopulation;
	stGenome father;
	stGenome mother;

	int parentsToUse = static_cast<int>(sqrt(static_cast<float>(m_Properties.m_PopulationSize)));
	for (int generation = 1; generation < m_Properties.m_NumberOfGenerations; generation++)
	{
		m_TotalFitnessOfPopulation = 0.0f;

		std::sort(m_Population.begin(), m_Population.end());
		newPopulation.clear();
		if (generation % 1000 == 0 || generation==1)
		{
			PrintCurrentPopulation(generation);
			GenerateHtml("RouteType3");
		}
		int populationIndex = 0;
		GenomeList newPopulation;
		for (int i = 0; i < parentsToUse; i++)
		{
			AddGenome(newPopulation, m_Population[i]);
		}
		for (int i = parentsToUse; i < m_Properties.m_PopulationSize; i++)
		{
			father = SelectFromPopulation(m_Population.size());
			ShuffleMutation(father);
			Mutate(father);
			AddGenome(newPopulation, father);
		}
		m_Population.clear();
		m_Population.insert(m_Population.end(), newPopulation.begin(), newPopulation.end());
	}
	PrintCurrentPopulation(m_Properties.m_NumberOfGenerations);
	GenerateHtml("RouteType3");
}

//	*******************************************************************************************************************
void cGeneticAlgorithm::RunGeneticAlgorithmType4()
{
	m_Population.clear();
	CreateRandomPopulation();

	stGenome father;

	int parentsToUse = static_cast<int>(sqrt(static_cast<float>(m_Properties.m_PopulationSize)));
	for (int generation = 1; generation < m_Properties.m_NumberOfGenerations; generation++)
	{
		m_TotalFitnessOfPopulation = 0.0f;

		std::sort(m_Population.begin(), m_Population.end());
		if (generation % 1000 == 0 || generation==1)
		{
			PrintCurrentPopulation(generation);
			GenerateHtml("RouteType4");
		}
		for (int i = parentsToUse; i < m_Properties.m_PopulationSize; i++)
		{
			father = SelectFromPopulation(parentsToUse);
			ShuffleMutation(father);
			Mutate(father);
			ReplaceGenome(i, father);
		}
	}
	PrintCurrentPopulation(m_Properties.m_NumberOfGenerations);
	GenerateHtml("RouteType4");
}

//	*******************************************************************************************************************
void cGeneticAlgorithm::RunGeneticAlgorithmType5()
{
	CreateRandomPopulation();

	GenomeList newPopulation;
	newPopulation.reserve(m_Properties.m_PopulationSize);
	stGenome father;
	stGenome mother;

	int parentsToUse = static_cast<int>(sqrt(static_cast<float>(m_Properties.m_PopulationSize)));
	for (int generation = 1; generation < m_Properties.m_NumberOfGenerations; generation++)
	{
		m_TotalFitnessOfPopulation = 0.0f;

		std::sort(m_Population.begin(), m_Population.end());
		newPopulation.clear();
		if (generation % 1000 == 0 || generation==1)
		{
			PrintCurrentPopulation(generation);
			GenerateHtml("RoueType1");
		}
		for (int i=0; i < parentsToUse; i++)
		{
			AddGenome(newPopulation, m_Population[i]);
		}
		int populationIndex = 0;
		while (newPopulation.size() < m_Properties.m_PopulationSize)
		{
			father = m_Population[populationIndex++];
			//father = SelectFromPopulation();

			if(populationIndex == parentsToUse)
			{
				populationIndex = 0;
			}
			//mother = SelectFromPopulation();
			//
			stGenome temp = father;
			//stGenome temp1 = mother;
			////Father = son ; Mother = Daughter after Crossover
			//CrossOver(temp, temp1);

			ShuffleMutation(father);

			Mutate(temp);
			//Mutate(temp1);
			AddGenome(newPopulation, temp);
			//if (ValidateGenome(temp1))
			//{
			//	newPopulation.push_back(temp1);
			//}
		}
		m_Population.swap(newPopulation);
	}
	PrintCurrentPopulation(m_Properties.m_NumberOfGenerations);
	GenerateHtml("RouteType4");
}

//  *******************************************************************************************************************
void cGeneticAlgorithm::SetData(const WaypointDataMap& dataList, const vector<Base::cHashedString>& waypointNames)
{
	m_DataList = dataList;
	for (int i = 0; i < waypointNames.size(); i++ )
	{
		m_WaypointNames[waypointNames[i].GetHash()] = waypointNames[i];
	}
}

//	*******************************************************************************************************************
void cGeneticAlgorithm::CreateRandomPopulation()
{
	GenomeDataList shuffledList;
	std::srand(m_Properties.m_Seed);
	for (auto iter = m_WaypointNames.begin(); iter != m_WaypointNames.end(); iter++)
	{
		shuffledList.push_back(iter->first);
	}
	stGenome genome;
	while(m_Population.size() < m_Properties.m_PopulationSize)
	{
		std::random_shuffle(shuffledList.begin(), shuffledList.end());
		genome.m_Data = shuffledList;
		AddGenome(m_Population, genome);
	}
}

//	*******************************************************************************************************************
void cGeneticAlgorithm::CalculateFitness(stGenome& genome)
{
	genome.m_Fitness = 0.0f;
	auto iter = genome.m_Data.begin();
	DataType waypoint1 = (*iter);
	DataType waypoint2;
	iter++;
	for (;iter != genome.m_Data.end(); iter++)
	{
		waypoint2 = (*iter);
		unsigned long distance = m_DataList.at(waypoint1).m_DistanceTimeMap.at(waypoint2).m_Distance;
		genome.m_Fitness += distance;
		waypoint1 = waypoint2;
	}
	waypoint2 = genome.m_Data[0];
	unsigned long distance = m_DataList.at(waypoint1).m_DistanceTimeMap.at(waypoint2).m_Distance;
	genome.m_Fitness += distance;

	m_TotalFitnessOfPopulation += genome.m_Fitness;
}

//	*******************************************************************************************************************
stGenome& cGeneticAlgorithm::SelectFromPopulation(const int size)
{
	//float ball = m_pRandomGenerator->VRandom() * m_TotalFitnessOfPopulation;
	//float pie = 0.0f;
	//for(auto iter = m_Population.begin(); iter != m_Population.end(); iter++)
	//{
	//	pie += iter->m_Fitness;
	//	if(ball < pie)
	//	{
	//		return (*iter);
	//	}
	//}
	int index = m_pRandomGenerator->VRandom(size);
	return m_Population[index];
}

void cGeneticAlgorithm::CrossOver(stGenome& father, stGenome& mother)
{
	int randomPosition;
	stGenome daughter;
	stGenome son;
	if(m_pRandomGenerator->VRandom() < m_Properties.m_CrossOverRate)
	{
		randomPosition = m_pRandomGenerator->VRandom(father.m_Data.size());
		for (int i = 0; i < randomPosition; i++)
		{
			son.m_Data.push_back(father.m_Data[i]);
			daughter.m_Data.push_back(mother.m_Data[i]);
		}
		for (int i = randomPosition; i < father.m_Data.size(); i++)
		{
			son.m_Data.push_back(mother.m_Data[i]);
			daughter.m_Data.push_back(father.m_Data[i]);
		}

		mother = daughter;
		father = son;
	}
}

//	*******************************************************************************************************************
void cGeneticAlgorithm::ShuffleMutation(stGenome& genome)
{
	stGenome son;
	int length = m_pRandomGenerator->VRandom(2, genome.m_Data.size() / 2);
	int startIndex = m_pRandomGenerator->VRandom(genome.m_Data.size() - length - 1);
	int insertIndex;
	do 
	{
		insertIndex = m_pRandomGenerator->VRandom(genome.m_Data.size() - length - 1);
	}
	while (startIndex == insertIndex);
	DataType temp;
	for (int i = 0; i < length; i++)
	{
		temp = genome.m_Data[startIndex + i];
		genome.m_Data[startIndex + i] = genome.m_Data[insertIndex + i];
		genome.m_Data[insertIndex + i] = temp;
	}


	//std::vector<cString> genomeSubset;
	//std::vector<cString> newGenomeData;
	//for (int i = startIndex; i < startIndex + length; i++)
	//{
	//	genomeSubset.push_back(genome.m_Data[i]);
	//}

	//for (int i = 0; i < insertIndex; i++)
	//{
	//	newGenomeData.push_back(genome.m_Data[i]);
	//}

	//newGenomeData.insert(newGenomeData.end(), genomeSubset.begin(), genomeSubset.end());
	//for (int i = insertIndex + length; i < genome.m_Data.size(); i++)
	//{
	//	newGenomeData.push_back(genome.m_Data[i]);
	//}
	//SP_ASSERT_ERROR(genome.m_Data.size() == newGenomeData.size())(genome.m_Data.size())(newGenomeData.size()).SetCustomMessage("Data length does not match\n");
	//SP_ASSERT_ERROR(genome.m_Data != newGenomeData).SetCustomMessage("Same Data\n");
	//genome.m_Data = newGenomeData;
}

//	*******************************************************************************************************************
void cGeneticAlgorithm::Mutate(stGenome& genome, int maxMutations /*= 3*/)
{
	if (m_pRandomGenerator->VRandom() < m_Properties.m_MutationRate)
	{
		int swap_index1;
		int swap_index2;
		do 
		{
			swap_index1 = m_pRandomGenerator->VRandom(genome.m_Data.size());
			swap_index2 = m_pRandomGenerator->VRandom(genome.m_Data.size());
		}
		while (swap_index1 == swap_index2);

		DataType temp = genome.m_Data[swap_index1];
		genome.m_Data[swap_index1] = genome.m_Data[swap_index2];
		genome.m_Data[swap_index2] = temp;
	}
}

void cGeneticAlgorithm::PrintCurrentPopulation(int currentGeneration)
{
	//cString message = cStringUtilities::MakeFormatted("\n\nGeneration: %d, best: %0.3f, population size %d\n", currentGeneration, m_Population[0].m_Fitness, m_Population.size()); 
	cString message = cStringUtilities::MakeFormatted("Generation: %d, best: %0.3f, population size %d\n", currentGeneration, (m_Population[0].m_Fitness/1000.0f), m_Population.size()); 
	/*for (int i = 0;	 i < m_Population[0].m_Data.size(); i++)
	{
		message += m_Population[0].m_Data[i] + ", ";
	}*/
	//cout << "\n\n" << message << "\n\n";
	cout << message.GetData();
	::OutputDebugString(message.GetData());
}

//	*******************************************************************************************************************
bool cGeneticAlgorithm::ValidateGenome(GenomeList& population, stGenome& genome, int size)
{
	//auto iter = genome.m_Data.begin();
	//DataType waypoint1 = (*iter);
	//DataType waypoint2;
	//iter++;
	//for (;iter != genome.m_Data.end(); iter++)
	//{
	//	waypoint2 = (*iter);
	//	if (waypoint1 == waypoint2)
	//	{
	//		return false;
	//	}
	//	waypoint1 = waypoint2;
	//}
	for (int i = 0; i < size; i++)
	{
		if (isEqual(genome.m_Fitness, population[i].m_Fitness))
		{
			if (genome.hash == 0)
			{
				SetGenomeHash(genome);
			}
			if (population[i].hash == 0)
			{
				SetGenomeHash(population[i]);
			}
			if (genome.hash == population[i].hash)
			{
				return false;
			}
		}
	}
	return true;
}

void cGeneticAlgorithm::GenerateHtml(const cString& fileNamePrefix)
{
	static int htmlIndex = 0;
	IFileIO * pFile = IFileIO::CreateFileIO();
	GenomeDataList data = m_Population[0].m_Data;
	data.push_back(data[0]);

	if(pFile->VOpenFile(cStringUtilities::MakeFormatted("Routes/%s_%d.html", fileNamePrefix.GetData(), htmlIndex), ios_base::out))
	{
		pFile->VWriteLine("<!DOCTYPE html>\n");
		pFile->VWriteLine("<html lang=\"en\">\n");
		pFile->VWriteLine("\t<head>\n");
		pFile->VWriteLine("\t\t<meta charset=\"utf-8\">\n");
		//pFile->VWriteLine("\t<meta name="viewport" content="initial-scale=1.0, user-scalable=no">\n");
		//pFile->VWriteLine("\t<meta name="description" content="Randy Olson uses machine learning to find the optimal road trip across the U.S.">
		pFile->VWriteLine("\t\t<meta name=\"author\" content=\"Ankur Sheel\">\n");

		pFile->VWriteLine("\t\t<title>The optimal road trip using GA</title>\n");
		pFile->VWriteLine("\t\t<style>\n");
		pFile->VWriteLine("\t\t\thtml, body, #map-canvas {\n");
		pFile->VWriteLine("\t\t\t\theight: 100%;\n");
		pFile->VWriteLine("\t\t\t\tmargin: 0px;\n");
		pFile->VWriteLine("\t\t\t\tpadding: 0px\n");
		pFile->VWriteLine("\t\t\t}\n");
		pFile->VWriteLine("\t\t\t#panel {\n");
		pFile->VWriteLine("\t\t\t\tposition: absolute;\n");
		pFile->VWriteLine("\t\t\t\ttop: 5px;\n");
		pFile->VWriteLine("\t\t\t\tleft: 50%;\n");
		pFile->VWriteLine("\t\t\t\tmargin-left: -180px;\n");
		pFile->VWriteLine("\t\t\t\tz-index: 5;\n");
		pFile->VWriteLine("\t\t\t\tbackground-color: #fff;\n");
		pFile->VWriteLine("\t\t\t\tpadding: 10px;\n");
		pFile->VWriteLine("\t\t\t\tborder: 1px solid #999;\n");
		pFile->VWriteLine("\t\t\t}\n");
		pFile->VWriteLine("\t\t</style>\n");
		pFile->VWriteLine("\t\t<script src=\"https://maps.googleapis.com/maps/api/js?v=3.exp&signed_in=true\"></script>\n");
		pFile->VWriteLine("\t\t<script>\n");

		const int googleWaypointsAllowed  = 8;
		int numberOfDirectionVariables = static_cast<int>(ceil(data.size() / static_cast<float>(googleWaypointsAllowed)));
		for (int directionIndex = 1; directionIndex <= numberOfDirectionVariables; directionIndex++)
		{
			pFile->VWriteLine(cStringUtilities::MakeFormatted("\t\t\tvar directionsDisplay%d\n", directionIndex));
		}
		pFile->VWriteLine("\t\t\tvar markerOptions = {icon: \"http://maps.gstatic.com/mapfiles/markers2/marker.png\"};\n");
		pFile->VWriteLine("\t\t\tvar directionsDisplayOptions = {preserveViewport: true,\n");
		pFile->VWriteLine("\t\t\t\tmarkerOptions: markerOptions};\n");
		pFile->VWriteLine("\t\t\tvar directionsService = new google.maps.DirectionsService();\n");
		pFile->VWriteLine("\t\t\tvar map;\n");
		pFile->VWriteLine("\t\t\t\n");
		pFile->VWriteLine("\t\t\tfunction initialize() {\n");
		pFile->VWriteLine("\t\t\t\tvar center = new google.maps.LatLng(39, -96);\n");
		pFile->VWriteLine("\t\t\t\tvar mapOptions = {\n");
		pFile->VWriteLine("\t\t\t\t\tzoom: 5,\n");
		pFile->VWriteLine("\t\t\t\t\tcenter: center\n");
		pFile->VWriteLine("\t\t\t\t};\n");
		pFile->VWriteLine("\t\t\t\tmap = new google.maps.Map(document.getElementById('map-canvas'), mapOptions);\n");
		for (int directionIndex = 1; directionIndex <= numberOfDirectionVariables; directionIndex++)
		{
			pFile->VWriteLine(cStringUtilities::MakeFormatted("\t\t\t\tdirectionsDisplay%d.setMap(map);\n", directionIndex));
			pFile->VWriteLine(cStringUtilities::MakeFormatted("\t\t\t\tdirectionsDisplay%d.setPanel(document.getElementById('directionsPanel'));\n", directionIndex));
		}
		pFile->VWriteLine("\t\t\t}\n");
		pFile->VWriteLine("\t\t\t\n");
		pFile->VWriteLine("\t\t\tfunction calcRoute(start, end, routes) {\n");
		pFile->VWriteLine("\t\t\t\tswitch (start) {\n");
		int directionIndex = 1;
		for (int startIndex = 0; startIndex < data.size(); startIndex= startIndex + googleWaypointsAllowed)
		{
			cString route = "\t\t\t\t\tcase \"" + m_WaypointNames[data[startIndex]].GetString() + "\":\n";
			route += cStringUtilities::MakeFormatted("\t\t\t\t\t\tdirectionsDisplay%d= new google.maps.DirectionsRenderer(directionsDisplayOptions);\n", directionIndex);
			route += "\t\t\t\t\t\tbreak;\n";
			pFile->VWriteLine(route);
			directionIndex++;
		}
		pFile->VWriteLine("\t\t\t\t}\n");
		pFile->VWriteLine("\n");
		pFile->VWriteLine("\t\t\t\tvar waypts = [];\n");
		pFile->VWriteLine("\t\t\t\t\tfor (var i = 0; i < routes.length; i++) {\n");
		pFile->VWriteLine("\t\t\t\t\t\twaypts.push({\n");
		pFile->VWriteLine("\t\t\t\t\t\tlocation:routes[i],\n");
		pFile->VWriteLine("\t\t\t\t\t\tstopover:true});\n");
		pFile->VWriteLine("\t\t\t\t}\n");
		pFile->VWriteLine("\n");
		pFile->VWriteLine("\t\t\t\tvar request = \"\";\n");
		pFile->VWriteLine("\t\t\t\tif (waypts.length > 0) {\n");
		pFile->VWriteLine("\t\t\t\t\trequest = {\n");
		pFile->VWriteLine("\t\t\t\t\t\torigin: start,\n");
		pFile->VWriteLine("\t\t\t\t\t\tdestination: end,\n");
		pFile->VWriteLine("\t\t\t\t\t\twaypoints: waypts,\n");
		pFile->VWriteLine("\t\t\t\t\t\toptimizeWaypoints: false,\n");
		pFile->VWriteLine("\t\t\t\t\t\ttravelMode: google.maps.TravelMode.DRIVING\n");
		pFile->VWriteLine("\t\t\t\t\t};\n");
		pFile->VWriteLine("\t\t\t\t}\n");
		pFile->VWriteLine("\t\t\t\telse {\n");
		pFile->VWriteLine("\t\t\t\t\trequest = {\n");
		pFile->VWriteLine("\t\t\t\t\t\torigin: start,\n");
		pFile->VWriteLine("\t\t\t\t\t\tdestination: end,\n");
		pFile->VWriteLine("\t\t\t\t\t\ttravelMode: google.maps.TravelMode.DRIVING\n");
		pFile->VWriteLine("\t\t\t\t\t};\n");
		pFile->VWriteLine("\t\t\t\t}\n");
		pFile->VWriteLine("\t\t\t\tdirectionsService.route(request, function(response, status) {\n");
		pFile->VWriteLine("\t\t\t\t\tif (status == google.maps.DirectionsStatus.OK) {\n");
		pFile->VWriteLine("\t\t\t\t\t\tswitch (start) {\n");
		
		directionIndex = 1;
		for (int startIndex = 0; startIndex < data.size(); startIndex= startIndex + googleWaypointsAllowed)
		{
			cString route = "\t\t\t\t\t\t\tcase \"" + m_WaypointNames[data[startIndex]].GetString() + "\":\n";
			route += cStringUtilities::MakeFormatted("\t\t\t\t\t\t\t\tdirectionsDisplay%d.setDirections(response);\n", directionIndex);
			route += "\t\t\t\t\t\t\t\tbreak;\n";
			pFile->VWriteLine(route);
			directionIndex++;
		}
		pFile->VWriteLine("\t\t\t\t\t\t}\n");
		pFile->VWriteLine("\t\t\t\t\t}\n");
		pFile->VWriteLine("\t\t\t\t});\n");
		pFile->VWriteLine("\t\t\t}\n");
		pFile->VWriteLine("\t\t\tgoogle.maps.event.addDomListener(window, 'load', initialize);\n");
		int waypointIndex = 0;
		while (waypointIndex < data.size())
		{
			int startIndex = waypointIndex;
			int endIndex = startIndex + googleWaypointsAllowed;
			if(endIndex >= data.size())
			{
				endIndex = data.size() - 1;
			}
			cString route = "\t\t\tcalcRoute(\"" + m_WaypointNames[data[startIndex]].GetString() + "\", \"" + m_WaypointNames[data[endIndex]].GetString() + "\", [";
			startIndex++;
			for (; startIndex < endIndex; startIndex++)
			{
				route += "\"" + m_WaypointNames[data[startIndex]].GetString() + "\"";
				if (startIndex < (endIndex - 1))
				{
					route += ", ";
				}
			}
			route += "]);\n";
			waypointIndex += googleWaypointsAllowed;
			pFile->VWriteLine(route);
		}
		pFile->VWriteLine("\t\t</script>\n");
		pFile->VWriteLine("\t</head>\n");
		pFile->VWriteLine("\t<body>\n");
		pFile->VWriteLine("\t\t<div id=\"map-canvas\" style=\"float:left;width:70%; height:100%\"></div>\n");
		pFile->VWriteLine("\t\t<div id=\"directionsPanel\" style=\"float:right;width:30%;height 100%\">\n");
		//pFile->VWriteLine("\t\t<p>Total Distance: <span id=\"total\"></span></p>\n");

		pFile->VWriteLine("\t</body>\n");
		pFile->VWriteLine("</html>\n");
		pFile->VCloseFile();
	}
	SafeDelete(&pFile);
	htmlIndex++;
}

//	*******************************************************************************************************************
void cGeneticAlgorithm::AddGenome(GenomeList& population, stGenome& genome)
{
	genome.hash = 0;
	CalculateFitness(genome);
	if(ValidateGenome(population, genome, population.size()))
	{
		population.push_back(genome);
	}
}

//	*******************************************************************************************************************
void cGeneticAlgorithm::ReplaceGenome(int index, stGenome& genome)
{
	genome.hash = 0;
	CalculateFitness(genome);
	if(ValidateGenome(m_Population, genome, index))
	{
		m_Population[index] = genome;
	}
}

//	*******************************************************************************************************************
void cGeneticAlgorithm::SetGenomeHash(stGenome &genome)
{
	cString str;
	for (int i = 0; i < genome.m_Data.size(); i++)
	{
		str += cStringUtilities::MakeFormatted("%d", genome.m_Data[i]);
	}
	genome.hash = cHashedString::CalculateChecksum(str);
}
