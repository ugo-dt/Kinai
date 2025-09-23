#pragma once

#include "Kinai/Core/Core.hpp"
#include "BufferLayout.hpp"

namespace Kinai
{

class VertexBuffer
{
public:
	virtual ~VertexBuffer() = default;

	virtual void	Bind() const = 0;
	virtual void	Unbind() const = 0;

	virtual void	SetData(const void* data, uint32_t size) = 0;

	#ifdef KN_DEBUG_STATS
		virtual uint32_t GetSize() const = 0;
	#endif

	static Ref<VertexBuffer>	Create(uint32_t size);
	static Ref<VertexBuffer>	Create(const void* vertices, uint32_t size);
};

} // Kinai
