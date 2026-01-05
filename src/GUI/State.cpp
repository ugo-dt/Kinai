#include "Kinai/GUI/State.hpp"
#include "Kinai/Core/Application.hpp"

namespace Kinai
{

namespace GUI
{

State g_GuiState;
Style g_GuiStyle;

State& GetState() { return g_GuiState; }
Style& GetStyle() { return g_GuiStyle; }

static struct GUI::Button* GetMouseButton(MouseButton button)
{
	switch (button)
	{
		case Kinai::Mouse::ButtonLeft:
			return &g_GuiState.mouse.left;
		case Kinai::Mouse::ButtonRight:
			return &g_GuiState.mouse.right;
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

	update_button(g_GuiState.mouse.left);
	update_button(g_GuiState.mouse.right);
}

void	UpdateCanvasSize(float width, float height)
{
	KN_ASSERT(g_GuiState.context);
	DebugText::SetContext(g_GuiState.context);
	DebugText::SetCanvasSize(width, height);
	g_GuiState.canvas_size.x = width;
	g_GuiState.canvas_size.y = height;
	g_GuiState.glyph_size = DebugText::GetGlyphSize() * g_GuiState.canvas_size;
}

void	LockCursor()
{
	auto& app = Application::Get();

	app.GetWindow().SetWindowMouseGrab(true);
	g_GuiState.locked_cursor = true;
}

void	UnlockCursor()
{
	auto& app = Application::Get();

	app.GetWindow().SetWindowMouseGrab(g_GuiState.app_mouse_grab);
	g_GuiState.locked_cursor = false;
}

void	SetMouseCursor(SDL_SystemCursor cursor)
{
	KN_ASSERT(cursor >= SDL_SYSTEM_CURSOR_DEFAULT && cursor < SDL_SYSTEM_CURSOR_COUNT);
	SDL_SetCursor(g_GuiState.sdl_cursors[static_cast<int>(cursor)]);
}

void	MouseCursorNewFrame()
{
	SDL_SetCursor(g_GuiState.sdl_cursors[SDL_SYSTEM_CURSOR_DEFAULT]);
	if (!g_GuiState.locked_cursor)
		g_GuiState.app_mouse_grab = Application::Get().GetWindow().GetWindowMouseGrab();
}

void	SetActiveWindow(uint32_t id)
{
	auto it = g_GuiState.windows.find(id);
	if (it != g_GuiState.windows.end())
		g_GuiState.active_window = it->second;
	else
		g_GuiState.active_window = nullptr;
}

glm::vec2	GetRenderTextSize(const char* str)
{
	KN_ASSERT(g_GuiState.context);

	glm::ivec2 size;
	SDL_GetWindowSize((SDL_Window*)Application::Get().GetWindow().GetNativeWindow(), &size.x, &size.y);
	glm::vec2 factor = g_GuiState.glyph_size * ((glm::vec2)size / g_GuiState.canvas_size);
	return glm::vec2(strlen(str) * factor.x, factor.y);
}

void	RenderText(const char* str, float x, float y)
{
	KN_ASSERT(g_GuiState.context);

	DebugText::SetContext(g_GuiState.context);

	glm::ivec2 size;
	SDL_GetWindowSize((SDL_Window*)Application::Get().GetWindow().GetNativeWindow(), &size.x, &size.y);

	glm::vec2 factor = g_GuiState.glyph_size * ((glm::vec2)size / g_GuiState.canvas_size);
	DebugText::SetOrigin(x / factor.x, y / factor.y);
	DebugText::Put(str);
}

} // GUI

} // Kinai
