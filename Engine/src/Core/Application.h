#pragma once

#include "ccpch.h"

#include "Core.h"
#include "Events/Event.h"
#include "Events/SysEventDispatcher/SysEventDispatcher.h"
#include "Window/Window.h"
#include "Root/Root.h"
#include "Subsystem/Subsystem.h"
#include "UI/UIService.h"
#include "ECS/World/World.h"

#include "Renderer/Shader/Shader.h"
#include "Renderer/VertexBuffer/VertexBuffer.h"
#include "Renderer/IndexBuffer/IndexBuffer.h"
#include "Renderer/VertexArray/VertexArray.h"

namespace Cannis {
	class CANNIS_API Application {
	private:
		static Application* s_instance;
		std::unique_ptr<Shader> m_shader;
		std::shared_ptr<VertexBuffer> m_vertexBuffer;
		std::shared_ptr<IndexBuffer> m_indexBuffer;
		std::unique_ptr<VertexArray> m_vertexArray;

	private:
		std::unique_ptr<Window> m_window;
		std::shared_ptr<SysEventDispatcher> m_eventDispatcher;
		std::shared_ptr<WorldCoordinator> m_worldCoordinator;
		std::unique_ptr<UIService> m_uiService;
		bool m_running;

		void OnWindowClose(const SysEvent& p_event);

	public:
		Application();
		virtual ~Application();

		void Run();

		template<typename SystemType>
		void AddSubsystem();

		void OnSysEvent(SysEvent& p_event);

		inline static Application& Get() { return *s_instance; }
		inline Window& GetWindow() { return *m_window; }

		inline std::shared_ptr<WorldCoordinator>& GetCoordinator() { return m_worldCoordinator; }
	};

	Application* CreateApplication();

	template<typename SystemType>
	inline void Application::AddSubsystem() {
		m_worldCoordinator->AddSubsystem<SystemType>();
	}
}