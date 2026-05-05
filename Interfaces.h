#pragma once

#include <windows.h>
#include <GeneralDefinitions.h>

#include <comdef.h>

__interface __declspec(uuid("5FF0CA70-8B12-11D1-B708-00A024DDAFD1"))
ISwizzle : IUnknown
{
	virtual HRESULT __stdcall Reset() = 0;
	virtual HRESULT __stdcall Swizzle(void** pointer) = 0;
	virtual HRESULT __stdcall Fetch_Swizzle_ID(void* pointer, long* id) const = 0;
	virtual HRESULT __stdcall Here_I_Am(long id, void* pointer) = 0;
	virtual HRESULT __stdcall Save_Interface(IStream* stream, IUnknown* pointer) = 0;
	virtual HRESULT __stdcall Load_Interface(IStream* stream, GUID* riid, void** pointer) = 0;
	virtual HRESULT __stdcall Get_Save_Size(int* size) const = 0;
};

_COM_SMARTPTR_TYPEDEF(ISwizzle, __uuidof(ISwizzle));

__interface __declspec(uuid("96F02EC3-6FE8-11D1-B6FD-00A024DDAFD1"))
IApplication : IUnknown
{
	virtual HRESULT __stdcall FullName(BSTR* retval) = 0;
	virtual HRESULT __stdcall Name(BSTR* retval) = 0;
	virtual HRESULT __stdcall Quit() = 0;
	virtual HRESULT __stdcall ScenarioName(BSTR* retval) = 0;
	virtual HRESULT __stdcall FrameCount(long* retval) = 0;
	virtual HRESULT __stdcall Swizzle_Interface(ISwizzle** pVal) = 0;
};

_COM_SMARTPTR_TYPEDEF(IApplication, __uuidof(IApplication));

__interface INoticeSource
{
	virtual void __stdcall INoticeSource_Unknown() = 0;
};

__interface INoticeSink
{
	virtual bool __stdcall INoticeSink_Unknown(DWORD dwUnknown) = 0;
};

__interface __declspec(uuid("170DAC82-12E4-11D2-8175-006008055BB5"))
IRTTITypeInfo : IUnknown
{
	virtual AbstractType __stdcall What_Am_I() const = 0;
	virtual int __stdcall Fetch_ID() const = 0;
	virtual void __stdcall Create_ID() = 0;
};

_COM_SMARTPTR_TYPEDEF(IRTTITypeInfo, __uuidof(IRTTITypeInfo));

__interface __declspec(uuid("96F02EC4-6FE8-11D1-B6FD-00A024DDAFD1"))
IAIHouse : IUnknown
{
	virtual void __stdcall Link_House(void* unknown) const = 0;
	virtual void __stdcall AI(int* unknown) = 0;
};

_COM_SMARTPTR_TYPEDEF(IAIHouse, __uuidof(IAIHouse));

__interface __declspec(uuid("941582E0-86DA-11D1-B706-00A024DDAFD1"))
IHouse : IUnknown
{
	virtual long __stdcall				ID_Number() const = 0;
	virtual BSTR __stdcall				Name() const = 0;
	virtual IApplication* __stdcall		Get_Application() = 0;
	virtual long __stdcall				Available_Money() const = 0;
	virtual long __stdcall				Available_Storage() const = 0;
	virtual long __stdcall				Power_Output() const = 0;
	virtual long __stdcall				Power_Drain() const = 0;
	virtual long __stdcall				Category_Quantity(Category category) const = 0;
	virtual long __stdcall				Category_Power(Category category) const = 0;
	virtual CellStruct __stdcall		Base_Center() const = 0;
	virtual HRESULT __stdcall			Fire_Sale() const = 0;
	virtual HRESULT __stdcall			All_To_Hunt() = 0;
};

_COM_SMARTPTR_TYPEDEF(IHouse, __uuidof(IHouse));

__interface __declspec(uuid("CAACF210-86E3-11D1-B706-00A024DDAFD1"))
IPublicHouse : IUnknown
{
	virtual long __stdcall			ID_Number() const = 0;
	virtual BSTR __stdcall			Name() const = 0;
	virtual long __stdcall			Apparent_Category_Quantity(Category category) const = 0;
	virtual long __stdcall			Apparent_Category_Power(Category category) const = 0;
	virtual CellStruct __stdcall	Apparent_Base_Center() const = 0;
	virtual bool __stdcall			Is_Powered() const = 0;
};

_COM_SMARTPTR_TYPEDEF(IPublicHouse, __uuidof(IPublicHouse));

