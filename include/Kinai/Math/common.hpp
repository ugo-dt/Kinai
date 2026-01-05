#pragma once

#include "vector_relational.hpp"
#include "type/vec1.hpp"
#include "type/vec2.hpp"
#include "type/vec3.hpp"
#include "type/vec4.hpp"
#include "type/vectorize.hpp"

namespace Kinai
{

namespace math
{

// min
template <typename T>
inline constexpr T min(T x, T y)
{
	static_assert(std::numeric_limits<T>::is_iec559 || std::numeric_limits<T>::is_integer, "'min' only accepts floating-point or integer inputs");
	return (y < x) ? y : x;
}

// max
template <typename T>
inline constexpr T max(T x, T y)
{
	static_assert(std::numeric_limits<T>::is_iec559 || std::numeric_limits<T>::is_integer, "'max' only accepts floating-point or integer inputs");

	return (x < y) ? y : x;
}

// abs
inline constexpr int abs(int x)
{
	int const y = x >> (sizeof(int) * 8 - 1);
	return (x ^ y) - y;
}

// round
using ::std::round;

// trunc
using ::std::trunc;

template <length_t L, typename T>
struct compute_abs_vector
{
	inline constexpr static vec<L, T> call(vec<L, T> const& x)
	{
		return functor1<vec, L, T, T>::call(abs, x);
	}
};

template <length_t L, typename T, typename U>
struct compute_mix_vector
{
	inline static vec<L, T> call(vec<L, T> const& x, vec<L, T> const& y, vec<L, U> const& a)
	{
		static_assert(std::numeric_limits<U>::is_iec559, "'mix' only accepts floating-point inputs for the interpolator a");

		return vec<L, T>(vec<L, U>(x) * (static_cast<U>(1) - a) + vec<L, U>(y) * a);
	}
};

template <length_t L, typename T>
struct compute_mix_vector<L, T, bool>
{
	inline static vec<L, T> call(vec<L, T> const& x, vec<L, T> const& y, vec<L, bool> const& a)
	{
		vec<L, T> Result;
		for(length_t i = 0; i < x.length(); ++i)
			Result[i] = a[i] ? y[i] : x[i];
		return Result;
	}
};

template <length_t L, typename T, typename U>
struct compute_mix_scalar
{
	inline static vec<L, T> call(vec<L, T> const& x, vec<L, T> const& y, U const& a)
	{
		static_assert(std::numeric_limits<U>::is_iec559, "'mix' only accepts floating-point inputs for the interpolator a");

		return vec<L, T>(vec<L, U>(x) * (static_cast<U>(1) - a) + vec<L, U>(y) * a);
	}
};

template <length_t L, typename T>
struct compute_mix_scalar<L, T, bool>
{
	inline static vec<L, T> call(vec<L, T> const& x, vec<L, T> const& y, bool const& a)
	{
		return a ? y : x;
	}
};

template <typename T, typename U>
struct compute_mix
{
	inline static T call(T const& x, T const& y, U const& a)
	{
		static_assert(std::numeric_limits<U>::is_iec559, "'mix' only accepts floating-point inputs for the interpolator a");

		return static_cast<T>(static_cast<U>(x) * (static_cast<U>(1) - a) + static_cast<U>(y) * a);
	}
};

template <typename T>
struct compute_mix<T, bool>
{
	inline static T call(T const& x, T const& y, bool const& a)
	{
		return a ? y : x;
	}
};

template <length_t L, typename T, bool isFloat>
struct compute_sign
{
	inline static vec<L, T> call(vec<L, T> const& x)
	{
		return vec<L, T>(Kinai::math::lessThan(vec<L, T>(0), x)) - vec<L, T>(Kinai::math::lessThan(x, vec<L, T>(0)));
	}
};

template <length_t L, typename T>
struct compute_floor
{
	inline static vec<L, T> call(vec<L, T> const& x)
	{
		return functor1<vec, L, T, T>::call(std::floor, x);
	}
};

template <length_t L, typename T>
struct compute_ceil
{
	inline static vec<L, T> call(vec<L, T> const& x)
	{
		return functor1<vec, L, T, T>::call(std::ceil, x);
	}
};

template <length_t L, typename T>
struct compute_fract
{
	inline static vec<L, T> call(vec<L, T> const& x)
	{
		return x - floor(x);
	}
};

template <length_t L, typename T>
struct compute_trunc
{
	inline static vec<L, T> call(vec<L, T> const& x)
	{
		return functor1<vec, L, T, T>::call(trunc, x);
	}
};

template <length_t L, typename T>
struct compute_round
{
	inline static vec<L, T> call(vec<L, T> const& x)
	{
		return functor1<vec, L, T, T>::call(round, x);
	}
};

template <length_t L, typename T>
struct compute_mod
{
	inline static vec<L, T> call(vec<L, T> const& a, vec<L, T> const& b)
	{
		static_assert(std::numeric_limits<T>::is_iec559, "'mod' only accepts floating-point inputs.");
		return a - b * floor(a / b);
	}
};

template <length_t L, typename T>
struct compute_min_vector
{
	inline static vec<L, T> call(vec<L, T> const& x, vec<L, T> const& y)
	{
		return functor2<vec, L, T>::call(min, x, y);
	}
};

template <length_t L, typename T>
struct compute_max_vector
{
	inline static vec<L, T> call(vec<L, T> const& x, vec<L, T> const& y)
	{
		return functor2<vec, L, T>::call(max, x, y);
	}
};

template <length_t L, typename T>
struct compute_clamp_vector
{
	inline static vec<L, T> call(vec<L, T> const& x, vec<L, T> const& minVal, vec<L, T> const& maxVal)
	{
		return min(max(x, minVal), maxVal);
	}
};

template <length_t L, typename T>
struct compute_step_vector
{
	inline static vec<L, T> call(vec<L, T> const& edge, vec<L, T> const& x)
	{
		return mix(vec<L, T>(1), vec<L, T>(0), Kinai::math::lessThan(x, edge));
	}
};

template <length_t L, typename T>
struct compute_smoothstep_vector
{
	inline static vec<L, T> call(vec<L, T> const& edge0, vec<L, T> const& edge1, vec<L, T> const& x)
	{
		static_assert(std::numeric_limits<T>::is_iec559, "'smoothstep' only accepts floating-point inputs");
		vec<L, T> const tmp(clamp((x - edge0) / (edge1 - edge0), static_cast<T>(0), static_cast<T>(1)));
		return tmp * tmp * (static_cast<T>(3) - static_cast<T>(2) * tmp);
	}
};

template <typename T>
inline constexpr T abs(T x)
{
	return compute_abs<T, std::numeric_limits<T>::is_signed>::call(x);
}

template <length_t L, typename T>
inline constexpr vec<L, T> abs(vec<L, T> const& x)
{
	return compute_abs_vector<L, T>::call(x);
}

// sign
// fast and works for any type
template <typename T>
inline T sign(T x)
{
	static_assert(
		std::numeric_limits<T>::is_iec559 || (std::numeric_limits<T>::is_signed && std::numeric_limits<T>::is_integer),
		"'sign' only accepts signed inputs");

	return compute_sign<1, T, std::numeric_limits<T>::is_iec559>::call(vec<1, T>(x)).x;
}

template <length_t L, typename T>
inline vec<L, T> sign(vec<L, T> const& x)
{
	static_assert(
		std::numeric_limits<T>::is_iec559 || (std::numeric_limits<T>::is_signed && std::numeric_limits<T>::is_integer),
		"'sign' only accepts signed inputs");

	return compute_sign<L, T, std::numeric_limits<T>::is_iec559>::call(x);
}

// floor
using ::std::floor;
template <length_t L, typename T>
inline vec<L, T> floor(vec<L, T> const& x)
{
	static_assert(std::numeric_limits<T>::is_iec559, "'floor' only accepts floating-point inputs.");
	return compute_floor<L, T>::call(x);
}

template <length_t L, typename T>
inline vec<L, T> trunc(vec<L, T> const& x)
{
	static_assert(std::numeric_limits<T>::is_iec559, "'trunc' only accepts floating-point inputs");
	return compute_trunc<L, T>::call(x);
}

template <length_t L, typename T>
inline vec<L, T> round(vec<L, T> const& x)
{
	static_assert(std::numeric_limits<T>::is_iec559, "'round' only accepts floating-point inputs");
	return compute_round<L, T>::call(x);
}

/*
// roundEven
template <typename T>
inline T roundEven(T const& x)
{
	static_assert(std::numeric_limits<T>::is_iec559, "'roundEven' only accepts floating-point inputs");

	return T(int(x + T(int(x) % 2)));
}
*/

// roundEven
template <typename T>
inline T roundEven(T x)
{
	static_assert(std::numeric_limits<T>::is_iec559, "'roundEven' only accepts floating-point inputs");

	int Integer = static_cast<int>(x);
	T IntegerPart = static_cast<T>(Integer);
	T FractionalPart = fract(x);

	if(FractionalPart > static_cast<T>(0.5) || FractionalPart < static_cast<T>(0.5))
	{
		return round(x);
	}
	else if((Integer % 2) == 0)
	{
		return IntegerPart;
	}
	else if(x <= static_cast<T>(0)) // Work around...
	{
		return IntegerPart - static_cast<T>(1);
	}
	else
	{
		return IntegerPart + static_cast<T>(1);
	}
	//else // Bug on MinGW 4.5.2
	//{
	//	return mix(IntegerPart + T(-1), IntegerPart + T(1), x <= T(0));
	//}
}

template <length_t L, typename T>
inline vec<L, T> roundEven(vec<L, T> const& x)
{
	static_assert(std::numeric_limits<T>::is_iec559, "'roundEven' only accepts floating-point inputs");
	return functor1<vec, L, T, T>::call(roundEven, x);
}

// ceil
using ::std::ceil;
template <length_t L, typename T>
inline vec<L, T> ceil(vec<L, T> const& x)
{
	static_assert(std::numeric_limits<T>::is_iec559, "'ceil' only accepts floating-point inputs");
	return compute_ceil<L, T>::call(x);
}

// fract
template <typename T>
inline T fract(T x)
{
	return fract(vec<1, T>(x)).x;
}

template <length_t L, typename T>
inline vec<L, T> fract(vec<L, T> const& x)
{
	static_assert(std::numeric_limits<T>::is_iec559, "'fract' only accepts floating-point inputs");
	return compute_fract<L, T>::call(x);
}

// mod
template <typename T>
inline T mod(T x, T y)
{
	return mod(vec<1, T>(x), y).x;
}

template <length_t L, typename T>
inline vec<L, T> mod(vec<L, T> const& x, T y)
{
	return compute_mod<L, T>::call(x, vec<L, T>(y));
}

template <length_t L, typename T>
inline vec<L, T> mod(vec<L, T> const& x, vec<L, T> const& y)
{
	return compute_mod<L, T>::call(x, y);
}

// modf
template <typename T>
inline T modf(T x, T & i)
{
	static_assert(std::numeric_limits<T>::is_iec559, "'modf' only accepts floating-point inputs");
	return std::modf(x, &i);
}

template <typename T>
inline vec<1, T> modf(vec<1, T> const& x, vec<1, T> & i)
{
	return vec<1, T>(
		modf(x.x, i.x));
}

template <typename T>
inline vec<2, T> modf(vec<2, T> const& x, vec<2, T> & i)
{
	return vec<2, T>(
		modf(x.x, i.x),
		modf(x.y, i.y));
}

template <typename T>
inline vec<3, T> modf(vec<3, T> const& x, vec<3, T> & i)
{
	return vec<3, T>(
		modf(x.x, i.x),
		modf(x.y, i.y),
		modf(x.z, i.z));
}

template <typename T>
inline vec<4, T> modf(vec<4, T> const& x, vec<4, T> & i)
{
	return vec<4, T>(
		modf(x.x, i.x),
		modf(x.y, i.y),
		modf(x.z, i.z),
		modf(x.w, i.w));
}

//// Only valid if (INT_MIN <= x-y <= INT_MAX)
//// min(x,y)
//r = y + ((x - y) & ((x - y) >> (sizeof(int) *
//CHAR_BIT - 1)));
//// max(x,y)
//r = x - ((x - y) & ((x - y) >> (sizeof(int) *
//CHAR_BIT - 1)));

// min
template <length_t L, typename T>
inline constexpr vec<L, T> min(vec<L, T> const& a, T b)
{
	static_assert(std::numeric_limits<T>::is_iec559 || std::numeric_limits<T>::is_integer, "'min' only accepts floating-point or integer inputs");
	return compute_min_vector<L, T>::call(a, vec<L, T>(b));
}

template <length_t L, typename T>
inline constexpr vec<L, T> min(vec<L, T> const& a, vec<L, T> const& b)
{
	return compute_min_vector<L, T>::call(a, b);
}

// max
template <length_t L, typename T>
inline constexpr vec<L, T> max(vec<L, T> const& a, T b)
{
	static_assert(std::numeric_limits<T>::is_iec559 || std::numeric_limits<T>::is_integer, "'max' only accepts floating-point or integer inputs");
	return compute_max_vector<L, T>::call(a, vec<L, T>(b));
}

template <length_t L, typename T>
inline constexpr vec<L, T> max(vec<L, T> const& a, vec<L, T> const& b)
{
	return compute_max_vector<L, T>::call(a, b);
}

// clamp
template <typename T>
inline constexpr T clamp(T x, T minVal, T maxVal)
{
	static_assert(std::numeric_limits<T>::is_iec559 || std::numeric_limits<T>::is_integer, "'clamp' only accepts floating-point or integer inputs");
	return min(max(x, minVal), maxVal);
}

template <length_t L, typename T>
inline constexpr vec<L, T> clamp(vec<L, T> const& x, T minVal, T maxVal)
{
	static_assert(std::numeric_limits<T>::is_iec559 || std::numeric_limits<T>::is_integer, "'clamp' only accepts floating-point or integer inputs");
	return compute_clamp_vector<L, T>::call(x, vec<L, T>(minVal), vec<L, T>(maxVal));
}

template <length_t L, typename T>
inline constexpr vec<L, T> clamp(vec<L, T> const& x, vec<L, T> const& minVal, vec<L, T> const& maxVal)
{
	static_assert(std::numeric_limits<T>::is_iec559 || std::numeric_limits<T>::is_integer, "'clamp' only accepts floating-point or integer inputs");
	return compute_clamp_vector<L, T>::call(x, minVal, maxVal);
}

template <typename TT, typename TU>
inline TT mix(TT x, TT y, TU a)
{
	return compute_mix<TT, TU>::call(x, y, a);
}

template <length_t L, typename T, typename U>
inline vec<L, T> mix(vec<L, T> const& x, vec<L, T> const& y, U a)
{
	return compute_mix_scalar<L, T, U>::call(x, y, a);
}

template <length_t L, typename T, typename U>
inline vec<L, T> mix(vec<L, T> const& x, vec<L, T> const& y, vec<L, U> const& a)
{
	return compute_mix_vector<L, T, U>::call(x, y, a);
}

// step
template <typename T>
inline T step(T edge, T x)
{
	return mix(static_cast<T>(1), static_cast<T>(0), x < edge);
}

template <length_t L, typename T>
inline vec<L, T> step(T edge, vec<L, T> const& x)
{
	return compute_step_vector<L, T>::call(vec<L, T>(edge), x);
}

template <length_t L, typename T>
inline vec<L, T> step(vec<L, T> const& edge, vec<L, T> const& x)
{
	return compute_step_vector<L, T>::call(edge, x);
}

// smoothstep
template <typename T>
inline T smoothstep(T edge0, T edge1, T x)
{
	static_assert(std::numeric_limits<T>::is_iec559, "'smoothstep' only accepts floating-point inputs");

	T const tmp(clamp((x - edge0) / (edge1 - edge0), T(0), T(1)));
	return tmp * tmp * (T(3) - T(2) * tmp);
}

template <length_t L, typename T>
inline vec<L, T> smoothstep(T edge0, T edge1, vec<L, T> const& x)
{
	return compute_smoothstep_vector<L, T>::call(vec<L, T>(edge0), vec<L, T>(edge1), x);
}

template <length_t L, typename T>
inline vec<L, T> smoothstep(vec<L, T> const& edge0, vec<L, T> const& edge1, vec<L, T> const& x)
{
	return compute_smoothstep_vector<L, T>::call(edge0, edge1, x);
}

using std::isnan;

template <length_t L, typename T>
inline vec<L, bool> isnan(vec<L, T> const& v)
{
	static_assert(std::numeric_limits<T>::is_iec559, "'isnan' only accepts floating-point inputs");

	vec<L, bool> Result;
	for (length_t l = 0; l < v.length(); ++l)
		Result[l] = Kinai::math::isnan(v[l]);
	return Result;
}

using std::isinf;

template <length_t L, typename T>
inline vec<L, bool> isinf(vec<L, T> const& v)
{
	static_assert(std::numeric_limits<T>::is_iec559, "'isinf' only accepts floating-point inputs");

	vec<L, bool> Result;
	for (length_t l = 0; l < v.length(); ++l)
		Result[l] = Kinai::math::isinf(v[l]);
	return Result;
}

inline int floatBitsToInt(float const& v)
{
	union
	{
		float in;
		int out;
	} u;

	u.in = v;

	return u.out;
}

template <length_t L>
inline vec<L, int> floatBitsToInt(vec<L, float> const& v)
{
	return reinterpret_cast<vec<L, int>&>(const_cast<vec<L, float>&>(v));
}

inline uint_t floatBitsToUint(float const& v)
{
	union
	{
		float in;
		uint_t out;
	} u;

	u.in = v;

	return u.out;
}

template <length_t L>
inline vec<L, uint_t> floatBitsToUint(vec<L, float> const& v)
{
	return reinterpret_cast<vec<L, uint_t>&>(const_cast<vec<L, float>&>(v));
}

inline float intBitsToFloat(int const& v)
{
	union
	{
		int in;
		float out;
	} u;

	u.in = v;

	return u.out;
}

template <length_t L>
inline vec<L, float> intBitsToFloat(vec<L, int> const& v)
{
	return reinterpret_cast<vec<L, float>&>(const_cast<vec<L, int>&>(v));
}

inline float uintBitsToFloat(uint_t const& v)
{
	union
	{
		uint_t in;
		float out;
	} u;

	u.in = v;

	return u.out;
}

template <length_t L>
inline vec<L, float> uintBitsToFloat(vec<L, uint_t> const& v)
{
	return reinterpret_cast<vec<L, float>&>(const_cast<vec<L, uint_t>&>(v));
}

using std::fma;

template <typename T>
inline T frexp(T x, int& exp)
{
	static_assert(std::numeric_limits<T>::is_iec559, "'frexp' only accepts floating-point inputs");

	return std::frexp(x, &exp);
}

template <length_t L, typename T>
inline vec<L, T> frexp(vec<L, T> const& v, vec<L, int>& exp)
{
	static_assert(std::numeric_limits<T>::is_iec559, "'frexp' only accepts floating-point inputs");

	vec<L, T> Result;
	for (length_t l = 0; l < v.length(); ++l)
		Result[l] = std::frexp(v[l], &exp[l]);
	return Result;
}

template <typename T>
inline T ldexp(T const& x, int const& exp)
{
	static_assert(std::numeric_limits<T>::is_iec559, "'ldexp' only accepts floating-point inputs");

	return std::ldexp(x, exp);
}

template <length_t L, typename T>
inline vec<L, T> ldexp(vec<L, T> const& v, vec<L, int> const& exp)
{
	static_assert(std::numeric_limits<T>::is_iec559, "'ldexp' only accepts floating-point inputs");

	vec<L, T> Result;
	for (length_t l = 0; l < v.length(); ++l)
		Result[l] = std::ldexp(v[l], exp[l]);
	return Result;
}

} // math

} // Kinai
