#include "Kinai/Renderer/Renderer.hpp"
#include "Kinai/Core/Application.hpp"
#include "Kinai/Renderer/RenderCommand.hpp"

namespace Kinai
{

glm::mat4	Renderer::_view_proj;

void	Renderer::Init()
{
	KN_PRINT_FUNC();

	RenderCommand::Init();
}

void	Renderer::Shutdown()
{
	KN_PRINT_FUNC();
}

void	Renderer::BeginFrame(PerspectiveCamera& camera)
{
	KN_PRINT_FUNC();

	_view_proj = camera.GetViewProjectionMatrix();
}

void	Renderer::EndFrame()
{
	KN_PRINT_FUNC();
}

void	Renderer::OnWindowResize(uint32_t width, uint32_t height)
{
	KN_PRINT_FUNC();

	RenderCommand::SetViewport(0, 0, width, height);
}

void	Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform)
{
	shader->Bind();
	shader->SetMat4("u_ViewProjection", _view_proj);
	shader->SetMat4("u_Transform", transform);

	vertexArray->Bind();
	RenderCommand::DrawIndexed(vertexArray);
}

void	Renderer::SubmitTriangles(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, uint32_t vertex_count, const glm::mat4& transform)
{
	shader->Bind();
	shader->SetMat4("u_ViewProjection", _view_proj);
	shader->SetMat4("u_Transform", transform);

	vertexArray->Bind();
	RenderCommand::DrawTriangles(vertexArray, vertex_count);
}

}
