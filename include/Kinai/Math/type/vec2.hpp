#pragma once

# include "type.hpp"

namespace Kinai
{

namespace math
{

template <typename T>
struct vec<2, T>
{
	// -- Implementation detail --

	typedef T				value_type;
	typedef vec<2, T>		type;
	typedef vec<2, bool>	bool_type;
	typedef length_t		length_type;

	// -- Data --

	union {T x, r, s;};
	union {T y, g, t;};

	// -- Component accesses --

	/// Return the count of components of the vector
	static constexpr length_type length() { return 2; }

	constexpr T&		operator[](length_type i);
	constexpr T const&	operator[](length_type i) const;

	// -- Implicit basic constructors --

	constexpr vec() = default;
	constexpr vec(vec const& v) = default;

	// -- Explicit basic constructors --

	constexpr explicit vec(T scalar);
	constexpr vec(T x, T y);

	// -- Conversion constructors --

	template <typename U>
	constexpr explicit vec(vec<1, U> const& v);

	template <typename A, typename B>
	constexpr vec(A x, B y);
	template <typename A, typename B>
	constexpr vec(vec<1, A> const& x, B y);
	template <typename A, typename B>
	constexpr vec(A x, vec<1, B> const& y);
	template <typename A, typename B>
	constexpr vec(vec<1, A> const& x, vec<1, B> const& y);

	// -- Conversion vector constructors --

	template <typename U>
	constexpr explicit vec(vec<3, U> const& v);
	template <typename U>
	constexpr explicit vec(vec<4, U> const& v);

	template <typename U>
	constexpr explicit vec(vec<2, U> const& v);

	// -- Unary arithmetic operators --

	constexpr vec<2, T> & operator=(vec const& v) = default;

	template <typename U>
	constexpr vec<2, T> & operator=(vec<2, U> const& v);
	template <typename U>
	constexpr vec<2, T> & operator+=(U scalar);
	template <typename U>
	constexpr vec<2, T> & operator+=(vec<1, U> const& v);
	template <typename U>
	constexpr vec<2, T> & operator+=(vec<2, U> const& v);
	template <typename U>
	constexpr vec<2, T> & operator-=(U scalar);
	template <typename U>
	constexpr vec<2, T> & operator-=(vec<1, U> const& v);
	template <typename U>
	constexpr vec<2, T> & operator-=(vec<2, U> const& v);
	template <typename U>
	constexpr vec<2, T> & operator*=(U scalar);
	template <typename U>
	constexpr vec<2, T> & operator*=(vec<1, U> const& v);
	template <typename U>
	constexpr vec<2, T> & operator*=(vec<2, U> const& v);
	template <typename U>
	constexpr vec<2, T> & operator/=(U scalar);
	template <typename U>
	constexpr vec<2, T> & operator/=(vec<1, U> const& v);
	template <typename U>
	constexpr vec<2, T> & operator/=(vec<2, U> const& v);

	// -- Increment and decrement operators --

	constexpr vec<2, T> & operator++();
	constexpr vec<2, T> & operator--();
	constexpr vec<2, T> operator++(int);
	constexpr vec<2, T> operator--(int);

	// -- Unary bit operators --

