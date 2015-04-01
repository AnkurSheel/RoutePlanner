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
cGeneticAlgorithm::cGeneticAlgorithm(int generations/*=5000*/, int populationSize/*=100*/, float crossOverRate/*=0.5f*/
	, float mutationRate/*=0.02f*/, unsigned int seed/* = 0*/)
	: m_NumberOfGenerations(generations)
	, m_PopulationSize(populationSize)
	, m_TotalFitnessOfPopulation(0.0f)
	, m_pRandomGenerator(IRandomGenerator::CreateRandomGenerator())
	, m_CrossOverRate(crossOverRate)
	, m_MutationRate(mutationRate)
{
	if (seed == 0)
	{
		m_pRandomGenerator->VRandomize();
	}
	else 
	{
		m_pRandomGenerator->VSetRandomSeed(seed);
	}
}

//	*******************************************************************************************************************
cGeneticAlgorithm::~cGeneticAlgorithm()
{
	SafeDelete(&m_pRandomGenerator);
}

//	*******************************************************************************************************************
void cGeneticAlgorithm::RunGeneticAlgorithmType1(const WaypointDataMap& dataList, std::vector<Base::cString>& waypointNames)
{
	m_Population.clear();
	CreateRandomPopulation(waypointNames);

	GenomeList newPopulation;
	stGenome father;
	stGenome mother;

	int parentsToUse = static_cast<int>(sqrt(static_cast<float>(m_PopulationSize)));
	for (int generation = 1; generation < m_NumberOfGenerations; generation++)
	{
		cout << "Type1 Generation " << generation;
		m_TotalFitnessOfPopulation = 0.0f;
		CalculateFitness(dataList);
		
		std::sort(m_Population.begin(), m_Population.end());
		newPopulation.clear();
		if (generation % 100 == 0 || generation==1)
		{
			PrintCurrentPopulation(generation);
			GenerateHtml("RouteType1");
		}
		int populationIndex = 0;
		for (int i = parentsToUse + 1; i < m_PopulationSize; i++)
		{
			father = m_Population[populationIndex++];

			if(populationIndex == parentsToUse)
			{
				populationIndex = 0;
			}
			ShuffleMutation(father);
			Mutate(father);
			SetGenomeHash(father);
			ReplaceGenome(i, father);
		}
	}
	PrintCurrentPopulation(m_NumberOfGenerations);
	GenerateHtml("RouteType1");
}

//	*******************************************************************************************************************
void cGeneticAlgorithm::RunGeneticAlgorithmType2(const WaypointDataMap& dataList, std::vector<Base::cString>& waypointNames)
{
	m_Population.clear();
	CreateRandomPopulation(waypointNames);

	GenomeList newPopulation;
	stGenome father;
	stGenome mother;

	int parentsToUse = static_cast<int>(sqrt(static_cast<float>(m_PopulationSize)));
	for (int generation = 1; generation < m_NumberOfGenerations; generation++)
	{
		cout << "Type2 Generation " << generation;
		m_TotalFitnessOfPopulation = 0.0f;
		CalculateFitness(dataList);

		std::sort(m_Population.begin(), m_Population.end());
		newPopulation.clear();
		if (generation % 100 == 0 || generation==1)
		{
			PrintCurrentPopulation(generation);
			GenerateHtml("RouteType2");
		}
		int populationIndex = 0;
		for (int i = parentsToUse + 1; i < m_PopulationSize; i++)
		{
			father = m_Population[populationIndex++];

			if(populationIndex == parentsToUse)
			{
				populationIndex = 0;
			}
			ShuffleMutation(father);
			Mutate(father);
			SetGenomeHash(father);
			ReplaceGenome(i, father);
		}
	}
	PrintCurrentPopulation(m_NumberOfGenerations);
	GenerateHtml("RouteType2");
}

