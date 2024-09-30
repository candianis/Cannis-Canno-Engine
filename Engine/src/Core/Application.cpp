#include <ccpch.h>

#include "Application.h"
#include "Events/AppEvent/AppEvent.h"
#include "Events/MouseEvent.h"

#include <glad/glad.h>

namespace Cannis {
	Application* Application::s_instance = nullptr;

	Application::Application() : m_running(true) {
		CC_ASSERT(!s_instance, "Application already exists");
		s_instance = this;

		m_window = std::unique_ptr<Window>(Window::Create());
		m_window->SetSysEventCallback(std::bind(&Application::OnSysEvent, this, std::placeholders::_1));

		m_sysEventDispatcher = std::make_unique<SysEventDispatcher>();
		m_sysEventDispatcher->Subscribe(EventType::WindowClose, std::bind(&Application::OnWindowClose, this, std::placeholders::_1));

		m_root.Init();
		m_root.SubscribeSystemsToEvents(m_sysEventDispatcher);
	}

	Application::~Application() {
		m_root.Shutdown();
	}

	void Application::Run() {
		while (m_running) {
			glClearColor(0, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_root.Update();

			m_window->OnUpdate();
		}
	}

	void Application::OnSysEvent(SysEvent& p_event) {
		CC_CORE_INFO("Sys event was called: " + p_event.ToString());
		m_sysEventDispatcher->EmitEvent(p_event);
	}

	void Application::OnWindowClose(const SysEvent& p_event) {
		CC_CORE_INFO("Sys event was sent to the application through the dispatcher");
		m_running = false;
	}
}
