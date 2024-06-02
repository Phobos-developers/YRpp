#pragma once

#include <ASMMacros.h>
#include <YRPPCore.h>
#include <YRMath.h>
#include <YRMathVector.h>
#include <BasicStructures.h>

#include <Facing.h>

//used for cell coordinates/vectors
using CellStruct = Vector2D<short>;
using Point2D = Vector2D<int>;
using CoordStruct = Vector3D<int>;

struct BasePlanningCell {
	int Weight;
	CellStruct Position;
};

// this crap is used in several Base planning routines
struct BasePlanningCellContainer {
	BasePlanningCell * Items;
	int Count;
	int Capacity;
	bool Sorted;
	DWORD Unknown_10;

	bool AddCapacity(int AdditionalCapacity)
		{ JMP_THIS(0x510860); }

	// for qsort
	static int __cdecl Comparator(const void *, const void *)
		{ JMP_STD(0x5108F0); }
};

// combines number and a string
struct NamedValue {
	const char* Name;
	int Value;

	bool operator == (int value) const {
		return this->Value == value;
	}

	bool operator == (const char* name) const {
		return !_strcmpi(this->Name, name);
	}

	bool operator == (const NamedValue& other) const {
		return this->Value == other.Value && *this == other.Name;
	}
};

class RectangleStruct
{
	friend const RectangleStruct Intersect(const RectangleStruct& rect1, const RectangleStruct& rect2);
	friend const RectangleStruct Intersect(const RectangleStruct& rect1, const RectangleStruct& rect2, int* x, int* y);
	friend const RectangleStruct Union(const RectangleStruct& rect1, const RectangleStruct& rect2);

public:
	RectangleStruct();
	RectangleStruct(int x, int y, int w, int h);
	RectangleStruct(const Point2D& xy, int w, int h);
	RectangleStruct(const Point2D& xy, const Point2D& wh);
	RectangleStruct(const RectangleStruct& that);

	int& operator[](int index) { return (&X)[index]; }
	const int& operator[](int index) const { return (&X)[index]; }

	RectangleStruct& operator=(const RectangleStruct& that)
	{
		if (this != &that)
		{
			X = that.X;
			Y = that.Y;
			Width = that.Width;
			Height = that.Height;
		}
		return *this;
	}

	bool operator==(const RectangleStruct& that) const
	{
		return (that.X == X) && (that.Width == Width)
			&& (that.Y == Y) && (that.Height == Height);
	}

	bool operator!=(const RectangleStruct& that) const
	{
		return (that.X != X) && (that.Width != Width)
			&& (that.Y != Y) && (that.Height != Height);
	}

	RectangleStruct& operator|=(const RectangleStruct& that) { *this = Union(*this, that); return *this; }
	RectangleStruct& operator&=(const RectangleStruct& that) { *this = Intersect(*this, that); return *this; }
	RectangleStruct& operator+=(const Point2D& point) { X += point.X; Y += point.Y; return *this; }

	RectangleStruct& operator+=(const RectangleStruct& RectangleStruct)
	{
		X += RectangleStruct.X;
		Y += RectangleStruct.Y;
		Width += RectangleStruct.Width;
		Height += RectangleStruct.Height;
		return *this;
	}

	RectangleStruct& operator-=(const Point2D& point) { X -= point.X; Y -= point.Y; return *this; }

	RectangleStruct& operator-=(const RectangleStruct& RectangleStruct)
	{
		X -= RectangleStruct.X;
		Y -= RectangleStruct.Y;
		Width -= RectangleStruct.Width;
		Height -= RectangleStruct.Height;
		return *this;
	}

	RectangleStruct operator+(const Point2D& point)
	{
		RectangleStruct tmp = *this;
		tmp.X = X + point.X;
		tmp.Y = Y + point.Y;
		return tmp;
	}

	RectangleStruct operator-(const Point2D& point)
	{
		RectangleStruct tmp = *this;
		tmp.X = X - point.X;
		tmp.Y = Y - point.Y;
		return tmp;
	}

