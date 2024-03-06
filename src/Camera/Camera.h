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

	Camera(vec3 position = vec3(0.0f), float speed = 3.0f, float sensitivity = 0.1f);

	glm::mat4 getViewMatrix();

	void moveCamera(CameraMovement direction, double delta);
	void rotateCamera(float xOffset, float yOffset);

private: 
	void updateVectors();
};

