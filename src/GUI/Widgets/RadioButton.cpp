#include "Kinai/GUI/Widgets/RadioButton.hpp"
#include "Kinai/GUI/State.hpp"

namespace Kinai
{

namespace GUI
{

WidgetRadioButton::WidgetRadioButton(Point position, const char* label, int* value, int button_value, ButtonFlags flags)
	: WidgetButton(position, label, flags),
	  _value(value),
	  _button_value(button_value)
{
	Update(label, value, button_value, flags);
}

void	WidgetRadioButton::UpdateSize()
{
    _rect.w = 20.f;
    _rect.h = 20.f;
}

bool	WidgetRadioButton::Update(const char* label, int* value, int button_value, ButtonFlags flags)
{
    _value = value;
    _button_value = button_value;
    return WidgetButton::Update(label, flags);
}

void	WidgetRadioButton::OnClick()
{
    if (_value)
        *_value = _button_value;
}

void	WidgetRadioButton::Render() const
{
	KN_ASSERT(_value != nullptr);

	bool hovered = IsHovered();
	bool down = GUI::IsMouseButtonDown(Kinai::Mouse::ButtonLeft);

	Painter::DrawQuad(_rect.x - 1, _rect.y - 1, _rect.w + 2, _rect.h + 2, g_GuiStyle.widget.button.borderColor);

	if (IsDisabled())
		Painter::DrawQuad(_rect.x, _rect.y, _rect.w, _rect.h, g_GuiStyle.widget.button.disabledBackgroundColor);
	else
	{
		Painter::DrawQuad(_rect.x, _rect.y, _rect.w, _rect.h, g_GuiStyle.window.backgroundColor);
		float halfw = _rect.w / 2.f;
		float halfh = _rect.h / 2.f;
		if (*_value == _button_value)
		{
			Painter::DrawQuad(_rect.x + halfw / 2.f, _rect.y + halfh / 2.f, halfw, halfh,
				g_GuiStyle.widget.button.backgroundColor);
		}
		else if (hovered)
		{
			if (down)
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
	RenderText(_label.c_str(), _position.x + _rect.w, _position.y + _rect.h / 4.f);
}

} // GUI

} // Kinai
