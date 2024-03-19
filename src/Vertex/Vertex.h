#pragma once

#include <glm/glm.hpp>

#define MAX_BONE_INFLUENCE 4

namespace Cannis {

	struct Vertex {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texCoord;
        glm::vec3 tangent;
        glm::vec3 bitangent;

        //bone indexes which will influence this vertex
        int boneIDs[MAX_BONE_INFLUENCE];
        //weights from each bone
        float weights[MAX_BONE_INFLUENCE];

		Vertex();
	};

}