#pragma once

#include <Interfaces.h>
#include <FootClass.h>
#include <Unsorted.h>
#include <YRCom.h>
#include <Drawing.h>
#include <Helpers/CompileTime.h>

class LocomotionClass : public IPersistStream, public ILocomotion
{
public:
	class CLSIDs
	{
	public:
		DEFINE_REFERENCE(CLSID const, Drive, 0x7E9A30u)
		DEFINE_REFERENCE(CLSID const, Hover, 0x7E9A40u)
		DEFINE_REFERENCE(CLSID const, Tunnel, 0x7E9A50u)
		DEFINE_REFERENCE(CLSID const, Walk, 0x7E9A60u)
		DEFINE_REFERENCE(CLSID const, Droppod, 0x7E9A70u)
		DEFINE_REFERENCE(CLSID const, Fly, 0x7E9A80u)
		DEFINE_REFERENCE(CLSID const, Teleport, 0x7E9A90u)
		DEFINE_REFERENCE(CLSID const, Mech, 0x7E9AA0u)
		DEFINE_REFERENCE(CLSID const, Ship, 0x7E9AB0u)
		DEFINE_REFERENCE(CLSID const, Jumpjet, 0x7E9AC0u)
		DEFINE_REFERENCE(CLSID const, Rocket, 0x7E9AD0u)
	};

	//IUnknown
	virtual HRESULT __stdcall QueryInterface(REFIID iid, LPVOID* ppvObject) { JMP_STD(0x55A9B0); }
	virtual ULONG __stdcall AddRef() { JMP_STD(0x55A950); }
	virtual ULONG __stdcall Release() { JMP_STD(0x55A970); }

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) = 0;

	//IPersistStream
	virtual HRESULT __stdcall IsDirty() { JMP_STD(0x4B4C30); }
	virtual HRESULT __stdcall Load(IStream* pStm) { JMP_STD(0x55AAC0); } // for some reason was 0x4C9150 aka purecall
	virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) { JMP_STD(0x55AA60); }

	virtual HRESULT __stdcall GetSizeMax(ULARGE_INTEGER* pcbSize) { JMP_STD(0x55AB40); }

	virtual ~LocomotionClass() = default;
	virtual int Size() = 0;

	// ILocomotion
	// virtual HRESULT __stdcall QueryInterface(REFIID iid, void** ppvObject) { JMP_STD(0x4D0510); }
	// virtual ULONG __stdcall AddRef() { JMP_STD(0x4D0520); }
	// virtual ULONG __stdcall Release() { JMP_STD(0x4D0530); }
	virtual HRESULT __stdcall Link_To_Object(void* pointer) { JMP_STD(0x55A710); }
	virtual bool __stdcall Is_Moving() { JMP_STD(0x55ACD0); }
	virtual CoordStruct __stdcall Destination() { JMP_STD(0x55AC70); }
	virtual CoordStruct __stdcall Head_To_Coord() { JMP_STD(0x55ACA0); }
	virtual Move __stdcall Can_Enter_Cell(CellStruct cell) { JMP_STD(0x55ABF0); }
	virtual bool __stdcall Is_To_Have_Shadow() { JMP_STD(0x55ABE0); }
	virtual Matrix3D __stdcall Draw_Matrix(VoxelIndexKey* pIndex) { JMP_STD(0x55A730); }
	virtual Matrix3D __stdcall Shadow_Matrix(VoxelIndexKey* pIndex) { JMP_STD(0x55A7D0); }
	virtual Point2D __stdcall Draw_Point() { JMP_STD(0x55ABD0); }
	virtual Point2D __stdcall Shadow_Point() { JMP_STD(0x55A8C0); }
	virtual VisualType __stdcall Visual_Character(bool raw) { JMP_STD(0x55ABC0); }
	virtual int __stdcall Z_Adjust() { JMP_STD(0x55ABA0); }
	virtual ZGradient __stdcall Z_Gradient() { JMP_STD(0x55ABB0); }
	virtual bool __stdcall Process() { JMP_STD(0x55AC60); }
	virtual void __stdcall Move_To(CoordStruct to) { JMP_STD(0x55AC50); }
	virtual void __stdcall Stop_Moving() { JMP_STD(0x55AC40); }
	virtual void __stdcall Do_Turn(DirStruct coord) { JMP_STD(0x55AC30); }
	virtual void __stdcall Unlimbo() { JMP_STD(0x55AC20); }
	virtual void __stdcall Tilt_Pitch_AI() { JMP_STD(0x55AB90); }
	virtual bool __stdcall Power_On() { JMP_STD(0x55A8F0); }
	virtual bool __stdcall Power_Off() { JMP_STD(0x55A910); }
	virtual bool __stdcall Is_Powered() { JMP_STD(0x55A930); }
	virtual bool __stdcall Is_Ion_Sensitive() { JMP_STD(0x55A940); }
	virtual bool __stdcall Push(DirStruct dir) { JMP_STD(0x55AB70); }
	virtual bool __stdcall Shove(DirStruct dir) { JMP_STD(0x55AB80); }
	virtual void __stdcall Force_Track(int track, CoordStruct coord) { JMP_STD(0x55AC10); }
	virtual Layer __stdcall In_Which_Layer() = 0;
	virtual void __stdcall Force_Immediate_Destination(CoordStruct coord) { JMP_STD(0x55AC00); }
	virtual void __stdcall Force_New_Slope(int ramp) { JMP_STD(0x55ACE0); }
	virtual bool __stdcall Is_Moving_Now() { JMP_STD(0x4B6610); }
	virtual int __stdcall Apparent_Speed() { JMP_STD(0x55AD10); }
	virtual int __stdcall Drawing_Code() { JMP_STD(0x55ACF0); }
	virtual FireError __stdcall Can_Fire() { JMP_STD(0x55AD00); }
	virtual int __stdcall Get_Status() { JMP_STD(0x4B4C60); }
	virtual void __stdcall Acquire_Hunter_Seeker_Target() { JMP_STD(0x4B4C70); }
	virtual bool __stdcall Is_Surfacing() { JMP_STD(0x4B4C80); }
	virtual void __stdcall Mark_All_Occupation_Bits(MarkType mark) { JMP_STD(0x4B6620); }
	virtual bool __stdcall Is_Moving_Here(CoordStruct to) { JMP_STD(0x4B6630); }
	virtual bool __stdcall Will_Jump_Tracks() { JMP_STD(0x4B6640); }
	virtual bool __stdcall Is_Really_Moving_Now() { JMP_STD(0x4B4C50); }
	virtual void __stdcall Stop_Movement_Animation() { JMP_STD(0x4B4C90); }
	virtual void __stdcall Limbo() { JMP_STD(0x4B4CA0); }
	virtual void __stdcall Lock() { JMP_STD(0x4B6650); }
	virtual void __stdcall Unlock() { JMP_STD(0x4B6660); }
	virtual int __stdcall Get_Track_Number() { JMP_STD(0x4B6670); }
	virtual int __stdcall Get_Track_Index() { JMP_STD(0x4B6680); }
	virtual int __stdcall Get_Speed_Accum() { JMP_STD(0x4B6690); }

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
		ILocomotionPtr Original(Object->Locomotor);

		// create a new locomotor and link it
		auto NewLoco = CreateInstance(clsid);
		NewLoco->Link_To_Object(Object);

		// get piggy interface and piggy original
		IPiggybackPtr Piggy(NewLoco);
		Piggy->Begin_Piggyback(Original);

		// replace the current locomotor
		Object->Locomotor = NewLoco;
	}

	// creates a new instance by class ID. returns a pointer to ILocomotion
	static ILocomotionPtr CreateInstance(const CLSID& rclsid)
	{
		return ILocomotionPtr(rclsid, nullptr,
			CLSCTX_INPROC_SERVER | CLSCTX_INPROC_HANDLER | CLSCTX_LOCAL_SERVER);
	}

	// finds out whether a locomotor is currently piggybacking and restores
	// the original locomotor. this function ignores Is_Ok_To_End().
	static bool End_Piggyback(ILocomotionPtr& pLoco)
	{
		if (!pLoco)
			_com_issue_error(E_POINTER);

		if (IPiggybackPtr pPiggy = pLoco)
		{
			if (pPiggy->Is_Piggybacking())
			{
				// _com_ptr_t releases the old pointer automatically,
				// so we just use it without resetting it
				auto res = pPiggy->End_Piggyback(&pLoco);
				if (FAILED(res))
					_com_issue_error(res);

				return (res == S_OK);
			}
		}

		return false;
	}

	//Constructors
	LocomotionClass() { JMP_THIS(0x55A6C0); }

