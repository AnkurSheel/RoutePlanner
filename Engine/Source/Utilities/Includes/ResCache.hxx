// *****************************************************************************
//  ResCache   version:  1.0   Ankur Sheel  date: 2011/04/01
// *****************************************************************************
//  purpose:	
// *****************************************************************************
#ifndef ResCache_hxx__
#define ResCache_hxx__

#include "UtilitiesDefines.h"

namespace Base
{
	class cString;
}

namespace Utilities
{
	class IResCache;
	class IResHandle;

	class IResource
	{
	public:
		virtual ~IResource() {}
		virtual Base::cString VGetFileName() const = 0;
		virtual IResHandle * VCreateHandle(const char * pBuffer, unsigned int uiSize, IResCache * pResCache) = 0;
		UTILITIES_API static IResource * CreateResource(const Base::cString & strFileName);
	};

	class IResourceFile
	{
	public:
		virtual ~IResourceFile() {}
		virtual void Open() = 0;
		virtual int GetResourceSize(const IResource &r) = 0;
		virtual void GetResource(const IResource &r, char *buffer) = 0;
	};

	class IResHandle
	{
	public:
		virtual ~IResHandle() {}
		UTILITIES_API virtual unsigned int GetSize() const = 0;
		UTILITIES_API virtual char * GetBuffer() const = 0;
		virtual void Load(IResourceFile * pFile) = 0;
		virtual const IResource * GetResource() const = 0;
	};

	class IResCache
	{
	public:
		UTILITIES_API virtual ~IResCache() {}
		UTILITIES_API virtual void Init() = 0;
		UTILITIES_API virtual shared_ptr<IResHandle> GetHandle(IResource & r) = 0;
		virtual void MemoryHasBeenFreed(unsigned int iSize) = 0;
		UTILITIES_API static IResCache * CreateResourceCache(const int SizeInMB,
			const Base::cString & FileName, const bool UseDevelopmentDirectory);
	};
}
#endif // ResCache_hxx__