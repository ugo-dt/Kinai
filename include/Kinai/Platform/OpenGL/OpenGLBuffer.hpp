#pragma once

#include "Kinai/Core/Core.hpp"
#include "Kinai/Renderer/Buffer/Buffer.hpp"

namespace Kinai
{

class OpenGLVertexBuffer : public VertexBuffer
{
public:
	OpenGLVertexBuffer(uint32_t size);
	OpenGLVertexBuffer(const void* vertices, uint32_t size);
	~OpenGLVertexBuffer();

	void Bind() const override;
	void Unbind() const override;
	
	void SetData(const void* data, uint32_t size) override;

private:
	uint32_t _renderer_id;
};

class OpenGLIndexBuffer : public IndexBuffer
{
public:
	OpenGLIndexBuffer(const uint32_t* indices, uint32_t count);
	~OpenGLIndexBuffer();

	void Bind() const override;
	void Unbind() const override;

	uint32_t GetCount() const override { return _count; }

private:
	uint32_t _renderer_id;
	uint32_t _count;
};

} // Kinai
