//  *******************************************************************************************************************
//  HighScoreTable   version:  1.0   Ankur Sheel  date: 2013/03/14
//  *******************************************************************************************************************
// 
//  *******************************************************************************************************************
#ifndef HighScoreTable_h__
#define HighScoreTable_h__

#include "HighScoreTable.hxx"

namespace GameBase
{
	class cScore;
}

namespace Utilities
{
	class IXMLNode;
}

namespace GameBase
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @brief Base class to hold HighScoreTables. This class should be derived to hold
	/// game specific HighScoreTables
	///
	///
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class cHighScoreTable
		: public IHighScoreTable
		, public Base::cNonCopyable
	{
	private:
		cHighScoreTable();
		~cHighScoreTable();
		void Initialize(const stHighScoreTableDef & HighScoreTableDef);
		void VSave();
		void VAddNewScore(shared_ptr<cScore> pScore);
		ScoreSet VGetScores();
		bool VIsHighScore(const int inScore);
		Base::tOptional<int> VGetScorePositionInTable(const int inScore);
		
		bool VIsAscendingOrder() { return m_InAscendingOrder; }

		void Load();
		void SaveScore(const shared_ptr<const cScore> pScore, const shared_ptr<Utilities::IXMLNode> pRootNode);

	protected:
		Base::cString	m_ScoreFile;	///< The path for the score file
		unsigned int	m_NumScores;	///< The number of Scores to store
		ScoreSet	m_Scores;
		bool	m_InAscendingOrder;

		friend static IHighScoreTable * IHighScoreTable::CreateHighScoreTable(const stHighScoreTableDef & HighScoreTableDef);
	};
}
#endif