#version 450 core

layout (location = 0) out vec4 FragColor;

in vec3 WorldPos;
in vec3 Normal;
in vec2 TexCoord;

// material parameters
uniform vec3 u_albedo;
uniform float u_metallic;
uniform float u_roughness;
uniform float u_ambientOcclusion;

struct Light {
	vec3 position;
	vec3 color;
};

uniform Light lights[4];

uniform vec3 camPos;

const float PI = 3.14159265359;

float DistributionGGX(vec3 p_N, vec3 p_H, float p_roughness) {
	float a = p_roughness * p_roughness;
	float a2 = a * a;
	float NdotH = max(dot(p_N, p_H), 0.0);
	float NdotH2 = NdotH * NdotH;

	float nom = a2;
	float denom = (NdotH2 * (a2 - 1.0) + 1.0);
	denom = PI * denom * denom;

	return nom / denom;
}

float GeometrySchlickGGX(float p_NdotV, float p_roughness) {
	float r = (p_roughness + 1.0);
	float k = (r * r) / 8.0;
	float nom = p_NdotV;
	float denom = p_NdotV * (1.0 - k) + k;

	return nom / denom;
}

float GeometrySmith(vec3 p_N, vec3 p_V, vec3 p_L, float p_roughness) {
	float NdotV = max(dot(p_N, p_V), 0.0);

	float NdotL = max(dot(p_N, p_L), 0.0);
	float ggx2 = GeometrySchlickGGX(NdotV, p_roughness);
	float ggx1 = GeometrySchlickGGX(NdotL, p_roughness);

	return ggx1 * ggx2;
}

vec3 fresnelSchlick(float p_cosTheta, vec3 p_F0) {
	return p_F0 + (1.0 - p_F0) * pow(clamp(1.0 - p_cosTheta, 0.0, 1.0), 5.0);
}

void main() {
	vec3 N = normalize(Normal);
	vec3 V = normalize(camPos - WorldPos);

		vec3 F0 = vec3(0.04);
		F0 = mix(F0, u_albedo, u_metallic);

		//reflectance equation;
		vec3 Lo = vec3(0.0);
		for(int i = 0; i < 4; i++) {
			//Calculate per light radiance
			vec3 L = normalize(lights[i].position - WorldPos);
			vec3 H = normalize(V + L);
			float distance = length(lights[i].position - WorldPos);
			float attenuation = 1.0 / (distance * distance);
			vec3 radiance = lights[i].color * attenuation;

			//Cook Torrance BRDF
			float NDF = DistributionGGX(N, H, u_roughness);
			float G = GeometrySmith(N, V, L, u_roughness);
			vec3 F = fresnelSchlick(clamp(dot(H, V), 0.0, 1.0), F0);

			vec3 numerator = NDF * G * F;
			float denominator = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.0001;
			vec3 specular = numerator / denominator;

			vec3 ks = F;
			// for energy conservation, the diffuse and specular light can't
			// be above 1.0 (unless the surface emits light); to preserve this
			// relationship the diffuse component (kD) should equal 1.0 - kS.
			vec3 kD = vec3(1.0) - ks;

			kD *= 1.0 - u_metallic;
			float NdotL = max(dot(N, L), 0.0);
			Lo += (kD * u_albedo / PI + specular) * radiance * NdotL;
		}

		vec3 ambient = vec3(0.03) * u_albedo * u_ambientOcclusion;

		vec3 color = ambient + Lo;

		color = color / (color + vec3(1.0));

		color = pow(color, vec3(1.0/2.2));

		FragColor = vec4(color, 1.0);
}