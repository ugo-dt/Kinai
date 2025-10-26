#include "Kinai/GUI/Widgets/Text.hpp"
#include "Kinai/GUI/State.hpp"

namespace Kinai
{

namespace GUI
{

WidgetText::WidgetText(Point position, const char* text)
	: Widget(position),
	  _text(text)
{
}

bool	WidgetText::Update(const char* text)
{
	_text = text;
	return false;
}

void	WidgetText::Render() const
{
	DebugText::Home();
	RenderText(_text.c_str(), _position.x, _position.y + g_GuiState.glyph_size.y);
}

float	WidgetText::GetWidth() const
{
	return GetRenderTextSize(_text.c_str()).x;
}

float	WidgetText::GetHeight() const
{
	return GetRenderTextSize(_text.c_str()).y;
}

} // GUI

} // Kinai
