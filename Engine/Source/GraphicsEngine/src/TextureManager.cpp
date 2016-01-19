#include "stdafx.h"
#include "TextureManager.h"
#include "Texture.hxx"

using namespace Graphics;
using namespace Utilities;
using namespace Base;

ITextureManager * cTextureManager::s_pTexturemanager = NULL;

//  *******************************************************************************************************************
cTextureManager::cTextureManager()
{

}

//  *******************************************************************************************************************
cTextureManager::~cTextureManager()
{
	m_pTextures.clear();
}

//  *******************************************************************************************************************
shared_ptr<ITexture> cTextureManager::VGetTexture(const cString & strTexturePath)
{
	unsigned long hash = cHashedString::CalculateChecksum(strTexturePath);
	shared_ptr<ITexture> ptr = Find(hash);

	if(ptr == NULL)
	{
		ptr = ITexture::CreateTexture(strTexturePath);
		m_pTextures[hash] = ptr;
	}
	else
	{
		SP_LOG(3, "Texture already loaded " + 			strTexturePath);
	}
	return ptr;
}

//  *******************************************************************************************************************
shared_ptr<ITexture> cTextureManager::Find(const unsigned long ulTextureHash)
{
	auto itr = m_pTextures.find(ulTextureHash);
	if(itr == m_pTextures.end())
	{
		return shared_ptr<ITexture>(); 
	}

	return (*itr).second;
}

//  *******************************************************************************************************************
ITextureManager * ITextureManager::GetInstance()
{
	if(cTextureManager::s_pTexturemanager == NULL)
		cTextureManager::s_pTexturemanager = DEBUG_NEW cTextureManager();
	return cTextureManager::s_pTexturemanager ;
}

//  *******************************************************************************************************************
void ITextureManager::Destroy()
{
	SafeDelete(&cTextureManager::s_pTexturemanager);
}