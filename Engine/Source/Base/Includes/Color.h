//  *******************************************************************************************************************
//  Color   version:  1.0   Ankur Sheel  date: 2012/09/03
//  *******************************************************************************************************************
// 
//  *******************************************************************************************************************
#ifndef Color_h__
#define Color_h__

#include "BaseDefines.h"

namespace Base
{
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// @brief RGBA Color class 
	///
	/// 
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class cColor
	{
	public:
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Default Constructor which set RGBA to be 0
		///
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		BASE_API cColor();
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Constructor which takes in RGBA components as int values. 
		/// Clamps the values to be between 0 and 255
		///
		/// @param[in] red Red component of color.
		/// @param[in] green Green component of color.
		/// @param[in] blue Blue component of color.
		/// @param[in] alpha Alpha component of color.
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		BASE_API explicit cColor(int red, int green, int blue, int alpha);
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Constructor which takes in RGBA components as float values. 
		/// Clamps the values to be between 0.0f and 1.0f
		///
		/// @param[in] red Red component of color.
		/// @param[in] green Green component of color.
		/// @param[in] blue Blue component of color.
		/// @param[in] alpha Alpha component of color.
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		BASE_API explicit cColor(float red, float green, float blue, float alpha);
		BASE_API ~cColor();
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/// Calculates the components of the color as floats in the range 0 to 1.0f
		///
		/// @param[out] fRed Red component of color.
		/// @param[out] fGreen Green component of color.
		/// @param[out] fBlue Blue component of color.
		/// @param[out] fAlpha Alpha component of color.
		///
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		BASE_API void GetColorComponentsInFloat(float & red, float & blue, float & green, float & alpha) const;
		
	public:
			BASE_API static const cColor BLACK;	///< Black Color.
			BASE_API static const cColor WHITE;	///< White Color.
			BASE_API static const cColor RED;	///< Red Color.
			BASE_API static const cColor BLUE;	///< Blue Color.
			BASE_API static const cColor GREEN;	///< Green Color.
			BASE_API static const cColor GRAY;	///< Gray Color.
			BASE_API static const cColor TURQUOISE;	///< Turquoise Color.
			BASE_API static const cColor YELLOW;	///< Yellow Color.
			BASE_API static const cColor TAN;	///< Tan Color.
			BASE_API static const cColor ORANGE;	///< Orange Color.
			BASE_API static const cColor VIOLET;	///< Violet Color.

	public:
		int		m_Red;	///< Red component of the color.
		int		m_Green;	///< Green component of the color.
		int		m_Blue;	///< Blue component of the color.
		int		m_Alpha;	///< Alpha component of the color.
	};
}
#endif // Color_h__
