#include "ccpch.h"
#include "Camera.h"
#include "Core/Application.h"

namespace Cannis {
	Camera::Camera(const glm::vec3& p_position, const glm::vec3& p_front, const glm::vec3& p_up) : position(p_position), rotation(0), m_front(p_front), m_up(p_up) {
		m_front = glm::vec3(0.0f, 0.0f, -1.0f);
		m_worldUp = m_up;
		
		fov = 0;

		rotation.z = 45;

		UpdateCameraVectors();
		RecalculateViewMatrix();
	}

	void Camera::Update() {
		RecalculateViewMatrix();
		UpdateCameraVectors();
	}

	void Camera::RecalculateViewMatrix() {
		m_viewMatrix = glm::lookAt(position, position + m_front, m_up);
	}

	const glm::mat4& Camera::GetViewMatrix() const {
		return m_viewMatrix;
	}

	const glm::mat4& Camera::GetProjectionMatrix() const {
		return m_projectionMatrix;
	}

	const glm::mat4& Camera::GetViewProjectionMatrix() const {
		return m_projectionMatrix * m_viewMatrix;
	}

	void Camera::SetPerspective(float p_fov, float p_aspect, float p_near, float p_far) {
		m_projectionMatrix = glm::perspective(p_fov, p_aspect, p_near, p_far);
		fov = p_fov;
		aspect = p_aspect;
		Near = p_near;
		Far = p_far;
		
	}

	void Camera::UpdateCameraVectors() {
		// Calculate front vector
		glm::vec3 front;
		front.x = cos(glm::radians(rotation.z) * cos(glm::radians(rotation.y)));
		front.y = sin(glm::radians(rotation.y));
		front.z = sin(glm::radians(rotation.z) * cos(glm::radians(rotation.y)));
		front = glm::normalize(front);
		m_right = glm::normalize(glm::cross(m_front, m_worldUp));
		m_up = glm::normalize(glm::cross(m_right, m_front));
	}
}