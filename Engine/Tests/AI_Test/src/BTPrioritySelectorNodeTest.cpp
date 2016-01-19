#include "stdafx.h"
#include "BTPrioritySelectorNode.h"
#include "BTNodeFactory.h"
//#include "BTTreebuilder.h"
#include "MockBTNode.h"

using namespace AI;
using namespace Base;
using namespace testing;

class BTPrioritySelectorTest : public ::testing::Test
{
protected:
	static void SetUpTestCase()
	{
		m_pOutput = new AutoCaptureOutput();
	}

	static void TearDownTestCase() 
	{
		SafeDelete(&m_pOutput);
	}

	void SetUp()
	{

	}

	void TearDown()
	{
	}

	static AutoCaptureOutput * m_pOutput;
};

AutoCaptureOutput * BTPrioritySelectorTest::m_pOutput = NULL;

//  *******************************************************************************************************************
TEST_F(BTPrioritySelectorTest, TestBTPrioritySelectorInitial)
{
	shared_ptr<cBTPrioritySelectorNode> pPrioritySelectorNode = cBTNodeFactory::Create<cBTPrioritySelectorNode>();

	EXPECT_EQ(-1, pPrioritySelectorNode->GetCurrentChildIndex());

	BT_STATUS::Enum result = pPrioritySelectorNode->Tick(NULL);
	EXPECT_EQ(BT_STATUS::Invalid, result);
}

//  *******************************************************************************************************************
TEST_F(BTPrioritySelectorTest, AlwaysRunning)
{
	shared_ptr<cMockBTNode> pAlwaysRunningNode(new cMockBTNode);
	EXPECT_CALL(*pAlwaysRunningNode, VOnUpdate(NULL))
		.WillRepeatedly(Return(BT_STATUS::Running));

	shared_ptr<cBTPrioritySelectorNode> pPrioritySelectorNode = cBTNodeFactory::Create<cBTPrioritySelectorNode>()
		->AddChild<cBTPrioritySelectorNode>(pAlwaysRunningNode);

	BT_STATUS::Enum result = pPrioritySelectorNode->Tick(NULL);
	EXPECT_EQ(0, pPrioritySelectorNode->GetCurrentChildIndex());
	EXPECT_EQ(BT_STATUS::Running, result);

	result = pPrioritySelectorNode->Tick(NULL);
	EXPECT_EQ(0, pPrioritySelectorNode->GetCurrentChildIndex());
	EXPECT_EQ(BT_STATUS::Running, result);
}

//  *******************************************************************************************************************
TEST_F(BTPrioritySelectorTest, TestBTPrioritySelector1)
{
	shared_ptr<cMockBTNode> pFailureAfterNode1(new cMockBTNode);
	EXPECT_CALL(*pFailureAfterNode1, VOnUpdate(NULL))
		.WillRepeatedly(Return(BT_STATUS::Failure));

	shared_ptr<cMockBTNode> pFailureAfterNode2(new cMockBTNode);
	EXPECT_CALL(*pFailureAfterNode2, VOnUpdate(NULL))
		.WillRepeatedly(Return(BT_STATUS::Failure));

	shared_ptr<cMockBTNode> pSuccessAfterNode(new cMockBTNode);
	EXPECT_CALL(*pSuccessAfterNode, VOnUpdate(NULL))
		.WillRepeatedly(Return(BT_STATUS::Success));

	shared_ptr<cBTPrioritySelectorNode> pPrioritySelectorNode = cBTNodeFactory::Create<cBTPrioritySelectorNode>()
		->AddChild<cBTPrioritySelectorNode>(pFailureAfterNode1)
		->AddChild<cBTPrioritySelectorNode>(pFailureAfterNode2)
		->AddChild<cBTPrioritySelectorNode>(pSuccessAfterNode);

	BT_STATUS::Enum result = pPrioritySelectorNode->Tick(NULL);
	EXPECT_EQ(1, pPrioritySelectorNode->GetCurrentChildIndex());
	EXPECT_EQ(BT_STATUS::Running, result);

	result = pPrioritySelectorNode->Tick(NULL);
	EXPECT_EQ(2, pPrioritySelectorNode->GetCurrentChildIndex());
	EXPECT_EQ(BT_STATUS::Running, result);

	result = pPrioritySelectorNode->Tick(NULL);
	EXPECT_EQ(BT_STATUS::Success, result);
}

