#include "Kinai/Renderer/2D/Painter.hpp"
#include "Kinai/Renderer/2D/painter.glsl.hpp"
#include "Kinai/Renderer/Renderer.hpp"
#include "Kinai/Core/Application.hpp"

namespace Kinai
{

PainterContext Painter::context;

static BlendState BlendModeToBlendState(BlendMode blend_mode);

void Painter::Init()
{
	KN_PROFILE_FUNC();
	
	context.vao = VertexArray::Create();
	context.shader = Shader::Create(KinaiShader_PainterProgramShaderConfig());

	context.white_texture = Texture2D::Create(TextureConfig{
		.width = 2,
		.height = 2,
		.format = ImageFormat::RGBA8,
		.label = "Kinai Painter - White Texture"
	});
	uint32_t pixels[4] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
	context.white_texture->SetData(pixels, sizeof(pixels));

	context.state.texture_slots.reserve(MAX_TEXTURE_SLOTS);
	for (uint32_t i = 0; i < MAX_TEXTURE_SLOTS; i++)
		context.state.texture_slots.push_back(context.white_texture);

	MakePipelines();
	context.state.pipeline = LookupPipeline(PrimitiveType::Triangles, BlendMode::None);
	const glm::ivec2 size = Application::Get().GetWindow().GetSizeInPixels();
	context.state.camera.SetProjection(0.0f, (float)size.x, (float)size.y, 0.0f);
}

void Painter::Shutdown()
{
	KN_PROFILE_FUNC();

	context.state.pipeline = nullptr;
	for (auto& p: context.state.texture_slots)
		p.reset();

	context.state.vertex_buffer_ptr = nullptr;

	delete[] context.state.vertex_buffer_base;
	context.state.vertex_buffer_base = nullptr;

	context.state.bindings.reset();
	context.state.pipeline.reset();
	for (auto& t : context.state.texture_slots)
		t.reset();

    for (auto& p : context.pipelines)
		p.reset();
	
	context.vertex_buf.reset();
    context.white_texture.reset();
    context.shader.reset();
    context.vao.reset();
}

void Painter::BeginPass()
{
	KN_ASSERT(!context.state.in_pass, "Painter is already in a pass!");
	KN_PROFILE_FUNC();

	const glm::ivec2 size = Application::Get().GetWindow().GetSizeInPixels();
	Renderer::SetViewport(0, 0, size.x, size.y);

	StartBatch();
	context.state.in_pass = true;
}

void Painter::SetViewport(int x, int y, int width, int height)
{
	KN_PROFILE_FUNC();

	Renderer::SetViewport(x, y, width, height);
	context.state.camera.SetProjection(0.0f, (float)width, (float)height, 0.0f);
}

void Painter::EndPass()
{
	KN_PROFILE_FUNC();

	Flush();
	context.state.in_pass = false;
}

void Painter::SetImage(int channel, const Ref<Texture2D>& texture)
{
	Painter::NextBatch(); //fixme
	context.state.texture_slots[channel] = texture;
}

void Painter::ResetImage(int channel)
{
	Painter::NextBatch(); //fixme
	context.state.texture_slots[channel] = context.white_texture;
}

void Painter::SetBlendMode(BlendMode mode)
{
	Painter::NextBatch(); //fixme
	context.state.mode = mode;
}

void Painter::ResetBlendMode()
{
	Painter::NextBatch(); //fixme
	context.state.mode = BlendMode::None;
}

void Painter::Flush()
{
	if (context.state.index)
	{
		uint32_t dataSize = (uint32_t)((uint8_t*)context.state.vertex_buffer_ptr - (uint8_t*)context.state.vertex_buffer_base);
		context.state.bindings->GetVertexBuffer()->SetData(context.state.vertex_buffer_base, dataSize);

		//fixme
		context.state.pipeline->SetBlendState(BlendModeToBlendState(context.state.mode));

		Renderer::ApplyPipeline(context.state.pipeline);
		Renderer::ApplyBindings(context.state.bindings);
		Renderer::ApplyUniforms<KinaiShader_Painter_vs_params_t>({
			.u_ViewProjection = context.state.camera.GetViewProjectionMatrix(),
			.u_Transform = glm::mat4(1.0f),
		});

		context.shader->Bind();
		// for (uint32_t i = 0; i < MAX_TEXTURE_SLOTS; i++)
		// 	if (context.state.texture_slots[i])
		// 		context.state.texture_slots[i]->Bind(i);
		context.state.texture_slots[0]->Bind(0);
		Renderer::Submit();
		context.state.vertex_buffer_ptr = context.state.vertex_buffer_base;
	}
}

void Painter::StartBatch()
{
	context.state.index = 0;
	context.state.vertex_buffer_ptr = context.state.vertex_buffer_base;
}

void Painter::NextBatch()
{
	Flush();
	StartBatch();
}

static BlendState BlendModeToBlendState(BlendMode blend_mode)
{
    BlendState blend;
    switch (blend_mode)
	{
        case BlendMode::None:
            blend.enabled = false;
            blend.src_factor_rgb = BlendFactor::One;
            blend.dst_factor_rgb = BlendFactor::Zero;
            blend.op_rgb = BlendOp::Add;
            blend.src_factor_alpha = BlendFactor::One;
            blend.dst_factor_alpha = BlendFactor::Zero;
            blend.op_alpha = BlendOp::Add;
            break;
        case BlendMode::Blend:
            blend.enabled = true;
            blend.src_factor_rgb = BlendFactor::SrcAlpha;
            blend.dst_factor_rgb = BlendFactor::OneMinusSrcAlpha;
            blend.op_rgb = BlendOp::Add;
            blend.src_factor_alpha = BlendFactor::One;
            blend.dst_factor_alpha = BlendFactor::OneMinusSrcAlpha;
            blend.op_alpha = BlendOp::Add;
            break;
        case BlendMode::BlendPremultiplied:
            blend.enabled = true;
            blend.src_factor_rgb = BlendFactor::One;
            blend.dst_factor_rgb = BlendFactor::OneMinusSrcAlpha;
            blend.op_rgb = BlendOp::Add;
            blend.src_factor_alpha = BlendFactor::One;
            blend.dst_factor_alpha = BlendFactor::OneMinusSrcAlpha;
            blend.op_alpha = BlendOp::Add;
            break;
        case BlendMode::Add:
            blend.enabled = true;
            blend.src_factor_rgb = BlendFactor::SrcAlpha;
            blend.dst_factor_rgb = BlendFactor::One;
            blend.op_rgb = BlendOp::Add;
            blend.src_factor_alpha = BlendFactor::Zero;
            blend.dst_factor_alpha = BlendFactor::One;
            blend.op_alpha = BlendOp::Add;
            break;
        case BlendMode::AddPremultiplied:
            blend.enabled = true;
            blend.src_factor_rgb = BlendFactor::One;
            blend.dst_factor_rgb = BlendFactor::One;
            blend.op_rgb = BlendOp::Add;
            blend.src_factor_alpha = BlendFactor::Zero;
            blend.dst_factor_alpha = BlendFactor::One;
            blend.op_alpha = BlendOp::Add;
            break;
        case BlendMode::Mod:
            blend.enabled = true;
            blend.src_factor_rgb = BlendFactor::DstColor;
            blend.dst_factor_rgb = BlendFactor::Zero;
            blend.op_rgb = BlendOp::Add;
            blend.src_factor_alpha = BlendFactor::Zero;
            blend.dst_factor_alpha = BlendFactor::One;
            blend.op_alpha = BlendOp::Add;
            break;
        case BlendMode::Mul:
            blend.enabled = true;
            blend.src_factor_rgb = BlendFactor::DstColor;
            blend.dst_factor_rgb = BlendFactor::OneMinusSrcAlpha;
            blend.op_rgb = BlendOp::Add;
            blend.src_factor_alpha = BlendFactor::DstAlpha;
            blend.dst_factor_alpha = BlendFactor::OneMinusSrcAlpha;
            blend.op_alpha = BlendOp::Add;
            break;
        default:
			Log::Critical("Unknown BlendMode!");
    }
    return blend;
}

Ref<Pipeline>& Painter::LookupPipeline(PrimitiveType type, BlendMode mode)
{
	KN_PROFILE_FUNC();

	uint32_t pip_index = (static_cast<uint32_t>(type) *
		static_cast<uint32_t>(BlendMode::_BlendMode_NUM)) + static_cast<uint32_t>(mode);
	if (context.pipelines[pip_index] != nullptr)
		return context.pipelines[pip_index];
	
	Ref<Pipeline> pipeline = Pipeline::Create(PipelineConfig{
		.vao = context.vao,
		.shader = context.shader,
		.layout = {
			{ ShaderDataType::Float4, "a_Pos" }, // xy = pos, zw = uv
			{ ShaderDataType::Float4, "a_Color" },
		},
		.primitive_type = type,
		.cull_mode = CullMode::None,
		.depth_state = DepthState::Always,
		.blend_state = BlendModeToBlendState(mode),
		.label = "Kinai Painter default pipeline"
	});
	if (pipeline)
		context.pipelines[pip_index] = pipeline;
	return context.pipelines[pip_index];
}

void Painter::MakePipelines()
{
	KN_PROFILE_FUNC();

    bool pips_ok = true;
    pips_ok = pips_ok && LookupPipeline(PrimitiveType::Triangles, BlendMode::None) != nullptr;
    pips_ok = pips_ok && LookupPipeline(PrimitiveType::Triangles, BlendMode::Blend) != nullptr;
    pips_ok = pips_ok && LookupPipeline(PrimitiveType::Points, BlendMode::None) != nullptr;
    pips_ok = pips_ok && LookupPipeline(PrimitiveType::Points, BlendMode::Blend) != nullptr;
    pips_ok = pips_ok && LookupPipeline(PrimitiveType::Lines, BlendMode::None) != nullptr;
    pips_ok = pips_ok && LookupPipeline(PrimitiveType::Lines, BlendMode::Blend) != nullptr;
    pips_ok = pips_ok && LookupPipeline(PrimitiveType::TriangleStrip, BlendMode::None) != nullptr;
    pips_ok = pips_ok && LookupPipeline(PrimitiveType::TriangleStrip, BlendMode::Blend) != nullptr;
    pips_ok = pips_ok && LookupPipeline(PrimitiveType::LineStrip, BlendMode::None) != nullptr;
    pips_ok = pips_ok && LookupPipeline(PrimitiveType::LineStrip, BlendMode::Blend) != nullptr;
	if (!pips_ok)
		Log::Critical("Painter: failed to create pipelines!");

	context.state.bindings = Bindings::Create();
	context.state.bindings->AddVertexBuffer(VertexBuffer::Create(MAX_VERTICES * sizeof(QuadVertex)));
	context.state.vertex_buffer_base = new QuadVertex[MAX_VERTICES];

	uint32_t* indices = new uint32_t[MAX_INDICES];
	uint32_t offset = 0;
	for (uint32_t i = 0; i < MAX_INDICES; i += 6)
	{
		indices[i + 0] = offset + 0;
		indices[i + 1] = offset + 1;
		indices[i + 2] = offset + 2;

		indices[i + 3] = offset + 2;
		indices[i + 4] = offset + 3;
		indices[i + 5] = offset + 0;

		offset += 4;
	}
	context.state.bindings->SetIndexBuffer(IndexBuffer::Create(indices, MAX_INDICES));
	delete[] indices;
}

void Painter::DrawQuad(const glm::mat4& transform, const glm::vec2& uvStart, const glm::vec2& uvEnd, const glm::vec4& tint_color)
{
	KN_PROFILE_FUNC();

	constexpr size_t quadVertexCount = 4;
	const glm::vec4 quad_vertex_positions[4] = {
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
		glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
		glm::vec4(1.0f, 1.0f, 0.0f, 1.0f),
		glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),
	};
	const glm::vec2 textureCoords[] = {
		{ uvStart.x, uvStart.y },
		{ uvEnd.x, uvStart.y },
		{ uvEnd.x, uvEnd.y },
		{ uvStart.x, uvEnd.y }
	};

