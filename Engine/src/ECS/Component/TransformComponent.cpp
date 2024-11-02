#include "ccpch.h"
#include "TransformComponent.h"

namespace Cannis {
	TransformComponent::TransformComponent() : position(0), rotation(0), scale(1) {

	}

	TransformComponent::TransformComponent(glm::vec3 p_pos, glm::vec3 p_rot, glm::vec3 p_scale) : position(p_pos), rotation(p_rot), scale(p_scale) {

	}
}