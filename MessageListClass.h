/*
	Use this to print a message on the screen!
*/

#pragma once

#include <wchar.h>
#include <ASMMacros.h>
#include <ColorScheme.h>
#include <TextLabelClass.h>
#include <CommandClass.h>

#include <Helpers/CompileTime.h>

// https://github.com/electronicarts/CnC_Remastered_Collection/blob/7d496e8a633a8bbf8a14b65f490b4d21fa32ca03/REDALERT/MSGLIST.H
class MessageListClass
{
public:
	static constexpr reference<MessageListClass, 0xA8BC60u> const Instance{};

	explicit MessageListClass() noexcept
		{ JMP_THIS(0x5D39D0); }

	~MessageListClass() noexcept
		{ JMP_THIS(0x5D3A40); }

	void Init(int X, int Y, int MaxMsg, int MaxChars, int Height, int EditX, int EditY, int EnableOverflow, int OverflowStart, int OverflowEnd, int Width = 640)
		{ JMP_THIS(0x5D3A60); }

	TextLabelClass* AddMessage(const wchar_t* Name, int ID, const wchar_t* Message, int ColorSchemeIdx, TextPrintType Style, int Timeout, bool SinglePlayer)
		{ JMP_THIS(0x5D3BA0); }

	wchar_t* GetMessage(int ID) const
		{ JMP_THIS(0x5D3F60); }

	TextLabelClass* GetLabel(int ID) const
		{ JMP_THIS(0x5D3F90); }

	bool ConcatMessage(const wchar_t* Name, int ID, const wchar_t* Message, int Timeout)
		{ JMP_THIS(0x5D3FC0); }

	void SetEditFocus() const
		{ JMP_THIS(0x5D41E0); }

	bool HasEditFocus() const
		{ JMP_THIS(0x5D41F0); }

	TextLabelClass* AddEdit(int ColorSchemeIdx, TextPrintType Style, wchar_t* Message, char CursorCharacter = 0, int Width = 640)
		{ JMP_THIS(0x5D4210); }

	void RemoveEdit()
		{ JMP_THIS(0x5D4390); }

	wchar_t* GetEditBuffer() const
		{ JMP_THIS(0x5D4400); }

	void SetEditColor(int ColorSchemeIdx)
		{ JMP_THIS(0x5D4410); }

	int Manage()
		{ JMP_THIS(0x5D4430); }

	int Input(int& Input, int DefInput = 0)
		{ JMP_THIS(0x5D4510); }

	void Draw() const
		{ JMP_THIS(0x5D49A0); }

	int NumMessages() const
		{ JMP_THIS(0x5D4AA0); }

	void SetWidth(int width)
		{ JMP_THIS(0x5D4AD0); }

	int TrimMessage(wchar_t* dest, wchar_t* src, int min_chars, int max_chars, int scandir)
		{ JMP_THIS(0x5D4B20); }

	void ComputeY()
		{ JMP_THIS(0x5D4BF0); }

	// if pLabel is given, the message will be {$pLabel}:{$pMessage}
	// else it will be just {$pMessage}
	void PrintMessage(const wchar_t* pMessage, int durationFrames = 0x96, int nColorSchemeIndex = ColorScheme::White, bool bSilent = false)
		{ this->AddMessage(nullptr, 0, pMessage, nColorSchemeIndex, static_cast<TextPrintType>(0x4046), durationFrames, bSilent); }

	void PrintMessage(const wchar_t* pMessage, double durationMinutes, int nColorSchemeIndex = ColorScheme::White, bool bSilent = false)
		{ this->AddMessage(nullptr, 0, pMessage, nColorSchemeIndex, static_cast<TextPrintType>(0x4046), static_cast<int>(durationMinutes * 900), bSilent); }


	TextLabelClass* MessageList;
	Point2D MessagePos;
	int MaxMessageCount;
	int MaxCharacters;
	int Height;
	bool EnableOverflow;
	bool IsEdit;
	bool AdjustEdit;
	Point2D EditPos;
	TextLabelClass* EditLabel;
	wchar_t EditBuffer[162];
	wchar_t OverflowBuffer[162];
	DWORD EditCurrentPos;
	DWORD EditInitialPos;
	wchar_t CursorCharacter;
	DWORD OverflowStart;
	DWORD OverflowEnd;
	int Width;
	wchar_t MessageBuffers[14][162];
	wchar_t BufferAvail[14];
};

static_assert(sizeof(MessageListClass) == 0x149C);
