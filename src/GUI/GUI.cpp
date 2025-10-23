#include "Kinai/GUI/GUI.hpp"
#include "Kinai/GUI/Window.hpp"
#include "Kinai/Core/Input.hpp"
#include "Kinai/Core/Application.hpp"

#include "Kinai/GUI/Event.hpp"
#include "Kinai/GUI/Window.hpp"
#include "Kinai/GUI/State.hpp"

namespace Kinai
{

namespace GUI
{

Ref<DebugText::Context>	debug_context = nullptr;

void	CreateContext()
{
	state.context = DebugText::MakeContext();
	DebugText::SetContext(state.context);
	math::ivec2 size;
	SDL_GetWindowSize((SDL_Window*)Application::Get().GetWindow().GetNativeWindow(), &size.x, &size.y);
	UpdateCanvasSize((float)size.x / 1.3f, (float)size.y / 1.3f);
	state.scale = 1.3f;

	for (int i = 0; i < SDL_SYSTEM_CURSOR_COUNT; ++i)
		state.sdl_cursors[i] = SDL_CreateSystemCursor(static_cast<SDL_SystemCursor>(i));

	// debug
	debug_context = DebugText::MakeContext();
}

void	DestroyContext()
{
	for (int i = 0; i < SDL_SYSTEM_CURSOR_COUNT; ++i)
		if (state.sdl_cursors[i])
			SDL_DestroyCursor(state.sdl_cursors[i]);
}

bool	OnEvent(Event& event)
{
	EventDispatcher	dispatcher(event);

	dispatcher.Dispatch<WindowResizeEvent>(GUI::OnWindowResizeEvent);
	dispatcher.Dispatch<MouseMotionEvent>(GUI::OnMouseMotionEvent);
	dispatcher.Dispatch<MouseButtonPressedEvent>(GUI::OnMouseButtonPressedEvent);
	dispatcher.Dispatch<MouseButtonReleasedEvent>(GUI::OnMouseButtonReleasedEvent);
	return false;
}

Point	GetMousePosition()
{
	return Point{ state.mouse.x, state.mouse.y };
}

bool	IsMouseHovering(const Rect&rect)
{
	return PointInRect(GetMousePosition(), rect);
}

void	NewFrame()
{
	++state.frames;
	ResetMouseCursor();
	state.next_window_id = 1;
}

static void RenderWindow(const Ref<GUI::Window>& window)
{
	DebugText::SetContext(state.context);
	DebugText::SetOrigin(0.f, 0.f);
	DebugText::Home();
	DebugText::Font(DebugTextFont::ORIC);
	Painter::BeginPass();
	window->Render();
	Painter::EndPass();
	DebugText::SubmitContext(state.context);
}

void	Render()
{
	if (state.current_window && !state.begin_called)
	{
		// User didn't call Begin(), we need to End() now
		KN_ASSERT(state.current_window);
		state.begin_called = true;
		GUI::End();
	}

	for (const auto& [id, window] : state.windows)
	{
		if (state.active_window == window)
			continue;
		if (!window->IsOpen())
			continue;
		RenderWindow(window);
	}
	if (state.active_window && state.active_window->IsOpen())
		RenderWindow(state.active_window);

	for (const auto & [id, window] : state.windows)
			window->Update();

	UpdateMouseButtons();

	// math::ivec2 size;
	// SDL_GetWindowSize((SDL_Window*)Application::Get().GetWindow().GetNativeWindow(), &size.x, &size.y);
	// DebugText::SetContext(debug_context);
	// DebugText::SetCanvasSize((float)size.x, (float)size.y);
	// DebugText::Font(DebugTextFont::KC854);
	// DebugText::SetColor(math::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	// // debug text here
	// DebugText::Print("Active Window ID: {}\n", state.active_window ? state.active_window->GetID() : 0);
	// DebugText::Print("Total Windows: {}\n", state.windows.size());
	// DebugText::SubmitContext(debug_context);
}

void	SetNextWindowPos(const math::ivec2& pos)
{
	KN_ASSERT(pos.x >= 0.f && pos.y >= 0.f, "GUI: invalid window position");
	state.next_window_pos = pos;
}

void	Begin(const char* label, bool* is_open, WindowFlags flags)
{
	KN_ASSERT(!state.current_window, "GUI::Begin called before GUI::End!");

	math::vec2 pos = (state.next_window_pos.x >= 0.f && state.next_window_pos.y >= 0.f)
		? state.next_window_pos : math::vec2((state.next_window_id + 1) * 50.f, (state.next_window_id + 1) * 50.f);
	
	state.begin_called = true;
	state.current_window = state.windows.contains(state.next_window_id)
		? state.windows.at(state.next_window_id)
		: CreateRef<GUI::Window>(
			label,
			state.next_window_id,
			Rect{ pos.x, pos.y, 200.f, 200.f },
			is_open,
			flags
		);
	state.next_widget_id = 0;
	state.next_window_pos = math::vec2(-1.f, -1.f); // reset to invalid values
}

void	End()
{
	KN_ASSERT(state.current_window, "GUI::End called without a matching GUI::Begin!");
	KN_ASSERT(state.begin_called, "GUI::End called without a matching GUI::Begin!");
	
	state.windows.insert(std::make_pair(state.next_window_id++, state.current_window));
	state.current_window = nullptr;
}

} // GUI

} // Kinai
