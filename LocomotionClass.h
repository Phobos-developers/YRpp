#pragma once

#include <Interfaces.h>
#include <FootClass.h>
#include <Unsorted.h>
#include <YRCom.h>
#include <Drawing.h>
#include <Helpers/ComPtr.h>
#include <Helpers/CompileTime.h>

class LocomotionClass : public IPersistStream, public ILocomotion
{
public:
	class CLSIDs
	{
	public:
		static constexpr reference<CLSID const, 0x7E9A30u> const Drive {};
		static constexpr reference<CLSID const, 0x7E9AC0u> const Jumpjet {};
		static constexpr reference<CLSID const, 0x7E9A40u> const Hover {};
		static constexpr reference<CLSID const, 0x7E9AD0u> const Rocket {};
		static constexpr reference<CLSID const, 0x7E9A50u> const Tunnel {};
		static constexpr reference<CLSID const, 0x7E9A60u> const Walk {};
		static constexpr reference<CLSID const, 0x7E9A70u> const Droppod {};
		static constexpr reference<CLSID const, 0x7E9A80u> const Fly {};
		static constexpr reference<CLSID const, 0x7E9A90u> const Teleport {};
		static constexpr reference<CLSID const, 0x7E9AA0u> const Mech {};
		static constexpr reference<CLSID const, 0x7E9AB0u> const Ship {};
	};
	//IUnknown
	virtual HRESULT __stdcall QueryInterface(REFIID iid, void** ppvObject) R0;
	virtual ULONG __stdcall AddRef() R0;
	virtual ULONG __stdcall Release() R0;

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//IPersistStream
	virtual HRESULT __stdcall IsDirty() R0;
	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) R0;

	virtual HRESULT __stdcall GetSizeMax(ULARGE_INTEGER* pcbSize) R0;

	virtual ~LocomotionClass() RX; // should be SDDTOR in fact
	virtual int Size() R0;

	// ILocomotion
	// virtual HRESULT __stdcall QueryInterface(REFIID iid, void** ppvObject) R0;
	// virtual ULONG __stdcall AddRef() R0;
	// virtual ULONG __stdcall Release() R0;
	virtual HRESULT __stdcall Link_To_Object(void* pointer) R0;
	virtual bool __stdcall Is_Moving() R0;
	virtual CoordStruct* __stdcall Destination(CoordStruct* pcoord) R0;
	virtual CoordStruct* __stdcall Head_To_Coord(CoordStruct* pcoord) R0;
	virtual Move __stdcall Can_Enter_Cell(CellStruct cell) RT(Move);
	virtual bool __stdcall Is_To_Have_Shadow() R0;
	virtual Matrix3D __stdcall Draw_Matrix(VoxelIndexKey* pIndex) RT(Matrix3D);
	virtual Matrix3D __stdcall Shadow_Matrix(VoxelIndexKey* pIndex) RT(Matrix3D);
	virtual Point2D* __stdcall Draw_Point(Point2D* pPoint) R0;
	virtual Point2D* __stdcall Shadow_Point(Point2D* pPoint) R0;
	virtual VisualType __stdcall Visual_Character(VARIANT_BOOL unused) RT(VisualType);
	virtual int __stdcall Z_Adjust() R0;
	virtual ZGradient __stdcall Z_Gradient() RT(ZGradient);
	virtual bool __stdcall Process() R0;
	virtual void __stdcall Move_To(CoordStruct to) RX;
	virtual void __stdcall Stop_Moving() RX;
	virtual void __stdcall Do_Turn(DirStruct coord) RX;
	virtual void __stdcall Unlimbo() RX;
	virtual void __stdcall Tilt_Pitch_AI() RX;
	virtual bool __stdcall Power_On() R0;
	virtual bool __stdcall Power_Off() R0;
	virtual bool __stdcall Is_Powered() R0;
	virtual bool __stdcall Is_Ion_Sensitive() R0;
	virtual bool __stdcall Push(DirStruct dir) R0;
	virtual bool __stdcall Shove(DirStruct dir) R0;
	virtual void __stdcall Force_Track(int track, CoordStruct coord) RX;
	virtual Layer __stdcall In_Which_Layer() RT(Layer);
	virtual void __stdcall Force_Immediate_Destination(CoordStruct coord) RX;
	virtual void __stdcall Force_New_Slope(int ramp) RX;
	virtual bool __stdcall Is_Moving_Now() R0;
	virtual int __stdcall Apparent_Speed() R0;
	virtual int __stdcall Drawing_Code() R0;
	virtual FireError __stdcall Can_Fire() RT(FireError);
	virtual int __stdcall Get_Status() R0;
	virtual void __stdcall Acquire_Hunter_Seeker_Target() RX;
	virtual bool __stdcall Is_Surfacing() R0;
	virtual void __stdcall Mark_All_Occupation_Bits(int mark) RX;
	virtual bool __stdcall Is_Moving_Here(CoordStruct to) R0;
	virtual bool __stdcall Will_Jump_Tracks() R0;
	virtual bool __stdcall Is_Really_Moving_Now() R0;
	virtual void __stdcall Stop_Movement_Animation() RX;
	virtual void __stdcall Clear_Coords() RX;
	virtual void __stdcall Lock() RX;
	virtual void __stdcall Unlock() RX;
	virtual int __stdcall Get_Track_Number() R0;
	virtual int __stdcall Get_Track_Index() R0;
	virtual int __stdcall Get_Speed_Accum() R0;

	// Non virtuals
	static HRESULT TryPiggyback(IPiggyback** Piggy, ILocomotion** Loco)
	{ PUSH_VAR32(Loco); SET_REG32(ECX, Piggy); CALL(0x45AF20); }

	static HRESULT CreateInstance(ILocomotion** ppv, const CLSID* rclsid, LPUNKNOWN pUnkOuter, DWORD dwClsContext)
	{ PUSH_VAR32(dwClsContext); PUSH_VAR32(pUnkOuter); PUSH_VAR32(rclsid); SET_REG32(ECX, ppv); CALL(0x41C250); }

	// these two are identical, why do they both exist...
	static void AddRef1(LocomotionClass** Loco)
	{ SET_REG32(ECX, Loco); CALL(0x45A170); }

	static void AddRef2(LocomotionClass** Loco)
	{ SET_REG32(ECX, Loco); CALL(0x6CE270); }

	static void ChangeLocomotorTo(FootClass* Object, const CLSID& clsid)
	{
		// remember the current one
		YRComPtr<ILocomotion> Original(Object->Locomotor);

		// create a new locomotor and link it
		auto NewLoco = CreateInstance(clsid);
		NewLoco->Link_To_Object(Object);

		// get piggy interface and piggy original
		YRComPtr<IPiggyback> Piggy(NewLoco);
		Piggy->Begin_Piggyback(Original.get());

		// replace the current locomotor
		Object->Locomotor = std::move(NewLoco);
	}

	// creates a new instance by class ID. returns a pointer to ILocomotion
	static YRComPtr<ILocomotion> CreateInstance(const CLSID& rclsid)
	{
		return YRComPtr<ILocomotion>(rclsid, nullptr,
			CLSCTX_INPROC_SERVER | CLSCTX_INPROC_HANDLER | CLSCTX_LOCAL_SERVER);
	}

	// finds out whether a locomotor is currently piggybacking and restores
	// the original locomotor. this function ignores Is_Ok_To_End().
	static bool End_Piggyback(YRComPtr<ILocomotion>& pLoco)
	{
		if (!pLoco)
		{
			Game::RaiseError(E_POINTER);
		}

		if (YRComPtr<IPiggyback> pPiggy = pLoco)
		{
			if (pPiggy->Is_Piggybacking())
			{
				// this frees the current locomotor
				pLoco.reset(nullptr);

				// this restores the old one
				auto res = pPiggy->End_Piggyback(pLoco.pointer_to());
				if (FAILED(res))
				{
					Game::RaiseError(res);
				}
				return (res == S_OK);
			}
		}

		return false;
	}

	//Constructors
	LocomotionClass(LocomotionClass& another) { JMP_THIS(0x55A6C0); }

protected:
	explicit __forceinline LocomotionClass(noinit_t)  noexcept
	{
	}

	//Properties
public:

	FootClass* Owner;
	FootClass* LinkedTo;
	bool Powered;
	bool Dirty;
	int RefCount;
};
