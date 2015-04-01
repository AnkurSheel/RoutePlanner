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

typedef std::vector<Base::cHashedString> GenomeDataList;

struct stGenome
{
	std::vector<Base::cHashedString> m_Data;
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
	void RunGeneticAlgorithmType1(const WaypointDataMap& dataList, std::vector<Base::cString>& waypointNames);
	void RunGeneticAlgorithmType2(const WaypointDataMap& dataList, std::vector<Base::cString>& waypointNames);
	void RunGeneticAlgorithmType3(const WaypointDataMap& dataList, std::vector<Base::cString>& waypointNames);
	void RunGeneticAlgorithmType4(const WaypointDataMap& dataList, std::vector<Base::cString>& waypointNames);
	void SetSeed(unsigned int seed) { m_Seed = seed; }

private:
	void CreateRandomPopulation(const std::vector<Base::cString>& dataList);
	void CalculateFitness(const WaypointDataMap& dataList);
	stGenome& SelectFromPopulation();
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
};

#endif // GENETICALGORITHM_H__

//class cGenetic
//{
//protected:
//	UINT			m_iTarget,
//		m_iRowSize,
//		m_iColSize,
//		m_iGenomeLength,
//		m_iPopSize,
//		m_iMaxGenerations ;
//	const float		m_iCrossoverRate,
//		m_iMutationRate ;
//	vector<Genome>	m_Population ;
//	BOOL			m_bSolutionFound ;
//	Genome			m_Solution ;
//	int				m_iFoundinGenNo ;
//
//public:
//	cGenetic() ;
//	~cGenetic() ;
//	UINT GetTarget() ;
//	UINT GetPopSize() ;
//	float GetCrossOverRate() ;
//	float GetMutationRate() ;
//	void SetRandSeed() ;
//	void CreateRandomPopulation() ;
//	void FindSolution() ;
//	void CalculateFitness() ;
//	vector<int> ParseGenes(Genome genome) ;
//	int ConvertBinaryStringtoNo(string szBinary) ;
//	int CalculateRowTotal(vector<int> values) ;
//	int CalculateColTotal(vector<int> values) ;
//	Genome Selection() ;
//	void CrossOver(Genome &Father, Genome &Mother) ;
//	void Mutate(Genome &gene) ;
//	void PrintSolution() ;
//};