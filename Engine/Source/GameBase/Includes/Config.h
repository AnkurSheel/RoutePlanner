//  *******************************************************************************************************************
//  Config   version:  1.0   Ankur Sheel  date: 2013/05/06
//  *******************************************************************************************************************
//  purpose:	
//  *******************************************************************************************************************

#ifndef Config_h__
#define Config_h__

#include "GenericObjectCreation.h"
#include "GameBaseDefines.h"

namespace GameBase
{
	class cEntityDef;
	class IBaseComponent;
}

namespace Utilities
{
	class IXMLNode;
}

namespace GameBase
{
	class cConfig
		: public Base::cNonCopyable
	{
	public:
		GAMEBASE_API cConfig();
		GAMEBASE_API virtual ~cConfig();
		GAMEBASE_API virtual void VInitialize(const Base::cString & FileName);
		GAMEBASE_API static const cEntityDef * const GetEntityDef(const Base::cHashedString & EntityType);

	private:
		void LoadEntities(const Base::cString & EntitiesFileName);
		void Cleanup();

	protected:
		shared_ptr<Utilities::IXMLNode>	m_pRoot;

	private:
		typedef std::map<unsigned long, const cEntityDef *> EnitityDefMap;
		EnitityDefMap	m_EntityDefs;
		static cConfig *	m_pInstance;
	};
}
#endif // Config_h__