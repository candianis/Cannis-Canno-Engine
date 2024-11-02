#pragma once 

#include "Core/Core.h"
#include "Component.h"

namespace Cannis {
	struct CANNIS_API TransformComponent {
	public:
		TransformComponent();
		TransformComponent(glm::vec3 p_pos, glm::vec3 p_rot, glm::vec3 p_scale);

		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;
	};
}