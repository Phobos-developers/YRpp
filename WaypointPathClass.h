#ifndef WAYPOINTPATH_H
#define WAYPOINTPATH_H

#include <AbstractClass.h>

// this refers to the "planning mode" waypoints you place with your mouse, not mapping waypoints
class WaypointClass
{
public:
	//need to define a == operator so it can be used in array classes
	bool operator == (WaypointClass tWaypoint)
	{
		return (Coords == *tWaypoint.get_Coords() &&
				unknown == tWaypoint.get_unknown());
	}

	//Properties
	PROPERTY_STRUCT(CellStruct,  Coords);
	PROPERTY(DWORD,       unknown);
};

class WaypointPathClass : public AbstractClass
{
public:
	//IPersist
	virtual HRESULT _stdcall GetClassID(CLSID* pClassID) R0;

	//IPersistStream
	virtual HRESULT _stdcall Load(IStream* pStm) R0;
	virtual HRESULT _stdcall Save(IStream* pStm, BOOL fClearDirty) R0;
	
	//Destructor
	virtual ~WaypointPathClass() RX;

	//AbstractClass
	virtual eAbstractType WhatAmI() R0;
	virtual int Size() R0;

	WaypointClass * GetWaypoint(int idx)
		{ PUSH_VAR32(idx); THISCALL(0x763980); }
	WaypointClass * GetWaypointAfter(int idx)
		{ PUSH_VAR32(idx); THISCALL(0x763BA0); }
	bool WaypointExistsAt(WaypointClass *wpt)
		{ PUSH_VAR32(wpt); THISCALL(0x763A50); }

	// Constructor
	WaypointPathClass(int idx)
		{ PUSH_VAR32(idx); THISCALL(0x763810); }

protected:
	//Constructor
	WaypointPathClass():AbstractClass(false)
		{ }
	WaypointPathClass(bool X):AbstractClass(X)
		{ }

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================
	PROPERTY(int,  CurrentWaypointIndex); //seems that way
	PROPERTY_STRUCT(DynamicVectorClass<WaypointClass>,  Waypoints); // actual path waypoints, no *
};

#endif