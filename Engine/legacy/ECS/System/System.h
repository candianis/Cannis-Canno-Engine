#pragma once

#include "../Entity/Entity.h"
#include "../../Utilities/Signature/Signature.h"

#include <memory>
#include <vector>

using std::vector;
using std::shared_ptr;

class Entity;

class System {
private:
	// @brief Bitset with the components this system is interested in
	Signature m_systemComponents;

	// @brief List of all the entities that have the desired components
	// @Note This list will not be updated and cleaned each frame, instead if an Entity removes a critical component
	// it will be discarded from the list
	std::vector<shared_ptr<Entity>> entities;

public:
	System() = default;
	~System() = default;

	void AddEntityToSystem(const shared_ptr<Entity> entity);
	void RemoveEntityFromSystem(const shared_ptr<Entity> entity);
	std::vector<shared_ptr<Entity>> GetSystemEntities() const;
};

