#include "Kinai/Core/Application.hpp"
#include "Kinai/Core/Input.hpp"

namespace Kinai
{

bool	Input::IsKeyPressed(KeyCode key)
{
	return SDL_GetKeyboardState(nullptr)[key];
}

bool	Input::IsMouseButtonPressed(MouseButton button)
{
	return SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON_MASK(button);
}

glm::vec2	Input::GetMousePosition()
{
	float xpos, ypos;

	SDL_GetMouseState(&xpos, &ypos);
	return glm::vec2(xpos, ypos);
}

float	Input::GetMouseX()
{
	return GetMousePosition().x;
}

float	Input::GetMouseY()
{
	return GetMousePosition().y;
}

}
