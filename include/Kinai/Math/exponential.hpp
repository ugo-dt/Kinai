#pragma once

# include "type/vec1.hpp"
# include "type/vec2.hpp"
# include "type/vec3.hpp"
# include "type/vec4.hpp"
# include "type/vectorize.hpp"

namespace Kinai
{

namespace math
{

using std::log2;

template <length_t L, typename T, bool isFloat>
struct compute_log2
{
	inline static vec<L, T> call(vec<L, T> const& v)
	{
		static_assert(std::numeric_limits<T>::is_iec559, "'log2' only accepts floating-point inputs.");

		return functor1<vec, L, T, T>::call(log2, v);
	}
};

template <length_t L, typename T>
struct compute_sqrt
{
	inline static vec<L, T> call(vec<L, T> const& x)
	{
		return functor1<vec, L, T, T>::call(std::sqrt, x);
	}
};

template <length_t L, typename T>
struct compute_inversesqrt
{
	inline static vec<L, T> call(vec<L, T> const& x)
	{
		return static_cast<T>(1) / sqrt(x);
	}
};

template <length_t L>
struct compute_inversesqrt<L, float>
{
	inline static vec<L, float> call(vec<L, float> const& x)
	{
		vec<L, float> tmp(x);
		vec<L, float> xhalf(tmp * 0.5f);
		vec<L, uint_t>* p = reinterpret_cast<vec<L, uint_t>*>(const_cast<vec<L, float>*>(&x));
		vec<L, uint_t> i = vec<L, uint_t>(0x5f375a86) - (*p >> vec<L, uint_t>(1));
		vec<L, float>* ptmp = reinterpret_cast<vec<L, float>*>(&i);
		tmp = *ptmp;
		tmp = tmp * (1.5f - xhalf * tmp * tmp);
		return tmp;
	}
};

// pow
using std::pow;
template <length_t L, typename T>
inline vec<L, T> pow(vec<L, T> const& base, vec<L, T> const& exponent)
{
	return functor2<vec, L, T>::call(pow, base, exponent);
}

// exp
using std::exp;
template <length_t L, typename T>
inline vec<L, T> exp(vec<L, T> const& x)
{
	return functor1<vec, L, T, T>::call(exp, x);
}

// log
using std::log;
template <length_t L, typename T>
inline vec<L, T> log(vec<L, T> const& x)
{
	return functor1<vec, L, T, T>::call(log, x);
}

using std::exp2;

template <length_t L, typename T>
inline vec<L, T> exp2(vec<L, T> const& x)
{
	return functor1<vec, L, T, T>::call(exp2, x);
}

// log2, ln2 = 0.69314718055994530941723212145818f
template <typename T>
inline T log2(T x)
{
	return log2(vec<1, T>(x)).x;
}

template <length_t L, typename T>
inline vec<L, T> log2(vec<L, T> const& x)
{
	return compute_log2<L, T, std::numeric_limits<T>::is_iec559>::call(x);
}

// sqrt
using std::sqrt;
template <length_t L, typename T>
inline vec<L, T> sqrt(vec<L, T> const& x)
{
	static_assert(std::numeric_limits<T>::is_iec559, "'sqrt' only accepts floating-point inputs");
	return compute_sqrt<L, T>::call(x);
}

// inversesqrt
template <typename T>
inline T inversesqrt(T x)
{
	return static_cast<T>(1) / sqrt(x);
}

template <length_t L, typename T>
inline vec<L, T> inversesqrt(vec<L, T> const& x)
{
	static_assert(std::numeric_limits<T>::is_iec559, "'inversesqrt' only accepts floating-point inputs");
	return compute_inversesqrt<L, T>::call(x);
}

} // math

} // Kinai
