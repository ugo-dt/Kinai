#include "Kinai/Renderer/Renderer2D.hpp"
#include "Kinai/Renderer/RenderCommand.hpp"
#include "Kinai/Renderer/UniformBuffer.hpp"

namespace Kinai
{

struct QuadVertex
{
	glm::vec3	position;
	glm::vec4	color;
	glm::vec2	tex_coord;
	float		tex_index;
	float		tiling_factor;
};

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

struct Renderer2DState
{
	static const uint32_t	MAX_QUADS = 20000;
	static const uint32_t	MAX_VERTICES = MAX_QUADS * 4;
	static const uint32_t	MAX_INDICES = MAX_QUADS * 6;
	static const uint32_t	MAX_TEXTURE_SLOTS = 32;

	Ref<VertexArray>	quad_vertex_array;
	Ref<VertexBuffer>	quad_vertex_buffer;
	Ref<Shader>			quad_shader;
	Ref<Texture2D>		white_texture;

	Ref<VertexArray>	circle_vertex_array;
	Ref<VertexBuffer>	circle_vertex_buffer;
	Ref<Shader>			circle_shader;
	
	Ref<VertexArray>	line_vertex_array;
	Ref<VertexBuffer>	line_vertex_buffer;
	Ref<Shader>			line_shader;

	Ref<VertexArray>	text_vertex_array;
	Ref<VertexBuffer>	text_vertex_buffer;
	Ref<Shader>			text_shader;

	uint32_t			quad_index_count = 0;
	QuadVertex*			quad_vertex_buffer_base = nullptr;
	QuadVertex*			quad_vertex_buffer_ptr = nullptr;
	
	uint32_t			circle_index_count = 0;
	CircleVertex*		circle_vertex_buffer_base = nullptr;
	CircleVertex*		circle_vertex_buffer_ptr = nullptr;
	
	uint32_t			line_vertex_count = 0;
	LineVertex*			line_vertex_buffer_base = nullptr;
	LineVertex*			line_vertex_buffer_ptr = nullptr;

	float				line_width = 2.0f;

	std::array<Ref<Texture2D>,MAX_TEXTURE_SLOTS>	texture_slots;
	uint32_t			texture_slot_index = 1;

	Ref<Texture2D>		font_atlas_texture;

	glm::vec4			quad_vertex_positions[4];

	struct CameraData
	{
		glm::mat4	view_projection;
	};
	CameraData			camera_buffer;
	Ref<UniformBuffer>	camera_uniform_buffer;
	
