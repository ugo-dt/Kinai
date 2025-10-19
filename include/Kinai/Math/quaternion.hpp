#pragma once

#include "type/vec3.hpp"
#include "type/quat.hpp"

namespace Kinai
{

namespace math
{

template<typename T>
inline vec<3, T> rotate(qua<T> const& q, vec<3, T> const& v)
{
	return q * v;
}

template<typename T>
inline vec<4, T> rotate(qua<T> const& q, vec<4, T> const& v)
{
	return q * v;
}

template<typename T>
inline mat<3, 3, T> mat3_cast(qua<T> const& q)
{
	mat<3, 3, T> Result(T(1));
	T qxx(q.x * q.x);
	T qyy(q.y * q.y);
	T qzz(q.z * q.z);
	T qxz(q.x * q.z);
	T qxy(q.x * q.y);
	T qyz(q.y * q.z);
	T qwx(q.w * q.x);
	T qwy(q.w * q.y);
	T qwz(q.w * q.z);

	Result[0][0] = T(1) - T(2) * (qyy +  qzz);
	Result[0][1] = T(2) * (qxy + qwz);
	Result[0][2] = T(2) * (qxz - qwy);

	Result[1][0] = T(2) * (qxy - qwz);
	Result[1][1] = T(1) - T(2) * (qxx +  qzz);
	Result[1][2] = T(2) * (qyz + qwx);

	Result[2][0] = T(2) * (qxz + qwy);
	Result[2][1] = T(2) * (qyz - qwx);
	Result[2][2] = T(1) - T(2) * (qxx +  qyy);
	return Result;
}

template<typename T>
inline mat<4, 4, T> mat4_cast(qua<T> const& q)
{
	return mat<4, 4, T>(mat3_cast(q));
}

template<typename T>
inline qua<T> quat_cast(mat<3, 3, T> const& m)
{
	T fourXSquaredMinus1 = m[0][0] - m[1][1] - m[2][2];
	T fourYSquaredMinus1 = m[1][1] - m[0][0] - m[2][2];
	T fourZSquaredMinus1 = m[2][2] - m[0][0] - m[1][1];
	T fourWSquaredMinus1 = m[0][0] + m[1][1] + m[2][2];

	int biggestIndex = 0;
	T fourBiggestSquaredMinus1 = fourWSquaredMinus1;
	if(fourXSquaredMinus1 > fourBiggestSquaredMinus1)
	{
		fourBiggestSquaredMinus1 = fourXSquaredMinus1;
		biggestIndex = 1;
	}
	if(fourYSquaredMinus1 > fourBiggestSquaredMinus1)
	{
		fourBiggestSquaredMinus1 = fourYSquaredMinus1;
		biggestIndex = 2;
	}
	if(fourZSquaredMinus1 > fourBiggestSquaredMinus1)
	{
		fourBiggestSquaredMinus1 = fourZSquaredMinus1;
		biggestIndex = 3;
	}

	T biggestVal = sqrt(fourBiggestSquaredMinus1 + static_cast<T>(1)) * static_cast<T>(0.5);
	T mult = static_cast<T>(0.25) / biggestVal;

	switch(biggestIndex)
	{
	case 0:
		return qua<T>::wxyz(biggestVal, (m[1][2] - m[2][1]) * mult, (m[2][0] - m[0][2]) * mult, (m[0][1] - m[1][0]) * mult);
	case 1:
		return qua<T>::wxyz((m[1][2] - m[2][1]) * mult, biggestVal, (m[0][1] + m[1][0]) * mult, (m[2][0] + m[0][2]) * mult);
	case 2:
		return qua<T>::wxyz((m[2][0] - m[0][2]) * mult, (m[0][1] + m[1][0]) * mult, biggestVal, (m[1][2] + m[2][1]) * mult);
	case 3:
		return qua<T>::wxyz((m[0][1] - m[1][0]) * mult, (m[2][0] + m[0][2]) * mult, (m[1][2] + m[2][1]) * mult, biggestVal);
	default: // Silence a -Wswitch-default warning in GCC. Should never actually get here. Assert is just for sanity.
		assert(false);
		return qua<T>::wxyz(1, 0, 0, 0);
	}
}

template<typename T>
inline mat<3, 3, T> toMat3(qua<T> const& x)
{
	return mat3_cast(x);
}

template<typename T>
inline mat<4, 4, T> toMat4(qua<T> const& x)
{
	return mat4_cast(x);
}

template<typename T>
inline qua<T> toQuat(mat<3, 3, T> const& x)
{
	return quat_cast(x);
}

template<typename T>
inline qua<T> toQuat(mat<4, 4, T> const& x)
{
	return quat_cast(x);
}

} // math


} // Kinai
