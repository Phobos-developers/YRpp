#pragma once

#include <AbstractClass.h>
#include "VTable.h"

class ObjectClass;
class MissionClass;
class RadioClass;
class TechnoClass;
class FootClass;

// Just a proposal for the conventions :
// either we use abstract_cast everywhere or remove abstract_cast and only use specific_cast and generic_cast.
// what do you think?

template <typename T, bool SkipNullCheck = false>
__forceinline T specific_cast(AbstractClass* pAbstract) {
	using Base = std::remove_pointer_t<T>;

	return const_cast<Base*>(specific_cast<const Base*, SkipNullCheck>(static_cast<const AbstractClass*>(pAbstract)));
};

template <typename T, bool SkipNullCheck = false>
__forceinline T specific_cast(const AbstractClass* pAbstract) {
	using Base = std::remove_const_t<std::remove_pointer_t<T>>;

	static_assert(std::is_const<std::remove_pointer_t<T>>::value,
		"specific_cast: T is required to be const.");

	static_assert(std::is_base_of<AbstractClass, Base>::value,
		"specific_cast: T is required to be a type derived from AbstractClass.");

	static_assert(!std::is_abstract<Base>::value,
		"specific_cast: Abstract types (not fully implemented classes) are not supported.");

	if constexpr (!SkipNullCheck)
	{
		if (!pAbstract)
			return nullptr;
	}

	return pAbstract->WhatAmI() == Base::AbsID ? static_cast<T>(pAbstract) : nullptr;
};

template <typename T, bool SkipNullCheck = false>
__forceinline T generic_cast(AbstractClass* pAbstract) {
	using Base = std::remove_pointer_t<T>;

	return const_cast<Base*>(generic_cast<const Base*, SkipNullCheck>(static_cast<const AbstractClass*>(pAbstract)));
};

template <typename T, bool SkipNullCheck = false>
__forceinline T generic_cast(const AbstractClass* pAbstract) {
	using Base = std::remove_const_t<std::remove_pointer_t<T>>;

	static_assert(std::is_const<std::remove_pointer_t<T>>::value,
		"generic_cast: T is required to be const.");

	static_assert(std::is_base_of<ObjectClass, Base>::value
		&& std::is_abstract<Base>::value,
		"generic_cast: T is required to be an abstract type derived from ObjectClass.");

	if constexpr (!SkipNullCheck)
	{
		if (!pAbstract)
			return nullptr;
	}

	return (pAbstract->AbstractFlags & Base::AbsDerivateID) != AbstractFlags::None ? static_cast<T>(pAbstract) : nullptr;
};

template <typename T, bool SkipNullCheck = false>
__forceinline T abstract_cast(AbstractClass* pAbstract) {
	using Base = std::remove_pointer_t<T>;

	return const_cast<T>(abstract_cast<const Base*, SkipNullCheck>(static_cast<const AbstractClass*>(pAbstract)));
};

template <typename T, bool SkipNullCheck = false>
__forceinline T abstract_cast(const AbstractClass* pAbstract) {
	using Base = std::remove_const_t<std::remove_pointer_t<T>>;

	static_assert(std::is_const<std::remove_pointer_t<T>>::value,
		"abstract_cast: T is required to be const.");

	static_assert(std::is_base_of<AbstractClass, Base>::value,
		"abstract_cast: T is required to be a type derived from AbstractClass.");

	static_assert(!std::is_base_of<AbstractTypeClass, Base>::value
		|| !std::is_abstract<Base>::value,
		"abstract_cast: Abstract types (not fully implemented classes) derived from AbstractTypeClass are not suppored.");

	return specific_cast<T, SkipNullCheck>(pAbstract);
};

#define ABSTRACT_PARAM pAbstract
#define GENERIC_CAST(TypePointer, ConstQual, SkipNullCheck) \
	generic_cast<ConstQual TypePointer, SkipNullCheck>(ABSTRACT_PARAM)
#define RT_GENERIC_CAST(TypePointer, ConstQual, SkipNullCheck) \
	reinterpret_cast<ConstQual TypePointer>(GENERIC_CAST(TechnoClass*, ConstQual, SkipNullCheck))
#define ABSTRACT_CAST(TypePointer, ConstQual, SkipNullCheck, Code) \
	template <> \
	__forceinline ConstQual TypePointer abstract_cast<ConstQual TypePointer, SkipNullCheck>(ConstQual AbstractClass* ABSTRACT_PARAM) \
	{ return Code; }
#define APPLY_ABSTRACT_CAST(TypePointer) \
	ABSTRACT_CAST(TypePointer, , true, ABSTRACT_PARAM) \
	ABSTRACT_CAST(TypePointer, , false, ABSTRACT_PARAM) \
	ABSTRACT_CAST(TypePointer, const, true, ABSTRACT_PARAM) \
	ABSTRACT_CAST(TypePointer, const, false, ABSTRACT_PARAM)
#define APPLY_GC_ABSTRACT_CAST(TypePointer) \
	ABSTRACT_CAST(TypePointer, , true, GENERIC_CAST(TypePointer, , true)) \
	ABSTRACT_CAST(TypePointer, , false, GENERIC_CAST(TypePointer, , false)) \
	ABSTRACT_CAST(TypePointer, const, true, GENERIC_CAST(TypePointer, const, true)) \
	ABSTRACT_CAST(TypePointer, const, false, GENERIC_CAST(TypePointer, const, false))
#define APPLY_RT_ABSTRACT_CAST(TypePointer) \
	ABSTRACT_CAST(TypePointer, , true, RT_GENERIC_CAST(TypePointer, , true)) \
	ABSTRACT_CAST(TypePointer, , false, RT_GENERIC_CAST(TypePointer, , false)) \
	ABSTRACT_CAST(TypePointer, const, true, RT_GENERIC_CAST(TypePointer, const, true)) \
	ABSTRACT_CAST(TypePointer, const, false, RT_GENERIC_CAST(TypePointer, const, false))

APPLY_ABSTRACT_CAST(AbstractClass*);
APPLY_GC_ABSTRACT_CAST(ObjectClass*);
APPLY_RT_ABSTRACT_CAST(MissionClass*);
APPLY_RT_ABSTRACT_CAST(RadioClass*);
APPLY_GC_ABSTRACT_CAST(TechnoClass*);
APPLY_GC_ABSTRACT_CAST(FootClass*);

#undef APPLY_RT_ABSTRACT_CAST
#undef APPLY_GC_ABSTRACT_CAST
#undef APPLY_ABSTRACT_CAST
#undef ABSTRACT_CAST
#undef RT_GENERIC_CAST
#undef GENERIC_CAST
#undef ABSTRACT_PARAM
