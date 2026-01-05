#include "Kinai/Core/Application.hpp"
#include "Kinai/GUI/Core.hpp"
#include "Kinai/GUI/Event.hpp"
#include "Kinai/GUI/State.hpp"
#include "Kinai/GUI/Window.hpp"
#include "Kinai/GUI/framebuffer.glsl.hpp"

namespace Kinai
{

namespace GUI
{

const float framebuffer_vertices[] = {
	-1.0f, -1.0f, 0.0f, 0.0f,
	 1.0f, -1.0f, 1.0f, 0.0f,
	 1.0f,  1.0f, 1.0f, 1.0f,
	-1.0f,  1.0f, 0.0f, 1.0f
};

const uint32_t framebuffer_indices[] = {
	0, 1, 2,
	0, 2, 3
};

Ref<DebugText::Context>	debug_context = nullptr;

void	CreateContext()
{
	g_GuiState.context = DebugText::MakeContext();
	DebugText::SetContext(g_GuiState.context);
	glm::ivec2 size = Application::Get().GetWindow().GetSize();
	g_GuiState.scale = 1.f;
	UpdateCanvasSize((float)size.x / g_GuiState.scale, (float)size.y / g_GuiState.scale);

	for (int i = 0; i < SDL_SYSTEM_CURSOR_COUNT; ++i)
		g_GuiState.sdl_cursors[i] = SDL_CreateSystemCursor(static_cast<SDL_SystemCursor>(i));

	g_GuiState.framebuffer = Framebuffer::Create(
		FramebufferConfig{
			.width = size.x,
			.height = size.y,
			.attachments = {
				{ FramebufferTextureFormat::RGBA8, {} },
				{ FramebufferTextureFormat::Depth, {} }
			},
		}
	);
	g_GuiState.framebuffer_pipeline = Pipeline::Create(
		PipelineConfig{
			.vao = VertexArray::Create(),
			.shader = Shader::Create(framebufferProgramShaderConfig()),
			.layout = BufferLayout{
				{ ShaderDataType::Float2, "a_Position" },
				{ ShaderDataType::Float2, "a_TexCoord" }
			},
			.label = "GUI framebuffer pipeline",
		}
	);
	g_GuiState.framebuffer_bindings = Bindings::Create();
	g_GuiState.framebuffer_bindings->AddVertexBuffer(VertexBuffer::Create(framebuffer_vertices, sizeof(framebuffer_vertices)));
	g_GuiState.framebuffer_bindings->SetIndexBuffer(IndexBuffer::Create(framebuffer_indices, sizeof(framebuffer_indices) / sizeof(uint32_t)));

	// debug
	debug_context = DebugText::MakeContext();
}

void	DestroyContext()
{
	g_GuiState.framebuffer = nullptr;
	g_GuiState.framebuffer_pipeline = nullptr;
	g_GuiState.framebuffer_bindings = nullptr;
	for (int i = 0; i < SDL_SYSTEM_CURSOR_COUNT; ++i)
		if (g_GuiState.sdl_cursors[i])
			SDL_DestroyCursor(g_GuiState.sdl_cursors[i]);
	DebugText::SetContext(DebugText::GetDefaultContext());
	g_GuiState.context = nullptr;

	debug_context = nullptr;
}

void	OnEvent(Event& event)
{
	EventDispatcher	dispatcher(event);

	dispatcher.Dispatch<WindowResizeEvent>(GUI::OnWindowResizeEvent);
	dispatcher.Dispatch<MouseMotionEvent>(GUI::OnMouseMotionEvent);
	// dispatcher.Dispatch<MouseButtonPressedEvent>(GUI::OnMouseButtonPressedEvent);
	// dispatcher.Dispatch<MouseButtonReleasedEvent>(GUI::OnMouseButtonReleasedEvent);

	if (g_GuiState.active_window && g_GuiState.active_window->IsOpen())
	{
		g_GuiState.active_window->OnEvent(event);
		if (event.handled)
			return;
	}

	for (const auto& gui_window : g_GuiState.windows)
	{
		auto& window = gui_window.second;
		if (g_GuiState.active_window && g_GuiState.active_window->GetID() == window->GetID())
			continue;
		if (!window->IsOpen())
			continue;

		window->OnEvent(event);
		if (event.handled)
			break;
	}
}

Point	GetMousePosition()
{
	return Point{ g_GuiState.mouse.x, g_GuiState.mouse.y };
}

bool	IsMouseHovering(const Rect&rect)
{
	return PointInRect(GetMousePosition(), rect);
}

void	NewFrame()
{
	++g_GuiState.frames;
	MouseCursorNewFrame();
	g_GuiState.next_window_id = 1;

	g_GuiState.framebuffer->Bind();
	Renderer::SetClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	Renderer::Clear();
}

static void RenderWindow(const Ref<GUI::Window>& window)
{
	DebugText::SetContext(g_GuiState.context);
	DebugText::SetOrigin(0.f, 0.f);
	DebugText::SetColor(255, 255, 255, 255);
	DebugText::Home();
	DebugText::Font(DebugTextFont::ORIC);

	Painter::Begin();
	window->Render();

	Renderer::BeginPass();
		Painter::Flush();
		Painter::End();

		DebugText::SubmitContext(g_GuiState.context);
	Renderer::EndPass();
}

void	Render()
{
	if (g_GuiState.current_window && !g_GuiState.begin_called)
	{
		// User didn't call Begin(), need to call End() now
		KN_ASSERT(g_GuiState.current_window);
		g_GuiState.begin_called = true;
		GUI::End();
	}

	for (const auto& gui_window : g_GuiState.windows)
	{
		auto& window = gui_window.second;
		if (g_GuiState.active_window && g_GuiState.active_window->GetID() == window->GetID())
			continue;
		if (!window->IsOpen())
			continue;
		RenderWindow(window);
	}
	if (g_GuiState.active_window && g_GuiState.active_window->IsOpen())
		RenderWindow(g_GuiState.active_window);
	g_GuiState.framebuffer->Unbind();

	Renderer::BeginPass();
		Renderer::ApplyPipeline(g_GuiState.framebuffer_pipeline);
		Renderer::ApplyBindings(g_GuiState.framebuffer_bindings);

		glBindTexture(GL_TEXTURE_2D, g_GuiState.framebuffer->GetColorAttachmentRendererID());
		Renderer::Submit();
	Renderer::EndPass();

	// update state

	for (const auto & gui_window : g_GuiState.windows)
		gui_window.second->Update();

	UpdateMouseButtons();

	// debug
	// glm::ivec2 size;
	// SDL_GetWindowSize((SDL_Window*)Application::Get().GetWindow().GetNativeWindow(), &size.x, &size.y);
	// DebugText::SetContext(debug_context);
	// DebugText::SetCanvasSize((float)size.x, (float)size.y);
	// DebugText::Font(DebugTextFont::KC854);
	// DebugText::SetColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	// // debug text here
	// DebugText::Printf("Active Window ID: %d\n", g_GuiState.active_window ? g_GuiState.active_window->GetID() : 0);
	// DebugText::Printf("Total Windows: %lld\n", g_GuiState.windows.size());
	// DebugText::SubmitContext(debug_context);
}

void	SetNextWindowPos(const glm::ivec2& pos)
{
	KN_ASSERT(pos.x >= 0.f && pos.y >= 0.f, "GUI: invalid window position");
	g_GuiState.next_window_pos = pos;
}

void	Begin(const char* label, bool* is_open, WindowFlags flags)
{
	KN_ASSERT(!g_GuiState.current_window, "GUI::Begin called before GUI::End!");

	glm::vec2 pos = (g_GuiState.next_window_pos.x >= 0.f && g_GuiState.next_window_pos.y >= 0.f)
		? g_GuiState.next_window_pos : glm::vec2((g_GuiState.next_window_id + 1) * 50.f, (g_GuiState.next_window_id + 1) * 50.f);
	
	g_GuiState.begin_called = true;
	g_GuiState.current_window = g_GuiState.windows.find(g_GuiState.next_window_id) != g_GuiState.windows.end()
		? g_GuiState.windows.at(g_GuiState.next_window_id)
		: CreateRef<GUI::Window>(
			label,
			g_GuiState.next_window_id,
			Rect{ pos.x, pos.y, 200.f, 200.f },
			is_open,
			flags
		);
	g_GuiState.next_widget_id = 0;
	g_GuiState.next_window_pos = glm::vec2(-1.f, -1.f); // reset to invalid values
}

void	End()
{
	KN_ASSERT(g_GuiState.current_window, "GUI::End called without a matching GUI::Begin!");
	KN_ASSERT(g_GuiState.begin_called, "GUI::End called without a matching GUI::Begin!");
	
	g_GuiState.windows.insert(std::make_pair(g_GuiState.next_window_id++, g_GuiState.current_window));
	g_GuiState.current_window = nullptr;
}

} // GUI

} // Kinai
