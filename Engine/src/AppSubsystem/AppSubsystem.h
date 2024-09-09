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

		void SubscribeToEvent(const std::unique_ptr<EventBus>& p_eventBus) override;

		void OnWindowClose(AppCloseEvent& p_event);
		void OnWindowResize(AppResizeEvent& p_event);

	private:

	};
}