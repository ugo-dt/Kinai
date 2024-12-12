#pragma once

#include "Kinai/Core/Core.hpp"
#include "Kinai/Core/KeyCode.hpp"
#include "Kinai/Events/Event.hpp"

namespace Kinai
{

class KeyEvent : public Event
{
public:
	KeyCode GetKeyCode() const { return _key_code; }

	EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
protected:
	KeyEvent(const KeyCode keycode)
		: _key_code(keycode) {}

	KeyCode _key_code;
};

class KeyPressedEvent : public KeyEvent
{
public:
	KeyPressedEvent(const KeyCode keycode, bool repeat = false)
		: KeyEvent(keycode), _is_repeat(repeat) {}

	bool IsRepeat() const { return _is_repeat; }

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "KeyPressedEvent: " << _key_code << " (repeat = " << _is_repeat << ")";
		return ss.str();
	}

	EVENT_CLASS_TYPE(SDL_EVENT_KEY_DOWN)
private:
	bool _is_repeat;
};

class KeyReleasedEvent : public KeyEvent
{
public:
	KeyReleasedEvent(const KeyCode keycode)
		: KeyEvent(keycode) {}

	std::string ToString() const override
	{
		std::stringstream ss;
		ss << "KeyReleasedEvent: " << _key_code;
		return ss.str();
	}

	EVENT_CLASS_TYPE(SDL_EVENT_KEY_UP)
};

} // Kinai
