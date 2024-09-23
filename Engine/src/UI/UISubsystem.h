#pragma once

#include "ccpch.h"
#include "Core/Core.h"

#include "imgui.h"
#include "Platform/OpenGL/imgui_impl_opengl3.h"

#include "Subsystem/Subsystem.h"
#include "Events/EventBus/EventBus.h"
#include "Events/MouseEvent.h"
#include "Events/AppEvent/AppEvent.h"

#include <GLFW/glfw3.h>

namespace Cannis {
	class CANNIS_API UISubsystem : public Subsystem {
	public:
		UISubsystem();
		~UISubsystem();

		void Update() override;
		void Shutdown() override;
		void OnEvent(SysEvent& p_event) override;

		void SubscribeToEvent(const std::unique_ptr<EventBus>& p_eventBus) override;

		void OnMouseButtonPressedEvent(MouseButtonPressedEvent& p_event);
		void OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& p_event);
		void OnMouseScrolled(MouseScrolledEvent& p_event);
		void OnMouseMovedEvent(MouseMovedEvent& p_event);

	private:
		void CreateEditor();

		float m_time;
	};
}