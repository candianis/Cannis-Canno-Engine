#include <ccpch.h>

#include "Application.h"
#include "Events/AppEvent/AppEvent.h"
#include "Events/MouseEvent.h"
#include "Input/Input.h"

#include "Renderer/Buffer/BufferLayout/BufferLayout.h"
#include "Platform/OpenGL/VertexBuffer/OpenGLVertexBuffer.h"

#include "Renderer/Renderer.h"
#include "TimeStep/Timestep.h"

#include <GLFW/glfw3.h>

namespace Cannis {
	Application* Application::s_instance = nullptr;

	Application::Application() : m_running(true), m_lastTime(0.0f) {
		CC_ASSERT(!s_instance, "Application already exists");
		s_instance = this;

		m_window = std::unique_ptr<Window>(Window::Create());
		m_window->SetSysEventCallback(std::bind(&Application::OnSysEvent, this, std::placeholders::_1));
		m_window->SetVSync(false);
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
			//There should be a Platform independent way to get the time like Platform::GetTime() and it returns it depending on whether it is Windows, Linux, Mac
			float time = (float)glfwGetTime();
			Timestep timestep = time - m_lastTime;
			m_lastTime = time;

			m_worldCoordinator->Update(timestep);

			m_uiService->Begin();
			m_uiService->Update(m_worldCoordinator, timestep);
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
