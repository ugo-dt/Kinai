@ctype mat4 Kinai::math::mat4

@vs vs
layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec2 a_TexCoord;
layout(location = 2) in vec4 a_Color;

layout(location = 0) out vec2 v_TexCoord;
layout(location = 1) out vec4 v_Color;

void main()
{
	gl_Position = vec4(fma(a_Position, vec2(2.0, -2.0), vec2(-1.0, 1.0)), 0.0, 1.0);
	v_TexCoord = a_TexCoord;
	v_Color = a_Color;
}
@end

@fs fs
uniform sampler2D u_Texture;

layout(location = 0) in vec2 v_TexCoord;
layout(location = 1) in vec4 v_Color;

layout(location = 0) out vec4 f_Color;

void main()
{
	f_Color = texture(u_Texture, v_TexCoord).xxxx * v_Color;
}
@end

@program KinaiShader_DebugText vs fs
