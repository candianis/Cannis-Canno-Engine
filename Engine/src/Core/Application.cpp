#include <ccpch.h>
#include "Application.h"
#include <GLFW/glfw3.h>

namespace Cannis {
	Application::Application() {
		m_window = std::unique_ptr<Window>(Window::Create());
		
	}

	Application::~Application() {

	}

	void Application::Run() {
		while (m_running) {
			glClearColor(0, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_window->OnUpdate();
		}
	}
}