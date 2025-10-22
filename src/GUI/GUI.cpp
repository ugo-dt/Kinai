#include "Kinai/GUI/GUI.hpp"
#include "Kinai/GUI/Window.hpp"
#include "Kinai/Core/Input.hpp"
#include "Kinai/Debug/Text/Text.hpp"

namespace Kinai
{

namespace GUI
{

struct Button
{
	bool pressed = false;
	bool down = false;
};

struct Mouse
{
	float x, y;
	Button left, right;
};

struct State
{
	Mouse mouse;
	Ref<DebugText::Context> context;
	std::unordered_map<int, Window> windows;
	Ref<Window> current_window = nullptr;
	uint32_t next_window_id = 1;
}state;

static bool	OnMouseMotionEvent(MouseMotionEvent &event)
{
	state.mouse.x = floorf(event.GetX());
	state.mouse.y = floorf(event.GetY());
	return false;
}

void	CreateContext()
{
	state.context = DebugText::MakeContext();
	// const math::ivec2 size = Application::Get().GetWindow().GetSize();
	// DebugText::SetCanvasSize((float)size.x / 2.f, (float)size.y / 2.f);
}

void	DestroyContext()
{

}

bool	OnEvent(Event& event)
{
	EventDispatcher	dispatcher(event);

	dispatcher.Dispatch<MouseMotionEvent>(GUI::OnMouseMotionEvent);
	return false;
}

void	NewFrame()
{
	DebugText::SetContext(state.context);
	DebugText::Font(5); // ORIC
	Painter::BeginPass();
	state.next_window_id = 1;
}

void	Render()
{

	for (const auto& [id, window] : state.windows)
	{
		if (!window.IsOpen())
			continue;
		Painter::BeginPass();
		window.Render();
		Painter::EndPass();
		DebugText::SubmitContext(state.context);
	}
	// DebugText::Print("Mouse: {},{}\n", state.mouse.x, state.mouse.y);
	// DebugText::Print("X {} {}\n", state.mouse.x >= 50.f, state.mouse.x <= 150.f);
	// DebugText::Print("Y {} {}\n", state.mouse.y >= 50.f, state.mouse.y <= 150.f);
	// DebugText::SubmitContext(state.context);
}

void	Begin(const char* label, bool* is_open)
{
	KN_ASSERT(!state.current_window, "GUI::Begin called before GUI::End!");
	state.current_window = CreateRef<Window>(
		label,
		Rect{ 50.f, 50.f, 200.f, 200.f },
		is_open
	);
}

void	End()
{
	state.windows.insert(std::make_pair(state.next_window_id++, *state.current_window));
	state.current_window = nullptr;
}

} // GUI

} // Kinai