	Renderer2D::Statistics	stats;
};

static Renderer2DState state;

void	Renderer2D::Init()
{
	KN_PRINT_FUNC();

	state.quad_vertex_array = VertexArray::Create();

	state.quad_vertex_buffer = VertexBuffer::Create(state.MAX_VERTICES * sizeof(QuadVertex));
	state.quad_vertex_buffer->SetLayout({
		{ ShaderDataType::Float3, "a_Position"     },
		{ ShaderDataType::Float4, "a_Color"        },
		{ ShaderDataType::Float2, "a_TexCoord"     },
		{ ShaderDataType::Float,  "a_TexIndex"     },
		{ ShaderDataType::Float,  "a_TilingFactor" },
	});
	state.quad_vertex_array->AddVertexBuffer(state.quad_vertex_buffer);

	state.quad_vertex_buffer_base = new QuadVertex[state.MAX_VERTICES];

	uint32_t* quad_indices = new uint32_t[state.MAX_INDICES];

	uint32_t offset = 0;
	for (uint32_t i = 0; i < state.MAX_INDICES; i += 6)
	{
		quad_indices[i + 0] = offset + 0;
		quad_indices[i + 1] = offset + 1;
		quad_indices[i + 2] = offset + 2;

		quad_indices[i + 3] = offset + 2;
		quad_indices[i + 4] = offset + 3;
		quad_indices[i + 5] = offset + 0;

		offset += 4;
	}

	Ref<IndexBuffer>	quad_ib = IndexBuffer::Create(quad_indices, state.MAX_INDICES);
	state.quad_vertex_array->SetIndexBuffer(quad_ib);
	delete[] quad_indices;

	// Circles
	state.circle_vertex_array = VertexArray::Create();

	state.circle_vertex_buffer = VertexBuffer::Create(state.MAX_VERTICES * sizeof(CircleVertex));
	state.circle_vertex_buffer->SetLayout({
		{ ShaderDataType::Float3, "a_WorldPosition" },
		{ ShaderDataType::Float3, "a_LocalPosition" },
		{ ShaderDataType::Float4, "a_Color"         },
		{ ShaderDataType::Float,  "a_Thickness"     },
		{ ShaderDataType::Float,  "a_Fade"          },
	});
	state.circle_vertex_array->AddVertexBuffer(state.circle_vertex_buffer);
	state.circle_vertex_array->SetIndexBuffer(quad_ib); // Use quad IB
	state.circle_vertex_buffer_base = new CircleVertex[state.MAX_VERTICES];

	// Lines
	state.line_vertex_array = VertexArray::Create();

	state.line_vertex_buffer = VertexBuffer::Create(state.MAX_VERTICES * sizeof(LineVertex));
	state.line_vertex_buffer->SetLayout({
		{ ShaderDataType::Float3, "a_Position" },
		{ ShaderDataType::Float4, "a_Color"    },
	});
	state.line_vertex_array->AddVertexBuffer(state.line_vertex_buffer);
	state.line_vertex_buffer_base = new LineVertex[state.MAX_VERTICES];

	state.white_texture = Texture2D::Create(TextureConfig());
	uint32_t whiteTextureData = 0xffffffff;
	state.white_texture->SetData(&whiteTextureData, sizeof(uint32_t));

	state.quad_shader   = Shader::Create("shaders/Renderer2D_Quad.glsl",   "2d_quad");
	state.circle_shader = Shader::Create("shaders/Renderer2D_Circle.glsl", "2d_circle");
	state.line_shader   = Shader::Create("shaders/Renderer2D_Line.glsl",   "2d_line");

	// Set first texture slot to 0
	state.texture_slots[0] = state.white_texture;

	state.quad_vertex_positions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
	state.quad_vertex_positions[1] = {  0.5f, -0.5f, 0.0f, 1.0f };
	state.quad_vertex_positions[2] = {  0.5f,  0.5f, 0.0f, 1.0f };
	state.quad_vertex_positions[3] = { -0.5f,  0.5f, 0.0f, 1.0f };

	state.camera_uniform_buffer = UniformBuffer::Create(sizeof(Renderer2DState::CameraData), 0);
}

void	Renderer2D::Shutdown()
{
	delete[] state.quad_vertex_buffer_base;
}

void Renderer2D::BeginFrame(const OrthographicCamera& camera)
{
	KN_PRINT_FUNC();

	state.camera_buffer.view_projection = camera.GetViewProjectionMatrix();
	state.camera_uniform_buffer->SetData(&state.camera_buffer, sizeof(Renderer2DState::CameraData));

	StartBatch();
}

void Renderer2D::BeginFrame(const Camera& camera, const glm::mat4& transform)
{
	KN_PRINT_FUNC();

	state.camera_buffer.view_projection = camera.GetProjectionMatrix() * glm::inverse(transform);
	state.camera_uniform_buffer->SetData(&state.camera_buffer, sizeof(Renderer2DState::CameraData));

	StartBatch();
}

void Renderer2D::EndFrame()
{
	KN_PRINT_FUNC();

	Flush();
}

void Renderer2D::StartBatch()
{
	state.quad_index_count = 0;
	state.quad_vertex_buffer_ptr = state.quad_vertex_buffer_base;

	state.circle_index_count = 0;
	state.circle_vertex_buffer_ptr = state.circle_vertex_buffer_base;

	state.line_vertex_count = 0;
	state.line_vertex_buffer_ptr = state.line_vertex_buffer_base;	
	
	state.texture_slot_index = 1;
}

void Renderer2D::Flush()
{
	if (state.quad_index_count)
	{
		uint32_t dataSize = (uint32_t)((uint8_t*)state.quad_vertex_buffer_ptr - (uint8_t*)state.quad_vertex_buffer_base);
		state.quad_vertex_buffer->SetData(state.quad_vertex_buffer_base, dataSize);

		// Bind textures
		for (uint32_t i = 0; i < state.texture_slot_index; i++)
			state.texture_slots[i]->Bind(i);

		state.quad_shader->Bind();
		RenderCommand::DrawIndexed(state.quad_vertex_array, state.quad_index_count);
		state.stats.DrawCalls++;
	}

	if (state.circle_index_count)
	{
		uint32_t dataSize = (uint32_t)((uint8_t*)state.circle_vertex_buffer_ptr - (uint8_t*)state.circle_vertex_buffer_base);
		state.circle_vertex_buffer->SetData(state.circle_vertex_buffer_base, dataSize);

		state.circle_shader->Bind();
		RenderCommand::DrawIndexed(state.circle_vertex_array, state.circle_index_count);
		state.stats.DrawCalls++;
	}

	if (state.line_vertex_count)
	{
		uint32_t dataSize = (uint32_t)((uint8_t*)state.line_vertex_buffer_ptr - (uint8_t*)state.line_vertex_buffer_base);
		state.line_vertex_buffer->SetData(state.line_vertex_buffer_base, dataSize);

		state.line_shader->Bind();
		RenderCommand::SetLineWidth(state.line_width);
		RenderCommand::DrawLines(state.line_vertex_array, state.line_vertex_count);
		state.stats.DrawCalls++;
	}
}

void Renderer2D::NextBatch()
{
	Flush();
	StartBatch();
}

void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
{
	DrawQuad({ position.x, position.y, 0.0f }, size, color);
}

void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
{
	KN_PRINT_FUNC();

	glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
		* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
	
	DrawQuad(transform, color);
}

void Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
{
	DrawQuad({ position.x, position.y, 0.0f }, size, texture, tilingFactor, tintColor);
}

void Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
{
	KN_PRINT_FUNC();

	glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
		* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

	DrawQuad(transform, texture, tilingFactor, tintColor);
}

void Renderer2D::DrawQuad(const glm::mat4& transform, const glm::vec4& color)
{
	KN_PRINT_FUNC();

	constexpr size_t quadVertexCount = 4;
	const float textureIndex = 0.0f; // White Texture
	constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
	const float tilingFactor = 1.0f;

	if (state.quad_index_count >= Renderer2DState::MAX_INDICES)
		NextBatch();

	for (size_t i = 0; i < quadVertexCount; i++)
	{
		state.quad_vertex_buffer_ptr->position = transform * state.quad_vertex_positions[i];
		state.quad_vertex_buffer_ptr->color = color;
		state.quad_vertex_buffer_ptr->tex_coord = textureCoords[i];
		state.quad_vertex_buffer_ptr->tex_index = textureIndex;
		state.quad_vertex_buffer_ptr->tiling_factor = tilingFactor;
		state.quad_vertex_buffer_ptr++;
	}

	state.quad_index_count += 6;
	
	state.stats.QuadCount++;
}

void Renderer2D::DrawQuad(const glm::mat4& transform, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
{
	KN_PRINT_FUNC();

	constexpr size_t quadVertexCount = 4;
	constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };

	if (state.quad_index_count >= Renderer2DState::MAX_INDICES)
		NextBatch();

	float textureIndex = 0.0f;
	for (uint32_t i = 1; i < state.texture_slot_index; i++)
	{
		if (*state.texture_slots[i] == *texture)
		{
			textureIndex = (float)i;
			break;
		}
	}

	if (textureIndex == 0.0f)
	{
		if (state.texture_slot_index >= Renderer2DState::MAX_TEXTURE_SLOTS)
			NextBatch();

		textureIndex = (float)state.texture_slot_index;
		state.texture_slots[state.texture_slot_index] = texture;
		state.texture_slot_index++;
	}

	for (size_t i = 0; i < quadVertexCount; i++)
	{
		state.quad_vertex_buffer_ptr->position = transform * state.quad_vertex_positions[i];
		state.quad_vertex_buffer_ptr->color = tintColor;
		state.quad_vertex_buffer_ptr->tex_coord = textureCoords[i];
		state.quad_vertex_buffer_ptr->tex_index = textureIndex;
		state.quad_vertex_buffer_ptr->tiling_factor = tilingFactor;
		state.quad_vertex_buffer_ptr++;
	}

	state.quad_index_count += 6;

	state.stats.QuadCount++;
}

void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
{
	DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, color);
}

