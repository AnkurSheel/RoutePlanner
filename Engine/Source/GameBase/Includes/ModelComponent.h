// *****************************************************************************
//  ModelComponent version:  1.0   Ankur Sheel  date: 2013/04/02
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef ModelComponent_h__
#define ModelComponent_h__

#include "BaseComponent.h"
#include "GameBaseDefines.h"
#include "RenderableComponent.hxx"


namespace Base
{
	template<class BaseType, class SubType> 
	BaseType * GenericObjectCreationFunction();
}

namespace Utilities
{
	class IXMLNode;
}

namespace Graphics
{
	class IModel;
	class ICamera;
}

namespace GameBase
{
	class cModelComponent
		: public cBaseComponent
		, public IRenderableComponent
	{
	public:
		void VInitialize(const Utilities::IXMLNode * const pXMLNode);
		void VCleanup();
		void VSetPosition(const Base::cVector3 & position);
		void VSetRotation(const Base::cVector3 & rotation);
		void VSetSize(const Base::cVector3 & size);
		void VRender(const Graphics::ICamera * const pCamera);
		GAMEBASE_API static Base::cHashedString	GetName()  {return m_Name; }

	private :
		cModelComponent();
		~cModelComponent();
		unsigned long VGetHashedID() const { return m_Name.GetHash(); }

	private:
		Graphics::IModel *			m_pModel;	///< The 3D model
		static Base::cHashedString	m_Name;	///< The component name

	private:
		template<class BaseType, class SubType> 
		friend BaseType * Base::GenericObjectCreationFunction();
	};
}
#endif // ModelComponent_h__
