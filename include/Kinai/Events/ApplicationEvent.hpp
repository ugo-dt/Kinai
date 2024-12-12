#pragma once

#include "Kinai/Core/Core.hpp"
#include "Kinai/Events/Event.hpp"

namespace Kinai
{

class WindowResizeEvent : public Event
{
public:
	WindowResizeEvent(uint32_t width, uint32_t height)
		: _width(width), _height(height) {}
	
	uint32_t	GetWidth() { return _width; }
	uint32_t	GetHeight() { return _height; }

	std::string	ToString() const override
	{
		std::stringstream ss;
		ss << "WindowResizeEvent: " << _width << ", " << _height;
		return ss.str();
	}

	EVENT_CLASS_TYPE(SDL_EVENT_WINDOW_RESIZED);
	EVENT_CLASS_CATEGORY(EventCategoryApplication);

private:
	uint32_t	_width, _height;

};

class WindowCloseEvent : public Event
{
public:
	WindowCloseEvent() = default;

	EVENT_CLASS_TYPE(SDL_EVENT_WINDOW_CLOSE_REQUESTED);
	EVENT_CLASS_CATEGORY(EventCategoryApplication);
};

class AppTickEvent : public Event
{
public:
	AppTickEvent() = default;

	EVENT_CLASS_TYPE(KN_EVENT_WINDOW_TICK)
	EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class AppUpdateEvent : public Event
{
public:
	AppUpdateEvent() = default;

	EVENT_CLASS_TYPE(KN_EVENT_WINDOW_UPDATE)
	EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class AppRenderEvent : public Event
{
public:
	AppRenderEvent() = default;

	EVENT_CLASS_TYPE(KN_EVENT_WINDOW_RENDER)
	EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

} // Kinai
