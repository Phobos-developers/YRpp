#pragma once

#include <PowerClass.h>
#include <StageClass.h>
#include <ShapeButtonClass.h>

class ColorScheme;
class FactoryClass;

// SidebarClass::StripClass::BuildType
struct BuildType
{
	int               ItemIndex{ -1 };
	AbstractType      ItemType{ AbstractType::None };
	BYTE              IsAlt{ 0 }; // the BuildCat of buildings, 0 for everything else
	FactoryClass*     CurrentFactory{ nullptr };
	DWORD             unknown_10{ 0 };
	StageClass        Progress{}; // 0 to 54, how much of this object is constructed (gclock anim level)
	int               FlashEndFrame{ 0 };

	BuildType() = default;

	BuildType(int itemIndex, AbstractType itemType) :
		ItemIndex(itemIndex),
		ItemType(itemType)
	{ /*JMP_THIS(0x6AC7C0);*/ }

	bool operator == (const BuildType& rhs) const {
		return ItemIndex == rhs.ItemIndex && ItemType == rhs.ItemType;
	}

	bool operator != (const BuildType& rhs) const {
		return ItemIndex != rhs.ItemIndex || ItemType != rhs.ItemType;
	}

	bool operator < (const BuildType& rhs) const {
		return SortsBefore(this->ItemType, this->ItemIndex, rhs.ItemType, rhs.ItemIndex);
	}

	static bool __stdcall SortsBefore(AbstractType leftType, int leftIndex, AbstractType rightType, int rightIndex)
		{ JMP_STD(0x6A8420); }
};

struct StripClass;

// the per-cameo button; an array of 4 strips times 60 buttons, stride 0x38
struct SelectClass
{
	static SelectClass* Array()
		{ return reinterpret_cast<SelectClass*>(0xB07E80); }

	// horizontal distance between the two cameo columns
	static int CameoPitchX()
		{ return *reinterpret_cast<int*>(0xB0B4FC); }

	// vertical distance between two cameo rows
	static int CameoPitchY()
		{ return *reinterpret_cast<int*>(0xB0B500); }

	enum { ButtonID = 202, CameoWidth = 60, CameoHeight = 48 };

	void Zap()
		{ JMP_THIS(0x5565F0); }

	void* VTable;
	SelectClass* Next;
	SelectClass* Previous;
	int X;
	int Y;
	int Width;
	int Height;
	DWORD Flags;
	DWORD Status;
	unsigned int ID;
	SelectClass* SendTo;
	StripClass* Strip;
	int Index;

	// unidentified, but it has to exist: without it the stride is 0x34 and Array()[i] walks short
	DWORD unknown_34;
};

static_assert(sizeof(SelectClass) == 0x38, "SelectClass must match the game's array stride");
static_assert(offsetof(SelectClass, X) == 0x0C, "SelectClass layout slipped");
static_assert(offsetof(SelectClass, Width) == 0x14, "SelectClass layout slipped");
static_assert(offsetof(SelectClass, ID) == 0x24, "SelectClass layout slipped");
static_assert(offsetof(SelectClass, Strip) == 0x2C, "SelectClass layout slipped");
static_assert(offsetof(SelectClass, Index) == 0x30, "SelectClass layout slipped");

// SidebarClass::StripClass
struct StripClass
{
	StageClass        Progress;
	bool              AllowedToDraw; // prevents redrawing when layouting the list
	PROTECTED_PROPERTY(BYTE, align_1D[3]);
	Point2D           Location;
	RectangleStruct   Bounds;
	int               Index; // the index of this tab
	bool              NeedsRedraw;
	bool              IsBuilding;
	bool              IsScrollingDown;
	bool              IsScrolling;
	int               Flasher;
	int               TopRowIndex; // scroll position, which row is topmost visible
	int               Scroller;
	int               Slid;
	int               LastSlid;
	int               CameoCount; // filled cameos
	BuildType         Cameos[75];

	void Initialize(int index)
		{ JMP_THIS(0x6A8220); }

	void Activate()
		{ JMP_THIS(0x6A8330); }

	void Deactivate()
		{ JMP_THIS(0x6A83E0); }

