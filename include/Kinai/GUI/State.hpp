#pragma once

#include "Kinai/GUI/GUI.hpp"

namespace Kinai
{

namespace GUI
{

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
	uint32_t next_window_id = 1;
	uint32_t next_widget_id = 1;
	std::array<SDL_Cursor*, SDL_SYSTEM_CURSOR_COUNT> sdl_cursors = { nullptr };
	math::vec2 next_window_pos = { -1.0f, -1.0f };
};

extern State state;

void SetMouseCursor(SDL_SystemCursor cursor);
void ResetMouseCursor();

void UpdateMouseButtons();
void UpdateCanvasSize(float width, float height);

void SetActiveWindow(uint32_t id);
math::vec2 GetRenderTextSize(const char* str);
void RenderText(const char* str, float x, float y);

} // GUI

} // Kinai
