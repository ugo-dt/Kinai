#pragma once

#include "Kinai/Core/Core.hpp"
#include "Kinai/Renderer/Pipeline.hpp"
#include "Kinai/Renderer/Bindings.hpp"
#include "Kinai/Renderer/Texture.hpp"
#include "Kinai/Renderer/Buffer/VertexBuffer.hpp"
#include "Kinai/Renderer/OrthographicCamera.hpp"

namespace Kinai
{

enum class BlendMode
{
	None = 0,
	Blend,
	BlendPremultiplied,
	Add,
	AddPremultiplied,
	Mod,
	Mul,
	_BlendMode_NUM
};

constexpr uint32_t MAX_QUADS = 20000;
constexpr uint32_t MAX_VERTICES = MAX_QUADS * 4;
constexpr uint32_t MAX_INDICES = MAX_QUADS * 6;
constexpr uint32_t MAX_TEXTURE_SLOTS = 4;

struct QuadVertex
{
	glm::vec4 position; // xy = position, zw = uv
	glm::vec4 color;
};

struct State
{
	OrthographicCamera camera = OrthographicCamera(0.0f, 1.0f, 1.0f, 0.0f);
	glm::vec4 color;
	BlendMode mode = BlendMode::None;
	Ref<Pipeline> pipeline = nullptr;
	std::vector<Ref<Texture2D>> texture_slots;
	Ref<Bindings> bindings = nullptr;
	QuadVertex *vertex_buffer_base = nullptr;
	QuadVertex *vertex_buffer_ptr = nullptr;
	uint32_t index = 0;
	bool in_pass = false;
};

struct PainterContext
{
	State state;

	Ref<VertexArray> vao = nullptr;
	Ref<Shader> shader = nullptr;
	Ref<VertexBuffer> vertex_buf = nullptr;
	Ref<Texture2D> white_texture = nullptr;
	std::array<Ref<Pipeline>,
		(int)PrimitiveType::_PrimitiveType_NUM * (int)BlendMode::_BlendMode_NUM> pipelines;
};

class Painter
{
public:
	static void Init();
	static void Shutdown();

	static void BeginPass();
	static void EndPass();
	static void SetViewport(int x, int y, int width, int height);

	static void SetImage(int channel, const Ref<Texture2D>& texture);
	static void ResetImage(int channel = 0);
	static void SetBlendMode(BlendMode mode);
	static void ResetBlendMode();

	static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
	static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);
	static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec2& uvStart, const glm::vec2& uvEnd, const glm::vec4& tint_color = glm::vec4(1.0f));
	static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec2& uvStart, const glm::vec2& uvEnd, const glm::vec4& tint_color = glm::vec4(1.0f));
	static void DrawQuad(const glm::mat4& transform);
	static void DrawQuad(const glm::mat4& transform, const glm::vec4& color);
	static void DrawQuad(const glm::mat4& transform, const glm::vec2& uvStart, const glm::vec2& uvEnd, const glm::vec4& tint_color = glm::vec4(1.0f));
	static void DrawQuad(float x, float y, float width, float height, const glm::vec4& color);

	static void MakePipelines();
	static void Flush();
	static void StartBatch();
	static void NextBatch();

private:
	static Ref<Pipeline>& LookupPipeline(PrimitiveType type, BlendMode mode);

private:
	static PainterContext context;

}; // Painter

} // Kinai
