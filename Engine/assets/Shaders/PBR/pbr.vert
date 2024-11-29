#version 450 core
layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_Normal;
layout (location = 2) in vec2 a_TexCoord;

out vec3 WorldPos;
out vec3 Normal;
out vec2 TexCoords;

uniform mat4 u_model;
uniform mat4 u_viewProjection;

void main() {
	WorldPos = vec3(u_model * vec4(a_Position, 1.0));
	Normal = mat3(transpose(inverse(u_model))) * a_Normal;
	TexCoords = a_TexCoord;

	gl_Position = u_viewProjection * vec4(WorldPos, 1.0);
}