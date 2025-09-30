// #pragma once

// #include "Kinai/Core/Core.hpp"
// #include "Kinai/Core/Layer.hpp"

// namespace Kinai
// {

// class LayerStack
// {
// public:
// 	LayerStack();
// 	~LayerStack();

// 	void PushLayer(std::unique_ptr<Layer> layer);
// 	void RemoveLayer(std::unique_ptr<Layer> layer);
// 	void PopLayer() { RemoveLayer(std::move(_layers.back())); }

// 	void Transition(std::unique_ptr<Layer> to)
// 	{
// 		for (auto& layer : _layers)
// 		{
// 			if (layer.get() == this)
// 			{
// 				layer = std::move(to);
// 				return ;
// 			}
// 		}
// 	}
	
// 	void Clear();

// 	std::vector<std::unique_ptr<Layer>>::iterator begin()
// 		{ return _layers.begin(); }
// 	std::vector<std::unique_ptr<Layer>>::const_iterator begin() const
// 		{ return _layers.begin(); }
// 	std::vector<std::unique_ptr<Layer>>::iterator end()
// 		{ return _layers.end(); }
// 	std::vector<std::unique_ptr<Layer>>::const_iterator end() const
// 		{ return _layers.end(); }
// 	std::vector<std::unique_ptr<Layer>>::reverse_iterator rbegin()
// 		{ return _layers.rbegin(); }
// 	std::vector<std::unique_ptr<Layer>>::const_reverse_iterator rbegin() const
// 		{ return _layers.rbegin(); }
// 	std::vector<std::unique_ptr<Layer>>::reverse_iterator rend()
// 		{ return _layers.rend(); }
// 	std::vector<std::unique_ptr<Layer>>::const_reverse_iterator rend() const
// 		{ return _layers.rend(); }
// 	std::unique_ptr<Layer>&	operator[](size_t index)
// 		{ return _layers[index]; }
// 	const std::unique_ptr<Layer>&	operator[](size_t index) const
// 		{ return _layers[index]; }
// 	std::unique_ptr<Layer>& back()
// 		{ return _layers.back(); }
// 	const std::unique_ptr<Layer>& back() const
// 		{ return _layers.back(); }

// private:
// 	std::vector<std::unique_ptr<Layer>> _layers;
// };

// } // Kinai
