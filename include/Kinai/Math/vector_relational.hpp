#pragma once

# include "type/type.hpp"

namespace Kinai
{

namespace math
{

template <length_t L, typename T>
inline constexpr vec<L, bool> lessThan(vec<L, T> const& x, vec<L, T> const& y)
{
	vec<L, bool> Result(true);
	for(length_t i = 0; i < L; ++i)
		Result[i] = x[i] < y[i];
	return Result;
}

template <length_t L, typename T>
inline constexpr vec<L, bool> lessThanEqual(vec<L, T> const& x, vec<L, T> const& y)
{
	vec<L, bool> Result(true);
	for(length_t i = 0; i < L; ++i)
		Result[i] = x[i] <= y[i];
	return Result;
}

template <length_t L, typename T>
inline constexpr vec<L, bool> greaterThan(vec<L, T> const& x, vec<L, T> const& y)
{
	vec<L, bool> Result(true);
	for(length_t i = 0; i < L; ++i)
		Result[i] = x[i] > y[i];
	return Result;
}

template <length_t L, typename T>
inline constexpr vec<L, bool> greaterThanEqual(vec<L, T> const& x, vec<L, T> const& y)
{
	vec<L, bool> Result(true);
	for(length_t i = 0; i < L; ++i)
		Result[i] = x[i] >= y[i];
	return Result;
}

template <length_t L, typename T>
inline constexpr vec<L, bool> equal(vec<L, T> const& x, vec<L, T> const& y)
{
	vec<L, bool> Result(true);
	for(length_t i = 0; i < L; ++i)
		Result[i] = x[i] == y[i];
	return Result;
}

template <length_t L, typename T>
inline constexpr vec<L, bool> notEqual(vec<L, T> const& x, vec<L, T> const& y)
{
	vec<L, bool> Result(true);
	for(length_t i = 0; i < L; ++i)
		Result[i] = x[i] != y[i];
	return Result;
}

template <length_t L>
inline constexpr bool any(vec<L, bool> const& v)
{
	bool Result = false;
	for(length_t i = 0; i < L; ++i)
		Result = Result || v[i];
	return Result;
}

template <length_t L>
inline constexpr bool all(vec<L, bool> const& v)
{
	bool Result = true;
	for(length_t i = 0; i < L; ++i)
		Result = Result && v[i];
	return Result;
}

template <length_t L>
inline constexpr vec<L, bool> not_(vec<L, bool> const& v)
{
	vec<L, bool> Result(true);
	for(length_t i = 0; i < L; ++i)
		Result[i] = !v[i];
	return Result;
}

} // math

} // Kinai
