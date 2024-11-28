#pragma once

#include "ccpch.h"

namespace Cannis {
	struct PBRLightComponent {
		PBRLightComponent() : position(0), color(0) {}
		
		PBRLightComponent(glm::vec3& p_position, const glm::vec3& p_color) {
			position = p_position;
			color = p_color;
		}

		glm::vec3 position;
		glm::vec3 color;
	};
}