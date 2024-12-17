#include "Kinai/Platform/Headless/HeadlessUniformBuffer.hpp"

namespace Kinai
{

HeadlessUniformBuffer::HeadlessUniformBuffer(uint32_t size, uint32_t binding)
{
	KN_NOTUSED(size)
	KN_NOTUSED(binding);
}

HeadlessUniformBuffer::~HeadlessUniformBuffer()
{
}

void	HeadlessUniformBuffer::SetData(const void *data, uint32_t size, uint32_t offset = 0)
{
	KN_NOTUSED(data);
	KN_NOTUSED(size);
	KN_NOTUSED(offset);
}

} // Kinai
