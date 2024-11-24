#pragma once

#include "ccpch.h"
#include "Renderer/Shader/Shader.h"

namespace Cannis {
	struct MaterialComponent {
		MaterialComponent(const glm::vec3& p_specular = glm::vec3(1), const float p_shininess = 0) {
			specular = p_specular;
			shininess = p_shininess;
		}

		glm::vec3 specular;
		float shininess;
	};
}