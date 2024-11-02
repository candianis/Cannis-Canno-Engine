#pragma once

#include "ccpch.h"
#include "ECS/Entity/Entity.h"
#include "ECS/Component/Component.h"
#include "ECS/ComponentArray/ComponentArray.h"
#include "ECS/ECSOptions.h"
#include "Events/SysEventDispatcher/SysEventDispatcher.h"

namespace Cannis {
	class CANNIS_API ComponentManager {
	public:
		ComponentManager() : m_nextComponentID(0) {}
		~ComponentManager() = default;

		template<typename ComponentType>
		void RegisterComponent();

		template<typename ComponentType>
		uint8_t& GetComponentID() const;

		template<typename ComponentType>
		void AddComponent(const Entity& p_entity, ComponentType& p_component);

		template<typename ComponentType, typename ...ComponentArgs>
		void AddComponent(const Entity& p_entity, ComponentArgs&& ...Args);

		template<typename ComponentType>
		void RemoveComponent(const Entity& p_entity);

		template<typename ComponentType>
		ComponentType& GetComponent(const Entity& p_entity);

		void SubscribeToEvent(const std::shared_ptr<SysEventDispatcher>& p_eventDispatcher);
		void OnEntityDestroyed(const SysEvent& p_event);

	private:
		std::unordered_map<std::type_index, uint8_t> m_componentTypes;
		std::unordered_map<std::type_index, std::shared_ptr<IComponentArray>> m_componentArrays;
		uint8_t m_nextComponentID;
	};

	template<typename ComponentType>
	inline void ComponentManager::RegisterComponent() {
		CC_ASSERT(m_componentTypes.find(std::type_index(typeid(ComponentType))), "Registering component more than once");

		//Register the new component 
		//m_componentTypes.insert(std::make_pair(std::type_index(typeid(ComponentType)), m_nextComponentID));
		m_componentTypes.insert({ std::type_index(typeid(ComponentType)), m_nextComponentID });
		
		//m_test.insert({ std::type_index(typeid(ComponentType)), std::make_shared<ComponentType>() });

		//Create a new array of components of the type
		std::type_index componentID = std::type_index(typeid(ComponentType));
		std::shared_ptr<ComponentArray<ComponentType>> newComponentArray = std::make_shared<ComponentArray<ComponentType>>();
		m_componentArrays.emplace(std::make_pair(componentID, newComponentArray));
		//m_componentArrays.insert({ std::type_index(typeid(ComponentType)), newComponentArray });

		//m_componentLists[0] = newComponentArray;

		++m_nextComponentID;
	}

	template<typename ComponentType>
	inline uint8_t& ComponentManager::GetComponentID() const {
		CC_ASSERT(m_componentTypes.find(std::type_index(typeid(ComponentType))) != m_componentTypes.end());

		uint8_t testI = m_componentTypes.at(std::type_index(typeid(ComponentType)));

		return testI;
	}

	template<typename ComponentType>
	inline void ComponentManager::AddComponent(const Entity& p_entity, ComponentType& p_component) {
		GetComponentArray<ComponentType>()->InsertData(p_entity, p_component);
	}

	template<typename ComponentType, typename ...ComponentArgs>
	inline void ComponentManager::AddComponent(const Entity& p_entity, ComponentArgs && ...Args) {
		CC_ASSERT(m_componentTypes.find(std::type_index(typeid(ComponentType))) != m_componentTypes.end(), "Component has not been registered");

		ComponentType newComponent(std::forward<ComponentArgs>(Args)...);
		std::type_index componentID = std::type_index(typeid(ComponentType));
		std::shared_ptr<ComponentArray<ComponentType>> componentArray = std::static_pointer_cast<ComponentArray<ComponentType>>(m_componentArrays[componentID]);

		componentArray->InsertData(p_entity, newComponent);
	}

	template<typename ComponentType>
	inline void ComponentManager::RemoveComponent(const Entity& p_entity) {
		std::type_index componentID = std::type_index(typeid(ComponentType));
		std::shared_ptr<ComponentArray<ComponentType>> componentArray = std::static_pointer_cast<ComponentArray<ComponentType>>(m_componentArrays[componentID]);

		componentArray->RemoveData(p_entity);
	}

	template<typename ComponentType>
	inline ComponentType& ComponentManager::GetComponent(const Entity& p_entity) {
		std::type_index componentID = std::type_index(typeid(ComponentType));
		std::shared_ptr<ComponentArray<ComponentType>> componentArray = std::static_pointer_cast<ComponentArray<ComponentType>>(m_componentArrays[componentID]);
		
		return componentArray->GetComponent(p_entity);
	}
}