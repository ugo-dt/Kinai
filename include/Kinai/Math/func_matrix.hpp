#pragma once

#include "geometric.hpp"
#include "matrix.hpp"
#include <limits>

namespace Kinai
{

namespace math
{

template<length_t C, length_t R, typename T>
struct compute_matrixCompMult
{
	static mat<C, R, T> call(mat<C, R, T> const& x, mat<C, R, T> const& y)
	{
		mat<C, R, T> Result(1);
		for(length_t i = 0; i < Result.length(); ++i)
			Result[i] = x[i] * y[i];
		return Result;
	}
};

template<length_t C, length_t R, typename T, bool IsFloat>
struct compute_matrixCompMult_type {
	static mat<C, R, T> call(mat<C, R, T> const& x, mat<C, R, T> const& y)
	{
		static_assert(std::numeric_limits<T>::is_iec559, 
			"'matrixCompMult' only accept floating-point inputs");
		return compute_matrixCompMult<C, R, T>::call(x, y);
	}
};

template<length_t DA, length_t DB, typename T>
struct compute_outerProduct {
	static typename outerProduct_trait<DA, DB, T>::type call(vec<DA, T> const& c, vec<DB, T> const& r)
	{
		typename outerProduct_trait<DA, DB, T>::type m(0);
		for(length_t i = 0; i < m.length(); ++i)
			m[i] = c * r[i];
		return m;
	}
};

template<length_t DA, length_t DB, typename T, bool IsFloat>
struct compute_outerProduct_type {
	static typename outerProduct_trait<DA, DB, T>::type call(vec<DA, T> const& c, vec<DB, T> const& r)
	{
		static_assert(std::numeric_limits<T>::is_iec559,
			"'outerProduct' only accept floating-point inputs");

		return compute_outerProduct<DA, DB, T>::call(c, r);
	}
};

template<length_t C, length_t R, typename T>
struct compute_transpose{};

template<typename T>
struct compute_transpose<2, 2, T>
{
	static mat<2, 2, T> call(mat<2, 2, T> const& m)
	{
		mat<2, 2, T> Result(1);
		Result[0][0] = m[0][0];
		Result[0][1] = m[1][0];
		Result[1][0] = m[0][1];
		Result[1][1] = m[1][1];
		return Result;
	}
};

template<typename T>
struct compute_transpose<2, 3, T>
{
	static mat<3, 2, T> call(mat<2, 3, T> const& m)
	{
		mat<3,2, T> Result(1);
		Result[0][0] = m[0][0];
		Result[0][1] = m[1][0];
		Result[1][0] = m[0][1];
		Result[1][1] = m[1][1];
		Result[2][0] = m[0][2];
		Result[2][1] = m[1][2];
		return Result;
	}
};

template<typename T>
struct compute_transpose<2, 4, T>
{
	static mat<4, 2, T> call(mat<2, 4, T> const& m)
	{
		mat<4, 2, T> Result(1);
		Result[0][0] = m[0][0];
		Result[0][1] = m[1][0];
		Result[1][0] = m[0][1];
		Result[1][1] = m[1][1];
		Result[2][0] = m[0][2];
		Result[2][1] = m[1][2];
		Result[3][0] = m[0][3];
		Result[3][1] = m[1][3];
		return Result;
	}
};

template<typename T>
struct compute_transpose<3, 2, T>
{
	static mat<2, 3, T> call(mat<3, 2, T> const& m)
	{
		mat<2, 3, T> Result(1);
		Result[0][0] = m[0][0];
		Result[0][1] = m[1][0];
		Result[0][2] = m[2][0];
		Result[1][0] = m[0][1];
		Result[1][1] = m[1][1];
		Result[1][2] = m[2][1];
		return Result;
	}
};

template<typename T>
struct compute_transpose<3, 3, T>
{
	static mat<3, 3, T> call(mat<3, 3, T> const& m)
	{
		mat<3, 3, T> Result(1);
		Result[0][0] = m[0][0];
		Result[0][1] = m[1][0];
		Result[0][2] = m[2][0];

		Result[1][0] = m[0][1];
		Result[1][1] = m[1][1];
		Result[1][2] = m[2][1];

		Result[2][0] = m[0][2];
		Result[2][1] = m[1][2];
		Result[2][2] = m[2][2];
		return Result;
	}
};

template<typename T>
struct compute_transpose<3, 4, T>
{
	static mat<4, 3, T> call(mat<3, 4, T> const& m)
	{
		mat<4, 3, T> Result(1);
		Result[0][0] = m[0][0];
		Result[0][1] = m[1][0];
		Result[0][2] = m[2][0];
		Result[1][0] = m[0][1];
		Result[1][1] = m[1][1];
		Result[1][2] = m[2][1];
		Result[2][0] = m[0][2];
		Result[2][1] = m[1][2];
		Result[2][2] = m[2][2];
		Result[3][0] = m[0][3];
		Result[3][1] = m[1][3];
		Result[3][2] = m[2][3];
		return Result;
	}
};

template<typename T>
struct compute_transpose<4, 2, T>
{
	static mat<2, 4, T> call(mat<4, 2, T> const& m)
	{
		mat<2, 4, T> Result(1);
		Result[0][0] = m[0][0];
		Result[0][1] = m[1][0];
		Result[0][2] = m[2][0];
		Result[0][3] = m[3][0];
		Result[1][0] = m[0][1];
		Result[1][1] = m[1][1];
		Result[1][2] = m[2][1];
		Result[1][3] = m[3][1];
		return Result;
	}
};

template<typename T>
struct compute_transpose<4, 3, T>
{
	static mat<3, 4, T> call(mat<4, 3, T> const& m)
	{
		mat<3, 4, T> Result(1);
		Result[0][0] = m[0][0];
		Result[0][1] = m[1][0];
		Result[0][2] = m[2][0];
		Result[0][3] = m[3][0];
		Result[1][0] = m[0][1];
		Result[1][1] = m[1][1];
		Result[1][2] = m[2][1];
		Result[1][3] = m[3][1];
		Result[2][0] = m[0][2];
		Result[2][1] = m[1][2];
		Result[2][2] = m[2][2];
		Result[2][3] = m[3][2];
		return Result;
	}
};

template<typename T>
struct compute_transpose<4, 4, T>
{
	static mat<4, 4, T> call(mat<4, 4, T> const& m)
	{
		mat<4, 4, T> Result(1);
		Result[0][0] = m[0][0];
		Result[0][1] = m[1][0];
		Result[0][2] = m[2][0];
		Result[0][3] = m[3][0];

		Result[1][0] = m[0][1];
		Result[1][1] = m[1][1];
		Result[1][2] = m[2][1];
		Result[1][3] = m[3][1];

		Result[2][0] = m[0][2];
		Result[2][1] = m[1][2];
		Result[2][2] = m[2][2];
		Result[2][3] = m[3][2];

		Result[3][0] = m[0][3];
		Result[3][1] = m[1][3];
		Result[3][2] = m[2][3];
		Result[3][3] = m[3][3];
		return Result;
	}
};

template<length_t C, length_t R, typename T, bool IsFloat>
struct compute_transpose_type {
	static mat<R, C, T> call(mat<C, R, T> const& m)
	{
		static_assert(std::numeric_limits<T>::is_iec559, 
			"'transpose' only accept floating-point inputs");
		return compute_transpose<C, R, T>::call(m);
	}
};

template<length_t C, length_t R, typename T>
struct compute_determinant{};

template<typename T>
struct compute_determinant<2, 2, T>
{
	static T call(mat<2, 2, T> const& m)
	{
		return m[0][0] * m[1][1] - m[1][0] * m[0][1];
	}
};

template<typename T>
struct compute_determinant<3, 3, T>
{
	static T call(mat<3, 3, T> const& m)
	{
		return
			+ m[0][0] * (m[1][1] * m[2][2] - m[2][1] * m[1][2])
			- m[1][0] * (m[0][1] * m[2][2] - m[2][1] * m[0][2])
			+ m[2][0] * (m[0][1] * m[1][2] - m[1][1] * m[0][2]);
	}
};

template<typename T>
struct compute_determinant<4, 4, T>
{
	static T call(mat<4, 4, T> const& m)
	{
		T SubFactor00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
		T SubFactor01 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
		T SubFactor02 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
		T SubFactor03 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
		T SubFactor04 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
		T SubFactor05 = m[2][0] * m[3][1] - m[3][0] * m[2][1];

		vec<4, T> DetCof(
			+ (m[1][1] * SubFactor00 - m[1][2] * SubFactor01 + m[1][3] * SubFactor02),
			- (m[1][0] * SubFactor00 - m[1][2] * SubFactor03 + m[1][3] * SubFactor04),
			+ (m[1][0] * SubFactor01 - m[1][1] * SubFactor03 + m[1][3] * SubFactor05),
			- (m[1][0] * SubFactor02 - m[1][1] * SubFactor04 + m[1][2] * SubFactor05));

		return
			m[0][0] * DetCof[0] + m[0][1] * DetCof[1] +
			m[0][2] * DetCof[2] + m[0][3] * DetCof[3];
	}
};

template<length_t C, length_t R, typename T, bool IsFloat>
struct compute_determinant_type{

