#pragma once

# include <cassert>
# include <cmath>
# include <cstddef>
# include <cstdint>
# include <limits>

namespace Kinai
{

namespace math
{

# define KINAI_ASSERT_LENGTH(l, max)	(assert ((l) < (max)))

typedef int				length_t;
typedef unsigned int	uint_t;

template <length_t L, class Tp>				struct vec;
template <length_t C, length_t R, class Tp>	struct mat;

template<typename Tp>
struct is_int
{
	enum test {value = 0};
};

template <>
struct is_int<unsigned int>
{
	enum test {value = ~0};
};

template <>
struct is_int<signed int>
{
	enum test {value = ~0};
};

template <typename T, bool isFloat>
struct compute_equal
{
	constexpr static bool call(T a, T b)
	{
		return a == b;
	}
};

template<typename T, bool /*signed*/>
struct compute_abs
{};

template<typename T>
struct compute_abs<T, true>
{
	inline constexpr static T call(T x)
	{
		static_assert(
			std::numeric_limits<T>::is_iec559 || std::numeric_limits<T>::is_signed,
			"'abs' only accepts floating-point and integer scalar or vector inputs");

		return x >= T(0) ? x : -x;
		// TODO, perf comp with: *(((int *) &x) + 1) &= 0x7fffffff;
	}
};

template<typename T>
struct compute_abs<T, false>
{
	inline constexpr static T call(T x)
	{
		static_assert(
			(!std::numeric_limits<T>::is_signed && std::numeric_limits<T>::is_integer),
			"'abs' only accepts floating-point and integer scalar or vector inputs");
		return x;
	}
};

/* Scalar constants */

template <typename T>
inline constexpr T epsilon()
{
	static_assert(std::numeric_limits<T>::is_iec559, "'epsilon' only accepts floating-point inputs");
	return std::numeric_limits<T>::epsilon();
}

template <typename T>
inline constexpr T pi()
{
	static_assert(std::numeric_limits<T>::is_iec559, "'pi' only accepts floating-point inputs");
	return static_cast<T>(3.14159265358979323846264338327950288);
}

template <typename T>
inline constexpr T cos_one_over_two()
{
	return T(0.877582561890372716130286068203503191);
}

/* data */

// vector data

template<typename T>
inline constexpr T const* value_ptr(vec<2, T>& v)
{
	return &(v.x);
}

template<typename T>
inline constexpr T const* value_ptr(vec<2, T> const& v)
{
	return &(v.x);
}

template<typename T>
inline constexpr T const* value_ptr(vec<3, T>& v)
{
	return &(v.x);
}

template<typename T>
inline constexpr T const* value_ptr(vec<3, T> const& v)
{
	return &(v.x);
}

template<typename T>
inline constexpr T const* value_ptr(vec<4, T>& v)
{
	return &(v.x);
}

template<typename T>
inline constexpr T const* value_ptr(vec<4, T> const& v)
{
	return &(v.x);
}

// matrix data

template<typename T>
inline constexpr T const* value_ptr(mat<3, 3, T> const& m)
{
	return &(m[0].x);
}

template<typename T>
inline constexpr T* value_ptr(mat<3, 3, T>& m)
{
	return &(m[0].x);
}

template<typename T>
inline constexpr T const* value_ptr(mat<4, 4, T>& m)
{
	return &(m[0].x);
}

template<typename T>
inline constexpr T const* value_ptr(mat<4, 4, T> const& m)
{
	return &(m[0].x);
}

// transfom
template <typename T>
inline mat<4, 4, T> translate(vec<3, T> const& v)
{
	return translate(mat<4, 4, T>(static_cast<T>(1)), v);
}

template <typename T>
inline mat<4, 4, T> rotate(T angle, vec<3, T> const& v)
{
	return rotate(mat<4, 4, T>(static_cast<T>(1)), angle, v);
}

template <typename T>
inline mat<4, 4, T> scale(vec<3, T> const& v)
{
	return scale(mat<4, 4, T>(static_cast<T>(1)), v);
}

} // math

} // Kinai
