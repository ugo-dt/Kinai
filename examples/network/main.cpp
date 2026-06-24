#include "Game.hpp"
#include <Kinai/EntryPoint.hpp>

AppLayer::AppLayer(): Kinai::Layer("App Layer") {}

void AppLayer::OnUpdate(float delta)
{
	KN_NOTUSED(delta);
}

void AppLayer::OnRender()
{
	Kinai::Renderer::SetClearColor(0.3f, 0.3f, 0.3f, 1.0f);
	Kinai::Renderer::Clear();
}

void AppLayer::OnEvent(Kinai::Event& event)
{
	Kinai::EventDispatcher dispatcher(event);
	dispatcher.Dispatch<Kinai::KeyPressedEvent>(KN_BIND_EVENT_FN(OnKeyPressed));
}

bool AppLayer::OnKeyPressed(Kinai::KeyPressedEvent &event)
{
	switch (event.GetKeyCode())
	{
		case Kinai::Key::Escape:
			Kinai::Quit();
			break;
		default:
			break;
	}
	return true;
}

void AppLayer::OnImGuiRender()
{
	ImGui::Begin("Network Example");
	ImGui::Text("Press ESC to quit");
	ImGui::End();
}

App::App()
	: Kinai::Application(Kinai::ApplicationConfig{
		.enable_imgui = true,
	})
{
	PushLayer<AppLayer>();
}

Kinai::Application*	Kinai::CreateApplication(int argc, char **argv)
{
	KN_NOTUSED(argc);
	KN_NOTUSED(argv);

	return new App();
}
