//  *******************************************************************************************************************
//  QTNode version:  1.0   Ankur Sheel  date: 2013/08/21
//  *******************************************************************************************************************
//  purpose:	
//  *******************************************************************************************************************

#ifndef QTNode_h
#define QTNode_h

namespace Base
{
	class cVector3;
}

namespace Physics
{
	class cRigidBody;
	class IShape;
	class cCollisionInfo;
	class cQuadTree;
}

namespace Physics
{
	class cQTNode
		: public Base::cNonCopyable
	{
	public:
		cQTNode(const cQuadTree * const pQuadTree);
		cQTNode(const unsigned int depth, const cQuadTree * const pQuadTree);
		~cQTNode();
		void AddObject(cRigidBody * const pBody);
		bool RemoveObject(cRigidBody * const pBody);
		void CreateRect(const Base::cVector3 & minBound, const Base::cVector3 & maxBound);
		bool Contains(cRigidBody * const pBody);
		void Print() const;
		void CreateCollisionPairs(cRigidBody * const pBody, std::vector<cCollisionInfo> & collisions);
		cQTNode * const GetChild(unsigned int index);
        const cQTNode * const GetChild(unsigned int index) const;
		bool HasChildren() const { return !m_Children.empty(); }
		cQTNode * const GetParent() const { return m_pParent; }
		bool CheckCollision(cRigidBody * const pBody) const;
		cQTNode * const GetChildQuadrant(cRigidBody * const pBody);
		
	private:
		bool IsLeaf() const{ return m_Children.empty(); }
		void KillChildren();
		bool CanSplit(const unsigned int maxDepth) { return m_Depth < maxDepth; }
		void Split();

	private:
		static const unsigned int		m_sSplitSize;
		unsigned int					m_Depth;
		cQTNode	*						m_pParent;
		IShape *						m_pActualRect;
		IShape *						m_pLooseRect;
		const cQuadTree *				m_pQuadTree;
		std::vector<cQTNode*>			m_Children;
		std::list<cRigidBody * const>	m_Items;
		bool							m_Full;
	};
}
#endif //QTNode_h