/*
typedef struct tagCONNECTDATA
{
	IUnknown* pUnk;
	unsigned long dwCookie;
}	CONNECTDATA;

__interface __declspec(uuid("B196B287-BAB4-101A-B69C-00AA00341D07"))
IEnumConnections : IUnknown
{
	virtual HRESULT __stdcall RemoteNext(unsigned long cConnections, CONNECTDATA* rgcd, unsigned long* pcFetched) = 0;
	virtual HRESULT __stdcall Skip(unsigned long cConnections) = 0;
	virtual HRESULT __stdcall Reset() = 0;
	virtual HRESULT __stdcall Clone(IEnumConnections** ppEnum) = 0;
};

__interface IConnectionPointContainer;
__interface __declspec(uuid("B196B286-BAB4-101A-B69C-00AA00341D07"))
IConnectionPoint : IUnknown
{
	virtual HRESULT __stdcall GetConnectionInterface(GUID* pIID) = 0;
	virtual HRESULT __stdcall GetConnectionPointContainer(IConnectionPointContainer** ppCPC) = 0;
	virtual HRESULT __stdcall Advise(IUnknown* pUnkSink, unsigned long* pdwCookie) = 0;
	virtual HRESULT __stdcall Unadvise(unsigned long dwCookie) = 0;
	virtual HRESULT __stdcall EnumConnections(IEnumConnections** ppEnum) = 0;
};

__interface IEnumConnectionPoints;
__interface __declspec(uuid("B196B284-BAB4-101A-B69C-00AA00341D07"))
IConnectionPointContainer : IUnknown
{
	virtual HRESULT __stdcall	EnumConnectionPoints(IEnumConnectionPoints** ppEnum) = 0;
	virtual HRESULT __stdcall	FindConnectionPoint(GUID* riid, IConnectionPoint** ppCP) = 0;
};

__interface __declspec(uuid("B196B285-BAB4-101A-B69C-00AA00341D07"))
IEnumConnectionPoints : IUnknown
{
	virtual HRESULT __stdcall RemoteNext(unsigned long cConnections, IConnectionPoint** ppCP, unsigned long* pcFetched) = 0;
	virtual HRESULT __stdcall Skip(unsigned long cConnections) = 0;
	virtual HRESULT __stdcall Reset() = 0;
	virtual HRESULT __stdcall Clone(IEnumConnectionPoints** ppEnum) = 0;
};
*/

__interface __declspec(uuid("96F02EC7-6FE8-11D1-B6FD-00A024DDAFD1"))
IGameMap : IUnknown
{
	virtual long __stdcall Is_Visible(CellStruct cell) = 0;
};

_COM_SMARTPTR_TYPEDEF(IGameMap, __uuidof(IGameMap));

__interface __declspec(uuid("0D5CD78E-6470-11D2-9B74-00104B972FE8"))
ILinkStream : IUnknown
{
	virtual HRESULT __stdcall Link_Stream(IUnknown* stream) = 0;
	virtual HRESULT __stdcall Unlink_Stream(IUnknown** stream) = 0;
};

_COM_SMARTPTR_TYPEDEF(ILinkStream, __uuidof(ILinkStream));

__interface __declspec(uuid("820F501C-4F39-11D2-9B70-00104B972FE8"))
IFlyControl : IUnknown
{
	virtual int __stdcall Landing_Altitude() = 0;
	virtual int __stdcall Landing_Direction() = 0;
	virtual long __stdcall Is_Loaded() = 0;
	virtual long __stdcall Is_Strafe() = 0;
	virtual long __stdcall Is_Fighter() = 0;
	virtual long __stdcall Is_Locked() = 0;
};

_COM_SMARTPTR_TYPEDEF(IFlyControl, __uuidof(IFlyControl));