void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
{
	KN_PRINT_FUNC();

	glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
		* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
		* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

	DrawQuad(transform, color);
}

void Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
{
	DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, texture, tilingFactor, tintColor);
}

void Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, float tilingFactor, const glm::vec4& tintColor)
{
	KN_PRINT_FUNC();

	glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
		* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
		* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

	DrawQuad(transform, texture, tilingFactor, tintColor);
}

void Renderer2D::DrawCircle(const glm::mat4& transform, const glm::vec4& color, float thickness /*= 1.0f*/, float fade /*= 0.005f*/)
{
	KN_PRINT_FUNC();

	// TODO: implement for circles
	// if (state.quad_index_count >= Renderer2DState::MAX_INDICES)
	// 	NextBatch();

	for (size_t i = 0; i < 4; i++)
	{
		state.circle_vertex_buffer_ptr->world_position = transform * state.quad_vertex_positions[i];
		state.circle_vertex_buffer_ptr->local_position = state.quad_vertex_positions[i] * 2.0f;
		state.circle_vertex_buffer_ptr->color = color;
		state.circle_vertex_buffer_ptr->thickness = thickness;
		state.circle_vertex_buffer_ptr->fade = fade;
		state.circle_vertex_buffer_ptr++;
	}

	state.circle_index_count += 6;
	
	state.stats.QuadCount++;
}

