#include "stdafx.h"
#include "FileIO.h"
#include <errno.h>

using namespace Base;
using namespace std;

//  *******************************************************************************************************************
cFileIO::cFileIO()
: m_FileSize(0)
{
}

//  *******************************************************************************************************************
cFileIO::~cFileIO()
{
	VCloseFile();
}

//  *******************************************************************************************************************
bool cFileIO::VOpenFile(const cString & fileName, const std::ios_base::openmode mode)
{
	if(m_FileStream.is_open())
	{
		VCloseFile();
	}

	if (fileName.IsEmpty())
	{
		SP_ASSERT_WARNING(false).SetCustomMessage("FileName is empty");
		return false;
	}

	m_FileName = fileName;
	m_FileStream.open(m_FileName.GetData(), mode);

	SP_ASSERT(m_FileStream.good()).SetCustomMessage("Could not open file " + m_FileName + " : " + strerror(errno));
	if (!m_FileStream.good())
	{
		return false;
	}
	SP_LOG(2, "Opened file: " + m_FileName);
	if (mode != ios_base::out)
	{
		m_FileStream.seekg(0, std::ios::end);
		m_FileSize = static_cast<unsigned long>(m_FileStream.tellg());
		m_FileStream.seekg(0, std::ios::beg);
	}
	SP_LOG(3, "Size of File " + m_FileName + cStringUtilities::MakeFormatted(" : %d bytes", m_FileSize));
	return true;
}

//  *******************************************************************************************************************
void cFileIO::VCloseFile()
{
	if(m_FileStream.is_open())
	{
		m_FileStream.close();
	}
}

//  *******************************************************************************************************************
bool cFileIO::VWriteLine(const cString & line)
{
	if (m_FileStream.good())
	{
		m_FileStream << line.GetData();
	}
	if(m_FileStream.good())
	{
		m_FileSize += line.GetLength();
		return true;
	}
	return false;
}

//  ********************************************************************************************************************
bool cFileIO::VWrite(const char * pBuffer, unsigned long size)
{
	if(m_FileStream.good())
	{
		m_FileStream.write(pBuffer, size);
	}
	if (m_FileStream.good())
	{
		m_FileSize += size; 
		return true;
	}
	return false;
}

//  ********************************************************************************************************************
void cFileIO::VFlush()
{
	SP_ASSERT_ERROR(m_FileStream.good()).SetCustomMessage("File not in good state : " + m_FileName);
	if (m_FileStream.good())
	{
		m_FileStream.flush();
	}
}

//  ********************************************************************************************************************
bool cFileIO::VRead(char * const pBuffer, unsigned long size)
{
	SP_ASSERT_ERROR(m_FileStream.good()).SetCustomMessage("File not in good state : " + m_FileName);

	if(!m_FileStream.good())
	{
		return false;
	}

	memset(pBuffer, 0, size);
	m_FileStream.read((char *)(pBuffer), size);
	if (m_FileStream.fail() && m_FileStream.eof())
	{
		return true;
	}
	SP_ASSERT_ERROR(m_FileStream.good()).SetCustomMessage("Error in reading file: " + m_FileName);

	return m_FileStream.good();
}

//  ********************************************************************************************************************
cString cFileIO::VReadLine()
{
	std::string str;
	std::getline(m_FileStream, str);
	return str;
}

//  ********************************************************************************************************************
unsigned long cFileIO::VGetCurrentInputPosition()
{
	return static_cast<long>(m_FileStream.tellg());
}

//  ********************************************************************************************************************
void Base::cFileIO::VSetCurrentInputPosition(const int relativePosition, std::ios_base::seekdir dir)
{
	m_FileStream.seekg(relativePosition, dir);
}

//  *******************************************************************************************************************
IFileIO * IFileIO::CreateFileIO()
{
	IFileIO * pFile = DEBUG_NEW cFileIO();
	return pFile;
}
