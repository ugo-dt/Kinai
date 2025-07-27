@vs __kn2d_quad_vs_source
#version 450 core

layout (location = 0) in vec2 a_VERTEX;
layout (location = 1) in vec2 a_UV;
layout (location = 2) in vec4 a_COLOR;
layout (location = 3) in int a_TEX_INDEX;

layout (location = 1) out vec2 v_UV;
layout (location = 2) out vec4 v_COLOR;
layout (location = 3) out flat int v_TEX_INDEX;

layout(std140, binding = 1) uniform Camera
{
	mat4 CANVAS_MATRIX;
};

void main()
{
	v_UV = a_UV;
	v_COLOR = a_COLOR;
	v_TEX_INDEX = a_TEX_INDEX;

	gl_Position = CANVAS_MATRIX * vec4(a_VERTEX, 0.0, 1.0);
	gl_PointSize = 1.0;
}
@end

@fs __kn2d_quad_fs_source
#version 450 core

layout (location = 0) out vec4 color;

layout (location = 1) in vec2 UV;
layout (location = 2) in vec4 COLOR;
layout (location = 3) in flat int TEX_INDEX;

layout (binding = 0) uniform sampler2D TEXTURE_SLOTS[32];
#define TEXTURE                       (TEXTURE_SLOTS[TEX_INDEX])

uniform sampler2D SCREEN_TEXTURE;

uniform vec2 VIEWPORT;

void main()
{
	color = COLOR * texture(TEXTURE, UV);
}
@end

@program __kn2d_quad_program __kn2d_quad_vs_source __kn2d_quad_fs_source
