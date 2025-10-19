#pragma once

# include "type.hpp"

namespace Kinai
{

namespace math
{

template<typename T>
struct vec<3, T>
{
	// -- Implementation detail --

	typedef T				value_type;
	typedef vec<3, T>		type;
	typedef vec<3, bool>	bool_type;
	typedef length_t		length_type;

	// -- Data --
	union { T x, r, s; };
	union { T y, g, t; };
	union { T z, b, p; };

	// -- Component accesses --

	/// Return the count of components of the vector
	static constexpr length_type length(){return 3;}

	constexpr T&		operator[](length_type i);
	constexpr T const&	operator[](length_type i) const;

	// -- Implicit basic constructors --

	constexpr vec() = default;
	constexpr vec(vec const& v) = default;

	// -- Explicit basic constructors --

	constexpr explicit vec(T scalar);
	constexpr vec(T a, T b, T c);

	// -- Conversion scalar constructors --

	template<typename U>
	constexpr explicit vec(vec<1, U> const& v);

	template<typename X, typename Y, typename Z>
	constexpr vec(X x, Y y, Z z);
	template<typename X, typename Y, typename Z>
	constexpr vec(vec<1, X> const& _x, Y _y, Z _z);
	template<typename X, typename Y, typename Z>
	constexpr vec(X _x, vec<1, Y> const& _y, Z _z);
	template<typename X, typename Y, typename Z>
	constexpr vec(vec<1, X> const& _x, vec<1, Y> const& _y, Z _z);
	template<typename X, typename Y, typename Z>
	constexpr vec(X _x, Y _y, vec<1, Z> const& _z);
	template<typename X, typename Y, typename Z>
	constexpr vec(vec<1, X> const& _x, Y _y, vec<1, Z> const& _z);
	template<typename X, typename Y, typename Z>
	constexpr vec(X _x, vec<1, Y> const& _y, vec<1, Z> const& _z);
	template<typename X, typename Y, typename Z>
	constexpr vec(vec<1, X> const& _x, vec<1, Y> const& _y, vec<1, Z> const& _z);

	// -- Conversion vector constructors --

	template<typename A, typename B>
	constexpr vec(vec<2, A> const& _xy, B _z);
	template<typename A, typename B>
	constexpr vec(vec<2, A> const& _xy, vec<1, B> const& _z);
	template<typename A, typename B>
	constexpr vec(A _x, vec<2, B> const& _yz);
	template<typename A, typename B>
	constexpr vec(vec<1, A> const& _x, vec<2, B> const& _yz);
	template<typename U>
	constexpr explicit vec(vec<4, U> const& v);

	template<typename U>
	constexpr explicit vec(vec<3, U> const& v);

	// -- Unary arithmetic operators --

	constexpr vec<3, T>& operator=(vec<3, T> const& v) = default;

	template<typename U>
	constexpr vec<3, T> & operator=(vec<3, U> const& v);
	template<typename U>
	constexpr vec<3, T> & operator+=(U scalar);
	template<typename U>
	constexpr vec<3, T> & operator+=(vec<1, U> const& v);
	template<typename U>
	constexpr vec<3, T> & operator+=(vec<3, U> const& v);
	template<typename U>
	constexpr vec<3, T> & operator-=(U scalar);
	template<typename U>
	constexpr vec<3, T> & operator-=(vec<1, U> const& v);
	template<typename U>
	constexpr vec<3, T> & operator-=(vec<3, U> const& v);
	template<typename U>
	constexpr vec<3, T> & operator*=(U scalar);
	template<typename U>
	constexpr vec<3, T> & operator*=(vec<1, U> const& v);
	template<typename U>
	constexpr vec<3, T> & operator*=(vec<3, U> const& v);
	template<typename U>
	constexpr vec<3, T> & operator/=(U scalar);
	template<typename U>
	constexpr vec<3, T> & operator/=(vec<1, U> const& v);
	template<typename U>
	constexpr vec<3, T> & operator/=(vec<3, U> const& v);

	// -- Increment and decrement operators --

	constexpr vec<3, T> & operator++();
	constexpr vec<3, T> & operator--();
	constexpr vec<3, T> operator++(int);
	constexpr vec<3, T> operator--(int);

	// -- Unary bit operators --

