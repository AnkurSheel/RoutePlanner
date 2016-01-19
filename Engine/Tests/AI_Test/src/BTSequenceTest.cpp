#include "stdafx.h"
#include "BTSequenceNode.h"
#include "PrintTextNode.h"
#include "BTNodeFactory.h"
#include "MockBTNode.h"

using namespace AI;
using namespace Base;
using ::testing::Return;

class BTSequenceTest : public ::testing::Test
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

AutoCaptureOutput * BTSequenceTest::m_pOutput = NULL;

//  *******************************************************************************************************************
TEST_F(BTSequenceTest, TestBTSequenceInitial)
{
	shared_ptr<cBTSequenceNode> pSequenceNode = cBTNodeFactory::Create<cBTSequenceNode>();

	BT_STATUS::Enum result = pSequenceNode->Tick(NULL);
	EXPECT_EQ(BT_STATUS::Invalid, result);
}

//  *******************************************************************************************************************
TEST_F(BTSequenceTest, TestBTSequenceRunning)
{
	shared_ptr<cMockBTNode> pAlwaysRunningNode(new cMockBTNode);
	EXPECT_CALL(*pAlwaysRunningNode, VOnUpdate(NULL))
		.WillRepeatedly(Return(BT_STATUS::Running));

	shared_ptr<cBTSequenceNode> pSequenceNode = cBTNodeFactory::Create<cBTSequenceNode>()
		->AddChild<cBTSequenceNode>(pAlwaysRunningNode);

	BT_STATUS::Enum result = pSequenceNode->Tick(NULL);
	EXPECT_EQ(0, pSequenceNode->GetActiveChildIndex());
	EXPECT_EQ(BT_STATUS::Running, result);

	result = pSequenceNode->Tick(NULL);
	EXPECT_EQ(0, pSequenceNode->GetActiveChildIndex());
	EXPECT_EQ(BT_STATUS::Running, result);
}

//  *******************************************************************************************************************
TEST_F(BTSequenceTest, TestBT1ChildSequenceSuccess)
{
	shared_ptr<cMockBTNode> pSuccessAfterNode(new cMockBTNode);
	EXPECT_CALL(*pSuccessAfterNode, VOnUpdate(NULL))
		.WillOnce(Return(BT_STATUS::Running))
		.WillOnce(Return(BT_STATUS::Success));

	shared_ptr<cBTSequenceNode> pSequenceNode = cBTNodeFactory::Create<cBTSequenceNode>()
		->AddChild<cBTSequenceNode>(pSuccessAfterNode);

	BT_STATUS::Enum result = pSequenceNode->Tick(NULL);
	EXPECT_EQ(0, pSequenceNode->GetActiveChildIndex());
	EXPECT_EQ(BT_STATUS::Running, result);

	result = pSequenceNode->Tick(NULL);
	EXPECT_EQ(BT_STATUS::Success, result);
}

//  *******************************************************************************************************************
TEST_F(BTSequenceTest, TestBT2ChildSequenceSuccess)
{
	shared_ptr<cMockBTNode> pSuccessAfterNode1(new cMockBTNode);
	EXPECT_CALL(*pSuccessAfterNode1, VOnUpdate(NULL))
		.WillOnce(Return(BT_STATUS::Running))
		.WillOnce(Return(BT_STATUS::Success));

	shared_ptr<cMockBTNode> pSuccessAfterNode2(new cMockBTNode);
	EXPECT_CALL(*pSuccessAfterNode2, VOnUpdate(NULL))
		.WillOnce(Return(BT_STATUS::Success));

	shared_ptr<cBTSequenceNode> pSequenceNode = cBTNodeFactory::Create<cBTSequenceNode>()
		->AddChild<cBTSequenceNode>(pSuccessAfterNode1)
		->AddChild<cBTSequenceNode>(pSuccessAfterNode2);

	BT_STATUS::Enum result = pSequenceNode->Tick(NULL);
	EXPECT_EQ(0, pSequenceNode->GetActiveChildIndex());
	EXPECT_EQ(BT_STATUS::Running, result);

	result = pSequenceNode->Tick(NULL);
	EXPECT_EQ(1, pSequenceNode->GetActiveChildIndex());
	EXPECT_EQ(BT_STATUS::Running, result);

	result = pSequenceNode->Tick(NULL);
	EXPECT_EQ(BT_STATUS::Success, result);
}

//  *******************************************************************************************************************
TEST_F(BTSequenceTest, TestBT2ChildSequenceFailure)
{
	shared_ptr<cMockBTNode> pFailureAfterNode(new cMockBTNode);
	EXPECT_CALL(*pFailureAfterNode, VOnUpdate(NULL))
		.WillOnce(Return(BT_STATUS::Running))
		.WillOnce(Return(BT_STATUS::Failure));

	shared_ptr<cMockBTNode> pSuccessAfterNode(new cMockBTNode);

	shared_ptr<cBTSequenceNode> pSequenceNode = cBTNodeFactory::Create<cBTSequenceNode>()
		->AddChild<cBTSequenceNode>(pFailureAfterNode)
		->AddChild<cBTSequenceNode>(pSuccessAfterNode);

	BT_STATUS::Enum result = pSequenceNode->Tick(NULL);
	EXPECT_EQ(0, pSequenceNode->GetActiveChildIndex());
	EXPECT_EQ(BT_STATUS::Running, result);

	result = pSequenceNode->Tick(NULL);
	EXPECT_EQ(BT_STATUS::Failure, result);
}

//  *******************************************************************************************************************
TEST_F(BTSequenceTest, TestBT3ChildSequence)
{
	shared_ptr<cBTSequenceNode> pSequenceNode = cBTNodeFactory::Create<cBTSequenceNode>()
		->AddChild<cBTSequenceNode>(cBTNodeFactory::Create<cPrintTextNode>()
			->SetText("1,"))
		->AddChild<cBTSequenceNode>(cBTNodeFactory::Create<cPrintTextNode>()
			->SetText("2..."))
		->AddChild<cBTSequenceNode>(cBTNodeFactory::Create<cPrintTextNode>()
			->SetText("3!"));

  m_pOutput->reset();
	BT_STATUS::Enum result = pSequenceNode->Tick(NULL);
	result = pSequenceNode->Tick(NULL);
	result = pSequenceNode->Tick(NULL);

	CHECK_OUTPUT("1,\n2...\n3!\n");
}

//  *******************************************************************************************************************
TEST_F(BTSequenceTest, PropogateError)
{
	shared_ptr<cMockBTNode> pErrorNode(new cMockBTNode);

	shared_ptr<cBTSequenceNode> pSequenceNode = cBTNodeFactory::Create<cBTSequenceNode>()
		->AddChild<cBTSequenceNode>(pErrorNode)
		->AddChild<cBTSequenceNode>(cBTNodeFactory::Create<cPrintTextNode>()
			->SetText("2..."));

	EXPECT_CALL(*pErrorNode, VOnUpdate(NULL))
		.WillRepeatedly(Return(BT_STATUS::Invalid));

	BT_STATUS::Enum result = pSequenceNode->Tick(NULL);
	EXPECT_EQ(BT_STATUS::Invalid, result);
}
