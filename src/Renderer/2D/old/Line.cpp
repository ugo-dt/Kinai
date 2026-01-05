#include "Kinai/Renderer/2D/Renderer2D.hpp"

namespace Kinai
{

// void	Renderer2D::DrawLine(const math::vec3& p0, math::vec3& p1, const math::vec4& color)
// {
// 	state.line_vertex_buffer_ptr->position = p0;
// 	state.line_vertex_buffer_ptr->color = color;
// 	state.line_vertex_buffer_ptr++;

// 	state.line_vertex_buffer_ptr->position = p1;
// 	state.line_vertex_buffer_ptr->color = color;
// 	state.line_vertex_buffer_ptr++;

// 	state.line_vertex_count += 2;
// }

// float	Renderer2D::GetLineWidth()
// {
// 	return state.line_width;
// }

// void	Renderer2D::SetLineWidth(float width)
// {
// 	state.line_width = width;
// }

void	Renderer2D::FlushLinePipeline()
{
	KN_PROFILE_FUNC();

	// if (state.line_vertex_count)
	// {
	// 	uint32_t dataSize = (uint32_t)((uint8_t*)state.line_vertex_buffer_ptr - (uint8_t*)state.line_vertex_buffer_base);
	// 	state.line_vertex_buffer->SetData(state.line_vertex_buffer_base, dataSize);

	// 	state.line_shader->Bind();
	// 	SetShaderUniforms(state.line_shader);
	// 	Renderer::SetLineWidth(state.line_width);
	// 	Renderer::DrawLines(state.line_vertex_array, state.line_vertex_count);
	// 	state.stats.DrawCalls++;
	// }
}

} // Kinai
