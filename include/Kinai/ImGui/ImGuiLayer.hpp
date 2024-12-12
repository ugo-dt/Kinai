#pragma once

#include "Kinai/Core/Core.hpp"
#include "Kinai/Core/Layer.hpp"

namespace Kinai
{

class ImGuiLayer final : public Layer
{
public:
	ImGuiLayer();
	~ImGuiLayer() = default;

	void	Begin();
	void	End();

	virtual void	OnAttach() override;
	virtual void	OnDetach() override;
	virtual void	OnEvent(Event& event) override;

	void	BlockEvents(bool block) { _block_events = block; }

private:
	bool		_block_events;
};

} // Kinai
