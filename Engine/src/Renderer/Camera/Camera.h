#pragma once

#include "ccpch.h"

namespace Cannis {
	class Camera {
	public:
		Camera(const glm::vec3& p_position, const glm::vec3& p_front = glm::vec3(0.0f, 0.0f, -1.0f), const glm::vec3& p_up = glm::vec3(0.0f, 1.0f, 0.0f));

		void Update();
		void RecalculateViewMatrix();
		const glm::mat4& GetViewMatrix() const;
		const glm::mat4& GetProjectionMatrix() const;
		const glm::mat4& GetViewProjectionMatrix() const;

		void SetPerspective(float p_fov, float p_aspect, float p_near, float p_far);

	private:
		void UpdateCameraVectors();

	public:
		float fov;
		float aspect;
		float Near;
		float Far;
		float yaw;
		float pitch;

		glm::vec3 position;

	private:
		glm::mat4 m_projectionMatrix;
		glm::mat4 m_viewMatrix;

		//Attributes
		glm::vec3 m_front;
		glm::vec3 m_up;
		glm::vec3 m_right;
		glm::vec3 m_worldUp;

	};
}