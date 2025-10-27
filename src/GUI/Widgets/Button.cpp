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
	  _rect()
{
	UpdatePosition();
	UpdateSize();
	Update(label, flags);
}

bool	WidgetButton::IsHovered() const
{
	return GUI::IsMouseHovering(_rect);
}

bool	WidgetButton::IsClicked() const
{
	bool clicked = btn.released && IsHovered();
	return clicked;
}

bool	WidgetButton::IsDisabled() const
{
	return _flags & ButtonFlags_Disabled;
}

void	WidgetButton::UpdatePosition()
{
	_rect.x = _position.x;
	_rect.y = _position.y;
}

void	WidgetButton::UpdateSize()
{
	_rect.w = g_GuiState.glyph_size.x * _label.length() * g_GuiState.scale;
	_rect.h = g_GuiState.glyph_size.y * g_GuiState.scale * 2.f;
}

bool	WidgetButton::BaseUpdate(const char* label, ButtonFlags flags)
{
	UpdatePosition();
	UpdateSize();
	_label = label;
	_flags = flags;

	bool hovered = IsHovered();
	bool disabled = IsDisabled();
	if (hovered && !disabled)
		GUI::SetMouseCursor(SDL_SYSTEM_CURSOR_POINTER);
	if (disabled)
		return false;
	
	if (!hovered)
	{
		btn.pressed = false;
		btn.released = false;
		return false;
	}

	if (btn.pressed)
		btn.pressed = false;
	if (btn.released)
		btn.released = false;

	bool mouse_pressed = GUI::IsMouseButtonPressed(Kinai::Mouse::ButtonLeft);
	bool mouse_released = GUI::IsMouseButtonReleased(Kinai::Mouse::ButtonLeft);

	if (mouse_pressed && hovered)
	{
		g_GuiState.mouse.left.pressed_handled = true;
		btn.pressed = true;
		btn.down = true;
	}

	if (mouse_released)
	{
		g_GuiState.mouse.left.released_handled = true;
		if (btn.down)
			btn.released = true;
		btn.down = false;
	}
	return IsClicked();
}

bool	WidgetButton::Update(const char* label, ButtonFlags flags)
{
	if (BaseUpdate(label, flags))
	{
		OnClick();
		return true;
	}
	return false;
}

void	WidgetButton::Render() const
{
	bool hovered = IsHovered();
	bool down = GUI::IsMouseButtonDown(Kinai::Mouse::ButtonLeft);
	math::vec4 button_color = IsDisabled()
		? g_GuiStyle.widget.button.disabledBackgroundColor
		: down && btn.down && hovered
			? g_GuiStyle.widget.button.activeBackgroundColor
			: hovered
				? g_GuiStyle.widget.button.hoverBackgroundColor
				: g_GuiStyle.widget.button.backgroundColor;

	Painter::DrawQuad(_rect.x - 1, _rect.y - 1, _rect.w + 2, _rect.h + 2, g_GuiStyle.widget.button.borderColor);
	Painter::DrawQuad(_rect.x, _rect.y, _rect.w, _rect.h, button_color);

	DebugText::Home();
	RenderText(_label.c_str(), _position.x, _position.y + _rect.h / 4.f);
}

} // GUI

} // Kinai
