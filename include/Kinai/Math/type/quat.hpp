#pragma once

#include "mat3x3.hpp"
#include "mat4x4.hpp"
#include "vec3.hpp"
#include "vec4.hpp"
// #include "../vector_relational.hpp"
// #include "../quaternion_relational.hpp"
// #include "../gtc/constants.hpp"
// #include "../matrix_transform.hpp"
// #include "../matrix.hpp"

// #include "../trigonometric.hpp"
// #include "../exponential.hpp"
// #include "../ext/quaternion_common.hpp"
// #include "../ext/quaternion_geometric.hpp"

#include "../geometric.hpp"
#include "../trigonometric.hpp"
#include "../func_matrix.hpp"

namespace Kinai
{

namespace math
{

template<typename T>
struct qua
{
	// -- Implementation math --

	typedef qua<T> type;
	typedef T value_type;

	// -- Data --
	T x, y, z, w;

	// -- Component accesses --

	typedef length_t length_type;

	/// Return the count of components of a quaternion
	static constexpr length_type length(){return 4;}

	constexpr T & operator[](length_type i);
	constexpr T const& operator[](length_type i) const;

	// -- Implicit basic constructors --

	constexpr qua() = default;
	constexpr qua(qua<T> const& q) = default;

	// -- Explicit basic constructors --

	constexpr qua(T s, vec<3, T> const& v);

	constexpr qua(T w, T x, T y, T z);

	static constexpr qua<T> wxyz(T w, T x, T y, T z);

	// -- Conversion constructors --

	template<typename U>
	constexpr explicit qua(qua<U> const& q);

	explicit operator mat<3, 3, T>() const;
	explicit operator mat<4, 4, T>() const;

	qua(vec<3, T> const& u, vec<3, T> const& v);

	/// Build a quaternion from euler angles (pitch, yaw, roll), in radians.
	constexpr explicit qua(vec<3, T> const& eulerAngles);
	constexpr explicit qua(mat<3, 3, T> const& q);
	constexpr explicit qua(mat<4, 4, T> const& q);

	// -- Unary arithmetic operators --

	constexpr qua<T>& operator=(qua<T> const& q) = default;

