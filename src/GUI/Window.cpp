#include "Kinai/GUI/Window.hpp"
#include "Kinai/GUI/State.hpp"

namespace Kinai
{

namespace GUI
{

Window::Window(const char* label, uint32_t id, Rect rect, bool* is_open, WindowFlags flags)
	: _id(id),
	  _rect(rect),
	  _label(label),
	  _is_open(is_open),
	  _flags(flags),
	  _widget_origin(rect.x, rect.y),
	  _dragging(false)
{
	if (!(_flags & WindowFlags_NoMenubar))
		_widget_origin.y += 20.f;
}

void	Window::CalculateWidgetPositions()
{
	_widget_origin.x = _rect.x;
	_widget_origin.y = _rect.y + ((_flags & WindowFlags_NoMenubar) ? 0.f : 20.f);

	for (const auto& widget : _widgets)
	{
		widget->SetPosition(_widget_origin);

		math::vec2 widget_size = widget->GetSize();
		if (widget_size.x > _rect.w)
			_rect.w = widget_size.x + 10.f;
		if (widget_size.y > _rect.y)
			_rect.h = widget_size.y + 10.f;

		_widget_origin.y += state.glyph_size.y * state.scale * 2.5f;
	}

}

void	Window::Update()
{
	if (!(_flags & WindowFlags_NoMove))
	{
		if (GUI::IsMouseButtonPressed(Kinai::Mouse::ButtonLeft))
		{
			if (IsHovered())
			{
				GUI::SetActiveWindow(_id);
				state.mouse.left.pressed_handled = true;
				_dragging = true;
				Point mouse_pos = GUI::GetMousePosition();
				_drag_offset.x = mouse_pos.x - _rect.x;
				_drag_offset.y = mouse_pos.y - _rect.y;
			}
			else
				GUI::SetActiveWindow(0);
		}
		if (!GUI::IsMouseButtonDown(Kinai::Mouse::ButtonLeft))
			_dragging = false;
		if (_dragging)
		{
			GUI::SetMouseCursor(SDL_SYSTEM_CURSOR_MOVE);
			Point mouse_pos = GUI::GetMousePosition();
			_rect.x = mouse_pos.x - _drag_offset.x;
			_rect.y = mouse_pos.y - _drag_offset.y;
			CalculateWidgetPositions();
		}
	}
	if (_flags & WindowFlags_AlwaysAutoResize)
		CalculateWidgetPositions();
}

void	Window::Render() const
{
	if (!(_flags & WindowFlags_NoBorder))
		Painter::DrawQuad(_rect.x - 1, _rect.y - 1, _rect.w + 2, _rect.h + 2, math::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	Painter::DrawQuad(_rect.x, _rect.y, _rect.w, _rect.h, math::vec4(0.05f, 0.05f, 0.05f, 1.0f));
	if (!(_flags & WindowFlags_NoMenubar))
	{
		Painter::DrawQuad(_rect.x - 1, _rect.y - 1, _rect.w + 2, 18 + 2, math::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		Painter::DrawQuad(_rect.x, _rect.y, _rect.w, 18,
			IsActive() ? math::vec4(0.1f, 0.3f, 1.0f, 1.0f) : math::vec4(0.1f, 0.2f, 0.3f, 1.0f) );
		RenderText(_label.c_str(), _rect.x + 5.f, _rect.y + 3.f);
	}

	for (const auto& widget : _widgets)
		widget->Render();
}

} // GUI

} // Kinai