	if (context.state.index >= MAX_INDICES) 
		NextBatch();

	for (size_t i = 0; i < quadVertexCount; i++)
	{
		const glm::vec2 pos = glm::vec2(transform * quad_vertex_positions[i]);
		const glm::vec2& uv = textureCoords[i];

		context.state.vertex_buffer_ptr->position = glm::vec4(pos.x, pos.y, uv.x, uv.y);
		context.state.vertex_buffer_ptr->color = tint_color;
		context.state.vertex_buffer_ptr++;
	}

	if (context.state.index + 6 > MAX_INDICES)
		NextBatch();

	context.state.index += 6;
}

void Painter::DrawQuad(float x, float y, float width, float height, const glm::vec4& color)
{
    // Build transform in pixel space
    glm::mat4 transform =
		glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 0.0f)) *
		glm::scale(glm::mat4(1.0f), glm::vec3(width, height, 1.0f));

    // Full texture UVs (0..1)
    glm::vec2 uvStart = { 0.0f, 0.0f };
    glm::vec2 uvEnd = { 1.0f, 1.0f };

    DrawQuad(transform, uvStart, uvEnd, color);
}

void Painter::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color)
{
	KN_PROFILE_FUNC();

	DrawQuad({ position.x, position.y, 0.0f }, size, color);
}

void Painter::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color)
{
	KN_PROFILE_FUNC();

	glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
		* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

	DrawQuad(transform, color);
}

void Painter::DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec2& uvStart, const glm::vec2& uvEnd, const glm::vec4& tint_color)
{
	KN_PROFILE_FUNC();

	DrawQuad( { position.x, position.y, 0.0f }, size, uvStart, uvEnd, tint_color);
}

void Painter::DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec2& uvStart, const glm::vec2& uvEnd, const glm::vec4& tint_color)
{
	KN_PROFILE_FUNC();

	glm::mat4 transform = glm::translate(glm::mat4(1.0f), position)
		* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
	DrawQuad(transform, uvStart, uvEnd, tint_color);
}

void Painter::DrawQuad(const glm::mat4& transform, const glm::vec4& color)
{
	DrawQuad(transform, glm::vec2(0.f), glm::vec2(1.f), color);
}

void Painter::DrawQuad(const glm::mat4& transform)
{
	KN_PROFILE_FUNC();

	DrawQuad(transform, glm::vec4(1.0f));
}

} // Kinai
