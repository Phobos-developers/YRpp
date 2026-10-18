/*
	Animations
*/

#pragma once

#include <ObjectClass.h>
#include <AnimTypeClass.h>
#include <BounceClass.h>
#include <StageClass.h>

//forward declarations
class AnimTypeClass;
class BulletClass;
class HouseClass;
class LightConvertClass;

class NOVTABLE AnimClass : public ObjectClass
{
public:
	static const AbstractType AbsID = AbstractType::Anim;

	//Static
	DEFINE_REFERENCE(DynamicVectorClass<AnimClass*>, Array, 0xA8E9A8u)

	// Local movement feedback animations, kept outside the synchronized Array.
	DEFINE_REFERENCE(DynamicVectorClass<AnimClass*>, MoveFlashes, 0xA83E00u)

	//IPersist
	virtual HRESULT __stdcall GetClassID(CLSID* pClassID) R0;

	//IPersistStream
	virtual HRESULT __stdcall Save(IStream* pStm, BOOL fClearDirty) R0;

	//Destructor
	virtual ~AnimClass() RX;

	//AbstractClass
	virtual void PointerExpired(AbstractClass* pAbstract, bool detachFromAll) override JMP_THIS(0x425150);
	virtual AbstractType WhatAmI() const RT(AbstractType);
	virtual int	Size() const R0;

	//ObjectClass
	//AnimClass
	virtual int AnimExtras() R0; // tumbling for IsMeteor and Bouncer anims
	virtual int GetEnd() const R0; //End tag from the AnimType

	void SetOwnerObject(ObjectClass *pOwner)
		{ JMP_THIS(0x424B50); }

	void Pause() {
		this->Paused = true;
		this->Unpaused = false;
		this->PausedAnimFrame = this->Animation.Value;
	}

	void Unpause() {
		this->Paused = false;
		this->Unpaused = true;
	}

	//Constructor
	// TODO fix
	AnimClass(AnimTypeClass* pAnimType, const CoordStruct& Location, int LoopDelay = 0,
		int LoopCount = 1, DWORD flags = 0x600, int ForceZAdjust = 0, bool reverse = false) noexcept
		: AnimClass(noinit_t())
	{ JMP_THIS(0x421EA0); }

	// Anim start logic: sound event handling, tiberium chain reaction etc.
	void Start() const
		{ JMP_THIS(0x424CE0); }

	// Anim midpoint logic: particle spawning, smudges etc.
	bool Middle() const
		{ JMP_THIS(0x424F00); }

protected:
	explicit __forceinline AnimClass(noinit_t) noexcept
		: ObjectClass(noinit_t())
	{ }

	//===========================================================================
	//===== Properties ==========================================================
	//===========================================================================

public:

	DECLARE_PROPERTY(StageClass, Animation);
	AnimTypeClass* Type; // AnimTypeClass.
	ObjectClass * OwnerObject; // Set by AnimClass::SetOwnerObject (0x424B50)
	DWORD unknown_D0; // Only set in CTOR/DTOR, never used. Used in Phobos for storing AnimExt::ExtData pointer.
	LightConvertClass* LightConvert; // Palette from building for building animations.
	int LightConvertIndex; // assert(ColorScheme::Array[this->LightConvertIndex] == this->LightConvert);
	char PaletteName[0x20]; // Filename set for destroy anims
	int TintColor;
	int ZAdjust;
	int YSortAdjust; // Same as YSortAdjust from Type
	CoordStruct FlamingGuyCoords; // The destination the anim tries to reach
	int FlamingGuyRetries; // Number of failed attemts to reach water. the random destination generator stops if >= 7
	bool IsBuildingAnim; // Whether this anim will invalidate on buildings, and whether it's tintable
	bool UnderTemporal; // Ttemporal'd building's active anims
	bool Paused; // If paused, does not advance anim, does not deliver damage
	bool Unpaused; // Set when unpaused
	int PausedAnimFrame; // The animation value when paused
	bool Reverse; // Anim is forced to be played from end to start
	PROTECTED_PROPERTY(BYTE, padding_121[0x7]);
	DECLARE_PROPERTY(BounceClass, Bounce);
	BYTE TranslucencyLevel; // On a scale of 1 - 100
	bool TimeToDie; // Or something to that effect, set just before UnInit
	BulletClass* AttachedBullet;
	HouseClass* Owner; // Used for remap (AltPalette)
	int LoopDelay; // Randomized value, depending on RandomLoopDelay
	double Accum; // Stores accumulated fractional animation damage and gets added to Type->Damage if at least 1.0 or above. Defaults to 1.0.
	BlitterFlags AnimFlags; // Argument that's 0x600 most of the time
	bool HasExtras; // Enables IsMeteor and Bouncer special behavior (AnimExtras)
	byte RemainingIterations; // Defaulted to deleteAfterIterations, when reaches zero, UnInit() is called
	bool UseCellLightConvert; // If set to true checks cell at render coords and uses its LightConvert if available
	bool DeleteOnMapCleanup;  // Set on tile anims, anims are deleted in MapClass::Overpass() (0x568BB0)
	bool IsInert; // Not official name, only set to true on TActionClass-created animations and prevents sounds, damage and TiberiumChainReaction from working.
	bool IsFogged;
	bool FlamingGuyExpire; // Finish animation and remove
	bool UnableToContinue; // Set when something prevents the anim from going on: cell occupied, veins destoyed or unit gone, ...
	bool SkipProcessOnce; // Set in constructor, cleared during Update. skips damage, veins, tiberium chain reaction and animation progress
	bool Invisible; // Don't draw, but Update state anyway
	bool PowerOff; // Powered animation has no power
	PROTECTED_PROPERTY(BYTE, unused_19F);
	DECLARE_PROPERTY(AudioController, StartSoundAudioController);
	DECLARE_PROPERTY(AudioController, StopSoundAudioController);
};

static_assert(sizeof(AnimClass) == 0x1C8);
