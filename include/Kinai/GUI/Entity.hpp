#pragma once

#include "Kinai/GUI/Core.hpp"

namespace Kinai
{

namespace GUI
{

class Entity
{
public:
	virtual float GetX() const;
	virtual float GetY() const;
	virtual glm::vec2 GetPosition() const;
	virtual float GetWidth() const;
	virtual float GetHeight() const;
	virtual glm::vec2 GetSize() const;
	virtual Rect GetRect() const;

	virtual void SetX(float x);
	virtual void SetY(float y);
	virtual void SetPosition(const glm::vec2& position);
	virtual void SetWidth(float width);
	virtual void SetHeight(float height);
	virtual void SetSize(float w, float h);
	virtual void SetSize(const glm::vec2& size);
	virtual void SetRect(const Rect& rect);
	
	virtual void OnEvent(Event& event);
	
	virtual bool Update() { return false; }

protected:
	Entity(Rect rect);
	virtual ~Entity() = default;

	virtual bool BaseUpdate(bool value_changed = false);

	virtual bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& event);
	virtual bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& event);
	virtual bool OnMouseMotionEvent(MouseMotionEvent& event);

protected:
	Rect _rect;
	bool _pressed = false;
	bool _down = false;
	bool _released = false;
	bool _hovered = false;
};

} // GUI

} // Kinai
