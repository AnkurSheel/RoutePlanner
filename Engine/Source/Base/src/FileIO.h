//  *******************************************************************************************************************
//  FileIO   version:  1.0   Ankur Sheel  date: 2014/10/30
//  *******************************************************************************************************************
// 
//  *******************************************************************************************************************
#ifndef __FILEIO_H__
#define __FILEIO_H__

#include "FileIO.hxx"
#include <fstream>

namespace Base
{
	class cString;
}

namespace Base
{
	class cFileIO
	: public IFileIO
	{
	public:
		cFileIO();
		~cFileIO();
		bool VOpenFile(const cString & fileName, const std::ios_base::openmode mode);
		void VCloseFile();
		bool VWriteLine(const cString & line);
		virtual bool VWrite(const char * pBuffer, unsigned long size);
		bool VReadAll(const char * pBuffer);
		bool VRead(char * const pBuffer, unsigned long size);
		cString VReadLine();
		void VFlush();
		const cString & VGetFileName() { return m_FileName; }
		bool VIsEOF() const { return m_FileStream.eof(); }
		unsigned long VGetFileSize() const  { return m_FileSize; }
		unsigned long VGetCurrentInputPosition();
		void VSetCurrentInputPosition(const int relativePosition, std::ios_base::seekdir dir);

	protected:
		std::fstream	m_FileStream;
		cString	m_FileName;
		unsigned long	m_FileSize;
	};
} 
#endif  // __FILEIO_H__