//	*******************************************************************************************************************
void cGeneticAlgorithm::RunGeneticAlgorithmType3(const WaypointDataMap& dataList, std::vector<Base::cString>& waypointNames)
{
	m_Population.clear();
	CreateRandomPopulation(waypointNames);

	GenomeList newPopulation;
	stGenome father;
	stGenome mother;

	int parentsToUse = static_cast<int>(sqrt(static_cast<float>(m_PopulationSize)));
	for (int generation = 1; generation < m_NumberOfGenerations; generation++)
	{
		cout << "Type3 Generation " << generation;
		m_TotalFitnessOfPopulation = 0.0f;
		CalculateFitness(dataList);

		std::sort(m_Population.begin(), m_Population.end());
		newPopulation.clear();
		if (generation % 100 == 0 || generation==1)
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
		for (int i = parentsToUse; i < m_PopulationSize; i++)
		{
			father = SelectFromPopulation();
			ShuffleMutation(father);
			Mutate(father);
			SetGenomeHash(father);
			AddGenome(newPopulation, father);
		}
		m_Population.clear();
		m_Population.insert(m_Population.end(), newPopulation.begin(), newPopulation.end());
	}
	PrintCurrentPopulation(m_NumberOfGenerations);
	GenerateHtml("RouteType3");
}

//	*******************************************************************************************************************
void cGeneticAlgorithm::RunGeneticAlgorithmType4(const WaypointDataMap& dataList, std::vector<Base::cString>& waypointNames)
{
	CreateRandomPopulation(waypointNames);

	GenomeList newPopulation;
	stGenome father;
	stGenome mother;

	int parentsToUse = static_cast<int>(sqrt(static_cast<float>(m_PopulationSize)));
	for (int generation = 1; generation < m_NumberOfGenerations; generation++)
	{
		cout << "Type1 Generation " << generation;
		m_TotalFitnessOfPopulation = 0.0f;
		CalculateFitness(dataList);

		std::sort(m_Population.begin(), m_Population.end());
		newPopulation.clear();
		if (generation % 100 == 0 || generation==1)
		{
			PrintCurrentPopulation(generation);
			GenerateHtml("RoueType1");
		}
		for (int i=0; i < parentsToUse; i++)
		{
			AddGenome(newPopulation, m_Population[i]);
		}
		int populationIndex = 0;
		while (newPopulation.size() < m_PopulationSize)
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
		m_Population = newPopulation;
	}
	PrintCurrentPopulation(m_NumberOfGenerations);
	GenerateHtml("RouteType4");
}

//	*******************************************************************************************************************
void cGeneticAlgorithm::CreateRandomPopulation(const vector<cString>& dataList)
{
	GenomeDataList shuffledList;
	std::srand(m_Seed);
	for (int i= 0; i< dataList.size(); i++)
	{
		shuffledList.push_back(cHashedString(dataList[i]));
	}
	stGenome genome;
	while(m_Population.size() < m_PopulationSize)
	{
		std::random_shuffle(shuffledList.begin(), shuffledList.end());
		genome.m_Data = shuffledList;
		AddGenome(m_Population, genome);
	}
}

//	*******************************************************************************************************************
void cGeneticAlgorithm::CalculateFitness(const WaypointDataMap& dataList)
{
	for(auto iterPopulation = m_Population.begin(); iterPopulation != m_Population.end(); iterPopulation++)
	{
		stGenome& genome = (*iterPopulation);
		genome.m_Fitness = 0.0f;
		auto iter = genome.m_Data.begin();
		cHashedString waypoint1 = (*iter);
		cHashedString waypoint2;
		iter++;
		for (;iter != genome.m_Data.end(); iter++)
		{
			waypoint2 = (*iter);
			unsigned long hash = cHashedString::CalculateChecksum(waypoint1.GetString() + waypoint2.GetString());
			genome.m_Fitness += dataList.at(hash).m_Distance/1000.0f;
			waypoint1 = waypoint2;
		}
		waypoint2 = genome.m_Data[0];
		unsigned long hash = cHashedString::CalculateChecksum(waypoint1.GetString() + waypoint2.GetString());
		genome.m_Fitness += dataList.at(hash).m_Distance/1000.0f;

		m_TotalFitnessOfPopulation += genome.m_Fitness;
	}
}

