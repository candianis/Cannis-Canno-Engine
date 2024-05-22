#include "System.h"

void System::AddEntityToSystem(const shared_ptr<Entity> p_entity) {
	entities.push_back(p_entity);
}

void System::RemoveEntityFromSystem(const shared_ptr<Entity> p_entity) {
	
	entities.erase(std::remove_if(entities.begin(), entities.end(), [p_entity](shared_ptr<Entity> other) {
		return p_entity->getID() == other->getID();
		}), entities.end());
}

std::vector<shared_ptr<Entity>> System::GetSystemEntities() const {
	return entities;
}
