#include "Kinai/Platform/Headless/HeadlessBuffer.hpp"

namespace Kinai
{

HeadlessVertexBuffer::HeadlessVertexBuffer(uint32_t size)
{
	EG_PRINT_FUNC();
	
	(void)size;
}

HeadlessVertexBuffer::HeadlessVertexBuffer(float* vertices, uint32_t size)
{
	EG_PRINT_FUNC();
	
	(void)vertices;
	(void)size;
}

HeadlessVertexBuffer::~HeadlessVertexBuffer()
{
	EG_PRINT_FUNC();
}

void	HeadlessVertexBuffer::Bind() const
{
	EG_PRINT_FUNC();
}

void	HeadlessVertexBuffer::Unbind() const
{
	EG_PRINT_FUNC();
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
	EG_PRINT_FUNC();
	
	(void)indices;
	(void)count;
}

HeadlessIndexBuffer::~HeadlessIndexBuffer()
{
	EG_PRINT_FUNC();
}

void	HeadlessIndexBuffer::Bind() const
{
	EG_PRINT_FUNC();
}

void	HeadlessIndexBuffer::Unbind() const
{
	EG_PRINT_FUNC();
}

} // Kinai
