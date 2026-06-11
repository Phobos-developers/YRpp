#pragma once
#include <LocomotionClass.h>

class NOVTABLE DropPodLocomotionClass : public LocomotionClass, public IPiggyback
{
public:
	static constexpr uintptr_t ILocoVTable = 0x7E8278;
	//IUnknown
	virtual HRESULT __stdcall QueryInterface(REFIID iid, void** ppvObject) R0;
	virtual ULONG __stdcall AddRef() R0;
	virtual ULONG __stdcall Release() R0;

	//IPiggyback
	virtual HRESULT __stdcall Begin_Piggyback(ILocomotion* pointer) R0;
	virtual HRESULT __stdcall End_Piggyback(ILocomotion** pointer) R0;
	virtual bool __stdcall Is_Ok_To_End() R0;
	virtual HRESULT __stdcall Piggyback_CLSID(GUID* classid) R0;
	virtual bool __stdcall Is_Piggybacking() R0;

	//ILocomotion
	virtual bool __stdcall Is_Moving() R0;
	virtual CoordStruct __stdcall Destination() RT(CoordStruct);
	virtual bool __stdcall Process() R0;
	virtual void __stdcall Move_To(CoordStruct to) RX;
	virtual void __stdcall Stop_Moving() RX;
	virtual int __stdcall Drawing_Code() R0;

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//IPersistStream
	virtual HRESULT __stdcall Load(IStream* pStm) R0;
	virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) R0;

	//Destructor
	virtual ~DropPodLocomotionClass() RX;

	//LocomotionClass
	virtual	int Size() R0;

	//Constructor
	DropPodLocomotionClass()
		: DropPodLocomotionClass(noinit_t())
	{
		JMP_THIS(0x4B5AB0);
	}

protected:
	explicit __forceinline DropPodLocomotionClass(noinit_t)
		: LocomotionClass(noinit_t())
	{}

public:
	bool OutOfMap;
	CoordStruct DestinationCoords;
	ILocomotionPtr Piggybackee;
};

static_assert(sizeof(DropPodLocomotionClass) == 0x30);
