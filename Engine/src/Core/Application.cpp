#include <ccpch.h>
#include "Application.h"
#include <GLFW/glfw3.h>

namespace Cannis {
	Application::Application() {
		m_window = std::unique_ptr<Window>(Window::Create());
		m_window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
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

	void Application::OnEvent(Event& p_event) {
		EventDispatcher dispatcher(p_event);
		dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));

		CC_CORE_INFO(p_event.ToString());
	}

	bool Application::OnWindowClose(WindowCloseEvent& p_event) {
		m_running = false;
		return true;
	}
}
