#pragma once

#include "Kinai/Core/Core.hpp"
#include "Kinai/Events/Event.hpp"

namespace Kinai
{

class Layer
{
protected:
	Layer(const std::string name = "DefaultLayer");

public:
	virtual ~Layer();

	virtual void OnUpdate(float delta) { KN_NOTUSED(delta); }
	virtual void OnRender() {}
	virtual void OnGUIRender() {}
	virtual void OnEvent(Event& event) { KN_NOTUSED(event); }

	const std::string& GetName() const { return _debug_name; }
	std::type_index GetType() const { return typeid(*this); }

	template <typename LayerT, typename... Args>
	void TransitionTo(Args&&... args)
	{
		QueueTransition(std::move(std::make_unique<LayerT>(std::forward<Args>(args)...)));
	}

private:
	void QueueTransition(std::unique_ptr<Layer> layer);

private:
	friend class Application;
	static std::vector<std::tuple<Layer*, std::unique_ptr<Layer>>>	_pendingTransitions;
	void DoTransition(std::unique_ptr<Layer> to);

private:
	std::string	_debug_name;
};

} // Kinai
