#include "Kinai/GUI/State.hpp"
#include "Kinai/Core/Application.hpp"

namespace Kinai
{

namespace GUI
{

State state;

static struct GUI::Button* GetMouseButton(MouseButton button)
{
	switch (button)
	{
		case Kinai::Mouse::ButtonLeft:
			return &state.mouse.left;
		case Kinai::Mouse::ButtonRight:
			return &state.mouse.right;
		default:
			return nullptr;
	}
}

bool	IsMouseButtonPressed(MouseButton button)
{
	struct GUI::Button* btn = GetMouseButton(button);
	bool pressed = (btn && !btn->pressed_handled && btn->pressed);
	// btn->pressed_handled = true;
	return pressed;
}

bool	IsMouseButtonDown(MouseButton button)
{
	struct GUI::Button* btn = GetMouseButton(button);
	bool down = (btn && !btn->down_handled && btn->down);
	// btn->down_handled = true;
	return down;
}

bool	IsMouseButtonReleased(MouseButton button)
{
	struct GUI::Button* btn = GetMouseButton(button);
	bool released = (btn && !btn->released_handled && btn->released);
	// btn->released_handled = true;
	return released;
}

void	UpdateMouseButtons()
{
	auto update_button = [](struct GUI::Button& btn)
	{
		btn.pressed = false;
		btn.released = false;
		btn.pressed_handled = false;
		btn.down_handled = false;
		btn.released_handled = false;
	};

	update_button(state.mouse.left);
	update_button(state.mouse.right);
}

void	UpdateCanvasSize(float width, float height)
{
	KN_ASSERT(state.context);
	DebugText::SetContext(state.context);
	DebugText::SetCanvasSize(width, height);
	state.canvas_size.x = width;
	state.canvas_size.y = height;
	state.glyph_size = DebugText::GetGlyphSize() * state.canvas_size;
}

void	SetMouseCursor(SDL_SystemCursor cursor)
{
	KN_ASSERT(cursor >= SDL_SYSTEM_CURSOR_DEFAULT && cursor < SDL_SYSTEM_CURSOR_COUNT);
	SDL_SetCursor(state.sdl_cursors[static_cast<int>(cursor)]);
}

void	ResetMouseCursor()
{
	SDL_SetCursor(state.sdl_cursors[SDL_SYSTEM_CURSOR_DEFAULT]);
}

void	SetActiveWindow(uint32_t id)
{
	auto it = state.windows.find(id);
	if (it != state.windows.end())
		state.active_window = it->second;
	else
		state.active_window = nullptr;
}

math::vec2	GetRenderTextSize(const char* str)
{
	KN_ASSERT(state.context);

	math::ivec2 size;
	SDL_GetWindowSize((SDL_Window*)Application::Get().GetWindow().GetNativeWindow(), &size.x, &size.y);
	math::vec2 factor = state.glyph_size * ((math::vec2)size / state.canvas_size);
	return math::vec2(strlen(str) * factor.x, factor.y);
}

void	RenderText(const char* str, float x, float y)
{
	KN_ASSERT(state.context);

	DebugText::SetContext(state.context);

	math::ivec2 size;
	SDL_GetWindowSize((SDL_Window*)Application::Get().GetWindow().GetNativeWindow(), &size.x, &size.y);

	math::vec2 factor = state.glyph_size * ((math::vec2)size / state.canvas_size);
	DebugText::SetOrigin(x / factor.x, y / factor.y);
	DebugText::Put(str);
}

} // GUI

} // Kinai
