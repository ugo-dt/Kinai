#pragma once

#include "Kinai/GUI/Widgets/Widget.hpp"
#include "Kinai/GUI/Widgets/Button.hpp"

namespace Kinai
{

namespace GUI
{

class WidgetRadioButton : public WidgetButton
{
public:
	WidgetRadioButton(Point position, const char* label, int* value, int button_value, ButtonFlags flags = 0);
	~WidgetRadioButton() = default;

	void UpdateSize() override;

	using WidgetButton::Update;
	bool Update(const char* label, int* value, int button_value, ButtonFlags flags = 0);
	void Render() const override;

private:
	int* _value;
	int _button_value;
};

bool RadioButton(const char* label, int* value, int button_value, ButtonFlags flags = 0);

} // GUI

} // Kinai
