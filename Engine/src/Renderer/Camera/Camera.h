#pragma once

#include "ccpch.h"

namespace Cannis {
	class Camera {
	public:
		Camera(const glm::vec3& p_position, const glm::vec3& p_rotation, const float p_fov);

		inline void SetPosition(const glm::vec3& p_newPos) { m_position = p_newPos; }

	private:
		glm::vec3 m_position;
		glm::quat m_rotation;

		//Attributes
		glm::vec3 m_front;
		glm::vec3 m_up;
		glm::vec3 m_right;
		glm::vec3 m_worldUp;

		float m_fov;

	};
}