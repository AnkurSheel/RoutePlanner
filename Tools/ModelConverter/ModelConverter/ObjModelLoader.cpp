// *************************************************************************
//  ObjModelLoader   version:  1.0   Ankur Sheel  date: 2012/10/29
//  ------------------------------------------------------------------------
//  
//  ------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *************************************************************************
// 
// *************************************************************************

#include "stdafx.h"
#include "ObjModelLoader.h"
#include "Optional.h"
#include "Vector3.h"
#include "FileInput.hxx"
#include "FileOutput.hxx"

using namespace Graphics;
using namespace Base;
using namespace Utilities;
using namespace std;

// *************************************************************************
cObjModelLoader::cObjModelLoader()
: m_vBoundingBoxMaxPos(-MaxFloat, -MaxFloat, -MaxFloat)
, m_vBoundingBoxMinPos(MaxFloat, MaxFloat, MaxFloat)
{

}

// *************************************************************************
cObjModelLoader::~cObjModelLoader()
{
	m_MaterialsMap.clear();
}
// *************************************************************************
void cObjModelLoader::ConvertObjFile(const Base::cString & strObjFile,
									 const Base::cString & strOutputFile)
{
	LoadObjFile(strObjFile);
	BuildVertexAndIndexData();
	WriteSPDOFile(strOutputFile);
	
	m_MaterialsMap.clear();
}

// *************************************************************************
void cObjModelLoader::LoadObjFile(const Base::cString & strObjFile)
{
	shared_ptr<IFileInput> pObjFile = shared_ptr<IFileInput>(IFileInput::CreateInputFile());

	if(pObjFile->Open(strObjFile, std::ios_base::in))
	{
		cString strLine;
		vector<cString> vtokens;
		int iCurrentSubset = -1;
		int iStartIndexNo = 0;
		do
		{
			strLine = pObjFile->ReadLine();
			if(!strLine.IsEmpty())
			{
				if (strLine[0] == '#')
				{
					continue;
				}
				strLine.TrimBoth();
				if(!strLine.IsEmpty())
				{
					vtokens.clear();
					strLine.Tokenize(' ', vtokens);
					// vertices
					if (vtokens[0] == "v")
					{
						float x = GetFloatValue(vtokens[1]);
						float y = GetFloatValue(vtokens[2]);
						float z = GetFloatValue(vtokens[3]);

						// invert z coordinate vertice
						//z = z * -1.0f;

						m_vVertexPositions.push_back(cVector3(x, y, z));
					}
					else if(vtokens[0] == "vt")
					{
						float u = GetFloatValue(vtokens[1]);
						float v = GetFloatValue(vtokens[2]);
						float w = 0.0f;
						if (vtokens.size() == 4)
						{
							w = GetFloatValue(vtokens[3]);
						}
						m_vVertexTexCoordinates.push_back(cVector3(u, v, w));
					}
					// faces/triangles
					else if (vtokens[0] == "f")
					{
						m_vObjSubset[iCurrentSubset].vFaces.push_back(ParseFaceInfo(vtokens[1]));
						m_vObjSubset[iCurrentSubset].vFaces.push_back(ParseFaceInfo(vtokens[2]));
						m_vObjSubset[iCurrentSubset].vFaces.push_back(ParseFaceInfo(vtokens[3]));
						iStartIndexNo += 3;
					}
					else if (vtokens[0] == "mtllib")
					{
						LoadMaterialFile(vtokens[1]);
					}
					else if (vtokens[0] == "usemtl")
					{
						MaterialMap::const_iterator curr = m_MaterialsMap.find(vtokens[1]);
						if (curr != m_MaterialsMap.end())
						{
							iCurrentSubset++;
							stObjSubsetData subset;
							subset.diffuseColor = curr->second.Diffuse;
							subset.iStartIndexNo = iStartIndexNo;
							subset.strDiffuseTextureFilename = curr->second.strDiffuseTextureFilename;
							m_vObjSubset.push_back(subset);
						}
					}
				}
			}
		}
		while(!pObjFile->IsEOF() || !strLine.IsEmpty());
		pObjFile->Close();
	}
}

// *************************************************************************
void cObjModelLoader::LoadMaterialFile(const Base::cString & strMaterialFile)
{
	shared_ptr<IFileInput> pMtlFile = shared_ptr<IFileInput>(IFileInput::CreateInputFile());

	if(pMtlFile->Open(strMaterialFile, std::ios_base::in))
	{
		cString strLine;
		vector<cString> vtokens;
		cString strCurrentMaterialName;

		do
		{
			strLine = pMtlFile->ReadLine();
			if(!strLine.IsEmpty())
			{
				if (strLine[0] == '#')
				{
					continue;
				}
				strLine.TrimBoth();
				if(!strLine.IsEmpty())
				{
					vtokens.clear();
					strLine.Tokenize(' ', vtokens);
					// vertices
					if (vtokens[0] == "newmtl")
					{
						stMaterial material;
						strCurrentMaterialName = vtokens[1];
						material.strMatName = strCurrentMaterialName;
						m_MaterialsMap.insert(std::make_pair(strCurrentMaterialName, material));
					}
					else if (vtokens[0] == "Kd")
					{
						MaterialMap::iterator curr = m_MaterialsMap.find(strCurrentMaterialName);
						if (curr != m_MaterialsMap.end())
						{
							float r = GetFloatValue(vtokens[1]);
							float g = GetFloatValue(vtokens[2]);
							float b = GetFloatValue(vtokens[3]);
							(curr->second).Diffuse = cColor(r, g, b, 1.0f);
						}

					}
					else if (vtokens[0] == "map_Kd")
					{
						MaterialMap::iterator curr = m_MaterialsMap.find(strCurrentMaterialName);
						if (curr != m_MaterialsMap.end())
						{
							(curr->second).strDiffuseTextureFilename = vtokens[1];

						}

					}
				}
			}
		}
		while(!pMtlFile->IsEOF() || !strLine.IsEmpty());
		pMtlFile->Close();
	}
}

