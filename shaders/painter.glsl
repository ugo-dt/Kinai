@ctype mat4 glm::mat4

@vs vs
in vec4 a_Pos; // xy = pos, zw = uv
in vec4 a_Color;

out vec2 v_TexCoord;
out vec4 v_iColor;

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
in vec2 v_TexCoord;
in vec4 v_iColor;

out vec4 f_Color;

uniform sampler2D u_Texture;

void main()
{
	vec4 texColor = texture(u_Texture, v_TexCoord) * v_iColor;
	f_Color = texColor;
}
@end

@program KinaiShader_Painter vs fs
