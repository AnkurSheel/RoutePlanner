#include "stdafx.h"
#include "HighScoreTable.h"
#include "Score.h"
#include "optional.h"
#include "XMLNode.hxx"
#include "GameDirectories.h"

using namespace GameBase;
using namespace Utilities;
using namespace Base;

//  *******************************************************************************************************************
cHighScoreTable::cHighScoreTable()
	: m_NumScores(10)
{

}

//  *******************************************************************************************************************
cHighScoreTable::~cHighScoreTable()
{
}

//  *******************************************************************************************************************
void cHighScoreTable::Initialize(const stHighScoreTableDef & HighScoreTableDef)
{
	SP_ASSERT_ERROR(!HighScoreTableDef.m_FileName.IsEmpty()).SetCustomMessage("High Score File Name is empty");

	m_ScoreFile = cGameDirectories::GetMediaDirectory() + HighScoreTableDef.m_FileName + ".hs";
	m_NumScores = HighScoreTableDef.m_NumberOfRecords;
	m_InAscendingOrder = HighScoreTableDef.m_StoreInAscendingOrder;

	// Make a default score table if none exists
	DWORD attr = GetFileAttributes(m_ScoreFile.GetData());
	if (attr == INVALID_FILE_ATTRIBUTES)
	{
		int score = HighScoreTableDef.m_DefaultScore;
		int step = (score / (m_NumScores * HighScoreTableDef.m_StepMultiplier));
		for (unsigned int i = 0; i < m_NumScores; i++)
		{
			shared_ptr<cScore> pScore(DEBUG_NEW cScore());
			pScore->SetPlayerName(HighScoreTableDef.m_DefaultPlayerName);
			pScore->SetScore(score);
			VAddNewScore(pScore);
			score -= step;
		}
		VSave();
		m_Scores.clear();
	}
}

//  *******************************************************************************************************************
void cHighScoreTable::VAddNewScore(shared_ptr<cScore> pScore)
{
	m_Scores.insert(pScore);
	if(m_Scores.size() > m_NumScores)
	{
		ScoreSet::iterator iter;
		if(m_InAscendingOrder)
		{
			iter = m_Scores.begin();
		}
		else
		{
			iter = m_Scores.end();
			--iter;
		}
		m_Scores.erase(iter);
	}
}

//  *******************************************************************************************************************
void cHighScoreTable::VSave()
{
	shared_ptr<IXMLNode> pXmlNode = IXMLNode::InitializeForSave("HighScores", "");

	for(auto iter = m_Scores.begin(); iter != m_Scores.end(); iter++)
	{
		SaveScore(*iter, pXmlNode);
	}

	pXmlNode->VSave(m_ScoreFile);
}

//  *******************************************************************************************************************
cHighScoreTable::ScoreSet cHighScoreTable::VGetScores()
{
	if(m_Scores.empty())
	{
		Load();
	}
	return m_Scores;
}

//  *******************************************************************************************************************
bool cHighScoreTable::VIsHighScore(const int inScore)
{
	if(m_Scores.empty())
	{
		Load();
	}

	if(m_InAscendingOrder)
	{
		auto iter = m_Scores.begin();
		if(inScore < (*iter)->GetScore())
		{
			return true;
		}
	}
	else
	{
		auto iter = m_Scores.end();
		iter--;
		if(inScore > (*iter)->GetScore())
		{
			return true;
		}
	}
	return false;
}

//  *******************************************************************************************************************
tOptional<int> cHighScoreTable::VGetScorePositionInTable(const int inScore)
{
	if(VIsHighScore(inScore))
	{
		if(m_InAscendingOrder)
		{
			int pos = 0;
			for(auto iter = m_Scores.rbegin(); iter != m_Scores.rend(); iter++)
			{
				if(inScore < (*iter)->GetScore())
				{
					return pos;
				}
				pos++;
			}
		}
		else
		{

			int pos = m_Scores.size() - 1;
			for(auto iter = m_Scores.begin(); iter != m_Scores.end(); iter++)
			{
				if(inScore > (*iter)->GetScore())
				{
					return pos;
				}
				pos--;
			}
		}
	}

	return tOptional<int>();
}

//  *******************************************************************************************************************
void cHighScoreTable::Load()
{
	shared_ptr<IXMLNode> pXmlNode = IXMLNode::Load(m_ScoreFile);
	if(pXmlNode != NULL)
	{
		m_Scores.clear();

		IXMLNode::XMLNodeList List;
		pXmlNode->VGetChildren(List);
		for (auto Iter = List.begin(); Iter != List.end(); Iter++)
		{
			IXMLNode * pScoreNode = (*Iter).get();
			shared_ptr<cScore> pScore(DEBUG_NEW cScore());
			pScore->SetPlayerName(pScoreNode->VGetChildValue("name"));
			pScore->SetScore(pScoreNode->VGetChildValueAsInt("score", 0));
			VAddNewScore(pScore);
		}
	}
}

//  *******************************************************************************************************************
void cHighScoreTable::SaveScore(const shared_ptr<const cScore> pScore, const shared_ptr<Utilities::IXMLNode> pRootNode)
{
	shared_ptr<IXMLNode> pElement = MakeStrongPtr(pRootNode->VAddElement("HighScore", ""));
	pElement->VAddElement("name", pScore->GetPlayerName());
	pElement->VAddElement("score", cStringUtilities::MakeFormatted("%d", pScore->GetScore()));
}

//  *******************************************************************************************************************
IHighScoreTable * IHighScoreTable::CreateHighScoreTable(const stHighScoreTableDef & HighScoreTableDef)
{
	cHighScoreTable * pHighScoreTable = DEBUG_NEW cHighScoreTable();
	pHighScoreTable->Initialize(HighScoreTableDef);
	return pHighScoreTable;
}