	template<typename U>
	constexpr vec<3, T> & operator%=(U scalar);
	template<typename U>
	constexpr vec<3, T> & operator%=(vec<1, U> const& v);
	template<typename U>
	constexpr vec<3, T> & operator%=(vec<3, U> const& v);
	template<typename U>
	constexpr vec<3, T> & operator&=(U scalar);
	template<typename U>
	constexpr vec<3, T> & operator&=(vec<1, U> const& v);
	template<typename U>
	constexpr vec<3, T> & operator&=(vec<3, U> const& v);
	template<typename U>
	constexpr vec<3, T> & operator|=(U scalar);
	template<typename U>
	constexpr vec<3, T> & operator|=(vec<1, U> const& v);
	template<typename U>
	constexpr vec<3, T> & operator|=(vec<3, U> const& v);
	template<typename U>
	constexpr vec<3, T> & operator^=(U scalar);
	template<typename U>
	constexpr vec<3, T> & operator^=(vec<1, U> const& v);
	template<typename U>
	constexpr vec<3, T> & operator^=(vec<3, U> const& v);
	template<typename U>
	constexpr vec<3, T> & operator<<=(U scalar);
	template<typename U>
	constexpr vec<3, T> & operator<<=(vec<1, U> const& v);
	template<typename U>
	constexpr vec<3, T> & operator<<=(vec<3, U> const& v);
	template<typename U>
	constexpr vec<3, T> & operator>>=(U scalar);
	template<typename U>
	constexpr vec<3, T> & operator>>=(vec<1, U> const& v);
	template<typename U>
	constexpr vec<3, T> & operator>>=(vec<3, U> const& v);
};

// -- Explicit basic constructors --

template<typename T>
inline constexpr vec<3, T>::vec(T scalar)
	: x(scalar), y(scalar), z(scalar)
{}

template <typename T>
inline constexpr vec<3, T>::vec(T _x, T _y, T _z)
	: x(_x), y(_y), z(_z)
{}

// -- Conversion scalar constructors --

template<typename T>
template<typename U>
inline constexpr vec<3, T>::vec(vec<1, U> const& v)
	: x(static_cast<T>(v.x))
	, y(static_cast<T>(v.x))
	, z(static_cast<T>(v.x))
{}

template<typename T>
template<typename X, typename Y, typename Z>
inline constexpr vec<3, T>::vec(X _x, Y _y, Z _z)
	: x(static_cast<T>(_x))
	, y(static_cast<T>(_y))
	, z(static_cast<T>(_z))
{}

template<typename T>
template<typename X, typename Y, typename Z>
inline constexpr vec<3, T>::vec(vec<1, X> const& _x, Y _y, Z _z)
	: x(static_cast<T>(_x.x))
	, y(static_cast<T>(_y))
	, z(static_cast<T>(_z))
{}

template<typename T>
template<typename X, typename Y, typename Z>
inline constexpr vec<3, T>::vec(X _x, vec<1, Y> const& _y, Z _z)
	: x(static_cast<T>(_x))
	, y(static_cast<T>(_y.x))
	, z(static_cast<T>(_z))
{}

template<typename T>
template<typename X, typename Y, typename Z>
inline constexpr vec<3, T>::vec(vec<1, X> const& _x, vec<1, Y> const& _y, Z _z)
	: x(static_cast<T>(_x.x))
	, y(static_cast<T>(_y.x))
	, z(static_cast<T>(_z))
{}

template<typename T>
template<typename X, typename Y, typename Z>
inline constexpr vec<3, T>::vec(X _x, Y _y, vec<1, Z> const& _z)
	: x(static_cast<T>(_x))
	, y(static_cast<T>(_y))
	, z(static_cast<T>(_z.x))
{}

template<typename T>
template<typename X, typename Y, typename Z>
inline constexpr vec<3, T>::vec(vec<1, X> const& _x, Y _y, vec<1, Z> const& _z)
	: x(static_cast<T>(_x.x))
	, y(static_cast<T>(_y))
	, z(static_cast<T>(_z.x))
{}

template<typename T>
template<typename X, typename Y, typename Z>
inline constexpr vec<3, T>::vec(X _x, vec<1, Y> const& _y, vec<1, Z> const& _z)
	: x(static_cast<T>(_x))
	, y(static_cast<T>(_y.x))
	, z(static_cast<T>(_z.x))
{}

template<typename T>
template<typename X, typename Y, typename Z>
inline constexpr vec<3, T>::vec(vec<1, X> const& _x, vec<1, Y> const& _y, vec<1, Z> const& _z)
	: x(static_cast<T>(_x.x))
	, y(static_cast<T>(_y.x))
	, z(static_cast<T>(_z.x))
{}

// -- Conversion vector constructors --

template<typename T>
template<typename A, typename B>
inline constexpr vec<3, T>::vec(vec<2, A> const& _xy, B _z)
	: x(static_cast<T>(_xy.x))
	, y(static_cast<T>(_xy.y))
	, z(static_cast<T>(_z))
{}

template<typename T>
template<typename A, typename B>
inline constexpr vec<3, T>::vec(vec<2, A> const& _xy, vec<1, B> const& _z)
	: x(static_cast<T>(_xy.x))
	, y(static_cast<T>(_xy.y))
	, z(static_cast<T>(_z.x))
{}

template<typename T>
template<typename A, typename B>
inline constexpr vec<3, T>::vec(A _x, vec<2, B> const& _yz)
	: x(static_cast<T>(_x))
	, y(static_cast<T>(_yz.x))
	, z(static_cast<T>(_yz.y))
{}

template<typename T>
template<typename A, typename B>
inline constexpr vec<3, T>::vec(vec<1, A> const& _x, vec<2, B> const& _yz)
	: x(static_cast<T>(_x.x))
	, y(static_cast<T>(_yz.x))
	, z(static_cast<T>(_yz.y))
{}

template<typename T>
template<typename U>
inline constexpr vec<3, T>::vec(vec<3, U> const& v)
	: x(static_cast<T>(v.x))
	, y(static_cast<T>(v.y))
	, z(static_cast<T>(v.z))
{}

template<typename T>
template<typename U>
inline constexpr vec<3, T>::vec(vec<4, U> const& v)
	: x(static_cast<T>(v.x))
	, y(static_cast<T>(v.y))
	, z(static_cast<T>(v.z))
{}

// -- Component accesses --

template<typename T>
inline constexpr T & vec<3, T>::operator[](typename vec<3, T>::length_type i)
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
	}
}

