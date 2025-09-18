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

	void	PushLayer(Ref<Layer> layer);
	void	PopLayer(Ref<Layer> layer);

	void	PushOverlay(Ref<Layer> layer);
	void	PopOverlay(Ref<Layer> layer);

	void	Clear();

	std::vector<Ref<Layer>>::iterator				begin()        { return _layers.begin(); }
	std::vector<Ref<Layer>>::const_iterator			begin()  const { return _layers.begin(); }

	std::vector<Ref<Layer>>::iterator				end()          { return _layers.end(); }
	std::vector<Ref<Layer>>::const_iterator			end()    const { return _layers.end(); }

	std::vector<Ref<Layer>>::reverse_iterator 		rbegin()       { return _layers.rbegin(); }
	std::vector<Ref<Layer>>::const_reverse_iterator	rbegin() const { return _layers.rbegin(); }

	std::vector<Ref<Layer>>::reverse_iterator		rend()         { return _layers.rend(); }
	std::vector<Ref<Layer>>::const_reverse_iterator	rend()   const { return _layers.rend(); }

private:
	std::vector<Ref<Layer>> _layers;
	uint32_t _layer_insert_index;
};

} // Kinai
