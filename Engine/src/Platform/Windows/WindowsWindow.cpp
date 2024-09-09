#include "ccpch.h"

#include "WindowsWindow.h"
#include "Events/MouseEvent.h"
#include "Events/KeyEvent.h"
#include "Events/ApplicationEvent/ApplicationEvent.h"

#include <glad/glad.h>

namespace Cannis {
	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int error, const char* description) {
		CC_CORE_ERROR("GLFW error ({0}): {1}", error, description);
	}

	Window* Window::Create(const WindowProps& p_props) {
		return new WindowsWindow(p_props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& p_props) {
		Init(p_props);
	}

	WindowsWindow::~WindowsWindow() {
		Shutdown();
	}

	void WindowsWindow::OnUpdate() {
		glfwPollEvents();
		glfwSwapBuffers(m_window);
	}
	
	void WindowsWindow::SetVSync(bool p_enabled) {
		if (p_enabled) 
			glfwSwapInterval(1);

		else
			glfwSwapInterval(0);

		m_data.vsync = p_enabled;
	}
	void WindowsWindow::IsVSync() const {

	}
	
	void WindowsWindow::Init(const WindowProps& p_props) {
		m_data.width = p_props.width;
		m_data.height = p_props.height;
		m_data.title = p_props.title;

		CC_CORE_INFO("Creating Window {0} ({1}, {2})", p_props.title, p_props.width, p_props.height);

		if (!s_GLFWInitialized) {
			int success = glfwInit();
			CC_CORE_ASSERT(success, "Could not initialize GLFW");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		m_window = glfwCreateWindow((int)p_props.width, (int)p_props.height, p_props.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_window);

		int gladStatus = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		CC_CORE_ASSERT(gladStatus, "Failed to initialize GLAD");

		glfwSetWindowUserPointer(m_window, &m_data);
		SetVSync(true);

		// GLFW Callbacks
		glfwSetWindowSizeCallback(m_window, [](GLFWwindow* p_window, int p_width, int p_height) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(p_window);
			data.width = p_width;
			data.height = p_height;

			WindowResizeEvent windowEvent(p_width, p_height);
			data.eventCallback(windowEvent);
		});

		glfwSetWindowCloseCallback(m_window, [](GLFWwindow* p_window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(p_window);
			
			WindowCloseEvent windowEvent;
			data.eventCallback(windowEvent);
		});

		glfwSetKeyCallback(m_window, [](GLFWwindow* p_window, int p_key, int p_scancode, int p_action, int p_mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(p_window);

			switch (p_action) {
				case GLFW_PRESS: {
					KeyPressedEvent keyPressedEvent(p_key, 0);
					data.eventCallback(keyPressedEvent);
				}
					break;

				case GLFW_RELEASE: {
						KeyReleasedEvent keyReleasedEvent(p_key);
						data.eventCallback(keyReleasedEvent);
				}
					break;

				case GLFW_REPEAT: {
					KeyPressedEvent keyRepeatEvent(p_key, 1);
					data.eventCallback(keyRepeatEvent);
				}
					break;
			}
		});

		glfwSetMouseButtonCallback(m_window, [](GLFWwindow* p_window, int p_button, int p_action, int p_mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(p_window);

			switch (p_action) {
				case GLFW_PRESS: {
					KeyPressedEvent keyPressedEvent(p_button, 0);
					data.eventCallback(keyPressedEvent);
				}
					break;

				case GLFW_RELEASE: {
					KeyReleasedEvent keyReleasedEvent(p_button);
					data.eventCallback(keyReleasedEvent);
				}
					break;
			}
		});

		glfwSetScrollCallback(m_window, [](GLFWwindow* p_window, double p_xoffset, double p_yoffset) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(p_window);

			MouseScrolledEvent mouseEvent(p_xoffset, p_yoffset);
			data.eventCallback(mouseEvent);
		});

		glfwSetCursorPosCallback(m_window, [](GLFWwindow* p_window, double p_xPos, double p_yPos) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(p_window);

			MouseMovedEvent mouseEvent((float)p_xPos, (float)p_yPos);
			data.eventCallback(mouseEvent);
		});
	}
	
	void WindowsWindow::Shutdown()	{
		glfwDestroyWindow(m_window);
	}
}