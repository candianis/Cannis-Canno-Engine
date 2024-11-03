#include <ccpch.h>

#include "Application.h"
#include "Events/AppEvent/AppEvent.h"
#include "Events/MouseEvent.h"

#include "Input/Input.h"

#include <glad/glad.h>

namespace Cannis {
	Application* Application::s_instance = nullptr;

	Application::Application() : m_running(true) {
		CC_ASSERT(!s_instance, "Application already exists");
		s_instance = this;

		m_window = std::unique_ptr<Window>(Window::Create());
		m_window->SetSysEventCallback(std::bind(&Application::OnSysEvent, this, std::placeholders::_1));
		m_uiService = std::make_unique<UIService>();
		
		m_eventDispatcher = std::make_shared<SysEventDispatcher>();
		m_eventDispatcher->Subscribe(EventType::WindowClose, std::bind(&Application::OnWindowClose, this, std::placeholders::_1));

		m_worldCoordinator = std::make_shared<WorldCoordinator>(m_eventDispatcher);
		m_worldCoordinator->Init();
		m_worldCoordinator->SubscribeToEvent();
	}

	Application::~Application() {
		m_worldCoordinator->Shutdown();
	}

	void Application::Run() {
		while (m_running) {
			glClearColor(0, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_worldCoordinator->Update();

			m_uiService->Begin();
			m_uiService->Update();
			m_worldCoordinator->OnUIRender();
			m_uiService->End();
			
			m_window->OnUpdate();
		}
	}

	void Application::OnSysEvent(SysEvent& p_event) {
		m_eventDispatcher->EmitEvent(p_event);
	}

	void Application::OnWindowClose(const SysEvent& p_event) {
		m_running = false;
	}
}
