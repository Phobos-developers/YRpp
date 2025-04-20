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

// check nullptr

// This is more safer when unsure if pAbstract is a nullptr
template <typename T>
__forceinline T specific_cast(AbstractClass* pAbstract) {
	using Base = std::remove_pointer_t<T>;

	return const_cast<Base*>(specific_cast<const Base*>(static_cast<const AbstractClass*>(pAbstract)));
};

// This is more safer when unsure if pAbstract is a nullptr
template <typename T>
__forceinline T specific_cast(const AbstractClass* pAbstract) {
	using Base = std::remove_const_t<std::remove_pointer_t<T>>;

	static_assert(std::is_const<std::remove_pointer_t<T>>::value,
		"specific_cast: T is required to be const.");

	static_assert(std::is_base_of<AbstractClass, Base>::value,
		"specific_cast: T is required to be a type derived from AbstractClass.");

	static_assert(!std::is_abstract<Base>::value,
		"specific_cast: Abstract types (not fully implemented classes) are not supported.");

	if(pAbstract && pAbstract->WhatAmI() == Base::AbsID) {
		return static_cast<T>(pAbstract);
	}
	return nullptr;
};

// This is more safer when unsure if pAbstract is a nullptr
template <typename T>
__forceinline T generic_cast(AbstractClass* pAbstract) {
	using Base = std::remove_pointer_t<T>;

	return const_cast<Base*>(generic_cast<const Base*>(static_cast<const AbstractClass*>(pAbstract)));
};

// This is more safer when unsure if pAbstract is a nullptr
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

// This is more safer when unsure if pAbstract is a nullptr
template <typename T>
__forceinline T abstract_cast(AbstractClass* pAbstract) {
	using Base = std::remove_pointer_t<T>;

	return const_cast<T>(abstract_cast<const Base*>(static_cast<const AbstractClass*>(pAbstract)));
};

// This is more safer when unsure if pAbstract is a nullptr
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

// This is more safer when unsure if pAbstract is a nullptr
template <>
__forceinline AbstractClass* abstract_cast<AbstractClass*>(AbstractClass* pAbstract) {
	return pAbstract;
};

// This is more safer when unsure if pAbstract is a nullptr
template <>
__forceinline ObjectClass* abstract_cast<ObjectClass*>(AbstractClass* pAbstract) {
	return generic_cast<ObjectClass*>(pAbstract);
};

// This is more safer when unsure if pAbstract is a nullptr
template <>
__forceinline MissionClass* abstract_cast<MissionClass*>(AbstractClass* pAbstract) {
	return reinterpret_cast<MissionClass*>(generic_cast<TechnoClass*>(pAbstract));
};

// This is more safer when unsure if pAbstract is a nullptr
template <>
__forceinline RadioClass* abstract_cast<RadioClass*>(AbstractClass* pAbstract) {
	return reinterpret_cast<RadioClass*>(generic_cast<TechnoClass*>(pAbstract));
};

// This is more safer when unsure if pAbstract is a nullptr
template <>
__forceinline TechnoClass* abstract_cast<TechnoClass*>(AbstractClass* pAbstract) {
	return generic_cast<TechnoClass*>(pAbstract);
};

// This is more safer when unsure if pAbstract is a nullptr
template <>
__forceinline FootClass* abstract_cast<FootClass*>(AbstractClass* pAbstract) {
	return generic_cast<FootClass*>(pAbstract);
};

// const versions

// This is more safer when unsure if pAbstract is a nullptr
template <>
__forceinline const AbstractClass* abstract_cast<const AbstractClass*>(const AbstractClass* pAbstract) {
	return pAbstract;
};

// This is more safer when unsure if pAbstract is a nullptr
template <>
__forceinline const ObjectClass* abstract_cast<const ObjectClass*>(const AbstractClass* pAbstract) {
	return generic_cast<const ObjectClass*>(pAbstract);
};

// This is more safer when unsure if pAbstract is a nullptr
template <>
__forceinline const MissionClass* abstract_cast<const MissionClass*>(const AbstractClass* pAbstract) {
	return reinterpret_cast<const MissionClass*>(generic_cast<const TechnoClass*>(pAbstract));
};

// This is more safer when unsure if pAbstract is a nullptr
template <>
__forceinline const RadioClass* abstract_cast<const RadioClass*>(const AbstractClass* pAbstract) {
	return reinterpret_cast<const RadioClass*>(generic_cast<const TechnoClass*>(pAbstract));
};

// This is more safer when unsure if pAbstract is a nullptr
template <>
__forceinline const TechnoClass* abstract_cast<const TechnoClass*>(const AbstractClass* pAbstract) {
	return generic_cast<const TechnoClass*>(pAbstract);
};

// This is more safer when unsure if pAbstract is a nullptr
template <>
__forceinline const FootClass* abstract_cast<const FootClass*>(const AbstractClass* pAbstract) {
	return generic_cast<const FootClass*>(pAbstract);
};



// non-nullptr

// This is more efficient when confirmed that pAbstract is not a nullptr
template <typename T>
__forceinline T real_specific_cast(AbstractClass* pAbstract) {
	using Base = std::remove_pointer_t<T>;

	return const_cast<Base*>(real_specific_cast<const Base*>(static_cast<const AbstractClass*>(pAbstract)));
};

// This is more efficient when confirmed that pAbstract is not a nullptr
template <typename T>
__forceinline T real_specific_cast(const AbstractClass* pAbstract) {
	using Base = std::remove_const_t<std::remove_pointer_t<T>>;

	static_assert(std::is_const<std::remove_pointer_t<T>>::value,
		"real_specific_cast: T is required to be const.");

	static_assert(std::is_base_of<AbstractClass, Base>::value,
		"real_specific_cast: T is required to be a type derived from AbstractClass.");

	static_assert(!std::is_abstract<Base>::value,
		"real_specific_cast: Abstract types (not fully implemented classes) are not supported.");

	if(pAbstract->WhatAmI() == Base::AbsID) {
		return static_cast<T>(pAbstract);
	}
	return nullptr;
};

