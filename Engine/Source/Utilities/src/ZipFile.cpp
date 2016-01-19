//  *******************************************************************************************************************
//  ZipFile   version:  1.0   Ankur Sheel  date: 2011/03/12
//  *******************************************************************************************************************
//  Taken from Game Coding Complete
//  *******************************************************************************************************************
#include "stdafx.h"
#include "ZipFile.h"
#include "zlib.h"
#include "FileIO.hxx"

using namespace Base;
using namespace Utilities;

typedef unsigned long dword;
typedef unsigned short word;
typedef unsigned char byte;

// --------------------------------------------------------------------------
// ZIP file structures. Note these have to be packed.
// --------------------------------------------------------------------------

#pragma pack(1)
//  *******************************************************************************************************************
struct cZipFile::TZipLocalHeader
{
	enum
	{
		SIGNATURE = 0x04034b50,
	};
	dword   sig;
	word    version;
	word    flag;
	word    compression;      // Z_NO_COMPRESSION or Z_DEFLATED
	word    modTime;
	word    modDate;
	dword   crc32;
	dword   cSize;
	dword   ucSize;
	word    fnameLen;         // Filename string follows header.
	word    xtraLen;          // Extra field follows filename.
};

//  *******************************************************************************************************************
struct cZipFile::TZipDirHeader
{
	enum
	{
		SIGNATURE = 0x06054b50
	};
	dword   sig;
	word    nDisk;
	word    nStartDisk;
	word    nDirEntries;
	word    totalDirEntries;
	dword   dirSize;
	dword   dirOffset;
	word    cmntLen;
};

//  *******************************************************************************************************************
struct cZipFile::TZipDirFileHeader
{
	enum
	{
		SIGNATURE   = 0x02014b50
	};
	dword   sig;
	word    verMade;
	word    verNeeded;
	word    flag;
	word    compression;      // COMP_xxxx
	word    modTime;
	word    modDate;
	dword   crc32;
	dword   cSize;            // Compressed size
	dword   ucSize;           // Uncompressed size
	word    fnameLen;         // Filename string follows header.
	word    xtraLen;          // Extra field follows filename.
	word    cmntLen;          // Comment field follows extra field.
	word    diskStart;
	word    intAttr;
	dword   extAttr;
	dword   hdrOffset;

	char *GetName   () const { return (char *)(this + 1);   }
	char *GetExtra  () const { return GetName() + fnameLen; }
	char *GetComment() const { return GetExtra() + xtraLen; }
};

#pragma pack()

//  *******************************************************************************************************************
cZipFile::cZipFile()
: m_nEntries(0)
, m_pDirData(NULL)
, m_pFile(NULL)
{ 
}

//  *******************************************************************************************************************
cZipFile::~cZipFile() 
{ 
	End(); 
}

//  *******************************************************************************************************************
void cZipFile::Init(const Base::cString & resFileName)
{
	End();

	m_pFile = IFileIO::CreateFileIO();
	bool success = m_pFile->VOpenFile(resFileName, std::ios_base::in | std::ios_base::binary);
	SP_ASSERT_ERROR(success)(resFileName).SetCustomMessage("Could not open zipfile");

	// Assuming no extra comment at the end, read the whole end record.
	TZipDirHeader dh;
	memset(&dh, 0, sizeof(dh));
	m_pFile->VSetCurrentInputPosition(-(int)sizeof(dh), std::ios_base::end);
	long dhOffset = m_pFile->VGetCurrentInputPosition();
	m_pFile->VRead(reinterpret_cast<char * const>(&dh), sizeof(dh));

	SP_ASSERT_ERROR(dh.sig == TZipDirHeader::SIGNATURE)(dh.sig)(m_pFile->VGetFileName()).SetCustomMessage("Dir Header Signature did not match");

	SP_LOG(3, m_pFile->VGetFileName() + cStringUtilities::MakeFormatted("Dir Size : %d", dh.dirSize));
	SP_LOG(3, cStringUtilities::MakeFormatted("No. of Entries : %d in file ", dh.nDirEntries) + m_pFile->VGetFileName());

	// Allocate the data buffer, and read the whole thing.
	m_pDirData = DEBUG_NEW char[dh.dirSize + dh.nDirEntries*sizeof(*m_papDir)];

	SP_ASSERT_ERROR(m_pDirData != NULL).SetCustomMessage("Could not allocate data buffer");

	memset(m_pDirData, 0, dh.dirSize + dh.nDirEntries*sizeof(*m_papDir));

	//Set the file position to the beginning of the array of TZipDirFileHeader structures
	m_pFile->VSetCurrentInputPosition(dhOffset - dh.dirSize, std::ios_base::beg);
	m_pFile->VRead(reinterpret_cast<char * const>(m_pDirData), dh.dirSize);

	// Now process each entry.
	char *pfh = m_pDirData;
	m_papDir = (const TZipDirFileHeader **)(m_pDirData + dh.dirSize);

	for (int i = 0; i < dh.nDirEntries; i++)
	{
		TZipDirFileHeader &fh = *(TZipDirFileHeader*)pfh;

		// Store the address of nth file for quicker access.
		m_papDir[i] = &fh;

		SP_ASSERT_ERROR(fh.sig == TZipDirFileHeader::SIGNATURE)(fh.sig)(m_pFile->VGetFileName()).SetCustomMessage("Dir File Header Signature did not match for file");
		pfh += sizeof(fh);

		// Convert UNIX slashes to DOS backlashes.
		for (int j = 0; j < fh.fnameLen; j++)
		{
			if (pfh[j] == '/')
			{
				pfh[j] = '\\';
			}
		}

		char fileName[_MAX_PATH];
		memcpy(fileName, fh.GetName(), fh.fnameLen);
		fileName[fh.fnameLen]=0;
		_strlwr_s(fileName, _MAX_PATH);

		cString strPath(fileName);
		m_ZipContentsMap[strPath] = i;

		// Skip name, extra and comment fields.
		pfh += fh.fnameLen + fh.xtraLen + fh.cmntLen;
	}
	m_nEntries = dh.nDirEntries;
}

