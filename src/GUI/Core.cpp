#include "Kinai/Core/Application.hpp"
#include "Kinai/GUI/Core.hpp"
#include "Kinai/GUI/Event.hpp"
#include "Kinai/GUI/State.hpp"
#include "Kinai/GUI/Window.hpp"

namespace Kinai
{

namespace GUI
{

Ref<DebugText::Context>	debug_context = nullptr;

void	CreateContext()
{
	g_GuiState.context = DebugText::MakeContext();
	DebugText::SetContext(g_GuiState.context);
	math::ivec2 size;
	SDL_GetWindowSize((SDL_Window*)Application::Get().GetWindow().GetNativeWindow(), &size.x, &size.y);
	g_GuiState.scale = 1.f;
	UpdateCanvasSize((float)size.x / g_GuiState.scale, (float)size.y / g_GuiState.scale);

	for (int i = 0; i < SDL_SYSTEM_CURSOR_COUNT; ++i)
		g_GuiState.sdl_cursors[i] = SDL_CreateSystemCursor(static_cast<SDL_SystemCursor>(i));

	// debug
	debug_context = DebugText::MakeContext();
}

void	DestroyContext()
{
	for (int i = 0; i < SDL_SYSTEM_CURSOR_COUNT; ++i)
		if (g_GuiState.sdl_cursors[i])
			SDL_DestroyCursor(g_GuiState.sdl_cursors[i]);
}

void	OnEvent(Event& event)
{
	EventDispatcher	dispatcher(event);

	dispatcher.Dispatch<WindowResizeEvent>(GUI::OnWindowResizeEvent);
	dispatcher.Dispatch<MouseMotionEvent>(GUI::OnMouseMotionEvent);
	// dispatcher.Dispatch<MouseButtonPressedEvent>(GUI::OnMouseButtonPressedEvent);
	// dispatcher.Dispatch<MouseButtonReleasedEvent>(GUI::OnMouseButtonReleasedEvent);

	if (g_GuiState.active_window && g_GuiState.active_window->IsOpen())
	{
		g_GuiState.active_window->OnEvent(event);
		if (event.handled)
			return;
	}

	for (const auto& gui_window : g_GuiState.windows)
	{
		auto& window = gui_window.second;
		if (g_GuiState.active_window && g_GuiState.active_window->GetID() == window->GetID())
			continue;
		if (!window->IsOpen())
			continue;

		window->OnEvent(event);
		if (event.handled)
			break;
	}
}

Point	GetMousePosition()
{
	return Point{ g_GuiState.mouse.x, g_GuiState.mouse.y };
}

bool	IsMouseHovering(const Rect&rect)
{
	return PointInRect(GetMousePosition(), rect);
}

void	NewFrame()
{
	++g_GuiState.frames;
	MouseCursorNewFrame();
	g_GuiState.next_window_id = 1;
}

static void RenderWindow(const Ref<GUI::Window>& window)
{
	DebugText::SetContext(g_GuiState.context);
	DebugText::SetOrigin(0.f, 0.f);
	DebugText::SetColor(255, 255, 255, 255);
	DebugText::Home();
	DebugText::Font(DebugTextFont::ORIC);

	Painter::Begin();
	window->Render();

	Renderer::BeginPass();
	Painter::Flush();
	Painter::End();

	DebugText::SubmitContext(g_GuiState.context);
	Renderer::EndPass();
}

void	Render()
{
	if (g_GuiState.current_window && !g_GuiState.begin_called)
	{
		// User didn't call Begin(), we need to End() now
		KN_ASSERT(g_GuiState.current_window);
		g_GuiState.begin_called = true;
		GUI::End();
	}

	for (const auto& gui_window : g_GuiState.windows)
	{
		auto& window = gui_window.second;
		if (g_GuiState.active_window && g_GuiState.active_window->GetID() == window->GetID())
			continue;
		if (!window->IsOpen())
			continue;
		RenderWindow(window);
	}
	if (g_GuiState.active_window && g_GuiState.active_window->IsOpen())
		RenderWindow(g_GuiState.active_window);

	for (const auto & gui_window : g_GuiState.windows)
		gui_window.second->Update();

	UpdateMouseButtons();

	// debug
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
	g_GuiState.next_window_pos = pos;
}

void	Begin(const char* label, bool* is_open, WindowFlags flags)
{
	KN_ASSERT(!g_GuiState.current_window, "GUI::Begin called before GUI::End!");

	math::vec2 pos = (g_GuiState.next_window_pos.x >= 0.f && g_GuiState.next_window_pos.y >= 0.f)
		? g_GuiState.next_window_pos : math::vec2((g_GuiState.next_window_id + 1) * 50.f, (g_GuiState.next_window_id + 1) * 50.f);
	
	g_GuiState.begin_called = true;
	g_GuiState.current_window = g_GuiState.windows.find(g_GuiState.next_window_id) != g_GuiState.windows.end()
		? g_GuiState.windows.at(g_GuiState.next_window_id)
		: CreateRef<GUI::Window>(
			label,
			g_GuiState.next_window_id,
			Rect{ pos.x, pos.y, 200.f, 200.f },
			is_open,
			flags
		);
	g_GuiState.next_widget_id = 0;
	g_GuiState.next_window_pos = math::vec2(-1.f, -1.f); // reset to invalid values
}

void	End()
{
	KN_ASSERT(g_GuiState.current_window, "GUI::End called without a matching GUI::Begin!");
	KN_ASSERT(g_GuiState.begin_called, "GUI::End called without a matching GUI::Begin!");
	
	g_GuiState.windows.insert(std::make_pair(g_GuiState.next_window_id++, g_GuiState.current_window));
	g_GuiState.current_window = nullptr;
}

} // GUI

} // Kinai
