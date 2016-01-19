// ***************************************************************
//  ZipFile   version:  1.0   Ankur Sheel  date: 2011/04/12
//  -------------------------------------------------------------
//  
//  -------------------------------------------------------------
//  Copyright (C) 2008 - All Rights Reserved
// ***************************************************************
// 
// ***************************************************************
#ifndef ZipFile_h__
#define ZipFile_h__

#define ZLIB_WINAPI

#include "ZipFile.hxx"

namespace Base
{
	class cString;
	class IFileIO;
	template<class T>
	class tOptional;
}

namespace Utilities
{
	class cZipFile
	: public IZipFile
	{
	public:
		cZipFile();
		~cZipFile();

		void Init(const Base::cString & resFileName);
		void End();

		int GetNumFiles() const;
		Base::cString GetFilename(int i) const;
		int GetFileLen(int i) const;
		void ReadFile(int i, void *pBuf);

		// --------------------------------------------------------------------------
		// Function:      ReadLargeFile
		// Purpose:       Uncompress a complete file with callbacks.
		// Parameters:    The file index and the pre-allocated buffer
		// --------------------------------------------------------------------------
		bool ReadLargeFile(int i, void *pBuf, void (*callback)(int, bool &));

		Base::tOptional<int> Find(const Base::cString & strPath) const;

	private:

		struct TZipDirHeader;
		struct TZipDirFileHeader;
		struct TZipLocalHeader;

		char * m_pDirData;	// Raw data buffer.
		int  m_nEntries;	// Number of entries.
		const TZipDirFileHeader **m_papDir; // Pointers to the dir entries in pDirData.
		ZipContentsMap m_ZipContentsMap;
		Base::IFileIO * m_pFile;
	};
#include "Zipfile.inl"
}

#endif // ZipFile_h__
