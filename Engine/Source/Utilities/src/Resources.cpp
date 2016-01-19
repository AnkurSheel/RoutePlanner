// *****************************************************************************
//  Resource   version:  1.0   Ankur Sheel  date: 2012/12/29
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#include "stdafx.h"
#include "Resources.h"

using namespace Utilities;
using namespace Base;
// *****************************************************************************
cResource::cResource(const cString & strFileName)
: m_strFileName(strFileName)
{
}

// *****************************************************************************
IResHandle * cResource::VCreateHandle(const char * pBuffer, unsigned int uiSize,
									  IResCache *pResCache)
{
	return DEBUG_NEW cResHandle((*this), (char *)pBuffer, uiSize, pResCache);
}

// *****************************************************************************
Base::cString cResource::VGetFileName() const
{
	return m_strFileName;
}

// *****************************************************************************
IResource * IResource::CreateResource(const Base::cString & strFileName)
{
	cResource * pResource = DEBUG_NEW cResource(strFileName);
	return pResource;
}

// *****************************************************************************
cResHandle::cResHandle(cResource & resource, char * pBuffer, unsigned int iSize, IResCache * pResCache)
: m_Resource(resource)
, m_pBuffer(pBuffer)
, m_iBufferSize(iSize)
, m_pResCache(pResCache)
{
}

// *****************************************************************************
cResHandle::~cResHandle()
{
	SafeDelete(&m_pBuffer);
	m_pResCache->MemoryHasBeenFreed(m_iBufferSize);
}

// *****************************************************************************
void cResHandle::Load(IResourceFile * pFile)
{
	return pFile->GetResource(m_Resource, m_pBuffer);
}

// *****************************************************************************
unsigned int cResHandle::GetSize() const
{
	return m_iBufferSize;
}

// *****************************************************************************
char * cResHandle::GetBuffer() const
{
	return m_pBuffer;
}

// *****************************************************************************
const IResource * cResHandle::GetResource() const
{
	return &m_Resource;
}
