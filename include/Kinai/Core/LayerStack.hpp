#pragma once

#include "Kinai/Core/Core.hpp"
#include "Kinai/Core/Layer.hpp"

namespace Kinai
{

class LayerStack
{
public:
	LayerStack();
	~LayerStack();

	void	PushLayer(Layer *layer);
	void	PopLayer(Layer *layer);

	void	PushOverlay(Layer *layer);
	void	PopOverlay(Layer *layer);

	void	Clear();

	std::vector<Layer*>::iterator				begin()        { return _layers.begin(); }
	std::vector<Layer*>::const_iterator			begin()  const { return _layers.begin(); }

	std::vector<Layer*>::iterator				end()          { return _layers.end(); }
	std::vector<Layer*>::const_iterator			end()    const { return _layers.end(); }

	std::vector<Layer*>::reverse_iterator 		rbegin()       { return _layers.rbegin(); }
	std::vector<Layer*>::const_reverse_iterator	rbegin() const { return _layers.rbegin(); }

	std::vector<Layer*>::reverse_iterator		rend()         { return _layers.rend(); }
	std::vector<Layer*>::const_reverse_iterator	rend()   const { return _layers.rend(); }

private:
	std::vector<Layer*>	_layers;
	uint32_t			_layer_insert_index;
};

} // Kinai
