#include "stdafx.h"
#include "QuadTree.h"
#include "RigidBody.h"
#include "QTNode.h"

using namespace Physics;
using namespace Base;
using namespace std;
using namespace Utilities;

//  *******************************************************************************************************************
cQuadTree::cQuadTree()
	: m_NoOfItems(0)
	, m_MaxDepth(6)
	, m_MaxObjects(8)
	, m_LooseningFactor(0.0f)
	, m_pRoot(NULL)
{
}

//  *******************************************************************************************************************
cQuadTree::~cQuadTree()
{
	SafeDelete(&m_pRoot);
}

//  *******************************************************************************************************************
void cQuadTree::Initialize(shared_ptr<const stQuadTreeDef> pDef)
{
	SP_ASSERT_ERROR(pDef != NULL).SetCustomMessage("QuadTree Definition is null");

	m_MaxDepth = pDef->m_MaxDepth;
	m_MaxObjects = pDef->m_MaxObjects;
	m_LooseningFactor = pDef->m_LooseningFactor;

	m_pRoot = DEBUG_NEW cQTNode(this);
	m_pRoot->CreateRect(pDef->m_MinBounds, pDef->m_MaxBounds);
}

//  *******************************************************************************************************************
bool cQuadTree::Insert(cRigidBody * const pBody)
{
	m_NoOfItems++;
	return RecursiveInsert(pBody, m_pRoot);
}

//  *******************************************************************************************************************
void cQuadTree::OnBodyMoved(cRigidBody * const pBody)
{
	cQTNode * pNode = pBody->GetNode();
	cQTNode * pParent = NULL;
	if (pNode == NULL || pNode->GetParent() == NULL)
	{
		pParent = m_pRoot;
	}
	else
	{
		pParent = pNode->GetParent();
	}

	if(pParent->GetChildQuadrant(pBody) != pNode)
	{
		pNode->RemoveObject(pBody);
		pParent->AddObject(pBody);
	}
}

//  *******************************************************************************************************************
bool cQuadTree::RecursiveInsert(cRigidBody * const pBody, cQTNode * const pNode)
{
	if(pNode == NULL)
	{
		return false;
	}
	// if part of the body is on screen or if the body is completely contained by a child node add it
	if((pNode->GetParent() == NULL && pNode->CheckCollision(pBody))
		|| pNode->Contains(pBody))
	{
		pNode->AddObject(pBody);
		return true;
	}

	if(pNode->GetParent() == NULL)
	{
		return false;
	}

	return RecursiveInsert(pBody, pNode->GetParent());
}

//  *******************************************************************************************************************
bool cQuadTree::Remove(cRigidBody * const pBody)
{
	cQTNode * pNode = pBody->GetNode();
	if(pNode == NULL)
	{
		return false;
	}
	m_NoOfItems--;
	return pNode->RemoveObject(pBody);
}

//  *******************************************************************************************************************
void cQuadTree::CreateCollisionPairs(cRigidBody * const pBody, vector<cCollisionInfo> & collisions)
{
	if(m_pRoot == NULL)
	{
		return;
	}
	m_pRoot->CreateCollisionPairs(pBody, collisions);
}

//  *******************************************************************************************************************
void cQuadTree::Print() const
{
	SP_LOG(2, cStringUtilities::MakeFormatted("Printing QuadTree with %u objects", m_NoOfItems));
	m_pRoot->Print();
}
