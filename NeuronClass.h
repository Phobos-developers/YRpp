/*
	I have not the slightest idea what this is good for...
*/

#ifndef NEURON_H
#define NEURON_H

#include <AbstractClass.h>

class NeuronClass : public AbstractClass
{
public:
	//IPersist
	virtual HRESULT _stdcall GetClassID(CLSID* pClassID) R0;

	//IPersistStream
	virtual HRESULT _stdcall Load(IStream* pStm) R0;
	virtual HRESULT _stdcall Save(IStream* pStm,BOOL fClearDirty) R0;

	//Destructor
	virtual ~NeuronClass() RX;

	//AbstractClass
	virtual eAbstractType WhatAmI() R0;

	virtual int Size() R0;

	//Constructor
	NeuronClass() : AbstractClass(false)
		JMP_THIS(0x43A350);

protected:
	NeuronClass(bool X) : AbstractClass(X) { }

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================
	PROPERTY(void*,			unknown_ptr_24);
	PROPERTY(void*,			unknown_ptr_28);
	PROPERTY(void*,			unknown_ptr_2C);
	PROPERTY_STRUCT(TimerStruct,	unknown_timer_30);
};

//Even more questions marks on the use of this... >.<
class BrainClass
{
public:
	virtual ~BrainClass() RX;

	BrainClass()
		{ THISCALL(0x43A600); }

	//Properties
	PROPERTY(VectorClass<NeuronClass*>, Neurons);	//???
};

#endif