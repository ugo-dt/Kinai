@vs __kn2d_quad_vs_source
#version 410 core

layout (location = 0) in vec2 a_VERTEX;
layout (location = 1) in vec2 a_UV;
layout (location = 2) in vec4 a_COLOR;
layout (location = 3) in int a_TEX_INDEX;

layout (location = 1) out vec2 UV;
layout (location = 2) out vec4 COLOR;

void main()
{
	UV = a_UV;
	COLOR = a_COLOR;

	gl_Position = vec4(a_VERTEX, 0.0, 1.0);
	gl_PointSize = 1.0;
}
@end

@fs __kn2d_quad_fs_source
#version 410 core

layout (location = 0) in vec4 COLOR;

layout (location = 0) out vec4 color;

void main()
{
	color = COLOR;
}
@end

@program __kn2d_quad_program __kn2d_quad_vs_source __kn2d_quad_fs_source
