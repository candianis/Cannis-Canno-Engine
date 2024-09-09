#include "ccpch.h"
#include "AppSubsystem.h"

namespace Cannis {
	AppSubsystem::AppSubsystem() {

	}

	AppSubsystem::~AppSubsystem() {

	}

	void AppSubsystem::Update() {

	}

	void AppSubsystem::SubscribeToEvent(const std::unique_ptr<EventBus>& p_eventBus) {
		p_eventBus->SubscribeToEvent<AppCloseEvent>(this, &AppSubsystem::OnWindowClose);
	}

	void AppSubsystem::OnWindowClose(AppCloseEvent& p_event) {

	}

	void AppSubsystem::OnWindowResize(AppResizeEvent& p_event) {

	}
}