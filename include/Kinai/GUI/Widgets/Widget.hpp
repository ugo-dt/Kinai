#pragma once

#include "Kinai/GUI/Core.hpp"
#include "Kinai/GUI/State.hpp"
#include "Kinai/GUI/Entity.hpp"

namespace Kinai
{

namespace GUI
{

class Widget : public Entity
{
public:
	Widget(Point position): Entity({position.x, position.y, 0.f, 0.f}) {}
	virtual ~Widget() = default;

	virtual void Render() const = 0;
};

} // GUI

} // Kinai
