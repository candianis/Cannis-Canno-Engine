#include "ccpch.h"

#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Cannis {
	OpenGLContext::OpenGLContext(GLFWwindow* p_windowHandle) : m_windowHandle(p_windowHandle) {
		CC_CORE_ASSERT(m_windowHandle, "GLFW window was null");
	}

	void OpenGLContext::Init() {
		glfwMakeContextCurrent(m_windowHandle);
		
		int gladStatus = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		CC_CORE_ASSERT(gladStatus, "Failed to initialize GLAD");
	}

	void OpenGLContext::SwapBuffers() {
		glfwSwapBuffers(m_windowHandle);
	}
}