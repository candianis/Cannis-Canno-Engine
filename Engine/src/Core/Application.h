#pragma once

#include "ccpch.h"
#include "Core.h"
#include "Events/Event.h"
#include "Events/SysEventDispatcher/SysEventDispatcher.h"
#include "Events/ApplicationEvent/ApplicationEvent.h"
#include "Window/Window.h"
#include "Root/Root.h"

namespace Cannis {
	class CANNIS_API Application {
	private:
		static Application* s_instance;

	private:
		std::unique_ptr<Window> m_window;
		std::unique_ptr<SysEventDispatcher> m_sysEventDispatcher;
		Root m_root;
		bool m_running;

		void OnWindowClose(const SysEvent& p_event);

	public:
		Application();
		virtual ~Application();

		void Run();

		void OnSysEvent(SysEvent& p_event);

		inline static Application& Get() { return *s_instance; }
		inline Window& GetWindow() { return *m_window; }
	};

	Application* CreateApplication();
}