	RectangleStruct Bias_To(const RectangleStruct& rect)
	{
		Point2D xy = Top_Left() + rect.Top_Left();
		return RectangleStruct(xy, Width, Height);
	}

	bool Intersects_With(const RectangleStruct& with) const
	{
		return (X > with.Width) || (Width < with.X) || (Y > with.Height) || (Height < with.Y);
	}

	bool Is_Overlapping(const RectangleStruct& rect)
	{
		return X < rect.X + rect.Width
			&& Y < rect.Y + rect.Height
			&& X + Width > rect.X
			&& Y + Height > rect.Y;
	}

	__forceinline bool Is_Within(const RectangleStruct& RectangleStruct) const { return (RectangleStruct.X >= X && RectangleStruct.X < (X + Width)) && (RectangleStruct.Width >= Y && RectangleStruct.Width < (Y + Height)); }
	__forceinline bool Is_Within(const Point2D& point) const { return (point.X >= X && point.X < (X + Width)) && (point.Y >= Y && point.Y < (Y + Height)); }
	__forceinline bool Is_Within(int x, int y) const { return (x >= X && x < (X + Width)) && (y >= Y && y < (Y + Height)); }

	void Inflate(int w, int h, bool adjust_xy = false)
	{
		if (adjust_xy)
		{
			X -= w;
			Y -= h;
		}
		Width += w;
		Height += h;
	}

	void Move(int x, int y) { X += x; Y += y; }
	void Move(const Point2D& point) { X += point.X; Y += point.Y; }

	const RectangleStruct Intersect_With(const RectangleStruct& rectangle, int* x = nullptr, int* y = nullptr) const;

	inline int Size() const { return Width * Height; }

	inline Point2D Center_Point() const { return Point2D(X + (Width / 2), Y + (Height / 2)); }
	inline Point2D Top_Left() const { return Point2D(X, Y); }
	inline Point2D Top_Right() const { return Point2D(X + Width, Y); }
	inline Point2D Bottom_Left() const { return Point2D(X, Y + Height); }
	inline Point2D Bottom_Right() const { return Point2D(X + Width, Y + Height); }
	inline Point2D Top_Center() const { return Point2D((X + Width) / 2, Y); }
	inline Point2D Bottom_Center() const { return Point2D((X + Width) / 2, Height); }
	inline Point2D Left_Center() const { return Point2D(X, (Y + Height) / 2); }
	inline Point2D Center_Right() const { return Point2D(Width, (Y + Height) / 2); }

	inline void Reset_Position() { X = 0; Y = 0; }

	bool Is_Valid() const;

public:
	int X;
	int Y;
	int Width;
	int Height;

public:
	static const RectangleStruct Invalid;
};


const RectangleStruct Intersect(const RectangleStruct& rect1, const RectangleStruct& rect2, int* x, int* y);
inline const RectangleStruct Intersect(const RectangleStruct& rect1, const RectangleStruct& rect2) { return Intersect(rect1, rect2, nullptr, nullptr); }

const RectangleStruct Union(const RectangleStruct& rect1, const RectangleStruct& rect2);


inline bool operator==(const RectangleStruct& left, const RectangleStruct& right)
{
	return (left.X == right.X)
		&& (left.Width == right.Width)
		&& (left.Y == right.Y)
		&& (left.Height == right.Height);
}


inline bool operator!=(const RectangleStruct& left, const RectangleStruct& right)
{
	return (left.X != right.X)
		&& (left.Width != right.Width)
		&& (left.Y != right.Y)
		&& (left.Height != right.Height);
}


inline RectangleStruct operator+(const RectangleStruct& left, const RectangleStruct& right)
{
	RectangleStruct result = left;
	RectangleStruct tmp = right;
	result += tmp;
	return result;
}


inline RectangleStruct operator-(const RectangleStruct& left, const RectangleStruct& right)
{
	RectangleStruct result = left;
	RectangleStruct tmp = right;
	result -= tmp;
	return result;
}
