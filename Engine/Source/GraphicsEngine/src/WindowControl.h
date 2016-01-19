//  *******************************************************************************************************************
//  WindowControl   version:  1.0   Ankur Sheel  date: 2011/11/21
//  *******************************************************************************************************************
//  purpose:	
//  *******************************************************************************************************************
#ifndef WindowControl_h__
#define WindowControl_h__

#include "BaseControl.h"

namespace Base
{
	template<class BaseType, class SubType> 
	BaseType * GenericObjectCreationFunction();
}

namespace Graphics
{
	/********************************************//**
     * @brief Class Declaration for a Window UI Control
     ***********************************************/
	class cWindowControl
		: public cBaseControl
	{
	public:
		/********************************************//**
		 * @param[in] def The parameter definition to create a window control
		 *
		 * Initializes the window control as per the parameters
		 ***********************************************/
		void Initialize(const cWindowControlDef & def);
		static Base::cHashedString	GetName()  {return m_Name; }
		~cWindowControl();

	private:
		cWindowControl();
		void VInitialize(const shared_ptr<Utilities::IXMLNode const> pXMLNode);
		shared_ptr<IBaseControl> VDuplicate();
		bool VOnLeftMouseButtonUp(const int X, const int Y);
		bool VOnLeftMouseButtonDown(const int X, const int Y);
		bool VOnMouseMove(const int X, const int Y);
		void VSetAbsolutePosition();
		unsigned long VGetHashedID() const { return m_Name.GetHash(); }

	private:
		GRAPHIC_API static Base::cHashedString	m_Name;	///< The control name
		cWindowControlDef::WINDOWTYPE	m_eWindowType;	///< The window type.

	private:
		template<class BaseType, class SubType> 
		friend BaseType * Base::GenericObjectCreationFunction();

		friend class IBaseControl;
	};
}

#endif // WindowControl_h__