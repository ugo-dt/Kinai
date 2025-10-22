#include "Kinai/GUI/Event.hpp"
#include "Kinai/GUI/State.hpp"

namespace Kinai
{

namespace GUI
{

bool	OnWindowResizeEvent(WindowResizeEvent &event)
{
	UpdateCanvasSize((float)event.GetWidth() / 2.f, (float)event.GetHeight() / 2.f);
	return false;
}

bool	OnMouseMotionEvent(MouseMotionEvent &event)
{
	state.mouse.x = floorf(event.GetX());
	state.mouse.y = floorf(event.GetY());
	return false;
}

bool	OnMouseButtonPressedEvent(MouseButtonPressedEvent &event)
{
	struct GUI::Button* btn = nullptr;

	switch (event.GetButton())
	{
		case Kinai::Mouse::ButtonLeft: btn = &state.mouse.left; break;
		case Kinai::Mouse::ButtonRight: btn = &state.mouse.right; break;
		default: break;
	}
	if (btn)
	{
		btn->pressed = !btn->down;
		btn->down = true;
		btn->pressed_frame = state.frames;
	}
	return false;
}

bool	OnMouseButtonReleasedEvent(MouseButtonReleasedEvent &event)
{
	struct GUI::Button* btn = nullptr;

	switch (event.GetButton())
	{
		case Kinai::Mouse::ButtonLeft: btn = &state.mouse.left; break;
		case Kinai::Mouse::ButtonRight: btn = &state.mouse.right; break;
		default: break;
	}
	if (btn)
	{
		btn->pressed = false;
		btn->down = false;
		btn->released = true;
		btn->pressed_frame = 0;
	}
	return false;
}

} // GUI


} // Kinai
