#pragma once

# include "type/type.hpp"
# include "type/vec3.hpp"
# include "type/mat3x3.hpp"

namespace Kinai
{

namespace math
{

template <typename T>
inline vec<3, T> slerp(vec<3, T> const& x, vec<3, T> const& y, T const& a)
{
	// get cosine of angle between vectors (-1 -> 1)
	T CosAlpha = dot(x, y);
	// get angle (0 -> pi)
	T Alpha = acos(CosAlpha);
	// get sine of angle between vectors (0 -> 1)
	T SinAlpha = sin(Alpha);
	// this breaks down when SinAlpha = 0, i.e. Alpha = 0 or pi
	T t1 = sin((static_cast<T>(1) - a) * Alpha) / SinAlpha;
	T t2 = sin(a * Alpha) / SinAlpha;

	// interpolate src vectors
	return x * t1 + y * t2;
}

template <typename T>
inline vec<2, T> rotate(vec<2, T> const& v, T const& angle)
{
	vec<2, T> Result;
	T const Cos(cos(angle));
	T const Sin(sin(angle));

	Result.x = v.x * Cos - v.y * Sin;
	Result.y = v.x * Sin + v.y * Cos;
	return Result;
}

template <typename T>
inline vec<3, T> rotate(vec<3, T> const& v, T const& angle, vec<3, T> const& normal)
{
	return mat<3, 3, T>(math::rotate(angle, normal)) * v;
}
/*
template <typename T>
inline vec<3, T> rotateGTX(
	const vec<3, T>& x,
	T angle,
	const vec<3, T>& normal)
{
	const T Cos = cos(radians(angle));
	const T Sin = sin(radians(angle));
	return x * Cos + ((x * normal) * (T(1) - Cos)) * normal + cross(x, normal) * Sin;
}
*/
template <typename T>
inline vec<4, T> rotate(vec<4, T> const& v, T const& angle, vec<3, T> const& normal)
{
	return rotate(angle, normal) * v;
}

template <typename T>
inline vec<3, T> rotateX(vec<3, T> const& v, T const& angle)
{
	vec<3, T> Result(v);
	T const Cos(cos(angle));
	T const Sin(sin(angle));

	Result.y = v.y * Cos - v.z * Sin;
	Result.z = v.y * Sin + v.z * Cos;
	return Result;
}

template <typename T>
inline vec<3, T> rotateY(vec<3, T> const& v, T const& angle)
{
	vec<3, T> Result = v;
	T const Cos(cos(angle));
	T const Sin(sin(angle));

	Result.x =  v.x * Cos + v.z * Sin;
	Result.z = -v.x * Sin + v.z * Cos;
	return Result;
}

template <typename T>
inline vec<3, T> rotateZ(vec<3, T> const& v, T const& angle)
{
	vec<3, T> Result = v;
	T const Cos(cos(angle));
	T const Sin(sin(angle));

	Result.x = v.x * Cos - v.y * Sin;
	Result.y = v.x * Sin + v.y * Cos;
	return Result;
}

template <typename T>
inline vec<4, T> rotateX(vec<4, T> const& v, T const& angle)
{
	vec<4, T> Result = v;
	T const Cos(cos(angle));
	T const Sin(sin(angle));

	Result.y = v.y * Cos - v.z * Sin;
	Result.z = v.y * Sin + v.z * Cos;
	return Result;
}

template <typename T>
inline vec<4, T> rotateY(vec<4, T> const& v, T const& angle)
{
	vec<4, T> Result = v;
	T const Cos(cos(angle));
	T const Sin(sin(angle));

	Result.x =  v.x * Cos + v.z * Sin;
	Result.z = -v.x * Sin + v.z * Cos;
	return Result;
}

template <typename T>
inline vec<4, T> rotateZ(vec<4, T> const& v, T const& angle)
{
	vec<4, T> Result = v;
	T const Cos(cos(angle));
	T const Sin(sin(angle));

	Result.x = v.x * Cos - v.y * Sin;
	Result.y = v.x * Sin + v.y * Cos;
	return Result;
}

template <typename T>
inline mat<4, 4, T> orientation(vec<3, T> const& Normal, vec<3, T> const& Up)
{
	if(all(equal(Normal, Up, epsilon<T>())))
		return mat<4, 4, T>(static_cast<T>(1));

	vec<3, T> RotationAxis = cross(Up, Normal);
	T Angle = acos(dot(Normal, Up));

	return rotate(Angle, RotationAxis);
}
	
} // math

} // Kinai
