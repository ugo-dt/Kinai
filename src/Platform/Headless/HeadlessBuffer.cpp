#include "Kinai/Platform/Headless/HeadlessBuffer.hpp"

namespace Kinai
{

HeadlessVertexBuffer::HeadlessVertexBuffer(uint32_t size)
{
	KN_PRINT_FUNC();
	
	(void)size;
}

HeadlessVertexBuffer::HeadlessVertexBuffer(float* vertices, uint32_t size)
{
	KN_PRINT_FUNC();
	
	(void)vertices;
	(void)size;
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
	(void)data;
	(void)size;
}

/** Index buffer */

HeadlessIndexBuffer::HeadlessIndexBuffer(const uint32_t* indices, uint32_t count)
	: _count(count)
{
	KN_PRINT_FUNC();
	
	(void)indices;
	(void)count;
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
