//  *******************************************************************************************************************
//  HighScoreTable   version:  1.0   Ankur Sheel  date: 2014/04/07
//  *******************************************************************************************************************
// 
//  *******************************************************************************************************************
#ifndef HighScoreTable_hxx__
#define HighScoreTable_hxx__

#include "GameBaseDefines.h"

namespace GameBase
{
	class cScore;
}

namespace GameBase
{
	struct stHighScoreTableDef
	{
		int	m_NumberOfRecords;
		int	m_DefaultScore;
		int	m_StepMultiplier;
		Base::cString	m_FileName;
		Base::cString	m_DefaultPlayerName;
		bool	m_StoreInAscendingOrder;

		stHighScoreTableDef()
			: m_NumberOfRecords(1)
			, m_DefaultScore(0)
			, m_StepMultiplier(1)
			, m_StoreInAscendingOrder(true)
			, m_DefaultPlayerName("PlayerName")
		{
		}
	};

	class IHighScoreTable
	{
	public:
		typedef std::multiset<shared_ptr<cScore>, Base::sharedptr_compare<cScore, std::greater<cScore> > > ScoreSet;

	public:
		virtual ~IHighScoreTable(){};
		virtual void VSave() = 0;
		virtual void VAddNewScore(shared_ptr<cScore> pScore) = 0;
		virtual ScoreSet VGetScores() = 0;
		virtual bool VIsAscendingOrder() = 0;
		virtual bool VIsHighScore(const int inScore) = 0;
		virtual Base::tOptional<int> VGetScorePositionInTable(const int inScore) = 0;

		GAMEBASE_API static IHighScoreTable * CreateHighScoreTable(const stHighScoreTableDef & HighScoreTableDef);
	};
}
#endif // HighScoreTable_hxx__