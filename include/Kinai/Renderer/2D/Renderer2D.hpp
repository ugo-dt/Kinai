#pragma once

#include "Kinai/Core/Core.hpp"

#include "Kinai/Renderer/Framebuffer.hpp"
#include "Kinai/Renderer/OrthographicCamera.hpp"
#include "Kinai/Renderer/PerspectiveCamera.hpp"
#include "Kinai/Renderer/RenderCommand.hpp"
#include "Kinai/Renderer/Texture.hpp"
#include "Kinai/Renderer/UniformBuffer.hpp"

namespace Kinai
{

struct CircleVertex
{
	glm::vec3	world_position;
	glm::vec3	local_position;
	glm::vec4	color;
	float		thickness;
	float		fade;
};

struct LineVertex
{
	glm::vec3	position;
	glm::vec4	color;
	glm::vec2	tex_coord;
};

struct QuadVertex
{
	glm::vec2	position;
	glm::vec2	tex_coord;
	glm::vec4	color;
	int			tex_index;
};

template <class Tp>
struct Pipeline
{
	Ref<Shader> shader = nullptr;
	Ref<VertexArray> vertex_array = nullptr;
	Ref<VertexBuffer> vertex_buffer = nullptr;

	uint32_t index;
	Tp* vertex_buffer_base = nullptr;
	Tp* vertex_buffer_ptr = nullptr;

	// primitive type
	// blend
	// color format
	// depth format
	// sample count
};

class Renderer2D
{
public:
	static void	BeginFrame(const Camera& camera, const glm::mat4& transform);
	static void	BeginFrame(const OrthographicCamera& camera);
	static void	BeginFrame(const PerspectiveCamera& camera);

	static void	Flush();
	static void	UpdateViewport();

	/** This function calls Renderer2D::Flush(). */
	static void	EndFrame();
	
	static void	DrawCircle(const glm::mat4& transform, const glm::vec4& color, float thickness = 1.0f, float fade = 0.005f);

	static void	DrawLine(const glm::vec3& p0, glm::vec3& p1, const glm::vec4& color);

	static float GetLineWidth();
	static void	SetLineWidth(float width);

	static void	DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
	static void	DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
	static void	DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& tint_color = glm::vec4(1.0f));
	static void	DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& tint_color = glm::vec4(1.0f));
	static void	DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec2& uvStart, const glm::vec2& uvEnd, const glm::vec4& tint_color = glm::vec4(1.0f));
	static void	DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec2& uvStart, const glm::vec2& uvEnd, const glm::vec4& tint_color = glm::vec4(1.0f));
	static void	DrawQuad(const glm::mat4& transform, const glm::vec4& color);
	static void	DrawQuad(const glm::mat4& transform, const Ref<Texture2D>& texture);
	static void	DrawQuad(const glm::mat4& transform, const Ref<Texture2D>& texture, const glm::vec2& uvStart, const glm::vec2& uvEnd, const glm::vec4& tint_color = glm::vec4(1.0f));

	static void	DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color);
	static void	DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color);
	static void	DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, const glm::vec4& tintColor = glm::vec4(1.0f));
	static void	DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, const glm::vec4& tintColor = glm::vec4(1.0f));
	
	static void	DrawRect(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
	static void	DrawRect(const glm::mat4& transform, const glm::vec4& color);

public:
	class Shader2D
	{
	public:
		Ref<Shader>&	GetShader() { return _shader; }

	private:
		Shader2D(const Ref<Shader>& shader): _shader(shader) {}
		Ref<Shader> _shader;
		friend class Renderer2D;
	};

	//TODO
	// static Shader2D	MakeShader(const std::string& filepath, const std::string& program_name);
	static Shader2D	MakeShader(const std::string& program_name, const std::string& vertexSrc, const std::string& fragmentSrc);

	static void	SetQuadShader(Shader2D& shader);
	static void	ResetQuadShader();

public:
	static void	Init();
	static void	Shutdown();

	// void	AddVertexShader(const std::string& filepath);
	// void	AddFragmentShader(const std::string& filepath);

	class Statistics
	{
	public:
		uint32_t	GetTotalVertexCount() { return _quad_count * 4; }
		uint32_t	GetTotalIndexCount()  { return _quad_count * 6; }
		void		Reset()               { memset(this, 0, sizeof(Statistics)); }

		uint32_t	GetDrawCalls() const { return _draw_calls; }
		uint32_t	GetQuadCount() const { return _quad_count; }

	private:
		uint32_t	_draw_calls;
		uint32_t	_quad_count;

		Statistics() = default;
	
		friend class Renderer2D;
	};

	static Statistics&	GetStats() { return _stats; }

private:
	static constexpr uint32_t	MAX_QUADS = 20000;
	static constexpr uint32_t	MAX_VERTICES = MAX_QUADS * 4;
	static constexpr uint32_t	MAX_INDICES = MAX_QUADS * 6;
	static constexpr uint32_t	MAX_TEXTURE_SLOTS = 31;

private:
	static void	StartBatch();
	static void	NextBatch();

	static void	MakeCommonPipelines();
	static void	MakeQuadPipeline();

	static void	FlushQuadPipeline();
	static void	FlushCirclePipeline();
	static void	FlushLinePipeline();

	static void	DestroyQuadPipeline();

	static void	MakeShaders();

	static void	MakeScreenFramebuffers();
	static void	CopyScreenToBackBuffer();

private:
	static ShaderLibrary _shader_library;

	static Pipeline<QuadVertex>	_pip_quad;
	static glm::vec4 _quad_vertex_positions[4];

	static std::array<Ref<Texture2D>, MAX_TEXTURE_SLOTS> _texture_slots;
	static uint32_t _texture_slot_index;

	struct CameraUniforms
	{
		glm::mat4	view_projection;
	};
	static CameraUniforms		_camera_uniforms;
	static Ref<UniformBuffer>	_camera_uniforms_buffer;

	struct BuiltinUniforms
	{
		float	time;
		float	pi;
		float	tau;
		float	e;
	};
	static BuiltinUniforms		_builtin_uniforms;
	static Ref<UniformBuffer>	_builtin_uniforms_buffer;

	static unsigned int			_screen_framebuffer;

	static Statistics	_stats;
};

} // Kinai
