#pragma once

# include "type.hpp"

namespace Kinai
{

namespace math
{

template <typename T>
struct vec<4, T>
{
	// -- Implementation detail --

	typedef T				value_type;
	typedef vec<4, T>		type;
	typedef vec<4, bool>	bool_type;
	typedef length_t		length_type;

	// -- Data --
	union { T x, r, s; };
	union { T y, g, t; };
	union { T z, b, p; };
	union { T w, a, q; };

	// -- Component accesses --

	/// Return the count of components of the vector
	static constexpr length_type length(){return 4;}

	constexpr T&		operator[](length_type i);
	constexpr T const&	operator[](length_type i) const;

	// -- Implicit basic constructors --

	constexpr vec() = default;
	constexpr vec(vec<4, T> const& v) = default;

	// -- Explicit basic constructors --

	constexpr explicit vec(T scalar);
	constexpr vec(T x, T y, T z, T w);

	// -- Conversion scalar constructors --

	template <typename U>
	constexpr explicit vec(vec<1, U> const& v);

	template <typename X, typename Y, typename Z, typename W>
	constexpr vec(X _x, Y _y, Z _z, W _w);
	template <typename X, typename Y, typename Z, typename W>
	constexpr vec(vec<1, X> const& _x, Y _y, Z _z, W _w);
	template <typename X, typename Y, typename Z, typename W>
	constexpr vec(X _x, vec<1, Y> const& _y, Z _z, W _w);
	template <typename X, typename Y, typename Z, typename W>
	constexpr vec(vec<1, X> const& _x, vec<1, Y> const& _y, Z _z, W _w);
	template <typename X, typename Y, typename Z, typename W>
	constexpr vec(X _x, Y _y, vec<1, Z> const& _z, W _w);
	template <typename X, typename Y, typename Z, typename W>
	constexpr vec(vec<1, X> const& _x, Y _y, vec<1, Z> const& _z, W _w);
	template <typename X, typename Y, typename Z, typename W>
	constexpr vec(X _x, vec<1, Y> const& _y, vec<1, Z> const& _z, W _w);
	template <typename X, typename Y, typename Z, typename W>
	constexpr vec(vec<1, X> const& _x, vec<1, Y> const& _y, vec<1, Z> const& _z, W _w);
	template <typename X, typename Y, typename Z, typename W>
	constexpr vec(vec<1, X> const& _x, Y _y, Z _z, vec<1, W> const& _w);
	template <typename X, typename Y, typename Z, typename W>
	constexpr vec(X _x, vec<1, Y> const& _y, Z _z, vec<1, W> const& _w);
	template <typename X, typename Y, typename Z, typename W>
	constexpr vec(vec<1, X> const& _x, vec<1, Y> const& _y, Z _z, vec<1, W> const& _w);
	template <typename X, typename Y, typename Z, typename W>
	constexpr vec(X _x, Y _y, vec<1, Z> const& _z, vec<1, W> const& _w);
	template <typename X, typename Y, typename Z, typename W>
	constexpr vec(vec<1, X> const& _x, Y _y, vec<1, Z> const& _z, vec<1, W> const& _w);
	template <typename X, typename Y, typename Z, typename W>
	constexpr vec(X _x, vec<1, Y> const& _y, vec<1, Z> const& _z, vec<1, W> const& _w);
	template <typename X, typename Y, typename Z, typename W>
	constexpr vec(vec<1, X> const& _x, vec<1, Y> const& _Y, vec<1, Z> const& _z, vec<1, W> const& _w);

	// -- Conversion vector constructors --

	template <typename A, typename B, typename C>
	constexpr vec(vec<2, A> const& _xy, B _z, C _w);
	template <typename A, typename B, typename C>
	constexpr vec(vec<2, A> const& _xy, vec<1, B> const& _z, C _w);
	template <typename A, typename B, typename C>
	constexpr vec(vec<2, A> const& _xy, B _z, vec<1, C> const& _w);
	template <typename A, typename B, typename C>
	constexpr vec(vec<2, A> const& _xy, vec<1, B> const& _z, vec<1, C> const& _w);
	template <typename A, typename B, typename C>
	constexpr vec(A _x, vec<2, B> const& _yz, C _w);
	template <typename A, typename B, typename C>
	constexpr vec(vec<1, A> const& _x, vec<2, B> const& _yz, C _w);
	template <typename A, typename B, typename C>
	constexpr vec(A _x, vec<2, B> const& _yz, vec<1, C> const& _w);
	template <typename A, typename B, typename C>
	constexpr vec(vec<1, A> const& _x, vec<2, B> const& _yz, vec<1, C> const& _w);
	template <typename A, typename B, typename C>
	constexpr vec(A _x, B _y, vec<2, C> const& _zw);
	template <typename A, typename B, typename C>
	constexpr vec(vec<1, A> const& _x, B _y, vec<2, C> const& _zw);
	template <typename A, typename B, typename C>
	constexpr vec(A _x, vec<1, B> const& _y, vec<2, C> const& _zw);
	template <typename A, typename B, typename C>
	constexpr vec(vec<1, A> const& _x, vec<1, B> const& _y, vec<2, C> const& _zw);
	template <typename A, typename B>
	constexpr vec(vec<3, A> const& _xyz, B _w);
	template <typename A, typename B>
	constexpr vec(vec<3, A> const& _xyz, vec<1, B> const& _w);
	template <typename A, typename B>
	constexpr vec(A _x, vec<3, B> const& _yzw);
	template <typename A, typename B>
	constexpr vec(vec<1, A> const& _x, vec<3, B> const& _yzw);
	template <typename A, typename B>
	constexpr vec(vec<2, A> const& _xy, vec<2, B> const& _zw);