template<typename T>
inline constexpr T const& vec<3, T>::operator[](typename vec<3, T>::length_type i) const
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
	}
}

// -- Unary arithmetic operators --

template<typename T>
template<typename U>
inline constexpr vec<3, T>& vec<3, T>::operator=(vec<3, U> const& v)
{
	this->x = static_cast<T>(v.x);
	this->y = static_cast<T>(v.y);
	this->z = static_cast<T>(v.z);
	return *this;
}

template<typename T>
template<typename U>
inline constexpr vec<3, T> & vec<3, T>::operator+=(U scalar)
{
	this->x += static_cast<T>(scalar);
	this->y += static_cast<T>(scalar);
	this->z += static_cast<T>(scalar);
	return *this;
}

template<typename T>
template<typename U>
inline constexpr vec<3, T> & vec<3, T>::operator+=(vec<1, U> const& v)
{
	this->x += static_cast<T>(v.x);
	this->y += static_cast<T>(v.x);
	this->z += static_cast<T>(v.x);
	return *this;
}

template<typename T>
template<typename U>
inline constexpr vec<3, T> & vec<3, T>::operator+=(vec<3, U> const& v)
{
	this->x += static_cast<T>(v.x);
	this->y += static_cast<T>(v.y);
	this->z += static_cast<T>(v.z);
	return *this;
}

template<typename T>
template<typename U>
inline constexpr vec<3, T> & vec<3, T>::operator-=(U scalar)
{
	this->x -= static_cast<T>(scalar);
	this->y -= static_cast<T>(scalar);
	this->z -= static_cast<T>(scalar);
	return *this;
}

template<typename T>
template<typename U>
inline constexpr vec<3, T> & vec<3, T>::operator-=(vec<1, U> const& v)
{
	this->x -= static_cast<T>(v.x);
	this->y -= static_cast<T>(v.x);
	this->z -= static_cast<T>(v.x);
	return *this;
}

