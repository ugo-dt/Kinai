#pragma once

#include "Kinai/Renderer/OrthographicCamera.hpp"
#include "Kinai/Renderer/Texture.hpp"

namespace Kinai
{

class Renderer2D
{
public:
	static void	Init();
	static void	Shutdown();

	static void	BeginFrame(const Camera& camera, const glm::mat4& transform);
	static void	BeginFrame(const OrthographicCamera& camera);
	static void	EndFrame();
	static void	Flush();

	static void	DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
	static void	DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
	static void	DrawQuad(const glm::vec2& position, const glm::vec2& size, const Texture2DRef& texture, float tiling_factor = 1.0f, const glm::vec4& tint_color = glm::vec4(1.0f));
};

} // Kinai
