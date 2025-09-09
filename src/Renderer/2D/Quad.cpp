#include "Kinai/Renderer/2D/Renderer2D.hpp"
#include "Kinai/Core/Application.hpp"

namespace Kinai
{

void	Renderer2D::MakeQuadPipeline()
{
	KN_PRINT_FUNC();

	_pip_quad.vertex_array = VertexArray::Create();

	_pip_quad.vertex_buffer = VertexBuffer::Create(Renderer2D::MAX_VERTICES * sizeof(QuadVertex));
	_pip_quad.vertex_buffer->SetLayout({
		{ ShaderDataType::Float2, "a_VERTEX"    },
		{ ShaderDataType::Float2, "a_UV"        },
		{ ShaderDataType::Float4, "a_COLOR"     },
		{ ShaderDataType::Int,    "a_TEX_INDEX" },
	});
	_pip_quad.vertex_array->AddVertexBuffer(_pip_quad.vertex_buffer);

	_pip_quad.vertex_buffer_base = new QuadVertex[Renderer2D::MAX_VERTICES];

	uint32_t* indices = new uint32_t[Renderer2D::MAX_INDICES];

	uint32_t offset = 0;
	for (uint32_t i = 0; i < Renderer2D::MAX_INDICES; i += 6)
	{
		indices[i + 0] = offset + 0;
		indices[i + 1] = offset + 1;
		indices[i + 2] = offset + 2;

		indices[i + 3] = offset + 2;
		indices[i + 4] = offset + 3;
		indices[i + 5] = offset + 0;

		offset += 4;
	}

	Ref<IndexBuffer>	ib = IndexBuffer::Create(indices, Renderer2D::MAX_INDICES);
	_pip_quad.vertex_array->SetIndexBuffer(ib);
	delete[] indices;
}

void	Renderer2D::DestroyQuadPipeline()
{
	KN_PRINT_FUNC();

	delete[] _pip_quad.vertex_buffer_base;
}

void	Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
{
	KN_PRINT_FUNC();

	DrawQuad({ position.x, position.y, 0.0f }, size, color);
}

void	Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
{
	KN_PRINT_FUNC();

	glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
		* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
	
	DrawQuad(transform, color);
}

void	Renderer2D::DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& tintColor)
{
	KN_PRINT_FUNC();

	DrawQuad({ position.x, position.y, 0.0f }, size, texture, tintColor);
}

void	Renderer2D::DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D>& texture, const glm::vec4& tintColor)
{
	DrawQuad(position, size, texture, glm::vec2(0.0f), glm::vec2(1.0f), tintColor);
}

void	Renderer2D::DrawQuad(
	const glm::vec2& position,
	const glm::vec2& size,
	const Ref<Texture2D>& texture,
	const glm::vec2& uvStart,
	const glm::vec2& uvEnd,
	const glm::vec4& tintColor)
{
	KN_PRINT_FUNC();

	DrawQuad( { position.x, position.y, 0.0f }, size, texture, uvStart, uvEnd, tintColor);
}

void	Renderer2D::DrawQuad(
	const glm::vec3& position,
	const glm::vec2& size,
	const Ref<Texture2D>& texture,
	const glm::vec2& uvStart,
	const glm::vec2& uvEnd,
	const glm::vec4& tintColor)
{
	KN_PRINT_FUNC();

	glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
		* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

	DrawQuad(transform, texture, uvStart, uvEnd, tintColor);
}

void	Renderer2D::DrawQuad(const glm::mat4& transform, const glm::vec4& color)
{
	KN_PRINT_FUNC();

	constexpr size_t quadVertexCount = 4;
	constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };

	if (_pip_quad.index >= Renderer2D::MAX_INDICES)
		NextBatch();

	for (size_t i = 0; i < quadVertexCount; i++)
	{
		_pip_quad.vertex_buffer_ptr->position = transform * _quad_vertex_positions[i];
		_pip_quad.vertex_buffer_ptr->color = color;
		_pip_quad.vertex_buffer_ptr->tex_coord = textureCoords[i];
		_pip_quad.vertex_buffer_ptr->tex_index = 0; // White texture
		_pip_quad.vertex_buffer_ptr++;
	}

	_pip_quad.index += 6;
	
	_stats._quad_count++;
}

