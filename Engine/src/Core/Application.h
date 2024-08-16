#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent/ApplicationEvent.h"
#include "Window/Window.h"

namespace Cannis {
	class CANNIS_API Application {
	private:
		std::unique_ptr<Window> m_window;
		bool m_running;

		bool OnWindowClose(WindowCloseEvent& p_event);

	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& p_event);
	};

	Application* CreateApplication();
}