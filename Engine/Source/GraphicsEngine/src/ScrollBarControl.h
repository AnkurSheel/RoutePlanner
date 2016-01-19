//  *******************************************************************************************************************
//  ScrollBarControl   version:  1.0   Ankur Sheel  date: 2012/04/24
//  *******************************************************************************************************************
//  purpose
//  *******************************************************************************************************************
#ifndef ScrollBarControl_h__
#define ScrollBarControl_h__

#include "BaseControl.h"

namespace Graphics
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @brief Base Class for Horizontal and vertical scrollbar UI Control
	///
	///
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class cScrollBarControl
		: public cBaseControl
	{
	protected:
		cScrollBarControl();
		virtual ~cScrollBarControl();
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Sets the position of the thumb to iNewPosition. Constrains the position between 0 and the no of increments
		/// 
		/// @param[in] iNewPosition The new position of the thumb
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void VSetThumbPosition(const int iNewPosition) ;
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Resizes the thumb depending on the number of increments and the total size of the scrollbar
		///
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		virtual void VAutoSizeThumb() = 0;

	private:
		void VInitialize(const shared_ptr<Utilities::IXMLNode const> pXMLNode);
		bool VOnLeftMouseButtonUp(const int X, const int Y);
		bool VOnLeftMouseButtonDown(const int X, const int Y);
		void VRender(const ICamera * const pCamera);
		void VCleanup();
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Increments the thumb position by 1 when the down/right button is released
		///
		/// @param[in] params Not Used
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void IncrementArrowPressed(const Graphics::stUIEventCallbackParam & params);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Decrements the thumb position by 1 when the up/left button is released
		///
		/// @param[in] params Not Used
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void DecrementArrowPressed(const Graphics::stUIEventCallbackParam & params);
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Sets the drag mode
		///
		/// @param[in] params Not Used
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void ThumbPressed(const Graphics::stUIEventCallbackParam & params);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Resets the drag mode
		///
		/// @param[in] params Not Used
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void ThumbReleased(const Graphics::stUIEventCallbackParam & params);

	protected:
		int	m_MinPos;	/// The minimum value that the scrollbar can go to. 
		int	m_MaxPos;	/// The maximum value that the scrollbar can go to. 
		int	m_ThumbPos;	/// The current thumb position. 
		int	m_NoOfIncrements;	/// The number of increments in the scrollbar. Equal to m_iMaxPos - m_iMinPos. 
		bool	m_DragMode;	/// True if we are dragging the thumb. False otherwise. 
		shared_ptr<IBaseControl>	m_pBtnThumb;	/// The thumb button. 
		shared_ptr<IBaseControl>	m_pBtnDecrementArrow; /// The up/left button. 
		shared_ptr<IBaseControl>	m_pBtnIncrementArrow;	/// The bottom/right button. 	
		UIEventCallBackFn	m_callbackIncrementArrowPressed;	/// Callback function when the up/left button is pressed/released. 	
		UIEventCallBackFn	m_callbackDecrementArrowPressed;	/// Callback function when the bottom/right button is pressed/released. 	
		UIEventCallBackFn	m_callbackThumbPressed;	/// Callback function when the thumb button is pressed. 	
		UIEventCallBackFn	m_callbackThumbReleased;	/// Callback function when the thumb button is released.
	};
}

#endif // ScrollBarControl_h__