template<typename T>
template<typename U>
inline constexpr vec<3, T> & vec<3, T>::operator-=(vec<3, U> const& v)
{
	this->x -= static_cast<T>(v.x);
	this->y -= static_cast<T>(v.y);
	this->z -= static_cast<T>(v.z);
	return *this;
}

template<typename T>
template<typename U>
inline constexpr vec<3, T> & vec<3, T>::operator*=(U scalar)
{
	this->x *= static_cast<T>(scalar);
	this->y *= static_cast<T>(scalar);
	this->z *= static_cast<T>(scalar);
	return *this;
}

template<typename T>
template<typename U>
inline constexpr vec<3, T> & vec<3, T>::operator*=(vec<1, U> const& v)
{
	this->x *= static_cast<T>(v.x);
	this->y *= static_cast<T>(v.x);
	this->z *= static_cast<T>(v.x);
	return *this;
}

template<typename T>
template<typename U>
inline constexpr vec<3, T> & vec<3, T>::operator*=(vec<3, U> const& v)
{
	this->x *= static_cast<T>(v.x);
	this->y *= static_cast<T>(v.y);
	this->z *= static_cast<T>(v.z);
	return *this;
}

template<typename T>
template<typename U>
inline constexpr vec<3, T> & vec<3, T>::operator/=(U v)
{
	this->x /= static_cast<T>(v);
	this->y /= static_cast<T>(v);
	this->z /= static_cast<T>(v);
	return *this;
}

template<typename T>
template<typename U>
inline constexpr vec<3, T> & vec<3, T>::operator/=(vec<1, U> const& v)
{
	this->x /= static_cast<T>(v.x);
	this->y /= static_cast<T>(v.x);
	this->z /= static_cast<T>(v.x);
	return *this;
}

template<typename T>
template<typename U>
inline constexpr vec<3, T> & vec<3, T>::operator/=(vec<3, U> const& v)
{
	this->x /= static_cast<T>(v.x);
	this->y /= static_cast<T>(v.y);
	this->z /= static_cast<T>(v.z);
	return *this;
}

// -- Increment and decrement operators --

template<typename T>
inline constexpr vec<3, T> & vec<3, T>::operator++()
{
	++this->x;
	++this->y;
	++this->z;
	return *this;
}

template<typename T>
inline constexpr vec<3, T> & vec<3, T>::operator--()
{
	--this->x;
	--this->y;
	--this->z;
	return *this;
}

template<typename T>
inline constexpr vec<3, T> vec<3, T>::operator++(int)
{
	vec<3, T> Result(*this);
	++*this;
	return Result;
}

template<typename T>
inline constexpr vec<3, T> vec<3, T>::operator--(int)
{
	vec<3, T> Result(*this);
	--*this;
	return Result;
}

// -- Unary bit operators --

template<typename T>
template<typename U>
inline constexpr vec<3, T> & vec<3, T>::operator%=(U scalar)
{
	this->x %= scalar;
	this->y %= scalar;
	this->z %= scalar;
	return *this;
}

template<typename T>
template<typename U>
inline constexpr vec<3, T> & vec<3, T>::operator%=(vec<1, U> const& v)
{
	this->x %= v.x;
	this->y %= v.x;
	this->z %= v.x;
	return *this;
}

template<typename T>
template<typename U>
inline constexpr vec<3, T> & vec<3, T>::operator%=(vec<3, U> const& v)
{
	this->x %= v.x;
	this->y %= v.y;
	this->z %= v.z;
	return *this;
}

template<typename T>
template<typename U>
inline constexpr vec<3, T> & vec<3, T>::operator&=(U scalar)
{
	this->x &= scalar;
	this->y &= scalar;
	this->z &= scalar;
	return *this;
}

template<typename T>
template<typename U>
inline constexpr vec<3, T> & vec<3, T>::operator&=(vec<1, U> const& v)
{
	this->x &= v.x;
	this->y &= v.x;
	this->z &= v.x;
	return *this;
}

template<typename T>
template<typename U>
inline constexpr vec<3, T> & vec<3, T>::operator&=(vec<3, U> const& v)
{
	this->x &= v.x;
	this->y &= v.y;
	this->z &= v.z;
	return *this;
}

