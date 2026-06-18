#include "Kinai/Core/Layer.hpp"
#include "Kinai/Core/Application.hpp"

namespace Kinai
{

std::vector<std::tuple<Layer*, std::unique_ptr<Layer>>>	Layer::_pendingTransitions;
std::vector<std::unique_ptr<Layer>>	Layer::_pendingPushes;
std::vector<Layer*>	Layer::_pendingRemovals;

Layer::Layer(const std::string name)
	: _debug_name(name)
{
	KN_PROFILE_FUNC();
}

void Layer::QueueTransition(std::unique_ptr<Layer> layer)
{
	KN_PROFILE_FUNC();

	_pendingTransitions.push_back(std::make_tuple(this, std::move(layer)));
}

void Layer::QueuePush(std::unique_ptr<Layer> layer)
{
	KN_PROFILE_FUNC();

	_pendingPushes.push_back(std::move(layer));
}

void Layer::DoTransition(std::unique_ptr<Layer> to)
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

void Layer::DoPush(std::unique_ptr<Layer> to)
{
	KN_PROFILE_FUNC();

	auto& stack = Application::Get()._layerStack;
	stack.push_back(std::move(to));
}

void Layer::QueueRemoval()
{
	KN_PROFILE_FUNC();
	_pendingRemovals.push_back(this);
}

void Layer::DoRemoval()
{
	KN_PROFILE_FUNC();

	auto& stack = Application::Get()._layerStack;
	for (auto it = stack.begin(); it != stack.end(); it++)
	{
		if (it->get() == this)
		{
			stack.erase(it);
			return;
		}
	}
}

} // Kinai