	void AddButtons()
		{ JMP_THIS(0x6A93F0); }

	void RemoveButtons()
		{ JMP_THIS(0x6A94B0); }
};

class NOVTABLE SidebarClass : public PowerClass
{
public:
	//Static
	DEFINE_REFERENCE(SidebarClass, Instance, 0x87F7E8u);

	DEFINE_ARRAY_REFERENCE(wchar_t, [0x42u], TooltipBuffer, 0xB07BC4u);
	DEFINE_REFERENCE(ToggleClass, ToggleRepairButton, 0xB0B3A0);
	DEFINE_ARRAY_REFERENCE(ShapeButtonClass, [4], TabButtons, 0xB07C48u);

	void SidebarNeedsRepaint(int mode = 0) {
		this->SidebarNeedsRedraw = true;
		this->SidebarBackgroundNeedsRedraw = true;
		this->Tabs[this->ActiveTabIndex].AllowedToDraw = true;
		this->Tabs[this->ActiveTabIndex].NeedsRedraw = true;
		this->RedrawSidebar(mode);
		SidebarClass::Draw(1);
	}

	void RepaintSidebar(int tab = 0)
		{ JMP_THIS(0x6A60A0); }

	bool AddCameo(AbstractType absType, int idxType)
		{ JMP_THIS(0x6A6300); }

	virtual void Draw(DWORD dwUnk) override
		{ JMP_THIS(0x6A6C30); }

	//Destructor
	virtual ~SidebarClass() RX;

	//SidebarClass
	virtual bool Activate(int control) R0;

	//Non-virtual

	// which tab does the 'th object of that type belong in?
	static int __fastcall GetObjectTabIdx(AbstractType abs, int idxType, int unused)
		{ JMP_STD(0x6ABC60); }

	// which tab does the 'th object of that type belong in?
	static int __fastcall GetObjectTabIdx(AbstractType abs, BuildCat buildCat, bool isNaval)
		{ JMP_STD(0x6ABCD0); }

	bool Scroll(bool up, int column)
		{ JMP_THIS(0x6A6A00); }

	int SetTab(int tabIndex)
		{ JMP_THIS(0x6A7590); }

	void OnTechnoDestroyed(TechnoClass* pTechno)
		{ JMP_THIS(0x6A5F20); }

	void BlitSidebar(bool force)
		{ JMP_THIS(0x6A70E0); }

	// enables or disables the two scroll buttons
	void UpdateScrollButtons()
		{ JMP_THIS(0x6A6610); }

	// how many cameo buttons fit on the strip at the current resolution
	int GetVisibleCameoCount()
		{ JMP_THIS(0x6AC430); }

protected:
	//Constructor
	SidebarClass() {}	//don't need this

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

public:
	StripClass Tabs[0x4];
	DWORD unknown_5394;
	DWORD unknown_5398;
	int ActiveTabIndex;
	DWORD unknown_53A0;
	bool HideObjectNameInTooltip; // see 0x6A9343
	bool IsSidebarActive;
	bool SidebarNeedsRedraw;
	bool SidebarBackgroundNeedsRedraw;
	bool unknown_bool_53A8;

	//Information for the Diplomacy menu, I believe
	HouseClass* DiplomacyHouses[0x8];		//8 players max!
	int DiplomacyKills[0x8];		//total amount of kills per house
	int DiplomacyOwned[0x8];		//total amount of currently owned unit/buildings per house
	int DiplomacyPowerDrain[0x8];	//current power drain per house
	ColorScheme* DiplomacyColors[0x8];		//color scheme per house
	DWORD unknown_544C[0x8];			//??? per house - unused
	DWORD unknown_546C[0x8];			//??? per house - unused
	DWORD unknown_548C[0x8];			//??? per house - unused
	DWORD unknown_54AC[0x8];			//??? per house - unused
	DWORD unknown_54CC[0x8];			//??? per house - unused
	DWORD unknown_54EC[0x8];			//??? per house - unused
	BYTE unknown_550C;
	int DiplomacyNumHouses;			//possibly?

	bool unknown_bool_5514;
	bool unknown_bool_5515;
	PROTECTED_PROPERTY(BYTE, padding_5516[2]);
};
