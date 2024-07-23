#include "EntityManager.h"

EntityManager::EntityManager() {
	for (size_t id = 0; id < maxEntities; ++id) {
		m_reusableIDs.push_back(id);
	}

	m_existingEntities = 0;
}

Entity EntityManager::createEntity() {
    uint32_t newEntityID;
    //If there are no free ids waiting to be reused then...
    if (m_reusableIDs.empty()) {
        newEntityID = m_existingEntities++;
        if (newEntityID >= m_entitySignatures.size()) {
            m_entitySignatures.resize(static_cast<size_t>(newEntityID + 10));
        }
    }

    else {
        newEntityID = m_reusableIDs.front();
        m_reusableIDs.pop_front();
    }

    m_existingEntities++;
    Entity newEntity = Entity(newEntityID);
    m_entities.push_back(newEntity);

    return newEntity;
}

void EntityManager::killEntity(const Entity& p_entityToKill) {

}