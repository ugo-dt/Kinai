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

	void Bind() const override;
	void Unbind() const override;
	
	void SetData(const void* data, uint32_t size) override;

	#ifdef KN_DEBUG_STATS
		uint32_t GetSize() const override { return _size; }
	#endif

private:
	#ifdef KN_DEBUG_STATS
		uint32_t _size;
	#endif
};

class HeadlessIndexBuffer : public IndexBuffer
{
public:
	HeadlessIndexBuffer(const void* indices, uint32_t count, IndexType type);
	~HeadlessIndexBuffer();

	void Bind() const override;
	void Unbind() const override;

	void SetIndexType(IndexType index_type) override { _index_type = index_type; }

	uint32_t GetCount() const override { return _count; }
	IndexType GetIndexType() const override { return _index_type; }

private:
	uint32_t _count;
	IndexType _index_type;
};

} // Kinai
