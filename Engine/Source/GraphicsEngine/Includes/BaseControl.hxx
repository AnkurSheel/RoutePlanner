//  *******************************************************************************************************************
//  BaseControl   version:  1.0   Ankur Sheel  date: 2011/11/22
//  *******************************************************************************************************************
//  purpose:	
//  *******************************************************************************************************************
#ifndef BaseControl_hxx__
#define BaseControl_hxx__

#include "GraphicEngineDefines.h"
#include "MouseHandler.hxx"
#include "KeyboardHandler.hxx"
#include "ControlStructures.h"

namespace Base
{
	class cString;
	class cVector2;
	class cColor;
	struct AppMsg;
}

namespace Graphics
{
	class ICamera;
	class IMyFont;
}

namespace Utilities
{
	class IXMLNode;
}

namespace Graphics
{
	typedef function<void (const stUIEventCallbackParam &)> UIEventCallBackFn;

	/********************************************//**
	 * @brief Interface for All UI controls.
	 *
	 * Used to create UI controls such as Window, Label, 
	 * Button, CheckBox, TextBox and ScrollBars
	 ***********************************************/
	class IBaseControl
		: public IMouseHandler
		, public IKeyboardHandler
	{
	public:
		virtual ~IBaseControl(){}
		virtual void VInitialize(const shared_ptr<Utilities::IXMLNode const> pXMLNode) = 0;
		virtual shared_ptr<IBaseControl> VDuplicate() = 0;
		/********************************************//**
 		 * @param[in] msg The window message that needs to be processed
		 * return True if the message is handled by this control or one of its children
		 *
		 * Checks if any of the child controls can handle the message. If no child
		 * controls can handle the message it tries to handle the message itself.
		 * Returns true if the message is handled. False otherwise
		 ***********************************************/
		virtual bool VPostMsg(const Base::AppMsg & msg) = 0;
		/********************************************//**
 		 * @param[in] pChildControl The control that needs to be added
		 *
		 * Adds a child control
		 ***********************************************/
		virtual void VAddChildControl(shared_ptr<IBaseControl> pChildControl) = 0;
		/********************************************//**
		 *
		 * Removes and deletes all the child controls.
		 ***********************************************/
		virtual void VRemoveAllChildren() = 0;
		/********************************************//**
 		 * @param[in] strControlName The name of the control that needs to be removed
		 *
		 * Removes and deletes the child control
		 ***********************************************/
		virtual void VRemoveChildControl(const Base::cString & strControlName) = 0;
		/********************************************//**
 		 * @param[in] strControlName The name of the control that needs to be found
		 * @return The child control with name equal to strControlName
		 *
		 * Returns the child control
		 ***********************************************/
		virtual const shared_ptr<Graphics::IBaseControl> VFindChildControl(const Base::cString & strControlName) = 0;
		/********************************************//**
 		 * @param[in] pCamera The camera which contains the current view matrix
		 *
		 * Draws the control
		 ***********************************************/
		virtual void VRender(const ICamera * const pCamera) = 0;
		/********************************************//**
 		 * @param[in] bIsVisible True if the control should be visible, false otherwise
		 *
		 * Sets the visibility of the 2D element
		 ***********************************************/
		virtual void VSetVisible(bool bIsVisible) = 0;
		/********************************************//**
 		 * @param[in] vPosition The position of the control
		 *
		 * Sets the position of the control
		 ***********************************************/
		virtual void VSetPosition(const Base::cVector2 & vPosition) = 0;
		/********************************************//**
 		 * @return vSize The size of the control
		 *
		 * Returns the size of the control
		 ***********************************************/
		virtual const Base::cVector2 VGetSize() const = 0;
		/********************************************//**
 		 * @param[in] vSize The new size of the control
		 *
		 * Sets the size of the control
		 ***********************************************/
		virtual void VSetSize(const Base::cVector2 & vSize) = 0;
		/********************************************//**
		 * @param[in] eventType The type of the event for the call back.
 		 * @param[in] fnCallback Function pointer to the callback funtion. The function takes in a stUIEventCallbackParam and returns void
		 *
		 * Sets the callback function to invoke when the eventType event occurs
		 ***********************************************/
		virtual void VRegisterCallBack(const UIEVENTTYPE::ENUM eventType,
			UIEventCallBackFn fnCallback) = 0;
		/********************************************//**
		 * @param[in] eventType The type of the event for the call back.
		 *
		 * Unregisters the callback function for the eventtype event
		 ***********************************************/
		virtual void VUnregisterCallBack(const UIEVENTTYPE::ENUM eventType) = 0;
		virtual void VUnRegisterAllCallBacks() = 0;
		/********************************************//**
		 * @param[in] pControl The control to be moved to the front
		 *
		 * Moves the child control to the front.
		 ***********************************************/
		virtual void VMoveToFront(const IBaseControl * const pControl) = 0;
		/********************************************//**
 		 * @return The width of the control
		 *
		 * Returns the width of the control
		 ***********************************************/
		virtual float VGetWidth() const = 0;
		/********************************************//**
 		 * @return The width of the control
		 *
		 * Returns the height of the control
		 ***********************************************/
		virtual float VGetHeight() const = 0;
		/********************************************//**
 		 * @param[in] strText The text to be displayed on the control
		 *
		 * Sets the text to be displayed on the control
		 ***********************************************/
		virtual void VSetText(const Base::cString & strText) = 0;
		/********************************************//**
 		 * @return The name of the control
		 *
		 * Returns the name of the control
		 ***********************************************/
		virtual Base::cString VGetControlName() const = 0;
		virtual void VSetControlName(const Base::cString & inControlName) = 0;
		/********************************************//**
		 * @param[in] def The params to create the window control  
		 * @return Pointer to a window control object
		 *
		 * Returns a pointer to a window control object
		 ***********************************************/
		GRAPHIC_API static IBaseControl * CreateWindowControl(const cWindowControlDef & def);
		/********************************************//**
		 * @param[in] def The params to create the label control  
		 * @return Pointer to a label control object
		 *
		 * Returns a pointer to a label control object
		 ***********************************************/
		GRAPHIC_API static IBaseControl * CreateLabelControl(const cLabelControlDef & def);
	};
}
#endif // BaseControl_hxx__