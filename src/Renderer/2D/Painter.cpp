#include "Kinai/Renderer/2D/Painter.hpp"
#include "Kinai/Renderer/2D/painter.glsl.hpp"
#include "Kinai/Renderer/Renderer.hpp"

namespace Kinai
{

Ref<VertexArray> Painter::_vao = nullptr;
Ref<Shader> Painter::_shader = nullptr;
Ref<Texture2D> Painter::_white_texture = nullptr;
Ref<Texture2D> Painter::_current_texture = nullptr;
Painter::QuadPipeline Painter::_quad;

void	Painter::Init()
{
	KN_PROFILE_FUNC();
	
	_vao = VertexArray::Create();
	_shader = Shader::Create(KinaiPainterProgramShaderConfig());

	_white_texture = Texture2D::Create(TextureConfig{
		.width = 2,
		.height = 2,
		.format = ImageFormat::RGBA8,
		.label = "Kinai Painter - White Texture"
	});
	uint32_t pixels[4];
	std::memset(pixels, 0xff, sizeof(pixels));
	_white_texture->SetData(pixels, sizeof(pixels));
	_current_texture = nullptr;

	MakePipelines();
}

void	Painter::Shutdown()
{
	KN_PROFILE_FUNC();

	delete[] _quad.vertex_buffer_base;
}

void	Painter::BeginPass()
{
	KN_PROFILE_FUNC();

	glm::ivec2 size = Application::Get().GetWindow().GetSize();
	Renderer::SetViewport(0, 0, size.x, size.y);

	StartBatch();
}

void	Painter::EndPass()
{
	KN_PROFILE_FUNC();

	Flush();
}

void	Painter::Flush()
{
	if (_quad.index)
	{
		uint32_t dataSize = (uint32_t)((uint8_t*)_quad.vertex_buffer_ptr - (uint8_t*)_quad.vertex_buffer_base);
		_quad.bindings->GetVertexBuffer()->SetData(_quad.vertex_buffer_base, dataSize);

		Renderer::ApplyPipeline(_quad.pipeline);
		Renderer::ApplyBindings(_quad.bindings);

		_shader->Bind();

		if (_current_texture)
			_current_texture->Bind(0);
		else
			_white_texture->Bind(0);
		Renderer::Submit();
		_quad.vertex_buffer_ptr = 0;
	}
}

void	Painter::StartBatch()
{
	_quad.index = 0;
	_quad.vertex_buffer_ptr = _quad.vertex_buffer_base;
}

void	Painter::NextBatch()
{
	Flush();
	StartBatch();
}

void	Painter::MakePipelines()
{
	KN_PROFILE_FUNC();

	_quad.pipeline = Pipeline::Create(PipelineConfig{
		.vao = _vao,
		.shader = _shader,
		.layout = {
			{ ShaderDataType::Float4, "a_Pos" }, // xy = pos, zw = uv
			{ ShaderDataType::Float4, "a_Color" },
		},
		.primitive_type = PrimitiveType::Triangles,
		.cull_mode = CullMode::None,
		.depth_state = DepthState::Always,
		.label = "Kinai Painter - Quad Pipeline (No blending)"
	});

	_quad.blend_state = BlendState{
		.enabled = false
	};

	_quad.bindings = Bindings::Create();
	_quad.bindings->AddVertexBuffer(VertexBuffer::Create(Painter::MAX_VERTICES * sizeof(QuadVertex)));
	_quad.vertex_buffer_base = new QuadVertex[Painter::MAX_VERTICES];

	uint32_t* indices = new uint32_t[Painter::MAX_INDICES];
	uint32_t offset = 0;
	for (uint32_t i = 0; i < Painter::MAX_INDICES; i += 6)
	{
		indices[i + 0] = offset + 0;
		indices[i + 1] = offset + 1;
		indices[i + 2] = offset + 2;

		indices[i + 3] = offset + 2;
		indices[i + 4] = offset + 3;
		indices[i + 5] = offset + 0;

		offset += 4;
	}
	_quad.bindings->SetIndexBuffer(IndexBuffer::Create(indices, Painter::MAX_INDICES));
	delete[] indices;
}

void	Painter::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
{
	KN_PROFILE_FUNC();

	DrawQuad({ position.x, position.y, 0.0f }, size, color);
}

void	Painter::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
{
	KN_PROFILE_FUNC();

	glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
		* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
	DrawQuad(transform, color);
}

void	Painter::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec2& uvStart, const glm::vec2& uvEnd, const glm::vec4& tint_color)
{
	KN_PROFILE_FUNC();

	DrawQuad( { position.x, position.y, 0.0f }, size, uvStart, uvEnd, tint_color);
}

void	Painter::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec2& uvStart, const glm::vec2& uvEnd, const glm::vec4& tint_color)
{
	KN_PROFILE_FUNC();

	glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
		* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
	DrawQuad(transform, uvStart, uvEnd, tint_color);
}

void	Painter::DrawQuad(const glm::mat4& transform, const glm::vec4& color)
{
	KN_PROFILE_FUNC();
	KN_ASSERT(_quad.vertex_buffer_ptr);

	constexpr size_t quadVertexCount = 4;
	constexpr glm::vec4 quad_vertex_positions[4] = {
		glm::vec4(-0.5f, -0.5f, 0.0f, 0.0f),
		glm::vec4( 0.5f, -0.5f, 1.0f, 0.0f),
		glm::vec4( 0.5f,  0.5f, 1.0f, 1.0f),
		glm::vec4(-0.5f,  0.5f, 0.0f, 1.0f),
	};
	
	if (_quad.index >= Painter::MAX_INDICES)
		NextBatch();

	for (size_t i = 0; i < quadVertexCount; i++)
	{
		_quad.vertex_buffer_ptr->position = transform * quad_vertex_positions[i];
		_quad.vertex_buffer_ptr->color = color;
		_quad.vertex_buffer_ptr++;
	}

	_quad.index += 6;
}

void	Painter::DrawQuad(const glm::mat4& transform)
{
	KN_PROFILE_FUNC();

	DrawQuad(transform, glm::vec4(1.0f));
}

void	Painter::DrawQuad(const glm::mat4& transform, const glm::vec2& uvStart, const glm::vec2& uvEnd, const glm::vec4& tint_color)
{
	KN_PROFILE_FUNC();

	constexpr size_t quadVertexCount = 4;
	const glm::vec4 quad_vertex_positions[4] = {
		glm::vec4(-0.5f, -0.5f, uvStart.x, uvStart.y),
		glm::vec4( 0.5f, -0.5f, uvEnd.x, uvStart.y),
		glm::vec4( 0.5f,  0.5f, uvEnd.x, uvEnd.y),
		glm::vec4(-0.5f,  0.5f, uvStart.x, uvEnd.y),
	};

	if (_quad.index >= MAX_INDICES) 
		NextBatch();

	for (size_t i = 0; i < quadVertexCount; i++)
	{
		_quad.vertex_buffer_ptr->position = transform * quad_vertex_positions[i];
		_quad.vertex_buffer_ptr->color = tint_color;
		_quad.vertex_buffer_ptr++;
	}

	_quad.index += 6;
}

} // Kinai::Painter
