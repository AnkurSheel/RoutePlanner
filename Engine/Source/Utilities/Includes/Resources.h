// *****************************************************************************
//  Resource   version:  1.0   Ankur Sheel  date: 2012/12/29
//  ----------------------------------------------------------------------------
//  
//  ----------------------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// *****************************************************************************
// 
// *****************************************************************************
#include "ResCache.hxx"

namespace Utilities
{
	class cResHandle;
	class cResCache;

	class cResource 
		: public IResource
	{
	public:
		UTILITIES_API cResource(const Base::cString & strFileName);
		IResHandle * VCreateHandle(const char * pBuffer, unsigned int size, IResCache * pResCache);
		UTILITIES_API Base::cString VGetFileName() const;

	private:
		Base::cString m_strFileName;
	};

	class cResHandle
		: public IResHandle
	{
	public:
		UTILITIES_API cResHandle(cResource & resource, char * pBuffer,
			unsigned int iSize, IResCache * pResCache);
		UTILITIES_API virtual ~cResHandle();
		UTILITIES_API void Load(IResourceFile * pFile);
		UTILITIES_API unsigned int GetSize() const;
		UTILITIES_API char * GetBuffer() const;
		UTILITIES_API const IResource * GetResource() const;

	protected:
		cResource 		m_Resource;
		char *			m_pBuffer;
		unsigned int	m_iBufferSize;
		IResCache *		m_pResCache;

	private:
		friend class cResCache;
	};
};