@module quad
@ctype mat4 glm::mat4

@vs vs
layout(location = 0) in vec4 coord;
layout(location = 0) out vec2 texUV;
layout(location = 1) out vec4 iColor;
layout(location = 1) in vec4 color;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;
uniform float u_floatz[2][2];
uniform int u_ints[23];

layout(std140, binding = 0) uniform BlockTextureTable {
	int faceTextures[256 * 6];
};

void main()
{
	gl_Position = vec4(coord.x, 1.0 - coord.y, 0.0, 1.0);
	gl_PointSize = 1.0;
	texUV = coord.zw;
	iColor = color;
}
@end

@fs fs
uniform sampler2D iTexChannel0_iSmpChannel0;

layout(location = 0) out vec4 fragColor;
layout(location = 0) in vec2 texUV;
layout(location = 1) in vec4 iColor;

void main()
{
	fragColor = texture(iTexChannel0_iSmpChannel0, texUV) * iColor;
}
@end

@program quad vs fs
