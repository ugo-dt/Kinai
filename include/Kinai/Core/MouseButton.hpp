#pragma once

#include "Kinai/Core/Core.hpp"

namespace Kinai
{

using MouseButton = uint16_t;

namespace Mouse
{

enum : MouseButton
{
	Button0      = 0,
	Button1      = SDL_BUTTON_LEFT,
	Button2      = SDL_BUTTON_MIDDLE,
	Button3      = SDL_BUTTON_RIGHT,
	Button4      = SDL_BUTTON_X1,
	Button5      = SDL_BUTTON_X2,
	Button6      = 6,
	Button7      = 7,
	ButtonLast   = Button7,
	ButtonLeft   = Button1,
	ButtonMiddle = Button2,
	ButtonRight  = Button3,
	MouseButton_NUM
};

}

} // Kinai
