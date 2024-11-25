#version 450 core
layout (location = 0) out vec4 color;

in vec3 Normal;
in vec2 TexCoord;

uniform sampler2D texture_diffuse1;

void main() {
	color = texture(texture_diffuse1, TexCoord);
};