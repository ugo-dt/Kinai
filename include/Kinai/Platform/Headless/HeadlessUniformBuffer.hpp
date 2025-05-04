#pragma once

#include "Kinai/Renderer/UniformBuffer.hpp"

namespace Kinai
{

class HeadlessUniformBuffer : public UniformBuffer
{
public:
	HeadlessUniformBuffer(uint32_t size, uint32_t binding);
	~HeadlessUniformBuffer();

	void	SetData(const void *data, uint32_t size, uint32_t offset = 0) override;

private:
	// uint32_t	_renderer_id = 0;
};

} // Kinai