//  *******************************************************************************************************************
TEST_F(BTPrioritySelectorTest, TestBTPrioritySelector2)
{
	shared_ptr<cMockBTNode> pSuccessAfterNode1(new cMockBTNode);
	EXPECT_CALL(*pSuccessAfterNode1, VOnUpdate(NULL))
		.WillRepeatedly(Return(BT_STATUS::Success));

	shared_ptr<cMockBTNode> pFailureAfterNode1(new cMockBTNode);
	EXPECT_CALL(*pFailureAfterNode1, VOnUpdate(NULL))
		.WillRepeatedly(Return(BT_STATUS::Failure));

	shared_ptr<cMockBTNode> pSuccessAfterNode2(new cMockBTNode);
	EXPECT_CALL(*pSuccessAfterNode2, VOnUpdate(NULL))
		.WillRepeatedly(Return(BT_STATUS::Success));

	shared_ptr<cBTPrioritySelectorNode> pPrioritySelectorNode = cBTNodeFactory::Create<cBTPrioritySelectorNode>()
		->AddChild<cBTPrioritySelectorNode>(pSuccessAfterNode1)
		->AddChild<cBTPrioritySelectorNode>(pFailureAfterNode1)
		->AddChild<cBTPrioritySelectorNode>(pSuccessAfterNode2);

	BT_STATUS::Enum result = pPrioritySelectorNode->Tick(NULL);
	EXPECT_EQ(BT_STATUS::Success, result);
}

//  *******************************************************************************************************************
TEST_F(BTPrioritySelectorTest, TestBTPrioritySelector3)
{
	shared_ptr<cMockBTNode> pFailureAfterNode1(new cMockBTNode);
	EXPECT_CALL(*pFailureAfterNode1, VOnUpdate(NULL))
		.WillRepeatedly(Return(BT_STATUS::Failure));

	shared_ptr<cMockBTNode> pFailureAfterNode2(new cMockBTNode);
	EXPECT_CALL(*pFailureAfterNode2, VOnUpdate(NULL))
		.WillRepeatedly(Return(BT_STATUS::Failure));

	shared_ptr<cBTPrioritySelectorNode> pPrioritySelectorNode = cBTNodeFactory::Create<cBTPrioritySelectorNode>()
		->AddChild<cBTPrioritySelectorNode>(pFailureAfterNode1)
		->AddChild<cBTPrioritySelectorNode>(pFailureAfterNode2);

	BT_STATUS::Enum result = pPrioritySelectorNode->Tick(NULL);
	EXPECT_EQ(1, pPrioritySelectorNode->GetCurrentChildIndex());
	EXPECT_EQ(BT_STATUS::Running, result);

	result = pPrioritySelectorNode->Tick(NULL);
	EXPECT_EQ(BT_STATUS::Failure, result);
}

//  *******************************************************************************************************************
TEST_F(BTPrioritySelectorTest, PropogateError)
{
	shared_ptr<cMockBTNode> pErrorNode(new cMockBTNode);
	EXPECT_CALL(*pErrorNode, VOnUpdate(NULL))
		.WillRepeatedly(Return(BT_STATUS::Invalid));

	shared_ptr<cMockBTNode> pSuccessAfterNode1(new cMockBTNode);
	EXPECT_CALL(*pSuccessAfterNode1, VOnUpdate(NULL))
		.WillRepeatedly(Return(BT_STATUS::Success));

	shared_ptr<cBTPrioritySelectorNode> pPrioritySelectorNode = cBTNodeFactory::Create<cBTPrioritySelectorNode>()
		->AddChild<cBTPrioritySelectorNode>(pErrorNode)
		->AddChild<cBTPrioritySelectorNode>(pSuccessAfterNode1);

	BT_STATUS::Enum result = pPrioritySelectorNode->Tick(NULL);
	EXPECT_EQ(BT_STATUS::Invalid, result);
}
