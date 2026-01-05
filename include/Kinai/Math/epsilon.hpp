#pragma once

// Dependencies
#include "type/type.hpp"
#include "type/vec4.hpp"
#include "vector_relational.hpp"
#include "common.hpp"

namespace Kinai
{

namespace math
{

template<typename T>
inline bool epsilonEqual(T const& x, T const& y, T const& epsilon)
{
	return abs(x - y) < epsilon;
}

template<typename T>
inline bool epsilonNotEqual(T const& x, T const& y, T const& epsilon)
{
	return abs(x - y) >= epsilon;
}

template<typename T>
vec<4, bool> epsilonEqual(qua<T> const& x, qua<T> const& y, T const& epsilon)
{
	vec<4, T> v(x.x - y.x, x.y - y.y, x.z - y.z, x.w - y.w);
	return lessThan(abs(v), vec<4, T>(epsilon));
}

template<typename T>
vec<4, bool> epsilonNotEqual(qua<T> const& x, qua<T> const& y, T const& epsilon)
{
	vec<4, T> v(x.x - y.x, x.y - y.y, x.z - y.z, x.w - y.w);
	return greaterThanEqual(abs(v), vec<4, T>(epsilon));
}

} // math

} // Kinai
