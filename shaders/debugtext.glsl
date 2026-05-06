@ctype mat4 glm::mat4

@vs vs
in vec2 a_Position;
in vec2 a_TexCoord;
in vec4 a_Color;

out vec2 v_TexCoord;
out vec4 v_Color;

void main()
{
	gl_Position = vec4(a_Position * vec2(2.0, -2.0) + vec2(-1.0, +1.0), 0.0, 1.0);
	v_TexCoord = a_TexCoord;
	v_Color = a_Color;
}
@end

@fs fs
in vec2 v_TexCoord;
in vec4 v_Color;

out vec4 f_Color;

uniform sampler2D u_Texture;

void main()
{
	f_Color = texture(u_Texture, v_TexCoord).xxxx * v_Color;
}
@end

@program KinaiShader_DebugText vs fs
