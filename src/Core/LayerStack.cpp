// #include "Kinai/Core/LayerStack.hpp"

// namespace Kinai
// {

// LayerStack::LayerStack()
// 	: _layers()
// {
// 	KN_PROFILE_FUNC();
// }

// LayerStack::~LayerStack()
// {
// 	KN_PROFILE_FUNC();

// 	Clear();
// }

// void	LayerStack::Clear()
// {
// 	KN_PROFILE_FUNC();

// 	if (_layers.empty())
// 		return ;
// 	for (Scope<Layer>& layer : _layers)
// 		layer->OnDetach();
// 	_layers.clear();
// }

// void LayerStack::PushLayer(Scope<Layer> layer)
// {
// 	KN_PROFILE_FUNC();
// 	_layers.emplace_back(layer);
// }

// void LayerStack::RemoveLayer(Scope<Layer> layer)
// {
// 	KN_PROFILE_FUNC();
// 	auto it = std::find(_layers.begin(), _layers.end(), layer);
// 	if (it != _layers.end())
// 	{
// 		layer->OnDetach();
// 		_layers.erase(it);
// 	}
// }

// } // Kinai
