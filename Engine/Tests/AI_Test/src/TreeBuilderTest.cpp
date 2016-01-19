#include "stdafx.h"
#include "BTNode.h"
#include "BTSequenceNode.h"
#include "BTParallelNode.h"
#include "BTProbabilitySelectorNode.h"
#include "BTPrioritySelectorNode.h"
#include "BTNodeFactory.h"
#include "BTInverterDecoratorNode.h"

using namespace AI;
using namespace Base;

class cSimpleNode 
	: public cBTNode
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


class BTTreeBuilderTest : public ::testing::Test
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

AutoCaptureOutput * BTTreeBuilderTest::m_pOutput;

//  *******************************************************************************************************************
TEST_F(BTTreeBuilderTest, SingleNode)
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

//  *******************************************************************************************************************
TEST_F(BTTreeBuilderTest, CompositeData)
{
	shared_ptr<cBTParallelNode> pParallelNode = cBTNodeFactory::Create<cBTParallelNode>();

	pParallelNode
		->SetSuccessPolicy(BT_POLICY::RequireAll)
		->SetFailurePolicy(BT_POLICY::RequireAll);

	EXPECT_TRUE(pParallelNode != NULL);
	EXPECT_EQ(pParallelNode->GetSuccessPolicy(), BT_POLICY::RequireAll);
	EXPECT_EQ(pParallelNode->GetFailurePolicy(), BT_POLICY::RequireAll);
}

//  *******************************************************************************************************************
TEST_F(BTTreeBuilderTest, CompositeCustomAttribute)
{
	shared_ptr<cBTProbabilitySelectorNode> pProbabilitySelectorNode = cBTNodeFactory::Create<cBTProbabilitySelectorNode>()
		->AddChild<cBTProbabilitySelectorNode>(cBTNodeFactory::Create<cSimpleNode>())
		->SetWeight(1)
		->AddChild<cBTProbabilitySelectorNode>(cBTNodeFactory::Create<cSimpleNode>())
		->SetWeight(2)
		->SetWeight(3)
		->AddChild<cBTProbabilitySelectorNode>(cBTNodeFactory::Create<cSimpleNode>());

	pProbabilitySelectorNode->VOnEnter(NULL);
	EXPECT_EQ(pProbabilitySelectorNode->GetWeights().size(), 3);
	EXPECT_EQ(pProbabilitySelectorNode->GetWeights()[0], 1.0f);
	EXPECT_EQ(pProbabilitySelectorNode->GetWeights()[1], 2.0f);
	EXPECT_EQ(pProbabilitySelectorNode->GetWeights()[2], 3.0f);
}

//  *******************************************************************************************************************
TEST_F(BTTreeBuilderTest, CompositeChildren)
{
	shared_ptr<cBTPrioritySelectorNode> pPrioritySelectorNode = cBTNodeFactory::Create<cBTPrioritySelectorNode>()
		->AddChild<cBTPrioritySelectorNode>(cBTNodeFactory::Create<cSimpleNode>()
			->SetA(3))
		->AddChild<cBTPrioritySelectorNode>(cBTNodeFactory::Create<cSimpleNode>()
			->SetB(4.0f));

	EXPECT_EQ(2, pPrioritySelectorNode->GetSize());

	BTNodeStrongPtr pChild0 = MakeStrongPtr(pPrioritySelectorNode ->GetChildAt(0));
	EXPECT_EQ(pPrioritySelectorNode , MakeStrongPtr(pChild0->GetParent()));
	EXPECT_TRUE(dynamic_pointer_cast<cSimpleNode>(pChild0) != NULL);
}

//  *******************************************************************************************************************
TEST_F(BTTreeBuilderTest, NestedComposites)
{
	shared_ptr<cBTPrioritySelectorNode> pPrioritySelectorNode = cBTNodeFactory::Create<cBTPrioritySelectorNode>()
		->AddChild<cBTPrioritySelectorNode>(cBTNodeFactory::Create<cSimpleNode>()
			->SetC(true))
		->AddChild<cBTPrioritySelectorNode>(cBTNodeFactory::Create<cBTPrioritySelectorNode>()
			->AddChild<cBTPrioritySelectorNode>(cBTNodeFactory::Create<cSimpleNode>()))
		->AddChild<cBTPrioritySelectorNode>(cBTNodeFactory::Create<cSimpleNode>()
			->SetA(2))
		->AddChild<cBTPrioritySelectorNode>(cBTNodeFactory::Create<cBTInverterDecoratorNode>()
			->SetChild<cBTInverterDecoratorNode>(cBTNodeFactory::Create<cSimpleNode>()
				->SetB(1.0f)));

	pPrioritySelectorNode->Tick(NULL);
	EXPECT_EQ(4, pPrioritySelectorNode ->GetSize());
	for (int i=0; i<4; ++i)
	{
		BTNodeStrongPtr pChild = MakeStrongPtr(pPrioritySelectorNode ->GetChildAt(i));
		EXPECT_EQ(pPrioritySelectorNode , MakeStrongPtr(pChild->GetParent()));
	}
}

//  *******************************************************************************************************************
TEST_F(BTTreeBuilderTest, Decorator)
{
	shared_ptr<cBTDecoratorNode> pDecoratorNode = cBTNodeFactory::Create<cBTInverterDecoratorNode>()
		->SetChild<cBTInverterDecoratorNode>(cBTNodeFactory::Create<cSimpleNode>());

	EXPECT_TRUE(pDecoratorNode  != NULL);
	EXPECT_TRUE(pDecoratorNode->GetChild() != NULL);

	shared_ptr<cSimpleNode> pChild = dynamic_pointer_cast<cSimpleNode>(pDecoratorNode ->GetChild());
	EXPECT_TRUE(pChild != NULL);
	EXPECT_EQ(pDecoratorNode , MakeStrongPtr(pChild->GetParent()));
	EXPECT_EQ(pDecoratorNode, MakeStrongPtr(pDecoratorNode->GetChild()->GetParent()));
}