	template<typename U>
	constexpr qua<T>& operator=(qua<U> const& q);
	template<typename U>
	constexpr qua<T>& operator+=(qua<U> const& q);
	template<typename U>
	constexpr qua<T>& operator-=(qua<U> const& q);
	template<typename U>
	constexpr qua<T>& operator*=(qua<U> const& q);
	template<typename U>
	constexpr qua<T>& operator*=(U s);
	template<typename U>
	constexpr qua<T>& operator/=(U s);
};

// -- Unary bit operators --

template<typename T>
constexpr qua<T> operator+(qua<T> const& q);

template<typename T>
constexpr qua<T> operator-(qua<T> const& q);

// -- Binary operators --

template<typename T>
constexpr qua<T> operator+(qua<T> const& q, qua<T> const& p);

template<typename T>
constexpr qua<T> operator-(qua<T> const& q, qua<T> const& p);

template<typename T>
constexpr qua<T> operator*(qua<T> const& q, qua<T> const& p);

template<typename T>
constexpr vec<3, T> operator*(qua<T> const& q, vec<3, T> const& v);

template<typename T>
constexpr vec<3, T> operator*(vec<3, T> const& v, qua<T> const& q);

template<typename T>
constexpr vec<4, T> operator*(qua<T> const& q, vec<4, T> const& v);

template<typename T>
constexpr vec<4, T> operator*(vec<4, T> const& v, qua<T> const& q);

template<typename T>
constexpr qua<T> operator*(qua<T> const& q, T const& s);

template<typename T>
constexpr qua<T> operator*(T const& s, qua<T> const& q);

template<typename T>
constexpr qua<T> operator/(qua<T> const& q, T const& s);

// -- Boolean operators --

template<typename T>
constexpr bool operator==(qua<T> const& q1, qua<T> const& q2);

template<typename T>
constexpr bool operator!=(qua<T> const& q1, qua<T> const& q2);

template<typename T>
struct compute_dot<qua<T>, T>
{
	inline constexpr static T call(qua<T> const& a, qua<T> const& b)
	{
		vec<4, T> tmp(a.w * b.w, a.x * b.x, a.y * b.y, a.z * b.z);
		return (tmp.x + tmp.y) + (tmp.z + tmp.w);
	}
};

template<typename T>
struct compute_quat_add
{
	inline constexpr static qua<T> call(qua<T> const& q, qua<T> const& p)
	{
		return qua<T>::wxyz(q.w + p.w, q.x + p.x, q.y + p.y, q.z + p.z);
	}
};

template<typename T>
struct compute_quat_sub
{
	inline constexpr static qua<T> call(qua<T> const& q, qua<T> const& p)
	{
		return qua<T>::wxyz(q.w - p.w, q.x - p.x, q.y - p.y, q.z - p.z);
	}
};

template<typename T>
struct compute_quat_mul_scalar
{
	inline constexpr static qua<T> call(qua<T> const& q, T s)
	{
		return qua<T>::wxyz(q.w * s, q.x * s, q.y * s, q.z * s);
	}
};

template<typename T>
struct compute_quat_div_scalar
{
	inline constexpr static qua<T> call(qua<T> const& q, T s)
	{
		return qua<T>::wxyz(q.w / s, q.x / s, q.y / s, q.z / s);
	}
};

template<typename T>
struct compute_quat_mul_vec4
{
	inline constexpr static vec<4, T> call(qua<T> const& q, vec<4, T> const& v)
	{
		return vec<4, T>(q * vec<3, T>(v), v.w);
	}
};

// -- Component accesses --

template<typename T>
inline constexpr T & qua<T>::operator[](typename qua<T>::length_type i)
{
	KINAI_ASSERT_LENGTH(i, this->length());
	return (&x)[i];
}

template<typename T>
inline constexpr T const& qua<T>::operator[](typename qua<T>::length_type i) const
{
	KINAI_ASSERT_LENGTH(i, this->length());
	return (&x)[i];
}

// -- Explicit basic constructors --

template<typename T>
inline constexpr qua<T>::qua(T s, vec<3, T> const& v)
	: x(v.x), y(v.y), z(v.z), w(s)
{}

template <typename T>
inline constexpr qua<T>::qua(T _w, T _x, T _y, T _z)
	: x(_x), y(_y), z(_z), w(_w)
{}

template <typename T>
constexpr qua<T> qua<T>::wxyz(T w, T x, T y, T z) {
	return qua<T>(w, x, y, z);
}

// -- Conversion constructors --

template<typename T>
template<typename U>
inline constexpr qua<T>::qua(qua<U> const& q)
	: x(static_cast<T>(q.x)), y(static_cast<T>(q.y)), z(static_cast<T>(q.z)), w(static_cast<T>(q.w))
{}

//template<typename valType>
//inline qua<valType>::qua
//(
//	valType const& pitch,
//	valType const& yaw,
//	valType const& roll
//)
//{
//	vec<3, valType> eulerAngle(pitch * valType(0.5), yaw * valType(0.5), roll * valType(0.5));
//	vec<3, valType> c = math::cos(eulerAngle * valType(0.5));
//	vec<3, valType> s = math::sin(eulerAngle * valType(0.5));
//
//	this->w = c.x * c.y * c.z + s.x * s.y * s.z;
//	this->x = s.x * c.y * c.z - c.x * s.y * s.z;
//	this->y = c.x * s.y * c.z + s.x * c.y * s.z;
//	this->z = c.x * c.y * s.z - s.x * s.y * c.z;
//}

template<typename T>
inline qua<T>::qua(vec<3, T> const& u, vec<3, T> const& v)
{
	T norm_u_norm_v = sqrt(dot(u, u) * dot(v, v));
	T real_part = norm_u_norm_v + dot(u, v);
	vec<3, T> t;

	if(real_part < static_cast<T>(1.e-6f) * norm_u_norm_v)
	{
		// If u and v are exactly opposite, rotate 180 degrees
		// around an arbitrary orthogonal axis. Axis normalisation
		// can happen later, when we normalise the quaternion.
		real_part = static_cast<T>(0);
		t = abs(u.x) > abs(u.z) ? vec<3, T>(-u.y, u.x, static_cast<T>(0)) : vec<3, T>(static_cast<T>(0), -u.z, u.y);
	}
	else
	{
		// Otherwise, build quaternion the standard way.
		t = cross(u, v);
	}

	*this = normalize(qua<T>::wxyz(real_part, t.x, t.y, t.z));
}

template<typename T>
inline constexpr qua<T>::qua(vec<3, T> const& eulerAngle)
{
	vec<3, T> c = math::cos(eulerAngle * T(0.5));
	vec<3, T> s = math::sin(eulerAngle * T(0.5));

	this->w = c.x * c.y * c.z + s.x * s.y * s.z;
	this->x = s.x * c.y * c.z - c.x * s.y * s.z;
	this->y = c.x * s.y * c.z + s.x * c.y * s.z;
	this->z = c.x * c.y * s.z - s.x * s.y * c.z;
}

template<typename T>
inline constexpr qua<T>::qua(mat<3, 3, T> const& m)
{
	*this = quat_cast(m);
}

template<typename T>
inline constexpr qua<T>::qua(mat<4, 4, T> const& m)
{
	*this = quat_cast(m);
}

template<typename T>
inline qua<T>::operator mat<3, 3, T>() const
{
	return mat3_cast(*this);
}

template<typename T>
inline qua<T>::operator mat<4, 4, T>() const
{
	return mat4_cast(*this);
}

// -- Unary arithmetic operators --

template<typename T>
template<typename U>
inline constexpr qua<T> & qua<T>::operator=(qua<U> const& q)
{
	this->w = static_cast<T>(q.w);
	this->x = static_cast<T>(q.x);
	this->y = static_cast<T>(q.y);
	this->z = static_cast<T>(q.z);
	return *this;
}

template<typename T>
template<typename U>
inline constexpr qua<T> & qua<T>::operator+=(qua<U> const& q)
{
	return (*this = math::compute_quat_add<T>::call(*this, qua<T>(q)));
}

template<typename T>
template<typename U>
inline constexpr qua<T> & qua<T>::operator-=(qua<U> const& q)
{
	return (*this = math::compute_quat_sub<T>::call(*this, qua<T>(q)));
}

template<typename T>
template<typename U>
inline constexpr qua<T> & qua<T>::operator*=(qua<U> const& r)
{
	qua<T> const p(*this);
	qua<T> const q(r);

	this->w = p.w * q.w - p.x * q.x - p.y * q.y - p.z * q.z;
	this->x = p.w * q.x + p.x * q.w + p.y * q.z - p.z * q.y;
	this->y = p.w * q.y + p.y * q.w + p.z * q.x - p.x * q.z;
	this->z = p.w * q.z + p.z * q.w + p.x * q.y - p.y * q.x;
	return *this;
}

template<typename T>
template<typename U>
inline constexpr qua<T> & qua<T>::operator*=(U s)
{
	return (*this = math::compute_quat_mul_scalar<T>::call(*this, static_cast<U>(s)));
}

template<typename T>
template<typename U>
inline constexpr qua<T> & qua<T>::operator/=(U s)
{
	return (*this = math::compute_quat_div_scalar<T>::call(*this, static_cast<U>(s)));
}

// -- Unary bit operators --

template<typename T>
inline constexpr qua<T> operator+(qua<T> const& q)
{
	return q;
}

template<typename T>
inline constexpr qua<T> operator-(qua<T> const& q)
{
	return qua<T>::wxyz(-q.w, -q.x, -q.y, -q.z);
}

// -- Binary operators --

template<typename T>
inline constexpr qua<T> operator+(qua<T> const& q, qua<T> const& p)
{
	return qua<T>(q) += p;
}

template<typename T>
inline constexpr qua<T> operator-(qua<T> const& q, qua<T> const& p)
{
	return qua<T>(q) -= p;
}

template<typename T>
inline constexpr qua<T> operator*(qua<T> const& q, qua<T> const& p)
{
	return qua<T>(q) *= p;
}

template<typename T>
inline constexpr vec<3, T> operator*(qua<T> const& q, vec<3, T> const& v)
{
	vec<3, T> const QuatVector(q.x, q.y, q.z);
	vec<3, T> const uv(math::cross(QuatVector, v));
	vec<3, T> const uuv(math::cross(QuatVector, uv));

	return v + ((uv * q.w) + uuv) * static_cast<T>(2);
}

template<typename T>
inline constexpr vec<3, T> operator*(vec<3, T> const& v, qua<T> const& q)
{
	return math::inverse(q) * v;
}

template<typename T>
inline constexpr vec<4, T> operator*(qua<T> const& q, vec<4, T> const& v)
{
	return math::compute_quat_mul_vec4<T>::call(q, v);
}

template<typename T>
inline constexpr vec<4, T> operator*(vec<4, T> const& v, qua<T> const& q)
{
	return math::inverse(q) * v;
}

template<typename T>
inline constexpr qua<T> operator*(qua<T> const& q, T const& s)
{
	return qua<T>::wxyz(
		q.w * s, q.x * s, q.y * s, q.z * s);
}

template<typename T>
inline constexpr qua<T> operator*(T const& s, qua<T> const& q)
{
	return q * s;
}

template<typename T>
inline constexpr qua<T> operator/(qua<T> const& q, T const& s)
{
	return qua<T>::wxyz(
		q.w / s, q.x / s, q.y / s, q.z / s);
}

// -- Boolean operators --

template<typename T>
inline constexpr bool operator==(qua<T> const& q1, qua<T> const& q2)
{
	return q1.x == q2.x && q1.y == q2.y && q1.z == q2.z && q1.w == q2.w;
}

template<typename T>
inline constexpr bool operator!=(qua<T> const& q1, qua<T> const& q2)
{
	return q1.x != q2.x || q1.y != q2.y || q1.z != q2.z || q1.w != q2.w;
}

} // math

} // Kinai
