// *************************************************************************
//  ObjModelLoader   version:  1.0   Ankur Sheel  date: 2012/10/29
//  ------------------------------------------------------------------------
//  
//  ------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *************************************************************************
// 
// *************************************************************************

namespace Utilities
{
	class IFileInput;
}

namespace Graphics
{
	struct stObjFaceInfo
	{
		int iPosIndex;
		int iTexCoordIndex;

		stObjFaceInfo()
			:iPosIndex(0)
			, iTexCoordIndex(0)
		{
		}
	};
	
	struct stObjSubsetData
	{
		std::vector<stObjFaceInfo> vFaces;
		Base::cColor diffuseColor;
		Base::cString strDiffuseTextureFilename;
		int iStartIndexNo;

		stObjSubsetData()
			: iStartIndexNo(0)
		{
		}
	};

	struct stSPDOVertexData
	{
		Base::cVector3 vPos;
		Base::cVector3 vTex;
	};

	struct stSPDOSubsetData
	{
		std::vector<int> vIndexData;
		Base::cColor diffuseColor;
		Base::cString strDiffuseTextureFilename;
		int iStartIndexNo;
		Base::cVector3 vBoundingBoxMinPos;
		Base::cVector3 vBoundingBoxMaxPos;

		stSPDOSubsetData()
			: iStartIndexNo(0)
			, vBoundingBoxMaxPos(- Base::MaxFloat, -Base::MaxFloat, -Base::MaxFloat)
			, vBoundingBoxMinPos(Base::MaxFloat, Base::MaxFloat, Base::MaxFloat)
		{
		}
	};

	struct stMaterial
	{
		Base::cString strMatName;

		// Surface's colors
		Base::cColor Diffuse;       // Transparency (Alpha) stored in 4th component

		// Textures
		Base::cString strDiffuseTextureFilename;
	};

	class cObjModelLoader
	{
		typedef std::map<Base::cString, stMaterial> MaterialMap;

	public:
		cObjModelLoader();
		~cObjModelLoader();
		void ConvertObjFile(const Base::cString & strObjFile, const Base::cString & strOutputFile);

	private:
		void LoadObjFile(const Base::cString & strObjFile);
		stObjFaceInfo ParseFaceInfo(const Base::cString & strFaceVal);
		void LoadMaterialFile(const Base::cString & strMaterialFile);
		void BuildVertexAndIndexData();
		void WriteSPDOFile(const Base::cString & strOutputFile);
		float GetFloatValue(const Base::cString & strVal);
		int GetIntValue(const Base::cString & strVal);

	private:
		MaterialMap						m_MaterialsMap;
		std::vector<stObjSubsetData>	m_vObjSubset;
		std::vector<Base::cVector3>		m_vVertexTexCoordinates;
		std::vector<Base::cVector3>		m_vVertexPositions;
		int								m_iTotalIndices;
		std::vector<stSPDOVertexData>	m_vVertexData;
		std::vector<stSPDOSubsetData>	m_vSubsetData;
		Base::cVector3					m_vBoundingBoxMinPos;
		Base::cVector3					m_vBoundingBoxMaxPos;
	};
}