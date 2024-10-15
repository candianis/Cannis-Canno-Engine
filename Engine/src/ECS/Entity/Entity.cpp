#include "ccpch.h"
#include "Entity.h"

namespace Cannis {
	Entity::Entity(const Entity& p_entity, const uint32_t& p_ID) {
		name = p_entity.name + " (Copy)";
		m_ID = p_ID;
	}
}
