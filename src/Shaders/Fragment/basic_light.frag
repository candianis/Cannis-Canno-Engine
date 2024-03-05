#version 450 core

struct Material {
	//This sampler will work as both the diffuse and ambient values
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;
	float shininess;
};

struct Light {
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

out vec4 FragColor;


in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform Material material;
uniform Light light;
uniform vec3 viewPos;

void main(){
	//Ambient light calculation
	vec3 ambient = light.ambient * texture(material.diffuse, TexCoords).rgb;

	//Diffuse light calculation
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(-light.direction);
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = light.diffuse * texture(material.diffuse, TexCoords).rgb;

	//Specular light calculation
	vec3 viewDir = normalize(viewPos - FragPos);
	//Use the negative lightDir because in its assignment we are getting the fragment towards the light
	vec3 reflecDir = reflect(-lightDir, norm);

	//Use a max because the spec value cannot be negative
	//Raise the value by the power of 32 so that its value can be seen
	float spec = pow(max(dot(viewDir, reflecDir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * texture(material.specular, TexCoords).rgb;

	vec3 emissionMask = step(vec3(1.0), vec3(1.0) - texture(material.specular, TexCoords).rgb);
	vec3 emission = texture(material.emission, TexCoords).rgb * emissionMask;

	FragColor = vec4(ambient + diffuse + specular + emission, 1.0);
}