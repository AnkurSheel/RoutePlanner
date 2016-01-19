//  *******************************************************************************************************************
//  TextBoxControl   version:  1.0   Ankur Sheel  date: 2011/12/01
//  *******************************************************************************************************************
//  purpose
//  *******************************************************************************************************************
#ifndef TextBoxControl_h__
#define TextBoxControl_h__

#include "BaseControl.h"

namespace Base
{
	template<class BaseType, class SubType> 
	BaseType * GenericObjectCreationFunction();
}

namespace Graphics
{
	class ISentence;
	class ISprite;
}

namespace Utilities
{
	class ITimer;
}

namespace Graphics
{
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @brief Class Declaration for a TextBox UI Control
	///
	///
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class cTextBoxControl
		: public cBaseControl
	{
	public:
	public:
		static Base::cHashedString	GetName()  {return m_Name; }
		~cTextBoxControl();

	private:
		cTextBoxControl();
		void VInitialize(const shared_ptr<Utilities::IXMLNode const> pXMLNode);
		shared_ptr<IBaseControl> VDuplicate();
		void VRender(const ICamera * const pCamera);
		bool VOnKeyDown(const unsigned int iCharID);
		bool VOnCharPress(const unsigned int iCharID);
		void VSetText(const Base::cString & strText);
		void VSetAbsolutePosition();
		void VOnFocusChanged();
		void VCleanup();
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Inserts the text at the carat position
		///
		/// @param[in] Text The text to be inserted
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		bool InsertText(const Base::cString & Text);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Removes the Quantity characters at the carat position
		///
		/// @param[in] Quantity The number of characters to be removed
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void RemoveText(const unsigned int Quantity);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Returns the width in pixels of the text in the textbox.
		///
		/// @return The width in pixels of the text in the textbox.
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		float GetStringWidth();
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Returns the width of the sentence thats has been passed in Text
		///
		/// @param[in] strText The text for which the width is needed
		/// @return The width of the text that has been passed 
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		float GetStringWidth(const Base::cString & Text);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Sets the text of the textbox
		///
		/// @param[in] Text The text to be set
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void SetText(const Base::cString & Text);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Sets the position of the carat. The position is constrained between 0 and the sentence length.
		///
		/// @param[in] Pos The new position of the carat
		/// @return True if the carat was set to iPos. False otherwise
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		bool SetCaratPosition(const unsigned int Pos);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Sets the absolute position of the carat on the screen
		///
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		void SetCaratAbsolutePosition();

	private:
		ISentence *	m_pSentence;	/// The text in the textbox.
		ISprite *	m_pCaretSprite;	/// The sprite of the caret line.
		float	m_CaretPosInTextBox;	/// The position (in pixles) of the caret in the textbox.
		float	m_LastCaretUpdateTime;	/// The time at which the caret visibility was last updated.
		unsigned int	m_CaretPosInText;	/// The position of the carat in the text.
		bool	m_TextBoxFull;	/// True if textbox cannot contain any more characters. False otherwise.
		float	m_CaretUpdateTime;	/// The time after which the caret visibility should be updated.
		Utilities::ITimer *	m_pTimer;	/// The timer for updating the caret visibility.
		bool	m_IsCaretVisible;	/// True if the caret is currently visible. False otherwise.
		static Base::cHashedString	m_Name;	///< The control name.

	private:
		template<class BaseType, class SubType> 
		friend BaseType * Base::GenericObjectCreationFunction();
	};
}
#endif // TextBoxControl_h__s