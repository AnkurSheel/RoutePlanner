#include "stdafx.h"
#include "QTNode.h"
#include "QuadTree.h"
#include "vector3.h"
#include "Shape.hxx"
#include "RigidBody.h"
#include "collisionInfo.h"
#include "QuadTree.h"

using namespace Physics;
using namespace Base;
using namespace Utilities;
using namespace std;

const unsigned int cQTNode::m_sSplitSize = 4;

//  *******************************************************************************************************************
cQTNode::cQTNode(const cQuadTree * const pQuadTree)
	: m_pParent(NULL)
	, m_pActualRect(NULL)
	, m_pLooseRect(NULL)
	, m_Depth(0)
	, m_Full(false)
	, m_pQuadTree(pQuadTree)
{
	m_Children.reserve(m_sSplitSize);
	m_Items.clear();
}

//  *******************************************************************************************************************
cQTNode::cQTNode(const unsigned int depth, const cQuadTree * const pQuadTree)
	: m_pParent(NULL)
	, m_pActualRect(NULL)
	, m_pLooseRect(NULL)
	, m_Depth(depth)
	, m_Full(false)
	, m_pQuadTree(pQuadTree)
{
	if(HasChildren())
	{
		KillChildren();
	}
	m_Items.clear();
}

//  *******************************************************************************************************************
cQTNode::~cQTNode()
{
	SafeDelete(&m_pActualRect);
	SafeDelete(&m_pLooseRect);
	if(HasChildren())
	{
		for(unsigned int i = 0; i < m_sSplitSize; i++)
		{
			SafeDelete(&(m_Children[i]));
		}
	}
	m_Items.clear();
}

//  *******************************************************************************************************************
cQTNode * const cQTNode::GetChild(unsigned int index)
{
	if(IsLeaf())
	{
		return NULL;
	}
	Clamp<unsigned int>(index, 0, m_sSplitSize - 1);
	return m_Children[index];
}

//  *******************************************************************************************************************
const cQTNode * const cQTNode::GetChild(unsigned int index) const
{
	if(IsLeaf())
	{
		return NULL;
	}
	Clamp<unsigned int>(index, 0, m_sSplitSize - 1);
	return m_Children[index];
}

//  *******************************************************************************************************************
void cQTNode::AddObject(cRigidBody * const pBody)
{
	m_Items.push_back(pBody);

	pBody->SetNode(this);

	if(HasChildren())
	{
		cQTNode * pChildNode = GetChildQuadrant(pBody);
		if(pChildNode != NULL)
		{
			RemoveObject(pBody);
			pChildNode->AddObject(pBody);
		}
	}

	if(m_Full)
	{
		if(CanSplit(m_pQuadTree->GetMaxDepth()))
		{
			Split();

			for(auto iter = m_Items.begin(); iter != m_Items.end();)
			{
				cQTNode * pChildNode = GetChildQuadrant(*iter);
				if(pChildNode != NULL)
				{
					pChildNode->AddObject(*iter);
					iter = m_Items.erase(iter);
				}
				else
				{
					iter++;
				}
			}
		}
	}
	m_Full = m_Items.size() >= m_pQuadTree->GetMaxObjects();
}

//  *******************************************************************************************************************
bool cQTNode::RemoveObject(cRigidBody * const pBody)
{
	for(auto iter = m_Items.begin(); iter != m_Items.end(); iter++)
	{
		if(*iter == pBody)
		{
			pBody->SetNode(NULL);
			m_Items.erase(iter);
			return true;
		}
	}
	return false;
}

//  *******************************************************************************************************************
void cQTNode::Split()
{
	if(!IsLeaf())
	{
		return;
	}

	m_Children.resize(m_sSplitSize);
	cVector3 start = m_pActualRect->VGetMinBound();
	cVector3 end = start + m_pActualRect->VGetHalfExtents();

	int depth = m_Depth + 1;

	for(unsigned int i = 0; i< m_sSplitSize; i++)
	{
		cQTNode * pCurrent = DEBUG_NEW cQTNode(depth, m_pQuadTree);
		pCurrent->m_pParent = this;

		// node becomes half the size
		pCurrent->CreateRect(start, end);

		m_Children[i] = pCurrent;
		start.x += m_pActualRect->VGetHalfExtents().x;
		end.x += m_pActualRect->VGetHalfExtents().x;

		if(start.x >= m_pActualRect->VGetMaxBound().x)
		{
			start.x = m_pActualRect->VGetMinBound().x;
			end.x = start.x + m_pActualRect->VGetHalfExtents().x;
			start.y += m_pActualRect->VGetHalfExtents().y;
			end.y += m_pActualRect->VGetHalfExtents().y;
		}
	}
}

