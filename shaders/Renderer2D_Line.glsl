@vs __kn2d_line_vs_source
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;

layout(std140, binding = 0) uniform Camera
{
	mat4 u_ViewProjection;
};

struct VertexOutput
{
	vec4 Color;
};

layout (location = 0) out VertexOutput Output;

void main()
{
	Output.Color = a_Color;

	gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
}
@end

@fs __kn2d_line_fs_source
layout(location = 0) out vec4 fragColor;

struct VertexOutput
{
	vec4 Color;
};

layout (location = 0) in VertexOutput Input;

void main()
{
	fragColor = Input.Color;
}
@end

@program __kn2d_line_program __kn2d_line_vs_source __kn2d_line_fs_source
