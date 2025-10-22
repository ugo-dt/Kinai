#pragma once

#include "Kinai/Core/Core.hpp"
#include "Kinai/Events/Event.hpp"
#include "Kinai/Renderer/2D/Painter.hpp"

namespace Kinai
{

namespace GUI
{

using Point = math::vec2;
struct Rect { float x, y, w, h; };

static KN_INLINE KN_UNUSED bool PointInRect(const Point& point, const Rect& rect)
{
	return (point.x >= rect.x && point.x <= rect.x + rect.w &&
			point.y >= rect.y && point.y <= rect.y + rect.h);
}

void CreateContext();
void DestroyContext();
void NewFrame();
void Render();
bool OnEvent(Event& event);

void Begin(const char* label, bool* is_open = nullptr);
void End();

} // GUI

} // Kinai
