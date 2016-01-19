#include "stdafx.h"
#include "BTProbabilitySelectorNode.h"
#include "RandomGenerator.hxx"

using namespace AI;
using namespace Base;
using namespace Utilities;
//  ********************************************************************************************************************
cBTProbabilitySelectorNode::cBTProbabilitySelectorNode()
	: m_pRandomGenerator(IRandomGenerator::CreateRandomGenerator())
	, m_Total(0)
{
}

//  ********************************************************************************************************************
cBTProbabilitySelectorNode::~cBTProbabilitySelectorNode()
{
	SafeDelete(&m_pRandomGenerator);
}

//  ********************************************************************************************************************
void cBTProbabilitySelectorNode::VOnInitialize(void * pOwner)
{
	m_RemainingIndices.clear();
	m_Total = 0;
	SP_ASSERT(m_Weights.size() == m_Children.size())(m_Weights.size())(m_Children.size())
		.SetCustomMessage("All Children need to have a weight");
	m_RemainingIndices.reserve(m_Children.size());
	for (int index = 0; index < m_Weights.size(); index++)
	{
		m_Total += m_Weights[index];
		m_RemainingIndices.push_back(index);
	}
	cBTBaseSelectorNode::VOnInitialize(pOwner);
}

//  ********************************************************************************************************************
void cBTProbabilitySelectorNode::VCalculateNextChildIndex()
{
	int roll = m_pRandomGenerator->VRandom(m_Total);
	int choice = 0;
	int sum = 0;
	for (;choice < m_RemainingIndices.size(); choice++)
	{
		int weight = m_Weights[m_RemainingIndices[choice]];
		sum += weight;
		if (sum >= roll)
		{
			m_Total -= weight;
			break;
		}
	}
	m_CurrentChildIndex = m_RemainingIndices[choice];
	m_RemainingIndices[choice] = m_RemainingIndices.back();
	m_RemainingIndices.pop_back();
}

//  ********************************************************************************************************************
shared_ptr<cBTProbabilitySelectorNode> cBTProbabilitySelectorNode::SetWeight(const int weight)
{
	m_Weights.push_back(weight);
	return dynamic_pointer_cast<cBTProbabilitySelectorNode>(shared_from_this());
}
