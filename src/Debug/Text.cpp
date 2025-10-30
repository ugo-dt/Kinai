#include "Kinai/Debug/Text/Text.hpp"
#include "Kinai/Debug/Text/DebugText.glsl.hpp"
#include "Kinai/Debug/Text/Font.hpp"

namespace Kinai
{

Ref<VertexArray> DebugText::_vao;
Ref<Texture2D> DebugText::_font_texture;
Ref<Shader> DebugText::_shader;
uint32_t DebugText::_fmt_buf_size;
char* DebugText::_fmt_buf;
Ref<DebugText::Context> DebugText::_default_context;
Ref<DebugText::Context> DebugText::_current_context;
std::vector<Ref<DebugText::Context>> DebugText::_contexts;
uint8_t DebugText::_font_pixels[256 * 8 * 8 * MAX_FONTS];

constexpr int DEFAULT_PRINTF_BUF_SIZE = 4096;

struct DebugText::Context
{
	uint32_t frame_id;
	uint32_t update_frame_id;
	std::vector<TextVertex> vertices;
	std::vector<TextCommand> commands;
	size_t commands_cap;
	Ref<VertexBuffer> vertex_buffer;
	Ref<Pipeline> pipeline;
	int cur_font;
	int cur_layer_id;
	glm::vec2 canvas_size;
	glm::vec2 glyph_size;
	glm::vec2 origin;
	glm::vec2 pos;
	float tab_width;
	glm::vec4 color;
};

void	DebugText::Rewind()
{
	KN_ASSERT(_current_context);

    _current_context->frame_id++;
    _current_context->vertices.clear();
    _current_context->commands.clear();
    SetLayer(_current_context, 0);
    _current_context->cur_font = 0;
    _current_context->pos.x = 0.0f;
    _current_context->pos.y = 0.0f;
}

DebugText::TextCommand&	DebugText::NextCommand(Ref<Context>& context)
{
	if (context->commands.size() >= context->commands_cap)
		Log::Critical("Command buffer full");
	return context->commands.emplace_back(TextCommand{});
}

void	DebugText::SetLayer(Ref<Context>& context, int layer_id)
{
	context->cur_layer_id = layer_id;

	if (context->commands.empty())
	{
		// first draw command in frame
		TextCommand& cmd = NextCommand(context);
		cmd.layer_id = layer_id;
		cmd.first_vertex = 0;
		cmd.vertex_count = 0;
	}
	else
	{
		TextCommand& cmd = context->commands.back();
		if ((cmd.vertex_count == 0) || (cmd.layer_id == layer_id))
			cmd.layer_id = layer_id;
		else
		{
			TextCommand& next_cmd = NextCommand(context);
			next_cmd.layer_id = layer_id;
			next_cmd.first_vertex = cmd.first_vertex + cmd.vertex_count;
			next_cmd.vertex_count = 0;
		}
	}
}

Ref<DebugText::Context>	DebugText::MakeContext(const DebugTextContextConfig& config)
{
	Ref<Context> context = CreateRef<Context>();
	InitContext(context, config);
	_contexts.push_back(context);
	return context;
}

void	DebugText::SetContext(Ref<Context> context)
{
	_current_context = context;
}

Ref<DebugText::Context>	DebugText::GetContext()
{
	return _current_context;
}

Ref<DebugText::Context>	DebugText::GetDefaultContext()
{
	return _default_context;
}

glm::vec2	DebugText::GetCanvasSize()
{
	KN_ASSERT(_current_context);
	return glm::vec2(_current_context->canvas_size.x, _current_context->canvas_size.y);
}

glm::vec2	DebugText::GetGlyphSize()
{
	KN_ASSERT(_current_context);
	return glm::vec2(_current_context->glyph_size.x, _current_context->glyph_size.y);
}

int	DebugText::GetFontIndex()
{
	KN_ASSERT(_current_context);
	return _current_context->cur_font;
}

DebugTextFont	DebugText::GetFont()
{
	KN_ASSERT(_current_context);
	return static_cast<DebugTextFont>(_current_context->cur_font);
}

void	DebugText::InitContext(Ref<Context>& context, const DebugTextContextConfig& config)
{
	context->frame_id = 1;

	const size_t vbuf_size = 6 * config.char_buf_size * sizeof(TextVertex);
	context->vertices.reserve(vbuf_size);

	context->commands_cap = config.max_commands;
	context->commands.reserve(context->commands_cap * sizeof(TextCommand));
	SetLayer(context, 0);

	context->vertex_buffer = VertexBuffer::Create(vbuf_size);
	context->pipeline = Pipeline::Create(PipelineConfig{
		.vao = _vao,
		.shader = _shader,
		.layout = {
			{ ShaderDataType::Float2, "a_Position" },
			{ ShaderDataType::Float2, "a_TexCoord" },
			{ ShaderDataType::Float4, "a_Color" },
		},
		.cull_mode = CullMode::None,
		.depth_state = DepthState::Always,
		.blend_state = {
			.enabled = true,
			.src_factor_rgb = BlendFactor::SrcAlpha,
			.dst_factor_rgb = BlendFactor::OneMinusSrcAlpha,
			.src_factor_alpha = BlendFactor::One,
			.dst_factor_alpha = BlendFactor::Zero,
		},
		.label = "Kinai DebugText default pipeline"
	});

	context->canvas_size.x = config.canvas_width;
	context->canvas_size.y = config.canvas_height;
	context->glyph_size.x = 8.0f / context->canvas_size.x;
	context->glyph_size.y = 8.0f / context->canvas_size.y;
	context->tab_width = static_cast<float>(config.tab_width);
	context->color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
}

void	DebugText::UnpackFont(const FontDesc& desc, uint8_t* out_pixels)
{
	KN_ASSERT(desc.ptr);
    KN_ASSERT((desc.size > 0) && ((desc.size % 8) == 0));
    KN_ASSERT(desc.first_char <= desc.last_char);
    KN_ASSERT((size_t)(((desc.last_char - desc.first_char) + 1) * 8) == desc.size);
	const uint8_t* ptr = desc.ptr;
	for (int chr = desc.first_char; chr <= desc.last_char; chr++)
	{
		for (int line = 0; line < 8; line++)
		{
			uint8_t bits = *ptr++;
			for (int x = 0; x < 8; x++)
			{
				out_pixels[line * 256 * 8 + chr * 8 + x] = ((bits >> (7 - x)) & 1) ? 0xFF : 0x00;
			}
		}
	}
}

void	DebugText::Init()
{
	_fmt_buf_size = DEFAULT_PRINTF_BUF_SIZE;
	_fmt_buf = new char[_fmt_buf_size];
	_vao = VertexArray::Create();
	_shader = Shader::Create(KinaiShader_DebugTextProgramShaderConfig());

	std::memset(_font_pixels, 0xFF, sizeof(_font_pixels));
	std::array<FontDesc, MAX_FONTS> font_descs = {
		FontDesc{ _sdtx_font_kc853, sizeof(_sdtx_font_kc853), 0, 255 },
		FontDesc{ _sdtx_font_kc854, sizeof(_sdtx_font_kc854), 0, 255 },
		FontDesc{ _sdtx_font_z1013, sizeof(_sdtx_font_z1013), 0, 255 },
		FontDesc{ _sdtx_font_cpc, sizeof(_sdtx_font_cpc), 0, 255 },
		FontDesc{ _sdtx_font_c64, sizeof(_sdtx_font_c64), 0, 255 },
		FontDesc{ _sdtx_font_oric, sizeof(_sdtx_font_oric), 0, 255 },
		FontDesc{ 0, 0, 0, 0 },
		FontDesc{ 0, 0, 0, 0 }
	};
	const int unpacked_font_size = (int)(sizeof(_font_pixels) / MAX_FONTS);
	for (int i = 0; i < MAX_FONTS; i++)
	{
		if (font_descs[i].ptr)
			UnpackFont(font_descs[i], &_font_pixels[i * unpacked_font_size]);
	}
	_font_texture = Texture2D::Create(TextureConfig{
		.width = 256 * 8,
		.height = MAX_FONTS * 8,
		.format = ImageFormat::R8,
		.sampler_config = SamplerConfig{
			.wrap_s = Wrap::ClampToEdge,
			.wrap_t = Wrap::ClampToEdge,
		},
		.label = "Kinai DebugText font texture"
	});
	_font_texture->SetData(_font_pixels, sizeof(_font_pixels));

	_default_context = MakeContext(DebugTextContextConfig{});
	SetContext(_default_context);
}

void	DebugText::Shutdown()
{
	delete[] _fmt_buf;
	_fmt_buf = nullptr;
}

void	DebugText::Layer(int layer_id)
{
	if (_current_context)
		SetLayer(_current_context, layer_id);
}

void	DebugText::Font(int font_index)
{
	KN_ASSERT(font_index >= 0 && font_index < MAX_FONTS);
	if (_current_context)
		_current_context->cur_font = font_index;
}

void	DebugText::Font(DebugTextFont font)
{
	Font(static_cast<int>(font));
}

void	DebugText::SetCanvasSize(float width, float height)
{
	if (_current_context)
	{
		_current_context->canvas_size.x = width;
		_current_context->canvas_size.y = height;
		_current_context->glyph_size.x = 8.0f / width;
		_current_context->glyph_size.y = 8.0f / height;
		_current_context->origin = glm::vec2(0.0f, 0.0f);
		_current_context->pos = glm::vec2(0.0f, 0.0f);
	}
}

void	DebugText::SetOrigin(float x, float y)
{
	if (_current_context)
	{
		_current_context->origin.x = x;
		_current_context->origin.y = y;
	}
}

void	DebugText::Home()
{
	if (_current_context)
		_current_context->pos = glm::vec2(0.0f, 0.0f);
}

void	DebugText::Pos(float x, float y)
{
	if (_current_context)
		_current_context->pos = glm::vec2(x, y);
}

void	DebugText::PosX(float x)
{
	if (_current_context)
		_current_context->pos.x = x;
}

void	DebugText::PosY(float y)
{
	if (_current_context)
		_current_context->pos.y = y;
}

void	DebugText::Move(float dx, float dy)
{
	if (_current_context)
		_current_context->pos += glm::vec2(dx, dy);
}

void	DebugText::MoveX(float dx)
{
	if (_current_context)
		_current_context->pos.x += dx;
}

void	DebugText::MoveY(float dy)
{
	if (_current_context)
		_current_context->pos.y += dy;
}

void	DebugText::NewLine()
{
	if (_current_context)
	{
		_current_context->pos.x = 0.0f;
		_current_context->pos.y += 1.0f;
	}
}

void	DebugText::SetColor(glm::vec3 color)
{
	if (_current_context)
		_current_context->color = glm::vec4(color.r, color.g, color.b, 1.0f);
}

void	DebugText::SetColor(glm::vec4 color)
{
	if (_current_context)
		_current_context->color = color;
}

void	DebugText::SetColor(uint8_t r, uint8_t g, uint8_t b)
{
	if (_current_context)
		_current_context->color = glm::vec4(
			static_cast<float>(r) / 255.0f,
			static_cast<float>(g) / 255.0f,
			static_cast<float>(b) / 255.0f,
			1.0f);
}

void	DebugText::SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	if (_current_context)
		_current_context->color = glm::vec4(
			static_cast<float>(r) / 255.0f,
			static_cast<float>(g) / 255.0f,
			static_cast<float>(b) / 255.0f,
			static_cast<float>(a) / 255.0f);
}

