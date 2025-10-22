#pragma once

#include "Kinai/GUI/GUI.hpp"

namespace Kinai
{

namespace GUI
{

class Widget
{
public:
	Widget(Point position): _position(position) {}
	virtual ~Widget() = default;

	void SetPosition(const Point& position) { _position = position; }

	virtual float GetWidth() const { return 0.f; }
	virtual float GetHeight() const { return 0.f; }
	virtual math::vec2 GetSize() const { return math::vec2(GetWidth(), GetHeight()); }

	virtual bool Update() { return false; }
	virtual void Render() const = 0;

protected:
	Point _position;
};

} // GUI

} // Kinai
