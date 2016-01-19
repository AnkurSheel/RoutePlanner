#include "stdafx.h"
#include "FileIO.hxx"


using namespace Base;
using namespace std;

class FileIOTest : public ::testing::Test
{
protected:

	void SetUp()
	{
	}

	void TearDown()
	{
	}
};

TEST_F(FileIOTest, CreateFileIO)
{
	unique_ptr<IFileIO> pFile(IFileIO::CreateFileIO());
	EXPECT_TRUE(pFile != NULL);
}

TEST_F(FileIOTest, OpenSuccess)
{
	unique_ptr<IFileIO> pFile(IFileIO::CreateFileIO());
	pFile->VOpenFile("test_ascii.txt", ios::out);
	EXPECT_STREQ("test_ascii.txt", pFile->VGetFileName().GetData());
}

TEST_F(FileIOTest, OpenFail)
{
	unique_ptr<IFileIO> pFile(IFileIO::CreateFileIO());
	bool result = pFile->VOpenFile("test_ascii_not_exist.txt", ios::in); 
	EXPECT_FALSE(result);
}

TEST_F(FileIOTest, WriteLineFailOnFileModeInput)
{
	unique_ptr<IFileIO> pAsciiFile(IFileIO::CreateFileIO());
	pAsciiFile->VOpenFile("test_ascii.txt", ios::in);
	bool result = pAsciiFile->VWriteLine("Testing WriteLineFailOnFileModeInput.\n");
	pAsciiFile->VCloseFile();
	EXPECT_FALSE(result);
}

TEST_F(FileIOTest, ReadLineFailOnFileModeOutput)
{
	unique_ptr<IFileIO> pAsciiFile(IFileIO::CreateFileIO());
	pAsciiFile->VOpenFile("test_ascii.txt", ios::out);
	bool result = pAsciiFile->VWriteLine("Testing ReadLineFailOnFileModeOutput\n");
	pAsciiFile->VCloseFile();

	pAsciiFile->VOpenFile("test_ascii.txt", ios::app);
	EXPECT_STREQ("", pAsciiFile->VReadLine().GetData());
	pAsciiFile->VCloseFile();
}

TEST_F(FileIOTest, WriteLineAndReadLineSuccess)
{
	unique_ptr<IFileIO> pAsciiFile(IFileIO::CreateFileIO());
	pAsciiFile->VOpenFile("test_ascii.txt", ios::out);
	bool result = pAsciiFile->VWriteLine("Testing WriteLineAndReadLineSuccess\n");
	pAsciiFile->VCloseFile();

	EXPECT_TRUE(result);

	pAsciiFile->VOpenFile("test_ascii.txt", ios::in);
	EXPECT_STREQ("Testing WriteLineAndReadLineSuccess", pAsciiFile->VReadLine().GetData());
	pAsciiFile->VCloseFile();
	EXPECT_LT(unsigned long(0), pAsciiFile->VGetFileSize());
}

TEST_F(FileIOTest, WriteFailOnFileModeInput)
{
	unique_ptr<IFileIO> pAsciiFile(IFileIO::CreateFileIO());
	pAsciiFile->VOpenFile("test_ascii.txt", ios::in);
	cString testString = "Testing WriteLineAndReadLineSuccess\n";
	bool result = pAsciiFile->VWrite(testString.GetData(), testString.GetLength());
	pAsciiFile->VCloseFile();
	EXPECT_FALSE(result);
}

TEST_F(FileIOTest, ReadAllFailOnFileModeOutput)
{
	unique_ptr<IFileIO> pAsciiFile(IFileIO::CreateFileIO());
	pAsciiFile->VOpenFile("test_ascii.txt", ios::out);
	bool result = pAsciiFile->VWriteLine("Testing ReadAllFailOnFileModeOutput\n");
	pAsciiFile->VCloseFile();

	pAsciiFile->VOpenFile("test_ascii.txt", ios::app);
	EXPECT_STREQ("", pAsciiFile->VReadLine().GetData());
	pAsciiFile->VCloseFile();
}

TEST_F(FileIOTest, WriteAndReadAllAsciiSuccess)
{
	unique_ptr<IFileIO> pAsciiFile(IFileIO::CreateFileIO());

	pAsciiFile->VOpenFile("test_ascii.txt", ios::out);
	cString testString = "Testing WriteAndReadAllAsciiSuccess\n";
	bool result = pAsciiFile->VWrite(testString.GetData(), testString.GetLength());
	pAsciiFile->VCloseFile();
	EXPECT_TRUE(result);

	pAsciiFile->VOpenFile("test_ascii.txt", ios::in);
	char * pBuffer = new char[pAsciiFile->VGetFileSize()];
	result = pAsciiFile->VRead(pBuffer, pAsciiFile->VGetFileSize());
	pAsciiFile->VCloseFile();
	EXPECT_LT(unsigned long(0), pAsciiFile->VGetFileSize());
	EXPECT_TRUE(result);
	SafeDeleteArray(&pBuffer);
}

TEST_F(FileIOTest, WriteAndReadSuccessBinary)
{
	struct rec
	{
		int x, y, z;
	};

	unique_ptr<IFileIO> pBinaryFile(IFileIO::CreateFileIO());
	pBinaryFile->VOpenFile("test_binary.bin", ios::out|ios::binary);

	struct rec my_record;
	my_record.x= 1;
	my_record.y= 2;
	my_record.z= 3;
	bool result = pBinaryFile->VWrite(reinterpret_cast<const char *>(&my_record), sizeof(struct rec));

	EXPECT_TRUE(result);
	pBinaryFile->VCloseFile();

	pBinaryFile->VOpenFile("test_binary.bin", ios::in|ios::binary);
	char * pBuffer = new char[sizeof(struct rec)];
	result = pBinaryFile->VRead(pBuffer, sizeof(struct rec));
	const struct rec * pRec = reinterpret_cast<const struct rec *>(pBuffer);
	pBinaryFile->VCloseFile();

	EXPECT_TRUE(result);
	EXPECT_LT(unsigned long(0), pBinaryFile->VGetFileSize());
	EXPECT_EQ(1, pRec->x);
	EXPECT_EQ(2, pRec->y);
	EXPECT_EQ(3, pRec->z);
	SafeDeleteArray(&pBuffer);
}

