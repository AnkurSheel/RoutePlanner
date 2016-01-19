#include "stdafx.h"
#include "ResCache.h"
#include "ZipFile.hxx"
#include "Optional.h"
#include "FileIO.hxx"

using namespace Utilities;
using namespace Base;

// ********************************************************************************************************************
cResCache::cResCache(unsigned int iCacheSizeInMB, const IResourceFile * pResFile)
	: m_iCacheSize(iCacheSizeInMB * MEGABYTE)
	, m_iTotalMemoryAllocated(0)
{
	m_pFile = const_cast<IResourceFile *>(pResFile);
}

// ********************************************************************************************************************
cResCache::~cResCache()
{
	while(!m_lru.empty())
	{
		FreeOneResource();
	}
	SafeDelete(&m_pFile);
}

// ********************************************************************************************************************
void cResCache::Init()
{
	m_pFile->Open();
}

// ********************************************************************************************************************
shared_ptr<IResHandle> cResCache::GetHandle(IResource & r)
{
	shared_ptr<IResHandle> handle(Find(r));
	if(handle == NULL)
	{
		handle = Load(r);
	}
	else
	{
		Update(handle);
	}
	return handle;
}

// ********************************************************************************************************************
void cResCache::Flush()
{
	while(m_lru.empty())
	{
		shared_ptr<IResHandle> handle = *(m_lru.begin());
		Free(handle);
		m_lru.pop_front();
	}
}

// ********************************************************************************************************************
shared_ptr<IResHandle> cResCache::Find(const IResource & r)
{
	auto itr = m_Resources.find(r.VGetFileName());
	if(itr == m_Resources.end())
	{
		SP_LOG(2, "Could not find in cache")(r.VGetFileName());
		return shared_ptr<IResHandle>(); 
	}
	SP_LOG(3, "Found in cache")(r.VGetFileName());

	return (*itr).second;
}

// ********************************************************************************************************************
const void cResCache::Update(shared_ptr<IResHandle> handle)
{
	m_lru.remove(handle);
	m_lru.push_front(handle);
}

// ********************************************************************************************************************
shared_ptr<IResHandle> cResCache::Load(IResource & r)
{
	int iSize = m_pFile->GetResourceSize(r);
	SP_ASSERT_ERROR(iSize > 0)(r.VGetFileName()).SetCustomMessage("Could not find file in zip file");

	char * pBuffer = Allocate(iSize);
	SP_ASSERT_ERROR(pBuffer != NULL).SetCustomMessage("Could not allocate memory");

	shared_ptr<IResHandle> handle(r.VCreateHandle(pBuffer, iSize, this));

	handle->Load(m_pFile);

	m_lru.push_front(handle);
	m_Resources[r.VGetFileName()] = handle;

	return handle;
}

// ********************************************************************************************************************
void cResCache::Free(shared_ptr<IResHandle> handle)
{
	m_lru.remove(handle);
	m_Resources.erase(handle->GetResource()->VGetFileName());
}

// ********************************************************************************************************************
bool cResCache::MakeRoom(unsigned int iSize)
{
	SP_ASSERT_ERROR(iSize < m_iCacheSize)(iSize)(m_iCacheSize).SetCustomMessage("File size is greater than cache size");

	while(iSize > (m_iCacheSize - m_iTotalMemoryAllocated))
	{
		SP_LOG_CUSTOM(AssertLevels::LEVEL_DEBUG, 2, "Cache needs to be freed to make space")(iSize)(m_iCacheSize)(m_iTotalMemoryAllocated);
		if(m_lru.empty())
		{
			return false;
		}
		FreeOneResource();
	}
	return true;
}

// ********************************************************************************************************************
char * cResCache::Allocate(unsigned int iSize)
{
	if(!MakeRoom(iSize))
	{
		return NULL;
	}
	char * pBuffer = DEBUG_NEW char[iSize];
	if(pBuffer)
	{	
		m_iTotalMemoryAllocated += iSize;
		SP_LOG_CUSTOM(AssertLevels::LEVEL_DEBUG, 2, cStringUtilities::MakeFormatted("Allocating Memory. File Size : %u KB. Currently using %u KB (%0.2f MB) out of %u MB in cache", iSize/KILOBYTE, m_iTotalMemoryAllocated/KILOBYTE, (float)m_iTotalMemoryAllocated/MEGABYTE, m_iCacheSize/MEGABYTE));
	}
	return pBuffer;
}

// ********************************************************************************************************************
void cResCache::FreeOneResource()
{
	auto itr = m_lru.end();

	itr--;
	shared_ptr<IResHandle> handle = *itr;
	m_lru.pop_back();
	m_Resources.erase(handle->GetResource()->VGetFileName());
	SP_LOG_CUSTOM(AssertLevels::LEVEL_DEBUG, 3, "Removed file from cache")(handle->GetResource()->VGetFileName());
}

// ********************************************************************************************************************
void cResCache::MemoryHasBeenFreed(unsigned int iSize)
{
	m_iTotalMemoryAllocated -= iSize;
	SP_LOG(2, cStringUtilities::MakeFormatted("Freeing Memory. File Size : %u KB. Currently using %u KB (%0.2f MB) out of %u MB in cache", iSize/KILOBYTE, m_iTotalMemoryAllocated/KILOBYTE, (float)m_iTotalMemoryAllocated/MEGABYTE, m_iCacheSize/MEGABYTE));
}

