#pragma once

#include "ccpch.h"

namespace Cannis {
	struct PBRMaterialComponent {
		PBRMaterialComponent() = default;

		PBRMaterialComponent(const glm::vec3& p_albedo = glm::vec3(0), const float p_metallic = 0, const float p_roughness = 0, const float p_ao = 0) {
			albedo = p_albedo;
			metallic = p_metallic;
			roughness = p_roughness;
			ao = p_ao;
		}

		glm::vec3 albedo;
		float metallic;
		float roughness;
		float ao;
	};
}