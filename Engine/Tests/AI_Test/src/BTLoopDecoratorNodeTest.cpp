#include "stdafx.h"
#include "BTLoopDecoratorNode.h"
#include "BTNodeFactory.h"
#include "MockBTNode.h"

using namespace AI;
using namespace Base;
using namespace testing;

class BTLoopDecoratorNodeTest : public ::testing::Test
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

AutoCaptureOutput * BTLoopDecoratorNodeTest::m_pOutput;

//  *******************************************************************************************************************
TEST_F(BTLoopDecoratorNodeTest, RepeatSimple1)
{
	shared_ptr<cMockBTNode> pSuccessNode(new cMockBTNode);
	EXPECT_CALL(*pSuccessNode, VOnUpdate(NULL))
		.WillRepeatedly(Return(BT_STATUS::Success));

	shared_ptr<cBTLoopDecoratorNode> pLoopNode = cBTNodeFactory::Create<cBTLoopDecoratorNode>()
		->SetRepeats(5)
		->SetChild<cBTLoopDecoratorNode>(pSuccessNode);

	BT_STATUS::Enum result;
	for (int i = 0 ; i<2 ; i++)
	{
		result = pLoopNode->Tick(NULL);
		EXPECT_EQ(BT_STATUS::Running, result);
		result = pLoopNode->Tick(NULL);
		EXPECT_EQ(BT_STATUS::Running, result);
		result = pLoopNode->Tick(NULL);
		EXPECT_EQ(BT_STATUS::Running, result);
		result = pLoopNode->Tick(NULL);
		EXPECT_EQ(BT_STATUS::Running, result);
		result = pLoopNode->Tick(NULL);
		EXPECT_EQ(BT_STATUS::Success, result);
	}
}

//  *******************************************************************************************************************
TEST_F(BTLoopDecoratorNodeTest, RepeatSimple2)
{
	shared_ptr<cMockBTNode> pFailureNode(new cMockBTNode);
	EXPECT_CALL(*pFailureNode, VOnUpdate(NULL))
		.WillRepeatedly(Return(BT_STATUS::Failure));

	shared_ptr<cBTLoopDecoratorNode> pLoopNode = cBTNodeFactory::Create<cBTLoopDecoratorNode>()
		->SetRepeats(5)
		->SetChild<cBTLoopDecoratorNode>(pFailureNode);

	BT_STATUS::Enum result = pLoopNode->Tick(NULL);
	EXPECT_EQ(BT_STATUS::Failure, result);
}
