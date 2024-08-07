#pragma once

#include "../Component.h"

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

using glm::vec3;
using glm::quat;

struct Transform {
	vec3 position;
	quat rotation;
	vec3 scale;

	Transform(vec3 p_position = vec3(0, 0, 0), quat p_rotation = quat(0, 0, 0, 0), vec3 p_scale = vec3(1.0f, 1.0f, 1.0f)) {
		position = p_position;
		rotation = p_rotation;
		scale = p_scale;
	}
};