	template <typename U>
	constexpr explicit vec(vec<4, U> const& v);

	// -- Unary arithmetic operators --

	constexpr vec<4, T>& operator=(vec<4, T> const& v) = default;

	template <typename U>
	constexpr vec<4, T>& operator=(vec<4, U> const& v);
	template <typename U>
	constexpr vec<4, T>& operator+=(U scalar);
	template <typename U>
	constexpr vec<4, T>& operator+=(vec<1, U> const& v);
	template <typename U>
	constexpr vec<4, T>& operator+=(vec<4, U> const& v);
	template <typename U>
	constexpr vec<4, T>& operator-=(U scalar);
	template <typename U>
	constexpr vec<4, T>& operator-=(vec<1, U> const& v);
	template <typename U>
	constexpr vec<4, T>& operator-=(vec<4, U> const& v);
	template <typename U>
	constexpr vec<4, T>& operator*=(U scalar);
	template <typename U>
	constexpr vec<4, T>& operator*=(vec<1, U> const& v);
	template <typename U>
	constexpr vec<4, T>& operator*=(vec<4, U> const& v);
	template <typename U>
	constexpr vec<4, T>& operator/=(U scalar);
	template <typename U>
	constexpr vec<4, T>& operator/=(vec<1, U> const& v);
	template <typename U>
	constexpr vec<4, T>& operator/=(vec<4, U> const& v);

	// -- Increment and decrement operators --

	constexpr vec<4, T> & operator++();
	constexpr vec<4, T> & operator--();
	constexpr vec<4, T> operator++(int);
	constexpr vec<4, T> operator--(int);

	// -- Unary bit operators --