void	DebugText::CtrlChar(Ref<Context> context, char c)
{
	switch (c)
	{
		case '\n':
			context->pos.x = 0.0f;
			context->pos.y += 1.0f;
			break;
		case '\r':
			context->pos.x = 0.0f;
			break;
		case '\t':
			context->pos.x = (context->pos.x - std::fmodf(context->pos.x, context->tab_width)) + context->tab_width;
			break;
		case ' ':
			context->pos.x += 1.0f;
			break;
		default:
			// ignore other control characters
			break;
	}
}

void	DebugText::RenderChar(Ref<Context> context, char c)
{
	TextVertex vertex;
	TextCommand& cmd = context->commands.back();

	cmd.vertex_count += 6;

	const float x0 = (context->origin.x + context->pos.x) * context->glyph_size.x;
	const float y0 = (context->origin.y + context->pos.y) * context->glyph_size.y;
	const float x1 = x0 + context->glyph_size.x;
	const float y1 = y0 + context->glyph_size.y;

	// glyph width and height in font texture space
	// NOTE: the '+1' and '-2' fixes texture bleeding into the neighboring font texture cell
	const uint16_t uvw = 0x10000 / 0x100;
	const uint16_t uvh = 0x10000 / MAX_FONTS;
	const uint16_t u0 = (((uint16_t)c) * uvw) + 1;
	const uint16_t v0 = (((uint16_t)context->cur_font) * uvh) + 1;
	uint16_t u1 = (u0 + uvw) - 2;
	uint16_t v1 = (v0 + uvh) - 2;

	// write 6 vertices
	vertex.pos.x = x0;
	vertex.pos.y = y0;
	vertex.uv.x = u0 / 65535.f; // normalize it to opengl coods
	vertex.uv.y = v0 / 65535.f;
	vertex.color = context->color;
	context->vertices.push_back(vertex);

	vertex.pos.x = x1;
	vertex.pos.y = y0;
	vertex.uv.x = u1 / 65535.f;
	vertex.uv.y = v0 / 65535.f;
	vertex.color = context->color;
	context->vertices.push_back(vertex);

	vertex.pos.x = x1;
	vertex.pos.y = y1;
	vertex.uv.x = u1 / 65535.f;
	vertex.uv.y = v1 / 65535.f;
	vertex.color = context->color;
	context->vertices.push_back(vertex);
	
	vertex.pos.x = x0;
	vertex.pos.y = y0;
	vertex.uv.x = u0 / 65535.f;
	vertex.uv.y = v0 / 65535.f;
	vertex.color = context->color;
	context->vertices.push_back(vertex);

	vertex.pos.x = x1;
	vertex.pos.y = y1;
	vertex.uv.x = u1 / 65535.f;
	vertex.uv.y = v1 / 65535.f;
	vertex.color = context->color;
	context->vertices.push_back(vertex);

	vertex.pos.x = x0;
	vertex.pos.y = y1;
	vertex.uv.x = u0 / 65535.f;
	vertex.uv.y = v1 / 65535.f;
	vertex.color = context->color;
	context->vertices.push_back(vertex);

	context->pos.x += 1.0f;
}

