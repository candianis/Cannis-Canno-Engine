#include "ccpch.h"
#include "Root.h"

namespace Cannis {
	void Root::Init() {
		
	}

	void Root::SubscribeSystemsToEvents(const std::shared_ptr<SysEventDispatcher>& p_sysEventDispatcher) {
		p_sysEventDispatcher->Subscribe(EventType::EntityDestroyed, std::bind(&Root::OnEntityDestroyed, this, std::placeholders::_1));
		p_sysEventDispatcher->Subscribe(EventType::SignatureChanged, std::bind(&Root::OnSignatureChanged, this, std::placeholders::_1));

		for (const auto& pair : m_subsystems) {
			const auto& curSys = pair.second;

			curSys->SubscribeToEvent(p_sysEventDispatcher);
		}
	}

	void Root::OnEntityDestroyed(const SysEvent& p_event) {
		for (const auto& pair : m_subsystems) {
			const auto& curSys = pair.second;

			curSys->OnEntityDestroyed(p_event);
		}
	}

	void Root::OnSignatureChanged(const SysEvent& p_event) {
		for (const auto& pair : m_subsystems) {
			const auto& system = pair.second;

			system->OnSignatureChanged(p_event);
		}
	}

	void Root::Update() {
		for (const auto& pair : m_subsystems) {
			const auto& curSys = pair.second;

			curSys->Update();
		}
	}

	void Root::Shutdown() {
		for (const auto& pair : m_subsystems) {
			const auto& curSys = pair.second;
			
			curSys->Shutdown();
		}
	}
	void Root::OnUIRender() {
		for (const auto& pair : m_subsystems) {
			const auto& curSys = pair.second;

			curSys->OnUIRender();
		}
	}
}