template<typename T>
template<typename U>
inline constexpr vec<3, T> & vec<3, T>::operator|=(U scalar)
{
	this->x |= scalar;
	this->y |= scalar;
	this->z |= scalar;
	return *this;
}

template<typename T>
template<typename U>
inline constexpr vec<3, T> & vec<3, T>::operator|=(vec<1, U> const& v)
{
	this->x |= v.x;
	this->y |= v.x;
	this->z |= v.x;
	return *this;
}

template<typename T>
template<typename U>
inline constexpr vec<3, T> & vec<3, T>::operator|=(vec<3, U> const& v)
{
	this->x |= v.x;
	this->y |= v.y;
	this->z |= v.z;
	return *this;
}

template<typename T>
template<typename U>
inline constexpr vec<3, T> & vec<3, T>::operator^=(U scalar)
{
	this->x ^= scalar;
	this->y ^= scalar;
	this->z ^= scalar;
	return *this;
}

template<typename T>
template<typename U>
inline constexpr vec<3, T> & vec<3, T>::operator^=(vec<1, U> const& v)
{
	this->x ^= v.x;
	this->y ^= v.x;
	this->z ^= v.x;
	return *this;
}

template<typename T>
template<typename U>
inline constexpr vec<3, T> & vec<3, T>::operator^=(vec<3, U> const& v)
{
	this->x ^= v.x;
	this->y ^= v.y;
	this->z ^= v.z;
	return *this;
}

template<typename T>
template<typename U>
inline constexpr vec<3, T> & vec<3, T>::operator<<=(U scalar)
{
	this->x <<= scalar;
	this->y <<= scalar;
	this->z <<= scalar;
	return *this;
}

template<typename T>
template<typename U>
inline constexpr vec<3, T> & vec<3, T>::operator<<=(vec<1, U> const& v)
{
	this->x <<= static_cast<T>(v.x);
	this->y <<= static_cast<T>(v.x);
	this->z <<= static_cast<T>(v.x);
	return *this;
}

template<typename T>
template<typename U>
inline constexpr vec<3, T> & vec<3, T>::operator<<=(vec<3, U> const& v)
{
	this->x <<= static_cast<T>(v.x);
	this->y <<= static_cast<T>(v.y);
	this->z <<= static_cast<T>(v.z);
	return *this;
}

template<typename T>
template<typename U>
inline constexpr vec<3, T> & vec<3, T>::operator>>=(U scalar)
{
	this->x >>= static_cast<T>(scalar);
	this->y >>= static_cast<T>(scalar);
	this->z >>= static_cast<T>(scalar);
	return *this;
}

template<typename T>
template<typename U>
inline constexpr vec<3, T> & vec<3, T>::operator>>=(vec<1, U> const& v)
{
	this->x >>= static_cast<T>(v.x);
	this->y >>= static_cast<T>(v.x);
	this->z >>= static_cast<T>(v.x);
	return *this;
}

template<typename T>
template<typename U>
inline constexpr vec<3, T> & vec<3, T>::operator>>=(vec<3, U> const& v)
{
	this->x >>= static_cast<T>(v.x);
	this->y >>= static_cast<T>(v.y);
	this->z >>= static_cast<T>(v.z);
	return *this;
}

// -- Unary arithmetic operators --

template<typename T>
inline constexpr vec<3, T> operator+(vec<3, T> const& v)
{
	return v;
}

template<typename T>
inline constexpr vec<3, T> operator-(vec<3, T> const& v)
{
	return vec<3, T>(
		-v.x,
		-v.y,
		-v.z);
}

// -- Binary arithmetic operators --

template<typename T>
inline constexpr vec<3, T> operator+(vec<3, T> const& v, T scalar)
{
	return vec<3, T>(
		v.x + scalar,
		v.y + scalar,
		v.z + scalar);
}

template<typename T>
inline constexpr vec<3, T> operator+(vec<3, T> const& v, vec<1, T> const& scalar)
{
	return vec<3, T>(
		v.x + scalar.x,
		v.y + scalar.x,
		v.z + scalar.x);
}

template<typename T>
inline constexpr vec<3, T> operator+(T scalar, vec<3, T> const& v)
{
	return vec<3, T>(
		scalar + v.x,
		scalar + v.y,
		scalar + v.z);
}

