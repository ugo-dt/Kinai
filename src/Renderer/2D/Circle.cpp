#include "Kinai/Renderer/2D/Renderer2D.hpp"

namespace Kinai
{

// void	Renderer2D::DrawCircle(const glm::mat4& transform, const glm::vec4& color, float thickness /*= 1.0f*/, float fade /*= 0.005f*/)
// {
// 	KN_PRINT_FUNC();

// 	// TODO: implement for circles
// 	// if (state.quad_index_count >= Renderer2DState::MAX_INDICES)
// 	// 	NextBatch();

// 	for (size_t i = 0; i < 4; i++)
// 	{
// 		state.circle_vertex_buffer_ptr->world_position = transform * state.quad_vertex_positions[i];
// 		state.circle_vertex_buffer_ptr->local_position = state.quad_vertex_positions[i] * 2.0f;
// 		state.circle_vertex_buffer_ptr->color = color;
// 		state.circle_vertex_buffer_ptr->thickness = thickness;
// 		state.circle_vertex_buffer_ptr->fade = fade;
// 		state.circle_vertex_buffer_ptr++;
// 	}

// 	state.circle_index_count += 6;
	
// 	state.stats.QuadCount++;
// }

void	Renderer2D::FlushCirclePipeline()
{
	// if (state.circle_index_count)
	// {
	// 	uint32_t dataSize = (uint32_t)((uint8_t*)state.circle_vertex_buffer_ptr - (uint8_t*)state.circle_vertex_buffer_base);
	// 	state.circle_vertex_buffer->SetData(state.circle_vertex_buffer_base, dataSize);

	// 	state.circle_shader->Bind();
	// 	SetShaderUniforms(state.circle_shader);
	// 	RenderCommand::DrawIndexed(state.circle_vertex_array, state.circle_index_count);
	// 	state.stats.DrawCalls++;
	// }
}

} // Kinai
