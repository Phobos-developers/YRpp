#pragma once

#include <AbstractClass.h>

#include <type_traits>

class ObjectClass;
class MissionClass;
class RadioClass;
class TechnoClass;
class FootClass;

template <typename T>
__forceinline T specific_cast(AbstractClass* pAbstract) {
	using Base = std::remove_pointer_t<T>;

	return const_cast<Base*>(specific_cast<const Base*>(static_cast<const AbstractClass*>(pAbstract)));
};

template <typename T>
__forceinline T specific_cast(const AbstractClass* pAbstract) {
	using Base = std::remove_const_t<std::remove_pointer_t<T>>;

	static_assert(std::is_const<std::remove_pointer_t<T>>::value,
		"specific_cast: T is required to be const.");

	static_assert(std::is_base_of<AbstractClass, Base>::value,
		"specific_cast: T is required to be a type derived from AbstractClass.");

	static_assert(!std::is_abstract<Base>::value,
		"specific_cast: Abstract types (not fully implemented classes) are not suppored.");

	if(pAbstract && pAbstract->WhatAmI() == Base::AbsID) {
		return static_cast<T>(pAbstract);
	}
	return nullptr;
};

template <typename T>
__forceinline T generic_cast(AbstractClass* pAbstract) {
	using Base = std::remove_pointer_t<T>;

	return const_cast<Base*>(generic_cast<const Base*>(static_cast<const AbstractClass*>(pAbstract)));
};

template <typename T>
__forceinline T generic_cast(const AbstractClass* pAbstract) {
	using Base = std::remove_const_t<std::remove_pointer_t<T>>;

	static_assert(std::is_const<std::remove_pointer_t<T>>::value,
		"generic_cast: T is required to be const.");

	static_assert(std::is_base_of<ObjectClass, Base>::value
		&& std::is_abstract<Base>::value,
		"generic_cast: T is required to be an abstract type derived from ObjectClass.");

	if(pAbstract && (pAbstract->AbstractFlags & Base::AbsDerivateID) != AbstractFlags::None) {
		return static_cast<T>(pAbstract);
	}
	return nullptr;
};

template <typename T>
__forceinline T abstract_cast(AbstractClass* pAbstract) {
	using Base = std::remove_pointer_t<T>;

	return const_cast<T>(abstract_cast<const Base*>(static_cast<const AbstractClass*>(pAbstract)));
};

template <typename T>
__forceinline T abstract_cast(const AbstractClass* pAbstract) {
	using Base = std::remove_const_t<std::remove_pointer_t<T>>;

	static_assert(std::is_const<std::remove_pointer_t<T>>::value,
		"abstract_cast: T is required to be const.");

	static_assert(std::is_base_of<AbstractClass, Base>::value,
		"abstract_cast: T is required to be a type derived from AbstractClass.");

	static_assert(!std::is_base_of<AbstractTypeClass, Base>::value
		|| !std::is_abstract<Base>::value,
		"abstract_cast: Abstract types (not fully implemented classes) derived from AbstractTypeClass are not suppored.");

	return specific_cast<T>(pAbstract);
};

// non-const versions

template <>
__forceinline AbstractClass* abstract_cast<AbstractClass*>(AbstractClass* pAbstract) {
	return pAbstract;
};

template <>
__forceinline ObjectClass* abstract_cast<ObjectClass*>(AbstractClass* pAbstract) {
	return generic_cast<ObjectClass*>(pAbstract);
};

template <>
__forceinline MissionClass* abstract_cast<MissionClass*>(AbstractClass* pAbstract) {
	return reinterpret_cast<MissionClass*>(generic_cast<TechnoClass*>(pAbstract));
};

template <>
__forceinline RadioClass* abstract_cast<RadioClass*>(AbstractClass* pAbstract) {
	return reinterpret_cast<RadioClass*>(generic_cast<TechnoClass*>(pAbstract));
};

template <>
__forceinline TechnoClass* abstract_cast<TechnoClass*>(AbstractClass* pAbstract) {
	return generic_cast<TechnoClass*>(pAbstract);
};

template <>
__forceinline FootClass* abstract_cast<FootClass*>(AbstractClass* pAbstract) {
	return generic_cast<FootClass*>(pAbstract);
};

// const versions

template <>
__forceinline const AbstractClass* abstract_cast<const AbstractClass*>(const AbstractClass* pAbstract) {
	return pAbstract;
};

template <>
__forceinline const ObjectClass* abstract_cast<const ObjectClass*>(const AbstractClass* pAbstract) {
	return generic_cast<const ObjectClass*>(pAbstract);
};

template <>
__forceinline const MissionClass* abstract_cast<const MissionClass*>(const AbstractClass* pAbstract) {
	return reinterpret_cast<const MissionClass*>(generic_cast<const TechnoClass*>(pAbstract));
};

template <>
__forceinline const RadioClass* abstract_cast<const RadioClass*>(const AbstractClass* pAbstract) {
	return reinterpret_cast<const RadioClass*>(generic_cast<const TechnoClass*>(pAbstract));
};

template <>
__forceinline const TechnoClass* abstract_cast<const TechnoClass*>(const AbstractClass* pAbstract) {
	return generic_cast<const TechnoClass*>(pAbstract);
};

template <>
__forceinline const FootClass* abstract_cast<const FootClass*>(const AbstractClass* pAbstract) {
	return generic_cast<const FootClass*>(pAbstract);
};
