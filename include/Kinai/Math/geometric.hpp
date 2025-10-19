#pragma once

# include "common.hpp"
# include "exponential.hpp"

namespace Kinai
{

namespace math
{

template <length_t L, typename T>
struct compute_length
{
	inline static T call(vec<L, T> const& v)
	{
		return sqrt(dot(v, v));
	}
};

template <length_t L, typename T>
struct compute_distance
{
	inline static T call(vec<L, T> const& p0, vec<L, T> const& p1)
	{
		return length(p1 - p0);
	}
};

template <typename V, typename T>
struct compute_dot{};

template <typename T>
struct compute_dot<vec<1, T>, T>
{
	inline static T call(vec<1, T> const& a, vec<1, T> const& b)
	{
		return a.x * b.x;
	}
};

template <typename T>
struct compute_dot<vec<2, T>, T>
{
	inline static T call(vec<2, T> const& a, vec<2, T> const& b)
	{
		vec<2, T> tmp(a * b);
		return tmp.x + tmp.y;
	}
};

template <typename T>
struct compute_dot<vec<3, T>, T>
{
	inline static T call(vec<3, T> const& a, vec<3, T> const& b)
	{
		vec<3, T> tmp(a * b);
		return tmp.x + tmp.y + tmp.z;
	}
};

template <typename T>
struct compute_dot<vec<4, T>, T>
{
	inline static T call(vec<4, T> const& a, vec<4, T> const& b)
	{
		vec<4, T> tmp(a * b);
		return (tmp.x + tmp.y) + (tmp.z + tmp.w);
	}
};

template <typename T>
struct compute_cross
{
	inline static vec<3, T> call(vec<3, T> const& x, vec<3, T> const& y)
	{
		static_assert(std::numeric_limits<T>::is_iec559, "'cross' accepts only floating-point inputs");

		return vec<3, T>(
			x.y * y.z - y.y * x.z,
			x.z * y.x - y.z * x.x,
			x.x * y.y - y.x * x.y);
	}
};

template <length_t L, typename T>
struct compute_normalize
{
	inline static vec<L, T> call(vec<L, T> const& v)
	{
		static_assert(std::numeric_limits<T>::is_iec559, "'normalize' accepts only floating-point inputs");

		return v * inversesqrt(dot(v, v));
	}
};

template <length_t L, typename T>
struct compute_faceforward
{
	inline static vec<L, T> call(vec<L, T> const& N, vec<L, T> const& I, vec<L, T> const& Nref)
	{
		static_assert(std::numeric_limits<T>::is_iec559, "'normalize' accepts only floating-point inputs");

		return dot(Nref, I) < static_cast<T>(0) ? N : -N;
	}
};

template <length_t L, typename T>
struct compute_reflect
{
	inline static vec<L, T> call(vec<L, T> const& I, vec<L, T> const& N)
	{
		return I - N * dot(N, I) * static_cast<T>(2);
	}
};

template <length_t L, typename T>
struct compute_refract
{
	inline static vec<L, T> call(vec<L, T> const& I, vec<L, T> const& N, T eta)
	{
		T const dotValue(dot(N, I));
		T const k(static_cast<T>(1) - eta * eta * (static_cast<T>(1) - dotValue * dotValue));
		vec<L, T> const Result =
			(k >= static_cast<T>(0)) ? (eta * I - (eta * dotValue + std::sqrt(k)) * N) : vec<L, T>(0);
		return Result;
	}
};

// length
template <typename T>
inline T length(T x)
{
	static_assert(std::numeric_limits<T>::is_iec559, "'length' accepts only floating-point inputs");

	return math::abs(x);
}

template <length_t L, typename T>
inline T length(vec<L, T> const& v)
{
	static_assert(std::numeric_limits<T>::is_iec559, "'length' accepts only floating-point inputs");

	return compute_length<L, T>::call(v);
}

// distance
template <typename T>
inline T distance(T const& p0, T const& p1)
{
	static_assert(std::numeric_limits<T>::is_iec559, "'distance' accepts only floating-point inputs");

	return length(p1 - p0);
}

template <length_t L, typename T>
inline T distance(vec<L, T> const& p0, vec<L, T> const& p1)
{
	return compute_distance<L, T>::call(p0, p1);
}

// dot
template <typename T>
inline T dot(T x, T y)
{
	static_assert(std::numeric_limits<T>::is_iec559, "'dot' accepts only floating-point inputs");
	return x * y;
}

template <length_t L, typename T>
inline T dot(vec<L, T> const& x, vec<L, T> const& y)
{
	static_assert(std::numeric_limits<T>::is_iec559, "'dot' accepts only floating-point inputs");
	return compute_dot<vec<L, T>, T>::call(x, y);
}

// cross
template <typename T>
inline vec<3, T> cross(vec<3, T> const& x, vec<3, T> const& y)
{
	return compute_cross<T>::call(x, y);
}
/*
// normalize
template <typename T>
inline T normalize(T const& x)
{
	static_assert(std::numeric_limits<T>::is_iec559, "'normalize' accepts only floating-point inputs");

	return x < T(0) ? T(-1) : T(1);
}
*/
template <length_t L, typename T>
inline vec<L, T> normalize(vec<L, T> const& x)
{
	static_assert(std::numeric_limits<T>::is_iec559, "'normalize' accepts only floating-point inputs");

	return compute_normalize<L, T>::call(x);
}

// faceforward
template <typename T>
inline T faceforward(T const& N, T const& I, T const& Nref)
{
	return dot(Nref, I) < static_cast<T>(0) ? N : -N;
}

template <length_t L, typename T>
inline vec<L, T> faceforward(vec<L, T> const& N, vec<L, T> const& I, vec<L, T> const& Nref)
{
	return compute_faceforward<L, T>::call(N, I, Nref);
}

// reflect
template <typename T>
inline T reflect(T const& I, T const& N)
{
	return I - N * dot(N, I) * T(2);
}

template <length_t L, typename T>
inline vec<L, T> reflect(vec<L, T> const& I, vec<L, T> const& N)
{
	return compute_reflect<L, T>::call(I, N);
}

// refract
template <typename T>
inline T refract(T const& I, T const& N, T eta)
{
	static_assert(std::numeric_limits<T>::is_iec559, "'refract' accepts only floating-point inputs");
	T const dotValue(dot(N, I));
	T const k(static_cast<T>(1) - eta * eta * (static_cast<T>(1) - dotValue * dotValue));
	return (eta * I - (eta * dotValue + sqrt(k)) * N) * static_cast<T>(k >= static_cast<T>(0));
}

template <length_t L, typename T>
inline vec<L, T> refract(vec<L, T> const& I, vec<L, T> const& N, T eta)
{
	static_assert(std::numeric_limits<T>::is_iec559, "'refract' accepts only floating-point inputs");
	return compute_refract<L, T>::call(I, N, eta);
}

} // math

} // Kinai
