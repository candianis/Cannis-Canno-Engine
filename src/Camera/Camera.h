#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

using glm::vec3;

enum CameraMovement {
	FORWARD,
	BACKWARD,
	RIGHT,
	LEFT,
	NONE
};

class Camera
{
public:
	vec3 position;

	vec3 up;
	vec3 front;
	vec3 right;

	float speed;
	float sensitivity;

	//Euler angles
	float yaw;
	float pitch;

	CameraMovement camMovement;

	Camera(vec3 position, float speed, float sensitivity);

	glm::mat4 GetViewMatrix();

	void MoveCamera(CameraMovement direction, double delta);
	void RotateCamera(float xOffset, float yOffset);

private: 
	void UpdateVectors();
};

