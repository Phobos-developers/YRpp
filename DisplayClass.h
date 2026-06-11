#pragma once

#include <MapClass.h>

class CCINIClass;
class ObjectTypeClass;

class NOVTABLE DisplayClass : public MapClass
{
public:
	//Static
	DEFINE_REFERENCE(DisplayClass, Instance, 0x87F7E8u)

	//WIP: DisplayClass::TacticalClass goes HERE

	bool ProcessClickCoords(Point2D *src, CellStruct *XYdst, CoordStruct *XYZdst, ObjectClass **Target, BYTE *a5, BYTE *a6)
		{ JMP_THIS(0x692300); }

	// the foundation for placement with green/red
	void  SetActiveFoundation(const CellStruct *Coords)
		{ JMP_THIS(0x4A8BF0); }

	// Building Adjacent etc. check. Pretty much always called with:
	// foundationData = DisplayClass::CurrentFoundation_Data
	// currentPosition = DisplayClass::CurrentFoundation_CenterCell + DisplayClass::CurrentFoundation_TopLeftOffset
	bool PassesProximityCheck(ObjectTypeClass* pType, int houseArrayIndex, CellStruct* foundationData, CellStruct* currentPosition)
		{ JMP_THIS(0x4A8EB0); }

	//Destructor
	virtual ~DisplayClass() RX;

	//GScreenClass
	//MapClass
	//DisplayClass
	virtual HRESULT Load(IStream* pStm) RX;
	virtual HRESULT Save(IStream* pStm) RX;
	virtual void LoadFromINI(CCINIClass* pINI) RX; //Loads the map from a map file.
	virtual const wchar_t* GetToolTip(UINT nDlgID) R0;
	virtual void InitGUI() RX;
	virtual void ClearDragBand() RX;
	virtual bool MapCell(CellStruct* pMapCoord, HouseClass* pHouse) R0;
	virtual bool RevealFogShroud(CellStruct* pMapCoord, HouseClass* pHouse, bool bIncreaseShroudCounter) R0;
	virtual bool MapCellFoggedness(CellStruct* pMapCoord, HouseClass* pHouse) R0;
	virtual bool MapCellVisibility(CellStruct* pMapCoord, HouseClass* pHouse) R0;
	virtual MouseCursorType GetLastMouseCursor() = 0;
	virtual bool ScrollMap(DWORD dwUnk1, DWORD dwUnk2, DWORD dwUnk3) R0;
	virtual void Set_View_Dimensions(const RectangleStruct& rect) RX;
	virtual void vt_entry_AC(DWORD dwUnk) RX;
	virtual void RightMouseButtonClick(Point2D* pPoint) RX;
	virtual void LeftMouseButtonClick(Point2D* pPoint) RX;

	//Decides which mouse pointer to set and then does it.
	//Mouse is over cell pMapCoords which is bShrouded and holds pObject.
	virtual bool ConvertAction(const CellStruct& cell, bool bShrouded, ObjectClass* pObject, Action action, bool dwUnk) RX;
	virtual void LeftMouseButtonDown(const Point2D& point) RX;
	virtual void LeftMouseButtonUp(const CoordStruct& coords, const CellStruct& cell, ObjectClass* pObject, Action action, DWORD dwUnk2) RX;
	virtual void RightMouseButtonUp(DWORD dwUnk) RX;

	//Non-virtual

	Action DecideAction(const CellStruct& cell, ObjectClass* pObject, DWORD dwUnk)
		{ JMP_THIS(0x692610); }

	/* pass in CurrentFoundationData and receive the width/height of a bounding rectangle in cells */
	CellStruct FoundationBoundsSize(CellStruct const* const pFoundationData) const
		{ JMP_THIS(0x4A94F0); }

	/* marks or unmarks the cells pointed to by CurrentFoundationData as containing a building */
	void MarkFoundation(CellStruct * BaseCell, bool Mark)
		{ JMP_THIS(0x4A95A0); }

	// Submit object to layer.
	void Submit(ObjectClass* pObject)
		{ JMP_THIS(0x4A9720); }

	// Remove object from layer.
	void Remove(ObjectClass* pObject)
		{ JMP_THIS(0x4A9770); }

protected:
	//Constructor
	DisplayClass() {}	//don't need this

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

public:
	CellStruct CurrentFoundation_CenterCell;	//Currently placing the building here
	CellStruct CurrentFoundation_TopLeftOffset;		// offset from center cell of the current foundation (under the mouse) to the top left cell
	CellStruct* CurrentFoundation_Data;	//Foundation data of the building we're currently placing (note: limited to 120 cells)
	bool unknown_1180;
	bool unknown_1181;
	CellStruct CurrentFoundationCopy_CenterCell; // All the Copies are used in the time between clicking and actual execution
	CellStruct CurrentFoundationCopy_TopLeftOffset;
	CellStruct * CurrentFoundationCopy_Data; // (note: limited to 50 [!] cells)
	ObjectClass *CurrentBuildingCopy;
	ObjectTypeClass *CurrentBuildingTypeCopy;
	int CurrentBuildingOwnerArrayIndexCopy;
	bool FollowObject;
	ObjectClass* ObjectToFollow;
	ObjectClass* CurrentBuilding;		//Building we're currently placing
	ObjectTypeClass* CurrentBuildingType;	//Type of that building
	int CurrentBuildingOwnerArrayIndex;
	bool RepairMode;
	bool SellMode;
	bool PowerToggleMode;
	bool PlanningMode;
	bool PlaceBeaconMode;
	int CurrentSWTypeIndex;	//Index of the SuperWeaponType we have currently selected
	DWORD unknown_11BC;
	Point2D unknown_11C0;
	DWORD unknown_11C8;
	bool unknown_bool_11CC;
	bool unknown_bool_11CD;
	bool unknown_bool_11CE;
	bool DraggingRectangle;
	bool unknown_bool_11D0;
	bool unknown_bool_11D1;
	Point2D unknown_11D4;
	Point2D unknown_11DC;
	PROTECTED_PROPERTY(DWORD, padding_11E4);
};
