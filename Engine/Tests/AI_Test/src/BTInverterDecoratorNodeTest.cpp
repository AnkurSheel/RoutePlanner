#include "stdafx.h"
#include "BTInverterDecoratorNode.h"
#include "BTNodeFactory.h"
#include "MockBTNode.h"

using namespace AI;
using namespace Base;
using namespace testing;

class BTInverterDecoratorNodeTest : public ::testing::Test
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

AutoCaptureOutput * BTInverterDecoratorNodeTest::m_pOutput;

////  *******************************************************************************************************************
//TEST_F(BTInverterDecoratorNodeTest, ChildSuccess)
//{
//	shared_ptr<cMockBTNode> pChildNode(new cMockBTNode);
//	EXPECT_CALL(*pChildNode, VOnUpdate(NULL))
//		.WillRepeatedly(Return(BT_STATUS::Success));
//
//	shared_ptr<cBTInverterDecoratorNode> pInverterNode = cBTNodeFactory::Create<cBTInverterDecoratorNode>()
//		->SetChild<cBTInverterDecoratorNode>(pChildNode);
//
//	pInverterNode->VOnEnter(NULL);
//	BT_STATUS::Enum result = pInverterNode->VOnUpdate(NULL);
//	EXPECT_EQ(BT_STATUS::Failure, result);
//}
//
//
////  *******************************************************************************************************************
//TEST_F(BTInverterDecoratorNodeTest, ChildFailure)
//{
//	shared_ptr<cMockBTNode> pChildNode(new cMockBTNode);
//	EXPECT_CALL(*pChildNode, VOnUpdate(NULL))
//		.WillRepeatedly(Return(BT_STATUS::Failure));
//
//	shared_ptr<cBTInverterDecoratorNode> pInverterNode = cBTNodeFactory::Create<cBTInverterDecoratorNode>()
//		->SetChild<cBTInverterDecoratorNode>(pChildNode);
//
//	pInverterNode->VOnEnter(NULL);
//	BT_STATUS::Enum result = pInverterNode->VOnUpdate(NULL);
//	EXPECT_EQ(BT_STATUS::Success, result);
//}
//
////  *******************************************************************************************************************
//TEST_F(BTInverterDecoratorNodeTest, ChildRunning)
//{
//	shared_ptr<cMockBTNode> pChildNode(new cMockBTNode);
//	EXPECT_CALL(*pChildNode, VOnUpdate(NULL))
//		.WillRepeatedly(Return(BT_STATUS::Running));
//
//	shared_ptr<cBTInverterDecoratorNode> pInverterNode = cBTNodeFactory::Create<cBTInverterDecoratorNode>()
//		->SetChild<cBTInverterDecoratorNode>(pChildNode);
//
//	pInverterNode->VOnEnter(NULL);
//	for (int i=0; i< 10; i++)
//	{
//		BT_STATUS::Enum result = pInverterNode->VOnUpdate(NULL);
//		EXPECT_EQ(BT_STATUS::Running, result);
//	}
//}
//
////  *******************************************************************************************************************
//TEST_F(BTInverterDecoratorNodeTest, ChildError)
//{
//	shared_ptr<cMockBTNode> pChildNode(new cMockBTNode);
//	EXPECT_CALL(*pChildNode, VOnUpdate(NULL))
//		.WillRepeatedly(Return(BT_STATUS::Invalid));
//
//	shared_ptr<cBTInverterDecoratorNode> pInverterNode = cBTNodeFactory::Create<cBTInverterDecoratorNode>()
//		->SetChild<cBTInverterDecoratorNode>(pChildNode);
//
//	pInverterNode->VInitialize(NULL);
//	for (int i=0; i< 10; i++)
//	{
//		BT_STATUS::Enum result = pInverterNode->VOnUpdate(NULL);
//		EXPECT_EQ(BT_STATUS::Invalid, result);
//	}
//}
