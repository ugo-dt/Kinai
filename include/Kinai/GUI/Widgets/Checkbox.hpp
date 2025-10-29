#pragma once

#include "Kinai/GUI/Widgets/Widget.hpp"
#include "Kinai/GUI/Widgets/Button.hpp"

namespace Kinai
{

namespace GUI
{

class WidgetCheckbox : public WidgetButton
{
public:
	WidgetCheckbox(Point position, const char* label, bool* value, ButtonFlags flags = 0);
	~WidgetCheckbox() = default;

	void UpdateSize() override;

	using WidgetButton::Update;
	bool Update(const char* label, bool* value, ButtonFlags flags = 0);
	void Render() const override;

private:
	bool* _value;
};

bool Checkbox(const char* label, bool* value, ButtonFlags flags = 0);

} // GUI

} // Kinai
