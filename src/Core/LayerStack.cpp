#include "Kinai/Core/LayerStack.hpp"

namespace Kinai
{

LayerStack::LayerStack()
	: _layers(), _layer_insert_index(0)
{
	EG_PRINT_FUNC();
}

LayerStack::~LayerStack()
{
	EG_PRINT_FUNC();

	Clear();
}

void	LayerStack::Clear()
{
	EG_PRINT_FUNC();

	if (_layers.empty())
		return ;
	for (Layer* layer : _layers)
	{
		layer->OnDetach();
		delete layer;
	}
	_layers.clear();
}

void LayerStack::PushLayer(Layer* layer)
{
	EG_PRINT_FUNC();
	_layers.emplace(_layers.begin() + _layer_insert_index, layer);
	_layer_insert_index++;
}

void LayerStack::PushOverlay(Layer* overlay)
{
	EG_PRINT_FUNC();
	_layers.emplace_back(overlay);
}

void LayerStack::PopLayer(Layer* layer)
{
	EG_PRINT_FUNC();
	auto it = std::find(_layers.begin(), _layers.begin() + _layer_insert_index, layer);
	if (it != _layers.begin() + _layer_insert_index)
	{
		layer->OnDetach();
		_layers.erase(it);
		_layer_insert_index--;
	}
}

void LayerStack::PopOverlay(Layer* overlay)
{
	EG_PRINT_FUNC();
	auto it = std::find(_layers.begin() + _layer_insert_index, _layers.end(), overlay);
	if (it != _layers.end())
	{
		overlay->OnDetach();
		_layers.erase(it);
	}
}

} // Kinai