template<typename T>
inline constexpr vec<3, T> operator+(vec<1, T> const& scalar, vec<3, T> const& v)
{
	return vec<3, T>(
		scalar.x + v.x,
		scalar.x + v.y,
		scalar.x + v.z);
}

template<typename T>
inline constexpr vec<3, T> operator+(vec<3, T> const& v1, vec<3, T> const& v2)
{
	return vec<3, T>(
		v1.x + v2.x,
		v1.y + v2.y,
		v1.z + v2.z);
}

template<typename T>
inline constexpr vec<3, T> operator-(vec<3, T> const& v, T scalar)
{
	return vec<3, T>(
		v.x - scalar,
		v.y - scalar,
		v.z - scalar);
}

template<typename T>
inline constexpr vec<3, T> operator-(vec<3, T> const& v, vec<1, T> const& scalar)
{
	return vec<3, T>(
		v.x - scalar.x,
		v.y - scalar.x,
		v.z - scalar.x);
}

template<typename T>
inline constexpr vec<3, T> operator-(T scalar, vec<3, T> const& v)
{
	return vec<3, T>(
		scalar - v.x,
		scalar - v.y,
		scalar - v.z);
}

template<typename T>
inline constexpr vec<3, T> operator-(vec<1, T> const& scalar, vec<3, T> const& v)
{
	return vec<3, T>(
		scalar.x - v.x,
		scalar.x - v.y,
		scalar.x - v.z);
}

template<typename T>
inline constexpr vec<3, T> operator-(vec<3, T> const& v1, vec<3, T> const& v2)
{
	return vec<3, T>(
		v1.x - v2.x,
		v1.y - v2.y,
		v1.z - v2.z);
}

template<typename T>
inline constexpr vec<3, T> operator*(vec<3, T> const& v, T scalar)
{
	return vec<3, T>(
		v.x * scalar,
		v.y * scalar,
		v.z * scalar);
}

template<typename T>
inline constexpr vec<3, T> operator*(vec<3, T> const& v, vec<1, T> const& scalar)
{
	return vec<3, T>(
		v.x * scalar.x,
		v.y * scalar.x,
		v.z * scalar.x);
}

template<typename T>
inline constexpr vec<3, T> operator*(T scalar, vec<3, T> const& v)
{
	return vec<3, T>(
		scalar * v.x,
		scalar * v.y,
		scalar * v.z);
}

template<typename T>
inline constexpr vec<3, T> operator*(vec<1, T> const& scalar, vec<3, T> const& v)
{
	return vec<3, T>(
		scalar.x * v.x,
		scalar.x * v.y,
		scalar.x * v.z);
}

template<typename T>
inline constexpr vec<3, T> operator*(vec<3, T> const& v1, vec<3, T> const& v2)
{
	return vec<3, T>(
		v1.x * v2.x,
		v1.y * v2.y,
		v1.z * v2.z);
}

template<typename T>
inline constexpr vec<3, T> operator/(vec<3, T> const& v, T scalar)
{
	return vec<3, T>(
		v.x / scalar,
		v.y / scalar,
		v.z / scalar);
}

template<typename T>
inline constexpr vec<3, T> operator/(vec<3, T> const& v, vec<1, T> const& scalar)
{
	return vec<3, T>(
		v.x / scalar.x,
		v.y / scalar.x,
		v.z / scalar.x);
}

template<typename T>
inline constexpr vec<3, T> operator/(T scalar, vec<3, T> const& v)
{
	return vec<3, T>(
		scalar / v.x,
		scalar / v.y,
		scalar / v.z);
}

template<typename T>
inline constexpr vec<3, T> operator/(vec<1, T> const& scalar, vec<3, T> const& v)
{
	return vec<3, T>(
		scalar.x / v.x,
		scalar.x / v.y,
		scalar.x / v.z);
}

template<typename T>
inline constexpr vec<3, T> operator/(vec<3, T> const& v1, vec<3, T> const& v2)
{
	return vec<3, T>(
		v1.x / v2.x,
		v1.y / v2.y,
		v1.z / v2.z);
}

// -- Binary bit operators --

