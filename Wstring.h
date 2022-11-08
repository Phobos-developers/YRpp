#pragma once

#include <cstring>
#include <Memory.h>

struct CharTrait
{
	size_t Length(const char* pString) const
	{
		return strlen(pString);
	}

	size_t Find(const char* _Str, const char* _Control)
	{
		return strcspn(_Str, _Control);
	}

	const char* Find(const char* _String, char _Ch)
	{
		return strchr(_String, _Ch);
	}

	int ToInteger(const char* _String)
	{
		return atoi(_String);
	}

	char* CopyN(char* _Destination, const char* _Source, size_t _Count)
	{
		return strncpy(_Destination, _Source, _Count);
	}

	char* Copy(char* _Dest, const char* _Source)
	{
		return strcpy(_Dest, _Source);
	}

	char* ConcatN(char* _Dest, const char* _Source, size_t _Count)
	{
		return strncat(_Dest, _Source, _Count);
	}

	char* Concat(char* _Destination, const char* _Source, size_t _Count)
	{
		return strcat(_Destination, _Source);
	}

	int Compare(const char* _Str1, const char* _Str2)
	{
		return strcmp(_Str1, _Str2);
	}

	static int(__cdecl* Format)(char* Buffer, const char* Format, ...);
	static const char* IntegerFormatString;
	static const char* LeadingZeroIntegerFormatString;
	static char Null;

private:
	char Dummy;
};

__declspec(selectany) int(__cdecl* CharTrait::Format)(char*, const char*, ...) = sprintf;
__declspec(selectany) const char* CharTrait::IntegerFormatString = "%d";
__declspec(selectany) const char* CharTrait::LeadingZeroIntegerFormatString = "%%0%dd";
__declspec(selectany) char CharTrait::Null = '\0';

struct WCharTrait
{
	size_t Length(const wchar_t* pString) const
	{
		return wcslen(pString);
	}

	size_t Find(const wchar_t* _Str, const wchar_t* _Control)
	{
		return wcscspn(_Str, _Control);
	}

	const wchar_t* Find(const wchar_t* _String, wchar_t _Ch)
	{
		return wcschr(_String, _Ch);
	}

	int ToInteger(const wchar_t* _String)
	{
		return _wtoi(_String);
	}

	wchar_t* CopyN(wchar_t* _Destination, const wchar_t* _Source, size_t _Count)
	{
		return wcsncpy(_Destination, _Source, _Count);
	}

	wchar_t* Copy(wchar_t* _Dest, const wchar_t* _Source)
	{
		return wcscpy(_Dest, _Source);
	}

	wchar_t* ConcatN(wchar_t* _Dest, const wchar_t* _Source, size_t _Count)
	{
		return wcsncat(_Dest, _Source, _Count);
	}

	wchar_t* Concat(wchar_t* _Destination, const wchar_t* _Source, size_t _Count)
	{
		return wcscat(_Destination, _Source);
	}

	int Compare(const wchar_t* _Str1, const wchar_t* _Str2)
	{
		return wcscmp(_Str1, _Str2);
	}

	static int(__cdecl* Format)(wchar_t* Buffer, const wchar_t* Format, ...);
	static const wchar_t* IntegerFormatString;
	static const wchar_t* LeadingZeroIntegerFormatString;
	static wchar_t Null;

private:
	char Dummy;
};

__declspec(selectany) int(__cdecl* WCharTrait::Format)(wchar_t*, const wchar_t*, ...) = swprintf;
__declspec(selectany) const wchar_t* WCharTrait::IntegerFormatString = L"%d";
__declspec(selectany) const wchar_t* WCharTrait::LeadingZeroIntegerFormatString = L"%%0%dd";
__declspec(selectany) wchar_t WCharTrait::Null = L'\0';

template<typename TChar, typename TCharTraits>
class Wstring_base
{
private:
	using My_Type = Wstring_base<TChar, TCharTraits>;

public:
	static const My_Type EmptyString;

	explicit Wstring_base<TChar, TCharTraits>() noexcept { };

	explicit Wstring_base<TChar, TCharTraits>(const TChar* pString) noexcept : Wstring_base<TChar, TCharTraits> { }
	{
		if (pString)
		{
			Buffer = AllocateBuffer(TCharTraits().Length(pString) + 1);
			Buffer[0] = TCharTraits::Null;
			TCharTraits().Copy(Buffer, pString);
		}
		else
		{
			Buffer = AllocateBuffer(1);
			Buffer[0] = TCharTraits::Null;
		}
	}

	explicit Wstring_base<TChar, TCharTraits>(const My_Type& another) noexcept : Wstring_base<TChar, TCharTraits> {}
	{
		if (another.Buffer)
		{
			Buffer = AllocateBuffer(another.Length() + 1);
			TCharTraits().Copy(Buffer, another.Buffer);
		}
	}

	My_Type& operator=(const TChar* pString)
	{
		ReleaseBuffer();

		if (pString)
		{
			Buffer = AllocateBuffer(TCharTraits().Length(pString) + 1);
			Buffer[0] = TCharTraits::Null;
			TCharTraits().Copy(Buffer, pString);
		}
		else
		{
			Buffer = AllocateBuffer(1);
			Buffer[0] = TCharTraits::Null;
		}

		return *this;
	}

