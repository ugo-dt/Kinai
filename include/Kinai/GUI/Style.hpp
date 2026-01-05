#pragma once

#include "Kinai/Core/Core.hpp"

namespace Kinai
{

namespace GUI
{

struct WindowStyle
{
	float borderWidth = 1.0f;

	glm::vec4 backgroundColor = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
	glm::vec4 borderColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec4 textColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

	float titleBarHeight = 20.0f;
	glm::vec4 titleBarColor = glm::vec4(0.2f, 0.2f, 0.8f, 1.0f);
	glm::vec4 titleBarTextColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
};

struct WidgetStyle
{
	struct Button
	{
		glm::vec4 backgroundColor = glm::vec4(0.2f, 0.2f, 0.8f, 1.0f);
		glm::vec4 disabledBackgroundColor = glm::vec4(0.3f, 0.3f, 0.3f, 1.0f);
		glm::vec4 hoverBackgroundColor = glm::vec4(0.3f, 0.3f, 0.8f, 1.0f);
		glm::vec4 activeBackgroundColor = glm::vec4(0.1f, 0.1f, 0.8f, 1.0f);
		glm::vec4 borderColor = glm::vec4(0.7f, 0.7f, 1.0f, 1.0f);
		glm::vec4 textColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	}button;

	struct Slider
	{
		glm::vec4 backgroundColor = glm::vec4(0.1f, 0.1f, 0.1f, 1.0f);
		glm::vec4 hoverBackgroundColor = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
		glm::vec4 borderColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		glm::vec4 textColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
		glm::vec4 sliderColor = glm::vec4(0.2f, 0.2f, 0.8f, 1.0f);
		glm::vec4 sliderHoverColor = glm::vec4(0.4f, 0.4f, 1.0f, 1.0f);
		glm::vec4 sliderActiveColor = glm::vec4(0.1f, 0.1f, 0.8f, 1.0f);
	}slider;

	struct Text
	{
		glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	}text;
};

struct Style
{
	WindowStyle window;
	WidgetStyle widget;
};

} // GUI

} // Kinai