void	Renderer2D::DrawQuad(const glm::mat4& transform, const Ref<Texture2D>& texture)
{
	DrawQuad(transform, texture, glm::vec2(0.0f), glm::vec2(1.0f));
}

void	Renderer2D::DrawQuad(
	const glm::mat4& transform,
	const Ref<Texture2D>& texture,
	const glm::vec2& uvStart,
	const glm::vec2& uvEnd,
	const glm::vec4& tintColor)
{
	KN_PRINT_FUNC();

	constexpr size_t quadVertexCount = 4;
	// constexpr glm::vec2 textureCoords[] = { { 0.0f, 0.0f }, { 1.0f, 0.0f }, { 1.0f, 1.0f }, { 0.0f, 1.0f } };
    glm::vec2 textureCoords[] = { { uvStart.x, uvStart.y }, { uvEnd.x, uvStart.y }, { uvEnd.x, uvEnd.y }, { uvStart.x, uvEnd.y } };

	if (_pip_quad.index >= MAX_INDICES)
		NextBatch();

	int tex_index = 0;
	for (uint32_t i = 0; i < _texture_slot_index; i++)
	{
		if (*_texture_slots[i] == *texture)
		{
			tex_index = i;
			break;
		}
	}

	if (tex_index == 0)
	{
		if (_texture_slot_index >= MAX_TEXTURE_SLOTS)
			NextBatch();

		tex_index = _texture_slot_index;
		_texture_slots[_texture_slot_index] = texture;
		_texture_slot_index++;
	}

	for (size_t i = 0; i < quadVertexCount; i++)
	{
		_pip_quad.vertex_buffer_ptr->position = transform * _quad_vertex_positions[i];
		_pip_quad.vertex_buffer_ptr->color = tintColor;
		_pip_quad.vertex_buffer_ptr->tex_coord = textureCoords[i];
		_pip_quad.vertex_buffer_ptr->tex_index = tex_index;
		_pip_quad.vertex_buffer_ptr++;
	}

	_pip_quad.index += 6;

	_stats._quad_count++;
}

void	Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const glm::vec4& color)
{
	KN_PRINT_FUNC();

	DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, color);
}

void	Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const glm::vec4& color)
{
	KN_PRINT_FUNC();

	glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
		* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
		* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

	DrawQuad(transform, color);
}

void	Renderer2D::DrawRotatedQuad(const glm::vec2& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, const glm::vec4& tintColor)
{
	KN_PRINT_FUNC();

	DrawRotatedQuad({ position.x, position.y, 0.0f }, size, rotation, texture, tintColor);
}

void	Renderer2D::DrawRotatedQuad(const glm::vec3& position, const glm::vec2& size, float rotation, const Ref<Texture2D>& texture, const glm::vec4& tintColor)
{
	KN_PRINT_FUNC();

	glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
		* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
		* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

	DrawQuad(transform, texture, glm::vec2(0.0f), glm::vec2(1.0f), tintColor);
}

void	Renderer2D::FlushQuadPipeline()
{
	KN_PRINT_FUNC();

	if (_pip_quad.index)
	{
		uint32_t dataSize = (uint32_t)((uint8_t*)_pip_quad.vertex_buffer_ptr - (uint8_t*)_pip_quad.vertex_buffer_base);
		_pip_quad.vertex_buffer->SetData(_pip_quad.vertex_buffer_base, dataSize);

		_pip_quad.shader->Bind();

		// Bind textures
		for (uint32_t i = 0; i < _texture_slot_index; i++)
			_texture_slots[i]->Bind(i);

		_pip_quad.shader->SetFloat2("VIEWPORT", glm::vec2(Application::Get().GetWindow().GetSize()));

		RenderCommand::DrawIndexed(_pip_quad.vertex_array, _pip_quad.index);
		_stats._draw_calls++;
	}
}

void	Renderer2D::SetQuadShader(Shader2D& shader)
{
	KN_PRINT_FUNC();

	if (_shader_library.Exists(shader._shader->GetName()))
	{
		NextBatch();
		_pip_quad.shader = shader._shader;
	}
}

void	Renderer2D::ResetQuadShader()
{
	KN_PRINT_FUNC();

	NextBatch();
	_pip_quad.shader = _shader_library.Get("__kn2d_quad_program");
}

} // Kinai
