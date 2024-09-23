#pragma once

#include "ccpch.h"
#include "Core.h"
#include "Events/Event.h"
#include "Events/EventBus/EventBus.h"
#include "Events/ApplicationEvent/ApplicationEvent.h"
#include "Window/Window.h"
#include "Root/Root.h"

namespace Cannis {
	class CANNIS_API Application {
	private:
		static Application* s_instance;

	private:
		std::unique_ptr<Window> m_window;
		std::unique_ptr<EventBus> m_eventBus;
		std::vector<std::unique_ptr<Event>> m_events;
		Root m_root;
		bool m_running;

		bool OnWindowClose(WindowCloseEvent& p_event);


	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& p_event);

		inline static Application& Get() { return *s_instance; }
		inline Window& GetWindow() { return *m_window; }
	};

	Application* CreateApplication();
}