#include "Kinai/GUI/Widgets/Widgets.hpp"
#include "Kinai/GUI/Window.hpp"

namespace Kinai
{

namespace GUI
{

template <typename WidgetType, typename... Args>
static bool CreateWidget(Args&&... args)
{
	if (!g_GuiState.current_window)
	{
		// Begin wasn't called yet
		Begin("Debug", nullptr);
		g_GuiState.begin_called = false;
	}
	return g_GuiState.current_window->AddWidget<WidgetType>(g_GuiState.next_widget_id++, std::forward<Args>(args)...);
}

bool	Button(const char* label, ButtonFlags flags)
{
	return CreateWidget<WidgetButton>(label, flags);
}

bool	RadioButton(const char* label, int* value, int button_value, ButtonFlags flags)
{
	return CreateWidget<WidgetRadioButton>(label, value, button_value, flags);
}

void	Text(const char* str)
{
	CreateWidget<WidgetText>(str);
}

bool	SliderFloat(const char* label, float* value, float min_value, float max_value)
{
	return CreateWidget<WidgetSlider<float>>(label, value, min_value, max_value);
}

bool	SliderDouble(const char* label, double* value, double min_value, double max_value)
{
	return CreateWidget<WidgetSlider<double>>(label, value, min_value, max_value);
}

bool	SliderInt(const char* label, int* value, int min_value, int max_value)
{
	return CreateWidget<WidgetSlider<int>>(label, value, min_value, max_value);
}

bool	SliderUInt(const char* label, unsigned int* value, unsigned int min_value, unsigned int max_value)
{
	return CreateWidget<WidgetSlider<unsigned int>>(label, value, min_value, max_value);
}

bool	SliderShort(const char* label, short* value, short min_value, short max_value)
{
	return CreateWidget<WidgetSlider<short>>(label, value, min_value, max_value);
}

bool	SliderChar(const char* label, char* value, char min_value, char max_value)
{
	return CreateWidget<WidgetSlider<char>>(label, value, min_value, max_value);
}

} // GUI

} // Kinai