void	DebugText::Putchar(Ref<Context> context, char c)
{
	uint8_t c_u8 = static_cast<uint8_t>(c);
	if (c_u8 <= 32)
		CtrlChar(context, c_u8);
	else
		RenderChar(context, c_u8);
}

void	DebugText::Put(char c)
{
	KN_ASSERT(_current_context);
	Putchar(_current_context, c);
}

void	DebugText::Put(const char* str)
{
	if (_current_context)
	{
		while (*str)
		{
			Putchar(_current_context, *str);
			str++;
		}
	}
}

void	DebugText::Put(const char* str, size_t len)
{
	if (_current_context)
	{
		size_t i = 0;
		while (i < len && str[i])
		{
			Putchar(_current_context, str[i]);
			i++;
		}
	}
}

int	DebugText::Printf(const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	int n = vsnprintf(_fmt_buf, _fmt_buf_size, fmt, args);
	va_end(args);
	_fmt_buf[_fmt_buf_size - 1] = '\0'; // make sure it's null-terminated
	Put(_fmt_buf);
	return n;
}

void	DebugText::DrawLayer(Ref<Context> context, int layer_id)
{
	if (!context->vertices.empty() && !context->commands.empty())
	{
		if (context->update_frame_id != context->frame_id)
		{
			context->update_frame_id = context->frame_id;
			context->vertex_buffer->SetData(context->vertices.data(), context->vertices.size() * sizeof(TextVertex));
		}

		Renderer::ApplyPipeline(context->pipeline);
		Ref<Bindings> bindings = Bindings::Create();
		bindings->AddVertexBuffer(context->vertex_buffer);
		bindings->AddTexture(_font_texture);
		Renderer::ApplyBindings(bindings);
		for (const auto& cmd : context->commands)
		{
			if (cmd.layer_id != layer_id)
				continue;
			KN_ASSERT(cmd.vertex_count % 6 == 0);
			Renderer::Submit(cmd.vertex_count);
		}
	}
	Rewind();
}

void	DebugText::Submit()
{
	if (_current_context)
		DrawLayer(_current_context, 0);
}

void	DebugText::SubmitContext(Ref<Context> context)
{
	if (context)
		DrawLayer(context, 0);
}

void	DebugText::SubmitLayer(int layer_id)
{
	if (_current_context)
		DrawLayer(_current_context, layer_id);
}

void	DebugText::SubmitContextLayer(Ref<Context> context, int layer_id)
{
	if (context)
		DrawLayer(context, layer_id);
}
} // Kinai