//  *******************************************************************************************************************
tOptional<int> cZipFile::Find(const Base::cString & strPath) const
{
	tOptional<int> val;

	char lwrPath[MAX_PATH_WIDTH];
	strcpy_s(lwrPath, MAX_PATH_WIDTH, strPath.GetData());
	_strlwr_s(lwrPath, MAX_PATH_WIDTH);
	auto iter = m_ZipContentsMap.find(lwrPath);
	if (iter == m_ZipContentsMap.end())
	val.clear();
	else
	val = (*iter).second;

	return val;
}

//  *******************************************************************************************************************
void cZipFile::End()
{
	SafeDelete(&m_pFile);
	m_ZipContentsMap.empty();
	SafeDeleteArray(&m_pDirData);
	m_nEntries = 0;
}

//  *******************************************************************************************************************
cString cZipFile::GetFilename(int i)  const
{
	SP_ASSERT_ERROR((i >=0 && i < m_nEntries))(i)(m_pFile->VGetFileName())(m_nEntries).SetCustomMessage("Passed Index is invalid");
	char szDest[MAX_FILENAME_WIDTH];
	memcpy(szDest, m_papDir[i]->GetName(), m_papDir[i]->fnameLen);
	szDest[m_papDir[i]->fnameLen] = '\0';
	return szDest;
}

//  *******************************************************************************************************************
int cZipFile::GetFileLen(int i) const
{
	SP_ASSERT_ERROR((i >=0 && i < m_nEntries))(i)(m_pFile->VGetFileName())(m_nEntries).SetCustomMessage("Passed Index is invalid");
	return m_papDir[i]->ucSize;
}

