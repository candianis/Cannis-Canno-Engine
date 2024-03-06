#version 450 core

struct Material {
	//This sampler will work as both the diffuse and ambient values
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;		
	float shininess;
};

struct DirectionalLight {
	vec3 direction;

	vec3 constant;
	vec3 linear;
	vec3 quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};
vec3 CalculateDirLight(DirectionalLight light, vec3 normal, vec3 viewDir);
	
struct PointLight {
	vec3 position;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

};
vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

struct SpotLight {
	vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
  
    float constant;
    float linear;
    float quadratic;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;  
};
vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

out vec4 FragColor;


in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform Material material;
uniform PointLight pointLights[4];
uniform DirectionalLight dirLight;
uniform vec3 viewPos;

void main(){
	vec3 norm = normalize(Normal);
	vec3 viewDir = normalize(viewPos - FragPos);

	vec3 lightInfluence = CalculateDirLight(dirLight, norm, viewDir);

	for(int i = 0; i < 4; i++)
		lightInfluence += CalculatePointLight(pointLights[i], norm, FragPos, viewDir);

	FragColor = vec4(lightInfluence, 1.0);
}

vec3 CalculateDirLight(DirectionalLight light, vec3 normal, vec3 viewDir) {
	vec3 lightDir = normalize(-light.direction);
	vec3 reflectDir = reflect(-lightDir, normal);
	
	//Ambient shading
	vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));

	//Diffuse shading	
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));

	//Specular shading
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));

	return (ambient + diffuse + specular);
}

vec3 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    // attenuation
    float lightDistance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * lightDistance + light.quadratic * (lightDistance * lightDistance));    
    
	//Calculate light direction towards a fragment
	vec3 lightDir = normalize(light.position - fragPos);

	//Ambient shading
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    ambient *= attenuation;

    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    diffuse *= attenuation;

    // specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    specular *= attenuation;

    return (ambient + diffuse + specular);
}

vec3 CalculateSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - fragPos);

	// attenuation
    float distance = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));    

	// spotlight intensity
    float theta = dot(lightDir, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

	// Ambient shading
    vec3 ambient = light.ambient * vec3(texture(material.diffuse, TexCoords));
    ambient *= attenuation * intensity;

    // Diffuse shading
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, TexCoords));
    diffuse *= attenuation * intensity;
    
	// specular shading
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
    specular *= attenuation * intensity;
    
    return (ambient + diffuse + specular);
}