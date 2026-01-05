#pragma once

# include "type/type.hpp"

namespace Kinai
{

namespace math
{

template <typename T>
inline T angle(T const& x, T const& y)
{
	static_assert(std::numeric_limits<T>::is_iec559, "'angle' only accept floating-point inputs");
	return acos(clamp(dot(x, y), T(-1), T(1)));
}

template <length_t L, typename T>
inline T angle(vec<L, T> const& x, vec<L, T> const& y)
{
	static_assert(std::numeric_limits<T>::is_iec559, "'angle' only accept floating-point inputs");
	return acos(clamp(dot(x, y), T(-1), T(1)));
}

template <typename T>
inline T orientedAngle(vec<2, T> const& x, vec<2, T> const& y)
{
	static_assert(std::numeric_limits<T>::is_iec559, "'orientedAngle' only accept floating-point inputs");
	T const Angle(acos(clamp(dot(x, y), T(-1), T(1))));

	if (all(epsilonEqual(y, math::rotate(x, Angle), epsilon<T>())))
		return Angle;
	else
		return -Angle;
}

} // math

} // Kinai
