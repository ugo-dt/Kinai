#pragma once

#include "Kinai/GUI/Core.hpp"

namespace Kinai
{

namespace GUI
{

bool OnWindowResizeEvent(WindowResizeEvent &event);
bool OnMouseMotionEvent(MouseMotionEvent &event);
bool OnMouseButtonPressedEvent(MouseButtonPressedEvent &event);
bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent &event);

} // GUI

} // Kinai
