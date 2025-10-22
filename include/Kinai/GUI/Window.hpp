#pragma once

#include "Kinai/Core/Core.hpp"
#include "Kinai/GUI/GUI.hpp"
#include "Kinai/Debug/Text/Text.hpp"

namespace Kinai
{

namespace GUI
{

enum WindowFlags_ : uint32_t
{
	WindowFlags_None = 0,
	WindowFlags_NoMenubar = 1 << 0,
	WindowFlags_NoResize = 1 << 1,
	WindowFlags_NoMove = 1 << 2,
	WindowFlags_NoCollapse = 1 << 3,
};

using WindowFlags = uint32_t;

class Window
{
public:
	Window(const char* label, Rect rect, bool* is_open, WindowFlags flags = 0);
	~Window() = default;

	bool IsOpen() const { return _is_open ? *_is_open : true; }
	// bool IsHovered() const { return PointInRect({ state.mouse.x, state.mouse.y }, _rect); }

	void Render() const;

private:
	Rect _rect;
	std::string _label;
	bool* _is_open;
	WindowFlags _flags;
};

} // GUI


} // Kinai
