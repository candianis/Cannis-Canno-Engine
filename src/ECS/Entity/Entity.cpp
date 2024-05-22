#include "Entity.h"

Entity::Entity(uint32_t p_ID) : m_ID(p_ID), transform(), name("Entity") {
	
}

Entity::Entity(const Entity& entity) {
	transform = entity.transform;
	name = entity.name + " (Copy)";
	m_ID = entity.getID();
}

uint32_t Entity::getID() const {
	return m_ID;
}

void Entity::kill() const {
	//Registry::getInstance().killEntity(std::make_shared<Entity>(this));
}