TEST_F(FileIOTest, WriteBinaryOpenAscii)
{
	struct rec
	{
		int x, y, z;
	};

	unique_ptr<IFileIO> pBinaryFile(IFileIO::CreateFileIO());
	pBinaryFile->VOpenFile("test_binary.bin", ios::out|ios::binary);

	struct rec my_record;
	my_record.x= 1;
	my_record.y= 2;
	my_record.z= 3;
	bool result = pBinaryFile->VWrite(reinterpret_cast<const char *>(&my_record), sizeof(struct rec));

	EXPECT_TRUE(result);
	pBinaryFile->VCloseFile();

	pBinaryFile->VOpenFile("test_binary.bin", ios::in);
	char * pBuffer = new char[pBinaryFile->VGetFileSize()];
	result = pBinaryFile->VRead(pBuffer, pBinaryFile->VGetFileSize());
	const struct rec * pRec = reinterpret_cast<const struct rec *>(pBuffer);
	pBinaryFile->VCloseFile();

	EXPECT_TRUE(result);
	EXPECT_LT(unsigned long(0), pBinaryFile->VGetFileSize());
	EXPECT_EQ(1, pRec->x);
	EXPECT_EQ(2, pRec->y);
	EXPECT_EQ(3, pRec->z);
	SafeDeleteArray(&pBuffer);
}

TEST_F(FileIOTest, WriteAsciiReadBinary)
{
	unique_ptr<IFileIO> pAsciiFile(IFileIO::CreateFileIO());

	pAsciiFile->VOpenFile("test_ascii.txt", ios::out);
	cString testString = "Testing WriteAndReadAllAsciiSuccess\n";
	bool result = pAsciiFile->VWrite(testString.GetData(), testString.GetLength());
	pAsciiFile->VCloseFile();
	EXPECT_TRUE(result);

	pAsciiFile->VOpenFile("test_ascii.txt", ios::in|ios::binary);
	char * pBuffer = new char[pAsciiFile->VGetFileSize()];
	result = pAsciiFile->VRead(pBuffer, pAsciiFile->VGetFileSize());
	pAsciiFile->VCloseFile();
	EXPECT_LT(unsigned long(0), pAsciiFile->VGetFileSize());
	EXPECT_TRUE(result);
	EXPECT_STRNE("Testing WriteAndReadAllAsciiSuccess\n", pBuffer);
	SafeDeleteArray(&pBuffer);
}

TEST_F(FileIOTest, WriteAndReadMoreThanFileSize)
{
	struct rec
	{
		int x, y, z;
	};

	unique_ptr<IFileIO> pBinaryFile(IFileIO::CreateFileIO());
	pBinaryFile->VOpenFile("test_binary.bin", ios::out|ios::binary);

	struct rec my_record;
	my_record.x= 1;
	my_record.y= 2;
	my_record.z= 3;
	bool result = pBinaryFile->VWrite(reinterpret_cast<const char *>(&my_record), sizeof(struct rec));

	EXPECT_TRUE(result);
	pBinaryFile->VCloseFile();

	pBinaryFile->VOpenFile("test_binary.bin", ios::in|ios::binary);
	char * pBuffer = new char[100];
	result = pBinaryFile->VRead(pBuffer, 100);
	const struct rec * pRec = reinterpret_cast<const struct rec *>(pBuffer);
	pBinaryFile->VCloseFile();

	EXPECT_TRUE(result);
	EXPECT_LT(unsigned long(0), pBinaryFile->VGetFileSize());
	EXPECT_EQ(1, pRec->x);
	EXPECT_EQ(2, pRec->y);
	EXPECT_EQ(3, pRec->z);
	EXPECT_TRUE(pBinaryFile->VIsEOF());
	SafeDeleteArray(&pBuffer);
}

TEST_F(FileIOTest, WriteAndReadLessThanFileSize)
{
	struct rec
	{
		int x, y, z;
	};

	unique_ptr<IFileIO> pBinaryFile(IFileIO::CreateFileIO());
	pBinaryFile->VOpenFile("test_binary.bin", ios::out|ios::binary);

	struct rec my_record;
	my_record.x= 1;
	my_record.y= 2;
	my_record.z= 3;
	bool result = pBinaryFile->VWrite(reinterpret_cast<const char *>(&my_record), sizeof(struct rec));

	EXPECT_TRUE(result);
	pBinaryFile->VCloseFile();

	pBinaryFile->VOpenFile("test_binary.bin", ios::in|ios::binary);
	char * pBuffer = new char[sizeof(int)];
	result = pBinaryFile->VRead(pBuffer, sizeof(int));
	const int * pX =reinterpret_cast<const int *>(pBuffer);
	pBinaryFile->VCloseFile();

	EXPECT_TRUE(result);
	EXPECT_LT(unsigned long(0), pBinaryFile->VGetFileSize());
	EXPECT_EQ(1, *pX);
	EXPECT_FALSE(pBinaryFile->VIsEOF());
	SafeDeleteArray(&pBuffer);
}