#include "Kinai/Core/Application.hpp"
#include "Kinai/Core/Input.hpp"

namespace Kinai
{

bool	Input::IsKeyPressed(KeyCode key)
{
	KN_NOTUSED(key);

	return false;
}

bool	Input::IsMouseButtonPressed(MouseButton button)
{
	KN_NOTUSED(button);

	return false;
}

glm::vec2	Input::GetMousePosition()
{
	return {0, 0};
}

float	Input::GetMouseX()
{
	return 0.f;
}

float	Input::GetMouseY()
{
	return 0.f;
}

}