	template <typename U>
	constexpr vec<2, T> & operator%=(U scalar);
	template <typename U>
	constexpr vec<2, T> & operator%=(vec<1, U> const& v);
	template <typename U>
	constexpr vec<2, T> & operator%=(vec<2, U> const& v);
	template <typename U>
	constexpr vec<2, T> & operator&=(U scalar);
	template <typename U>
	constexpr vec<2, T> & operator&=(vec<1, U> const& v);
	template <typename U>
	constexpr vec<2, T> & operator&=(vec<2, U> const& v);
	template <typename U>
	constexpr vec<2, T> & operator|=(U scalar);
	template <typename U>
	constexpr vec<2, T> & operator|=(vec<1, U> const& v);
	template <typename U>
	constexpr vec<2, T> & operator|=(vec<2, U> const& v);
	template <typename U>
	constexpr vec<2, T> & operator^=(U scalar);
	template <typename U>
	constexpr vec<2, T> & operator^=(vec<1, U> const& v);
	template <typename U>
	constexpr vec<2, T> & operator^=(vec<2, U> const& v);
	template <typename U>
	constexpr vec<2, T> & operator<<=(U scalar);
	template <typename U>
	constexpr vec<2, T> & operator<<=(vec<1, U> const& v);
	template <typename U>
	constexpr vec<2, T> & operator<<=(vec<2, U> const& v);
	template <typename U>
	constexpr vec<2, T> & operator>>=(U scalar);
	template <typename U>
	constexpr vec<2, T> & operator>>=(vec<1, U> const& v);
	template <typename U>
	constexpr vec<2, T> & operator>>=(vec<2, U> const& v);
};

// -- Explicit basic constructors --

template <typename T>
inline constexpr vec<2, T>::vec(T scalar)
	: x(scalar), y(scalar)
{}

template <typename T>
inline constexpr vec<2, T>::vec(T _x, T _y)
	: x(_x), y(_y)
{}

// -- Conversion scalar constructors --

template <typename T>
template <typename U>
inline constexpr vec<2, T>::vec(vec<1, U> const& v)
	: x(static_cast<T>(v.x))
	, y(static_cast<T>(v.x))
{}

template <typename T>
template <typename A, typename B>
inline constexpr vec<2, T>::vec(A _x, B _y)
	: x(static_cast<T>(_x))
	, y(static_cast<T>(_y))
{}

template <typename T>
template <typename A, typename B>
inline constexpr vec<2, T>::vec(vec<1, A> const& _x, B _y)
	: x(static_cast<T>(_x.x))
	, y(static_cast<T>(_y))
{}

template <typename T>
template <typename A, typename B>
inline constexpr vec<2, T>::vec(A _x, vec<1, B> const& _y)
	: x(static_cast<T>(_x))
	, y(static_cast<T>(_y.x))
{}

template <typename T>
template <typename A, typename B>
inline constexpr vec<2, T>::vec(vec<1, A> const& _x, vec<1, B> const& _y)
	: x(static_cast<T>(_x.x))
	, y(static_cast<T>(_y.x))
{}

// -- Conversion vector constructors --

template <typename T>
template <typename U>
inline constexpr vec<2, T>::vec(vec<2, U> const& v)
	: x(static_cast<T>(v.x))
	, y(static_cast<T>(v.y))
{}

template <typename T>
template <typename U>
inline constexpr vec<2, T>::vec(vec<3, U> const& v)
	: x(static_cast<T>(v.x))
	, y(static_cast<T>(v.y))
{}

template <typename T>
template <typename U>
inline constexpr vec<2, T>::vec(vec<4, U> const& v)
	: x(static_cast<T>(v.x))
	, y(static_cast<T>(v.y))
{}

// -- Component accesses --

template <typename T>
inline constexpr T & vec<2, T>::operator[](typename vec<2, T>::length_type i)
{
	assert(i >= 0 && i < this->length());
	switch(i)
	{
	default:
	case 0:
		return x;
	case 1:
		return y;
	}
}

template <typename T>
inline constexpr T const& vec<2, T>::operator[](typename vec<2, T>::length_type i) const
{
	assert(i >= 0 && i < this->length());
	switch(i)
	{
	default:
	case 0:
		return x;
	case 1:
		return y;
	}
}

// -- Unary arithmetic operators --

template <typename T>
template <typename U>
inline constexpr vec<2, T> & vec<2, T>::operator=(vec<2, U> const& v)
{
	this->x = static_cast<T>(v.x);
	this->y = static_cast<T>(v.y);
	return *this;
}

template <typename T>
template <typename U>
inline constexpr vec<2, T> & vec<2, T>::operator+=(U scalar)
{
	this->x += static_cast<T>(scalar);
	this->y += static_cast<T>(scalar);
	return *this;
}

template <typename T>
template <typename U>
inline constexpr vec<2, T> & vec<2, T>::operator+=(vec<1, U> const& v)
{
	this->x += static_cast<T>(v.x);
	this->y += static_cast<T>(v.x);
	return *this;
}

template <typename T>
template <typename U>
inline constexpr vec<2, T> & vec<2, T>::operator+=(vec<2, U> const& v)
{
	this->x += static_cast<T>(v.x);
	this->y += static_cast<T>(v.y);
	return *this;
}

template <typename T>
template <typename U>
inline constexpr vec<2, T> & vec<2, T>::operator-=(U scalar)
{
	this->x -= static_cast<T>(scalar);
	this->y -= static_cast<T>(scalar);
	return *this;
}

template <typename T>
template <typename U>
inline constexpr vec<2, T> & vec<2, T>::operator-=(vec<1, U> const& v)
{
	this->x -= static_cast<T>(v.x);
	this->y -= static_cast<T>(v.x);
	return *this;
}

template <typename T>
template <typename U>
inline constexpr vec<2, T> & vec<2, T>::operator-=(vec<2, U> const& v)
{
	this->x -= static_cast<T>(v.x);
	this->y -= static_cast<T>(v.y);
	return *this;
}

template <typename T>
template <typename U>
inline constexpr vec<2, T> & vec<2, T>::operator*=(U scalar)
{
	this->x *= static_cast<T>(scalar);
	this->y *= static_cast<T>(scalar);
	return *this;
}

template <typename T>
template <typename U>
inline constexpr vec<2, T> & vec<2, T>::operator*=(vec<1, U> const& v)
{
	this->x *= static_cast<T>(v.x);
	this->y *= static_cast<T>(v.x);
	return *this;
}

template <typename T>
template <typename U>
inline constexpr vec<2, T> & vec<2, T>::operator*=(vec<2, U> const& v)
{
	this->x *= static_cast<T>(v.x);
	this->y *= static_cast<T>(v.y);
	return *this;
}

template <typename T>
template <typename U>
inline constexpr vec<2, T> & vec<2, T>::operator/=(U scalar)
{
	this->x /= static_cast<T>(scalar);
	this->y /= static_cast<T>(scalar);
	return *this;
}

template <typename T>
template <typename U>
inline constexpr vec<2, T> & vec<2, T>::operator/=(vec<1, U> const& v)
{
	this->x /= static_cast<T>(v.x);
	this->y /= static_cast<T>(v.x);
	return *this;
}

template <typename T>
template <typename U>
inline constexpr vec<2, T> & vec<2, T>::operator/=(vec<2, U> const& v)
{
	this->x /= static_cast<T>(v.x);
	this->y /= static_cast<T>(v.y);
	return *this;
}

// -- Increment and decrement operators --

template <typename T>
inline constexpr vec<2, T> & vec<2, T>::operator++()
{
	++this->x;
	++this->y;
	return *this;
}

template <typename T>
inline constexpr vec<2, T> & vec<2, T>::operator--()
{
	--this->x;
	--this->y;
	return *this;
}

template <typename T>
inline constexpr vec<2, T> vec<2, T>::operator++(int)
{
	vec<2, T> Result(*this);
	++*this;
	return Result;
}

template <typename T>
inline constexpr vec<2, T> vec<2, T>::operator--(int)
{
	vec<2, T> Result(*this);
	--*this;
	return Result;
}

// -- Unary bit operators --

template <typename T>
template <typename U>
inline constexpr vec<2, T> & vec<2, T>::operator%=(U scalar)
{
	this->x %= static_cast<T>(scalar);
	this->y %= static_cast<T>(scalar);
	return *this;
}

template <typename T>
template <typename U>
inline constexpr vec<2, T> & vec<2, T>::operator%=(vec<1, U> const& v)
{
	this->x %= static_cast<T>(v.x);
	this->y %= static_cast<T>(v.x);
	return *this;
}

template <typename T>
template <typename U>
inline constexpr vec<2, T> & vec<2, T>::operator%=(vec<2, U> const& v)
{
	this->x %= static_cast<T>(v.x);
	this->y %= static_cast<T>(v.y);
	return *this;
}

template <typename T>
template <typename U>
inline constexpr vec<2, T> & vec<2, T>::operator&=(U scalar)
{
	this->x &= static_cast<T>(scalar);
	this->y &= static_cast<T>(scalar);
	return *this;
}

template <typename T>
template <typename U>
inline constexpr vec<2, T> & vec<2, T>::operator&=(vec<1, U> const& v)
{
	this->x &= static_cast<T>(v.x);
	this->y &= static_cast<T>(v.x);
	return *this;
}

template <typename T>
template <typename U>
inline constexpr vec<2, T> & vec<2, T>::operator&=(vec<2, U> const& v)
{
	this->x &= static_cast<T>(v.x);
	this->y &= static_cast<T>(v.y);
	return *this;
}

template <typename T>
template <typename U>
inline constexpr vec<2, T> & vec<2, T>::operator|=(U scalar)
{
	this->x |= static_cast<T>(scalar);
	this->y |= static_cast<T>(scalar);
	return *this;
}

template <typename T>
template <typename U>
inline constexpr vec<2, T> & vec<2, T>::operator|=(vec<1, U> const& v)
{
	this->x |= static_cast<T>(v.x);
	this->y |= static_cast<T>(v.x);
	return *this;
}

template <typename T>
template <typename U>
inline constexpr vec<2, T> & vec<2, T>::operator|=(vec<2, U> const& v)
{
	this->x |= static_cast<T>(v.x);
	this->y |= static_cast<T>(v.y);
	return *this;
}

template <typename T>
template <typename U>
inline constexpr vec<2, T> & vec<2, T>::operator^=(U scalar)
{
	this->x ^= static_cast<T>(scalar);
	this->y ^= static_cast<T>(scalar);
	return *this;
}

template <typename T>
template <typename U>
inline constexpr vec<2, T> & vec<2, T>::operator^=(vec<1, U> const& v)
{
	this->x ^= static_cast<T>(v.x);
	this->y ^= static_cast<T>(v.x);
	return *this;
}

template <typename T>
template <typename U>
inline constexpr vec<2, T> & vec<2, T>::operator^=(vec<2, U> const& v)
{
	this->x ^= static_cast<T>(v.x);
	this->y ^= static_cast<T>(v.y);
	return *this;
}

template <typename T>
template <typename U>
inline constexpr vec<2, T> & vec<2, T>::operator<<=(U scalar)
{
	this->x <<= static_cast<T>(scalar);
	this->y <<= static_cast<T>(scalar);
	return *this;
}

template <typename T>
template <typename U>
inline constexpr vec<2, T> & vec<2, T>::operator<<=(vec<1, U> const& v)
{
	this->x <<= static_cast<T>(v.x);
	this->y <<= static_cast<T>(v.x);
	return *this;
}

template <typename T>
template <typename U>
inline constexpr vec<2, T> & vec<2, T>::operator<<=(vec<2, U> const& v)
{
	this->x <<= static_cast<T>(v.x);
	this->y <<= static_cast<T>(v.y);
	return *this;
}

template <typename T>
template <typename U>
inline constexpr vec<2, T> & vec<2, T>::operator>>=(U scalar)
{
	this->x >>= static_cast<T>(scalar);
	this->y >>= static_cast<T>(scalar);
	return *this;
}

template <typename T>
template <typename U>
inline constexpr vec<2, T> & vec<2, T>::operator>>=(vec<1, U> const& v)
{
	this->x >>= static_cast<T>(v.x);
	this->y >>= static_cast<T>(v.x);
	return *this;
}

template <typename T>
template <typename U>
inline constexpr vec<2, T> & vec<2, T>::operator>>=(vec<2, U> const& v)
{
	this->x >>= static_cast<T>(v.x);
	this->y >>= static_cast<T>(v.y);
	return *this;
}

// -- Unary arithmetic operators --

template <typename T>
inline constexpr vec<2, T> operator+(vec<2, T> const& v)
{
	return v;
}

template <typename T>
inline constexpr vec<2, T> operator-(vec<2, T> const& v)
{
	return vec<2, T>(
		-v.x,
		-v.y);
}

// -- Binary arithmetic operators --

template <typename T>
inline constexpr vec<2, T> operator+(vec<2, T> const& v, T scalar)
{
	return vec<2, T>(
		v.x + scalar,
		v.y + scalar);
}

template <typename T>
inline constexpr vec<2, T> operator+(vec<2, T> const& v1, vec<1, T> const& v2)
{
	return vec<2, T>(
		v1.x + v2.x,
		v1.y + v2.x);
}

template <typename T>
inline constexpr vec<2, T> operator+(T scalar, vec<2, T> const& v)
{
	return vec<2, T>(
		scalar + v.x,
		scalar + v.y);
}

template <typename T>
inline constexpr vec<2, T> operator+(vec<1, T> const& v1, vec<2, T> const& v2)
{
	return vec<2, T>(
		v1.x + v2.x,
		v1.x + v2.y);
}

template <typename T>
inline constexpr vec<2, T> operator+(vec<2, T> const& v1, vec<2, T> const& v2)
{
	return vec<2, T>(
		v1.x + v2.x,
		v1.y + v2.y);
}

template <typename T>
inline constexpr vec<2, T> operator-(vec<2, T> const& v, T scalar)
{
	return vec<2, T>(
		v.x - scalar,
		v.y - scalar);
}

template <typename T>
inline constexpr vec<2, T> operator-(vec<2, T> const& v1, vec<1, T> const& v2)
{
	return vec<2, T>(
		v1.x - v2.x,
		v1.y - v2.x);
}

template <typename T>
inline constexpr vec<2, T> operator-(T scalar, vec<2, T> const& v)
{
	return vec<2, T>(
		scalar - v.x,
		scalar - v.y);
}

template <typename T>
inline constexpr vec<2, T> operator-(vec<1, T> const& v1, vec<2, T> const& v2)
{
	return vec<2, T>(
		v1.x - v2.x,
		v1.x - v2.y);
}

template <typename T>
inline constexpr vec<2, T> operator-(vec<2, T> const& v1, vec<2, T> const& v2)
{
	return vec<2, T>(
		v1.x - v2.x,
		v1.y - v2.y);
}

template <typename T>
inline constexpr vec<2, T> operator*(vec<2, T> const& v, T scalar)
{
	return vec<2, T>(
		v.x * scalar,
		v.y * scalar);
}

template <typename T>
inline constexpr vec<2, T> operator*(vec<2, T> const& v1, vec<1, T> const& v2)
{
	return vec<2, T>(
		v1.x * v2.x,
		v1.y * v2.x);
}

template <typename T>
inline constexpr vec<2, T> operator*(T scalar, vec<2, T> const& v)
{
	return vec<2, T>(
		scalar * v.x,
		scalar * v.y);
}

template <typename T>
inline constexpr vec<2, T> operator*(vec<1, T> const& v1, vec<2, T> const& v2)
{
	return vec<2, T>(
		v1.x * v2.x,
		v1.x * v2.y);
}

template <typename T>
inline constexpr vec<2, T> operator*(vec<2, T> const& v1, vec<2, T> const& v2)
{
	return vec<2, T>(
		v1.x * v2.x,
		v1.y * v2.y);
}

template <typename T>
inline constexpr vec<2, T> operator/(vec<2, T> const& v, T scalar)
{
	return vec<2, T>(
		v.x / scalar,
		v.y / scalar);
}

template <typename T>
inline constexpr vec<2, T> operator/(vec<2, T> const& v1, vec<1, T> const& v2)
{
	return vec<2, T>(
		v1.x / v2.x,
		v1.y / v2.x);
}

template <typename T>
inline constexpr vec<2, T> operator/(T scalar, vec<2, T> const& v)
{
	return vec<2, T>(
		scalar / v.x,
		scalar / v.y);
}

template <typename T>
inline constexpr vec<2, T> operator/(vec<1, T> const& v1, vec<2, T> const& v2)
{
	return vec<2, T>(
		v1.x / v2.x,
		v1.x / v2.y);
}

template <typename T>
inline constexpr vec<2, T> operator/(vec<2, T> const& v1, vec<2, T> const& v2)
{
	return vec<2, T>(
		v1.x / v2.x,
		v1.y / v2.y);
}

// -- Binary bit operators --

template <typename T>
inline constexpr vec<2, T> operator%(vec<2, T> const& v, T scalar)
{
	return vec<2, T>(
		v.x % scalar,
		v.y % scalar);
}

template <typename T>
inline constexpr vec<2, T> operator%(vec<2, T> const& v1, vec<1, T> const& v2)
{
	return vec<2, T>(
		v1.x % v2.x,
		v1.y % v2.x);
}

template <typename T>
inline constexpr vec<2, T> operator%(T scalar, vec<2, T> const& v)
{
	return vec<2, T>(
		scalar % v.x,
		scalar % v.y);
}

template <typename T>
inline constexpr vec<2, T> operator%(vec<1, T> const& v1, vec<2, T> const& v2)
{
	return vec<2, T>(
		v1.x % v2.x,
		v1.x % v2.y);
}

template <typename T>
inline constexpr vec<2, T> operator%(vec<2, T> const& v1, vec<2, T> const& v2)
{
	return vec<2, T>(
		v1.x % v2.x,
		v1.y % v2.y);
}

template <typename T>
inline constexpr vec<2, T> operator&(vec<2, T> const& v, T scalar)
{
	return vec<2, T>(
		v.x & scalar,
		v.y & scalar);
}

template <typename T>
inline constexpr vec<2, T> operator&(vec<2, T> const& v1, vec<1, T> const& v2)
{
	return vec<2, T>(
		v1.x & v2.x,
		v1.y & v2.x);
}

template <typename T>
inline constexpr vec<2, T> operator&(T scalar, vec<2, T> const& v)
{
	return vec<2, T>(
		scalar & v.x,
		scalar & v.y);
}

template <typename T>
inline constexpr vec<2, T> operator&(vec<1, T> const& v1, vec<2, T> const& v2)
{
	return vec<2, T>(
		v1.x & v2.x,
		v1.x & v2.y);
}

template <typename T>
inline constexpr vec<2, T> operator&(vec<2, T> const& v1, vec<2, T> const& v2)
{
	return vec<2, T>(
		v1.x & v2.x,
		v1.y & v2.y);
}

template <typename T>
inline constexpr vec<2, T> operator|(vec<2, T> const& v, T scalar)
{
	return vec<2, T>(
		v.x | scalar,
		v.y | scalar);
}

template <typename T>
inline constexpr vec<2, T> operator|(vec<2, T> const& v1, vec<1, T> const& v2)
{
	return vec<2, T>(
		v1.x | v2.x,
		v1.y | v2.x);
}

template <typename T>
inline constexpr vec<2, T> operator|(T scalar, vec<2, T> const& v)
{
	return vec<2, T>(
		scalar | v.x,
		scalar | v.y);
}

template <typename T>
inline constexpr vec<2, T> operator|(vec<1, T> const& v1, vec<2, T> const& v2)
{
	return vec<2, T>(
		v1.x | v2.x,
		v1.x | v2.y);
}

template <typename T>
inline constexpr vec<2, T> operator|(vec<2, T> const& v1, vec<2, T> const& v2)
{
	return vec<2, T>(
		v1.x | v2.x,
		v1.y | v2.y);
}

template <typename T>
inline constexpr vec<2, T> operator^(vec<2, T> const& v, T scalar)
{
	return vec<2, T>(
		v.x ^ scalar,
		v.y ^ scalar);
}

template <typename T>
inline constexpr vec<2, T> operator^(vec<2, T> const& v1, vec<1, T> const& v2)
{
	return vec<2, T>(
		v1.x ^ v2.x,
		v1.y ^ v2.x);
}

template <typename T>
inline constexpr vec<2, T> operator^(T scalar, vec<2, T> const& v)
{
	return vec<2, T>(
		scalar ^ v.x,
		scalar ^ v.y);
}

template <typename T>
inline constexpr vec<2, T> operator^(vec<1, T> const& v1, vec<2, T> const& v2)
{
	return vec<2, T>(
		v1.x ^ v2.x,
		v1.x ^ v2.y);
}

template <typename T>
inline constexpr vec<2, T> operator^(vec<2, T> const& v1, vec<2, T> const& v2)
{
	return vec<2, T>(
		v1.x ^ v2.x,
		v1.y ^ v2.y);
}

template <typename T>
inline constexpr vec<2, T> operator<<(vec<2, T> const& v, T scalar)
{
	return vec<2, T>(
		v.x << scalar,
		v.y << scalar);
}

template <typename T>
inline constexpr vec<2, T> operator<<(vec<2, T> const& v1, vec<1, T> const& v2)
{
	return vec<2, T>(
		v1.x << v2.x,
		v1.y << v2.x);
}

template <typename T>
inline constexpr vec<2, T> operator<<(T scalar, vec<2, T> const& v)
{
	return vec<2, T>(
		scalar << v.x,
		scalar << v.y);
}

template <typename T>
inline constexpr vec<2, T> operator<<(vec<1, T> const& v1, vec<2, T> const& v2)
{
	return vec<2, T>(
		v1.x << v2.x,
		v1.x << v2.y);
}

template <typename T>
inline constexpr vec<2, T> operator<<(vec<2, T> const& v1, vec<2, T> const& v2)
{
	return vec<2, T>(
		v1.x << v2.x,
		v1.y << v2.y);
}

template <typename T>
inline constexpr vec<2, T> operator>>(vec<2, T> const& v, T scalar)
{
	return vec<2, T>(
		v.x >> scalar,
		v.y >> scalar);
}

template <typename T>
inline constexpr vec<2, T> operator>>(vec<2, T> const& v1, vec<1, T> const& v2)
{
	return vec<2, T>(
		v1.x >> v2.x,
		v1.y >> v2.x);
}

template <typename T>
inline constexpr vec<2, T> operator>>(T scalar, vec<2, T> const& v)
{
	return vec<2, T>(
		scalar >> v.x,
		scalar >> v.y);
}

template <typename T>
inline constexpr vec<2, T> operator>>(vec<1, T> const& v1, vec<2, T> const& v2)
{
	return vec<2, T>(
		v1.x >> v2.x,
		v1.x >> v2.y);
}

template <typename T>
inline constexpr vec<2, T> operator>>(vec<2, T> const& v1, vec<2, T> const& v2)
{
	return vec<2, T>(
		v1.x >> v2.x,
		v1.y >> v2.y);
}

template <typename T>
inline constexpr vec<2, T> operator~(vec<2, T> const& v)
{
	return vec<2, T>(
		~v.x,
		~v.y);
}

// -- Boolean operators --

template <typename T>
inline constexpr bool operator==(vec<2, T> const& v1, vec<2, T> const& v2)
{
	return
		compute_equal<T, std::numeric_limits<T>::is_iec559>::call(v1.x, v2.x) &&
		compute_equal<T, std::numeric_limits<T>::is_iec559>::call(v1.y, v2.y);
}

template <typename T>
inline constexpr bool operator!=(vec<2, T> const& v1, vec<2, T> const& v2)
{
	return !(v1 == v2);
}

inline constexpr vec<2, bool> operator&&(vec<2, bool> const& v1, vec<2, bool> const& v2)
{
	return vec<2, bool>(v1.x && v2.x, v1.y && v2.y);
}

inline constexpr vec<2, bool> operator||(vec<2, bool> const& v1, vec<2, bool> const& v2)
{
	return vec<2, bool>(v1.x || v2.x, v1.y || v2.y);
}

} // math

} // Kinai
