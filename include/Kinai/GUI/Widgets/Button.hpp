#pragma once

#include "Kinai/GUI/Widgets/Widget.hpp"

namespace Kinai
{

namespace GUI
{

enum ButtonFlags_ : uint32_t
{
	ButtonFlags_None = 0,
	ButtonFlags_Disabled = 1 << 0,
};

using ButtonFlags = uint32_t;

class WidgetButton : public Widget
{
public:
	WidgetButton(Point position, const char* label, ButtonFlags flags = 0);
	~WidgetButton() = default;

	using Widget::Update;
	bool Update(const char* label, ButtonFlags flags = 0);
	void Render() const override;

	void SetLabel(const char* label) { _label = label; }

	bool IsHovered() const;
	bool IsClicked() const;
	bool IsDisabled() const;

	float GetWidth() const override { return _rect.w; }
	float GetHeight() const override { return _rect.h; }
	math::vec2 GetSize() const override { return math::vec2(_rect.w, _rect.h); }

private:
	std::string	_label;
	ButtonFlags _flags;
	Rect _rect;
	bool _pressed;
};

bool Button(const char* label, ButtonFlags flags = ButtonFlags_None);

} // GUI

} // Kinai
