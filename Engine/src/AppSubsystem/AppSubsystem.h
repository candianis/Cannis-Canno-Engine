#pragma once

#include "Core/Core.h"
#include "Subsystem/Subsystem.h"
#include "Events/AppEvent/AppEvent.h"

namespace Cannis {
	class CANNIS_API AppSubsystem : public Subsystem {
	public:
		AppSubsystem();
		~AppSubsystem();

		void Update() override;

		void SubscribeToEvent(const std::unique_ptr<SysEventDispatcher>& p_eventBus) override;

		void OnWindowClose(WindowCloseEvent& p_event);
		void OnWindowResize(WindowResizeEvent& p_event);

	private:

	};
}