template<typename T>
inline constexpr vec<3, T> operator%(vec<3, T> const& v, T scalar)
{
	return vec<3, T>(
		v.x % scalar,
		v.y % scalar,
		v.z % scalar);
}

template<typename T>
inline constexpr vec<3, T> operator%(vec<3, T> const& v, vec<1, T> const& scalar)
{
	return vec<3, T>(
		v.x % scalar.x,
		v.y % scalar.x,
		v.z % scalar.x);
}

template<typename T>
inline constexpr vec<3, T> operator%(T scalar, vec<3, T> const& v)
{
	return vec<3, T>(
		scalar % v.x,
		scalar % v.y,
		scalar % v.z);
}

template<typename T>
inline constexpr vec<3, T> operator%(vec<1, T> const& scalar, vec<3, T> const& v)
{
	return vec<3, T>(
		scalar.x % v.x,
		scalar.x % v.y,
		scalar.x % v.z);
}

template<typename T>
inline constexpr vec<3, T> operator%(vec<3, T> const& v1, vec<3, T> const& v2)
{
	return vec<3, T>(
		v1.x % v2.x,
		v1.y % v2.y,
		v1.z % v2.z);
}

template<typename T>
inline constexpr vec<3, T> operator&(vec<3, T> const& v, T scalar)
{
	return vec<3, T>(
		v.x & scalar,
		v.y & scalar,
		v.z & scalar);
}

template<typename T>
inline constexpr vec<3, T> operator&(vec<3, T> const& v, vec<1, T> const& scalar)
{
	return vec<3, T>(
		v.x & scalar.x,
		v.y & scalar.x,
		v.z & scalar.x);
}

template<typename T>
inline constexpr vec<3, T> operator&(T scalar, vec<3, T> const& v)
{
	return vec<3, T>(
		scalar & v.x,
		scalar & v.y,
		scalar & v.z);
}

template<typename T>
inline constexpr vec<3, T> operator&(vec<1, T> const& scalar, vec<3, T> const& v)
{
	return vec<3, T>(
		scalar.x & v.x,
		scalar.x & v.y,
		scalar.x & v.z);
}

template<typename T>
inline constexpr vec<3, T> operator&(vec<3, T> const& v1, vec<3, T> const& v2)
{
	return vec<3, T>(
		v1.x & v2.x,
		v1.y & v2.y,
		v1.z & v2.z);
}

template<typename T>
inline constexpr vec<3, T> operator|(vec<3, T> const& v, T scalar)
{
	return vec<3, T>(
		v.x | scalar,
		v.y | scalar,
		v.z | scalar);
}

template<typename T>
inline constexpr vec<3, T> operator|(vec<3, T> const& v, vec<1, T> const& scalar)
{
	return vec<3, T>(
		v.x | scalar.x,
		v.y | scalar.x,
		v.z | scalar.x);
}

template<typename T>
inline constexpr vec<3, T> operator|(T scalar, vec<3, T> const& v)
{
	return vec<3, T>(
		scalar | v.x,
		scalar | v.y,
		scalar | v.z);
}

template<typename T>
inline constexpr vec<3, T> operator|(vec<1, T> const& scalar, vec<3, T> const& v)
{
	return vec<3, T>(
		scalar.x | v.x,
		scalar.x | v.y,
		scalar.x | v.z);
}

template<typename T>
inline constexpr vec<3, T> operator|(vec<3, T> const& v1, vec<3, T> const& v2)
{
	return vec<3, T>(
		v1.x | v2.x,
		v1.y | v2.y,
		v1.z | v2.z);
}

template<typename T>
inline constexpr vec<3, T> operator^(vec<3, T> const& v, T scalar)
{
	return vec<3, T>(
		v.x ^ scalar,
		v.y ^ scalar,
		v.z ^ scalar);
}

template<typename T>
inline constexpr vec<3, T> operator^(vec<3, T> const& v, vec<1, T> const& scalar)
{
	return vec<3, T>(
		v.x ^ scalar.x,
		v.y ^ scalar.x,
		v.z ^ scalar.x);
}

template<typename T>
inline constexpr vec<3, T> operator^(T scalar, vec<3, T> const& v)
{
	return vec<3, T>(
		scalar ^ v.x,
		scalar ^ v.y,
		scalar ^ v.z);
}

