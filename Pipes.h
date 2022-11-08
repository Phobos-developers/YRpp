#pragma once

#include <YRPP.h>

class NOVTABLE Pipe
{
public:
	explicit Pipe() = default;

	virtual ~Pipe()
	{
		if (this->ChainTo)
			this->ChainTo->ChainFrom = this->ChainFrom;

		if (this->ChainFrom)
			this->ChainFrom->Put_To(this->ChainTo);

		this->ChainFrom = nullptr;
		this->ChainTo = nullptr;
	}

	virtual int Flush()
	{
		if (this->ChainTo)
			return this->ChainTo->Flush();

		return 0;
	}

	virtual int End() { return(Flush()); }
	
	virtual void Put_To(Pipe* pPipe)
	{
		if (this->ChainTo != pPipe)
		{
			if (pPipe && pPipe->ChainFrom)
			{
				pPipe->ChainFrom->Put_To(nullptr);
				pPipe->ChainFrom = nullptr;
			}

			if (this->ChainTo)
			{
				this->ChainTo->ChainFrom = nullptr;
				this->ChainTo->Flush();
			}

			this->ChainTo = pPipe;
			if (this->ChainTo)
				this->ChainTo->ChainFrom = this;
		}
	}

	void Put_To(Pipe& pipe) { Put_To(&pipe); }

	virtual int Put(void const* source, int length)
	{
		if (this->ChainTo)
			this->ChainTo->Put(source, length);

		return length;
	}

	Pipe* ChainTo { nullptr };
	Pipe* ChainFrom { nullptr };

private:
	Pipe(Pipe& rvalue) = delete;
	Pipe& operator=(Pipe const& pipe) = delete;
};

class BufferPipe : public Pipe
{
public:
	explicit BufferPipe() = delete;
	explicit BufferPipe(void* pBuffer, size_t nLength) : Pipe {}, Buffer { pBuffer,nLength }
	{
	}

	virtual ~BufferPipe() override final
	{
	}

	virtual int Put(void const* pSource, int nLength) override final
	{
		if (this->Buffer.Buffer && pSource && nLength > 0)
		{
			if (this->Buffer.Size)
			{
				int nResidue = this->Buffer.Size - this->Index;
				if (nLength >= nResidue)
					nLength = nResidue;
			}
			if (nLength > 0)
				memcpy((char*)this->Buffer.Buffer + this->Index, pSource, nLength);

			this->Index += nLength;
			return nLength;
		}

		return 0;
	}

	MemoryBuffer Buffer;
	int Index;

private:
	BufferPipe(BufferPipe& rvalue) = delete;
	BufferPipe& operator=(BufferPipe const& pipe) = delete;
};

class LCWPipe : public Pipe
{
public:
	explicit LCWPipe() = delete;
	explicit LCWPipe(BOOL bControl, size_t nBlockSize) : Pipe {}
	{
		this->Control = bControl;
		this->SafetyMargin = nBlockSize / 0x80 + 1;
		if (this->SafetyMargin < 0x80)
			this->SafetyMargin = 0x80;
		this->Counter = 0;
		this->Buffer = nullptr;
		this->Buffer2 = nullptr;
		this->BlockSize = nBlockSize;
		this->Buffer = YRMemory::Allocate(this->BlockSize + this->SafetyMargin);
		this->Buffer2 = YRMemory::Allocate(this->BlockSize + this->SafetyMargin);
		this->BlockHeader_CompCount = -1;
		this->BlockHeader_UncompCount = 0;
	}

	virtual ~LCWPipe() override final
	{
		YRMemory::Deallocate(this->Buffer);
		YRMemory::Deallocate(this->Buffer2);
	}

	virtual int Flush() override final
	{
		JMP_THIS(0x5522D0);
	}

	virtual int Put(void const* pSource, int nLength) override final
	{
		JMP_THIS(0x5520A0);
	}

	BOOL Control;
	int Counter;
	void* Buffer;
	void* Buffer2;
	size_t BlockSize;
	int SafetyMargin;
	short BlockHeader_CompCount;
	short BlockHeader_UncompCount;

private:
	LCWPipe(LCWPipe& rvalue) = delete;
	LCWPipe& operator=(LCWPipe const& pipe) = delete;
};