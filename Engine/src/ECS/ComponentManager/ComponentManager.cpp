#include "ccpch.h"
#include "ComponentManager.h"

namespace Cannis {
	void ComponentManager::SubscribeToEvent(const std::shared_ptr<SysEventDispatcher>& p_eventDispatcher) {
		p_eventDispatcher->Subscribe(EventType::EntityDestroyed, std::bind(&ComponentManager::OnEntityDestroyed, this, std::placeholders::_1));
	}

	void ComponentManager::OnEntityDestroyed(const SysEvent& p_event) {
		for (auto const& pair : m_componentArrays) {
			const auto& componentArray = pair.second;

			componentArray->OnEntityDestroyed(p_event);
		}
	}
}