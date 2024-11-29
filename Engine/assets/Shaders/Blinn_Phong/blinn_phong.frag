#version 450 core
layout (location = 0) out vec4 color;

uniform sampler2D diffuseMap;
uniform vec3 specular;
uniform float shininess;

struct Light {
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

in vec3 Normal;
in vec2 TexCoord;
in vec3 FragPos;

uniform vec3 ViewPos;
uniform Light light;

void main() {
	vec3 ambient = light.ambient * vec3(texture(diffuseMap, TexCoord));

	//diffuse
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(light.position - FragPos);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * vec3(texture(diffuseMap, TexCoord));	

	//specular
	vec3 viewDir = normalize(ViewPos - FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
	vec3 specular = light.specular * (spec * specular);

	vec3 result = ambient + diffuse + specular;
	color = vec4(result, 1.0f);
};