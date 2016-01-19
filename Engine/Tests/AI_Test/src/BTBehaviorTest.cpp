#include "stdafx.h"
#include "BTBehavior.h"
#include "MockBTNode.h"
#include "BTNodeFactory.h"

using namespace AI;
using namespace Base;
using namespace testing;

class cSimpleNode 
	: public cBTBehavior
{
	DEFINE_NODE_PROPERTY(cSimpleNode, int, A)
	DEFINE_NODE_PROPERTY(cSimpleNode, float, B)
	DEFINE_NODE_PROPERTY(cSimpleNode, bool, C)

private:
	cSimpleNode()
		: m_A(0)
		, m_B(0.0f)
		, m_C(false)
	{
	}

private:
	friend class cBTNodeFactory;
};


class BTBehaviorTest : public ::testing::Test
{
protected:
	static void SetUpTestCase()
	{
		DefaultValue<BT_STATUS::Enum>::Set(BT_STATUS::Invalid);
		m_pOutput = new AutoCaptureOutput();
	}

	static void TearDownTestCase() 
	{
		SafeDelete(&m_pOutput);
		DefaultValue<BT_STATUS::Enum>::Clear();
	}

	void SetUp()
	{
	}

	void TearDown()
	{
	}

	static AutoCaptureOutput * m_pOutput;
};

AutoCaptureOutput * BTBehaviorTest::m_pOutput;

//  *******************************************************************************************************************
TEST_F(BTBehaviorTest, Tick_DoesInitialize_Successful)
{
	shared_ptr<cMockBTNode> pNode(DEBUG_NEW cMockBTNode());
	pNode->DelegateToFake();

	EXPECT_EQ(0, pNode->m_InitializeCalled);

	pNode->Tick(NULL);
	EXPECT_EQ(1, pNode->m_InitializeCalled);
}

//  *******************************************************************************************************************
TEST_F(BTBehaviorTest, Tick_UpdateCalled_Successful)
{
	shared_ptr<cMockBTNode> pNode(DEBUG_NEW cMockBTNode());
	pNode->DelegateToFake();

	BT_STATUS::Enum result = pNode->Tick(NULL);
	EXPECT_EQ(1, pNode->m_UpdateCalled);

	pNode->Tick(NULL);
	EXPECT_EQ(2, pNode->m_UpdateCalled);
}

//  *******************************************************************************************************************
TEST_F(BTBehaviorTest, Tick_TerminateCalled_Successful)
{
	shared_ptr<cMockBTNode> pNode(DEBUG_NEW cMockBTNode());
	pNode->DelegateToFake();

	pNode->Tick(NULL);
	EXPECT_EQ(0, pNode->m_TerminateCalled);

	pNode->SetStatus(BT_STATUS::Success);
	pNode->Tick(NULL);
	EXPECT_EQ(1, pNode->m_TerminateCalled);
}

//  *******************************************************************************************************************
TEST_F(BTBehaviorTest, SingleNode)
{
	shared_ptr<cSimpleNode> pSimpleNode = cBTNodeFactory::Create<cSimpleNode>()
		->SetA(1)
		->SetB(2.0f)
		->SetC(true);

	EXPECT_TRUE(pSimpleNode != NULL);
	EXPECT_EQ(pSimpleNode->GetA(), 1);
	EXPECT_EQ(pSimpleNode->GetB(), 2.0f);
	EXPECT_TRUE(pSimpleNode->GetC());
}
