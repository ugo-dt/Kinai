@vs __kn2d_quad_vs_source
layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoord;
layout(location = 3) in float a_TexIndex;

layout(std140, binding = 0) uniform Camera
{
	mat4 u_ViewProjection;
	vec2 u_Viewport;
};

void main()
{
	gl_Position = vec4(a_Position.xy, 0.0, 1.0);
	gl_PointSize = 1.0;
}
@end

@fs __kn2d_quad_fs_source
/*
in vec4 FRAGCOORD;
in vec2	VERTEX;
in vec2	UV;
in vec4	COLOR;
in sampler2D TEXTURE;
*/

void main()
{
	FRAGCOORD = gl_FragCoord;
	VERTEX = _v_VERTEX;
	UV = _v_UV;
	COLOR = _v_COLOR;

	vec4 texCol = texture(TEXTURE, UV);

	COLOR *= texCol;

	// Run custom shader
	fragment();
}
@end

@program __kn2d_quad_program __kn2d_quad_vs_source __kn2d_quad_fs_source