//  *******************************************************************************************************************
void cZipFile::ReadFile(int i, void *pBuf)
{
	SP_ASSERT_ERROR(pBuf != NULL)(pBuf).SetCustomMessage("Buffer should not be null");
	SP_ASSERT_ERROR((i >=0 && i < m_nEntries))(i)(m_pFile->VGetFileName())(m_nEntries).SetCustomMessage("Passed Index is invalid");

	// Go to the actual file and read the local header.
	m_pFile->VSetCurrentInputPosition(m_papDir[i]->hdrOffset, std::ios_base::beg);
	TZipLocalHeader h;

	memset(&h, 0, sizeof(h));
	m_pFile->VRead(reinterpret_cast<char * const>(&h), sizeof(h));
	SP_ASSERT_ERROR(h.sig == TZipLocalHeader::SIGNATURE)(h.sig)(m_pFile->VGetFileName()).SetCustomMessage("Corrupt ZipFile : Local Header Signature did not match");

	// Skip extra fields
	m_pFile->VSetCurrentInputPosition(h.fnameLen + h.xtraLen, std::ios_base::cur);

	if (h.compression == Z_NO_COMPRESSION)
	{
		SP_LOG(3, "No Compression for file " + GetFilename(i) + " in ZipFile: " + m_pFile->VGetFileName());
		// Simply read in raw stored data.
		m_pFile->VRead(reinterpret_cast<char * const>(pBuf), h.cSize);
		return;
	}

	SP_ASSERT_ERROR(h.compression == Z_DEFLATED)(GetFilename(i))(m_pFile->VGetFileName()).SetCustomMessage("Unknown Compression");

	// Alloc compressed data buffer and read the whole stream
	char *pcData = DEBUG_NEW char[h.cSize];
	SP_ASSERT_ERROR(pcData != NULL).SetCustomMessage("Could not allocate memory");

	memset(pcData, 0, h.cSize);
	m_pFile->VRead(reinterpret_cast<char * const>(pcData), h.cSize);

	// Setup the inflate stream.
	z_stream stream;
	int err;

	stream.next_in = (Bytef*)pcData;
	stream.avail_in = (uInt)h.cSize;
	stream.next_out = (Bytef*)pBuf;
	stream.avail_out = h.ucSize;
	stream.zalloc = Z_NULL;
	stream.zfree = Z_NULL;

	// Perform inflation. wbits < 0 indicates no zlib header inside the data.
	err = inflateInit2(&stream, -MAX_WBITS);
	if (err == Z_OK)
	{
		err = inflate(&stream, Z_FINISH);
		inflateEnd(&stream);
		if (err == Z_STREAM_END)
		err = Z_OK;
		inflateEnd(&stream);
	}
	SP_ASSERT_ERROR(err == Z_OK)(err).SetCustomMessage("Error while inflating stream");
	SafeDeleteArray(&pcData);
}

//  *******************************************************************************************************************
bool cZipFile::ReadLargeFile(int i, void *pBuf, void (*callback)(int, bool &))

{
	if (pBuf == NULL || i < 0 || i >= m_nEntries)
	return false;

	// Quick'n dirty read, the whole file at once.
	// Not good if the ZIP has huge files inside

	// Go to the actual file and read the local header.
	m_pFile->VSetCurrentInputPosition(m_papDir[i]->hdrOffset, std::ios_base::beg);
	TZipLocalHeader h;

	memset(&h, 0, sizeof(h));
	m_pFile->VRead(reinterpret_cast<char * const>(&h), sizeof(h));
	if (h.sig != TZipLocalHeader::SIGNATURE)
	return false;

	// Skip extra fields
	m_pFile->VSetCurrentInputPosition(h.fnameLen + h.xtraLen, std::ios_base::cur);

	if (h.compression == Z_NO_COMPRESSION)
	{
		// Simply read in raw stored data.
		m_pFile->VRead(reinterpret_cast<char * const>(pBuf), h.cSize);
		return true;
	}
	else if (h.compression != Z_DEFLATED)
	return false;

	// Alloc compressed data buffer and read the whole stream
	char *pcData = DEBUG_NEW char[h.cSize];
	if (!pcData)
	return false;

	memset(pcData, 0, h.cSize);
	m_pFile->VRead(reinterpret_cast<char * const>(pcData), h.cSize);

	bool ret = true;

	// Setup the inflate stream.
	z_stream stream;
	int err;

	stream.next_in = (Bytef*)pcData;
	stream.avail_in = (uInt)h.cSize;
	stream.next_out = (Bytef*)pBuf;
	stream.avail_out = (128 * 1024); //  read 128k at a time h.ucSize;
	stream.zalloc = Z_NULL;
	stream.zfree = Z_NULL;

	// Perform inflation. wbits < 0 indicates no zlib header inside the data.
	err = inflateInit2(&stream, -MAX_WBITS);
	if (err == Z_OK)
	{
		uInt count = 0;
		bool cancel = false;
		while (stream.total_in < (uInt)h.cSize && !cancel)
		{
			err = inflate(&stream, Z_SYNC_FLUSH);
			if (err == Z_STREAM_END)
			{
				err = Z_OK;
				break;
			}
			else if (err != Z_OK)
			{
				//assert(0 && "Something happened.");
				break;
			}

			stream.avail_out = (128 * 1024); 
			stream.next_out += stream.total_out;

			callback(count * 100 / h.cSize, cancel);
		}
		inflateEnd(&stream);
	}
	if (err != Z_OK)
	ret = false;

	SafeDeleteArray(&pcData);
	return ret;
}

//  *******************************************************************************************************************
IZipFile * IZipFile::CreateZipFile()
{
	IZipFile * pZipFile = DEBUG_NEW cZipFile();
	return pZipFile;
}
