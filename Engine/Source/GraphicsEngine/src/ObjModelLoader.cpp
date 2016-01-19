#include "stdafx.h"
#include "ObjModelLoader.h"
#include "FileIO.hxx"
#include "Optional.h"
#include "Model.hxx"
#include "vertexstruct.h"
#include "GameDirectories.h"
#include "ResCache.hxx"
#include "ResourceManager.hxx"

using namespace Graphics;
using namespace Base;
using namespace Utilities;
using namespace std;

IObjModelLoader * cObjModelLoader::s_pModelLoader = NULL;

//  *******************************************************************************************************************
cObjModelLoader::cObjModelLoader()
{
}

//  *******************************************************************************************************************
cObjModelLoader::~cObjModelLoader()
{
	Cleanup();
}

//  *******************************************************************************************************************
shared_ptr<stModelDef> cObjModelLoader::VGetModelDef(const Base::cString & strModelFile)
{
	unsigned long hash = cHashedString::CalculateChecksum(strModelFile);
	shared_ptr<stModelDef> ptr = Find(hash);

	if(ptr == NULL)
	{
		ptr = LoadModelDef(strModelFile);
		m_pModelDefMap[hash] = ptr;
	}
	else
	{
		SP_LOG(3, "Model def already loaded: " + strModelFile);
	}
	return ptr;
}

//  *******************************************************************************************************************
shared_ptr<stModelDef> cObjModelLoader::LoadModelDef(const cString & strModelFile)
{
	//shared_ptr<IFileInput> pObjFile = shared_ptr<IFileInput>(IFileInput::CreateInputFile());

	cString strModelPath = cGameDirectories::GetModelDirectory() + strModelFile + ".spdo";
	IResource * pResource = IResource::CreateResource(strModelPath);
	shared_ptr<IResHandle> modelHandle = IResourceManager::GetInstance()->VGetResourceCache()->GetHandle(*pResource);
	shared_ptr<stModelDef> pDef;

	if (modelHandle != NULL)
	{
		cString str(modelHandle->GetBuffer());
		vector<cString> vLines;
		str.Tokenize("\n", vLines);

		vector<cString> vtokens;
		pDef = shared_ptr<stModelDef>(DEBUG_NEW stModelDef());
		int iCurrentVertexNo = 0;
		int iCurrentIndexNo = 0;
		int iCurrentSubsetNumber = -1;
		for (auto iter = vLines.begin(); iter != vLines.end(); iter++)
		{
			cString strLine = (*iter);
			if(!strLine.IsEmpty())
			{
				strLine.TrimBoth();
				if(!strLine.IsEmpty())
				{
					vtokens.clear();
					strLine.Tokenize(" ", vtokens);
					// vertex Count
					if (vtokens[0] == "VertexCount")
					{
						pDef->iNumberOfVertices = GetIntValue(vtokens[1]);
						pDef->pVertices = DEBUG_NEW stTexVertex[pDef->iNumberOfVertices];
					}
					//vertex data
					else if(vtokens[0] == "v")
					{
						pDef->pVertices[iCurrentVertexNo].m_fX = GetFloatValue(vtokens[1]);
						pDef->pVertices[iCurrentVertexNo].m_fY = GetFloatValue(vtokens[2]);
						pDef->pVertices[iCurrentVertexNo].m_fZ = GetFloatValue(vtokens[3]);
						pDef->pVertices[iCurrentVertexNo].m_fTex0 = GetFloatValue(vtokens[4]);
						pDef->pVertices[iCurrentVertexNo].m_fTex1 = GetFloatValue(vtokens[5]);
						iCurrentVertexNo++;
					}
					// total index Count
					else if (vtokens[0] == "TotalIndexCount")
					{
						pDef->iNumberOfIndices = GetIntValue(vtokens[1]);
						pDef->pIndices = DEBUG_NEW unsigned long[pDef->iNumberOfIndices];
					}
					// faces/triangles
					else if (vtokens[0] == "t")
					{
						pDef->pIndices[iCurrentIndexNo++] = GetIntValue(vtokens[1]);
						pDef->pIndices[iCurrentIndexNo++] = GetIntValue(vtokens[2]);
						pDef->pIndices[iCurrentIndexNo++] = GetIntValue(vtokens[3]);
					}
					// min pos of Bounding Box
					else if(vtokens[0] == "BBMin")
					{
						pDef->vBoundingBoxMinPos.x = GetFloatValue(vtokens[1]);
						pDef->vBoundingBoxMinPos.y = GetFloatValue(vtokens[2]);
						pDef->vBoundingBoxMinPos.z = GetFloatValue(vtokens[3]);
					}
					// max pos of Bounding Box
					else if(vtokens[0] == "BBMax")
					{
						pDef->vBoundingBoxMaxPos.x = GetFloatValue(vtokens[1]);
						pDef->vBoundingBoxMaxPos.y = GetFloatValue(vtokens[2]);
						pDef->vBoundingBoxMaxPos.z = GetFloatValue(vtokens[3]);
					}
					// new subset
					else if(vtokens[0] == "Subset")
					{
						stModelDef::stSubsetDef subset;
						pDef->vSubsetsDef.push_back(subset);
						iCurrentSubsetNumber++;
					}
					else if(vtokens[0] == "startindex")
					{
						pDef->vSubsetsDef[iCurrentSubsetNumber].iStartIndexNo = GetIntValue(vtokens[1]);
					}
					else if(vtokens[0] == "indexcount")
					{
						pDef->vSubsetsDef[iCurrentSubsetNumber].iNumberOfIndicesinSubset = GetIntValue(vtokens[1]);
					}
					// min pos of subset Bounding Box
					else if(vtokens[0] == "SBBMin")
					{
						pDef->vSubsetsDef[iCurrentSubsetNumber].vBoundingBoxMinPos.x = GetFloatValue(vtokens[1]);
						pDef->vSubsetsDef[iCurrentSubsetNumber].vBoundingBoxMinPos.y = GetFloatValue(vtokens[2]);
						pDef->vSubsetsDef[iCurrentSubsetNumber].vBoundingBoxMinPos.z = GetFloatValue(vtokens[3]);
					}
					// max pos of subset Bounding Box
					else if(vtokens[0] == "SBBMax")
					{
						pDef->vSubsetsDef[iCurrentSubsetNumber].vBoundingBoxMaxPos.x = GetFloatValue(vtokens[1]);
						pDef->vSubsetsDef[iCurrentSubsetNumber].vBoundingBoxMaxPos.y = GetFloatValue(vtokens[2]);
						pDef->vSubsetsDef[iCurrentSubsetNumber].vBoundingBoxMaxPos.z = GetFloatValue(vtokens[3]);
					}
					else if(vtokens[0] == "diffusecolor")
					{
						int r = GetIntValue(vtokens[1]);
						int b = GetIntValue(vtokens[2]);
						int g = GetIntValue(vtokens[3]);
						int a = GetIntValue(vtokens[4]);
						pDef->vSubsetsDef[iCurrentSubsetNumber].diffuseColor = cColor(r, g, b, a);
					}
					else if(vtokens[0] == "dTex")
					{
						pDef->vSubsetsDef[iCurrentSubsetNumber].strDiffuseTextureFilename = vtokens[1];
					}
				}
			}
		}
	}
	SafeDelete(&pResource);
	return pDef;
}

