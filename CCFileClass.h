#pragma once

#include <GeneralDefinitions.h>
#include <YRAllocator.h>
#include <YRPPCore.h>
#include <GenericList.h>

enum class FileAccessMode : unsigned int {
	None = 0,
	Read = 1,
	Write = 2,
	ReadWrite = Read | Write
};

MAKE_ENUM_FLAGS(FileAccessMode);

enum class FileSeekMode : unsigned int {
	Set = 0, // SEEK_SET
	Current = 1, // SEEK_CUR
	End = 2 // SEEK_END
};

//--------------------------------------------------------------------
//Abstract File class
//--------------------------------------------------------------------
class NOVTABLE FileClass
{
public:
	//Destructor
	virtual	~FileClass() RX;
	//FileClass
	virtual const char* GetFileName() const = 0;
	virtual const char* SetFileName(const char* pFileName) = 0;
	virtual BOOL CreateFile() = 0;
	virtual BOOL DeleteFile() = 0;
	virtual bool Exists(bool writeShared = false) = 0;
	virtual bool HasHandle() = 0;
	virtual bool Open(FileAccessMode access) = 0;
	virtual bool OpenEx(const char* pFileName, FileAccessMode access) = 0;
	virtual int ReadBytes(void* pBuffer, int nNumBytes) = 0; //Returns number of bytes read.
	virtual int Seek(int offset, FileSeekMode seek) = 0;
	virtual int GetFileSize() = 0;
	virtual int WriteBytes(void* pBuffer, int nNumBytes) = 0; //Returns number of bytes written.
	virtual void Close() = 0;
	virtual DWORD GetFileTime() JMP_THIS(0x65C5F0); //LoWORD = FatTime, HiWORD = FatDate
	virtual bool SetFileTime(DWORD FileTime) JMP_THIS(0x65C600);
	virtual void CDCheck(DWORD errorCode, bool bUnk, const char* pFilename) = 0;

	void* ReadWholeFile()
		{ JMP_THIS(0x4A3890); }

	template <typename T>
	bool Read(T& obj, int size = sizeof(T)) {
		return this->ReadBytes(&obj, size) == size;
	}

	template <typename T>
	bool Write(T& obj, int size = sizeof(T)) {
		return this->WriteBytes(&obj, size) == size;
	}

protected:
	explicit __forceinline FileClass(noinit_t)
	{ }

	//Properties

public:
	bool SkipCDCheck;
private:
	BYTE padding_5[3];
};

//--------------------------------------------------------------------
//Files in the game directory
//--------------------------------------------------------------------
class NOVTABLE RawFileClass : public FileClass
{
public:
	//Destructor
	virtual ~RawFileClass() RX;

	//FileClass
	virtual const char* GetFileName() const override JMP_THIS(0x401940);
	virtual const char* SetFileName(const char* pFileName) override JMP_THIS(0x65CAC0);
	virtual BOOL CreateFile() override JMP_THIS(0x65D150);
	virtual BOOL DeleteFile() override JMP_THIS(0x65D190);
	virtual bool Exists(bool writeShared = false) override JMP_THIS(0x65CBF0);
	virtual bool HasHandle() override JMP_THIS(0x65D420);
	virtual bool Open(FileAccessMode access) override JMP_THIS(0x65CB50);
	virtual bool OpenEx(const char* pFileName, FileAccessMode access) override JMP_THIS(0x65CB30);
	virtual int ReadBytes(void* pBuffer, int nNumBytes) override JMP_THIS(0x65CCE0);
	virtual int Seek(int offset, FileSeekMode seek) override JMP_THIS(0x65CF00);
	virtual int GetFileSize() override JMP_THIS(0x65D0D0);
	virtual int WriteBytes(void* pBuffer, int nNumBytes) override JMP_THIS(0x65CDD0);
	virtual void Close() override JMP_THIS(0x65CCA0);
	virtual DWORD GetFileTime() override JMP_THIS(0x65D1F0);
	virtual bool SetFileTime(DWORD FileTime) override JMP_THIS(0x65D240);
	virtual void CDCheck(DWORD errorCode, bool lUnk, const char* pFilename) override JMP_THIS(0x65CA70);

	void Bias(int offset = 0, int length = -1) { JMP_THIS(0x65D2B0); }

	//Constructor
	RawFileClass(const char* pFileName)
		: RawFileClass(noinit_t())
	{ JMP_THIS(0x65CA80); }

protected:
	explicit __forceinline RawFileClass(noinit_t)
		: FileClass(noinit_t())
	{ }

	//Properties

public:
	FileAccessMode FileAccess;
	int FilePointer;
	int FileSize;
	HANDLE Handle;
	const char* FileName;
	short unknown_short_1C;	//FatTime?
	short unknown_short_1E;	//FatDate?
	bool FileNameAllocated;
private:
	BYTE padding_21[3];
};

