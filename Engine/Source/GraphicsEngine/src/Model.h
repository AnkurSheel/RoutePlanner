// *****************************************************************************
//  Model   version:  1.0   Ankur Sheel  date: 2012/09/13
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#ifndef Model_h__
#define Model_h__

#include "Model.hxx"
namespace Graphics
{
	class cTextureShader;
	class ITexture;
	class IBoundingBox;
}

namespace Graphics
{
	////////////////////////////////////////////////////////////////////////////
	/// @brief Class Declaration for \c IModel interface
	///
	///
	////////////////////////////////////////////////////////////////////////////
	class cModel
		: public IModel 
		, public Base::cNonCopyable
	{
	public:
		////////////////////////////////////////////////////////////////////////
		/// @brief Structure to hold the properties of the subsets
		///
		///
		////////////////////////////////////////////////////////////////////////
		struct stObjectSubset
		{
			UINT							m_iIndexCountInSubset;	///< The number of indices in this model
			UINT							m_iStartIndexNo;		///< The start index nuber of the subset in the index buffer
			Base::cColor					m_diffuseColor;			///< The diffuse color of this model subset
			shared_ptr<Graphics::ITexture>	m_pTexture;				///< The Texture of the model

			stObjectSubset()
				: m_iIndexCountInSubset(0)
				, m_iStartIndexNo(0)
			{

			}
		};
		cModel();
		~cModel();
		////////////////////////////////////////////////////////////////////////
		/// Initializes the model
		///
		/// @param[in] def The params to create the model
		////////////////////////////////////////////////////////////////////////
		bool OnInitialization(shared_ptr<const stModelDef> pModeldef);

	private:
		void VRender(const ICamera * const pCamera);
		void VRecalculateWorldMatrix(const Base::cVector3 vPosition,
			const Base::cVector3 vRotation, const Base::cVector3 vScale);
		const Graphics::IAABB * const VGetAABB() const;
		void VCleanup();
		////////////////////////////////////////////////////////////////////////
		/// Creates the vertex buffer using the vertex data
		///
		/// @param[in] pVertices The vertex data of this model
		/// @return True if the vertex buffer was created successfully
		///
		////////////////////////////////////////////////////////////////////////
		bool CreateVertexBuffer( const stTexVertex * const pVertices);
		////////////////////////////////////////////////////////////////////////
		/// Creates the index buffer using the index data
		///
		/// @param[in] pIndices The indices data of this model
		/// @return True if the index buffer was created successfully
		///
		////////////////////////////////////////////////////////////////////////
		bool CreateIndexBuffer(const unsigned long * const pIndices);

	private:
		ID3D11Buffer * 					m_pVertexBuffer;	///< The vertex buffer
		ID3D11Buffer *					m_pIndexBuffer;	///< The index buffer
		UINT							m_iVertexCount;	///< The number of vertices in this model
		UINT							m_iIndexCount;	///< The number of indices in this model
		UINT							m_iVertexSize;	///< The size of the vertex structure
		shared_ptr<cTextureShader>		m_pShader;	///< The shader responsible for rendering the model depending on the model vertex data type.
		std::vector<stObjectSubset>		m_vSubsets;	///< Vector of subsets of the model.
		XMFLOAT4X4						m_matWorld;	///< The transform Matrix of the model
		IBoundingBox *					m_pBoundingBox;	///< The bounding box of the model
		Base::cVector3					m_vBoundingSphereCentre;	///< The centre for bounding sphere of model
		float							m_fBoundingSphereRadius;	///< The radius of the bounding sphere of model
	};
}
#endif // Model_h__