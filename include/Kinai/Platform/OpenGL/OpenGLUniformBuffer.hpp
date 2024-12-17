#pragma once

#include "Kinai/Renderer/UniformBuffer.hpp"

namespace Kinai
{

class OpenGLUniformBuffer : public UniformBuffer
{
public:
	OpenGLUniformBuffer(uint32_t size, uint32_t binding);
	~OpenGLUniformBuffer();

	void	SetData(const void *data, uint32_t size, uint32_t offset) override;

private:
	uint32_t	_renderer_id = 0;
};

} // Kinai
