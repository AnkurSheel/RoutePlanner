// *****************************************************************************
//  BaseComponent version:  1.0   Ankur Sheel  date: 2013/04/02
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef BaseComponent_hxx__
#define BaseComponent_hxx__

#include "GameBaseDefines.h"

namespace GameBase
{
	class IBaseEntity;
}

namespace Utilities
{
	class IXMLNode;
}

namespace GameBase
{
	class IBaseComponent
	{
	public:
		virtual ~IBaseComponent(){};
		virtual void VInitialize(const Utilities::IXMLNode * const pXMLNode) = 0;
		virtual void VOnAttached(IBaseEntity * const pOwner) = 0;
		virtual void VCleanup() = 0;
		virtual unsigned long VGetID() const = 0;
		virtual shared_ptr<Utilities::IXMLNode> VGenerateXml() const = 0;
	};
}
#endif //BaseComponent_hxx__