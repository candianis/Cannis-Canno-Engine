#pragma once

#include "ccpch.h"
#include "ECS/Entity/Entity.h"
#include "ECS/Component/Component.h"
#include "ECS/ECSOptions.h"
#include "Events/ECSEvents/ECSEvent.h"

namespace Cannis {
	class IComponentArray {
	public:
		~IComponentArray() = default;
		virtual void OnEntityDestroyed(const SysEvent& p_event) = 0;
	};

	template<typename ComponentType>
	class ComponentArray : public IComponentArray {
	public:
		//ComponentArray() = default;
		//~ComponentArray() = default;

		void InsertData(const Entity& p_entity, ComponentType p_component) {
			CC_ASSERT(m_entityToIndex.find(p_entity) == m_entityToIndex.end(), "Component was added to the same entity.");

			size_t newIndex = m_componentAmount;
			m_entityToIndex[p_entity.GetID()] = newIndex;
			m_indexToEntity[newIndex] = p_entity.GetID();
			m_componentData[newIndex] = p_component;

			++m_componentAmount;
		}

		void RemoveData(const Entity& p_entity) {
			CC_ASSERT(m_entityToIndex.find(p_entity) != m_entityToIndex.end());
			
			size_t indexOfRemovedEntity = m_entityToIndex[p_entity.GetID()];
			size_t indexOfLastElement = m_componentAmount - 1;
			m_componentData[indexOfRemovedEntity] = m_componentData[indexOfLastElement];

			uint32_t idOfLastElement = m_indexToEntity[indexOfLastElement];
			m_entityToIndex[idOfLastElement] = indexOfRemovedEntity;
			m_indexToEntity[indexOfRemovedEntity] = idOfLastElement;

			m_entityToIndex.erase(p_entity.GetID());
			m_indexToEntity.erase(indexOfLastElement);

			--m_componentAmount;
		}

		ComponentType& GetComponent(const Entity& p_entity) {
			CC_ASSERT(m_entityToIndex.find(p_entity.GetID()) != m_entityToIndex.end(), "Trying to retrieve non existing component from entity");

			return m_componentData[m_entityToIndex[p_entity.GetID()]];
		}

		void OnEntityDestroyed(const SysEvent& p_event) override {
			const EntityDestroyedEvent& curEvent = static_cast<const EntityDestroyedEvent&>(p_event);

			if (m_entityToIndex.find(curEvent.GetEntityID()) != m_entityToIndex.end()) {
				RemoveData(curEvent.GetEntityID());
			}
		}

	private:
		std::array<ComponentType, MaxEntities> m_componentData;
		std::unordered_map<uint32_t, size_t> m_entityToIndex;
		std::unordered_map<size_t, uint32_t> m_indexToEntity;
		size_t m_componentAmount;
	};
}