//	*******************************************************************************************************************
stGenome& cGeneticAlgorithm::SelectFromPopulation()
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
	int index = m_pRandomGenerator->VRandom(m_Population.size());
	return m_Population[index];
}

void cGeneticAlgorithm::CrossOver(stGenome& father, stGenome& mother)
{
	int randomPosition;
	stGenome daughter;
	stGenome son;
	if(m_pRandomGenerator->VRandom() < m_CrossOverRate)
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
	cHashedString temp;
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
	if (m_pRandomGenerator->VRandom() < m_MutationRate)
	{
		int swap_index1;
		int swap_index2;
		do 
		{
			swap_index1 = m_pRandomGenerator->VRandom(genome.m_Data.size());
			swap_index2 = m_pRandomGenerator->VRandom(genome.m_Data.size());
		}
		while (swap_index1 == swap_index2);

		cHashedString temp = genome.m_Data[swap_index1];
		genome.m_Data[swap_index1] = genome.m_Data[swap_index2];
		genome.m_Data[swap_index2] = temp;
	}
}

void cGeneticAlgorithm::PrintCurrentPopulation(int currentGeneration)
{
	//cString message = cStringUtilities::MakeFormatted("\n\nGeneration: %d, best: %0.3f, population size %d\n", currentGeneration, m_Population[0].m_Fitness, m_Population.size()); 
	cString message = cStringUtilities::MakeFormatted("Generation: %d, best: %0.3f, population size %d\n", currentGeneration, m_Population[0].m_Fitness, m_Population.size()); 
	/*for (int i = 0;	 i < m_Population[0].m_Data.size(); i++)
	{
		message += m_Population[0].m_Data[i] + ", ";
	}*/
	//cout << "\n\n" << message << "\n\n";
	::OutputDebugString(message.GetData());
}

//	*******************************************************************************************************************
bool cGeneticAlgorithm::ValidateGenome(const GenomeList& population, const stGenome& genome, int size)
{
	auto iter = genome.m_Data.begin();
	cHashedString waypoint1 = (*iter);
	cHashedString waypoint2;
	iter++;
	for (;iter != genome.m_Data.end(); iter++)
	{
		waypoint2 = (*iter);
		if (waypoint1 == waypoint2)
		{
			return false;
		}
		waypoint1 = waypoint2;
	}

	for (int i = 0; i < size; i++)
	{
		if (genome.hash == population[i].hash)
		{
			return false;
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
			cString route = "\t\t\t\t\tcase \"" + data[startIndex].GetString() + "\":\n";
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
		pFile->VWriteLine("\t\t\t\t\}\n");
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
			cString route = "\t\t\t\t\t\t\tcase \"" + data[startIndex].GetString() + "\":\n";
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
			cString route = "\t\t\tcalcRoute(\"" + data[startIndex].GetString() + "\", \"" + data[endIndex].GetString() + "\", [";
			startIndex++;
			for (; startIndex < endIndex; startIndex++)
			{
				route += "\"" + data[startIndex].GetString() + "\"";
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
	SetGenomeHash(genome);

	if(ValidateGenome(population, genome, population.size()))
	{
		population.push_back(genome);
	}
}

//	*******************************************************************************************************************
void cGeneticAlgorithm::SetGenomeHash(stGenome &genome)
{
	cString str;
	for (int i = 0; i < genome.m_Data.size(); i++)
	{
		str += genome.m_Data[i].GetString();
	}
	genome.hash = cHashedString::CalculateChecksum(str);
}

//	*******************************************************************************************************************
void cGeneticAlgorithm::ReplaceGenome(int index, const stGenome& genome)
{
	if(ValidateGenome(m_Population, genome, index))
	{
		m_Population[index] = genome;
	}
}
