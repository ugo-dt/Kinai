#pragma once

#include <Kinai/Kinai.hpp>

class AppLayer : public Kinai::Layer
{
public:
	AppLayer();
	~AppLayer() = default;

	void OnUpdate(float delta) override;
	void OnRender() override;
	void OnEvent(Kinai::Event& event) override;
	void OnImGuiRender() override;

	bool OnKeyPressed(Kinai::KeyPressedEvent &event);
};

class App : public Kinai::Application
{
public:
	App();
	~App() = default;
};
