#pragma once

#include "Kinai/GUI/State.hpp"
#include "Kinai/GUI/Widgets/Widget.hpp"

namespace Kinai
{

namespace GUI
{

template <typename Tp>
class WidgetSlider : public Widget
{
public:
	WidgetSlider(Point position, const char* label, Tp* value, Tp min_value, Tp max_value);
	~WidgetSlider() = default;

	using Entity::Update;
	virtual bool Update(const char* label, Tp* value, Tp min_value, Tp max_value);

	void Render() const override;

	float GetWidth() const override { return _rect.w + GetRenderTextSize(_label.c_str()).x + g_GuiState.scale; }

private:
	std::string	_label;
	Rect _slider;
	Tp* _value;
	Tp _min_value;
	Tp _max_value;
	bool _dragging;
};

bool SliderFloat(const char* label, float* value, float min_value, float max_value);
bool SliderInt(const char* label, int* value, int min_value, int max_value);
bool SliderDouble(const char* label, double* value, double min_value, double max_value);
bool SliderUInt(const char* label, unsigned int* value, unsigned int min_value, unsigned int max_value);
bool SliderShort(const char* label, short* value, short min_value, short max_value);
bool SliderChar(const char* label, char* value, char min_value, char max_value);

template <typename Tp>
WidgetSlider<Tp>::WidgetSlider(Point position, const char* label, Tp* value, Tp min_value, Tp max_value)
	: Widget(position),
	  _label(label),
	  _slider{ 0, 0, 20.f, 20.f },
	  _value(value),
	  _min_value(min_value),
	  _max_value(max_value),
	  _dragging(false)
{
	SetSize(150.0f, 20.f);
	Update(label, value, min_value, max_value);
}

template <typename Tp>
bool
WidgetSlider<Tp>::Update(const char* label, Tp* value, Tp min_value, Tp max_value)
{
	KN_ASSERT(_value != nullptr);

	Tp old_value = *value;

	_label = label;
	_value = value;
	_min_value = min_value;
	_max_value = max_value;

	_dragging = _dragging ? _down : _down && _hovered;

	if (_hovered || _dragging)
		GUI::SetMouseCursor(SDL_SYSTEM_CURSOR_POINTER);
	if (_dragging)
	{
		Point mouse_pos = GUI::GetMousePosition();
		float relative_x = mouse_pos.x - _rect.x;
		if (relative_x < 0.f) relative_x = 0.f;
		if (relative_x > _rect.w) relative_x = _rect.w;
		float t = relative_x / _rect.w;
		*_value = static_cast<Tp>(_min_value + t * (_max_value - _min_value));
		if (*_value < _min_value) *_value = _min_value;
		if (*_value > _max_value) *_value = _max_value;
	}
	_slider.x = _rect.x + ((_rect.w - _slider.w) * ((*_value - _min_value) / (_max_value - _min_value)));
	_slider.y = _rect.y;
	return Entity::BaseUpdate(old_value != *value);
}

template <typename Tp>
void
WidgetSlider<Tp>::Render() const
{
	math::vec4 bg_color = _hovered || _dragging ?
		g_GuiStyle.widget.slider.hoverBackgroundColor : g_GuiStyle.widget.slider.backgroundColor;
	math::vec4 border_color = g_GuiStyle.widget.slider.borderColor;
	math::vec4 slider_color =
		_dragging ? g_GuiStyle.widget.slider.sliderActiveColor
		          : _hovered
		              ? g_GuiStyle.widget.slider.sliderHoverColor
		              : g_GuiStyle.widget.slider.sliderColor;

	Painter::DrawQuad(_rect.x - 1, _rect.y - 1, _rect.w + 2, _rect.h + 2, border_color);
	Painter::DrawQuad(_rect.x, _rect.y, _rect.w, _rect.h, bg_color);

	Painter::DrawQuad(_slider.x - 1, _slider.y - 1, _slider.w + 2, _slider.h + 2, border_color);
	Painter::DrawQuad(_slider.x, _slider.y, _slider.w, _slider.h, slider_color);

	DebugText::Home();
	RenderText(_label.c_str(), _rect.x + _rect.w + g_GuiState.scale, _rect.y + _rect.h / 4.f);
}

} // GUI

} // Kinai
