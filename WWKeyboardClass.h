#pragma once

#include <GameOptionsClass.h>
#include <GeneralStructures.h>

#include <Helpers/CompileTime.h>

class WWKeyboardClass {
public:
	DEFINE_REFERENCE(WWKeyboardClass*, Instance, 0x87F770u)

	byte Clear()
		{ JMP_THIS(0x54F720); }

	bool Put_Element(unsigned short value)
		{ JMP_THIS(0x54F1C0); }

	bool Put_Key_Message(unsigned short key, bool release = false)
		{ JMP_THIS(0x54F200); }

	bool Down(int key) const
		{ JMP_THIS(0x54F5C0); }

	bool IsForceFireKeyPressed() const {
		return this->Down(GameOptionsClass::Instance.KeyForceFire1)
			|| this->Down(GameOptionsClass::Instance.KeyForceFire2);
	}

	bool IsForceMoveKeyPressed() const {
		return this->Down(GameOptionsClass::Instance.KeyForceMove1)
			|| this->Down(GameOptionsClass::Instance.KeyForceMove2);
	}

	bool IsForceSelectKeyPressed() const {
		return this->Down(GameOptionsClass::Instance.KeyForceSelect1)
			|| this->Down(GameOptionsClass::Instance.KeyForceSelect2);
	}

	int MouseQX;
	int MouseQY;
	wchar_t LastCharacter; // Character from the last dequeued text event.
	Point2D MousePos;
	byte KeyState[256];
	WORD Buffer[256];
	int Head; // Next queue element to read.
	int Tail; // Next queue slot to write.
};

static_assert(sizeof(WWKeyboardClass) == 0x31C, "WWKeyboardClass is the wrong size.");
