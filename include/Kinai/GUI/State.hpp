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
	math::vec2 canvas_size, glyph_size;
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
	math::vec2 next_window_pos = { -1.0f, -1.0f };
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
bool OnEvent(Event& event);

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

math::vec2 GetRenderTextSize(const char* str);
void RenderText(const char* str, float x, float y);

template <class... Args>
KN_INLINE void	RenderText(float x, float y, std::string_view fmt, Args&&... args)
{
	std::string str = std::vformat(fmt, std::make_format_args(args...));
	RenderText(str.c_str(), x, y);	
}

} // GUI

} // Kinai
