#pragma once

#include "Kinai/Core/Core.hpp"
#include "Kinai/Core/Layer.hpp"
#include "Kinai/GUI/GUI.hpp"

namespace Kinai
{

class GUILayer final : public Layer
{
public:
	GUILayer();
	~GUILayer();

	void Begin();
	void End();

	void OnEvent(Event& event) override;

	void BlockEvents(bool block) { _block_events = block; }

private:
	bool _block_events;
};

} // Kinai