//  *******************************************************************************************************************
bool cQTNode::CheckCollision(cRigidBody * const pBody) const
{
	// use existing function
	cVector3 centerDelta = pBody->GetCollisionShape()->VGetCenter() - m_pLooseRect->VGetCenter();
	cVector3 overlap = centerDelta;
	overlap.AbsTo();

	cVector3 halfExtentSum = pBody->GetCollisionShape()->VGetHalfExtents() + m_pLooseRect->VGetHalfExtents();
	overlap = halfExtentSum - overlap;

	return (overlap.x > 0 && overlap.y > 0);
}

//  *******************************************************************************************************************
bool cQTNode::Contains(cRigidBody * const pBody)
{
	cVector3 BodyMinBounds = pBody->GetCollisionShape()->VGetMinBound();
	cVector3 BodyMaxBounds = pBody->GetCollisionShape()->VGetMaxBound();
	cVector3 NodeMinBounds = m_pLooseRect->VGetMinBound();
	cVector3 NodeMaxBounds = m_pLooseRect->VGetMaxBound();

	return (NodeMinBounds.x <= BodyMinBounds .x && NodeMinBounds.y <= BodyMinBounds.y
		&& NodeMaxBounds.x >= BodyMaxBounds.x && NodeMaxBounds.y >= BodyMaxBounds.y);
}

//  *******************************************************************************************************************
void cQTNode::KillChildren()
{
	for(unsigned int i = 0; i < m_sSplitSize; i++)
	{
		for(auto iter = m_Children[i]->m_Items.begin();	iter != m_Children[i]->m_Items.end(); iter++)
		{
			m_Items.push_back(*iter);
		}
		SafeDelete(&(m_Children[i]));
	}
	m_Children.clear();
}

//  *******************************************************************************************************************
void cQTNode::CreateRect(const cVector3 & minBound, const cVector3 & maxBound)
{
	m_pActualRect= IShape::CreateRectangleShape();
	m_pActualRect->VInitialize(minBound, maxBound);

	m_pLooseRect = m_pActualRect->VDuplicate();
	m_pLooseRect->VScale(1.0f + m_pQuadTree->GetLooseningFactor());
}

//  *******************************************************************************************************************
void cQTNode::Print() const
{
	cString str = cStringUtilities::MakeFormatted("QTNode %u parent (%u) Depth (%d)", this, m_pParent, m_Depth);
	int children = 0;
	if(HasChildren())
	{
		children = m_Children.size();
	}
	str += cStringUtilities::MakeFormatted("Children (%d) ", children);
	str += cStringUtilities::MakeFormatted("objCount (%u) ", m_Items.size());

	str += cStringUtilities::MakeFormatted("ActualRect (left: %f, right: %f, top: %f bottom: %f) ", m_pActualRect->VGetMinBound().x,
		m_pActualRect->VGetMaxBound().x, m_pActualRect->VGetMinBound().y, m_pActualRect->VGetMaxBound().y);

	str += cStringUtilities::MakeFormatted("LooseRect (left: %f, right: %f, top: %f bottom: %f) ", m_pLooseRect->VGetMinBound().x, 
		m_pLooseRect->VGetMaxBound().x, m_pLooseRect->VGetMinBound().y, m_pLooseRect->VGetMaxBound().y);

	SP_LOG(2, str);

	if(HasChildren())
	{
		for(size_t i = 0; i < m_sSplitSize; i++)
		{
			GetChild(i)->Print();
		}
	}
}

//  *******************************************************************************************************************
cQTNode * const cQTNode::GetChildQuadrant(cRigidBody * const pBody)
{
	float bestSquaredDistance = MaxFloat;
	cQTNode * pBestNode = NULL;
	for(unsigned int i = 0; i < m_sSplitSize; i++)
	{
		cQTNode * pChildNode = GetChild(i);
		if(pChildNode !=NULL && pChildNode->Contains(pBody))
		{
			float distance = pBody->GetCollisionShape()->VGetCenter().DistanceSquared(pChildNode->m_pActualRect->VGetCenter());
			if(distance < bestSquaredDistance)
			{
				bestSquaredDistance = distance;
				pBestNode = pChildNode;
			}
		}
	}
	return pBestNode;
}

//  *******************************************************************************************************************
void cQTNode::CreateCollisionPairs(cRigidBody * const pBody, vector<cCollisionInfo> & collisions)
{
	if(CheckCollision(pBody))
	{
		for(auto iter = m_Items.cbegin(); iter != m_Items.cend(); iter++)
		{
			cRigidBody * const pOtherRigidBody = (*iter);
			if(pBody != pOtherRigidBody && pOtherRigidBody->IsInitialized())
			{
				cCollisionInfo c(pBody, pOtherRigidBody);
				c.Solve();
				if(c.GetCollided())
				{
					collisions.emplace_back(c);
				}
			}
		}
		if(HasChildren())
		{
			for(unsigned int i = 0; i < m_sSplitSize; i++)
			{
				cQTNode * pChildNode = GetChild(i);
				pChildNode->CreateCollisionPairs(pBody, collisions);
			}
		}
	}
}
