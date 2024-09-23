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
		m_window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

		m_root.Init();
		m_root.SubscribeSystemsToEvents(m_eventBus);
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

	void Application::OnEvent(Event& p_event) {
		EventDispatcher dispatcher(p_event);
		dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));

		switch (p_event.GetEventType()) {
			case EventType::WindowClose:
				m_eventBus->EmitEvent<AppCloseEvent>();
				break;

			case EventType::MouseMoved:
				m_eventBus->EmitEvent<MouseMovedEvent>(13.0f, 13.0f);
				break;

			case EventType::MouseButtonPressed:
				m_eventBus->EmitEvent<MouseButtonPressedEvent>();
				break;

			case EventType::MouseButtonReleased:
				m_eventBus->EmitEvent<MouseButtonReleasedEvent>();
				break;
		}

		CC_CORE_INFO(p_event.ToString());
	}

	bool Application::OnWindowClose(WindowCloseEvent& p_event) {
		m_running = false;
		return true;
	}
}