	template <typename U>
	constexpr vec<4, T> & operator%=(U scalar);
	template <typename U>
	constexpr vec<4, T> & operator%=(vec<1, U> const& v);
	template <typename U>
	constexpr vec<4, T> & operator%=(vec<4, U> const& v);
	template <typename U>
	constexpr vec<4, T> & operator&=(U scalar);
	template <typename U>
	constexpr vec<4, T> & operator&=(vec<1, U> const& v);
	template <typename U>
	constexpr vec<4, T> & operator&=(vec<4, U> const& v);
	template <typename U>
	constexpr vec<4, T> & operator|=(U scalar);
	template <typename U>
	constexpr vec<4, T> & operator|=(vec<1, U> const& v);
	template <typename U>
	constexpr vec<4, T> & operator|=(vec<4, U> const& v);
	template <typename U>
	constexpr vec<4, T> & operator^=(U scalar);
	template <typename U>
	constexpr vec<4, T> & operator^=(vec<1, U> const& v);
	template <typename U>
	constexpr vec<4, T> & operator^=(vec<4, U> const& v);
	template <typename U>
	constexpr vec<4, T> & operator<<=(U scalar);
	template <typename U>
	constexpr vec<4, T> & operator<<=(vec<1, U> const& v);
	template <typename U>
	constexpr vec<4, T> & operator<<=(vec<4, U> const& v);
	template <typename U>
	constexpr vec<4, T> & operator>>=(U scalar);
	template <typename U>
	constexpr vec<4, T> & operator>>=(vec<1, U> const& v);
	template <typename U>
	constexpr vec<4, T> & operator>>=(vec<4, U> const& v);
};

template <typename T>
struct compute_vec4_add
{
	constexpr static vec<4, T> call(vec<4, T> const& a, vec<4, T> const& b)
	{
		return vec<4, T>(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
	}
};

template <typename T>
struct compute_vec4_sub
{
	constexpr static vec<4, T> call(vec<4, T> const& a, vec<4, T> const& b)
	{
		return vec<4, T>(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
	}
};

template <typename T>
struct compute_vec4_mul
{
	constexpr static vec<4, T> call(vec<4, T> const& a, vec<4, T> const& b)
	{
		return vec<4, T>(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
	}
};

template <typename T>
struct compute_vec4_div
{
	constexpr static vec<4, T> call(vec<4, T> const& a, vec<4, T> const& b)
	{
		return vec<4, T>(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
	}
};

template <typename T>
struct compute_vec4_mod
{
	constexpr static vec<4, T> call(vec<4, T> const& a, vec<4, T> const& b)
	{
		return vec<4, T>(a.x % b.x, a.y % b.y, a.z % b.z, a.w % b.w);
	}
};

template <typename T, int IsInt, std::size_t Size>
struct compute_vec4_and
{
	constexpr static vec<4, T> call(vec<4, T> const& a, vec<4, T> const& b)
	{
		return vec<4, T>(a.x & b.x, a.y & b.y, a.z & b.z, a.w & b.w);
	}
};

template <typename T, int IsInt, std::size_t Size>
struct compute_vec4_or
{
	constexpr static vec<4, T> call(vec<4, T> const& a, vec<4, T> const& b)
	{
		return vec<4, T>(a.x | b.x, a.y | b.y, a.z | b.z, a.w | b.w);
	}
};

template <typename T, int IsInt, std::size_t Size>
struct compute_vec4_xor
{
	constexpr static vec<4, T> call(vec<4, T> const& a, vec<4, T> const& b)
	{
		return vec<4, T>(a.x ^ b.x, a.y ^ b.y, a.z ^ b.z, a.w ^ b.w);
	}
};

template <typename T, int IsInt, std::size_t Size>
struct compute_vec4_shift_left
{
	constexpr static vec<4, T> call(vec<4, T> const& a, vec<4, T> const& b)
	{
		return vec<4, T>(a.x << b.x, a.y << b.y, a.z << b.z, a.w << b.w);
	}
};

template <typename T, int IsInt, std::size_t Size>
struct compute_vec4_shift_right
{
	constexpr static vec<4, T> call(vec<4, T> const& a, vec<4, T> const& b)
	{
		return vec<4, T>(a.x >> b.x, a.y >> b.y, a.z >> b.z, a.w >> b.w);
	}
};

template <typename T, int IsInt, std::size_t Size>
struct compute_vec4_equal
{
	constexpr static bool call(vec<4, T> const& v1, vec<4, T> const& v2)
	{
		return
			compute_equal<T, std::numeric_limits<T>::is_iec559>::call(v1.x, v2.x) &&
			compute_equal<T, std::numeric_limits<T>::is_iec559>::call(v1.y, v2.y) &&
			compute_equal<T, std::numeric_limits<T>::is_iec559>::call(v1.z, v2.z) &&
			compute_equal<T, std::numeric_limits<T>::is_iec559>::call(v1.w, v2.w);
	}
};

template <typename T, int IsInt, std::size_t Size>
struct compute_vec4_nequal
{
	constexpr static bool call(vec<4, T> const& v1, vec<4, T> const& v2)
	{
		return !compute_vec4_equal<T, is_int<T>::value, sizeof(T) * 8>::call(v1, v2);
	}
};

template <typename T, int IsInt, std::size_t Size>
struct compute_vec4_bitwise_not
{
	constexpr static vec<4, T> call(vec<4, T> const& v)
	{
		return vec<4, T>(~v.x, ~v.y, ~v.z, ~v.w);
	}
};

// -- Explicit basic constructors --

template <typename T>
constexpr vec<4, T>::vec(T scalar)
	: x(scalar), y(scalar), z(scalar), w(scalar)
{}

template <typename T>
constexpr vec<4, T>::vec(T _x, T _y, T _z, T _w)
	: x(_x), y(_y), z(_z), w(_w)
{}

// -- Conversion scalar constructors --

template <typename T>
template <typename U>
constexpr vec<4, T>::vec(vec<1, U> const& v)
	: x(static_cast<T>(v.x))
	, y(static_cast<T>(v.x))
	, z(static_cast<T>(v.x))
	, w(static_cast<T>(v.x))
{}

template <typename T>
template <typename X, typename Y, typename Z, typename W>
constexpr vec<4, T>::vec(X _x, Y _y, Z _z, W _w)
	: x(static_cast<T>(_x))
	, y(static_cast<T>(_y))
	, z(static_cast<T>(_z))
	, w(static_cast<T>(_w))
{}

template <typename T>
template <typename X, typename Y, typename Z, typename W>
constexpr vec<4, T>::vec(vec<1, X> const& _x, Y _y, Z _z, W _w)
	: x(static_cast<T>(_x.x))
	, y(static_cast<T>(_y))
	, z(static_cast<T>(_z))
	, w(static_cast<T>(_w))
{}

template <typename T>
template <typename X, typename Y, typename Z, typename W>
constexpr vec<4, T>::vec(X _x, vec<1, Y> const& _y, Z _z, W _w)
	: x(static_cast<T>(_x))
	, y(static_cast<T>(_y.x))
	, z(static_cast<T>(_z))
	, w(static_cast<T>(_w))
{}

template <typename T>
template <typename X, typename Y, typename Z, typename W>
constexpr vec<4, T>::vec(vec<1, X> const& _x, vec<1, Y> const& _y, Z _z, W _w)
	: x(static_cast<T>(_x.x))
	, y(static_cast<T>(_y.x))
	, z(static_cast<T>(_z))
	, w(static_cast<T>(_w))
{}

template <typename T>
template <typename X, typename Y, typename Z, typename W>
constexpr vec<4, T>::vec(X _x, Y _y, vec<1, Z> const& _z, W _w)
	: x(static_cast<T>(_x))
	, y(static_cast<T>(_y))
	, z(static_cast<T>(_z.x))
	, w(static_cast<T>(_w))
{}

template <typename T>
template <typename X, typename Y, typename Z, typename W>
constexpr vec<4, T>::vec(vec<1, X> const& _x, Y _y, vec<1, Z> const& _z, W _w)
	: x(static_cast<T>(_x.x))
	, y(static_cast<T>(_y))
	, z(static_cast<T>(_z.x))
	, w(static_cast<T>(_w))
{}

template <typename T>
template <typename X, typename Y, typename Z, typename W>
constexpr vec<4, T>::vec(X _x, vec<1, Y> const& _y, vec<1, Z> const& _z, W _w)
	: x(static_cast<T>(_x))
	, y(static_cast<T>(_y.x))
	, z(static_cast<T>(_z.x))
	, w(static_cast<T>(_w))
{}

template <typename T>
template <typename X, typename Y, typename Z, typename W>
constexpr vec<4, T>::vec(vec<1, X> const& _x, vec<1, Y> const& _y, vec<1, Z> const& _z, W _w)
	: x(static_cast<T>(_x.x))
	, y(static_cast<T>(_y.x))
	, z(static_cast<T>(_z.x))
	, w(static_cast<T>(_w))
{}

template <typename T>
template <typename X, typename Y, typename Z, typename W>
constexpr vec<4, T>::vec(vec<1, X> const& _x, Y _y, Z _z, vec<1, W> const& _w)
	: x(static_cast<T>(_x.x))
	, y(static_cast<T>(_y))
	, z(static_cast<T>(_z))
	, w(static_cast<T>(_w.x))
{}

template <typename T>
template <typename X, typename Y, typename Z, typename W>
constexpr vec<4, T>::vec(X _x, vec<1, Y> const& _y, Z _z, vec<1, W> const& _w)
	: x(static_cast<T>(_x))
	, y(static_cast<T>(_y.x))
	, z(static_cast<T>(_z))
	, w(static_cast<T>(_w.x))
{}

template <typename T>
template <typename X, typename Y, typename Z, typename W>
constexpr vec<4, T>::vec(vec<1, X> const& _x, vec<1, Y> const& _y, Z _z, vec<1, W> const& _w)
	: x(static_cast<T>(_x.x))
	, y(static_cast<T>(_y.x))
	, z(static_cast<T>(_z))
	, w(static_cast<T>(_w.x))
{}

template <typename T>
template <typename X, typename Y, typename Z, typename W>
constexpr vec<4, T>::vec(X _x, Y _y, vec<1, Z> const& _z, vec<1, W> const& _w)
	: x(static_cast<T>(_x))
	, y(static_cast<T>(_y))
	, z(static_cast<T>(_z.x))
	, w(static_cast<T>(_w.x))
{}

template <typename T>
template <typename X, typename Y, typename Z, typename W>
constexpr vec<4, T>::vec(vec<1, X> const& _x, Y _y, vec<1, Z> const& _z, vec<1, W> const& _w)
	: x(static_cast<T>(_x.x))
	, y(static_cast<T>(_y))
	, z(static_cast<T>(_z.x))
	, w(static_cast<T>(_w.x))
{}

template <typename T>
template <typename X, typename Y, typename Z, typename W>
constexpr vec<4, T>::vec(X _x, vec<1, Y> const& _y, vec<1, Z> const& _z, vec<1, W> const& _w)
	: x(static_cast<T>(_x))
	, y(static_cast<T>(_y.x))
	, z(static_cast<T>(_z.x))
	, w(static_cast<T>(_w.x))
{}

template <typename T>
template <typename X, typename Y, typename Z, typename W>
constexpr vec<4, T>::vec(vec<1, X> const& _x, vec<1, Y> const& _y, vec<1, Z> const& _z, vec<1, W> const& _w)
	: x(static_cast<T>(_x.x))
	, y(static_cast<T>(_y.x))
	, z(static_cast<T>(_z.x))
	, w(static_cast<T>(_w.x))
{}

// -- Conversion vector constructors --

template <typename T>
template <typename A, typename B, typename C>
constexpr vec<4, T>::vec(vec<2, A> const& _xy, B _z, C _w)
	: x(static_cast<T>(_xy.x))
	, y(static_cast<T>(_xy.y))
	, z(static_cast<T>(_z))
	, w(static_cast<T>(_w))
{}

template <typename T>
template <typename A, typename B, typename C>
constexpr vec<4, T>::vec(vec<2, A> const& _xy, vec<1, B> const& _z, C _w)
	: x(static_cast<T>(_xy.x))
	, y(static_cast<T>(_xy.y))
	, z(static_cast<T>(_z.x))
	, w(static_cast<T>(_w))
{}

template <typename T>
template <typename A, typename B, typename C>
constexpr vec<4, T>::vec(vec<2, A> const& _xy, B _z, vec<1, C> const& _w)
	: x(static_cast<T>(_xy.x))
	, y(static_cast<T>(_xy.y))
	, z(static_cast<T>(_z))
	, w(static_cast<T>(_w.x))
{}

template <typename T>
template <typename A, typename B, typename C>
constexpr vec<4, T>::vec(vec<2, A> const& _xy, vec<1, B> const& _z, vec<1, C> const& _w)
	: x(static_cast<T>(_xy.x))
	, y(static_cast<T>(_xy.y))
	, z(static_cast<T>(_z.x))
	, w(static_cast<T>(_w.x))
{}

template <typename T>
template <typename A, typename B, typename C>
constexpr vec<4, T>::vec(A _x, vec<2, B> const& _yz, C _w)
	: x(static_cast<T>(_x))
	, y(static_cast<T>(_yz.x))
	, z(static_cast<T>(_yz.y))
	, w(static_cast<T>(_w))
{}

template <typename T>
template <typename A, typename B, typename C>
constexpr vec<4, T>::vec(vec<1, A> const& _x, vec<2, B> const& _yz, C _w)
	: x(static_cast<T>(_x.x))
	, y(static_cast<T>(_yz.x))
	, z(static_cast<T>(_yz.y))
	, w(static_cast<T>(_w))
{}

template <typename T>
template <typename A, typename B, typename C>
constexpr vec<4, T>::vec(A _x, vec<2, B> const& _yz, vec<1, C> const& _w)
	: x(static_cast<T>(_x))
	, y(static_cast<T>(_yz.x))
	, z(static_cast<T>(_yz.y))
	, w(static_cast<T>(_w.x))
{}

template <typename T>
template <typename A, typename B, typename C>
constexpr vec<4, T>::vec(vec<1, A> const& _x, vec<2, B> const& _yz, vec<1, C> const& _w)
	: x(static_cast<T>(_x.x))
	, y(static_cast<T>(_yz.x))
	, z(static_cast<T>(_yz.y))
	, w(static_cast<T>(_w.x))
{}

template <typename T>
template <typename A, typename B, typename C>
constexpr vec<4, T>::vec(A _x, B _y, vec<2, C> const& _zw)
	: x(static_cast<T>(_x))
	, y(static_cast<T>(_y))
	, z(static_cast<T>(_zw.x))
	, w(static_cast<T>(_zw.y))
{}

template <typename T>
template <typename A, typename B, typename C>
constexpr vec<4, T>::vec(vec<1, A> const& _x, B _y, vec<2, C> const& _zw)
	: x(static_cast<T>(_x.x))
	, y(static_cast<T>(_y))
	, z(static_cast<T>(_zw.x))
	, w(static_cast<T>(_zw.y))
{}

template <typename T>
template <typename A, typename B, typename C>
constexpr vec<4, T>::vec(A _x, vec<1, B> const& _y, vec<2, C> const& _zw)
	: x(static_cast<T>(_x))
	, y(static_cast<T>(_y.x))
	, z(static_cast<T>(_zw.x))
	, w(static_cast<T>(_zw.y))
{}

template <typename T>
template <typename A, typename B, typename C>
constexpr vec<4, T>::vec(vec<1, A> const& _x, vec<1, B> const& _y, vec<2, C> const& _zw)
	: x(static_cast<T>(_x.x))
	, y(static_cast<T>(_y.x))
	, z(static_cast<T>(_zw.x))
	, w(static_cast<T>(_zw.y))
{}

template <typename T>
template <typename A, typename B>
constexpr vec<4, T>::vec(vec<3, A> const& _xyz, B _w)
	: x(static_cast<T>(_xyz.x))
	, y(static_cast<T>(_xyz.y))
	, z(static_cast<T>(_xyz.z))
	, w(static_cast<T>(_w))
{}

template <typename T>
template <typename A, typename B>
constexpr vec<4, T>::vec(vec<3, A> const& _xyz, vec<1, B> const& _w)
	: x(static_cast<T>(_xyz.x))
	, y(static_cast<T>(_xyz.y))
	, z(static_cast<T>(_xyz.z))
	, w(static_cast<T>(_w.x))
{}

template <typename T>
template <typename A, typename B>
constexpr vec<4, T>::vec(A _x, vec<3, B> const& _yzw)
	: x(static_cast<T>(_x))
	, y(static_cast<T>(_yzw.x))
	, z(static_cast<T>(_yzw.y))
	, w(static_cast<T>(_yzw.z))
{}

template <typename T>
template <typename A, typename B>
constexpr vec<4, T>::vec(vec<1, A> const& _x, vec<3, B> const& _yzw)
	: x(static_cast<T>(_x.x))
	, y(static_cast<T>(_yzw.x))
	, z(static_cast<T>(_yzw.y))
	, w(static_cast<T>(_yzw.z))
{}

template <typename T>
template <typename A, typename B>
constexpr vec<4, T>::vec(vec<2, A> const& _xy, vec<2, B> const& _zw)
	: x(static_cast<T>(_xy.x))
	, y(static_cast<T>(_xy.y))
	, z(static_cast<T>(_zw.x))
	, w(static_cast<T>(_zw.y))
{}

template <typename T>
template <typename U>
constexpr vec<4, T>::vec(vec<4, U> const& v)
	: x(static_cast<T>(v.x))
	, y(static_cast<T>(v.y))
	, z(static_cast<T>(v.z))
	, w(static_cast<T>(v.w))
{}

// -- Component accesses --

template <typename T>
constexpr T& vec<4, T>::operator[](typename vec<4, T>::length_type i)
{
	assert(i >= 0 && i < this->length());
	switch(i)
	{
	default:
	case 0:
		return x;
	case 1:
		return y;
	case 2:
		return z;
	case 3:
		return w;
	}
}

template <typename T>
constexpr T const& vec<4, T>::operator[](typename vec<4, T>::length_type i) const
{
	assert(i >= 0 && i < this->length());
	switch(i)
	{
	default:
	case 0:
		return x;
	case 1:
		return y;
	case 2:
		return z;
	case 3:
		return w;
	}
}

// -- Unary arithmetic operators --

template <typename T>
template <typename U>
constexpr vec<4, T>& vec<4, T>::operator=(vec<4, U> const& v)
{
	this->x = static_cast<T>(v.x);
	this->y = static_cast<T>(v.y);
	this->z = static_cast<T>(v.z);
	this->w = static_cast<T>(v.w);
	return *this;
}

template <typename T>
template <typename U>
constexpr vec<4, T> & vec<4, T>::operator+=(U scalar)
{
	return (*this = compute_vec4_add<T>::call(*this, vec<4, T>(scalar)));
}

template <typename T>
template <typename U>
constexpr vec<4, T> & vec<4, T>::operator+=(vec<1, U> const& v)
{
	return (*this = compute_vec4_add<T>::call(*this, vec<4, T>(v.x)));
}

template <typename T>
template <typename U>
constexpr vec<4, T> & vec<4, T>::operator+=(vec<4, U> const& v)
{
	return (*this = compute_vec4_add<T>::call(*this, vec<4, T>(v)));
}

template <typename T>
template <typename U>
constexpr vec<4, T> & vec<4, T>::operator-=(U scalar)
{
	return (*this = compute_vec4_sub<T>::call(*this, vec<4, T>(scalar)));
}

template <typename T>
template <typename U>
constexpr vec<4, T> & vec<4, T>::operator-=(vec<1, U> const& v)
{
	return (*this = compute_vec4_sub<T>::call(*this, vec<4, T>(v.x)));
}

template <typename T>
template <typename U>
constexpr vec<4, T> & vec<4, T>::operator-=(vec<4, U> const& v)
{
	return (*this = compute_vec4_sub<T>::call(*this, vec<4, T>(v)));
}

template <typename T>
template <typename U>
constexpr vec<4, T> & vec<4, T>::operator*=(U scalar)
{
	return (*this = compute_vec4_mul<T>::call(*this, vec<4, T>(scalar)));
}

template <typename T>
template <typename U>
constexpr vec<4, T> & vec<4, T>::operator*=(vec<1, U> const& v)
{
	return (*this = compute_vec4_mul<T>::call(*this, vec<4, T>(v.x)));
}

template <typename T>
template <typename U>
constexpr vec<4, T> & vec<4, T>::operator*=(vec<4, U> const& v)
{
	return (*this = compute_vec4_mul<T>::call(*this, vec<4, T>(v)));
}

template <typename T>
template <typename U>
constexpr vec<4, T> & vec<4, T>::operator/=(U scalar)
{
	return (*this = compute_vec4_div<T>::call(*this, vec<4, T>(scalar)));
}

template <typename T>
template <typename U>
constexpr vec<4, T> & vec<4, T>::operator/=(vec<1, U> const& v)
{
	return (*this = compute_vec4_div<T>::call(*this, vec<4, T>(v.x)));
}

template <typename T>
template <typename U>
constexpr vec<4, T> & vec<4, T>::operator/=(vec<4, U> const& v)
{
	return (*this = compute_vec4_div<T>::call(*this, vec<4, T>(v)));
}

// -- Increment and decrement operators --

template <typename T>
constexpr vec<4, T> & vec<4, T>::operator++()
{
	++this->x;
	++this->y;
	++this->z;
	++this->w;
	return *this;
}

template <typename T>
constexpr vec<4, T> & vec<4, T>::operator--()
{
	--this->x;
	--this->y;
	--this->z;
	--this->w;
	return *this;
}

template <typename T>
constexpr vec<4, T> vec<4, T>::operator++(int)
{
	vec<4, T> Result(*this);
	++*this;
	return Result;
}

template <typename T>
constexpr vec<4, T> vec<4, T>::operator--(int)
{
	vec<4, T> Result(*this);
	--*this;
	return Result;
}

// -- Unary bit operators --

template <typename T>
template <typename U>
constexpr vec<4, T> & vec<4, T>::operator%=(U scalar)
{
	return (*this = compute_vec4_mod<T>::call(*this, vec<4, T>(scalar)));
}

template <typename T>
template <typename U>
constexpr vec<4, T> & vec<4, T>::operator%=(vec<1, U> const& v)
{
	return (*this = compute_vec4_mod<T>::call(*this, vec<4, T>(v)));
}

template <typename T>
template <typename U>
constexpr vec<4, T> & vec<4, T>::operator%=(vec<4, U> const& v)
{
	return (*this = compute_vec4_mod<T>::call(*this, vec<4, T>(v)));
}

template <typename T>
template <typename U>
constexpr vec<4, T> & vec<4, T>::operator&=(U scalar)
{
	return (*this = compute_vec4_and<T, is_int<T>::value, sizeof(T) * 8>::call(*this, vec<4, T>(scalar)));
}

template <typename T>
template <typename U>
constexpr vec<4, T> & vec<4, T>::operator&=(vec<1, U> const& v)
{
	return (*this = compute_vec4_and<T, is_int<T>::value, sizeof(T) * 8>::call(*this, vec<4, T>(v)));
}

template <typename T>
template <typename U>
constexpr vec<4, T> & vec<4, T>::operator&=(vec<4, U> const& v)
{
	return (*this = compute_vec4_and<T, is_int<T>::value, sizeof(T) * 8>::call(*this, vec<4, T>(v)));
}

template <typename T>
template <typename U>
constexpr vec<4, T> & vec<4, T>::operator|=(U scalar)
{
	return (*this = compute_vec4_or<T, is_int<T>::value, sizeof(T) * 8>::call(*this, vec<4, T>(scalar)));
}

template <typename T>
template <typename U>
constexpr vec<4, T> & vec<4, T>::operator|=(vec<1, U> const& v)
{
	return (*this = compute_vec4_or<T, is_int<T>::value, sizeof(T) * 8>::call(*this, vec<4, T>(v)));
}

template <typename T>
template <typename U>
constexpr vec<4, T> & vec<4, T>::operator|=(vec<4, U> const& v)
{
	return (*this = compute_vec4_or<T, is_int<T>::value, sizeof(T) * 8>::call(*this, vec<4, T>(v)));
}

template <typename T>
template <typename U>
constexpr vec<4, T> & vec<4, T>::operator^=(U scalar)
{
	return (*this = compute_vec4_xor<T, is_int<T>::value, sizeof(T) * 8>::call(*this, vec<4, T>(scalar)));
}

template <typename T>
template <typename U>
constexpr vec<4, T> & vec<4, T>::operator^=(vec<1, U> const& v)
{
	return (*this = compute_vec4_xor<T, is_int<T>::value, sizeof(T) * 8>::call(*this, vec<4, T>(v)));
}

template <typename T>
template <typename U>
constexpr vec<4, T> & vec<4, T>::operator^=(vec<4, U> const& v)
{
	return (*this = compute_vec4_xor<T, is_int<T>::value, sizeof(T) * 8>::call(*this, vec<4, T>(v)));
}

template <typename T>
template <typename U>
constexpr vec<4, T> & vec<4, T>::operator<<=(U scalar)
{
	return (*this = compute_vec4_shift_left<T, is_int<T>::value, sizeof(T) * 8>::call(*this, vec<4, T>(scalar)));
}

template <typename T>
template <typename U>
constexpr vec<4, T> & vec<4, T>::operator<<=(vec<1, U> const& v)
{
	return (*this = compute_vec4_shift_left<T, is_int<T>::value, sizeof(T) * 8>::call(*this, vec<4, T>(v)));
}

template <typename T>
template <typename U>
constexpr vec<4, T> & vec<4, T>::operator<<=(vec<4, U> const& v)
{
	return (*this = compute_vec4_shift_left<T, is_int<T>::value, sizeof(T) * 8>::call(*this, vec<4, T>(v)));
}

template <typename T>
template <typename U>
constexpr vec<4, T> & vec<4, T>::operator>>=(U scalar)
{
	return (*this = compute_vec4_shift_right<T, is_int<T>::value, sizeof(T) * 8>::call(*this, vec<4, T>(scalar)));
}

template <typename T>
template <typename U>
constexpr vec<4, T> & vec<4, T>::operator>>=(vec<1, U> const& v)
{
	return (*this = compute_vec4_shift_right<T, is_int<T>::value, sizeof(T) * 8>::call(*this, vec<4, T>(v)));
}

template <typename T>
template <typename U>
constexpr vec<4, T> & vec<4, T>::operator>>=(vec<4, U> const& v)
{
	return (*this = compute_vec4_shift_right<T, is_int<T>::value, sizeof(T) * 8>::call(*this, vec<4, T>(v)));
}

// -- Unary constant operators --

template <typename T>
constexpr vec<4, T> operator+(vec<4, T> const& v)
{
	return v;
}

template <typename T>
constexpr vec<4, T> operator-(vec<4, T> const& v)
{
	return vec<4, T>(0) -= v;
}

// -- Binary arithmetic operators --

template <typename T>
constexpr vec<4, T> operator+(vec<4, T> const& v, T const & scalar)
{
	return vec<4, T>(v) += scalar;
}

template <typename T>
constexpr vec<4, T> operator+(vec<4, T> const& v1, vec<1, T> const& v2)
{
	return vec<4, T>(v1) += v2;
}

template <typename T>
constexpr vec<4, T> operator+(T scalar, vec<4, T> const& v)
{
	return vec<4, T>(v) += scalar;
}

template <typename T>
constexpr vec<4, T> operator+(vec<1, T> const& v1, vec<4, T> const& v2)
{
	return vec<4, T>(v2) += v1;
}

template <typename T>
constexpr vec<4, T> operator+(vec<4, T> const& v1, vec<4, T> const& v2)
{
	return vec<4, T>(v1) += v2;
}

template <typename T>
constexpr vec<4, T> operator-(vec<4, T> const& v, T const & scalar)
{
	return vec<4, T>(v) -= scalar;
}

template <typename T>
constexpr vec<4, T> operator-(vec<4, T> const& v1, vec<1, T> const& v2)
{
	return vec<4, T>(v1) -= v2;
}

template <typename T>
constexpr vec<4, T> operator-(T scalar, vec<4, T> const& v)
{
	return vec<4, T>(scalar) -= v;
}

template <typename T>
constexpr vec<4, T> operator-(vec<1, T> const& v1, vec<4, T> const& v2)
{
	return vec<4, T>(v1.x) -= v2;
}

template <typename T>
constexpr vec<4, T> operator-(vec<4, T> const& v1, vec<4, T> const& v2)
{
	return vec<4, T>(v1) -= v2;
}

template <typename T>
constexpr vec<4, T> operator*(vec<4, T> const& v, T const & scalar)
{
	return vec<4, T>(v) *= scalar;
}

template <typename T>
constexpr vec<4, T> operator*(vec<4, T> const& v1, vec<1, T> const& v2)
{
	return vec<4, T>(v1) *= v2;
}

template <typename T>
constexpr vec<4, T> operator*(T scalar, vec<4, T> const& v)
{
	return vec<4, T>(v) *= scalar;
}

template <typename T>
constexpr vec<4, T> operator*(vec<1, T> const& v1, vec<4, T> const& v2)
{
	return vec<4, T>(v2) *= v1;
}

template <typename T>
constexpr vec<4, T> operator*(vec<4, T> const& v1, vec<4, T> const& v2)
{
	return vec<4, T>(v1) *= v2;
}

template <typename T>
constexpr vec<4, T> operator/(vec<4, T> const& v, T const & scalar)
{
	return vec<4, T>(v) /= scalar;
}

template <typename T>
constexpr vec<4, T> operator/(vec<4, T> const& v1, vec<1, T> const& v2)
{
	return vec<4, T>(v1) /= v2;
}

template <typename T>
constexpr vec<4, T> operator/(T scalar, vec<4, T> const& v)
{
	return vec<4, T>(scalar) /= v;
}

template <typename T>
constexpr vec<4, T> operator/(vec<1, T> const& v1, vec<4, T> const& v2)
{
	return vec<4, T>(v1.x) /= v2;
}

template <typename T>
constexpr vec<4, T> operator/(vec<4, T> const& v1, vec<4, T> const& v2)
{
	return vec<4, T>(v1) /= v2;
}

// -- Binary bit operators --

template <typename T>
constexpr vec<4, T> operator%(vec<4, T> const& v, T scalar)
{
	return vec<4, T>(v) %= scalar;
}

template <typename T>
constexpr vec<4, T> operator%(vec<4, T> const& v1, vec<1, T> const& v2)
{
	return vec<4, T>(v1) %= v2.x;
}

template <typename T>
constexpr vec<4, T> operator%(T scalar, vec<4, T> const& v)
{
	return vec<4, T>(scalar) %= v;
}

template <typename T>
constexpr vec<4, T> operator%(vec<1, T> const& scalar, vec<4, T> const& v)
{
	return vec<4, T>(scalar.x) %= v;
}

template <typename T>
constexpr vec<4, T> operator%(vec<4, T> const& v1, vec<4, T> const& v2)
{
	return vec<4, T>(v1) %= v2;
}

template <typename T>
constexpr vec<4, T> operator&(vec<4, T> const& v, T scalar)
{
	return vec<4, T>(v) &= scalar;
}

template <typename T>
constexpr vec<4, T> operator&(vec<4, T> const& v, vec<1, T> const& scalar)
{
	return vec<4, T>(v) &= scalar;
}

template <typename T>
constexpr vec<4, T> operator&(T scalar, vec<4, T> const& v)
{
	return vec<4, T>(scalar) &= v;
}

template <typename T>
constexpr vec<4, T> operator&(vec<1, T> const& v1, vec<4, T> const& v2)
{
	return vec<4, T>(v1.x) &= v2;
}

template <typename T>
constexpr vec<4, T> operator&(vec<4, T> const& v1, vec<4, T> const& v2)
{
	return vec<4, T>(v1) &= v2;
}

template <typename T>
constexpr vec<4, T> operator|(vec<4, T> const& v, T scalar)
{
	return vec<4, T>(v) |= scalar;
}

template <typename T>
constexpr vec<4, T> operator|(vec<4, T> const& v1, vec<1, T> const& v2)
{
	return vec<4, T>(v1) |= v2.x;
}

template <typename T>
constexpr vec<4, T> operator|(T scalar, vec<4, T> const& v)
{
	return vec<4, T>(scalar) |= v;
}

template <typename T>
constexpr vec<4, T> operator|(vec<1, T> const& v1, vec<4, T> const& v2)
{
	return vec<4, T>(v1.x) |= v2;
}

template <typename T>
constexpr vec<4, T> operator|(vec<4, T> const& v1, vec<4, T> const& v2)
{
	return vec<4, T>(v1) |= v2;
}

template <typename T>
constexpr vec<4, T> operator^(vec<4, T> const& v, T scalar)
{
	return vec<4, T>(v) ^= scalar;
}

template <typename T>
constexpr vec<4, T> operator^(vec<4, T> const& v1, vec<1, T> const& v2)
{
	return vec<4, T>(v1) ^= v2.x;
}

template <typename T>
constexpr vec<4, T> operator^(T scalar, vec<4, T> const& v)
{
	return vec<4, T>(scalar) ^= v;
}

template <typename T>
constexpr vec<4, T> operator^(vec<1, T> const& v1, vec<4, T> const& v2)
{
	return vec<4, T>(v1.x) ^= v2;
}

template <typename T>
constexpr vec<4, T> operator^(vec<4, T> const& v1, vec<4, T> const& v2)
{
	return vec<4, T>(v1) ^= v2;
}

template <typename T>
constexpr vec<4, T> operator<<(vec<4, T> const& v, T scalar)
{
	return vec<4, T>(v) <<= scalar;
}

template <typename T>
constexpr vec<4, T> operator<<(vec<4, T> const& v1, vec<1, T> const& v2)
{
	return vec<4, T>(v1) <<= v2.x;
}

template <typename T>
constexpr vec<4, T> operator<<(T scalar, vec<4, T> const& v)
{
	return vec<4, T>(scalar) <<= v;
}

template <typename T>
constexpr vec<4, T> operator<<(vec<1, T> const& v1, vec<4, T> const& v2)
{
	return vec<4, T>(v1.x) <<= v2;
}

template <typename T>
constexpr vec<4, T> operator<<(vec<4, T> const& v1, vec<4, T> const& v2)
{
	return vec<4, T>(v1) <<= v2;
}

template <typename T>
constexpr vec<4, T> operator>>(vec<4, T> const& v, T scalar)
{
	return vec<4, T>(v) >>= scalar;
}

template <typename T>
constexpr vec<4, T> operator>>(vec<4, T> const& v1, vec<1, T> const& v2)
{
	return vec<4, T>(v1) >>= v2.x;
}

template <typename T>
constexpr vec<4, T> operator>>(T scalar, vec<4, T> const& v)
{
	return vec<4, T>(scalar) >>= v;
}

template <typename T>
constexpr vec<4, T> operator>>(vec<1, T> const& v1, vec<4, T> const& v2)
{
	return vec<4, T>(v1.x) >>= v2;
}

template <typename T>
constexpr vec<4, T> operator>>(vec<4, T> const& v1, vec<4, T> const& v2)
{
	return vec<4, T>(v1) >>= v2;
}

template <typename T>
constexpr vec<4, T> operator~(vec<4, T> const& v)
{
	return compute_vec4_bitwise_not<T, is_int<T>::value, sizeof(T) * 8>::call(v);
}

// -- Boolean operators --

template <typename T>
constexpr bool operator==(vec<4, T> const& v1, vec<4, T> const& v2)
{
	return compute_vec4_equal<T, is_int<T>::value, sizeof(T) * 8>::call(v1, v2);
}

template <typename T>
constexpr bool operator!=(vec<4, T> const& v1, vec<4, T> const& v2)
{
	return compute_vec4_nequal<T, is_int<T>::value, sizeof(T) * 8>::call(v1, v2);
}

constexpr vec<4, bool> operator&&(vec<4, bool> const& v1, vec<4, bool> const& v2)
{
	return vec<4, bool>(v1.x && v2.x, v1.y && v2.y, v1.z && v2.z, v1.w && v2.w);
}

constexpr vec<4, bool> operator||(vec<4, bool> const& v1, vec<4, bool> const& v2)
{
	return vec<4, bool>(v1.x || v2.x, v1.y || v2.y, v1.z || v2.z, v1.w || v2.w);
}

} // math

} // Kinai