// This is more efficient when confirmed that pAbstract is not a nullptr
template <typename T>
__forceinline T real_generic_cast(AbstractClass* pAbstract) {
	using Base = std::remove_pointer_t<T>;

	return const_cast<Base*>(real_generic_cast<const Base*>(static_cast<const AbstractClass*>(pAbstract)));
};

// This is more efficient when confirmed that pAbstract is not a nullptr
template <typename T>
__forceinline T real_generic_cast(const AbstractClass* pAbstract) {
	using Base = std::remove_const_t<std::remove_pointer_t<T>>;

	static_assert(std::is_const<std::remove_pointer_t<T>>::value,
		"real_generic_cast: T is required to be const.");

	static_assert(std::is_base_of<ObjectClass, Base>::value
		&& std::is_abstract<Base>::value,
		"real_generic_cast: T is required to be an abstract type derived from ObjectClass.");

	if((pAbstract->AbstractFlags & Base::AbsDerivateID) != AbstractFlags::None) {
		return static_cast<T>(pAbstract);
	}
	return nullptr;
};

// This is more efficient when confirmed that pAbstract is not a nullptr
template <typename T>
__forceinline T real_abstract_cast(AbstractClass* pAbstract) {
	using Base = std::remove_pointer_t<T>;

	return const_cast<T>(real_abstract_cast<const Base*>(static_cast<const AbstractClass*>(pAbstract)));
};

// This is more efficient when confirmed that pAbstract is not a nullptr
template <typename T>
__forceinline T real_abstract_cast(const AbstractClass* pAbstract) {
	using Base = std::remove_const_t<std::remove_pointer_t<T>>;

	static_assert(std::is_const<std::remove_pointer_t<T>>::value,
		"real_abstract_cast: T is required to be const.");

	static_assert(std::is_base_of<AbstractClass, Base>::value,
		"real_abstract_cast: T is required to be a type derived from AbstractClass.");

	static_assert(!std::is_base_of<AbstractTypeClass, Base>::value
		|| !std::is_abstract<Base>::value,
		"real_abstract_cast: Abstract types (not fully implemented classes) derived from AbstractTypeClass are not suppored.");

	return real_specific_cast<T>(pAbstract);
};

// non-const versions

// This is more efficient when confirmed that pAbstract is not a nullptr
template <>
__forceinline AbstractClass* real_abstract_cast<AbstractClass*>(AbstractClass* pAbstract) {
	return pAbstract;
};

// This is more efficient when confirmed that pAbstract is not a nullptr
template <>
__forceinline ObjectClass* real_abstract_cast<ObjectClass*>(AbstractClass* pAbstract) {
	return real_generic_cast<ObjectClass*>(pAbstract);
};

// This is more efficient when confirmed that pAbstract is not a nullptr
template <>
__forceinline MissionClass* real_abstract_cast<MissionClass*>(AbstractClass* pAbstract) {
	return reinterpret_cast<MissionClass*>(real_generic_cast<TechnoClass*>(pAbstract));
};

// This is more efficient when confirmed that pAbstract is not a nullptr
template <>
__forceinline RadioClass* real_abstract_cast<RadioClass*>(AbstractClass* pAbstract) {
	return reinterpret_cast<RadioClass*>(real_generic_cast<TechnoClass*>(pAbstract));
};

// This is more efficient when confirmed that pAbstract is not a nullptr
template <>
__forceinline TechnoClass* real_abstract_cast<TechnoClass*>(AbstractClass* pAbstract) {
	return real_generic_cast<TechnoClass*>(pAbstract);
};

// This is more efficient when confirmed that pAbstract is not a nullptr
template <>
__forceinline FootClass* real_abstract_cast<FootClass*>(AbstractClass* pAbstract) {
	return real_generic_cast<FootClass*>(pAbstract);
};

// const versions

// This is more efficient when confirmed that pAbstract is not a nullptr
template <>
__forceinline const AbstractClass* real_abstract_cast<const AbstractClass*>(const AbstractClass* pAbstract) {
	return pAbstract;
};

// This is more efficient when confirmed that pAbstract is not a nullptr
template <>
__forceinline const ObjectClass* real_abstract_cast<const ObjectClass*>(const AbstractClass* pAbstract) {
	return real_generic_cast<const ObjectClass*>(pAbstract);
};

// This is more efficient when confirmed that pAbstract is not a nullptr
template <>
__forceinline const MissionClass* real_abstract_cast<const MissionClass*>(const AbstractClass* pAbstract) {
	return reinterpret_cast<const MissionClass*>(real_generic_cast<const TechnoClass*>(pAbstract));
};

// This is more efficient when confirmed that pAbstract is not a nullptr
template <>
__forceinline const RadioClass* real_abstract_cast<const RadioClass*>(const AbstractClass* pAbstract) {
	return reinterpret_cast<const RadioClass*>(real_generic_cast<const TechnoClass*>(pAbstract));
};

// This is more efficient when confirmed that pAbstract is not a nullptr
template <>
__forceinline const TechnoClass* real_abstract_cast<const TechnoClass*>(const AbstractClass* pAbstract) {
	return real_generic_cast<const TechnoClass*>(pAbstract);
};

// This is more efficient when confirmed that pAbstract is not a nullptr
template <>
__forceinline const FootClass* real_abstract_cast<const FootClass*>(const AbstractClass* pAbstract) {
	return real_generic_cast<const FootClass*>(pAbstract);
};
