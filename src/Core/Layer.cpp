#include "Kinai/Core/Layer.hpp"
#include "Kinai/Core/Application.hpp"
#include "Kinai/GUI/State.hpp"

namespace Kinai
{

std::vector<std::tuple<Layer*, std::unique_ptr<Layer>>>	Layer::_pendingTransitions;

Layer::Layer(const std::string name)
	: _debug_name(name)
{
	KN_PROFILE_FUNC();
}

Layer::~Layer()
{
	KN_PROFILE_FUNC();
}

void	Layer::QueueTransition(std::unique_ptr<Layer> layer)
{
	KN_PROFILE_FUNC();

	_pendingTransitions.push_back(std::make_tuple(this, std::move(layer)));
}

void	Layer::DoTransition(std::unique_ptr<Layer> to)
{
	KN_PROFILE_FUNC();

	auto& stack = Application::Get()._layerStack;
	for (auto& layer : stack)
	{
		if (layer.get() == this)
		{
			layer = std::move(to);
			return;
		}
	}
}

} // Kinai