//--------------------------------------------------------------------
//Files that get buffered in some way?
//--------------------------------------------------------------------
class NOVTABLE BufferIOFileClass : public RawFileClass
{
public:
	//Destructor
	virtual ~BufferIOFileClass() RX;
	//FileClass
	virtual const char* SetFileName(const char* pFileName) override JMP_THIS(0x431E80);
	virtual bool Exists(bool writeShared = false) override JMP_THIS(0x431F10);
	virtual bool HasHandle() override JMP_THIS(0x431F30);
	virtual bool Open(FileAccessMode access) override JMP_THIS(0x431F70);
	virtual bool OpenEx(const char* pFileName, FileAccessMode access) override JMP_THIS(0x431F50);
	virtual int ReadBytes(void* pBuffer, int nNumBytes) override JMP_THIS(0x4322A0);
	virtual int Seek(int offset, FileSeekMode seek) override JMP_THIS(0x4324B0);
	virtual int GetFileSize() override JMP_THIS(0x4325A0);
	virtual int WriteBytes(void* pBuffer, int nNumBytes) override JMP_THIS(0x432050);
	virtual void Close() override JMP_THIS(0x4325C0);

	//Constructor
	BufferIOFileClass()
		: BufferIOFileClass(noinit_t())
	{ JMP_THIS(0x431B20); }

protected:
	explicit __forceinline BufferIOFileClass(noinit_t)
		: RawFileClass(noinit_t())
	{ }

	//Properties

public:
	bool unknown_bool_24;
	bool unknown_bool_25;
	bool unknown_bool_26;
	bool unknown_bool_27;
	bool unknown_bool_28;
	bool unknown_bool_29;
	DWORD unknown_2C;
	DWORD unknown_30;
	DWORD unknown_34;
	DWORD unknown_38;
	DWORD unknown_3C;
	DWORD unknown_40;
	int unknown_int_44;
	int unknown_int_48;
	DWORD unknown_4C;
	DWORD unknown_50;
};

//--------------------------------------------------------------------
//Files on a CD?
//--------------------------------------------------------------------
class NOVTABLE CDFileClass : public BufferIOFileClass
{
public:
	//Destructor
	virtual ~CDFileClass() RX;
	//FileClass
	virtual const char* SetFileName(const char* pFileName) override JMP_THIS(0x47AE10);
	virtual bool Open(FileAccessMode access) override JMP_THIS(0x47AAB0);
	virtual bool OpenEx(const char* pFileName, FileAccessMode access) override JMP_THIS(0x47AF10);
	
	//Constructor
	CDFileClass()
		: CDFileClass(noinit_t())
	{ JMP_THIS(0x47AA30); }

protected:
	explicit __forceinline CDFileClass(noinit_t)
		: BufferIOFileClass(noinit_t())
	{ }

	//Property

public:
	bool IsDisabled;
};

//--------------------------------------------------------------------
//Files in MIXes
//--------------------------------------------------------------------
class NOVTABLE CCFileClass : public CDFileClass
{
public:
	//Destructor
	virtual ~CCFileClass() RX;

	//FileClass
	virtual const char* SetFileName(const char* pFileName) override JMP_THIS(0x473FC0);
	virtual bool Exists(bool writeShared = false) override JMP_THIS(0x473C50);
	virtual bool HasHandle() override JMP_THIS(0x473CD0);
	virtual bool Open(FileAccessMode access) override JMP_THIS(0x473D10);
	virtual bool OpenEx(const char* pFileName, FileAccessMode access) override JMP_THIS(0x401980);
	virtual int ReadBytes(void* pBuffer, int nNumBytes) override JMP_THIS(0x473B10);
	virtual int Seek(int offset, FileSeekMode seek) override JMP_THIS(0x473BA0);
	virtual int GetFileSize() override JMP_THIS(0x473C00);
	virtual int WriteBytes(void* pBuffer, int nNumBytes) override JMP_THIS(0x473AE0);
	virtual void Close() override JMP_THIS(0x473CE0);
	virtual DWORD GetFileTime() override JMP_THIS(0x473E50);
	virtual bool SetFileTime(DWORD FileTime) override JMP_THIS(0x473F00);
	virtual void CDCheck(DWORD errorCode, bool lUnk, const char* pFilename) override JMP_THIS(0x473AB0);

	//Constructor
	CCFileClass(const char* pFileName)
		: CCFileClass(noinit_t())
	{ JMP_THIS(0x4739F0); }

protected:
	explicit __forceinline CCFileClass(noinit_t)
		: CDFileClass(noinit_t())
	{ }

	//Properties

public:
	MemoryBuffer Buffer;
	DWORD Position;
	DWORD Availablility;
};

//TO BE CREATED WHEN NEEDED
//class RAMFileClass : public FileClass{/*...*/};
