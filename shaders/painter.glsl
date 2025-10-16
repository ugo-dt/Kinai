@ctype mat4 glm::mat4

@vs vs
layout(location = 0) in vec4 a_Pos; // xy = pos, zw = uv
layout(location = 1) in vec4 a_Color;

layout(location = 0) out vec2 v_TexCoord;
layout(location = 1) out vec4 v_iColor;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

void main()
{
	gl_Position = u_ViewProjection * u_Transform * vec4(a_Pos.xy, 0.0, 1.0);
	gl_PointSize = 1.0;
	v_TexCoord = a_Pos.zw;
	v_iColor = a_Color;
}
@end

@fs fs
uniform sampler2D u_Texture;

layout(location = 0) in vec2 v_TexCoord;
layout(location = 1) in vec4 v_iColor;

layout(location = 0) out vec4 f_Color;

void main()
{
	vec4 texColor = texture(u_Texture, v_TexCoord) * v_iColor;
	f_Color = texColor;
}
@end

@program KinaiPainter vs fs
