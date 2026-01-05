@ctype mat4 glm::mat4

@vs vs
layout (location = 0) in vec2 a_Position;
layout (location = 1) in vec2 a_TexCoord;

out vec2 v_TexCoord;

void	main()
{
	gl_Position = vec4(a_Position, 0.0, 1.0);
	v_TexCoord = a_TexCoord;
}
@end

@fs fs
layout (location = 0) out vec4 f_Color;

in vec2 v_TexCoord;

uniform sampler2D u_Texture;

void	main()
{
	f_Color = texture(u_Texture, v_TexCoord);
}
@end

@program framebuffer vs fs
