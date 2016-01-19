//  *******************************************************************************************************************
//  CheckBoxControl   version:  1.0   Ankur Sheel  date: 2011/12/11
//  *******************************************************************************************************************
//  purpose
//  *******************************************************************************************************************
#ifndef CheckBoxControl_h__
#define CheckBoxControl_h__

#include "BaseControl.h"

namespace Base
{
	template<class BaseType, class SubType> 
	BaseType * GenericObjectCreationFunction();
}

namespace Graphics
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @brief Class Declaration for \c CheckBox UI Control
	///
	///
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class cCheckBoxControl
		: public cBaseControl
	{
	public:
		static Base::cHashedString	GetName()  {return m_Name; }
		~cCheckBoxControl();

	private:
		cCheckBoxControl();
		void VInitialize(const shared_ptr<Utilities::IXMLNode const> pXMLNode);
		shared_ptr<IBaseControl> VDuplicate();
		void VRender(const ICamera * const pCamera );
		bool VOnLeftMouseButtonDown(const int X, const int Y);
		void VSetAbsolutePosition();

	private:
		bool	m_Checked;	/// True if The checkbox is checked. False otherwise.
		shared_ptr<IBaseControl>	m_pTickBox;	/// The check box. This is a button UI control.
		static Base::cHashedString	m_Name;	///< The control name

	private:
		template<class BaseType, class SubType> 
		friend BaseType * Base::GenericObjectCreationFunction();

		friend class IBaseControl;
	};
}
#endif // CheckBoxControl_h__