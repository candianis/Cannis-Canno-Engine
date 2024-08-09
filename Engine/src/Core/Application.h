#pragma once

#include "Core.h"
#include "Window/Window.h"

namespace Cannis {
	class CANNIS_API Application {
	private:
		std::unique_ptr<Window> m_window;
		bool m_running;

	public:
		Application();
		virtual ~Application();

		void Run();

	};

	Application* CreateApplication();
}