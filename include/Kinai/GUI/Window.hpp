#pragma once

#include "Kinai/GUI/Core.hpp"
#include "Kinai/GUI/Widgets/Widget.hpp"
#include "Kinai/GUI/State.hpp"

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
	WindowFlags_NoBorder = 1 << 4,
	WindowFlags_AlwaysAutoResize = 1 << 5,
};

using WindowFlags = uint32_t;

class Window : public Entity
{
public:
	Window(const char* label, uint32_t id, Rect rect, bool* is_open, WindowFlags flags = 0);
	~Window() = default;

	uint32_t GetID() const;
	Rect GetRect() const { return _rect; }

	bool IsOpen() const;
	bool IsHovered() const;
	bool IsActive() const;

	bool Update();
	void Render() const;
	void OnEvent(Event& event);

	template <typename WidgetType, typename... Args>
	bool AddWidget(uint32_t id, Args&&... args);

	void CalculateWidgetPositions();

private:
	uint32_t _id;
	std::string _label;
	bool* _is_open;
	WindowFlags _flags;
	std::vector<Ref<Widget>> _widgets;
	Point _widget_origin;
	Point _drag_offset;
};

void Begin(const char* label, bool* is_open = nullptr, WindowFlags flags = 0);
void End();
void SetNextWindowPos(const math::ivec2& pos);

#include "Kinai/GUI/State.hpp"

template <typename WidgetType, typename... Args>
bool Window::AddWidget(uint32_t id, Args&&... args)
{
	State& state = GetState();

	if (id < _widgets.size())
	{
		WidgetType* widget = dynamic_cast<WidgetType*>(_widgets[id].get());
		if (widget)
			return widget->Update(std::forward<Args>(args)...);
		return _widgets[id]->Update();
	}

	_widgets.emplace_back(CreateRef<WidgetType>(
		_widget_origin, std::forward<Args>(args)...
	));
	Ref<Widget>& w = _widgets.back();
	_widget_origin.y += state.glyph_size.y * state.scale * 4.f;
	return static_cast<WidgetType*>(w.get())->Update(std::forward<Args>(args)...);
}

} // GUI

} // Kinai
