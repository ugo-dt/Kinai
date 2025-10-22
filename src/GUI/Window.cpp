#include "Kinai/GUI/Window.hpp"

namespace Kinai
{

namespace GUI
{

Window::Window(const char* label, Rect rect, bool* is_open, WindowFlags flags)
	: _rect(rect),
	  _label(label),
	  _is_open(is_open),
	  _flags(flags)
{
}

void	Window::Render() const
{
	Painter::DrawQuad(_rect.x - 1, _rect.y - 1, _rect.w + 2, _rect.h + 2, math::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	Painter::DrawQuad(_rect.x, _rect.y, _rect.w, _rect.h, math::vec4(0.05f, 0.05f, 0.05f, 1.0f));
	if (!(_flags & WindowFlags_NoMenubar))
	{
		Painter::DrawQuad(_rect.x - 1, _rect.y - 1, _rect.w + 2, 18 + 2, math::vec4(1.0f, 1.0f, 1.0f, 1.0f));
		Painter::DrawQuad(_rect.x, _rect.y, _rect.w, 18, math::vec4(0.1f, 0.3f, 1.0f, 1.0f));
		math::vec2 origin(
			_rect.x / 16.f,
			_rect.y / 16.f + 1.f
		);
		DebugText::SetOrigin(origin.x, origin.y);
		DebugText::Put(_label.c_str());
	}
}

} // GUI


} // Kinai
