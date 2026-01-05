#pragma once

# include "type/type.hpp"
# include "trigonometric.hpp"

namespace Kinai
{

namespace math
{

template<typename T>
inline mat<4, 4, T> ortho(T left, T right, T bottom, T top)
{
	mat<4, 4, T> Result(static_cast<T>(1));
	Result[0][0] = static_cast<T>(2) / (right - left);
	Result[1][1] = static_cast<T>(2) / (top - bottom);
	Result[2][2] = - static_cast<T>(1);
	Result[3][0] = - (right + left) / (right - left);
	Result[3][1] = - (top + bottom) / (top - bottom);
	return Result;
}

template<typename T>
inline mat<4, 4, T> orthoLH_ZO(T left, T right, T bottom, T top, T zNear, T zFar)
{
	mat<4, 4, T> Result(1);
	Result[0][0] = static_cast<T>(2) / (right - left);
	Result[1][1] = static_cast<T>(2) / (top - bottom);
	Result[2][2] = static_cast<T>(1) / (zFar - zNear);
	Result[3][0] = - (right + left) / (right - left);
	Result[3][1] = - (top + bottom) / (top - bottom);
	Result[3][2] = - zNear / (zFar - zNear);
	return Result;
}

template<typename T>
inline mat<4, 4, T> orthoLH_NO(T left, T right, T bottom, T top, T zNear, T zFar)
{
	mat<4, 4, T> Result(1);
	Result[0][0] = static_cast<T>(2) / (right - left);
	Result[1][1] = static_cast<T>(2) / (top - bottom);
	Result[2][2] = static_cast<T>(2) / (zFar - zNear);
	Result[3][0] = - (right + left) / (right - left);
	Result[3][1] = - (top + bottom) / (top - bottom);
	Result[3][2] = - (zFar + zNear) / (zFar - zNear);
	return Result;
}

template<typename T>
inline mat<4, 4, T> orthoRH_ZO(T left, T right, T bottom, T top, T zNear, T zFar)
{
	mat<4, 4, T> Result(1);
	Result[0][0] = static_cast<T>(2) / (right - left);
	Result[1][1] = static_cast<T>(2) / (top - bottom);
	Result[2][2] = - static_cast<T>(1) / (zFar - zNear);
	Result[3][0] = - (right + left) / (right - left);
	Result[3][1] = - (top + bottom) / (top - bottom);
	Result[3][2] = - zNear / (zFar - zNear);
	return Result;
}

template<typename T>
inline mat<4, 4, T> orthoRH_NO(T left, T right, T bottom, T top, T zNear, T zFar)
{
	mat<4, 4, T> Result(1);
	Result[0][0] = static_cast<T>(2) / (right - left);
	Result[1][1] = static_cast<T>(2) / (top - bottom);
	Result[2][2] = - static_cast<T>(2) / (zFar - zNear);
	Result[3][0] = - (right + left) / (right - left);
	Result[3][1] = - (top + bottom) / (top - bottom);
	Result[3][2] = - (zFar + zNear) / (zFar - zNear);
	return Result;
}

template<typename T>
inline mat<4, 4, T> orthoZO(T left, T right, T bottom, T top, T zNear, T zFar)
{
	return orthoRH_ZO(left, right, bottom, top, zNear, zFar);
}

template<typename T>
inline mat<4, 4, T> orthoNO(T left, T right, T bottom, T top, T zNear, T zFar)
{
	return orthoRH_NO(left, right, bottom, top, zNear, zFar);
}

template<typename T>
inline mat<4, 4, T> orthoLH(T left, T right, T bottom, T top, T zNear, T zFar)
{
	return orthoLH_NO(left, right, bottom, top, zNear, zFar);

}

template<typename T>
inline mat<4, 4, T> orthoRH(T left, T right, T bottom, T top, T zNear, T zFar)
{
	return orthoRH_NO(left, right, bottom, top, zNear, zFar);
}

template<typename T>
inline mat<4, 4, T> ortho(T left, T right, T bottom, T top, T zNear, T zFar)
{
	return orthoRH_ZO(left, right, bottom, top, zNear, zFar);
}

template<typename T>
inline mat<4, 4, T> frustumLH_ZO(T left, T right, T bottom, T top, T nearVal, T farVal)
{
	mat<4, 4, T> Result(0);
	Result[0][0] = (static_cast<T>(2) * nearVal) / (right - left);
	Result[1][1] = (static_cast<T>(2) * nearVal) / (top - bottom);
	Result[2][0] = (right + left) / (right - left);
	Result[2][1] = (top + bottom) / (top - bottom);
	Result[2][2] = farVal / (farVal - nearVal);
	Result[2][3] = static_cast<T>(1);
	Result[3][2] = -(farVal * nearVal) / (farVal - nearVal);
	return Result;
}

template<typename T>
inline mat<4, 4, T> frustumLH_NO(T left, T right, T bottom, T top, T nearVal, T farVal)
{
	mat<4, 4, T> Result(0);
	Result[0][0] = (static_cast<T>(2) * nearVal) / (right - left);
	Result[1][1] = (static_cast<T>(2) * nearVal) / (top - bottom);
	Result[2][0] = (right + left) / (right - left);
	Result[2][1] = (top + bottom) / (top - bottom);
	Result[2][2] = (farVal + nearVal) / (farVal - nearVal);
	Result[2][3] = static_cast<T>(1);
	Result[3][2] = - (static_cast<T>(2) * farVal * nearVal) / (farVal - nearVal);
	return Result;
}

template<typename T>
inline mat<4, 4, T> frustumRH_ZO(T left, T right, T bottom, T top, T nearVal, T farVal)
{
	mat<4, 4, T> Result(0);
	Result[0][0] = (static_cast<T>(2) * nearVal) / (right - left);
	Result[1][1] = (static_cast<T>(2) * nearVal) / (top - bottom);
	Result[2][0] = (right + left) / (right - left);
	Result[2][1] = (top + bottom) / (top - bottom);
	Result[2][2] = farVal / (nearVal - farVal);
	Result[2][3] = static_cast<T>(-1);
	Result[3][2] = -(farVal * nearVal) / (farVal - nearVal);
	return Result;
}

template<typename T>
inline mat<4, 4, T> frustumRH_NO(T left, T right, T bottom, T top, T nearVal, T farVal)
{
	mat<4, 4, T> Result(0);
	Result[0][0] = (static_cast<T>(2) * nearVal) / (right - left);
	Result[1][1] = (static_cast<T>(2) * nearVal) / (top - bottom);
	Result[2][0] = (right + left) / (right - left);
	Result[2][1] = (top + bottom) / (top - bottom);
	Result[2][2] = - (farVal + nearVal) / (farVal - nearVal);
	Result[2][3] = static_cast<T>(-1);
	Result[3][2] = - (static_cast<T>(2) * farVal * nearVal) / (farVal - nearVal);
	return Result;
}

template<typename T>
inline mat<4, 4, T> frustumZO(T left, T right, T bottom, T top, T nearVal, T farVal)
{
	return frustumRH_ZO(left, right, bottom, top, nearVal, farVal);
}

template<typename T>
inline mat<4, 4, T> frustumNO(T left, T right, T bottom, T top, T nearVal, T farVal)
{
	return frustumRH_NO(left, right, bottom, top, nearVal, farVal);
}

template<typename T>
inline mat<4, 4, T> frustumRH(T left, T right, T bottom, T top, T nearVal, T farVal)
{
	return frustumRH_ZO(left, right, bottom, top, nearVal, farVal);
}

template<typename T>
inline mat<4, 4, T> frustum(T left, T right, T bottom, T top, T nearVal, T farVal)
{
	return frustumRH_ZO(left, right, bottom, top, nearVal, farVal);
}

template<typename T>
inline mat<4, 4, T> perspectiveRH_ZO(T fovy, T aspect, T zNear, T zFar)
{
	assert(std::abs(aspect - std::numeric_limits<T>::epsilon()) > static_cast<T>(0));

	T const tanHalfFovy = tan(fovy / static_cast<T>(2));

	mat<4, 4, T> Result(static_cast<T>(0));
	Result[0][0] = static_cast<T>(1) / (aspect * tanHalfFovy);
	Result[1][1] = static_cast<T>(1) / (tanHalfFovy);
	Result[2][2] = zFar / (zNear - zFar);
	Result[2][3] = - static_cast<T>(1);
	Result[3][2] = -(zFar * zNear) / (zFar - zNear);
	return Result;
}

template<typename T>
inline mat<4, 4, T> perspectiveLH_ZO(T fovy, T aspect, T zNear, T zFar)
{
	assert(std::abs(aspect - std::numeric_limits<T>::epsilon()) > static_cast<T>(0));

	T const tanHalfFovy = tan(fovy / static_cast<T>(2));

	mat<4, 4, T> Result(static_cast<T>(0));
	Result[0][0] = static_cast<T>(1) / (aspect * tanHalfFovy);
	Result[1][1] = static_cast<T>(1) / (tanHalfFovy);
	Result[2][2] = zFar / (zFar - zNear);
	Result[2][3] = static_cast<T>(1);
	Result[3][2] = -(zFar * zNear) / (zFar - zNear);
	return Result;
}

template<typename T>
inline mat<4, 4, T> perspectiveZO(T fovy, T aspect, T zNear, T zFar)
{
	return perspectiveRH_ZO(fovy, aspect, zNear, zFar);
}

template<typename T>
inline mat<4, 4, T> perspectiveRH(T fovy, T aspect, T zNear, T zFar)
{
	return perspectiveRH_ZO(fovy, aspect, zNear, zFar);
}

template<typename T>
inline mat<4, 4, T> perspective(T fovy, T aspect, T zNear, T zFar)
{
	return perspectiveRH_ZO(fovy, aspect, zNear, zFar);
}

template<typename T>
inline mat<4, 4, T> perspectiveFovRH_ZO(T fov, T width, T height, T zNear, T zFar)
{
	assert(width > static_cast<T>(0));
	assert(height > static_cast<T>(0));
	assert(fov > static_cast<T>(0));

	T const rad = fov;
	T const h = Kinai::math::cos(static_cast<T>(0.5) * rad) / Kinai::math::sin(static_cast<T>(0.5) * rad);
	T const w = h * height / width; ///todo max(width , Height) / min(width , Height)?

	mat<4, 4, T> Result(static_cast<T>(0));
	Result[0][0] = w;
	Result[1][1] = h;
	Result[2][2] = zFar / (zNear - zFar);
	Result[2][3] = - static_cast<T>(1);
	Result[3][2] = -(zFar * zNear) / (zFar - zNear);
	return Result;
}

template<typename T>
inline mat<4, 4, T> perspectiveFovRH_NO(T fov, T width, T height, T zNear, T zFar)
{
	assert(width > static_cast<T>(0));
	assert(height > static_cast<T>(0));
	assert(fov > static_cast<T>(0));

	T const rad = fov;
	T const h = Kinai::math::cos(static_cast<T>(0.5) * rad) / Kinai::math::sin(static_cast<T>(0.5) * rad);
	T const w = h * height / width; ///todo max(width , Height) / min(width , Height)?

	mat<4, 4, T> Result(static_cast<T>(0));
	Result[0][0] = w;
	Result[1][1] = h;
	Result[2][2] = - (zFar + zNear) / (zFar - zNear);
	Result[2][3] = - static_cast<T>(1);
	Result[3][2] = - (static_cast<T>(2) * zFar * zNear) / (zFar - zNear);
	return Result;
}

template<typename T>
inline mat<4, 4, T> perspectiveFovLH_ZO(T fov, T width, T height, T zNear, T zFar)
{
	assert(width > static_cast<T>(0));
	assert(height > static_cast<T>(0));
	assert(fov > static_cast<T>(0));

	T const rad = fov;
	T const h = Kinai::math::cos(static_cast<T>(0.5) * rad) / Kinai::math::sin(static_cast<T>(0.5) * rad);
	T const w = h * height / width; ///todo max(width , Height) / min(width , Height)?

	mat<4, 4, T> Result(static_cast<T>(0));
	Result[0][0] = w;
	Result[1][1] = h;
	Result[2][2] = zFar / (zFar - zNear);
	Result[2][3] = static_cast<T>(1);
	Result[3][2] = -(zFar * zNear) / (zFar - zNear);
	return Result;
}

template<typename T>
inline mat<4, 4, T> perspectiveFovLH_NO(T fov, T width, T height, T zNear, T zFar)
{
	assert(width > static_cast<T>(0));
	assert(height > static_cast<T>(0));
	assert(fov > static_cast<T>(0));

	T const rad = fov;
	T const h = Kinai::math::cos(static_cast<T>(0.5) * rad) / Kinai::math::sin(static_cast<T>(0.5) * rad);
	T const w = h * height / width; ///todo max(width , Height) / min(width , Height)?

	mat<4, 4, T> Result(static_cast<T>(0));
	Result[0][0] = w;
	Result[1][1] = h;
	Result[2][2] = (zFar + zNear) / (zFar - zNear);
	Result[2][3] = static_cast<T>(1);
	Result[3][2] = - (static_cast<T>(2) * zFar * zNear) / (zFar - zNear);
	return Result;
}

template<typename T>
inline mat<4, 4, T> perspectiveFovZO(T fov, T width, T height, T zNear, T zFar)
{
	return perspectiveFovRH_ZO(fov, width, height, zNear, zFar);
}

template<typename T>
inline mat<4, 4, T> perspectiveFovRH(T fov, T width, T height, T zNear, T zFar)
{
	return perspectiveFovRH_ZO(fov, width, height, zNear, zFar);
}

template<typename T>
inline mat<4, 4, T> perspectiveFov(T fov, T width, T height, T zNear, T zFar)
{
	return perspectiveFovRH_ZO(fov, width, height, zNear, zFar);
}

template<typename T>
inline mat<4, 4, T> infinitePerspectiveRH(T fovy, T aspect, T zNear)
{
	T const range = tan(fovy / static_cast<T>(2)) * zNear;
	T const left = -range * aspect;
	T const right = range * aspect;
	T const bottom = -range;
	T const top = range;

	mat<4, 4, T> Result(static_cast<T>(0));
	Result[0][0] = (static_cast<T>(2) * zNear) / (right - left);
	Result[1][1] = (static_cast<T>(2) * zNear) / (top - bottom);
	Result[2][2] = - static_cast<T>(1);
	Result[2][3] = - static_cast<T>(1);
	Result[3][2] = - static_cast<T>(2) * zNear;
	return Result;
}

template<typename T>
inline mat<4, 4, T> infinitePerspective(T fovy, T aspect, T zNear)
{
	return infinitePerspectiveRH(fovy, aspect, zNear);
}

template<typename T>
inline mat<4, 4, T> tweakedInfinitePerspective(T fovy, T aspect, T zNear, T ep)
{
	T const range = tan(fovy / static_cast<T>(2)) * zNear;
	T const left = -range * aspect;
	T const right = range * aspect;
	T const bottom = -range;
	T const top = range;

	mat<4, 4, T> Result(static_cast<T>(0));
	Result[0][0] = (static_cast<T>(2) * zNear) / (right - left);
	Result[1][1] = (static_cast<T>(2) * zNear) / (top - bottom);
	Result[2][2] = ep - static_cast<T>(1);
	Result[2][3] = static_cast<T>(-1);
	Result[3][2] = (ep - static_cast<T>(2)) * zNear;
	return Result;
}

template<typename T>
inline mat<4, 4, T> tweakedInfinitePerspective(T fovy, T aspect, T zNear)
{
	return tweakedInfinitePerspective(fovy, aspect, zNear, epsilon<T>());
}

} // math

} // Kinai