template<typename T>
inline constexpr vec<3, T> operator^(vec<1, T> const& scalar, vec<3, T> const& v)
{
	return vec<3, T>(
		scalar.x ^ v.x,
		scalar.x ^ v.y,
		scalar.x ^ v.z);
}

template<typename T>
inline constexpr vec<3, T> operator^(vec<3, T> const& v1, vec<3, T> const& v2)
{
	return vec<3, T>(
		v1.x ^ v2.x,
		v1.y ^ v2.y,
		v1.z ^ v2.z);
}

template<typename T>
inline constexpr vec<3, T> operator<<(vec<3, T> const& v, T scalar)
{
	return vec<3, T>(
		v.x << scalar,
		v.y << scalar,
		v.z << scalar);
}

template<typename T>
inline constexpr vec<3, T> operator<<(vec<3, T> const& v, vec<1, T> const& scalar)
{
	return vec<3, T>(
		v.x << scalar.x,
		v.y << scalar.x,
		v.z << scalar.x);
}

template<typename T>
inline constexpr vec<3, T> operator<<(T scalar, vec<3, T> const& v)
{
	return vec<3, T>(
		scalar << v.x,
		scalar << v.y,
		scalar << v.z);
}

template<typename T>
inline constexpr vec<3, T> operator<<(vec<1, T> const& scalar, vec<3, T> const& v)
{
	return vec<3, T>(
		scalar.x << v.x,
		scalar.x << v.y,
		scalar.x << v.z);
}

template<typename T>
inline constexpr vec<3, T> operator<<(vec<3, T> const& v1, vec<3, T> const& v2)
{
	return vec<3, T>(
		v1.x << v2.x,
		v1.y << v2.y,
		v1.z << v2.z);
}

template<typename T>
inline constexpr vec<3, T> operator>>(vec<3, T> const& v, T scalar)
{
	return vec<3, T>(
		v.x >> scalar,
		v.y >> scalar,
		v.z >> scalar);
}

template<typename T>
inline constexpr vec<3, T> operator>>(vec<3, T> const& v, vec<1, T> const& scalar)
{
	return vec<3, T>(
		v.x >> scalar.x,
		v.y >> scalar.x,
		v.z >> scalar.x);
}

template<typename T>
inline constexpr vec<3, T> operator>>(T scalar, vec<3, T> const& v)
{
	return vec<3, T>(
		scalar >> v.x,
		scalar >> v.y,
		scalar >> v.z);
}

template<typename T>
inline constexpr vec<3, T> operator>>(vec<1, T> const& scalar, vec<3, T> const& v)
{
	return vec<3, T>(
		scalar.x >> v.x,
		scalar.x >> v.y,
		scalar.x >> v.z);
}

template<typename T>
inline constexpr vec<3, T> operator>>(vec<3, T> const& v1, vec<3, T> const& v2)
{
	return vec<3, T>(
		v1.x >> v2.x,
		v1.y >> v2.y,
		v1.z >> v2.z);
}

template<typename T>
inline constexpr vec<3, T> operator~(vec<3, T> const& v)
{
	return vec<3, T>(
		~v.x,
		~v.y,
		~v.z);
}

// -- Boolean operators --

template<typename T>
inline constexpr bool operator==(vec<3, T> const& v1, vec<3, T> const& v2)
{
	return
		compute_equal<T, std::numeric_limits<T>::is_iec559>::call(v1.x, v2.x) &&
		compute_equal<T, std::numeric_limits<T>::is_iec559>::call(v1.y, v2.y) &&
		compute_equal<T, std::numeric_limits<T>::is_iec559>::call(v1.z, v2.z);
}

template<typename T>
inline constexpr bool operator!=(vec<3, T> const& v1, vec<3, T> const& v2)
{
	return !(v1 == v2);
}

inline constexpr vec<3, bool> operator&&(vec<3, bool> const& v1, vec<3, bool> const& v2)
{
	return vec<3, bool>(v1.x && v2.x, v1.y && v2.y, v1.z && v2.z);
}

inline constexpr vec<3, bool> operator||(vec<3, bool> const& v1, vec<3, bool> const& v2)
{
	return vec<3, bool>(v1.x || v2.x, v1.y || v2.y, v1.z || v2.z);
}

} // math

} // Kinai
