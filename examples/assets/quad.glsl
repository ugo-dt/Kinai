@ctype mat4 glm::mat4

@vs vs
layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec4 a_Color;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec4 v_Color;

void	main()
{
	gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
	v_Color = a_Color;
}
@end

@fs fs
layout (location = 0) out vec4 f_Color;

in vec4 v_Color;

void	main()
{
	f_Color = vec4(v_Color);
}
@end

@program quad vs fs
