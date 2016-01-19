#include "stdafx.h"
#include "ShaderManager.h"
#include "Shader.hxx"

using namespace Graphics;
using namespace Utilities;
using namespace Base;

IShaderManager * cShaderManager::s_pShadermanager = NULL;

//  *******************************************************************************************************************
cShaderManager::cShaderManager()
{

}

//  *******************************************************************************************************************
cShaderManager::~cShaderManager()
{
	m_pShaders.clear();
}

//  *******************************************************************************************************************
bool cShaderManager::VGetShader(shared_ptr<IShader> & pShader, const cString & strShaderName)
{
	bool bSuccess = true;
	unsigned long hash = cHashedString::CalculateChecksum(strShaderName);
	shared_ptr<IShader> ptr = Find(hash);

	if(ptr == NULL)
	{
		bSuccess = pShader->VInitialize(strShaderName);
		if(bSuccess)
		{
			m_pShaders[hash] = pShader;
		}
	}
	else
	{
		SP_LOG(3, "Shader already loaded " + strShaderName);
		pShader = ptr;
	}
	return bSuccess;
}

//  *******************************************************************************************************************
shared_ptr<IShader> cShaderManager::Find(const unsigned long ulShaderHash)
{
	auto itr = m_pShaders.find(ulShaderHash);
	if(itr == m_pShaders.end())
	{
		return shared_ptr<IShader>(); 
	}

	return (*itr).second;
}

//  *******************************************************************************************************************
IShaderManager * IShaderManager::GetInstance()
{
	if(cShaderManager::s_pShadermanager == NULL)
		cShaderManager::s_pShadermanager = DEBUG_NEW cShaderManager();
	return cShaderManager::s_pShadermanager ;
}

//  *******************************************************************************************************************
void IShaderManager::Destroy()
{
	SafeDelete(&cShaderManager::s_pShadermanager);
}