// *************************************************************************
stObjFaceInfo cObjModelLoader::ParseFaceInfo(const Base::cString & strFaceVal)
{
	stObjFaceInfo faceInfo;

	vector<cString> vtokens;
	strFaceVal.Tokenize('/', vtokens);

	for (unsigned int i = 0; i<vtokens.size();i++)
	{
		int iVal = GetIntValue(vtokens[i]) - 1;
		if (i == 0)
		{
			faceInfo.iPosIndex = iVal;
		}
		else if (i == 1)
		{
			faceInfo.iTexCoordIndex = iVal;
		}
	}
	return faceInfo;
}

// *************************************************************************
void cObjModelLoader::BuildVertexAndIndexData()
{
	m_iTotalIndices = 0;
	int totalVerts = 0;

	vector<stObjFaceInfo> vVertexIndex;

	for(unsigned int i=0; i< m_vObjSubset.size(); i++)
	{
		stObjSubsetData objSubset = m_vObjSubset[i];
		stSPDOSubsetData subsetData;

		subsetData.diffuseColor = objSubset.diffuseColor;
		subsetData.iStartIndexNo = objSubset.iStartIndexNo;
		subsetData.strDiffuseTextureFilename = objSubset.strDiffuseTextureFilename;

		for(unsigned int j = 0; j < objSubset.vFaces.size(); j++)
		{
			stObjFaceInfo faceInfo = objSubset.vFaces[j];
			bool vertAlreadyExists = false;
			if(totalVerts >= 3)
			{
				for(int iCheck = 0; iCheck < totalVerts; iCheck++)
				{
					if(!vertAlreadyExists && faceInfo.iPosIndex == vVertexIndex[iCheck].iPosIndex
						&& faceInfo.iTexCoordIndex == vVertexIndex[iCheck].iTexCoordIndex)
					{
						subsetData.vIndexData.push_back(iCheck);		//Set index for this vertex
						vertAlreadyExists = true;		//If we've made it here, the vertex already exists
						break;
					}
				}
			}

			//If this vertex is not already in our vertex arrays, put it there
			if(!vertAlreadyExists)
			{
				vVertexIndex.push_back(faceInfo);
				subsetData.vIndexData.push_back(totalVerts);		//Set index for this vertex
				stSPDOVertexData spdoVertexData;
				spdoVertexData.vPos = m_vVertexPositions[faceInfo.iPosIndex];
				if (m_vVertexTexCoordinates.empty())
				{
					spdoVertexData.vTex = cVector3::Zero();
				}
				else
				{
					spdoVertexData.vTex = m_vVertexTexCoordinates[faceInfo.iTexCoordIndex];
				}
				m_vVertexData.push_back(spdoVertexData);
				totalVerts++;	//We created a new vertex

				// get the bounding box min pos
				subsetData.vBoundingBoxMinPos.x = min(subsetData.vBoundingBoxMinPos.x, spdoVertexData.vPos.x);
				subsetData.vBoundingBoxMinPos.y = min(subsetData.vBoundingBoxMinPos.y, spdoVertexData.vPos.y);
				subsetData.vBoundingBoxMinPos.z = min(subsetData.vBoundingBoxMinPos.z, spdoVertexData.vPos.z);

				// get the bounding box max pos
				subsetData.vBoundingBoxMaxPos.x = max(subsetData.vBoundingBoxMaxPos.x, spdoVertexData.vPos.x);
				subsetData.vBoundingBoxMaxPos.y = max(subsetData.vBoundingBoxMaxPos.y, spdoVertexData.vPos.y);
				subsetData.vBoundingBoxMaxPos.z = max(subsetData.vBoundingBoxMaxPos.z, spdoVertexData.vPos.z);
			}		
			m_iTotalIndices++;
		}
		m_vSubsetData.push_back(subsetData);
	}
	
	for(unsigned int i=0; i< m_vSubsetData.size(); i++)
	{
		m_vBoundingBoxMinPos.x = min(m_vBoundingBoxMinPos.x, m_vSubsetData[i].vBoundingBoxMinPos.x);
		m_vBoundingBoxMinPos.y = min(m_vBoundingBoxMinPos.y, m_vSubsetData[i].vBoundingBoxMinPos.y);
		m_vBoundingBoxMinPos.z = min(m_vBoundingBoxMinPos.z, m_vSubsetData[i].vBoundingBoxMinPos.z);

		// get the bounding box max pos
		m_vBoundingBoxMaxPos.x = max(m_vBoundingBoxMaxPos.x, m_vSubsetData[i].vBoundingBoxMaxPos.x);
		m_vBoundingBoxMaxPos.y = max(m_vBoundingBoxMaxPos.y, m_vSubsetData[i].vBoundingBoxMaxPos.y);
		m_vBoundingBoxMaxPos.z = max(m_vBoundingBoxMaxPos.z, m_vSubsetData[i].vBoundingBoxMaxPos.z);
		
	}
}

