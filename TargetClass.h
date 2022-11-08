#pragma once

// Why should we call it TargetClass instead of xTargetClass:
// https://github.com/electronicarts/CnC_Remastered_Collection/blob/master/REDALERT/TARGET.H#L95
// https://github.com/electronicarts/CnC_Remastered_Collection/blob/master/REDALERT/TARGET.H#L145

class AbstractClass;
class AbstractTypeClass;
class ObjectClass;
class TagClass;
class TagTypeClass;
class TriggerClass;
class TriggerTypeClass;
class TeamClass;
class TeamTypeClass;
class TerrainClass;
class HouseClass;
class TechnoClass;
class TechnoTypeClass;
class InfantryClass;
class UnitClass;
class AircraftClass;
class BuildingClass;
class FootClass;
class BulletClass;
class AnimClass;

#include <CellClass.h>
#include <MapClass.h>

#pragma pack(push, 1)
class TargetClass
{
public:
	explicit TargetClass() noexcept : m_ID { 0 }, m_RTTI { 0 } { }
	explicit TargetClass(AbstractClass* pItem) noexcept
	{
		JMP_THIS(0x6E6AB0);
		// if (pItem)
		// {
		// 	if (pItem->WhatAmI() == AbstractType::Cell)
		// 	{
		// 		const auto pCell = static_cast<CellClass*>(pItem);
		// 
		// 		m_RTTI = static_cast<unsigned char>(AbstractType::Cell);
		// 		m_ID = pCell->MapCoords.X + 1000 * pCell->MapCoords.Y;
		// 	}
		// 	else
		// 	{
		// 		m_RTTI = static_cast<unsigned char>(AbstractType::Abstract);
		// 		m_ID = pItem->Fetch_ID();
		// 	}
		// }
		// else
		// {
		// 	m_RTTI = 0;
		// 	m_ID = 0;
		// }
	}
	explicit TargetClass(const CellStruct& cell)
	{
		JMP_THIS(0x6E6B20);
		// if (cell == CellStruct::Empty)
		// 	m_RTTI = 0;
		// else
		// {
		// 	m_RTTI = static_cast<unsigned char>(AbstractType::Cell);
		// 	m_ID = cell.X + 1000 * cell.Y;
		// }
	}
	explicit TargetClass(const CoordStruct& coord)
	{
		JMP_THIS(0x6E6B70);
		// m_RTTI = static_cast<unsigned char>(AbstractType::Cell);
		// m_ID = coord.X / 256 + 1000 * (coord.Y / 256);
	}

	// This one is just used to tell you what the game did.
	// We cannot use dynamic_cast here so just don't use this template
	// 
	// template<typename T>
	// T* As()
	// {
	// 	if constexpr (T::AbsID == AbstractType::Abstract)
	// 	{
	// 		if (m_RTTI != static_cast<int>(AbstractType::Abstract))
	// 			return nullptr;
	// 
	// 		if (AbstractClass::TargetIndex->IsPresent(m_ID))
	// 			return dynamic_cast<T*>(this);
	// 	}
	// 	else if constexpr (T::AbsID == AbstractType::Cell)
	// 	{
	// 		if (m_RTTI != static_cast<int>(AbstractType::Cell))
	// 			return nullptr;
	// 
	// 		CellStruct cell { m_ID % 1000,m_ID / 1000 };
	// 		return MapClass::Instance->GetCellAt(cell);
	// 	}
	// 	else
	// 	{
	// 		static_assert(false);
	// 	}
	// }

	// We provide three convertion here
	// [explicit] T* As()
	// [explicit] T* As_T()
	// [implicit] operator T*()

	// template helper
	template<typename T> T* As() { static_assert(false); }

#define DECLARE_CONVENTION_(name, T, addr) \
	template<> T* As() { JMP_THIS(addr); } \
	T* As_##name() { JMP_THIS(addr); } \
	operator T*() { return As_##name(); }
#define DECLARE_CONVENTION(name, addr) DECLARE_CONVENTION_(name, name ## Class, addr)

	DECLARE_CONVENTION(AbstractType, 0x6E6BB0);
	DECLARE_CONVENTION(Tag, 0x6E6C80);
	DECLARE_CONVENTION(TagType, 0x6E6D50);
	DECLARE_CONVENTION(Abstract, 0x6E6E20);
	DECLARE_CONVENTION(Techno, 0x6E6F20);
	DECLARE_CONVENTION(Object, 0x6E6FF0);
	DECLARE_CONVENTION(Foot, 0x6E70C0);
	DECLARE_CONVENTION(Trigger, 0x6E7190);
	DECLARE_CONVENTION(House, 0x6E7260);
	DECLARE_CONVENTION(TechnoType, 0x6E7330);
	DECLARE_CONVENTION(TriggerType, 0x6E7400);
	DECLARE_CONVENTION(TeamType, 0x6E74D0);
	DECLARE_CONVENTION(Terrain, 0x6E75A0);
	DECLARE_CONVENTION(Bullet, 0x6E7670);
	DECLARE_CONVENTION(Anim, 0x6E7740);
	DECLARE_CONVENTION(Team, 0x6E7810);
	DECLARE_CONVENTION(Infantry, 0x6E78E0);
	DECLARE_CONVENTION(Unit, 0x6E79B0);
	DECLARE_CONVENTION(Building, 0x6E7A80);
	DECLARE_CONVENTION(Aircraft, 0x6E7B50);
	DECLARE_CONVENTION(Cell, 0x6E7C20);

#undef DECLARE_CONVENTION
#undef DECLARE_CONVENTION_

	int m_ID;
	unsigned char m_RTTI;
};
#pragma pack(pop)
