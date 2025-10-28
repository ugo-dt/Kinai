#include "Kinai/GUI/Widgets/Button.hpp"
#include "Kinai/GUI/State.hpp"

namespace Kinai
{

namespace GUI
{

WidgetButton::WidgetButton(Point position, const char* label, ButtonFlags flags)
	: Widget(position),
	  _label(""),
	  _flags(flags)
{
	Update(label, flags);
}

void	WidgetButton::UpdateSize()
{
	_rect.w = g_GuiState.glyph_size.x * _label.length() * g_GuiState.scale;
	_rect.h = g_GuiState.glyph_size.y * g_GuiState.scale * 2.f;
}

bool	WidgetButton::Update(const char* label, ButtonFlags flags)
{
	UpdateSize();
	_label = label;
	_flags = flags;
	if (IsDisabled())
		return false;
	if (_hovered)
		GUI::SetMouseCursor(SDL_SYSTEM_CURSOR_POINTER);
	return Entity::BaseUpdate(_released);
}

void	WidgetButton::Render() const
{
	math::vec4 button_color = IsDisabled()
		? g_GuiStyle.widget.button.disabledBackgroundColor
		: _down && _hovered
			? g_GuiStyle.widget.button.activeBackgroundColor
			: _hovered
				? g_GuiStyle.widget.button.hoverBackgroundColor
				: g_GuiStyle.widget.button.backgroundColor;

	Painter::DrawQuad(_rect.x - 1, _rect.y - 1, _rect.w + 2, _rect.h + 2, g_GuiStyle.widget.button.borderColor);
	Painter::DrawQuad(_rect.x, _rect.y, _rect.w, _rect.h, button_color);

	DebugText::Home();
	RenderText(_label.c_str(), _rect.x, _rect.y + _rect.h / 4.f);
}

} // GUI

} // Kinai
