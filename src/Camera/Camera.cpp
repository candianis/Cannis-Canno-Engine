#include "Camera.h"

Camera::Camera(vec3 position, float speed, float sensitivity) {
	this->position = position;
	this->speed = speed;
	this->sensitivity = sensitivity;

	this->up = vec3(0.0f, 1.0f, 0.0f);
	this->front = vec3(0.0f, 0.0f, -1.0f);

	yaw = -90.0f;
	pitch = 0.0f;
	UpdateVectors();

	camMovement = CameraMovement::NONE;
}

glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(position, position + front, up);
}

void Camera::MoveCamera(CameraMovement direction, double delta)
{
	float modifiedSpeed = static_cast<float>(speed * delta);
	switch (direction) {
		case FORWARD:
			position += modifiedSpeed * front;
			break;
		case BACKWARD:
			position -= modifiedSpeed * front;
			break;

		case RIGHT:
			position += glm::normalize(glm::cross(front, up)) * modifiedSpeed;
			break;
		case LEFT:
			position -= glm::normalize(glm::cross(front, up)) * modifiedSpeed;
			break;
	}
}

void Camera::RotateCamera(float xOffset, float yOffset)
{
	xOffset *= sensitivity;
	yOffset *= sensitivity;

	yaw += xOffset;
	pitch += yOffset;

	UpdateVectors();
}

void Camera::UpdateVectors()
{
	glm::vec3 newFront;
	newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	newFront.y = sin(glm::radians(pitch));
	newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	this->front = glm::normalize(newFront);
	// also re-calculate the Right and Up vector
	right = glm::normalize(glm::cross(front, up));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	up = glm::normalize(glm::cross(right, front));
}
