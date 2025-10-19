#pragma once

# include "type.hpp"

namespace Kinai
{

namespace math
{

template <typename T>
struct vec<1, T>
{
	// -- Implementation detail --

	typedef T				value_type;
	typedef vec<1, T>		type;
	typedef vec<1, bool>	bool_type;
	typedef length_t		length_type;

	// -- Data --
	union {T x, r, s;};

	// -- Component accesses --

	/// Return the count of components of the vector
	static constexpr length_type length(){return 1;}

	constexpr T &		operator[](length_type i);
	constexpr T const&	operator[](length_type i) const;

	// -- Implicit basic constructors --

	constexpr vec() = default;
	constexpr vec(vec const& v) = default;

	// -- Explicit basic constructors --

	constexpr explicit vec(T scalar);

	// -- Conversion vector constructors --

	template <typename U>
	constexpr explicit vec(vec<2, U> const& v);
	template <typename U>
	constexpr explicit vec(vec<3, U> const& v);
	template <typename U>
	constexpr explicit vec(vec<4, U> const& v);

	template <typename U>
	constexpr explicit vec(vec<1, U> const& v);

	// -- Unary arithmetic operators --

	constexpr vec<1, T> & operator=(vec const& v) = default;

	template <typename U>
	constexpr vec<1, T> & operator=(vec<1, U> const& v);
	template <typename U>
	constexpr vec<1, T> & operator+=(U scalar);
	template <typename U>
	constexpr vec<1, T> & operator+=(vec<1, U> const& v);
	template <typename U>
	constexpr vec<1, T> & operator-=(U scalar);
	template <typename U>
	constexpr vec<1, T> & operator-=(vec<1, U> const& v);
	template <typename U>
	constexpr vec<1, T> & operator*=(U scalar);
	template <typename U>
	constexpr vec<1, T> & operator*=(vec<1, U> const& v);
	template <typename U>
	constexpr vec<1, T> & operator/=(U scalar);
	template <typename U>
	constexpr vec<1, T> & operator/=(vec<1, U> const& v);

	// -- Increment and decrement operators --

	constexpr vec<1, T> & operator++();
	constexpr vec<1, T> & operator--();
	constexpr vec<1, T> operator++(int);
	constexpr vec<1, T> operator--(int);

	// -- Unary bit operators --