// *************************************************************************
void cObjModelLoader::WriteSPDOFile(const cString & strOutputFile) 
{
	shared_ptr<IFileOutput> pOutputFile = shared_ptr<IFileOutput>(IFileOutput::CreateOutputFile());

	if(pOutputFile->Open(strOutputFile, std::ios_base::out))
	{
		pOutputFile->WriteLine(cString(100, "VertexCount %d\n\n", m_vVertexData.size()));
		for (unsigned int i=0; i<m_vVertexData.size(); i++)
		{
			pOutputFile->WriteLine(cString(100, "v %0.2f %0.2f %0.2f %0.2f %0.2f %0.2f\n",
				m_vVertexData[i].vPos.x, m_vVertexData[i].vPos.y, m_vVertexData[i].vPos.z,
				m_vVertexData[i].vTex.x, m_vVertexData[i].vTex.y, m_vVertexData[i].vTex.z));
		}
		pOutputFile->WriteLine(cString(100, "\nTotalIndexCount %d\n\n", m_iTotalIndices));
		for(unsigned int i=0; i< m_vSubsetData.size(); i++)
		{
			for(unsigned int j=0; j<m_vSubsetData[i].vIndexData.size();)
			{
				pOutputFile->WriteLine("t ");
				pOutputFile->WriteLine(cString(100, "%d ", m_vSubsetData[i].vIndexData[j++]));
				pOutputFile->WriteLine(cString(100, "%d ", m_vSubsetData[i].vIndexData[j++]));
				pOutputFile->WriteLine(cString(100, "%d\n", m_vSubsetData[i].vIndexData[j++]));
			}
		}

		pOutputFile->WriteLine(cString(100, "\nBBMin %0.2f %0.2f %0.2f\n",
			m_vBoundingBoxMinPos.x, m_vBoundingBoxMinPos.y,	m_vBoundingBoxMinPos.z));

		pOutputFile->WriteLine(cString(100, "BBMax %0.2f %0.2f %0.2f\n",
			m_vBoundingBoxMaxPos.x, m_vBoundingBoxMaxPos.y, m_vBoundingBoxMaxPos.z));

		for(unsigned int i=0; i< m_vSubsetData.size(); i++)
		{
			pOutputFile->WriteLine(cString(100, "\nSubset %d\n\n", i));

			pOutputFile->WriteLine(cString(100, "startindex %d\n", m_vSubsetData[i].iStartIndexNo));
			pOutputFile->WriteLine(cString(100, "indexcount %d\n", m_vSubsetData[i].vIndexData.size()));

			pOutputFile->WriteLine(cString(100, "SBBMin %0.2f %0.2f %0.2f\n",
				m_vSubsetData[i].vBoundingBoxMinPos.x, m_vSubsetData[i].vBoundingBoxMinPos.y,
				m_vSubsetData[i].vBoundingBoxMinPos.z));

			pOutputFile->WriteLine(cString(100, "SBBMax %0.2f %0.2f %0.2f\n",
				m_vSubsetData[i].vBoundingBoxMaxPos.x, m_vSubsetData[i].vBoundingBoxMaxPos.y,
				m_vSubsetData[i].vBoundingBoxMaxPos.z));

			pOutputFile->WriteLine(cString(100, "diffusecolor %d %d %d %d\n",
				m_vSubsetData[i].diffuseColor.m_iRed, m_vSubsetData[i].diffuseColor.m_iBlue,
				m_vSubsetData[i].diffuseColor.m_iGreen, m_vSubsetData[i].diffuseColor.m_iAlpha));

			if (!m_vSubsetData[i].strDiffuseTextureFilename.IsEmpty())
			{
				pOutputFile->WriteLine("dTex " + m_vSubsetData[i].strDiffuseTextureFilename + "\n");
			}
		}
		pOutputFile->Close();
	}
}

// *************************************************************************
float cObjModelLoader::GetFloatValue(const cString & strVal)
{
	tOptional<float> val = strVal.ToFloat();
	if (val.IsValid())
	{
		return *val;
	}
	return 0;
}

// *************************************************************************
int cObjModelLoader::GetIntValue(const Base::cString & strVal)
{
	tOptional<int> val = strVal.ToInt();
	if (val.IsValid())
	{
		return *val;
	}
	return 0;
}
