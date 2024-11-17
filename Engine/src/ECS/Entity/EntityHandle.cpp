#include "ccpch.h"
#include "EntityHandle.h"

//Only include the essential components all entities should have on creation
#include "ECS/Component/GUIComponent.hpp"

namespace Cannis {
	EntityHandle::EntityHandle(std::shared_ptr<WorldCoordinator> p_world) : m_world(p_world), m_entity(p_world->CreateEntity()) {
		Init();
	}

	EntityHandle::EntityHandle(std::shared_ptr<WorldCoordinator> p_world, std::string p_name) : m_world(p_world), m_entity(p_world->CreateEntity(p_name)) {
		Init();
	}

	void EntityHandle::Destroy() {
		m_world->DestroyEntity(m_entity);
	}

	TransformComponent& EntityHandle::GetTransform() {
		return m_world->GetComponent<TransformComponent>(m_entity);
	}

	void EntityHandle::SetPosition(glm::vec3& p_newPosition) {
		m_world->GetComponent<TransformComponent>(m_entity).position = p_newPosition;
	}

	void EntityHandle::SetRotation(glm::vec3& p_newRotation) {
		m_world->GetComponent<TransformComponent>(m_entity).rotation = p_newRotation;
	}

	void EntityHandle::SetScale(glm::vec3& p_newScale) {
		m_world->GetComponent<TransformComponent>(m_entity).scale = p_newScale;
	}

	const Entity& EntityHandle::GetInstance() const {
		return m_entity;
	}

	void EntityHandle::Init() {
		m_world->AddComponent<GUIComponent>(m_entity);
		m_world->AddComponent<TransformComponent>(m_entity, glm::vec4(0), glm::vec4(0), glm::vec4(1));
	}
}