	template <typename U>
	constexpr vec<1, T> & operator%=(U scalar);
	template <typename U>
	constexpr vec<1, T> & operator%=(vec<1, U> const& v);
	template <typename U>
	constexpr vec<1, T> & operator&=(U scalar);
	template <typename U>
	constexpr vec<1, T> & operator&=(vec<1, U> const& v);
	template <typename U>
	constexpr vec<1, T> & operator|=(U scalar);
	template <typename U>
	constexpr vec<1, T> & operator|=(vec<1, U> const& v);
	template <typename U>
	constexpr vec<1, T> & operator^=(U scalar);
	template <typename U>
	constexpr vec<1, T> & operator^=(vec<1, U> const& v);
	template <typename U>
	constexpr vec<1, T> & operator<<=(U scalar);
	template <typename U>
	constexpr vec<1, T> & operator<<=(vec<1, U> const& v);
	template <typename U>
	constexpr vec<1, T> & operator>>=(U scalar);
	template <typename U>
	constexpr vec<1, T> & operator>>=(vec<1, U> const& v);
};

// -- Explicit basic constructors --

template <typename T>
inline constexpr vec<1, T>::vec(T scalar)
	: x(scalar)
{}

// -- Conversion vector constructors --

template <typename T>
template <typename U>
inline constexpr vec<1, T>::vec(vec<1, U> const& v)
	: x(static_cast<T>(v.x))
{}

template <typename T>
template <typename U>
inline constexpr vec<1, T>::vec(vec<2, U> const& v)
	: x(static_cast<T>(v.x))
{}

template <typename T>
template <typename U>
inline constexpr vec<1, T>::vec(vec<3, U> const& v)
	: x(static_cast<T>(v.x))
{}

template <typename T>
template <typename U>
inline constexpr vec<1, T>::vec(vec<4, U> const& v)
	: x(static_cast<T>(v.x))
{}

// -- Component accesses --

template <typename T>
inline constexpr T & vec<1, T>::operator[](typename vec<1, T>::length_type)
{
	return x;
}

template <typename T>
inline constexpr T const& vec<1, T>::operator[](typename vec<1, T>::length_type) const
{
	return x;
}

// -- Unary arithmetic operators --

template <typename T>
template <typename U>
inline constexpr vec<1, T> & vec<1, T>::operator=(vec<1, U> const& v)
{
	this->x = static_cast<T>(v.x);
	return *this;
}

template <typename T>
template <typename U>
inline constexpr vec<1, T> & vec<1, T>::operator+=(U scalar)
{
	this->x += static_cast<T>(scalar);
	return *this;
}

template <typename T>
template <typename U>
inline constexpr vec<1, T> & vec<1, T>::operator+=(vec<1, U> const& v)
{
	this->x += static_cast<T>(v.x);
	return *this;
}

template <typename T>
template <typename U>
inline constexpr vec<1, T> & vec<1, T>::operator-=(U scalar)
{
	this->x -= static_cast<T>(scalar);
	return *this;
}

template <typename T>
template <typename U>
inline constexpr vec<1, T> & vec<1, T>::operator-=(vec<1, U> const& v)
{
	this->x -= static_cast<T>(v.x);
	return *this;
}

template <typename T>
template <typename U>
inline constexpr vec<1, T> & vec<1, T>::operator*=(U scalar)
{
	this->x *= static_cast<T>(scalar);
	return *this;
}

template <typename T>
template <typename U>
inline constexpr vec<1, T> & vec<1, T>::operator*=(vec<1, U> const& v)
{
	this->x *= static_cast<T>(v.x);
	return *this;
}

template <typename T>
template <typename U>
inline constexpr vec<1, T> & vec<1, T>::operator/=(U scalar)
{
	this->x /= static_cast<T>(scalar);
	return *this;
}

template <typename T>
template <typename U>
inline constexpr vec<1, T> & vec<1, T>::operator/=(vec<1, U> const& v)
{
	this->x /= static_cast<T>(v.x);
	return *this;
}

// -- Increment and decrement operators --

template <typename T>
inline constexpr vec<1, T> & vec<1, T>::operator++()
{
	++this->x;
	return *this;
}

template <typename T>
inline constexpr vec<1, T> & vec<1, T>::operator--()
{
	--this->x;
	return *this;
}

template <typename T>
inline constexpr vec<1, T> vec<1, T>::operator++(int)
{
	vec<1, T> Result(*this);
	++*this;
	return Result;
}

template <typename T>
inline constexpr vec<1, T> vec<1, T>::operator--(int)
{
	vec<1, T> Result(*this);
	--*this;
	return Result;
}

// -- Unary bit operators --

template <typename T>
template <typename U>
inline constexpr vec<1, T> & vec<1, T>::operator%=(U scalar)
{
	this->x %= static_cast<T>(scalar);
	return *this;
}

template <typename T>
template <typename U>
inline constexpr vec<1, T> & vec<1, T>::operator%=(vec<1, U> const& v)
{
	this->x %= static_cast<T>(v.x);
	return *this;
}

template <typename T>
template <typename U>
inline constexpr vec<1, T> & vec<1, T>::operator&=(U scalar)
{
	this->x &= static_cast<T>(scalar);
	return *this;
}

template <typename T>
template <typename U>
inline constexpr vec<1, T> & vec<1, T>::operator&=(vec<1, U> const& v)
{
	this->x &= static_cast<T>(v.x);
	return *this;
}

template <typename T>
template <typename U>
inline constexpr vec<1, T> & vec<1, T>::operator|=(U scalar)
{
	this->x |= static_cast<T>(scalar);
	return *this;
}

template <typename T>
template <typename U>
inline constexpr vec<1, T> & vec<1, T>::operator|=(vec<1, U> const& v)
{
	this->x |= U(v.x);
	return *this;
}

template <typename T>
template <typename U>
inline constexpr vec<1, T> & vec<1, T>::operator^=(U scalar)
{
	this->x ^= static_cast<T>(scalar);
	return *this;
}

template <typename T>
template <typename U>
inline constexpr vec<1, T> & vec<1, T>::operator^=(vec<1, U> const& v)
{
	this->x ^= static_cast<T>(v.x);
	return *this;
}

template <typename T>
template <typename U>
inline constexpr vec<1, T> & vec<1, T>::operator<<=(U scalar)
{
	this->x <<= static_cast<T>(scalar);
	return *this;
}

template <typename T>
template <typename U>
inline constexpr vec<1, T> & vec<1, T>::operator<<=(vec<1, U> const& v)
{
	this->x <<= static_cast<T>(v.x);
	return *this;
}

template <typename T>
template <typename U>
inline constexpr vec<1, T> & vec<1, T>::operator>>=(U scalar)
{
	this->x >>= static_cast<T>(scalar);
	return *this;
}

template <typename T>
template <typename U>
inline constexpr vec<1, T> & vec<1, T>::operator>>=(vec<1, U> const& v)
{
	this->x >>= static_cast<T>(v.x);
	return *this;
}

// -- Unary constant operators --

template <typename T>
inline constexpr vec<1, T> operator+(vec<1, T> const& v)
{
	return v;
}

template <typename T>
inline constexpr vec<1, T> operator-(vec<1, T> const& v)
{
	return vec<1, T>(
		-v.x);
}

// -- Binary arithmetic operators --

template <typename T>
inline constexpr vec<1, T> operator+(vec<1, T> const& v, T scalar)
{
	return vec<1, T>(
		v.x + scalar);
}

template <typename T>
inline constexpr vec<1, T> operator+(T scalar, vec<1, T> const& v)
{
	return vec<1, T>(
		scalar + v.x);
}

template <typename T>
inline constexpr vec<1, T> operator+(vec<1, T> const& v1, vec<1, T> const& v2)
{
	return vec<1, T>(
		v1.x + v2.x);
}

//operator-
template <typename T>
inline constexpr vec<1, T> operator-(vec<1, T> const& v, T scalar)
{
	return vec<1, T>(
		v.x - scalar);
}

template <typename T>
inline constexpr vec<1, T> operator-(T scalar, vec<1, T> const& v)
{
	return vec<1, T>(
		scalar - v.x);
}

template <typename T>
inline constexpr vec<1, T> operator-(vec<1, T> const& v1, vec<1, T> const& v2)
{
	return vec<1, T>(
		v1.x - v2.x);
}

template <typename T>
inline constexpr vec<1, T> operator*(vec<1, T> const& v, T scalar)
{
	return vec<1, T>(
		v.x * scalar);
}

template <typename T>
inline constexpr vec<1, T> operator*(T scalar, vec<1, T> const& v)
{
	return vec<1, T>(
		scalar * v.x);
}

template <typename T>
inline constexpr vec<1, T> operator*(vec<1, T> const& v1, vec<1, T> const& v2)
{
	return vec<1, T>(
		v1.x * v2.x);
}

template <typename T>
inline constexpr vec<1, T> operator/(vec<1, T> const& v, T scalar)
{
	return vec<1, T>(
		v.x / scalar);
}

template <typename T>
inline constexpr vec<1, T> operator/(T scalar, vec<1, T> const& v)
{
	return vec<1, T>(
		scalar / v.x);
}

template <typename T>
inline constexpr vec<1, T> operator/(vec<1, T> const& v1, vec<1, T> const& v2)
{
	return vec<1, T>(
		v1.x / v2.x);
}

// -- Binary bit operators --

template <typename T>
inline constexpr vec<1, T> operator%(vec<1, T> const& v, T scalar)
{
	return vec<1, T>(
		v.x % scalar);
}

template <typename T>
inline constexpr vec<1, T> operator%(T scalar, vec<1, T> const& v)
{
	return vec<1, T>(
		scalar % v.x);
}

template <typename T>
inline constexpr vec<1, T> operator%(vec<1, T> const& v1, vec<1, T> const& v2)
{
	return vec<1, T>(
		v1.x % v2.x);
}

template <typename T>
inline constexpr vec<1, T> operator&(vec<1, T> const& v, T scalar)
{
	return vec<1, T>(
		v.x & scalar);
}

template <typename T>
inline constexpr vec<1, T> operator&(T scalar, vec<1, T> const& v)
{
	return vec<1, T>(
		scalar & v.x);
}

template <typename T>
inline constexpr vec<1, T> operator&(vec<1, T> const& v1, vec<1, T> const& v2)
{
	return vec<1, T>(
		v1.x & v2.x);
}

template <typename T>
inline constexpr vec<1, T> operator|(vec<1, T> const& v, T scalar)
{
	return vec<1, T>(
		v.x | scalar);
}

template <typename T>
inline constexpr vec<1, T> operator|(T scalar, vec<1, T> const& v)
{
	return vec<1, T>(
		scalar | v.x);
}

template <typename T>
inline constexpr vec<1, T> operator|(vec<1, T> const& v1, vec<1, T> const& v2)
{
	return vec<1, T>(
		v1.x | v2.x);
}

template <typename T>
inline constexpr vec<1, T> operator^(vec<1, T> const& v, T scalar)
{
	return vec<1, T>(
		v.x ^ scalar);
}

template <typename T>
inline constexpr vec<1, T> operator^(T scalar, vec<1, T> const& v)
{
	return vec<1, T>(
		scalar ^ v.x);
}

template <typename T>
inline constexpr vec<1, T> operator^(vec<1, T> const& v1, vec<1, T> const& v2)
{
	return vec<1, T>(
		v1.x ^ v2.x);
}

template <typename T>
inline constexpr vec<1, T> operator<<(vec<1, T> const& v, T scalar)
{
	return vec<1, T>(
		static_cast<T>(v.x << scalar));
}

template <typename T>
inline constexpr vec<1, T> operator<<(T scalar, vec<1, T> const& v)
{
	return vec<1, T>(
		static_cast<T>(scalar << v.x));
}

template <typename T>
inline constexpr vec<1, T> operator<<(vec<1, T> const& v1, vec<1, T> const& v2)
{
	return vec<1, T>(
		static_cast<T>(v1.x << v2.x));
}

template <typename T>
inline constexpr vec<1, T> operator>>(vec<1, T> const& v, T scalar)
{
	return vec<1, T>(
		static_cast<T>(v.x >> scalar));
}

template <typename T>
inline constexpr vec<1, T> operator>>(T scalar, vec<1, T> const& v)
{
	return vec<1, T>(
		static_cast<T>(scalar >> v.x));
}

template <typename T>
inline constexpr vec<1, T> operator>>(vec<1, T> const& v1, vec<1, T> const& v2)
{
	return vec<1, T>(
		static_cast<T>(v1.x >> v2.x));
}

template <typename T>
inline constexpr vec<1, T> operator~(vec<1, T> const& v)
{
	return vec<1, T>(
		~v.x);
}

// -- Boolean operators --

template <typename T>
inline constexpr bool operator==(vec<1, T> const& v1, vec<1, T> const& v2)
{
	return compute_equal<T, std::numeric_limits<T>::is_iec559>::call(v1.x, v2.x);
}

template <typename T>
inline constexpr bool operator!=(vec<1, T> const& v1, vec<1, T> const& v2)
{
	return !(v1 == v2);
}

inline constexpr vec<1, bool> operator&&(vec<1, bool> const& v1, vec<1, bool> const& v2)
{
	return vec<1, bool>(v1.x && v2.x);
}

inline constexpr vec<1, bool> operator||(vec<1, bool> const& v1, vec<1, bool> const& v2)
{
	return vec<1, bool>(v1.x || v2.x);
}

} // math

} // Kinai
