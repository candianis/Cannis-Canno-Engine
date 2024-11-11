#pragma once 

#include "Core/Core.h"
#include "Component.h"

namespace Cannis {
	struct CANNIS_API TransformComponent {
	public:
		TransformComponent() : position(0), rotation(0), scale(1) {}
		TransformComponent(glm::vec3 p_pos, glm::vec3 p_rot, glm::vec3 p_scale) : position(p_pos), rotation(p_rot), scale(p_scale) {}

		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 scale;
	};
}