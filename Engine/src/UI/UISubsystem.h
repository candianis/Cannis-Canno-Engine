#pragma once

#include "ccpch.h"
#include "Core/Core.h"

#include "imgui.h"
#include "Platform/OpenGL/imgui_impl_opengl3.h"

#include "Subsystem/Subsystem.h"
#include "Events/EventBus/EventBus.h"
#include "Events/MouseEvent.h"
#include "Events/AppEvent/AppEvent.h"
#include "Events/KeyboardEvent/KeyEvent.h"

#include <GLFW/glfw3.h>

namespace Cannis {
	class CANNIS_API UISubsystem : public Subsystem {
	public:
		UISubsystem();
		~UISubsystem();

		void Update() override;
		void Shutdown() override;
		void OnEvent(SysEvent& p_event) override;

		void SubscribeToEvent(const std::unique_ptr<SysEventDispatcher>& p_sysEventDispatcher) override;

		// Window events
		void OnWindowClose(const SysEvent& p_event);
		void OnWindowResize(const SysEvent& p_event);

		// Mouse Events
		void OnMouseButtonPressedEvent(const SysEvent& p_event);
		void OnMouseButtonReleasedEvent(const SysEvent& p_event);
		void OnMouseScrolledEvent(const SysEvent& p_event);
		void OnMouseMovedEvent(const SysEvent& p_event);

		//Keyboard events
		void OnKeyPressedEvent(const SysEvent& p_event);
		void OnKeyReleasedEvent(const SysEvent& p_event);
		void OnKeyTypedEvent(const SysEvent& p_event);

	private:
		void CreateEditor();

		float m_time;
	};
}