	My_Type& operator=(const My_Type& another)
	{
		if (Buffer || another.Buffer)
		{
			if (!Buffer || !another.Buffer || *this != another)
			{
				ReleaseBuffer();

				if (!another.Buffer)
					const_cast<My_Type&>(another) = EmptyString;

				Buffer = AllocateBuffer(another.Length() + 1);
				TCharTraits().Copy(Buffer, another.Buffer);
			}
		}

		return *this;
	}

	~Wstring_base() noexcept
	{
		ReleaseBuffer();
	}

	bool operator==(const TChar* pString) const
	{
		if (!Buffer && !pString)
			return true;

		if (Buffer && pString)
			return TCharTraits().Compare(Buffer, pString) == 0;

		return 0;
	}

	bool operator==(const My_Type& another) const
	{
		return *this == another.Buffer;
	}

	bool operator!=(const TChar* pString) const
	{
		return *this != pString;
	}

	bool operator!=(const My_Type& another) const
	{
		return *this == another;
	}

	My_Type& operator+=(const TChar* pString)
	{
		Concat(pString);
		return *this;
	}

	My_Type& operator+=(const My_Type& another)
	{
		Concat(another);
		return *this;
	}

	const My_Type operator+(const TChar* pString)
	{
		My_Type ret = *this;
		ret += pString;
		return ret;
	}

	const My_Type operator+(const My_Type& another)
	{
		My_Type ret = *this;
		ret += another;
		return ret;
	}

	TChar operator[](size_t nIdx) const
	{
		return GetChar(nIdx);
	}

	bool Concat(const TChar* pString)
	{
		if (!pString)
			return true;

		if (Buffer)
		{
			auto pOldBuffer = Buffer;
			Buffer = AllocateBuffer(Length() + TCharTraits().Length(pString) + 1);
			TCharTraits().Copy(Buffer, pOldBuffer);
			YRMemory::Deallocate(pOldBuffer);
			TCharTraits().Concat(Buffer, pString);
		}
		else
		{
			Buffer = AllocateBuffer(TCharTraits().Length(pString) + 1);
			Buffer[0] = TCharTraits::Null;
			TCharTraits().Concat(Buffer, pString);
		}

		return true;
	}

	bool Concat(size_t nSize, const TChar* pString)
	{
		if (!pString || nSize == 0)
			return 1;

		if (Buffer)
		{
			auto pOldBuffer = Buffer;
			Buffer = AllocateBuffer(Length() + nSize + 1);
			TCharTraits().Copy(Buffer, pOldBuffer);
			YRMemory::Deallocate(pOldBuffer);
			TCharTraits().ConcatN(Buffer, pString, nSize);
		}
		else
		{
			Buffer = AllocateBuffer(nSize + 1);
			Buffer[0] = TCharTraits::Null;
			TCharTraits().ConcatN(Buffer, pString, nSize);
		}

		return true;
	}

	bool Concat(const My_Type& another)
	{
		if (!another.Buffer || another.Length() == 0)
			return true;

		return Concat(another.Length(), another.Buffer);
	}

	bool TrimRange(size_t nStart, size_t nLength)
	{
		if (nStart + nLength > Length())
			nStart = Length() - nLength;

		if (nStart < 0)
		{
			nLength += nStart;
			nStart = 0;
		}

		if (nLength <= 0)
			return false;

		auto pBuffer = AllocateBuffer(Length() - nLength + 1);
		Buffer[nStart] = Buffer[nStart - 1 + nLength] = TCharTraits::Null;
		TCharTraits().Copy(pBuffer, Buffer);
		TCharTraits().Concat(pBuffer, Buffer + nStart + nLength);
		YRMemory::Deallocate(Buffer);
		Buffer = pBuffer;

		return true;
	}

	bool RemoveCharacter(TChar ch)
	{
		if (!Buffer)
			return false;

		bool bRemoved = false;
		if (auto p = TCharTraits().Find(Buffer, ch))
		{
			for (size_t len = Length(); p; p = TCharTraits().Find(Buffer, ch))
			{
				memcpy(p, p + 1, Buffer - p + len-- - 1);
				Buffer[len] = TCharTraits::Null;
			}

			auto pBuffer = AllocateBuffer(Length() + 1);
			TCharTraits().Copy(pBuffer, Buffer);
			YRMemory::Deallocate(Buffer);
			bRemoved = true;
		}

		return bRemoved;
	}

	void RemoveSpaces()
	{
		RemoveCharacter(TCharTraits::Space);
		RemoveCharacter(TCharTraits::Tab);
	}

	void TrimToFirstDifference(const My_Type& another)
	{
		size_t i;
		for (i = 0; ; ++i)
		{
			size_t len = Buffer ? Length() : 0;
			if (i >= len)
				break;

			auto p = Buffer;
			if (!Buffer)
				p = EmptyString.Buffer;

			if (!TCharTraits().Find(p, Buffer[i]))
				break;
		}

		if (i > 0)
			TrimRange(0, i);
	}

