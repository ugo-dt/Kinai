#include "Kinai/Core/Application.hpp"
#include "Kinai/Renderer/Renderer.hpp"
#include "Kinai/Renderer/2D/Renderer2D.hpp"
#include "Kinai/Renderer/RenderCommand.hpp"

namespace Kinai
{

glm::mat4	Renderer::_view_proj;

void	Renderer::Init()
{
	KN_PRINT_FUNC();

	RenderCommand::Init();
	// Renderer2D::Init();
}

void	Renderer::Shutdown()
{
	KN_PRINT_FUNC();
	
	Renderer2D::Shutdown();
}

void	Renderer::BeginFrame(const PerspectiveCamera& camera)
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
	Renderer2D::UpdateViewport();
}

void	Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform)
{
	shader->Bind();
	shader->SetMat4("u_ViewProjection", _view_proj);
	shader->SetMat4("u_Transform", transform);

	vertexArray->Bind();
	RenderCommand::DrawIndexed(vertexArray);
}

void	Renderer::SubmitTriangles(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, uint32_t vertex_count, const glm::mat4& transform)
{
	shader->Bind();
	shader->SetMat4("u_ViewProjection", _view_proj);
	shader->SetMat4("u_Transform", transform);

	vertexArray->Bind();
	RenderCommand::DrawTriangles(vertexArray, vertex_count);
}

}
