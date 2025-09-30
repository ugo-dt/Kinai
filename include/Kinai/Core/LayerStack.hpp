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

	void PushLayer(Ref<Layer> layer);
	void RemoveLayer(Ref<Layer> layer);
	void PopLayer() { RemoveLayer(_layers.back()); }
	
	void Clear();

	std::vector<Ref<Layer>>::iterator				begin()        { return _layers.begin(); }
	std::vector<Ref<Layer>>::const_iterator			begin()  const { return _layers.begin(); }

	std::vector<Ref<Layer>>::iterator				end()          { return _layers.end(); }
	std::vector<Ref<Layer>>::const_iterator			end()    const { return _layers.end(); }

	std::vector<Ref<Layer>>::reverse_iterator 		rbegin()       { return _layers.rbegin(); }
	std::vector<Ref<Layer>>::const_reverse_iterator	rbegin() const { return _layers.rbegin(); }

	std::vector<Ref<Layer>>::reverse_iterator		rend()         { return _layers.rend(); }
	std::vector<Ref<Layer>>::const_reverse_iterator	rend()   const { return _layers.rend(); }

	Ref<Layer>&	operator[](size_t index) { return _layers[index]; }
	const Ref<Layer>&	operator[](size_t index) const { return _layers[index]; }

	Ref<Layer>& back() { return _layers.back(); }
	const Ref<Layer>& back() const { return _layers.back(); }

private:
	std::vector<Ref<Layer>> _layers;
};

} // Kinai
