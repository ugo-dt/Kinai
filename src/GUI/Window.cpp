#include "Kinai/GUI/Window.hpp"
#include "Kinai/GUI/State.hpp"

namespace Kinai
{

namespace GUI
{

Window::Window(const char* label, uint32_t id, Rect rect, bool* is_open, WindowFlags flags)
	: Entity(rect),
	  _id(id),
	  _label(label),
	  _is_open(is_open),
	  _flags(flags),
	  _widget_origin(rect.x, rect.y)
{
	if (!(_flags & WindowFlags_NoMenubar))
		_widget_origin.y += 20.f;
}

uint32_t	Window::GetID() const
{
	return _id;
}

bool	Window::IsOpen() const
{
	return _is_open ? *_is_open : true;
}

bool	Window::IsHovered() const
{
	return GUI::IsMouseHovering(_rect);
}

bool	Window::IsActive() const
{
	return g_GuiState.active_window && g_GuiState.active_window->GetID() == _id;
}

void	Window::CalculateWidgetPositions()
{
	_widget_origin.x = _rect.x + 5.f;
	_widget_origin.y = _rect.y + ((_flags & WindowFlags_NoMenubar) ? 0.f : 20.f);
	
	float max_widget_width = 0.f;
	for (const auto& widget : _widgets)
	{
		widget->SetPosition(_widget_origin);

		glm::vec2 widget_size = widget->GetSize();
		if (widget_size.x > max_widget_width)
			max_widget_width = widget_size.x + 20.f * g_GuiState.scale;
		_widget_origin.y += 25.f * g_GuiState.scale;
	}

	if (_flags & WindowFlags_AlwaysAutoResize)
	{
		_rect.w = max_widget_width;
		_rect.h = _widget_origin.y - _rect.y;
		if (_rect.w == 0.f) _rect.w = 50.f;
		if (_rect.h == 0.f) _rect.h = 50.f;
	}
}

bool	Window::Update()
{
	if (!(_flags & WindowFlags_NoMove))
	{
		if (_pressed)
		{
			if (_hovered)
			{
				GUI::SetActiveWindow(_id);
				Point mouse_pos = GUI::GetMousePosition();
				_drag_offset.x = mouse_pos.x - _rect.x;
				_drag_offset.y = mouse_pos.y - _rect.y;
			}
			else
				GUI::SetActiveWindow(0);
		}
		if (_down)
		{
			GUI::LockCursor();
			GUI::SetMouseCursor(SDL_SYSTEM_CURSOR_MOVE);
			Point mouse_pos = GUI::GetMousePosition();
			_rect.x = mouse_pos.x - _drag_offset.x;
			_rect.y = mouse_pos.y - _drag_offset.y;
			CalculateWidgetPositions();
		}
		else
			GUI::UnlockCursor();
	}
	CalculateWidgetPositions();
	return Entity::BaseUpdate();
}

void	Window::Render() const
{
	if (!(_flags & WindowFlags_NoBorder))
		Painter::DrawQuad(_rect.x - 1, _rect.y - 1, _rect.w + 2, _rect.h + 2, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	Painter::DrawQuad(_rect.x, _rect.y, _rect.w, _rect.h, glm::vec4(0.05f, 0.05f, 0.05f, 1.0f));
	if (!(_flags & WindowFlags_NoMenubar))
	{
		Painter::DrawQuad(_rect.x - 1, _rect.y - 1, _rect.w + 2, 18 + 2, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		Painter::DrawQuad(_rect.x, _rect.y, _rect.w, 18,
			IsActive() ? glm::vec4(0.1f, 0.3f, 1.0f, 1.0f) : glm::vec4(0.1f, 0.2f, 0.3f, 1.0f) );
		RenderText(_label.c_str(), _rect.x + 5.f, _rect.y + GetRenderTextSize(_label.c_str()).y / 2.f);
	}

	for (const auto& widget : _widgets)
		widget->Render();
}

void	Window::OnEvent(Event& event)
{
	for (const auto& widget : _widgets)
	{
		widget->OnEvent(event);
		if (event.handled)
			return ;
	}
	Entity::OnEvent(event);
}

} // GUI

} // Kinai
