#pragma once

#include "type/vectorize.hpp"

namespace Kinai
{

namespace math
{
// radians
template<typename T>
inline constexpr T radians(T degrees)
{
	static_assert(std::numeric_limits<T>::is_iec559, "'radians' only accept floating-point input");

	return degrees * static_cast<T>(0.01745329251994329576923690768489);
}

template<length_t L, typename T>
inline constexpr vec<L, T> radians(vec<L, T> const& v)
{
	return functor1<vec, L, T, T>::call(radians, v);
}

// degrees
template<typename T>
inline constexpr T degrees(T radians)
{
	static_assert(std::numeric_limits<T>::is_iec559, "'degrees' only accept floating-point input");

	return radians * static_cast<T>(57.295779513082320876798154814105);
}

template<length_t L, typename T>
inline constexpr vec<L, T> degrees(vec<L, T> const& v)
{
	return functor1<vec, L, T, T>::call(degrees, v);
}

// sin
using ::std::sin;

template<length_t L, typename T>
inline vec<L, T> sin(vec<L, T> const& v)
{
	return functor1<vec, L, T, T>::call(sin, v);
}

// cos
using std::cos;

template<length_t L, typename T>
inline vec<L, T> cos(vec<L, T> const& v)
{
	return functor1<vec, L, T, T>::call(cos, v);
}

// tan
using std::tan;

template<length_t L, typename T>
inline vec<L, T> tan(vec<L, T> const& v)
{
	return functor1<vec, L, T, T>::call(tan, v);
}

// asin
using std::asin;

template<length_t L, typename T>
inline vec<L, T> asin(vec<L, T> const& v)
{
	return functor1<vec, L, T, T>::call(asin, v);
}

// acos
using std::acos;

template<length_t L, typename T>
inline vec<L, T> acos(vec<L, T> const& v)
{
	return functor1<vec, L, T, T>::call(acos, v);
}

// atan
template<typename T>
inline T atan(T y, T x)
{
	static_assert(std::numeric_limits<T>::is_iec559, "'atan' only accept floating-point input");

	return ::std::atan2(y, x);
}

template<length_t L, typename T>
inline vec<L, T> atan(vec<L, T> const& a, vec<L, T> const& b)
{
	return functor2<vec, L, T>::call(::std::atan2, a, b);
}

using std::atan;

template<length_t L, typename T>
inline vec<L, T> atan(vec<L, T> const& v)
{
	return functor1<vec, L, T, T>::call(atan, v);
}

// sinh
using std::sinh;

template<length_t L, typename T>
inline vec<L, T> sinh(vec<L, T> const& v)
{
	return functor1<vec, L, T, T>::call(sinh, v);
}

// cosh
using std::cosh;

template<length_t L, typename T>
inline vec<L, T> cosh(vec<L, T> const& v)
{
	return functor1<vec, L, T, T>::call(cosh, v);
}

// tanh
using std::tanh;

template<length_t L, typename T>
inline vec<L, T> tanh(vec<L, T> const& v)
{
	return functor1<vec, L, T, T>::call(tanh, v);
}

// asinh
using std::asinh;

template<length_t L, typename T>
inline vec<L, T> asinh(vec<L, T> const& v)
{
	return functor1<vec, L, T, T>::call(asinh, v);
}

// acosh
using std::acosh;

template<length_t L, typename T>
inline vec<L, T> acosh(vec<L, T> const& v)
{
	return functor1<vec, L, T, T>::call(acosh, v);
}

// atanh
using std::atanh;

template<length_t L, typename T>
inline vec<L, T> atanh(vec<L, T> const& v)
{
	return functor1<vec, L, T, T>::call(atanh, v);
}

} // math

} // Kinai
