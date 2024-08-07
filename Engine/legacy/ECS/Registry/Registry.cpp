#include "Registry.h"

uint32_t Registry::m_existingEntities;
vector<Entity> Registry::m_entities;
deque<uint32_t> Registry::m_reusableIDs;
vector<shared_ptr<IPool>> Registry::m_componentPools;
vector<Signature> Registry::m_entityComponentSignatures;
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

    Entity newEntity = Entity(newEntityID);
    std::shared_ptr<Entity> ptrEntity = std::make_shared<Entity>(newEntity);
    return ptrEntity;
}

void Registry::killEntity(const shared_ptr<Entity>& p_entity) {
    
}

void Registry::addEntityToSystem(Entity p_entity) {

}

void Registry::removeEntityFromSystems(Entity p_entity) {

}

Registry::Registry() {
    
}