void Renderer2D::DrawLine(const glm::vec3& p0, glm::vec3& p1, const glm::vec4& color)
{
	state.line_vertex_buffer_ptr->position = p0;
	state.line_vertex_buffer_ptr->color = color;
	state.line_vertex_buffer_ptr++;

	state.line_vertex_buffer_ptr->position = p1;
	state.line_vertex_buffer_ptr->color = color;
	state.line_vertex_buffer_ptr++;

	state.line_vertex_count += 2;
}

void Renderer2D::DrawRect(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
{
	glm::vec3 p0 = glm::vec3(position.x - size.x * 0.5f, position.y - size.y * 0.5f, position.z);
	glm::vec3 p1 = glm::vec3(position.x + size.x * 0.5f, position.y - size.y * 0.5f, position.z);
	glm::vec3 p2 = glm::vec3(position.x + size.x * 0.5f, position.y + size.y * 0.5f, position.z);
	glm::vec3 p3 = glm::vec3(position.x - size.x * 0.5f, position.y + size.y * 0.5f, position.z);

	DrawLine(p0, p1, color);
	DrawLine(p1, p2, color);
	DrawLine(p2, p3, color);
	DrawLine(p3, p0, color);
}

void Renderer2D::DrawRect(const glm::mat4& transform, const glm::vec4& color)
{
	glm::vec3 lineVertices[4];
	for (size_t i = 0; i < 4; i++)
		lineVertices[i] = transform * state.quad_vertex_positions[i];

	DrawLine(lineVertices[0], lineVertices[1], color);
	DrawLine(lineVertices[1], lineVertices[2], color);
	DrawLine(lineVertices[2], lineVertices[3], color);
	DrawLine(lineVertices[3], lineVertices[0], color);
}

float Renderer2D::GetLineWidth()
{
	return state.line_width;
}

void Renderer2D::SetLineWidth(float width)
{
	state.line_width = width;
}

void Renderer2D::Statistics::Reset()
{
	memset(this, 0, sizeof(Statistics));
}

Renderer2D::Statistics& Renderer2D::GetStats()
{
	return state.stats;
}

} // Kinai
