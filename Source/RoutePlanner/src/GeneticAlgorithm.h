//	*******************************************************************************************************************
//	GeneticAlgorithm	 version:	 1.0	 Ankur Sheel	date: 2015/03/19
//	*******************************************************************************************************************
// 
//	*******************************************************************************************************************
#ifndef GENETICALGORITHM_H__
#define GENETICALGORITHM_H__\

#include "Main.h"

namespace Utilities
{
	class IRandomGenerator;
}

typedef unsigned long DataType;
typedef std::vector<DataType> GenomeDataList;
struct stGenome
{
	std::vector<DataType> m_Data;
	float m_Fitness;
	unsigned long hash;
	stGenome();
} ;

inline bool operator < (const stGenome & first, const stGenome & second)
{
	return first.m_Fitness < second.m_Fitness;
}

typedef std::vector<stGenome> GenomeList;

class cGeneticAlgorithm
{
public:
	cGeneticAlgorithm(int generations=5000, int populationSize=100, float crossOverRate=0.5f, float mutationRate=0.02f, unsigned int seed = 0);
	~cGeneticAlgorithm();
	void RunGeneticAlgorithmType1(const WaypointDataMap& dataList);
	void RunGeneticAlgorithmType2(const WaypointDataMap& dataList);
	void RunGeneticAlgorithmType3(const WaypointDataMap& dataList);
	void RunGeneticAlgorithmType4(const WaypointDataMap& dataList);
	void SetWayPointNames(const std::vector<Base::cHashedString>& waypointNames);
	void SetSeed(unsigned int seed) { m_Seed = seed; }

private:
	void CreateRandomPopulation();
	void CalculateFitness(const WaypointDataMap& dataList);
	stGenome& SelectFromPopulation(const int size);
	void CrossOver(stGenome& father, stGenome& mother);
	void ShuffleMutation(stGenome& genome);
	void Mutate(stGenome& genome, int maxMutations = 3);
	void PrintCurrentPopulation(int currentGeneration);
	bool ValidateGenome(const GenomeList& population, const stGenome& genome, int size);
	void GenerateHtml(const Base::cString& fileNamePrefix);
	void AddGenome(GenomeList& population, stGenome& genome);
	void SetGenomeHash(stGenome &genome);
	void ReplaceGenome(int index, const stGenome& genome);

private:
	int m_NumberOfGenerations;
	int m_PopulationSize;
	float m_TotalFitnessOfPopulation;
	float m_CrossOverRate;
	float m_MutationRate;
	Utilities::IRandomGenerator * m_pRandomGenerator;
	GenomeList m_Population;
	unsigned int m_Seed;
	std::map<unsigned long, Base::cHashedString> m_WaypointNames;
};

#endif // GENETICALGORITHM_H__
