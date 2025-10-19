#include "Kinai/Renderer/2D/Renderer2D.hpp"

namespace Kinai
{

void	Renderer2D::DrawRect(const math::vec3& position, const math::vec2& size, const math::vec4& color)
{
	KN_PROFILE_FUNC();

	math::vec3 p0 = math::vec3(position.x - size.x * 0.5f, position.y - size.y * 0.5f, position.z);
	math::vec3 p1 = math::vec3(position.x + size.x * 0.5f, position.y - size.y * 0.5f, position.z);
	math::vec3 p2 = math::vec3(position.x + size.x * 0.5f, position.y + size.y * 0.5f, position.z);
	math::vec3 p3 = math::vec3(position.x - size.x * 0.5f, position.y + size.y * 0.5f, position.z);

	DrawLine(p0, p1, color);
	DrawLine(p1, p2, color);
	DrawLine(p2, p3, color);
	DrawLine(p3, p0, color);
}

void	Renderer2D::DrawRect(const math::mat4& transform, const math::vec4& color)
{
	KN_PROFILE_FUNC();

	math::vec3 lineVertices[4];
	for (size_t i = 0; i < 4; i++)
		lineVertices[i] = transform * _quad_vertex_positions[i];

	DrawLine(lineVertices[0], lineVertices[1], color);
	DrawLine(lineVertices[1], lineVertices[2], color);
	DrawLine(lineVertices[2], lineVertices[3], color);
	DrawLine(lineVertices[3], lineVertices[0], color);
}

} // Kinai
