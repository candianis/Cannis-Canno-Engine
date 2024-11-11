#include "ccpch.h"
#include "EntityHandle.h"

namespace Cannis {
	EntityHandle::EntityHandle(std::shared_ptr<WorldCoordinator> p_world) : m_world(p_world), entity(p_world->CreateEntity()) {

	}

	EntityHandle::EntityHandle(std::shared_ptr<WorldCoordinator> p_world, std::string p_name) : m_world(p_world), entity(p_world->CreateEntity(p_name)) {
		
	}

	void EntityHandle::Destroy() {
		m_world->DestroyEntity(entity);
	}
}
