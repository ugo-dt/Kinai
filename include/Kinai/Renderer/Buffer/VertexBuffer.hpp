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
	virtual void	SetLayout(const BufferLayout& layout) = 0;

	virtual const BufferLayout&	GetLayout() const = 0;

	static std::shared_ptr<VertexBuffer>	Create(uint32_t size);
	static std::shared_ptr<VertexBuffer>	Create(const void* vertices, uint32_t size);
};

using VertexBufferRef = std::shared_ptr<VertexBuffer>;

} // Kinai
