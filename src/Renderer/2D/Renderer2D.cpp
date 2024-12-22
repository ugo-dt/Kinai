#include "Kinai/Renderer/2D/Renderer2D.hpp"

#include "Kinai/Platform/OpenGL/OpenGLShader.hpp"

#include "Kinai/Renderer/2D/Shaders/Quad.glsl.hpp"

namespace Kinai
{

Pipeline<QuadVertex>				Renderer2D::_pip_quad;
glm::vec4							Renderer2D::_quad_vertex_positions[4];
std::array<Ref<Texture2D>,
	Renderer2D::MAX_TEXTURE_SLOTS>	Renderer2D::_texture_slots;
uint32_t 							Renderer2D::_texture_slot_index;
Renderer2D::CameraUniforms			Renderer2D::_camera_uniforms;
Ref<UniformBuffer>					Renderer2D::_camera_uniforms_buffer;
Renderer2D::BuiltinUniforms			Renderer2D::_builtin_uniforms;
Ref<UniformBuffer>					Renderer2D::_builtin_uniforms_buffer;
Renderer2D::Statistics				Renderer2D::_stats;

void	Renderer2D::MakeCommonPipelines()
{
	MakeQuadPipeline();
}

void	Renderer2D::MakeShaders()
{
#ifndef KINAI_PATH
	#define KINAI_PATH "./"
#endif
	// OpenGLShader::GenerateHeaderFromShader(KINAI_PATH "include/Kinai/Renderer/2D/Shaders/Quad.glsl", "__kn2d_quad_program");
	// OpenGLShader::GenerateHeaderFromShader(KINAI_PATH "include/Kinai/Renderer/2D/Shaders/Circle.glsl", "__kn2d_circle_program");
	// OpenGLShader::GenerateHeaderFromShader(KINAI_PATH "include/Kinai/Renderer/2D/Shaders/Line.glsl", "__kn2d_line_program");

	_pip_quad.shader = _shader_library.Load(KINAI_PATH "include/Kinai/Renderer/2D/Shaders/Quad.glsl", "__kn2d_quad_program");
}	

void	Renderer2D::Init()
{
	MakeCommonPipelines();
	MakeShaders();
	MakeScreenFramebuffers();

	// Create a white texture
	_texture_slots[0] = Texture2D::Create(TextureConfig());
	uint32_t white_texture = 0xffffffff;
	_texture_slots[0]->SetData(&white_texture, sizeof(uint32_t));
	_texture_slot_index = 1;

	_quad_vertex_positions[0] = glm::vec4(-0.5f, -0.5f, 0.0f, 1.0f);
	_quad_vertex_positions[1] = glm::vec4( 0.5f, -0.5f, 0.0f, 1.0f);
	_quad_vertex_positions[2] = glm::vec4( 0.5f,  0.5f, 0.0f, 1.0f);
	_quad_vertex_positions[3] = glm::vec4(-0.5f,  0.5f, 0.0f, 1.0f);

	_builtin_uniforms.time = SDL_GetTicks() / 1000.0f;
	_builtin_uniforms.pi = glm::pi<float>();
	_builtin_uniforms.tau = glm::tau<float>();
	_builtin_uniforms.e = glm::e<float>();
	_builtin_uniforms_buffer = UniformBuffer::Create(sizeof(BuiltinUniforms), 0);

	_camera_uniforms_buffer = UniformBuffer::Create(sizeof(CameraUniforms), 1);
}

void	Renderer2D::Shutdown()
{
	DestroyQuadPipeline();
}

void	Renderer2D::BeginFrame(const OrthographicCamera& camera)
{
	KN_PRINT_FUNC();

	_camera_uniforms.view_projection = camera.GetViewProjectionMatrix();
	_camera_uniforms_buffer->SetData(&_camera_uniforms, sizeof(CameraUniforms));
	
	StartBatch();
}

void	Renderer2D::BeginFrame(const PerspectiveCamera& camera)
{
	KN_PRINT_FUNC();

	_camera_uniforms.view_projection = camera.GetViewProjectionMatrix();
	_camera_uniforms_buffer->SetData(&_camera_uniforms, sizeof(CameraUniforms));

	StartBatch();
}

void	Renderer2D::BeginFrame(const Camera& camera, const glm::mat4& transform)
{
	KN_PRINT_FUNC();

	_camera_uniforms.view_projection = camera.GetProjectionMatrix() * glm::inverse(transform);
	_camera_uniforms_buffer->SetData(&_camera_uniforms, sizeof(CameraUniforms));
	
	StartBatch();
}

void	Renderer2D::Flush()
{
	FlushQuadPipeline();
	FlushCirclePipeline();
	FlushLinePipeline();
	CopyScreenToBackBuffer();
}

void	Renderer2D::EndFrame()
{
	KN_PRINT_FUNC();

	Flush();
}

void	Renderer2D::StartBatch()
{
	_builtin_uniforms.time = SDL_GetTicks() / 1000.0f;
	_builtin_uniforms_buffer->SetData(&_builtin_uniforms, sizeof(BuiltinUniforms));

	_pip_quad.index = 0;
	_pip_quad.vertex_buffer_ptr = _pip_quad.vertex_buffer_base;

	// _circle_index_count = 0;
	// _circle_vertex_buffer_ptr = _circle_vertex_buffer_base;

	// _line_vertex_count = 0;
	// _line_vertex_buffer_ptr = _line_vertex_buffer_base;	

	_texture_slot_index = 2;
}

void	Renderer2D::NextBatch()
{
	Flush();
	StartBatch();
}

} // Kinai
