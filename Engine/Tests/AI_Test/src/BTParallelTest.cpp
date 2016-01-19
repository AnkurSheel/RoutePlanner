#include "stdafx.h"
#include "BTParallelNode.h"
#include "PrintTextNode.h"
#include "BTNodeFactory.h"
#include "MockBTNode.h"

using namespace AI;
using namespace Base;
using namespace ::testing;

class BTParallelTest : public ::testing::Test
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

AutoCaptureOutput * BTParallelTest::m_pOutput = NULL;

//  *******************************************************************************************************************
TEST_F(BTParallelTest, TestBTParallelErrors)
{
	shared_ptr<cBTParallelNode> pParallelNode = cBTNodeFactory::Create<cBTParallelNode>();

	BT_STATUS::Enum result = pParallelNode->Tick(NULL);
	EXPECT_EQ(BT_STATUS::Invalid, result);

	result = pParallelNode->Tick(NULL);
	EXPECT_EQ(BT_STATUS::Invalid, result);
}

//  *******************************************************************************************************************
TEST_F(BTParallelTest, OneChildFails)
{
	shared_ptr<cMockBTNode> pFailureNode(new cMockBTNode);
	EXPECT_CALL(*pFailureNode, VOnUpdate(NULL))
		.WillRepeatedly(Return(BT_STATUS::Failure));

	shared_ptr<cBTParallelNode> pParallelNode = cBTNodeFactory::Create<cBTParallelNode>()
		->AddChild<cBTParallelNode>(pFailureNode);

	BT_STATUS::Enum result = pParallelNode->Tick(NULL);
	EXPECT_EQ(BT_STATUS::Failure, result);
}

//  *******************************************************************************************************************
TEST_F(BTParallelTest, OneChildCompletes)
{
	shared_ptr<cMockBTNode> pSuccessNode(new cMockBTNode);
	EXPECT_CALL(*pSuccessNode, VOnUpdate(NULL))
		.WillRepeatedly(Return(BT_STATUS::Success));

	shared_ptr<cBTParallelNode> pParallelNode = cBTNodeFactory::Create<cBTParallelNode>()
		->AddChild<cBTParallelNode>(pSuccessNode);

	BT_STATUS::Enum result = pParallelNode->Tick(NULL);
	EXPECT_EQ(BT_STATUS::Success, result);
}
//
//  *******************************************************************************************************************
TEST_F(BTParallelTest, MultipleChildFailure)
{
	shared_ptr<cMockBTNode> pFailureNode(new cMockBTNode);
	EXPECT_CALL(*pFailureNode, VOnUpdate(NULL))
		.WillOnce(Return(BT_STATUS::Running))
		.WillOnce(Return(BT_STATUS::Running))
		.WillOnce(Return(BT_STATUS::Failure));

	shared_ptr<cMockBTNode> pSuccessNode1(new cMockBTNode);
	EXPECT_CALL(*pSuccessNode1, VOnUpdate(NULL))
		.WillRepeatedly(Return(BT_STATUS::Success));

	shared_ptr<cMockBTNode> pSuccessNode2(new cMockBTNode);
	EXPECT_CALL(*pSuccessNode2, VOnUpdate(NULL))
		.WillOnce(Return(BT_STATUS::Running))
		.WillOnce(Return(BT_STATUS::Success));

	shared_ptr<cBTParallelNode> pParallelNode = cBTNodeFactory::Create<cBTParallelNode>()
		->AddChild<cBTParallelNode>(pSuccessNode1)
		->AddChild<cBTParallelNode>(pFailureNode)
		->AddChild<cBTParallelNode>(pSuccessNode2);

	BT_STATUS::Enum result = pParallelNode->Tick(NULL);
	EXPECT_EQ(BT_STATUS::Running, result);
	result = pParallelNode->Tick(NULL);
	EXPECT_EQ(BT_STATUS::Running, result);
	result = pParallelNode->Tick(NULL);
	EXPECT_EQ(BT_STATUS::Failure, result);;
}

