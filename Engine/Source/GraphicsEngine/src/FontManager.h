// *************************************************************************
//  FontManager   version:  1.0   Ankur Sheel  date: 2012/11/27
//  ------------------------------------------------------------------------
//  
//  ------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *************************************************************************
// 
// *************************************************************************

#include "FontManager.hxx"

namespace Graphics
{
	class IMyFont;
}

namespace Graphics
{
	/********************************************//**
     * @brief Class Declaration for \c IFontManager
     * interface
     ***********************************************/
	class cFontManager
		: public IFontManager
	{
		/** Map of Fonts. The key is the hash of the font filename. Value is a shared_ptr to the actual font */
		typedef std::map<unsigned long, shared_ptr <IMyFont> > FontMap;

	private:
		cFontManager();
		~cFontManager();
		shared_ptr<IMyFont> VGetFont(const Base::cString & strFontName);
		/********************************************//**
 		 * param[in] ulFontHash The hash of the name of the font name
		 * @return Pointer to the font if it is found in the font list. NULL otherwise
		 *
		 * Checks if the font has already been loaded. Returns a pointer to the font if
		 * it is found. NULL otherwise.
		 ***********************************************/
		shared_ptr<IMyFont> Find(const unsigned long ulFontHash);

	private:
		FontMap		m_pFonts;					/*!< map of the fonts that have already been loaded */
		static IFontManager * s_pFontManager;	/*!< static object of this class */

	private:
		friend static IFontManager * IFontManager::GetInstance();
		friend static void IFontManager::Destroy();

	};
}
