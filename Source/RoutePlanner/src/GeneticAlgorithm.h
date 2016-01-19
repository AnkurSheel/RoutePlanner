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


struct stGAProperties
{
  int m_NumberOfGenerations;
  int m_PopulationSize;
  float m_CrossOverRate;
  float m_MutationRate;
  unsigned int m_Seed;
  float m_closestCityChance;

  stGAProperties()
  : m_NumberOfGenerations(5000)
  , m_PopulationSize(100)
  , m_CrossOverRate(0.7f)
  , m_MutationRate(0.1f)
  , m_Seed(0)
  , m_closestCityChance(0.9f)
  {

  }
};
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
	cGeneticAlgorithm(const stGAProperties& poperties);
	~cGeneticAlgorithm();
	void RunGeneticAlgorithmType1();
	void RunGeneticAlgorithmType2();
	void RunGeneticAlgorithmType3();
	void RunGeneticAlgorithmType4();
	void RunGeneticAlgorithmType5();
	void SetData(const WaypointDataMap& dataList, const std::vector<Base::cHashedString>& waypointNames);
	void SetSeed(unsigned int seed) { m_Properties.m_Seed = seed; }

private:
	void CreateRandomPopulation();
	void CalculateFitness(stGenome & genome);
	stGenome& SelectFromPopulation(const int size);
	void CrossOver(stGenome& father, stGenome& mother);
	void ShuffleMutation(stGenome& genome);
	void Mutate(stGenome& genome, int maxMutations = 3);
	void PrintCurrentPopulation(int currentGeneration);
	bool ValidateGenome(GenomeList& population, stGenome& genome, int size);
	void GenerateHtml(const Base::cString& fileNamePrefix);
	void AddGenome(GenomeList& population, stGenome& genome);
	void SetGenomeHash(stGenome &genome);
	void ReplaceGenome(int index, stGenome& genome);

private:
  stGAProperties m_Properties;
	float m_TotalFitnessOfPopulation;
	Utilities::IRandomGenerator * m_pRandomGenerator;
	GenomeList m_Population;
	std::map<unsigned long, Base::cHashedString> m_WaypointNames;
	WaypointDataMap m_DataList;
};

#endif // GENETICALGORITHM_H__