//  *******************************************************************************************************************
TEST_F(BTParallelTest, MultipleChildSuccess)
{
	shared_ptr<cMockBTNode> pSuccessNode1(new cMockBTNode);
	EXPECT_CALL(*pSuccessNode1, VOnUpdate(NULL))
		.WillRepeatedly(Return(BT_STATUS::Success));

	shared_ptr<cMockBTNode> pSuccessNode2(new cMockBTNode);
	EXPECT_CALL(*pSuccessNode2, VOnUpdate(NULL))
		.WillOnce(Return(BT_STATUS::Running))
		.WillOnce(Return(BT_STATUS::Running))
		.WillOnce(Return(BT_STATUS::Success));

	shared_ptr<cBTParallelNode> pParallelNode = cBTNodeFactory::Create<cBTParallelNode>()
		->AddChild<cBTParallelNode>(pSuccessNode1)
		->AddChild<cBTParallelNode>(pSuccessNode2);

	BT_STATUS::Enum result;
	result = pParallelNode->Tick(NULL);
	EXPECT_EQ(BT_STATUS::Running, result);
	result = pParallelNode->Tick(NULL);
	EXPECT_EQ(BT_STATUS::Running, result);
	result = pParallelNode->Tick(NULL);
	EXPECT_EQ(BT_STATUS::Success, result);;
}

//  *******************************************************************************************************************
TEST_F(BTParallelTest, RequireAllFailurePolicyLimbo)
{
	shared_ptr<cMockBTNode> pFailureNode(new cMockBTNode);
	EXPECT_CALL(*pFailureNode, VOnUpdate(NULL))
		.Times(AnyNumber())
		.WillOnce(Return(BT_STATUS::Running))
		.WillOnce(Return(BT_STATUS::Running))
		.WillOnce(Return(BT_STATUS::Failure))
		.WillOnce(Return(BT_STATUS::Running))
		.WillOnce(Return(BT_STATUS::Running))
		.WillOnce(Return(BT_STATUS::Failure));

	shared_ptr<cMockBTNode> pSuccessNode1(new cMockBTNode);
	EXPECT_CALL(*pSuccessNode1, VOnUpdate(NULL))
		.WillRepeatedly(Return(BT_STATUS::Failure));

	shared_ptr<cMockBTNode> pSuccessNode2(new cMockBTNode);
	EXPECT_CALL(*pSuccessNode2, VOnUpdate(NULL))
		.Times(AnyNumber())
		.WillOnce(Return(BT_STATUS::Running))
		.WillOnce(Return(BT_STATUS::Running))
		.WillOnce(Return(BT_STATUS::Success))
		.WillOnce(Return(BT_STATUS::Running))
		.WillOnce(Return(BT_STATUS::Running))
		.WillOnce(Return(BT_STATUS::Success));

	shared_ptr<cBTParallelNode> pParallelNode = cBTNodeFactory::Create<cBTParallelNode>()
		->SetFailurePolicy(BT_POLICY::RequireAll)
		->AddChild<cBTParallelNode>(pSuccessNode1)
		->AddChild<cBTParallelNode>(pFailureNode)
		->AddChild<cBTParallelNode>(pSuccessNode2);

	BT_STATUS::Enum result;
	for (int i=0; i<2; i++)
	{
		result = pParallelNode->Tick(NULL);
		EXPECT_EQ(BT_STATUS::Running, result);
		result = pParallelNode->Tick(NULL);
		EXPECT_EQ(BT_STATUS::Running, result);
		result = pParallelNode->Tick(NULL);
		EXPECT_EQ(BT_STATUS::Running, result);;
	}
}

//  *******************************************************************************************************************
TEST_F(BTParallelTest, RequireAllFailurePolicy)
{
	shared_ptr<cMockBTNode> pFailureNode(new cMockBTNode);
	EXPECT_CALL(*pFailureNode, VOnUpdate(NULL))
		.Times(AnyNumber())
		.WillOnce(Return(BT_STATUS::Running))
		.WillOnce(Return(BT_STATUS::Running))
		.WillOnce(Return(BT_STATUS::Failure))
		.WillOnce(Return(BT_STATUS::Running))
		.WillOnce(Return(BT_STATUS::Running))
		.WillOnce(Return(BT_STATUS::Failure));

	shared_ptr<cMockBTNode> pSuccessNode1(new cMockBTNode);
	EXPECT_CALL(*pSuccessNode1, VOnUpdate(NULL))
		.WillRepeatedly(Return(BT_STATUS::Failure));

	shared_ptr<cMockBTNode> pSuccessNode2(new cMockBTNode);
	EXPECT_CALL(*pSuccessNode2, VOnUpdate(NULL))
		.Times(AnyNumber())
		.WillOnce(Return(BT_STATUS::Running))
		.WillOnce(Return(BT_STATUS::Running))
		.WillOnce(Return(BT_STATUS::Failure));

	shared_ptr<cBTParallelNode> pParallelNode = cBTNodeFactory::Create<cBTParallelNode>()
		->SetFailurePolicy(BT_POLICY::RequireAll)
		->AddChild<cBTParallelNode>(pSuccessNode1)
		->AddChild<cBTParallelNode>(pFailureNode)
		->AddChild<cBTParallelNode>(pSuccessNode2);

	BT_STATUS::Enum result;
	result = pParallelNode->Tick(NULL);
	EXPECT_EQ(BT_STATUS::Running, result);
	result = pParallelNode->Tick(NULL);
	EXPECT_EQ(BT_STATUS::Running, result);
	result = pParallelNode->Tick(NULL);
	EXPECT_EQ(BT_STATUS::Failure, result);;
}

