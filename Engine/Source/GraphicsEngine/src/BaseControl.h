//  *******************************************************************************************************************
//  BaseControl   version:  1.0   Ankur Sheel  date: 2011/07/21
//  *******************************************************************************************************************
//  purpose:	
//  *******************************************************************************************************************
#ifndef BaseControl_h__
#define BaseControl_h__

#include "BaseControl.hxx"

namespace Base
{
	struct AppMsg;
	class cHashedString;
}

namespace Graphics
{
	class ISprite;
}

namespace Graphics
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @brief Encapsulates all the base functionality required by all the UI controls
	///
	/// 
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class cBaseControl
		: public IBaseControl
	{
	public:
		virtual ~cBaseControl();
		void VSetVisible(bool bIsVisible);

	protected:
		cBaseControl();
		cBaseControl(const cBaseControl & other);

		virtual unsigned long VGetHashedID() const {return 0;} // remove later
		void VInitialize(const shared_ptr<Utilities::IXMLNode const> pXMLNode);
		void Initialize(const cBaseControlDef & def); // remove later
		void VRender(const ICamera * const pCamera );
		bool VOnLeftMouseButtonUp(const int X, const int Y);
		bool VOnLeftMouseButtonDown(const int X, const int Y);
		bool VOnMouseMove(const int X, const int Y);
		bool VOnKeyDown(const unsigned int iCharID);
		bool VOnCharPress(const unsigned int iCharID);
		void VAddChildControl(shared_ptr<IBaseControl> pChildControl);
		const Base::cVector2 VGetSize() const;
		void VSetSize(const Base::cVector2 & vSize);
		float VGetWidth() const;
		float VGetHeight() const;
		void VUnregisterCallBack(const UIEVENTTYPE::ENUM eventType);
		void VUnRegisterAllCallBacks();
		/********************************************//**
 		 *
		 * Sets the absolute position of the control relative
		 * to the screen. 
		 ***********************************************/
		virtual void VSetAbsolutePosition();
		/********************************************//**
 		 *
		 * Event Handler for when the control gains/loses focus 
		 ***********************************************/
		virtual void VOnFocusChanged();
		/********************************************//**
		 *
		 * Releases and destroys all the resources/pointers 
		 ***********************************************/
		virtual void VCleanup();
		/********************************************//**
		 * @param[in] pControl The control which has the focus
		 *
		 * Sets the focus control to pControl
		 ***********************************************/
		void SetFocusControl(const cBaseControl * const pControl);
		/********************************************//**
		 * @param[in] bFocus True if the controls gains focus. False if the control loses focus
		 *
		 * Sets the focus 
		 ***********************************************/
		void SetFocus(const bool bFocus);
		/********************************************//**
	 	 * @param[in] eventType The type of the event for the call back.
		 * @return The callback function associated with this event
		 *
		 * Returns The callback function associated with this event. 
		 * If the function is not found, it will return null
		 ***********************************************/
		UIEventCallBackFn * GetCallbackFromMap(const UIEVENTTYPE::ENUM eventType);

	private:
		/** List of controls. */
		typedef std::list<shared_ptr<cBaseControl> >  ControlList;
		/** Map of callback functions with the event ype as the key. */
		typedef std::map<UIEVENTTYPE::ENUM, UIEventCallBackFn >  UIEventCallBackMap;

		bool VOnKeyUp(const unsigned int iCharID);
		bool VPostMsg(const Base::AppMsg & msg);
		void VRemoveAllChildren();
		void VRemoveChildControl(const Base::cString & strControlName);
		const shared_ptr<Graphics::IBaseControl> VFindChildControl(const Base::cString & strControlName);
		void VSetText(const Base::cString & strText);
		void VSetPosition(const Base::cVector2 & vPosition);
		void VRegisterCallBack(const UIEVENTTYPE::ENUM eventType,
			UIEventCallBackFn fnCallback);
		void VMoveToFront(const IBaseControl * const pControl);
		Base::cString VGetControlName() const;
		void VSetControlName(const Base::cString & inControlName);
		/********************************************//**
		 * @return True if the user can move the controls using the mouse.
		 * False otherwise
		 *
		 * Returns True if the user can move the controls using the mouse.
		 * False otherwise
		 ***********************************************/
		bool AllowMovingControl();
		/********************************************//**
		 * @param[in] fX The X position of the control
		 * @param[in] fY The Y position of the control
		 *
		 * Constrain child control in parent control
		 ***********************************************/
		void ConstrainChildControl(float & fX, float & fY);
		/********************************************//**
		 * @param[in] pParentControl Pointer to the parent control
		 *
		 * Sets the parent control of the current control
		 ***********************************************/
		void SetParentControl( cBaseControl * pParentControl );
		/********************************************//**
		 * @param[in] msg The windows message
		 * @return True if the child control handles the message. False otherwise
		 *
		 * Posts the msg to all the child controls
		 ***********************************************/
		bool PostToAll(const Base::AppMsg & msg);
		/********************************************//**
		 * @param[in] fx The X position of the mouse
		 * @param[in] fy The Y position of the mouse
		 * @return True if the mouse intersects this control. False otherwise
		 *
		 * Returns True if the mouse intersects this control. False otherwise
		 ***********************************************/
		bool IsCursorIntersect(const float fX, const float fY);
		/********************************************//**
		 * @param[in] pChildControl The child control for which we want the iterator
		 * @return a const_iterator if the child control is found in the list. 
		 *
		 * Returns a const_iterator if the child control is found in the list. 
		 * If the child control is not found, the const_iterator will be equal list.end();
		 ***********************************************/
		ControlList::const_iterator GetChildControlIterator(const IBaseControl * const pChildControl);
		
	protected:
		ISprite *				m_pBGSprite;				/*!< The background sprite associated with this control. */
		Base::cVector2			m_vControlAbsolutePosition;	/*!< The absolute position of the control on the screen. */
		Base::cVector2			m_vSize;					/*!< The size of the control. */
		Base::cVector2			m_vPosition;				/*!< The position of the control w.r.t to its parent control. */
		UIEventCallBackMap		m_CallbackMap;				/*!< The map containing all the callback functions with the event type as the key */
		ControlList				m_pChildControl;			/*!< List of child controls. */
		bool					m_bVisible;					/*!< True if the control is visible. False otherwise. */
		bool					m_bFocus;					/*!< True if the control or any of its child controls has focus. False otherwise */
		bool					m_bAllowMovingControls;		/*!< True if the user can move the controls using the mouse. False otherwise. */
		bool					m_bIsLeftMouseDown;			/*!< True if the left mouse button is pressed. */
	
	private:
		cBaseControl *			m_pFocusControl;			/*!< The control which has the focus. */
		cBaseControl *			m_pParentControl;			/*!< The parent control. */
		int						m_iMouseDownXPos;			/*!< The X position of the mouse relative to the absolute control position. */
		int						m_iMouseDownYPos;			/*!< The Y position of the mouse relative to the absolute control position. */
		Base::cHashedString 	m_strControlName;			/*!< The name of the control. */
		bool					m_ConstrainInParent;
	};
}
#endif // BaseControl_h__