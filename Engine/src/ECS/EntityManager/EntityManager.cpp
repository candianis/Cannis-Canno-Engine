#include "ccpch.h"
#include "EntityManager.h"

namespace Cannis {
	EntityManager::EntityManager() {
		for (size_t i = 0; i < MaxEntities; i++) {
			m_availableIDs.push(i);
		}
	}

	EntityManager::~EntityManager() {

	}

	Entity& EntityManager::CreateEntity() {
		if (m_availableIDs.empty()) {
			CC_ASSERT(m_availableIDs.empty(), "Max amount of entities has been reached")
		}

		Entity newEntity(m_availableIDs.front());
		m_availableIDs.pop();

		return newEntity;
	}

	void EntityManager::DestroyEntity(const Entity& p_entity) {
		m_entities.erase(std::remove_if(m_entities.begin(), m_entities.end(), [&p_entity](Entity other) {
			return p_entity == other;
			}), m_entities.end());
	}

	void EntityManager::SetSignature(const Entity& p_entity, Signature& p_signature) {
		m_signatures[p_entity.GetID()] = p_signature;
	}

	Signature& EntityManager::GetSignature(const Entity& p_entity)
	{
		return m_signatures[p_entity.GetID()];
	}
}