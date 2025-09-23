#include "Kinai/Platform/Headless/HeadlessBuffer.hpp"

namespace Kinai
{

HeadlessVertexBuffer::HeadlessVertexBuffer(uint32_t size)
{
	KN_PRINT_FUNC();
	
	KN_NOTUSED(size);
}

HeadlessVertexBuffer::HeadlessVertexBuffer(const void* vertices, uint32_t size)
{
	KN_PRINT_FUNC();
	
	KN_NOTUSED(vertices);
	KN_NOTUSED(size);
}

HeadlessVertexBuffer::~HeadlessVertexBuffer()
{
	KN_PRINT_FUNC();
}

void	HeadlessVertexBuffer::Bind() const
{
	KN_PRINT_FUNC();
}

void	HeadlessVertexBuffer::Unbind() const
{
	KN_PRINT_FUNC();
}

void	HeadlessVertexBuffer::SetData(const void* data, uint32_t size)
{
	KN_NOTUSED(data);
	KN_NOTUSED(size);
}

/** Index buffer */

HeadlessIndexBuffer::HeadlessIndexBuffer(const void* indices, uint32_t count)
	: _count(count)
{
	KN_PRINT_FUNC();
	
	KN_NOTUSED(indices);
}

HeadlessIndexBuffer::~HeadlessIndexBuffer()
{
	KN_PRINT_FUNC();
}

void	HeadlessIndexBuffer::Bind() const
{
	KN_PRINT_FUNC();
}

void	HeadlessIndexBuffer::Unbind() const
{
	KN_PRINT_FUNC();
}

} // Kinai
