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

	using WidgetButton::Update;
	bool Update(const char* label, int* value, int button_value, ButtonFlags flags = 0);
	void UpdateSize() override;
	void Render() const override;

protected:
	void OnClick() override;

private:
	int* _value;
	int _button_value;
};

bool RadioButton(const char* label, int* value, int button_value, ButtonFlags flags = 0);

} // GUI

} // Kinai
