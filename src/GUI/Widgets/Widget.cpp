#include "Kinai/GUI/Widgets/Widgets.hpp"
#include "Kinai/GUI/State.hpp"
#include "Kinai/GUI/Window.hpp"

namespace Kinai
{

namespace GUI
{

template <typename WidgetType, typename... Args>
static bool CreateWidget(Args&&... args)
{
	if (!state.current_window)
		Begin("Debug", nullptr);
	return state.current_window->AddWidget<WidgetType>(state.next_widget_id++, std::forward<Args>(args)...);
}

void	Text(const char* str)
{
	CreateWidget<WidgetText>(str);
}

bool	Button(const char* label, ButtonFlags flags)
{
	return CreateWidget<WidgetButton>(label, flags);
}

} // GUI

} // Kinai
