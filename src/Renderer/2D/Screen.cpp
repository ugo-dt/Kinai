#include "Kinai/Renderer/2D/Renderer2D.hpp"
#include "Kinai/Core/Application.hpp"

namespace Kinai
{

Ref<Framebuffer>	Renderer2D::_screen_main_framebuffer;
Ref<Framebuffer>	Renderer2D::_screen_shader_framebuffer;
Ref<VertexArray>	Renderer2D::_screen_vertex_array;
Ref<Shader>			Renderer2D::_screen_shader;

const char *SCREEN_SHADER_VERTEX = R"(
	#version 450 core

	layout (location = 0) in vec2 a_VERTEX;
	layout (location = 1) in vec2 a_UV;

	out vec2 SCREEN_UV;

	void main()
	{
		SCREEN_UV = a_UV;
		gl_Position = vec4(a_VERTEX.x, a_VERTEX.y, 0.0, 1.0); 
	}
)";

const char *SCREEN_SHADER_FRAGMENT = R"(
	#version 450 core

	out vec4 COLOR;

	in vec2 SCREEN_UV;

	uniform sampler2D Quad;

	void main()
	{
		vec3 col = texture(Quad, SCREEN_UV).rgb;
		COLOR = vec4(col, 1.0);
	} 
)";

void	Renderer2D::MakeScreenFramebuffers()
{
	_screen_vertex_array = VertexArray::Create();

	// Vertex attributes for a quad that fills
	// the entire screen in Normalized Device Coordinates.
	float quadVertices[] = {
		// Positions  // TexCoords
		-1.0f,  1.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 0.0f,
		 1.0f, -1.0f, 1.0f, 0.0f,
		-1.0f,  1.0f, 0.0f, 1.0f,
		 1.0f, -1.0f, 1.0f, 0.0f,
		 1.0f,  1.0f, 1.0f, 1.0f
	};

	Kinai::Ref<Kinai::VertexBuffer>	vbuf = Kinai::VertexBuffer::Create(quadVertices, sizeof(quadVertices));
	vbuf->SetLayout({
		{ Kinai::ShaderDataType::Float2, "a_VERTEX" },
		{ Kinai::ShaderDataType::Float2, "a_UV" },
	});
	_screen_vertex_array->AddVertexBuffer(vbuf);

	glm::ivec2 winsize = Application::Get().GetWindow().GetSize();

	FramebufferConfig config;
	config.attachments = { FramebufferTextureFormat::RGBA8, FramebufferTextureFormat::RED_INTEGER, FramebufferTextureFormat::Depth };
	config.width = winsize.x;
	config.height = winsize.y;

	_screen_main_framebuffer = Framebuffer::Create(config);
	_screen_shader_framebuffer = Framebuffer::Create(config);

	_screen_shader = Shader::Create("ScreenShader", SCREEN_SHADER_VERTEX, SCREEN_SHADER_FRAGMENT);
	_screen_shader->Bind();
    _screen_shader->SetInt("Quad", 0);
}

void	Renderer2D::UseMainFramebuffer()
{
	_screen_main_framebuffer->Bind();
	Kinai::RenderCommand::Clear();
	_screen_main_framebuffer->ClearAttachment(1, -1);
}

void	Renderer2D::RenderFramebuffer()
{
	_screen_main_framebuffer->Unbind();
	Kinai::RenderCommand::Clear();

	_screen_shader->Bind();
	_screen_vertex_array->Bind();
	glBindTexture(GL_TEXTURE_2D, _screen_main_framebuffer->GetColorAttachmentRendererID());	// use the color attachment texture as the texture of the quad plane
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void	Renderer2D::CopyScreenToBackBuffer()
{
}

} // Kinai
