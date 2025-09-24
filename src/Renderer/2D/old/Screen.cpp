#include "Kinai/Renderer/2D/Renderer2D.hpp"
#include "Kinai/Core/Application.hpp"

namespace Kinai
{

unsigned int		Renderer2D::_screen_framebuffer;

const char *SCREEN_SHADER_VERTEX = R"(
	#version 450 core

	layout (location = 0) in vec2 a_VERTEX;
	layout (location = 1) in vec2 a_UV;

	out vec2 SCREEN_UV;

	void main()
	{
		SCREEN_UV = a_UV;
		gl_Position = vec4(a_VERTEX.x, a_VERTEX.y, 0.0, 1.0); 
	}
)";

const char *SCREEN_SHADER_FRAGMENT = R"(
	#version 450 core

	out vec4 COLOR;

	in vec2 SCREEN_UV;

	uniform sampler2D Quad;

	void main()
	{
		vec3 col = texture(Quad, SCREEN_UV).rgb;
		COLOR = vec4(col, 1.0);
	} 
)";

void	Renderer2D::MakeScreenFramebuffers()
{
	KN_PROFILE_FUNC();

}

void	Renderer2D::CopyScreenToBackBuffer()
{
	KN_PROFILE_FUNC();

// FIXME: Abstract this with Kinai::Framebuffer
# ifdef KINAI_OPENGL
	glm::ivec2 winsize = Application::Get().GetWindow().GetSize();

	glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, _screen_framebuffer);
	glBlitFramebuffer(0, 0, winsize.x, winsize.y, 0, 0, winsize.x, winsize.y, GL_COLOR_BUFFER_BIT, GL_NEAREST);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
#endif
}

} // Kinai
