#pragma once

#include "Kinai/Core/Core.hpp"
#include "Kinai/Renderer/PerspectiveCamera.hpp"
#include "Kinai/Renderer/RendererAPI.hpp"
#include "Kinai/Renderer/Shader.hpp"

namespace Kinai
{

class Renderer
{
public:
	static void	Init();
	static void	Shutdown();

	static void	BeginFrame(PerspectiveCamera& _camera);
	static void	EndFrame();

	static void	OnWindowResize(uint32_t width, uint32_t height);

	static void	Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertex_array, const glm::mat4& transform = glm::mat4(1.0f));
	static void	SubmitTriangles(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertex_array, uint32_t vertex_count, const glm::mat4& transform = glm::mat4(1.0f));

private:
	static glm::mat4	_view_proj;
};

} // Kinai