//  *******************************************************************************************************************
TEST_F(BTParallelTest, SucceedRequireOneFailureRequireOne)
{
	shared_ptr<cMockBTNode> pFailureNode(new cMockBTNode);
	EXPECT_CALL(*pFailureNode, VOnUpdate(NULL))
		.Times(AnyNumber())
		.WillOnce(Return(BT_STATUS::Running))
		.WillOnce(Return(BT_STATUS::Running))
		.WillOnce(Return(BT_STATUS::Failure))
		.WillOnce(Return(BT_STATUS::Running))
		.WillOnce(Return(BT_STATUS::Running))
		.WillOnce(Return(BT_STATUS::Failure));

	shared_ptr<cMockBTNode> pSuccessNode(new cMockBTNode);
	EXPECT_CALL(*pSuccessNode, VOnUpdate(NULL))
		.Times(AnyNumber())
		.WillOnce(Return(BT_STATUS::Running))
		.WillRepeatedly(Return(BT_STATUS::Success));

	shared_ptr<cBTParallelNode> pParallelNode = cBTNodeFactory::Create<cBTParallelNode>()
		->SetSuccessPolicy(BT_POLICY::RequireOne)
		->AddChild<cBTParallelNode>(pFailureNode)
		->AddChild<cBTParallelNode>(pSuccessNode);

	BT_STATUS::Enum result;
	result = pParallelNode->Tick(NULL);
	EXPECT_EQ(BT_STATUS::Running, result);
	result = pParallelNode->Tick(NULL);
	EXPECT_EQ(BT_STATUS::Running, result);
	result = pParallelNode->Tick(NULL);
	EXPECT_EQ(BT_STATUS::Failure, result);;
}

//  *******************************************************************************************************************
TEST_F(BTParallelTest, SucceedRequireOneFailureRequireAll)
{
	shared_ptr<cMockBTNode> pFailureNode(new cMockBTNode);
	EXPECT_CALL(*pFailureNode, VOnUpdate(NULL))
		.Times(AnyNumber())
		.WillOnce(Return(BT_STATUS::Running))
		.WillOnce(Return(BT_STATUS::Running))
		.WillOnce(Return(BT_STATUS::Success))
		.WillOnce(Return(BT_STATUS::Running))
		.WillOnce(Return(BT_STATUS::Running))
		.WillOnce(Return(BT_STATUS::Success));

	shared_ptr<cMockBTNode> pSuccessNode(new cMockBTNode);
	EXPECT_CALL(*pSuccessNode, VOnUpdate(NULL))
		.Times(AnyNumber())
		.WillOnce(Return(BT_STATUS::Running))
		.WillRepeatedly(Return(BT_STATUS::Failure));

	shared_ptr<cBTParallelNode> pParallelNode = cBTNodeFactory::Create<cBTParallelNode>()
		->SetSuccessPolicy(BT_POLICY::RequireOne)
		->SetFailurePolicy(BT_POLICY::RequireAll)
		->AddChild<cBTParallelNode>(pFailureNode)
		->AddChild<cBTParallelNode>(pSuccessNode);


	BT_STATUS::Enum result;
	result = pParallelNode->Tick(NULL);
	EXPECT_EQ(BT_STATUS::Running, result);
	result = pParallelNode->Tick(NULL);
	EXPECT_EQ(BT_STATUS::Running, result);
	result = pParallelNode->Tick(NULL);
	EXPECT_EQ(BT_STATUS::Success, result);;
}
