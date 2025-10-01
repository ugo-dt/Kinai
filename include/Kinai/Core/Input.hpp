#pragma once

#include "Kinai/Core/Core.hpp"
#include "Kinai/Core/KeyCode.hpp"
#include "Kinai/Core/MouseButton.hpp"

namespace Kinai
{

class Input
{
public:
	static bool IsKeyPressed(KeyCode key);
	static bool IsMouseButtonPressed(MouseButton button);
	static glm::vec2 GetMousePosition();
	static float GetMouseX();
	static float GetMouseY();
};

}
