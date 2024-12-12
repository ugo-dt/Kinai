#pragma once

#include "Kinai/Core/Core.hpp"

namespace Kinai
{

// sg_buffer_desc
struct SokolBufferDesc
{
	uint32_t _start_canary = {};
	size_t size = {};
	sg_buffer_type type = {};
	sg_usage usage = {};
	sg_range data = {};
	const char* label = {};
	// optionally inject backend-specific resources
	uint32_t gl_buffers[SG_NUM_INFLIGHT_FRAMES] = {};
	const void* mtl_buffers[SG_NUM_INFLIGHT_FRAMES] = {};
	const void* d3d11_buffer = {};
	const void* wgpu_buffer = {};
	uint32_t _end_canary = {};

	operator sg_buffer_desc() { return sg_query_buffer_defaults((sg_buffer_desc *)this); }
};

// sg_bindings
struct SokolBindings
{
	uint32_t _start_canary = {};
	sg_buffer vertex_buffers[SG_MAX_VERTEXBUFFER_BINDSLOTS] = {};
	int vertex_buffer_offsets[SG_MAX_VERTEXBUFFER_BINDSLOTS] = {};
	sg_buffer index_buffer = {};
	int index_buffer_offset = {};
	sg_image images[SG_MAX_IMAGE_BINDSLOTS] = {};
	sg_sampler samplers[SG_MAX_SAMPLER_BINDSLOTS] = {};
	sg_buffer storage_buffers[SG_MAX_STORAGEBUFFER_BINDSLOTS] = {};
	uint32_t _end_canary = {};
	
	operator sg_bindings() {
		sg_bindings bnd = {};
		memcpy(&bnd, this, sizeof(bnd));
		return bnd;
	}
};

} // Kinai
