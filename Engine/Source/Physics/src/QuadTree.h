//  *******************************************************************************************************************
//  QuadTree version:  1.0   Ankur Sheel  date: 2013/08/21
//  *******************************************************************************************************************
//  purpose:	
//  *******************************************************************************************************************

#ifndef QuadTree_h
#define QuadTree_h

#include "vector3.h"

namespace Physics
{
	class cRigidBody;
	class cQTNode;
	class cCollisionInfo;
}

namespace Physics
{
	struct	stQuadTreeDef
	{
		Base::cVector3	m_MinBounds;
		Base::cVector3	m_MaxBounds;
		unsigned int	m_MaxObjects;
		unsigned int	m_MaxDepth;
		float			m_LooseningFactor;

		stQuadTreeDef()
			: m_MaxObjects(8)
			, m_MaxDepth(6)
			, m_LooseningFactor(0.0f)
		{
		}
	};

	class cQuadTree
		: public Base::cNonCopyable
	{
	public:
		cQuadTree();
		~cQuadTree();
		void Initialize(shared_ptr<const stQuadTreeDef> pDef);
		bool Insert(cRigidBody * const pBody);
		void OnBodyMoved(cRigidBody * const pBody);
		bool Remove(cRigidBody * const pBody);
		void CreateCollisionPairs(cRigidBody * const pBody, std::vector<cCollisionInfo> & collisions);
		void Print() const;
		unsigned int GetMaxObjects() const { return m_MaxObjects; }
		unsigned int GetMaxDepth() const { return m_MaxDepth; }
		float GetLooseningFactor() const { return m_LooseningFactor; }
		
	private:
		bool RecursiveInsert(cRigidBody * const pBody, cQTNode * const pNode);

	private:
		unsigned int	m_MaxObjects;
		unsigned int	m_MaxDepth;
		unsigned int	m_NoOfItems;
		float	 m_LooseningFactor;
		cQTNode *	 m_pRoot;
	};
}
#endif //QuadTree_h