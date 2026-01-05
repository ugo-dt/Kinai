#pragma once

#include "Kinai/Core/Core.hpp"
#include "Kinai/Renderer/Buffer/Buffer.hpp"
#include "Kinai/Renderer/Pipeline.hpp"
#include "Kinai/Renderer/Shader.hpp"
#include "Kinai/Renderer/Texture.hpp"
#include "Kinai/Renderer/Renderer.hpp"

namespace Kinai
{

struct DebugTextContextConfig
{
	int max_commands = 4096;
	int char_buf_size = 4096;
	float canvas_width = 640.0f;
	float canvas_height = 480.0f;
	int tab_width = 4;
};

enum class DebugTextFont
{
	KC853,
	KC854,
	Z1013,
	CPC,
	C64,
	ORIC,
};

class DebugText
{
public:
	struct Context;

public:
	static void Init();
	static void Shutdown();

	// Context functions
	static Ref<Context>	MakeContext(const DebugTextContextConfig& config = DebugTextContextConfig());
	static void SetContext(Ref<Context> context);
	static Ref<Context> GetContext();
	static Ref<Context> GetDefaultContext();
	static math::vec2 GetCanvasSize();
	static math::vec2 GetGlyphSize();
	static int GetFontIndex();
	static DebugTextFont GetFont();

	// Drawing functions (call inside a Kinai render pass)
	static void Submit();
	static void SubmitContext(Ref<Context> context);
	static void SubmitLayer(int layer_id);
	static void SubmitContextLayer(Ref<Context> context, int layer_id);

	// Switch render layer
	static void Layer(int layer_id);

	// Switch to a different font
	static void Font(int font_index);
	static void Font(DebugTextFont font);

	// Set a new virtual canvas size in screen pixels
	static void SetCanvasSize(float width, float height);

	// Set a new origin in character grid coordinates
	static void SetOrigin(float x, float y);

	// Cursor movement functions (relative to origin in character grid coordinates)
	static void Home();
	static void Pos(float x, float y);
	static void PosX(float x);
	static void PosY(float y);
	static void Move(float dx, float dy);
	static void MoveX(float dx);
	static void MoveY(float dy);
	static void NewLine();

	// Set the text color
	static void SetColor(math::vec3 color); // RGB 0.0f..1.0f, A=1.0f
	static void SetColor(math::vec4 color); // RGBA 0.0f..1.0f
	static void SetColor(uint8_t r, uint8_t g, uint8_t b); // RGB 0..255, A=255
	static void SetColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a); // RGBA 0..255

	// Text rendering functions
	static void Put(char c);
	static void Put(const char* str); // does not append newline
	static void Put(const char* str , size_t len); // range. stops at len or null terminator
	static int Printf(const char* fmt, ...) KN_PRINTF_LIKE(1, 2);
	// template <class... Args>
	// static void Print(std::string_view fmt, Args&&... args)
	// {
	// 	const std::string s = std::vformat(fmt, std::make_format_args(args...));
	// 	Put(s.c_str());
	// }

private:
	struct TextCommand;
	struct TextVertex;
	struct FontDesc;

	static void UnpackFont(const FontDesc& desc, uint8_t* out_pixels);
	static void InitContext(Ref<Context>& context, const DebugTextContextConfig& config);
	static void Rewind();
	static TextVertex& NextVertex(Ref<Context>& context);
	static TextCommand& NextCommand(Ref<Context>& context);
	static void SetLayer(Ref<Context>& context, int layer_id);
	static void Putchar(Ref<Context> context, char c);
	static void CtrlChar(Ref<Context> context, char c);
	static void RenderChar(Ref<Context> context, char c);
	static void DrawLayer(Ref<Context> context, int layer_id);

private:
	static constexpr int MAX_FONTS = 8;
	static constexpr uint32_t INVALID_ID = 0;

	struct FontDesc
	{
		const uint8_t* ptr;
		size_t size;
		uint8_t first_char;
		uint8_t last_char;
	};

	struct TextVertex
	{
		math::vec2 pos;
		math::vec2 uv;
		math::vec4 color;
	};

	struct TextCommand
	{
		int layer_id;
		int first_vertex;
		int vertex_count;
	};

	static Ref<VertexArray> _vao;
	static Ref<Texture2D> _font_texture;
	static Ref<Shader> _shader;
	static uint32_t _fmt_buf_size;
	static char* _fmt_buf;
	static Ref<Context> _default_context;
	static Ref<Context> _current_context; // may be null
	static std::vector<Ref<Context>> _contexts;
	static uint8_t _font_pixels[256 * 8 * 8 * MAX_FONTS];
};

} // Kinai
