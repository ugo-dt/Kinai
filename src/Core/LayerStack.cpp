#include "Kinai/Core/LayerStack.hpp"

namespace Kinai
{

LayerStack::LayerStack()
	: _layers(), _layer_insert_index(0)
{
	KN_PROFILE_FUNC();
}

LayerStack::~LayerStack()
{
	KN_PROFILE_FUNC();

	Clear();
}

void	LayerStack::Clear()
{
	KN_PROFILE_FUNC();

	if (_layers.empty())
		return ;
	for (Ref<Layer>& layer : _layers)
		layer->OnDetach();
	_layers.clear();
}

void LayerStack::PushLayer(Ref<Layer> layer)
{
	KN_PROFILE_FUNC();
	_layers.emplace(_layers.begin() + _layer_insert_index, layer);
	_layer_insert_index++;
}

void LayerStack::PushOverlay(Ref<Layer> overlay)
{
	KN_PROFILE_FUNC();
	_layers.emplace_back(overlay);
}

void LayerStack::PopLayer(Ref<Layer> layer)
{
	KN_PROFILE_FUNC();
	auto it = std::find(_layers.begin(), _layers.begin() + _layer_insert_index, layer);
	if (it != _layers.begin() + _layer_insert_index)
	{
		layer->OnDetach();
		_layers.erase(it);
		_layer_insert_index--;
	}
}

void LayerStack::PopOverlay(Ref<Layer> overlay)
{
	KN_PROFILE_FUNC();
	auto it = std::find(_layers.begin() + _layer_insert_index, _layers.end(), overlay);
	if (it != _layers.end())
	{
		overlay->OnDetach();
		_layers.erase(it);
	}
}

} // Kinai
