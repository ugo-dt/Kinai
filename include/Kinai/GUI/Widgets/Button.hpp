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
	
	virtual void UpdateSize();

	using Entity::Update;
	virtual bool Update(const char* label, ButtonFlags flags = 0);
	virtual void Render() const override;

	void SetLabel(const char* label) { _label = label; }

	bool IsHovered() const { return _hovered; }
	bool IsClicked() const { return _released; }
	bool IsDisabled() const { return _flags & ButtonFlags_Disabled; }

protected:
	virtual void OnClick() {}

protected:
	std::string	_label;
	ButtonFlags _flags;
};

bool Button(const char* label, ButtonFlags flags = ButtonFlags_None);

} // GUI

} // Kinai
