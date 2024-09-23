#include "ccpch.h"
#include "Root.h"

#include "UI/UISubsystem.h"

namespace Cannis {
	void Root::Init() {
		m_subsystems.push_back(std::make_shared<UISubsystem>());

	}

	void Root::SubscribeSystemsToEvents(const std::unique_ptr<EventBus>& p_eventBus) {
		for (std::shared_ptr<Subsystem>& subsystem : m_subsystems) {
			subsystem->SubscribeToEvent(p_eventBus);
		}
	}

	void Root::Update() {
		for (std::shared_ptr<Subsystem>& subsystem : m_subsystems) {
			subsystem->Update();
		}
	}

	void Root::Shutdown() {
		for (std::shared_ptr<Subsystem>& subsystem : m_subsystems) {
			subsystem->Shutdown();
		}
	}
}