	void ReleaseBuffer()
	{
		if (Buffer)
		{
			YRMemory::Deallocate(Buffer);
			Buffer = nullptr;
		}
	}

	void Reverse(size_t nLength)
	{
		ReleaseBuffer();

		if (nLength >= 0)
		{
			Buffer = AllocateBuffer(nLength);
			memset(Buffer, 0, nLength * sizeof(TChar));
		}
	}

	void MergeStrings(const TChar* pString, size_t nCount)
	{
		TCharTraits().CopyN(pString, Buffer, nCount);

		if (Length() < nCount)
			memset(pString + Length(), TCharTraits::Space, nCount - Length());

		pString[nCount] = TCharTraits::Null;
	}

	const TChar* const PeekBuffer() const
	{
		return Buffer ? Buffer : EmptyString.Buffer;
	}

	const TChar GetChar(size_t nIdx) const
	{
		return nIdx >= Length() ? 0 : Buffer[nIdx];
	}

	const size_t GetLength() const
	{
		return Buffer ? Length() : 0;
	}

	bool Set(const TChar* pString)
	{
		*this = pString;
	}

	bool SetAt(TChar ch, size_t nIdx)
	{
		if (nIdx >= Length())
			return false;

		Buffer[nIdx] = ch;
		return true;
	}

	bool Replace(size_t nSize, const TChar* pString)
	{
		ReleaseBuffer();

		Buffer = AllocateBuffer(nSize + 1);
		Buffer[0] = TCharTraits::Null;

		if (pString)
			TCharTraits().CopyN(Buffer, pString, nSize);

		Buffer[nSize] = TCharTraits::Null;

		return true;
	}

	void ToLower()
	{
		if (Buffer)
		{
			for (size_t i = 0; i < Length(); ++i)
				TCharTraits().ToLower(Buffer[i]);
		}
	}

	My_Type& ToLower(My_Type& ret)
	{
		ret = *this;
		ret.ToLower();
		return ret;
	}

	void ToUpper()
	{
		if (Buffer)
		{
			for (size_t i = 0; i < Length(); ++i)
				TCharTraits().ToUpper(Buffer[i]);
		}
	}

	My_Type& ToUpper(My_Type& ret)
	{
		ret = *this;
		ret.ToUpper();
		return ret;
	}

	bool Resize(size_t nLength)
	{
		auto pBuffer = AllocateBuffer(nLength + 1);
		pBuffer[0] = TCharTraits::Null;

		TCharTraits().CopyN(pBuffer, PeekBuffer(), nLength);
		pBuffer[nLength] = TCharTraits::Null;

		ReleaseBuffer();

		// Stupid WestWood wrote:
		// *this = pBuffer;
		// YRMemory::Deallocate(pBuffer);
		// I guess what we need to do is just assign this buffer
		Buffer = pBuffer;

		return true;
	}

	bool ResizeToChar(TChar ch)
	{
		if (!Buffer)
			return false;

		if (auto p = TCharTraits().Find(ch))
			return Resize(p - Buffer);

		return false;
	}

	// To be implemented
	int Token(size_t nIdx, TChar* cDelim, My_Type& ret);

	// To be implemented
	int NextLine(unsigned nIdx, My_Type& ret);

	int AsInteger() const
	{
		return TCharTraits().ToInteger(Buffer);
	}

	operator int() const
	{
		return AsInteger();
	}

	void FromInteger(int nValue)
	{
		TChar buffer[0x10];
		TCharTraits::Format(buffer, TCharTraits::IntegerFormatString, nValue);

		*this = buffer;
	}

	static My_Type StringFromInteger(int nValue)
	{
		My_Type ret;
		ret.FromInteger(nValue);
		return ret;
	}

	void FromInteger(int nValue, size_t nLeadingZero)
	{
		TChar buffer[0x10];
		TCharTraits::Format(buffer, TCharTraits::LeadingZeroIntegerFormatString, nLeadingZero);
		TCharTraits::Format(buffer, buffer, nValue);

		*this = buffer;
	}

	static My_Type StringFromInteger(int nValue, size_t nLeadingZero)
	{
		My_Type ret;
		ret.FromInteger(nValue, nLeadingZero);
		return ret;
	}

	bool Contains(const TChar* pString) const
	{
		if (pString && Buffer)
			return TCharTraits().Find(Buffer, pString) < Length();

		return false;
	}

	bool Contains(const My_Type& another) const
	{
		return Contains(another.PeekBuffer());
	}

private:

	TChar* AllocateBuffer(size_t nLen)
	{
		return (TChar*)YRMemory::Allocate(sizeof(TChar) * nLen);
	}

	size_t Length() const
	{
		return TCharTraits().Length(Buffer);
	}

public:
	TChar* Buffer { nullptr };
};

template<typename TChar, typename TCharTrait>
__declspec(selectany) const Wstring_base<TChar, TCharTrait> Wstring_base<TChar, TCharTrait>::EmptyString;

using Wstring = Wstring_base<char, CharTrait>;
using WideWstring = Wstring_base<wchar_t, WCharTrait>;