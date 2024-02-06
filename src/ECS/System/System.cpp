#include "System.h"

void System::AddEntityToSystem(Entity entity)
{
	entities.push_back(entity);
}

void System::RemoveEntityFromSystem(Entity entity)
{
	entities.erase(std::remove_if(entities.begin(), entities.end(), [&entity](Entity other) {
		return entity.GetID() == other.GetID();
		}), entities.end());
}

std::vector<Entity> System::GetSystemEntities() const
{
	return entities;
}