//  *******************************************************************************************************************
float cObjModelLoader::GetFloatValue(const cString & strVal)
{
	tOptional<float> val = strVal.ToFloat();
	if (val.IsValid())
	{
		return val.GetValue();
	}
	return 0;
}

//  *******************************************************************************************************************
int cObjModelLoader::GetIntValue(const Base::cString & strVal)
{
	tOptional<int> val = strVal.ToInt();
	if (val.IsValid())
	{
		return val.GetValue();
	}
	return 0;

}

// *************************************************************************
shared_ptr<stModelDef> cObjModelLoader::Find(const unsigned long ulModelDefHash)
{
	auto itr = m_pModelDefMap.find(ulModelDefHash);
	if(itr == m_pModelDefMap.end())
	{
		return shared_ptr<stModelDef>(); 
	}

	return (*itr).second;
}

//  *******************************************************************************************************************
void cObjModelLoader::Cleanup()
{
	for(auto iter = m_pModelDefMap.begin(); iter != m_pModelDefMap.end(); iter++)
	{
		if(iter->second)
		{
			SafeDeleteArray(&(iter->second->pVertices));
			SafeDeleteArray(&(iter->second->pIndices));
		}
	}
	m_pModelDefMap.clear();
}

//  *******************************************************************************************************************
IObjModelLoader * IObjModelLoader::GetInstance()
{
	if(cObjModelLoader::s_pModelLoader == NULL)
		cObjModelLoader::s_pModelLoader = DEBUG_NEW cObjModelLoader();
	return cObjModelLoader::s_pModelLoader;
}

//  *******************************************************************************************************************
void IObjModelLoader::Destroy()
{
	SafeDelete(&cObjModelLoader::s_pModelLoader);
}
