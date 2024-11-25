#pragma once

#include "ccpch.h"
#include "Renderer/Shader/Shader.h"
#include "Renderer/Shader/ShaderImplementation.h"

namespace Cannis {
	struct MaterialComponent {
		MaterialComponent(const ShaderImplementation p_shaderImpl = ShaderImplementation::None, const glm::vec3& p_specular = glm::vec3(1), const float p_shininess = 0) {
			shaderImpl = p_shaderImpl;
			specular = p_specular;
			shininess = p_shininess;
		}

		ShaderImplementation shaderImpl;
		glm::vec3 specular;
		float shininess;
	};
}