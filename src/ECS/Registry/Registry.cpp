#include "Registry.h"

uint32_t Registry::m_existingEntities;
vector<shared_ptr<Entity>> Registry::m_entities;
vector<shared_ptr<Entity>> Registry::m_entitiesToBeAdded;
vector<shared_ptr<Entity>> Registry::m_entitiesToBeDeleted;
deque<uint32_t> Registry::m_reusableIDs;
vector<shared_ptr<IPool>> Registry::m_componentPools;
vector<shared_ptr<Signature>> Registry::m_entityComponentSignatures;
unordered_map<type_index, shared_ptr<System>> m_systems;

Registry& Registry::getInstance() {
    static Registry instance;
    return instance;
}

void Registry::update() {

}

shared_ptr<Entity> Registry::createEntity() {
    uint32_t newEntityID;
    //If there are no free ids waiting to be reused then...
    if (m_reusableIDs.empty()) {
        newEntityID = m_existingEntities++;
        if (newEntityID >= m_entityComponentSignatures.size()) {
            m_entityComponentSignatures.resize(static_cast<size_t>(newEntityID + 10));
        }
    }

    else {  
        newEntityID = m_reusableIDs.front();
        m_reusableIDs.pop_front();
    }

    shared_ptr<Entity> newEntity = std::make_shared<Entity>(newEntityID);
    m_entitiesToBeAdded.push_back(newEntity);

    return newEntity;
}

void Registry::killEntity(const shared_ptr<Entity>& p_entity) {
    m_entitiesToBeDeleted.push_back(p_entity);
}

void Registry::addEntityToSystem(Entity p_entity) {

}

void Registry::removeEntityFromSystems(Entity p_entity) {

}

Registry::Registry() {
    
}