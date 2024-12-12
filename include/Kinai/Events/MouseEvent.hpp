#pragma once

#include "Kinai/Core/Core.hpp"
#include "Kinai/Core/MouseButton.hpp"
#include "Kinai/Events/Event.hpp"

namespace Kinai
{

class MouseMotionEvent : public Event
{
public:
	MouseMotionEvent(const float x, const float y, const float rel_x, const float rel_y)
		: _mouse_x(x), _mouse_y(y), _delta_x(rel_x), _delta_y(rel_y) {}
	
	float	GetX()         const { return _mouse_x; }
	float	GetY()         const { return _mouse_y; }
	float	GetXRelative() const { return _delta_x; }
	float	GetYRelative() const { return _delta_y; }

	EVENT_CLASS_TYPE(SDL_EVENT_MOUSE_MOTION);
	EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);

	std::string	ToString() const override
	{
		std::stringstream ss;
		ss << "MouseMotionEvent: " << _mouse_x << ", " << _mouse_y;
		return ss.str();
	}

private:
	float _mouse_x, _mouse_y;
	float _delta_x, _delta_y;
};

class MouseWheelEvent : public Event
{
public:
	MouseWheelEvent(const float x, const float y)
		: _wheel_x(x), _wheel_y(y) {}
	
	float	GetXOffset() const { return _wheel_x; }
	float	GetYOffset() const { return _wheel_y; }

	EVENT_CLASS_TYPE(SDL_EVENT_MOUSE_WHEEL);
	EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput);

	std::string	ToString() const override
	{
		std::stringstream ss;
		ss << "MouseWheelEvent: " << _wheel_x << ", " << _wheel_y;
		return ss.str();
	}

private:
	float _wheel_x, _wheel_y;
};

class MouseButtonEvent : public Event
{
public:
	MouseButtonEvent();

	MouseButton	GetButton() const { return _button; }

	EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput | EventCategoryMouseButton);

protected:
	MouseButtonEvent(const MouseButton button)
		: _button(button) {}
	
	MouseButton _button;
};

class MouseButtonPressedEvent : public MouseButtonEvent
{
public:
	MouseButtonPressedEvent(const MouseButton button)
		: MouseButtonEvent(button) {}

	EVENT_CLASS_TYPE(SDL_EVENT_MOUSE_BUTTON_DOWN);

	std::string	ToString() const override
	{
		std::stringstream ss;
		ss << "MouseButtonPressedEvent: " << this->_button;
		return ss.str();
	}
};

class MouseButtonReleasedEvent : public MouseButtonEvent
{
public:
	MouseButtonReleasedEvent(const MouseButton button)
		: MouseButtonEvent(button) {}

	EVENT_CLASS_TYPE(SDL_EVENT_MOUSE_BUTTON_UP);

	std::string	ToString() const override
	{
		std::stringstream ss;
		ss << "MouseButtonReleasedEvent: " << this->_button;
		return ss.str();
	}
};

} // Kinai
