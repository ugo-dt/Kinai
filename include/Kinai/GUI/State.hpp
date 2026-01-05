#pragma once

#include "Kinai/GUI/Core.hpp"
#include "Kinai/GUI/Event.hpp"
#include "Kinai/GUI/Style.hpp"

namespace Kinai
{

namespace GUI
{

// Forward declaration
class Window;

struct Button
{
	bool pressed = false;
	bool down = false;
	bool released = false;

	bool pressed_handled = false;
	bool down_handled = false;
	bool released_handled = false;
	uint64_t pressed_frame = 0;
};

struct Mouse
{
	float x, y;
	struct GUI::Button left, right;
};

struct State
{
	glm::vec2 canvas_size, glyph_size;
	float scale = 1.0f;
	uint64_t frames = 0;
	GUI::Mouse mouse;
	Ref<DebugText::Context> context;
	std::unordered_map<uint32_t, Ref<GUI::Window>> windows;
	Ref<GUI::Window> current_window = nullptr, active_window = nullptr;
	bool begin_called = false;
	uint32_t next_window_id = 1;
	uint32_t next_widget_id = 1;
	std::array<SDL_Cursor*, SDL_SYSTEM_CURSOR_COUNT> sdl_cursors = { nullptr };
	glm::vec2 next_window_pos = { -1.0f, -1.0f };
	bool app_mouse_grab, locked_cursor;
};

extern State g_GuiState;
extern Style g_GuiStyle;

State& GetState();
Style& GetStyle();

// Context
void CreateContext();
void DestroyContext();
void NewFrame();
void Render();
void OnEvent(Event& event);

// Input
Point GetMousePosition();
bool IsMouseHovering(const Rect&rect);
bool IsMouseButtonPressed(MouseButton button);
bool IsMouseButtonDown(MouseButton button);
bool IsMouseButtonReleased(MouseButton button);

void LockCursor();
void UnlockCursor();
void SetMouseCursor(SDL_SystemCursor cursor);
void MouseCursorNewFrame();

void UpdateMouseButtons();
void UpdateCanvasSize(float width, float height);

void SetActiveWindow(uint32_t id);

glm::vec2 GetRenderTextSize(const char* str);
void RenderText(const char* str, float x, float y);

KN_INLINE void	RenderText(float x, float y, const char* fmt, ...)
{
	// std::string str = std::vformat(fmt, std::make_format_args(args...));
	char str[4096];
	va_list args;
	va_start(args, fmt);
	std::vsnprintf(const_cast<char*>(str), sizeof(str), fmt, args);
	va_end(args);
	str[sizeof(str) - 1] = '\0';
	RenderText(str, x, y);	
}

} // GUI

} // Kinai
