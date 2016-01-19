// *****************************************************************************
//  Sentence   version:  1.0   Ankur Sheel  date: 2012/10/10
//  ---------------------------------------------------------------------------
//  
//  ---------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#ifndef Sentence_h__
#define Sentence_h__

#include "Sentence.hxx"

namespace Base
{
	class cString;
}

namespace Graphics
{
	class IMyFont;
	struct stTexVertex;
}

namespace Graphics
{
	/********************************************//**
	 * @brief Encapsulates all the text related functionality
	 ***********************************************/
	class cSentence
		: public ISentence
		, Base::cNonCopyable
	{
	public:
		cSentence() ;
	
	private:
		~cSentence() ;
		bool VInitialize(const Base::cString & strFont, 
			const Base::cString & strText, const Base::cColor & textColor);
		void VRender(const ICamera * const pCamera);
		void VSetPosition(const Base::cVector2 & vPosition);
		virtual Base::cString VGetText() const;
		void VSetText(const Base::cString & strText);
		void VSetTextColor(const Base::cColor & colorText);
		float VGetWidth() const ;
		float VGetWidth(const Base::cString & strText) const;
		float VGetHeight() const;
		void VSetHeight(const float fTextHeight);
		/********************************************//**
		 * return True if the vertex buffer was created successfully
		 *
		 * Creates the vertex buffer using the vertex data
		 ***********************************************/
		bool CreateVertexBuffer();
		/********************************************//**
		 * return True if the index buffer was created successfully
		 *
		 * Creates the index buffer using the index data
		 ***********************************************/
		bool CreateIndexBuffer( );
		/********************************************//**
		 * @param[in] pCamera The camera which contains the current view matrix
		 * return True if the vertex buffer was updated successfully
		 * 
		 * Recalculates the coordinates and updates the vertex data if the 
		 * position has changed for each line in the sentence
		 ***********************************************/
		bool ReInitializeVertexBuffer(const ICamera * const pCamera);
		/********************************************//**
		 * @param[out] pVertices The vertices data
		 * @param[in] iLineLength The length of the line 
		 * @param[in] iStartPos	The index at which this line starts in the whole text
		 * @param[in] vPos The position of the line
		 * @param[out] fWidth The length of the line in pixels
		 * 
		 * Recalculates the coordinates and updates the vertex data, if the 
		 * position has changed
		 ***********************************************/
		void InitializesVertexData(stTexVertex * const pVertices,
			const int iLineLength, const int iStartPos,
			const Base::cVector2 & vPos, float & fWidth);
		/********************************************//**
		 *
		 * Releases all the pointers/buffers
		 ***********************************************/
		void Cleanup();

	private:
		ID3D11Buffer * 						m_pVertexBuffer;	/*!< The vertex buffer */
		ID3D11Buffer *						m_pIndexBuffer;		/*!< The index buffer */
		Base::cString						m_strText;			/*!< The text that has to be displayed */
		shared_ptr<IMyFont>					m_pFont;			/*!< The font that needs to be used to display the text */
		Base::cColor						m_TextColor;		/*!< The text color */
		int									m_iVertexCount;		/*!< The number of vertices that have to be displayed */
		int									m_iIndexCount;		/*!< The number of indices that have to be displayed */
		Base::cVector2						m_vPosition;		/*!< The current position of the sprite */
		bool								m_bIsDirty;			/*!< True if the vertex data needs to be recalculated */
		float								m_fWidth;			/*!< The length of the text in pixels */
		float								m_fHeight;			/*!< The height of the text in pixels */
		float								m_fScale;			/*!< The scale of each character in the sentence relative to the actual size of the font */
	};
}
#endif // Sentence_h__