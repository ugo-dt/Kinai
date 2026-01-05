#include "Kinai/GUI/Entity.hpp"
#include "Kinai/GUI/State.hpp"

namespace Kinai
{

namespace GUI
{

Entity::Entity(Rect rect): _rect(rect) {}

float Entity::GetX() const { return _rect.x; }
float Entity::GetY() const { return _rect.y; }
glm::vec2 Entity::GetPosition() const { return glm::vec2(GetX(), GetY()); }

float Entity::GetWidth() const { return _rect.w; }
float Entity::GetHeight() const { return _rect.h; }
glm::vec2 Entity::GetSize() const { return glm::vec2(GetWidth(), GetHeight()); }
Rect Entity::GetRect() const { return Rect{	GetX(), GetY(), GetWidth(), GetHeight() }; }

void Entity::SetX(float x) { _rect.x = x; }
void Entity::SetY(float y) { _rect.y = y; }
void Entity::SetPosition(const glm::vec2& position) { _rect.x = position.x; _rect.y = position.y; }
void Entity::SetWidth(float width) { _rect.w = width; }
void Entity::SetHeight(float height) { _rect.h = height; }
void Entity::SetSize(float w, float h) { _rect.w = w; _rect.h = h; }
void Entity::SetSize(const glm::vec2& size) { _rect.w = size.x; _rect.h = size.y; }
void Entity::SetRect(const Rect& rect) { _rect = rect; }

bool Entity::BaseUpdate(bool value_changed)
{
	_pressed = false;
	_released = false;
	return value_changed;
}

void Entity::OnEvent(Event& event)
{
	EventDispatcher dispatcher(event);

	dispatcher.Dispatch<MouseButtonPressedEvent>(KN_BIND_EVENT_FN(Entity::OnMouseButtonPressedEvent));
	dispatcher.Dispatch<MouseButtonReleasedEvent>(KN_BIND_EVENT_FN(Entity::OnMouseButtonReleasedEvent));
	dispatcher.Dispatch<MouseMotionEvent>(KN_BIND_EVENT_FN(Entity::OnMouseMotionEvent));
}

bool	Entity::OnMouseButtonPressedEvent(MouseButtonPressedEvent& event)
{
	if (!_hovered)
		return false;
	switch (event.GetButton())
	{
		case Kinai::Mouse::ButtonLeft:
			_pressed = true;
			_down = true;
			break;
		default:
			break;
	}
	return true;
}

bool	Entity::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& event)
{
	switch (event.GetButton())
	{
		case Kinai::Mouse::ButtonLeft:
			if (_hovered && _down)
				_released = true;
			_down = false;
			break;
		default:
			break;
	}
	return false;
}

bool	Entity::OnMouseMotionEvent(MouseMotionEvent& event)
{
	_hovered = PointInRect(Point(event.GetX(), event.GetY()), _rect);
	return false;
}

} // GUI

} // Kinai
