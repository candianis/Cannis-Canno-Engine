#include "ccpch.h"
#include "WindowsWindow.h"

namespace Cannis {
	static bool s_GLFWInitialized = false;

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

			s_GLFWInitialized = true;
		}

		m_window = glfwCreateWindow((int)p_props.width, (int)p_props.height, p_props.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_window);
		glfwSetWindowUserPointer(m_window, &m_data);
		SetVSync(true);
	}
	
	void WindowsWindow::Shutdown()	{
		glfwDestroyWindow(m_window);
	}
}