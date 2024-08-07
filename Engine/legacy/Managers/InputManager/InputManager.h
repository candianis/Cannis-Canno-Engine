#pragma once

#include "../../Camera/Camera.h"

#include <GLFW/glfw3.h>
#include <memory>

using std::shared_ptr;

class InputManager {
public:
	~InputManager() = default;
	// Note: Scott Meyers mentions in his Effective Modern
	//       C++ book, that deleted functions should generally
	//       be public as it results in better error messages
	//       due to the compilers behavior to check accessibility
	//       before deleted status
	InputManager(const InputManager&) = delete;
	InputManager(InputManager&&) = delete;
	InputManager& operator =(const InputManager&) = delete;
	InputManager& operator =(InputManager&&) = delete;

	static void start(shared_ptr<Camera> p_camera);

	static void update(float delta);

	static void mouseCallback(GLFWwindow* window, double xposIn, double yposIn);

private:
	InputManager();
	
	static GLFWwindow* m_window;
	static shared_ptr<Camera> s_camera;

	static bool s_firstMouse;
	static float lastX;
	static float lastY;
};

