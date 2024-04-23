#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

using glm::vec3;
using glm::quat;

struct Transform {
	vec3 position;
	quat rotation;
	vec3 scale;
};

