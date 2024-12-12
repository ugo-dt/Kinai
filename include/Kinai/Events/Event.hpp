#pragma once

#include "Kinai/Core/Core.hpp"

namespace Kinai
{

using EG_EventType = uint32_t;

enum EventCategory
{
	EventCategoryNone = 0,
	EventCategoryApplication    = BIT(0),
	EventCategoryInput          = BIT(1),
	EventCategoryKeyboard       = BIT(2),
	EventCategoryMouse          = BIT(3),
	EventCategoryMouseButton    = BIT(4)
};

enum EG_CustomEventType : EG_EventType
{
	EG_EVENT_WINDOW_TICK = SDL_EVENT_USER,
	EG_EVENT_WINDOW_UPDATE,
	EG_EVENT_WINDOW_RENDER,
	EG_EVENT_LAST,
};

static_assert((uint32_t)EG_EVENT_LAST < (uint32_t)SDL_EVENT_LAST);

#define EG_CUSTOM_EVENT_TYPE_COUNT	((uint32_t)EG_EVENT_LAST - (uint32_t)SDL_EVENT_USER)

#define EVENT_CLASS_TYPE(type) static EG_EventType GetStaticType() { return type; }\
								virtual EG_EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

class Event
{
public:
	virtual ~Event() = default;

	bool 		handled = false;

	virtual EG_EventType GetEventType() const = 0;
	virtual const char* GetName() const = 0;
	virtual int GetCategoryFlags() const = 0;
	virtual std::string ToString() const { return GetName(); }

	bool IsInCategory(EventCategory category)
	{
		return GetCategoryFlags() & category;
	}
};

class EventDispatcher
{
public:
	EventDispatcher(Event& event)
		: _event(event) {}
	
	// F will be deduced by the compiler
	template<typename T, typename F>
	bool Dispatch(const F& func)
	{
		if (_event.GetEventType() == T::GetStaticType())
		{
			_event.handled |= func(static_cast<T&>(_event));
			return true;
		}
		return false;
	}
private:
	Event& _event;
};

inline std::ostream&	operator<<(std::ostream& os, const Event& e)
{
	return os << e.ToString();
}

} // Kinai
