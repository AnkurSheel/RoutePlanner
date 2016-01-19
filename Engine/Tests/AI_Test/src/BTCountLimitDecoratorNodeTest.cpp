#include "stdafx.h"
#include "BTCountLimitDecoratorNode.h"
#include "BTNodeFactory.h"
#include "MockBTNode.h"

using namespace AI;
using namespace Base;
using namespace testing;

class BTCountLimitDecoratorNodeTest : public ::testing::Test
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

AutoCaptureOutput * BTCountLimitDecoratorNodeTest::m_pOutput;

//  *******************************************************************************************************************
TEST_F(BTCountLimitDecoratorNodeTest, ZeroLimit)
{
	shared_ptr<cMockBTNode> pSuccessNode(new cMockBTNode);
	EXPECT_CALL(*pSuccessNode, VOnUpdate(NULL))
		.WillRepeatedly(Return(BT_STATUS::Success));

	shared_ptr<cBTCountLimitDecoratorNode> pCountLimitNode = cBTNodeFactory::Create<cBTCountLimitDecoratorNode>()
		->SetChild<cBTCountLimitDecoratorNode>(pSuccessNode);

	BT_STATUS::Enum result = pCountLimitNode->Tick(NULL);
	EXPECT_EQ(BT_STATUS::Failure, result);
}

//  *******************************************************************************************************************
TEST_F(BTCountLimitDecoratorNodeTest, ThreeLimit)
{
	shared_ptr<cMockBTNode> pSuccessNode(new cMockBTNode);
	EXPECT_CALL(*pSuccessNode, VOnUpdate(NULL))
		.WillRepeatedly(Return(BT_STATUS::Success));

	shared_ptr<cBTCountLimitDecoratorNode> pCountLimitNode = cBTNodeFactory::Create<cBTCountLimitDecoratorNode>()
		->SetLimit(3)
		->SetChild<cBTCountLimitDecoratorNode>(pSuccessNode);

	BT_STATUS::Enum result = pCountLimitNode->Tick(NULL);
	EXPECT_EQ(BT_STATUS::Success, result);
	result = pCountLimitNode->Tick(NULL);
	EXPECT_EQ(BT_STATUS::Success, result);
	result = pCountLimitNode->Tick(NULL);
	EXPECT_EQ(BT_STATUS::Success, result);
}

//  *******************************************************************************************************************
TEST_F(BTCountLimitDecoratorNodeTest, TwoLimitRunningSuccess)
{
	shared_ptr<cMockBTNode> pSuccessNode(new cMockBTNode);
	EXPECT_CALL(*pSuccessNode, VOnUpdate(NULL))
		.Times(AnyNumber())
		.WillOnce(Return(BT_STATUS::Running))
		.WillOnce(Return(BT_STATUS::Success))
		.WillOnce(Return(BT_STATUS::Running))
		.WillOnce(Return(BT_STATUS::Success))
		.WillOnce(Return(BT_STATUS::Running))
		.WillOnce(Return(BT_STATUS::Success))
		.WillOnce(Return(BT_STATUS::Running))
		.WillOnce(Return(BT_STATUS::Success));

	shared_ptr<cBTCountLimitDecoratorNode> pCountLimitNode = cBTNodeFactory::Create<cBTCountLimitDecoratorNode>()
		->SetLimit(2)
		->SetChild<cBTCountLimitDecoratorNode>(pSuccessNode);

	for (int i=0;i<2; i++)
	{
		pCountLimitNode->VOnInitialize(NULL);
		BT_STATUS::Enum result = pCountLimitNode->Tick(NULL);
		EXPECT_EQ(BT_STATUS::Running, result);
		result = pCountLimitNode->Tick(NULL);
		EXPECT_EQ(BT_STATUS::Success, result);
		result = pCountLimitNode->Tick(NULL);
		EXPECT_EQ(BT_STATUS::Running, result);
		result = pCountLimitNode->Tick(NULL);
		EXPECT_EQ(BT_STATUS::Success, result);
	}
}

//  *******************************************************************************************************************
TEST_F(BTCountLimitDecoratorNodeTest, TwoLimitRunningFailure)
{
	shared_ptr<cMockBTNode> pFailureNode(new cMockBTNode);
	EXPECT_CALL(*pFailureNode, VOnUpdate(NULL))
		.Times(AnyNumber())
		.WillOnce(Return(BT_STATUS::Running))
		.WillOnce(Return(BT_STATUS::Failure))
		.WillOnce(Return(BT_STATUS::Running))
		.WillOnce(Return(BT_STATUS::Failure))
		.WillOnce(Return(BT_STATUS::Running))
		.WillOnce(Return(BT_STATUS::Failure))
		.WillOnce(Return(BT_STATUS::Running))
		.WillOnce(Return(BT_STATUS::Failure));

	shared_ptr<cBTCountLimitDecoratorNode> pCountLimitNode = cBTNodeFactory::Create<cBTCountLimitDecoratorNode>()
		->SetLimit(2)
		->SetChild<cBTCountLimitDecoratorNode>(pFailureNode);

	for (int i=0;i<2; i++)
	{
		pCountLimitNode->VOnInitialize(NULL);
		BT_STATUS::Enum result = pCountLimitNode->Tick(NULL);
		EXPECT_EQ(BT_STATUS::Running, result);
		result = pCountLimitNode->Tick(NULL);
		EXPECT_EQ(BT_STATUS::Failure, result);
		result = pCountLimitNode->Tick(NULL);
		EXPECT_EQ(BT_STATUS::Running, result);
		result = pCountLimitNode->Tick(NULL);
		EXPECT_EQ(BT_STATUS::Failure, result);
	}
}

//  *******************************************************************************************************************
TEST_F(BTCountLimitDecoratorNodeTest, TwoLimitDisableReinit)
{
	shared_ptr<cMockBTNode> pSuccessNode(new cMockBTNode);
	EXPECT_CALL(*pSuccessNode, VOnUpdate(NULL))
		.Times(AnyNumber())
		.WillRepeatedly(Return(BT_STATUS::Success));

	shared_ptr<cBTCountLimitDecoratorNode> pCountLimitNode = cBTNodeFactory::Create<cBTCountLimitDecoratorNode>()
		->SetLimit(2)
		->SetAllowReinitialize(false)
		->SetChild<cBTCountLimitDecoratorNode>(pSuccessNode);

	pCountLimitNode->VOnInitialize(NULL);

	BT_STATUS::Enum result = pCountLimitNode->Tick(NULL);
	EXPECT_EQ(BT_STATUS::Success, result);
	result = pCountLimitNode->Tick(NULL);
	EXPECT_EQ(BT_STATUS::Success, result);
	result = pCountLimitNode->Tick(NULL);
	EXPECT_EQ(BT_STATUS::Failure, result);

	for (int i=0; i < 2; i++)
	{
		pCountLimitNode->VOnInitialize(NULL);
		result = pCountLimitNode->Tick(NULL);
		EXPECT_EQ(BT_STATUS::Failure, result);
		result = pCountLimitNode->Tick(NULL);
		EXPECT_EQ(BT_STATUS::Failure, result);
	}
}
