#include "Kinai/GUI/GUILayer.hpp"

namespace Kinai
{

GUILayer::GUILayer()
	: Layer("GUILayer"),
	  _block_events(true)
{
	GUI::CreateContext();
}

GUILayer::~GUILayer()
{
	GUI::DestroyContext();
}

void	GUILayer::OnEvent(Event& e)
{
	bool handled = GUI::OnEvent(e);
	if (_block_events)
	{
		e.handled |= handled && e.IsInCategory(EventCategoryMouse);
		e.handled |= handled && e.IsInCategory(EventCategoryKeyboard);
	}
}

void	GUILayer::Begin()
{
	GUI::NewFrame();
}

void	GUILayer::End()
{
	GUI::Render();
}

} // Kinai
