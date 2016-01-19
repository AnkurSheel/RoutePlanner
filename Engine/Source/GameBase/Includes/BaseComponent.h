// *****************************************************************************
//  BaseComponent version:  1.0   Ankur Sheel  date: 2013/04/02
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef BaseComponent_h__
#define BaseComponent_h__

#include "BaseComponent.hxx"

namespace GameBase
{
	class IBaseEntity;
}

namespace GameBase
{
	class cBaseComponent
		: public IBaseComponent
	{
	public:
		cBaseComponent();
		cBaseComponent(const cBaseComponent & other);
		cBaseComponent & operator =(const cBaseComponent & other);
		GAMEBASE_API virtual ~cBaseComponent();

		unsigned long VGetID() const OVERRIDE { return VGetHashedID(); }
		void VOnAttached(IBaseEntity * const pOwner) OVERRIDE;

	protected:
		virtual unsigned long VGetHashedID() const = 0;
		
	protected:
		IBaseEntity *		m_pOwner;
	};
}
#endif //Component_hxx__