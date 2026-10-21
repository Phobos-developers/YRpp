#pragma once

#include <SidebarClass.h>


class MouseCursor {
public:
	DEFINE_ARRAY_REFERENCE(MouseCursor, [86], Cursors, 0x82D028u);

	static MouseCursor& GetCursor(MouseCursorType cursor) {
		return Cursors[static_cast<int>(cursor)];
	}

	MouseCursor() = default;

	MouseCursor(
		int frame, int count, int interval, int miniFrame, int miniCount,
		MouseHotSpotX hotX, MouseHotSpotY hotY)
		: Frame(frame), Count(count), Interval(interval), MiniFrame(miniFrame),
		MiniCount(miniCount), HotX(hotX), HotY(hotY)
	{ }

	int Frame{ 0 };
	int Count{ 1 };
	int Interval{ 1 };
	int MiniFrame{ -1 };
	int MiniCount{ 0 };
	MouseHotSpotX HotX{ MouseHotSpotX::Center };
	MouseHotSpotY HotY{ MouseHotSpotY::Middle };
};

struct TabDataClass
{
	int TargetValue;
	int LastValue;
	bool NeedsRedraw;
	bool ValueIncreased;
	bool ValueChanged;
	PROTECTED_PROPERTY(BYTE, align_B);
	int ValueDelta;

	TabDataClass()
		{ JMP_THIS(0x4A2350); }
};

static_assert(sizeof(TabDataClass) == 0x10);

class TabClass : public SidebarClass, public INoticeSink
{
public:
	//Static
	DEFINE_REFERENCE(TabClass, Instance, 0x87F7E8u)

	TabDataClass TabData;
	CDTimerClass unknown_timer_552C;
	CDTimerClass InsufficientFundsBlinkTimer;
	bool ThumbActive;
	bool MissionTimerPinged;
	BYTE unknown_byte_5546;
	PROTECTED_PROPERTY(BYTE, padding_5547);
};

static_assert(sizeof(TabClass) == 0x5548);

class ScrollClass : public TabClass
{
public:
	//Static
	DEFINE_REFERENCE(ScrollClass, Instance, 0x87F7E8u)

	int Inertia; // 0x5548
	bool IsCoastScrollAllowed; // 0x554C
	PROTECTED_PROPERTY(BYTE, align_554D[3]);
	Point2D RightPressPoint; // 0x5550
	bool IsDragOperation; // 0x5558
	bool EdgeScrollAllowed; // 0x5559
	bool IsMouseDown; // 0x555A
	PROTECTED_PROPERTY(BYTE, padding_555B);
};

static_assert(sizeof(ScrollClass) == 0x555C);

class NOVTABLE MouseClass : public ScrollClass
{
public:
	//Static
	DEFINE_REFERENCE(MouseClass, Instance, 0x87F7E8u)

	//Destructor
	virtual ~MouseClass() RX;

	//GScreenClass
	virtual bool SetCursor(MouseCursorType idxCursor, bool miniMap) override R0;
	virtual bool UpdateCursor(MouseCursorType idxCursor, bool miniMap) override R0;
	virtual bool RestoreCursor() override R0;
	virtual void UpdateCursorMinimapState(bool miniMap) override RX;

	//DisplayClass
	virtual MouseCursorType GetLastMouseCursor() override RT(MouseCursorType);

	bool MouseCursorIsMini;
	PROTECTED_PROPERTY(BYTE, padding_555D[3]);
	MouseCursorType MouseCursorIndex;
	MouseCursorType MouseCursorLastIndex;
	int MouseCursorCurrentFrame;
};

static_assert(sizeof(MouseClass) == 0x556C);
