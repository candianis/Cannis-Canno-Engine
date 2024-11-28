#include "ccpch.h"
#include "ComponentManager.h"

#include "ECS/Component/TransformComponent.hpp"
#include "ECS/Component/GUIComponent.hpp"
#include "ECS/Component/ModelComponent.hpp"
#include "ECS/Component/ShaderComponent.hpp"
#include "ECS/Component/MaterialComponent.hpp"
#include "ECS/Component/LightComponent.hpp"
#include "ECS/Component/PBRMaterialComponent.hpp"
#include "ECS/Component/PBRLightComponent.hpp"

namespace Cannis {
	ComponentManager::ComponentManager() : m_nextComponentID(0) {
		//Any component to be used must first be registered here
		//In this order the bitset for each component
		RegisterComponent<TransformComponent>();
		RegisterComponent<ModelComponent>();
		RegisterComponent<GUIComponent>();
		RegisterComponent<ShaderComponent>();
		RegisterComponent<MaterialComponent>();
		RegisterComponent<LightComponent>();
		RegisterComponent<PBRLightComponent>();
		RegisterComponent<PBRMaterialComponent>();
	}

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