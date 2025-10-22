#include "Kinai/GUI/Widgets/Button.hpp"
#include "Kinai/GUI/State.hpp"

namespace Kinai
{

namespace GUI
{

WidgetButton::WidgetButton(Point position, const char* label, ButtonFlags flags)
	: Widget(position),
	  _label(""),
	  _flags(flags),
	  _rect({
		_position.x, _position.y,
		0, 0
	  })
{
	Update(label, flags);
}

bool WidgetButton::IsHovered() const
{
	return GUI::IsMouseHovering(_rect);
}

bool WidgetButton::IsClicked() const
{
	bool clicked = !_pressed && IsHovered() && GUI::IsMouseButtonReleased(Kinai::Mouse::ButtonLeft);
	if (clicked)
		state.mouse.left.released_handled = true;
	return clicked;
}

bool WidgetButton::IsDisabled() const
{
	return _flags & ButtonFlags_Disabled;
}

bool	WidgetButton::Update(const char* label, ButtonFlags flags)
{
	_rect.x = _position.x;
	_rect.y = _position.y;
	if (_label != label)
	{
		_label = label;
		_rect.w = state.glyph_size.x * _label.length() * state.scale;
		_rect.h = state.glyph_size.y * state.scale * 2.f;
	}
	_flags = flags;

	bool hovered = IsHovered();
	bool disabled = IsDisabled();
	if (hovered && !disabled)
		GUI::SetMouseCursor(SDL_SYSTEM_CURSOR_POINTER);
	if (disabled)
		return false;
	_pressed = hovered && GUI::IsMouseButtonPressed(Kinai::Mouse::ButtonLeft);
	if (_pressed)
		state.mouse.left.pressed_handled = true;
	return IsClicked();
}

void	WidgetButton::Render() const
{
	math::vec4 button_color = IsDisabled() ? math::vec4(0.3f, 0.3f, 0.3f, 1.0f)
		: IsHovered() ? math::vec4(0.3f, 0.3f, 0.8f, 1.0f) : math::vec4(0.2f, 0.2f, 0.8f, 1.0f);

	Painter::DrawQuad(_rect.x, _rect.y, _rect.w, _rect.h, button_color);
	DebugText::Home();
	RenderText(_label.c_str(), _position.x, _position.y + _rect.h / 4.f);
}

} // GUI

} // Kinai
