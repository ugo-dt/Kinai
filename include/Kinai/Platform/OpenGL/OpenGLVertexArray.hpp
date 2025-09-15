#pragma once

#include "Kinai/Renderer/VertexArray.hpp"

namespace Kinai
{

class OpenGLVertexArray : public VertexArray
{
public:
	OpenGLVertexArray();
	~OpenGLVertexArray();

	void	Bind() const override;
	void	Unbind() const override;

private:
	uint32_t _renderer_id;
};

} // Kinai