protected:
	explicit __forceinline LocomotionClass(noinit_t) noexcept { }

	//Properties
public:

	FootClass* Owner;
	FootClass* LinkedTo;
	bool Powered;
	bool Dirty;
	int RefCount;
};

namespace detail
{
	template<typename Base>
	concept LocoIsDerived = std::derived_from<Base, LocomotionClass> && !std::is_same_v<LocomotionClass, Base>;

	template<typename Base>
	concept LocoHasILocoVtbl = requires { { Base::ILocoVTable }->std::convertible_to<const uintptr_t>; };
}

template<typename T>
concept LocoCastEligible = std::is_pointer_v<T> && detail::LocoIsDerived<std::remove_cvref_t<std::remove_const_t<std::remove_pointer_t<T>>>>;


template <LocoCastEligible T>
__forceinline T locomotion_cast(ILocomotion* iLoco)
{
	using Base = std::remove_cvref_t<std::remove_const_t<std::remove_pointer_t<T>>>;

	if constexpr (detail::LocoHasILocoVtbl<Base>)
	{
		return VTable::Get(iLoco) == Base::ILocoVTable ? static_cast<T>(iLoco) : nullptr;
	}
	else
	{
		CLSID clsid;
		IPersistPtr comPersist = iLoco;

		return (SUCCEEDED(comPersist->GetClassID(&clsid)) && clsid == __uuidof(Base)) ? static_cast<T>(iLoco) : nullptr;
	}
}

template<LocoCastEligible T>
__forceinline T locomotion_cast(ILocomotionPtr& comLoco)
{
	return locomotion_cast<T>(comLoco.GetInterfacePtr());
/*
//	IPersistPtr comPersist = comLoco;
//	CLSID clsid;
//	if (SUCCEEDED(comPersist->GetClassID(&clsid)) && clsid == __uuidof(Base))
//		return static_cast<T>(comLoco.GetInterfacePtr());
*/
}

struct TurnTrackType
{
	char NormalTrackStructIndex;
	char ShortTrackStructIndex;
	int Face;
	int Flag;
};

struct TrackType
{
	Point2D Point;
	int Face;
};

struct RawTrackType
{
	TrackType* TrackPoint;
	int JumpIndex;
	int EntryIndex;
	int CellIndex;
};
