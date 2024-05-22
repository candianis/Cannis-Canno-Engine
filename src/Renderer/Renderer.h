#pragma once

#include "../Camera/Camera.h"
#include "../Managers/ShaderManager/ShaderSlot/ShaderSlot.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <memory>

using std::unique_ptr;
using std::shared_ptr;

class Renderer {
public:
	int screenWidth;
	int screenHeight;
	float fieldOfView;
	
	shared_ptr<Camera> mainCamera;
	ShaderSlot::ShaderSlot currentShader;

	Renderer(int p_screenWidth, int screenHeight, float p_fieldOfView = 45.0f);

	void init();
	void update();
	void clean();

	GLFWwindow* getWindow();
	void enableVSync(bool p_activateVSync);

	static void framebufferSizeCallbackR(GLFWwindow* p_window, int p_screenWidth, int p_screenHeight);

private:
	GLFWwindow* m_window;
};

