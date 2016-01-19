//  *******************************************************************************************************************
//  Physics version:  1.0   Ankur Sheel  date: 2013/06/06
//  *******************************************************************************************************************
//  purpose:	
//  *******************************************************************************************************************

#ifndef Physics_h
#define Physics_h

#include "Physics.hxx"

namespace Utilities
{
	class IXMLNode;
}

namespace Physics
{
	struct stMaterialData;
	class cQuadTree;
	class cRigidBody;
	class cCollisionInfo;
}

namespace Physics
{
	class cPhysics
		: public IPhysics
	{
	public:
		~cPhysics();

	private:
		cPhysics();
		void VInitialize(const Base::cString & FileName) OVERRIDE;
		void VUpdate(const float DeltaTime) OVERRIDE;
		IRigidBody * const VAddRigidBody(const int ID, shared_ptr<const stRigidBodyDef> pDef) OVERRIDE;
		void VRemoveRigidBody(const int ID) OVERRIDE;
		void VOnRigidBodyAdded(const int ID) OVERRIDE;
		stMaterialData VLookUpMaterialData(const Base::cString & materialName) const OVERRIDE;
		cRigidBody* FindRigidBody(const int ID) const;
		void InternalStep();
		void LoadMaterialData(shared_ptr<Utilities::IXMLNode> pParentNode);
		void CreateQuadTree(shared_ptr<Utilities::IXMLNode> pParentNode);
		void IntegrateForces();
		void GetCollisionInfo(std::vector<cCollisionInfo> & Collisions);
		void CreateCollisionPairs(std::vector<cCollisionInfo> & Collisions);
		const CollisionPairs & VGetCollisionPairs() const  OVERRIDE { return m_CollisionPairs; } 
		const CollisionPairs & VGetTriggerPairs() const  OVERRIDE { return m_TriggerPairs; }
		float VGetGravity() const  OVERRIDE { return m_Gravity; }

	private:
		typedef std::map<int, cRigidBody * const > RigidBodyMap;
		typedef std::map<unsigned long, stMaterialData> MaterialMap;
		
		float m_Gravity;
		float m_TimeStep;
		float m_Accumalator;
		cQuadTree * m_pQuadTree;		
		RigidBodyMap m_RigidBodyMap;
		MaterialMap m_MaterialMap;
		CollisionPairs m_CollisionPairs;
		CollisionPairs m_TriggerPairs;
		bool m_UseQuadTree;

		//private:
		friend static void IPhysics::CreateAsService();
	};
}
#endif //Physics_hxx