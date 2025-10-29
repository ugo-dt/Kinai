#include "Kinai/GUI/Widgets/Checkbox.hpp"
#include "Kinai/GUI/State.hpp"

namespace Kinai
{

namespace GUI
{

WidgetCheckbox::WidgetCheckbox(Point position, const char* label, bool* value, ButtonFlags flags)
	: WidgetButton(position, label, flags),
	  _value(value)
{
	Update(label, value, flags);
}

void	WidgetCheckbox::UpdateSize()
{
    _rect.w = 20.f;
    _rect.h = 20.f;
}

bool	WidgetCheckbox::Update(const char* label, bool* value, ButtonFlags flags)
{
    _value = value;
	bool value_changed = WidgetButton::Update(label, flags);
	if (value_changed && _value)
        *_value = !*_value;
	return value_changed;
}

void	WidgetCheckbox::Render() const
{
	KN_ASSERT(_value != nullptr);

	Painter::DrawQuad(_rect.x - 1, _rect.y - 1, _rect.w + 2, _rect.h + 2, g_GuiStyle.widget.button.borderColor);

	if (IsDisabled())
		Painter::DrawQuad(_rect.x, _rect.y, _rect.w, _rect.h, g_GuiStyle.widget.button.disabledBackgroundColor);
	else
	{
		Painter::DrawQuad(_rect.x, _rect.y, _rect.w, _rect.h, g_GuiStyle.window.backgroundColor);
		float halfw = _rect.w / 2.f;
		float halfh = _rect.h / 2.f;
		if (*_value == true)
		{
			Painter::DrawQuad(_rect.x + halfw / 2.f, _rect.y + halfh / 2.f, halfw, halfh,
				g_GuiStyle.widget.button.backgroundColor);
		}
		else if (_hovered)
		{
			if (_down)
				Painter::DrawQuad(_rect.x + halfw / 2.f, _rect.y + halfh / 2.f, halfw, halfh,
					g_GuiStyle.widget.button.activeBackgroundColor);
			else
				Painter::DrawQuad(_rect.x + halfw / 2.f, _rect.y + halfh / 2.f, halfw, halfh,
					g_GuiStyle.widget.button.hoverBackgroundColor);
		}
		else
			Painter::DrawQuad(_rect.x, _rect.y, _rect.w, _rect.h, g_GuiStyle.window.backgroundColor);
	}
	DebugText::Home();
	RenderText(_label.c_str(), _rect.x + _rect.w + g_GuiState.scale, _rect.y + _rect.h / 4.f);
}

} // GUI

} // Kinai
