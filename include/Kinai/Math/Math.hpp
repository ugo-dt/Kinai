#pragma once

# include "type/vec1.hpp"
# include "type/vec2.hpp"
# include "type/vec3.hpp"
# include "type/vec4.hpp"
# include "type/mat3x3.hpp"
# include "type/mat4x4.hpp"
# include "type/quat.hpp"

# include "matrix.hpp"
# include "func_matrix.hpp"
# include "matrix_clip_space.hpp"
# include "matrix_transform.hpp"

# include "trigonometric.hpp"

# include "rotate_vector.hpp"
# include "vector_angle.hpp"

#include "quaternion.hpp"

namespace Kinai
{

namespace math
{

typedef std::int8_t			int8;
typedef std::int16_t		int16;
typedef std::int32_t		int32;
typedef std::int64_t		int64;

typedef std::uint8_t		uint8;
typedef std::uint16_t		uint16;
typedef std::uint32_t		uint32;
typedef std::uint64_t		uint64;

typedef int8				i8;
typedef int8				int8_t;
typedef int16				i16;
typedef int16				int16_t;
typedef int32				i32;
typedef int32				int32_t;
typedef int64				i64;
typedef int64				int64_t;

typedef unsigned int		uint;

typedef uint8				u8;
typedef uint8				uint8_t;

typedef uint16				u16;
typedef uint16				uint16_t;

typedef uint32				u32;
typedef uint32				uint32_t;

typedef uint64				u64;
typedef uint64				uint64_t;

typedef float				f32;
typedef float				float32;
typedef float				float32_t;
typedef double				f64;
typedef double				float64;
typedef double				float64_t;

typedef vec<1, bool>		bvec1;
typedef vec<1, float>		vec1;
typedef vec<1, double>		dvec1;
typedef vec<1, int>			ivec1;
typedef vec<1, int8_t>		i8vec1;
typedef vec<1, int16_t>		i16vec1;
typedef vec<1, int32_t>		i32vec1;
typedef vec<1, int64_t>		i64vec1;
typedef vec<1, uint_t>		uvec1;
typedef vec<1, uint8_t>		u8vec1;
typedef vec<1, uint16_t>	u16vec1;
typedef vec<1, uint32_t>	u32vec1;
typedef vec<1, uint64_t>	u64vec1;

typedef vec<2, bool>		bvec2;
typedef vec<2, float>		vec2;
typedef vec<2, double>		dvec2;
typedef vec<2, int>			ivec2;
typedef vec<2, int8_t>		i8vec2;
typedef vec<2, int16_t>		i16vec2;
typedef vec<2, int32_t>		i32vec2;
typedef vec<2, int64_t>		i64vec2;
typedef vec<2, uint_t>		uvec2;
typedef vec<2, uint8_t>		u8vec2;
typedef vec<2, uint16_t>	u16vec2;
typedef vec<2, uint32_t>	u32vec2;
typedef vec<2, uint64_t>	u64vec2;

typedef vec<3, bool>		bvec3;
typedef vec<3, float>		vec3;
typedef vec<3, double>		dvec3;
typedef vec<3, int>			ivec3;
typedef vec<3, int8_t>		i8vec3;
typedef vec<3, int16_t>		i16vec3;
typedef vec<3, int32_t>		i32vec3;
typedef vec<3, int64_t>		i64vec3;
typedef vec<3, uint_t>		uvec3;
typedef vec<3, uint8_t>		u8vec3;
typedef vec<3, uint16_t>	u16vec3;
typedef vec<3, uint32_t>	u32vec3;
typedef vec<3, uint64_t>	u64vec3;

typedef vec<4, bool>		bvec4;
typedef vec<4, float>		vec4;
typedef vec<4, double>		dvec4;
typedef vec<4, int>			ivec4;
typedef vec<4, int8_t>		i8vec4;
typedef vec<4, int16_t>		i16vec4;
typedef vec<4, int32_t>		i32vec4;
typedef vec<4, int64_t>		i64vec4;
typedef vec<4, uint_t>		uvec4;
typedef vec<4, uint8_t>		u8vec4;
typedef vec<4, uint16_t>	u16vec4;
typedef vec<4, uint32_t>	u32vec4;
typedef vec<4, uint64_t>	u64vec4;

typedef mat<3, 3, float>	mat3x3;
typedef mat<3, 3, float>	mat3;
typedef mat<3, 3, double>	dmat3x3;
typedef mat<3, 3, double>	dmat3;

typedef mat<4, 4, float>	mat4x4;
typedef mat<4, 4, float>	mat4;
typedef mat<4, 4, double>	dmat4x4;
typedef mat<4, 4, double>	dmat4;

typedef qua<float> quat;

} // math

} // Kinai
