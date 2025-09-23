#pragma once

#include "Kinai/Core/Core.hpp"
#include "Kinai/Renderer/RendererAPI.hpp"

namespace Kinai
{

class IndexBuffer
{
public:
	virtual ~IndexBuffer() = default;

	virtual void Bind() const = 0;
	virtual void Unbind() const = 0;

	virtual void SetIndexType(IndexType index_type) = 0;

	virtual uint32_t GetCount() const = 0;
	virtual IndexType GetIndexType() const = 0;

	static Ref<IndexBuffer> Create(const void* indices, uint32_t count, IndexType type);
	static Ref<IndexBuffer> Create(const uint16_t* indices, uint32_t count, IndexType type = IndexType::Uint16);
	static Ref<IndexBuffer> Create(const uint32_t* indices, uint32_t count, IndexType type = IndexType::Uint32);
};

} // Kinai