__interface __declspec(uuid("070F3290-9841-11D1-B709-00A024DDAFD1"))
ILocomotion : IUnknown
{
	// Links object to locomotor.
	virtual HRESULT __stdcall Link_To_Object(void* pointer) = 0;

	// Sees if object is moving.
	virtual bool __stdcall Is_Moving() = 0;

	// Fetches destination coordinate.
	virtual CoordStruct __stdcall Destination() = 0;

	//  Fetches immediate (next cell) destination coordinate.
	virtual CoordStruct __stdcall Head_To_Coord() = 0;

	// Determine if specific cell can be entered.
	virtual Move __stdcall Can_Enter_Cell(CellStruct cell) = 0;

	// Should object cast a shadow?
	virtual bool __stdcall Is_To_Have_Shadow() = 0;

	// Fetch voxel draw matrix.
	virtual Matrix3D __stdcall Draw_Matrix(union VoxelIndexKey* pIndex) = 0;

	// Fetch shadow draw matrix.
	virtual Matrix3D __stdcall Shadow_Matrix(union VoxelIndexKey* pIndex) = 0;

	// Draw point center location.
	virtual Point2D __stdcall Draw_Point() = 0;

	// Shadow draw point center location.
	virtual Point2D __stdcall Shadow_Point() = 0;

	// Visual character for drawing.
	virtual VisualType __stdcall Visual_Character(bool raw) = 0;

	// Z adjust control value.
	virtual int __stdcall Z_Adjust() = 0;

	// Z gradient control value.
	virtual ZGradient __stdcall Z_Gradient() = 0;

	// Process movement of object.]
	virtual bool __stdcall Process() = 0;

	// Instruct to move to location specified.
	virtual void __stdcall Move_To(CoordStruct to) = 0;

	// Stop moving at first opportunity.
	virtual void __stdcall Stop_Moving() = 0;

	// Try to face direction specified.
	virtual void __stdcall Do_Turn(DirStruct coord) = 0;

	// Object is appearing in the world.
	virtual void __stdcall Unlimbo() = 0;

	// Special tilting AI function.
	virtual void __stdcall Tilt_Pitch_AI() = 0;

	// Locomotor becomes powered.
	virtual bool __stdcall Power_On() = 0;

	// Locomotor loses power.
	virtual bool __stdcall Power_Off() = 0;

	// Is locomotor powered?
	virtual bool __stdcall Is_Powered() = 0;

	// Is locomotor sensitive to ion storms?
	virtual bool __stdcall Is_Ion_Sensitive() = 0;

	// Push object in direction specified.
	virtual bool __stdcall Push(DirStruct dir) = 0;

	// Shove object (with spin) in direction specified.
	virtual bool __stdcall Shove(DirStruct dir) = 0;

	// Force drive track -- special case only.
	virtual void __stdcall Force_Track(int track, CoordStruct coord) = 0;

	// What display layer is it located in.
	virtual Layer __stdcall In_Which_Layer() = 0;

	// Don't use this function.
	virtual void __stdcall Force_Immediate_Destination(CoordStruct coord) = 0;

	// Force a voxel unit to a given slope. Used in cratering.
	virtual void __stdcall Force_New_Slope(int ramp) = 0;

	// Is it actually moving across the ground this very second?
	virtual bool __stdcall Is_Moving_Now() = 0;

	// Actual current speed of object expressed as leptons per game frame.
	virtual int __stdcall Apparent_Speed() = 0;

	// Special drawing feedback code (locomotor specific meaning)
	virtual int __stdcall Drawing_Code() = 0;

	// Queries if any locomotor specific state prevents the object from firing.
	virtual FireError __stdcall Can_Fire() = 0;

	// Queries the general state of the locomotor.
	virtual int __stdcall Get_Status() = 0;

	// Forces a hunter seeker droid to find a target.
	virtual void __stdcall Acquire_Hunter_Seeker_Target() = 0;

	// Is this object surfacing?
	virtual bool __stdcall Is_Surfacing() = 0;

	// Lifts all occupation bits associated with the object off the map
	virtual void __stdcall Mark_All_Occupation_Bits(MarkType mark) = 0;

	// Is this object in the process of moving into this coord.
	virtual bool __stdcall Is_Moving_Here(CoordStruct to) = 0;

	// Will this object jump tracks?
	virtual bool __stdcall Will_Jump_Tracks() = 0;

	// Infantry moving query function.
	virtual bool __stdcall Is_Really_Moving_Now() = 0;

	// Falsifies the IsReallyMoving flag in WalkLocomotionClass.
	virtual void __stdcall Stop_Movement_Animation() = 0;

	// Object is disappearing from the world.
	// Was added post TLB generation.
	virtual void __stdcall Limbo() = 0;

	// Locks the locomotor from being deleted.
	virtual void __stdcall Lock() = 0;

	// Unlocks the locomotor from being deleted.
	virtual void __stdcall Unlock() = 0;

	// Queries internal variables.
	virtual int __stdcall Get_Track_Number() = 0;

	// Queries internal variables.
	virtual int __stdcall Get_Track_Index() = 0;

	// Queries internal variables.
	virtual int __stdcall Get_Speed_Accum() = 0;
};

_COM_SMARTPTR_TYPEDEF(ILocomotion, __uuidof(ILocomotion));

// 'Piggyback' one locomotor onto another.
__interface __declspec(uuid("92FEA800-A184-11D1-B70A-00A024DDAFD1"))
IPiggyback : IUnknown
{
	// Piggybacks a locomotor onto this one.
	virtual HRESULT __stdcall Begin_Piggyback(ILocomotion* pointer) = 0;

	// End piggyback process and restore locomotor interface pointer.
	virtual HRESULT __stdcall End_Piggyback(ILocomotion** pointer) = 0;

	// Determines when should the piggybacking be ended (done automatically in FootClass::AI).
	virtual bool __stdcall Is_Ok_To_End() = 0;

	// Fetches piggybacked locomotor class ID.
	virtual HRESULT __stdcall Piggyback_CLSID(GUID* classid) = 0;

	// Is it currently piggybacking another locomotor?
	virtual bool __stdcall Is_Piggybacking() = 0;
};

_COM_SMARTPTR_TYPEDEF(IPiggyback, __uuidof(IPiggyback));
