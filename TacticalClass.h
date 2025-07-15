#pragma once

#include <GeneralDefinitions.h>
#include <GeneralStructures.h>
#include <AbstractClass.h>
#include <ColorScheme.h>
#include <Helpers/CompileTime.h>

class ObjectClass;
class DSurface;
class CellClass;

struct TacticalSelectableStruct
{
	ObjectClass* Object;
	int X;
	int Y;
};

class NOVTABLE TacticalClass : public AbstractClass
{
public:
	DEFINE_REFERENCE(TacticalClass*, Instance, 0x887324u)

	virtual bool sub_6DBB60(CoordStruct const& a2, CoordStruct const& a3, COLORREF a4, DWORD dwUnk) R0;

	void SetTacticalPosition(CoordStruct* pCoord)
		JMP_THIS(0x6D6070);

	CellStruct* CoordsToCell(CellStruct* pDest, CoordStruct* pSource)
		JMP_THIS(0x6D6590);

	[[deprecated]]// inlined in game
	bool CoordsToClient(CoordStruct const* coords, Point2D* pOutClient) const
		JMP_THIS(0x6D2140);

	// returns whether coords are visible at the moment
	std::pair<Point2D, bool> CoordsToClient(const CoordStruct& coords) const
	{
		DEFINE_NONSTATIC_REFERENCE(RectangleStruct, view_bound, 0xB0CE28);
		Point2D point = CoordsToScreen(coords) - this->TacticalPos;
		bool visible = point.X >= -360 && point.X <= view_bound.Width + 360
			&& point.Y >= -180 && point.Y <= view_bound.Height + 180;
		return std::make_pair(point, visible);
	}

	[[deprecated]] // inlined in game
	Point2D* CoordsToScreen(Point2D* pDest, const CoordStruct* pSource)
		JMP_THIS(0x6D1F10);

	static Point2D CoordsToScreen(const CoordStruct& coord)
	{
		auto [x, y] = AdjustForZShapeMove(coord.X, coord.Y);
		return Point2D { x, y - AdjustForZ(coord.Z) };
	}

	CoordStruct* ClientToCoords(CoordStruct* pOutBuffer, Point2D const& client) const
		JMP_THIS(0x6D2280);

	CoordStruct ClientToCoords(Point2D const& client) const
	{
		CoordStruct buffer;
		this->ClientToCoords(&buffer, client);
		return buffer;
	}

	char GetOcclusion(const CellStruct& cell, bool fog) const
		JMP_THIS(0x6D8700);

	/*
	[[deprecated]] // inlined in game
	Point2D * AdjustForZShapeMove(Point2D* pDest, Point2D* pClient)
		JMP_THIS(0x6D1FE0);
	*/

	// wrong name
	static Point2D AdjustForZShapeMove(int x, int y)
	{
		return Point2D {
			(-Unsorted::CellWidthInPixels * y / 2 + Unsorted::CellWidthInPixels * x / 2) / Unsorted::LeptonsPerCell,
			(Unsorted::CellHeightInPixels * y / 2 + Unsorted::CellHeightInPixels * x / 2) / Unsorted::LeptonsPerCell
		};
	}

	// in-game height to on-screen height
	static int __fastcall AdjustForZ(int Height)
		//JMP_STD(0x6D20E0); } // inlined in ga
	{
		// constexpr double sin60 = Math::Sqrt3 / 2;
		// constexpr double pixelPerLepton = Unsorted::CellWidthInPixels / (Math::Sqrt2 * Unsorted::LeptonsPerCell);
		// constexpr double b0cd48 = sin60 * pixelPerLepton;
		// however the precision is fucked up
		return static_cast<int>(Height * (*reinterpret_cast<double*>(0xB0CD48)) + int(Height >= 728) + 0.5);
	}

	void FocusOn(CoordStruct* pDest, int Velocity)
		JMP_THIS(0x6D2420);


	// called when area needs to be marked for redrawing due to external factors
	// - alpha lights, terrain changes like cliff destruction, etc
	void RegisterDirtyArea(RectangleStruct Area, bool bUnk)
		JMP_THIS(0x6D2790);

	void RegisterCellAsVisible(CellClass* pCell)
		JMP_THIS(0x6DA7D0)

		static int DrawTimer(int index, ColorScheme* Scheme, int Time, wchar_t* Text, Point2D* someXY1, Point2D* someXY2)
		JMP_STD(0x6D4B50);

	void AddSelectable(TechnoClass* pTechno, int x, int y)
		JMP_THIS(0x6D9EF0);

	/*
	*   TacticalRenderMode_0_ALL = 0x0,
	*   TacticalRenderMode_TERRAIN = 0x1,
	*   TacticalRenderMode_MOVING_ANIMATING = 0x2,
	*   TacticalRenderMode_3_ALL = 0x3,
	*   TacticalRenderMode_STOPDRAWING = 0x4,
	*   TacticalRenderMode_5 = 0x5,
	*/
	void Render(DSurface* pSurface, bool flag, int eMode)
		JMP_THIS(0x6D3D10);

	[[deprecated]]
	Point2D* ApplyMatrix_Pixel(Point2D* coords, Point2D* offset)
		JMP_THIS(0x6D2070);

	Point2D ApplyMatrix_Pixel(const Point2D& offset)
	{
		auto&& temp = this->IsoTransformMatrix * Vector3D<float>{(float)offset.X, (float)offset.Y, 0};
		return { (int)temp.X,(int)temp.Y };
	}

public:
	wchar_t ScreenText[64];
	int EndGameGraphicsFrame;
	int LastAIFrame;
	bool field_AC;
	bool field_AD;
	PROTECTED_PROPERTY(char, gap_AE[2]);
	Point2D TacticalPos;
	Point2D LastTacticalPos;
	double ZoomInFactor;
	Point2D Point_C8;
	Point2D Point_D0;
	float field_D8;
	float field_DC;
	int VisibleCellCount;
	CellClass* VisibleCells[800];
	Point2D TacticalCoord1;
	DWORD field_D6C;
	DWORD field_D70;
	Point2D TacticalCoord2;
	bool field_D7C;
	bool Redrawing; // set while redrawing - cheap mutex // TacticalPosUpdated
	PROTECTED_PROPERTY(char, gap_D7E[2]);
	RectangleStruct ContainingMapCoords;
	LTRBStruct Band;
	DWORD MouseFrameIndex;
	CDTimerClass StartTime;
	int SelectableCount;
	Matrix3D Unused_Matrix3D;
	Matrix3D IsoTransformMatrix;
	DWORD field_E14;

};
