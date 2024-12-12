#pragma once

#include "Kinai/Core/Core.hpp"

namespace Kinai
{

enum class ShaderDataType
{
	None = 0,
	Float, Float2, Float3, Float4,
	Mat3, Mat4,
	Int, Int2, Int3, Int4,
	Bool,
	UByte, UByte2, UByte3, UByte4,
	UInt, UInt2, UInt3, UInt4,
};

static inline uint32_t	ShaderDataTypeSize(ShaderDataType type)
{
	switch (type)
	{
		case ShaderDataType::None:		break;
		case ShaderDataType::Float:		return sizeof(float) * 1;
		case ShaderDataType::Float2:	return sizeof(float) * 2;
		case ShaderDataType::Float3:	return sizeof(float) * 3;
		case ShaderDataType::Float4:	return sizeof(float) * 4;
		case ShaderDataType::Mat3:		return sizeof(float) * 3 * 3;
		case ShaderDataType::Mat4:		return sizeof(float) * 4 * 4;
		case ShaderDataType::Int:		return sizeof(int) * 1;
		case ShaderDataType::Int2:		return sizeof(int) * 2;
		case ShaderDataType::Int3:		return sizeof(int) * 3;
		case ShaderDataType::Int4:		return sizeof(int) * 4;
		case ShaderDataType::Bool:		return sizeof(bool);
		case ShaderDataType::UByte:		return sizeof(unsigned char) * 1;
		case ShaderDataType::UByte2:	return sizeof(unsigned char) * 2;
		case ShaderDataType::UByte3:	return sizeof(unsigned char) * 3;
		case ShaderDataType::UByte4:	return sizeof(unsigned char) * 4;
		case ShaderDataType::UInt:		return sizeof(unsigned int) * 1;
		case ShaderDataType::UInt2:		return sizeof(unsigned int) * 2;
		case ShaderDataType::UInt3:		return sizeof(unsigned int) * 3;
		case ShaderDataType::UInt4:		return sizeof(unsigned int) * 4;
	}

	KN_ASSERT(false, "Unknown ShaderDataType");
	return 0;
}

struct BufferElement
{
	std::string		name;
	ShaderDataType	type;
	uint32_t		size;
	size_t			offset;
	bool			normalized;

	BufferElement() = default;
	BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
		: name(name), type(type), size(ShaderDataTypeSize(type)), offset(0), normalized(normalized)
	{
	}

	uint32_t GetComponentCount() const
	{
		switch (type)
		{
			case ShaderDataType::None:		break;
			case ShaderDataType::Float:		return 1;
			case ShaderDataType::Float2:	return 2;
			case ShaderDataType::Float3:	return 3;
			case ShaderDataType::Float4:	return 4;
			case ShaderDataType::Mat3:		return 3; // 3 * float3
			case ShaderDataType::Mat4:		return 4; // 4 * float4
			case ShaderDataType::Int:		return 1;
			case ShaderDataType::Int2:		return 2;
			case ShaderDataType::Int3:		return 3;
			case ShaderDataType::Int4:		return 4;
			case ShaderDataType::Bool:		return 1;
			case ShaderDataType::UByte:		return 1;
			case ShaderDataType::UByte2:	return 2;
			case ShaderDataType::UByte3:	return 3;
			case ShaderDataType::UByte4:	return 4;
			case ShaderDataType::UInt:		return 1;
			case ShaderDataType::UInt2:		return 2;
			case ShaderDataType::UInt3:		return 3;
			case ShaderDataType::UInt4:		return 4;
		}

		KN_ASSERT(false && "Unknown ShaderDataType");
		return 0;
	}
};

} // Kinai
