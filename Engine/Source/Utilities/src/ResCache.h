// *****************************************************************************
//  ResCache   version:  1.0   Ankur Sheel  date: 2011/04/01
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef ResCache_h__
#define ResCache_h__

#include "ResCache.hxx"
#include "ZipFile.hxx"

namespace Base
{
	class cString;
}

namespace Utilities
{
	//LRU
	typedef std::list<shared_ptr <IResHandle> > ResHandleList;
	typedef std::map<Base::cString, shared_ptr <IResHandle> > ResHandleMap;

	class cResCache
		: public IResCache
	{
	public:
		cResCache(unsigned int iCacheSizeInMB, const IResourceFile * pResFile);
		~cResCache();
		void Init();
		shared_ptr<IResHandle> GetHandle(IResource & r);
		void Flush();

	protected:
		shared_ptr<IResHandle> Find(const IResource & r);
		const void Update(shared_ptr<IResHandle> handle);
		shared_ptr<IResHandle> Load(IResource & r) ; 
		void Free(shared_ptr<IResHandle> handle);
		bool MakeRoom(unsigned int iSize);
		char * Allocate(unsigned int iSize);
		void FreeOneResource();
		void MemoryHasBeenFreed(unsigned int iSize);

	protected:
		ResHandleList m_lru;
		ResHandleMap  m_Resources;
		IResourceFile * m_pFile;
		unsigned int m_iCacheSize;
		unsigned int m_iTotalMemoryAllocated;

	private:
		friend class cResHandle;
	};

	class IZipFile;

	class cResourceZipFile : public IResourceFile
	{
	public:
		cResourceZipFile(const Base::cString & resFileName);
		virtual ~cResourceZipFile();

		virtual void Open() OVERRIDE;
		virtual int GetResourceSize(const IResource &r);
		virtual void GetResource(const IResource &r, char *buffer);

	private:
		IZipFile *	m_pZipFile;
		Base::cString m_strResFileName;
	};

	class cDevelopmentResourceZipFile : public cResourceZipFile
	{
	public:
		cDevelopmentResourceZipFile(const Base::cString & resFileName);
		virtual ~cDevelopmentResourceZipFile();

		virtual void  Open() OVERRIDE;
		virtual int GetResourceSize(const IResource &r);
		virtual void GetResource(const IResource &r, char * pBuffer);

	private:
		bool ReadAssetsDirectory(const Base::cString & FileSpec);
		Base::tOptional<int> Find(const Base::cString & Name);

	private:
		Base::cString					m_AssetsDir;
		IZipFile::ZipContentsMap		m_DirectoryContentsMap;
		std::vector<WIN32_FIND_DATA>	m_AssetFileInfo;
	};
}
#endif // ResCache_h__