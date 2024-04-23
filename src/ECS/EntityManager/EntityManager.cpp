#include "EntityManager.h"

EntityManager::EntityManager() {
	for (size_t id = 0; id < maxEntities; ++id) {
		m_availableIDs.push(id);
	}

	m_currentEntityAmount = 0;
}