	static T call(mat<C, R, T> const& m)
	{
		static_assert(std::numeric_limits<T>::is_iec559, 
			"'determinant' only accept floating-point inputs");
		return compute_determinant<C, R, T>::call(m);
	}
};

template<length_t C, length_t R, typename T>
struct compute_inverse{};

template<typename T>
struct compute_inverse<2, 2, T>
{
	static mat<2, 2, T> call(mat<2, 2, T> const& m)
	{
		T OneOverDeterminant = static_cast<T>(1) / (
			+ m[0][0] * m[1][1]
			- m[1][0] * m[0][1]);

		mat<2, 2, T> Inverse(
			+ m[1][1] * OneOverDeterminant,
			- m[0][1] * OneOverDeterminant,
			- m[1][0] * OneOverDeterminant,
			+ m[0][0] * OneOverDeterminant);

		return Inverse;
	}
};

// template<typename T>
// struct inv3x3 {};

template<typename T>
struct inv3x3
{
	static mat<3, 3, T> call(mat<3, 3, T> const& m)
	{
		// see: https://www.onlinemathstutor.org/post/3x3_inverses

		vec<4, T> a = xyz0(m[0]);
		vec<4, T> b = xyz0(m[1]);
		vec<4, T> c = xyz0(m[2]);

		vec<4, T> i0 = compute_cross<T>::call(b, c);
		vec<4, T> i1 = compute_cross<T>::call(c, a);
		vec<4, T> i2 = compute_cross<T>::call(a, b);

		mat<3, 3, T> Inverse;
		Inverse[0] = xyz(i0);
		Inverse[1] = xyz(i1);
		Inverse[2] = xyz(i2);
		Inverse = transpose(Inverse);

		T Determinant = compute_dot<vec<4, T>, T>::call(a, compute_cross<T>::call(b, c));
		vec<3, T> OneOverDeterminant(static_cast<T>(1) / Determinant);
		Inverse *= OneOverDeterminant;
		return Inverse;
	}
};

template<typename T>
struct compute_inverse<3, 3, T>
{
	static mat<3, 3, T> call(mat<3, 3, T> const& m)
	{
		return inv3x3<T>::call(m);
	}
};

template<typename T>
struct compute_inverse<4, 4, T>
{
	static mat<4, 4, T> call(mat<4, 4, T> const& m)
	{
		T Coef00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
		T Coef02 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
		T Coef03 = m[1][2] * m[2][3] - m[2][2] * m[1][3];

		T Coef04 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
		T Coef06 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
		T Coef07 = m[1][1] * m[2][3] - m[2][1] * m[1][3];

		T Coef08 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
		T Coef10 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
		T Coef11 = m[1][1] * m[2][2] - m[2][1] * m[1][2];

		T Coef12 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
		T Coef14 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
		T Coef15 = m[1][0] * m[2][3] - m[2][0] * m[1][3];

		T Coef16 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
		T Coef18 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
		T Coef19 = m[1][0] * m[2][2] - m[2][0] * m[1][2];

		T Coef20 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
		T Coef22 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
		T Coef23 = m[1][0] * m[2][1] - m[2][0] * m[1][1];

		vec<4, T> Fac0(Coef00, Coef00, Coef02, Coef03);
		vec<4, T> Fac1(Coef04, Coef04, Coef06, Coef07);
		vec<4, T> Fac2(Coef08, Coef08, Coef10, Coef11);
		vec<4, T> Fac3(Coef12, Coef12, Coef14, Coef15);
		vec<4, T> Fac4(Coef16, Coef16, Coef18, Coef19);
		vec<4, T> Fac5(Coef20, Coef20, Coef22, Coef23);

		vec<4, T> Vec0(m[1][0], m[0][0], m[0][0], m[0][0]);
		vec<4, T> Vec1(m[1][1], m[0][1], m[0][1], m[0][1]);
		vec<4, T> Vec2(m[1][2], m[0][2], m[0][2], m[0][2]);
		vec<4, T> Vec3(m[1][3], m[0][3], m[0][3], m[0][3]);

		vec<4, T> Inv0(Vec1 * Fac0 - Vec2 * Fac1 + Vec3 * Fac2);
		vec<4, T> Inv1(Vec0 * Fac0 - Vec2 * Fac3 + Vec3 * Fac4);
		vec<4, T> Inv2(Vec0 * Fac1 - Vec1 * Fac3 + Vec3 * Fac5);
		vec<4, T> Inv3(Vec0 * Fac2 - Vec1 * Fac4 + Vec2 * Fac5);

		vec<4, T> SignA(+1, -1, +1, -1);
		vec<4, T> SignB(-1, +1, -1, +1);
		mat<4, 4, T> Inverse(Inv0 * SignA, Inv1 * SignB, Inv2 * SignA, Inv3 * SignB);

		vec<4, T> Row0(Inverse[0][0], Inverse[1][0], Inverse[2][0], Inverse[3][0]);

		vec<4, T> Dot0(m[0] * Row0);
		T Dot1 = (Dot0.x + Dot0.y) + (Dot0.z + Dot0.w);

		T OneOverDeterminant = static_cast<T>(1) / Dot1;

		return Inverse * OneOverDeterminant;
	}
};

template<length_t C, length_t R, typename T>
mat<C, R, T> matrixCompMult(mat<C, R, T> const& x, mat<C, R, T> const& y)
{
	return compute_matrixCompMult_type<C, R, T, std::numeric_limits<T>::is_iec559>::call(x, y);
}

template<length_t DA, length_t DB, typename T>
typename outerProduct_trait<DA, DB, T>::type outerProduct(vec<DA, T> const& c, vec<DB, T> const& r)
{
	return compute_outerProduct_type<DA, DB, T, std::numeric_limits<T>::is_iec559>::call(c, r);
}

template<length_t C, length_t R, typename T>
typename mat<C, R, T>::transpose_type transpose(mat<C, R, T> const& m)
{
	return compute_transpose_type<C, R, T, std::numeric_limits<T>::is_iec559>::call(m);
}

template<length_t C, length_t R, typename T>
T determinant(mat<C, R, T> const& m)
{
	return compute_determinant_type<C, R, T, std::numeric_limits<T>::is_iec559>::call(m);
}

template<length_t C, length_t R, typename T>
mat<C, R, T> inverse(mat<C, R, T> const& m)
{
	static_assert(std::numeric_limits<T>::is_iec559, "'inverse' only accept floating-point inputs");
	return compute_inverse<C, R, T>::call(m);
}

} //namespace math

} //namespace Kinai
