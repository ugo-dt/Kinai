#include "Kinai/Renderer/2D/Renderer2D.hpp"

namespace Kinai
{

ShaderLibrary	Renderer2D::_shader_library;

const char *GLOBAL_VARIABLES_SOURCE = R"(
	#version 450 core

	layout(std140, binding = 0) uniform Builtin
	{
		float TIME;
		float PI;
		float TAU;
		float E;
	};
)";

const char *VERTEX_VARIABLES_SOURCE = R"(
	layout(std140, binding = 1) uniform Camera
	{
		mat4 CANVAS_MATRIX;
	};

	layout (location = 0) in  vec2 a_VERTEX;
	layout (location = 0) out vec2   VERTEX;
	
	layout (location = 1) in  vec2 a_UV;
	layout (location = 1) out vec2   UV;

	layout (location = 2) in  vec4 a_COLOR;
	layout (location = 2) out vec4   COLOR;

	layout (location = 3) in       int a_TEXTURE_INDEX;
	layout (location = 3) out flat int   TEXTURE_INDEX;

	layout (location = 4) in  vec2 a_SCREEN_UV;
	layout (location = 4) out vec2   SCREEN_UV;

	int VERTEX_ID; // gl_VertexID
	float POINT_SIZE; // gl_PointSize
)";

const char *VERTEX_MAIN_SOURCE = R"(
	void main()
	{
		VERTEX_ID = gl_VertexID;
		POINT_SIZE = gl_PointSize;
		VERTEX = a_VERTEX;
		UV = a_UV;
		COLOR = a_COLOR;
		TEXTURE_INDEX = a_TEXTURE_INDEX;
		SCREEN_UV = a_SCREEN_UV;

		// Custom shader code
		vertex();

		gl_Position = vec4(VERTEX, 0.0, 1.0);
		gl_PointSize = POINT_SIZE;
	}
)";

const char *FRAGMENT_VARIABLES_SOURCE = R"(
	layout (location = 0) in vec2 v_VERTEX;
	layout (location = 1) in vec2 v_UV;
	layout (location = 2) in vec4 v_COLOR;
	layout (location = 3) in flat int  v_TEXTURE_INDEX;
	layout (location = 4) in vec2 v_SCREEN_UV;

	vec2 VERTEX;
	vec2 UV;
	vec4 COLOR;
	int  TEXTURE_INDEX;
	vec2 SCREEN_UV;

	layout (binding = 0) uniform sampler2D TEXTURE_SLOTS[32];

	#define TEXTURE        (TEXTURE_SLOTS[TEXTURE_INDEX])
	#define SCREEN_TEXTURE (TEXTURE_SLOTS[0])

	vec4 FRAGCOORD; // gl_FragCoord
	vec2 SCREEN_PIXEL_SIZE; // TODO
	
	layout (location = 0) out vec4 out_COLOR;
)";

const char *FRAGMENT_MAIN_SOURCE = R"(
	void main()
	{
		VERTEX = v_VERTEX;
		UV = v_UV;
		COLOR = v_COLOR;
		TEXTURE_INDEX = v_TEXTURE_INDEX;
		SCREEN_UV = v_SCREEN_UV;

		FRAGCOORD = gl_FragCoord;
		// SCREEN_PIXEL_SIZE = 

		// Custom shader code
		fragment();

		out_COLOR = COLOR;
	}
)";

// Ref<Renderer2D::Shader2D>	Renderer2D::MakeShader(const std::string& filepath, const std::string& program_name)
// {
// }

Renderer2D::Shader2D	Renderer2D::MakeShader(const std::string& program_name, const std::string& vertexSrc, const std::string& fragmentSrc)
{
	std::string	vs;
	std::string	fs;

	vs.append(GLOBAL_VARIABLES_SOURCE);
	vs.append(VERTEX_VARIABLES_SOURCE);
	vs.append(vertexSrc);
	vs.append(VERTEX_MAIN_SOURCE);

	fs.append(GLOBAL_VARIABLES_SOURCE);
	fs.append(FRAGMENT_VARIABLES_SOURCE);
	fs.append(fragmentSrc);
	fs.append(FRAGMENT_MAIN_SOURCE);;

	std::cout << vs << std::endl;
	std::cout << "---" << std::endl;
	std::cout << fs << std::endl;

	return Shader2D(_shader_library.Load(program_name, vs, fs));
}

} // Kinai
