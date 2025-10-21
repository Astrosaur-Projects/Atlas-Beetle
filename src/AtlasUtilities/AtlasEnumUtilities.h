#ifndef ATLAS_ENUM_UTILS_H
#define ATLAS_ENUM_UTILS_H

namespace AtlasEnumUtilities
{
	template <typename E>
	constexpr auto getValue(E e) noexcept {
		return static_cast<typename std::underlying_type<E>::type>(e);
	}
}

#endif