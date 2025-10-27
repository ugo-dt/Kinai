#pragma once

#include "Kinai/Core/Core.hpp"

namespace Kinai
{

namespace GUI
{

struct WindowStyle
{
	float borderWidth = 1.0f;

	math::vec4 backgroundColor = math::vec4(0.1f, 0.1f, 0.1f, 1.0f);
	math::vec4 borderColor = math::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	math::vec4 textColor = math::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	float titleBarHeight = 20.0f;
	math::vec4 titleBarColor = math::vec4(0.2f, 0.2f, 0.8f, 1.0f);
	math::vec4 titleBarTextColor = math::vec4(1.0f, 1.0f, 1.0f, 1.0f);
};

struct WidgetStyle
{
	struct Button
	{
		math::vec4 backgroundColor = math::vec4(0.2f, 0.2f, 0.8f, 1.0f);
		math::vec4 disabledBackgroundColor = math::vec4(0.3f, 0.3f, 0.3f, 1.0f);
		math::vec4 hoverBackgroundColor = math::vec4(0.3f, 0.3f, 0.8f, 1.0f);
		math::vec4 activeBackgroundColor = math::vec4(0.1f, 0.1f, 0.8f, 1.0f);
		math::vec4 borderColor = math::vec4(0.7f, 0.7f, 1.0f, 1.0f);
		math::vec4 textColor = math::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	}button;

	struct Slider
	{
		math::vec4 backgroundColor = math::vec4(0.1f, 0.1f, 0.1f, 1.0f);
		math::vec4 hoverBackgroundColor = math::vec4(0.2f, 0.2f, 0.2f, 1.0f);
		math::vec4 borderColor = math::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		math::vec4 textColor = math::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		math::vec4 sliderColor = math::vec4(0.2f, 0.2f, 0.8f, 1.0f);
		math::vec4 sliderHoverColor = math::vec4(0.4f, 0.4f, 1.0f, 1.0f);
		math::vec4 sliderActiveColor = math::vec4(0.1f, 0.1f, 0.8f, 1.0f);
	}slider;

	struct Text
	{
		math::vec4 color = math::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	}text;
};

struct Style
{
	WindowStyle window;
	WidgetStyle widget;
};


} // GUI


} // Kinai