// ********************************************************************************************************************
IResCache * IResCache::CreateResourceCache(const int SizeInMB,
	const cString & FileName, const bool UseDevelopmentDirectory)
{
	IResourceFile * pResFile = NULL;
	if(UseDevelopmentDirectory)
	{
		pResFile = DEBUG_NEW cDevelopmentResourceZipFile(FileName);
	}
	else
	{
		pResFile = DEBUG_NEW cResourceZipFile(FileName);
	}

	cResCache * pResCache = DEBUG_NEW cResCache(SizeInMB, pResFile);
	return pResCache;
}

// ********************************************************************************************************************
cResourceZipFile::cResourceZipFile(const Base::cString & resFileName) 
	: m_pZipFile(NULL)
	, m_strResFileName(resFileName) 
{ 
}

// ********************************************************************************************************************
cResourceZipFile::~cResourceZipFile()
{
	SafeDelete(&m_pZipFile);
}

// ********************************************************************************************************************
void cResourceZipFile::Open()
{
	m_pZipFile = IZipFile::CreateZipFile();
	if(m_pZipFile)
	{
		m_pZipFile->Init(m_strResFileName);
	}
}

// ********************************************************************************************************************
int cResourceZipFile::GetResourceSize(const IResource &r)
{
	int iSize = 0;
	tOptional<int> resNum = m_pZipFile->Find(r.VGetFileName());
	if(resNum.IsValid())
	{
		iSize = m_pZipFile->GetFileLen(resNum.GetValue());
	}
	return iSize;
}

// ********************************************************************************************************************
void cResourceZipFile::GetResource(const IResource &r, char * pBuffer)
{
	int iSize = 0;
	tOptional<int> resNum = m_pZipFile->Find(r.VGetFileName());
	if(resNum.IsValid())
	{
		iSize = m_pZipFile->GetFileLen(resNum.GetValue());
		m_pZipFile->ReadFile(resNum.GetValue(), pBuffer);
	}
}

// ********************************************************************************************************************
cDevelopmentResourceZipFile::cDevelopmentResourceZipFile(const cString & resFileName) 
	: cResourceZipFile(resFileName)
{ 
	m_AssetsDir = resFileName;
}

// ********************************************************************************************************************
cDevelopmentResourceZipFile::~cDevelopmentResourceZipFile()
{
}

// ********************************************************************************************************************
void cDevelopmentResourceZipFile::Open()
{
	ReadAssetsDirectory("*");
}

// ********************************************************************************************************************
int cDevelopmentResourceZipFile::GetResourceSize(const IResource &r)
{
	int Size = 0;

	tOptional<int> num = Find(r.VGetFileName().GetData());
	if (num.IsValid())
		Size = m_AssetFileInfo[num.GetValue()].nFileSizeLow;
	return Size;
}

// ********************************************************************************************************************
void cDevelopmentResourceZipFile::GetResource(const IResource &r, char * pBuffer)
{
	int Size = 0;
	tOptional<int> num = Find(r.VGetFileName().GetData());
	if (num.IsValid())
	{
		Size = m_AssetFileInfo[num.GetValue()].nFileSizeLow;
		cString fullFileSpec = m_AssetsDir + r.VGetFileName(); 
		IFileIO * pFile = IFileIO::CreateFileIO();
		pFile->VOpenFile(fullFileSpec, std::ios::in | std::ios::binary);
		pFile->VRead(pBuffer, pFile->VGetFileSize());
		pFile->VCloseFile();
		SafeDelete(&pFile);
	}
}

// ********************************************************************************************************************
bool cDevelopmentResourceZipFile::ReadAssetsDirectory(const cString & FileSpec)
{
	HANDLE fileHandle;
	WIN32_FIND_DATA findData;

	// get first file
	cString PathSpec = m_AssetsDir + FileSpec;
	fileHandle = FindFirstFile(PathSpec.GetData(), &findData);
	if(fileHandle != INVALID_HANDLE_VALUE)
	{
		// loop on all remeaining entries in dir
		while(FindNextFile( fileHandle,&findData))
		{
			if (findData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN)
				continue;

			cString fileName(findData.cFileName); 
			if( findData.dwFileAttributes &FILE_ATTRIBUTE_DIRECTORY )
			{
				if (fileName == ".." || fileName == ".")
				{
					continue;
				}
				else
				{
					fileName = FileSpec.GetSubString(0, FileSpec.GetLength() - 2) + fileName + "\\*";
					ReadAssetsDirectory(fileName);
				}
			}
			else
			{
				fileName = FileSpec.GetSubString(0, FileSpec.GetLength() - 2) + fileName;
				cString lower = cStringUtilities::GetInLowerCase(fileName);
				m_DirectoryContentsMap[lower] = m_AssetFileInfo.size();
				m_AssetFileInfo.push_back(findData);
			} 
		}
	} 

	FindClose(fileHandle);
	return true;
}

// ********************************************************************************************************************
tOptional<int> cDevelopmentResourceZipFile::Find(const cString & Name)
{
	tOptional<int> val;

	cString lowerCase = cStringUtilities::GetInLowerCase(Name);
	auto iter = m_DirectoryContentsMap.find(lowerCase);
	if (iter == m_DirectoryContentsMap.end())
	{
		val.clear();
	}
	else
	{
		val = iter->second;
	}
	return val;
}
