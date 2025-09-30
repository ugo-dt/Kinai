#include "Kinai/ImGui/ImGuiLayer.hpp"
#include "Kinai/Core/Application.hpp"

namespace Kinai
{

ImGuiLayer::ImGuiLayer()
	: _block_events(false)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;	// Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;		// Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;		// Enable Multi-Viewport / Platform Windows

#if defined(KINAI_OPENGL)
	ImGui_ImplSDL3_InitForOpenGL(SDL_GL_GetCurrentWindow(), SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL3_Init();
	#ifdef KN_ENABLE_ASSERTS
		while (glGetError())
			;
	#endif
#elif defined(KINAI_HEADLESS)
	unsigned char* tex_pixels = nullptr;
    int tex_w, tex_h;
    io.Fonts->GetTexDataAsRGBA32(&tex_pixels, &tex_w, &tex_h);

	io.DisplaySize = ImVec2(KN_DEFAULT_WINDOW_WIDTH, KN_DEFAULT_WINDOW_HEIGHT);
	io.DeltaTime = 1.0f / 60.0f;
	
#endif
}

ImGuiLayer::~ImGuiLayer()
{
#ifdef KINAI_OPENGL
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL3_Shutdown();
#endif
	ImGui::DestroyContext();
}

void	ImGuiLayer::OnEvent(Event &e)
{
	if (_block_events)
	{
		ImGuiIO& io = ImGui::GetIO();
		e.handled |= e.IsInCategory(EventCategoryMouse) & io.WantCaptureMouse;
		e.handled |= e.IsInCategory(EventCategoryKeyboard) & io.WantCaptureKeyboard;
	}
}

void	ImGuiLayer::Begin()
{
#if defined(KINAI_OPENGL)
	ImGui_ImplOpenGL3_NewFrame();
	#if defined(KN_PLATFORM_DESKTOP)
		ImGui_ImplSDL3_NewFrame();
	#endif
	#if defined(KN_PLATFORM_WEB)
		ImGuiIO& io = ImGui::GetIO();
		const auto size = Application::Get().GetWindow().GetSize();
		io.DisplaySize.x = size.x;
		io.DisplaySize.y = size.y;
	#endif
#endif

	ImGui::NewFrame();
}

void	ImGuiLayer::End()
{
	ImGui::Render();

#if defined(KINAI_OPENGL)
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
		SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault(nullptr, nullptr);
		SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
	}
#endif
}

} // Kinai
