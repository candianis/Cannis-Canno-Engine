#pragma once

#include "ccpch.h"
#include "Core/Core.h"
#include "ECS/World/World.h"

#include "Subsystem/Subsystem.h"
#include "Events/MouseEvent.h"
#include "Events/AppEvent/AppEvent.h"
#include "Events/KeyboardEvent/KeyEvent.h"

namespace Cannis {
	class CANNIS_API UIService {
	public:
		UIService();
		~UIService();

		void Begin();
		void End();
		void Update(std::shared_ptr<WorldCoordinator> p_world);
		void Shutdown();

		void SubscribeToEvent(const std::shared_ptr<SysEventDispatcher>& p_sysEventDispatcher);


	private:
		void CreateEditor(std::shared_ptr<WorldCoordinator>& p_world);

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

		float m_time;
	};
}