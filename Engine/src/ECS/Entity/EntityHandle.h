#pragma once

#include "ccpch.h"
#include "Core/Core.h"
#include "Entity.h"
#include "ECS/World/World.h"
#include "ECS/Component/TransformComponent.hpp"

namespace Cannis {
	class CANNIS_API EntityHandle {
	private:
		std::shared_ptr<WorldCoordinator> m_world;
		Entity m_entity;
	
	public:
		EntityHandle() = default;
		EntityHandle(std::shared_ptr<WorldCoordinator> p_world);
		EntityHandle(std::shared_ptr<WorldCoordinator> p_world, std::string p_name);

		~EntityHandle() = default;
		
		void Destroy();

		// Component Management
		template<typename ComponentType, typename ...ComponentArgs>
		void AddComponent(ComponentArgs&& ...Args);

		template<typename ComponentType>
		void RemoveComponent();

		template<typename ComponentType>
		ComponentType& GetComponent();

		template<typename ComponentType>
		bool HasComponent();

		// Helper Functions
		TransformComponent& GetTransform();
		void SetPosition(glm::vec3& p_newPosition);
		void SetRotation(glm::vec3& p_newRotation);
		void SetScale(glm::vec3& p_newScale);

		const Entity& GetInstance() const;

	private:
		void Init();
	};

	template<typename ComponentType, typename ...ComponentArgs>
	inline void EntityHandle::AddComponent(ComponentArgs && ...Args) {
		m_world->AddComponent<ComponentType>(m_entity, std::forward<ComponentArgs>(Args)...);
	}

	template<typename ComponentType>
	inline void EntityHandle::RemoveComponent() {
		m_world->RemoveComponent<ComponentType>(m_entity);
	}

	template<typename ComponentType>
	inline ComponentType& EntityHandle::GetComponent() {
		return m_world->GetComponent<ComponentType>(m_entity);
	}

	template<typename ComponentType>
	inline bool EntityHandle::HasComponent() {
		return m_world->HasComponent<ComponentType>(m_entity);
	}
}