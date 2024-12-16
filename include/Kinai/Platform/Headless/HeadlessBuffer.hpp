#pragma once

#include "Kinai/Core/Core.hpp"
#include "Kinai/Renderer/Buffer/Buffer.hpp"

namespace Kinai
{

class HeadlessVertexBuffer : public VertexBuffer
{
public:
	HeadlessVertexBuffer(uint32_t size);
	HeadlessVertexBuffer(const void* vertices, uint32_t size);
	~HeadlessVertexBuffer();

	void	Bind() const override;
	void	Unbind() const override;
	
	void	SetData(const void* data, uint32_t size) override;

	void	SetLayout(const BufferLayout& layout) override { _layout = layout; }
	const	BufferLayout& GetLayout() const override { return _layout; }

private:
	BufferLayout	_layout;
};

class HeadlessIndexBuffer : public IndexBuffer
{
public:
	HeadlessIndexBuffer(const uint32_t* indices, uint32_t count);
	~HeadlessIndexBuffer();

	void	Bind() const override;
	void	Unbind() const override;

	uint32_t	GetCount() const override { return _count; }

private:
	uint32_t	_count;
};

} // Kinai
