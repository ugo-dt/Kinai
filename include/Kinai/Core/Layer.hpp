#pragma once

#include "Kinai/Core/Core.hpp"
#include "Kinai/Events/Event.hpp"

namespace Kinai
{

class Layer
{
protected:
	Layer(const std::string name = "DefaultLayer"): _debug_name(name) {}

public:
	virtual ~Layer() = default;

	virtual void	OnAttach() {};
	virtual void	OnDetach() {};
	virtual void	OnUpdate(float delta) { KN_NOTUSED(delta); };
	virtual void	OnRender() {};
	virtual void	OnImGuiRender() {}
	virtual void	OnEvent(Event& event) { KN_NOTUSED(event); };

	const std::string&	GetName() const { return _debug_name; }

private:
	std::string	_debug_name;
};

} // Kinai
