#version 460

uniform sampler2D tex;

in vec2 texCoord;

out vec4 fragColor;

void main()
{
	vec4 color = texture(tex, texCoord);

//	if (color.rgb == vec3(0.0, 0.0, 0.0)) {
//		discard;
//	}

	fragColor = color;
	//fragColor = vec4(1.0, 1.0, 0.0, 1.0);
}