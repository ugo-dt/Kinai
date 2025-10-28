#include "Kinai/GUI/GUILayer.hpp"
#include "Kinai/GUI/State.hpp"

namespace Kinai
{

GUILayer::GUILayer()
	: Layer("GUI Layer"),
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
	GUI::OnEvent(e);
	if (_block_events)
	{
		e.handled |= e.handled && e.IsInCategory(EventCategoryMouse);
		e.handled |= e.handled && e.IsInCategory(EventCategoryKeyboard);
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
