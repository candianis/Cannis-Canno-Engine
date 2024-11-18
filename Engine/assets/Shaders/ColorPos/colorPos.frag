#version 450 core
layout (location = 0) out vec4 color;

in vec3 v_Position;
in vec4 v_Color;

void main()
{
	color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
	color = v_Color;
};