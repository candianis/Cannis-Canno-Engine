#include "ccpch.h"
#include "WindowsInput.h"

#include <GLFW/glfw3.h>
#include "Core/Application.h"

namespace Cannis {
	Input* Input::s_instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedImpl(int p_keyCode) {
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		
		int state = glfwGetKey(window, p_keyCode);

		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int p_mouseButton) {
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		int state = glfwGetMouseButton(window, p_mouseButton);

		return state == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::GetMousePosImpl() {
		GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		double xPos, yPos;
		glfwGetCursorPos(window, &xPos, &yPos);

		return { (float)xPos, (float)yPos };
	}

	float WindowsInput::GetMouseXImpl() {
		auto [x, y] = GetMousePosImpl();
		return x;
	}

	float WindowsInput::GetMouseYImpl() {
		auto [x, y] = GetMousePosImpl();
		return y;
	}
}