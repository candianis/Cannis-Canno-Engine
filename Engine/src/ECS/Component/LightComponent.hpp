#pragma once

#include "ccpch.h"

namespace Cannis {
	struct LightComponent {
		LightComponent(const glm::vec3& p_position = glm::vec3(0), const glm::vec3& p_ambient = glm::vec3(0), const glm::vec3& p_diffuse = glm::vec3(0), const glm::vec3& p_specular = glm::vec3(0)) {
			position = p_position;
			ambient = p_ambient;
			diffuse = p_diffuse;
			specular = p_specular;
		}

		glm::vec3 position;
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
	};
}