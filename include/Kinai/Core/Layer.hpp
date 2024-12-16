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
	virtual ~Layer(void) = default;

	virtual void	OnAttach() {};
	virtual void	OnDetach() {};
	virtual void	OnUpdate(float delta) { (void)delta; };
	virtual void	OnImGuiRender() {}
	virtual void	OnEvent(Event& event) { (void)event; };

	const std::string&	GetName() const { return _debug_name; }

private:
	std::string	_debug_name;
};

} // Kinai
