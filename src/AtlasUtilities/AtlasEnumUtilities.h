#ifndef ATLAS_ENUM_UTILS_H
#define ATLAS_ENUM_UTILS_H

namespace AtlasEnumUtilities
{
	/**
	 * This utility function provides a standard way to obtain the value of any strongly-typed enum.
	 */
	template <typename E>
	constexpr auto getValue(E e) noexcept {
		return static_cast<typename std::underlying_type<E>::type>(e);
	}
}

#endif