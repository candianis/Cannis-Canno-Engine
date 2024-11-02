#pragma once

#include "ccpch.h"
#include "Core/Core.h"
#include "Entity.h"
#include "ECS/World/World.h"

namespace Cannis {
	class CANNIS_API EntityHandle {
	private:
		std::shared_ptr<WorldCoordinator> m_world;
	
	public:
		EntityHandle() = default;
		EntityHandle(std::shared_ptr<WorldCoordinator> p_world);/* : m_world(p_world) {
			entity = p_world->CreateEntity();
		}*/

		~EntityHandle() = default;
		
		Entity entity;
		
		void Destroy();

		template<typename ComponentType, typename ...ComponentArgs>
		void AddComponent(ComponentArgs&& ...Args);

		template<typename ComponentType>
		void RemoveComponent();

		template<typename ComponentType>
		ComponentType& GetComponent();
	};

	template<typename ComponentType, typename ...ComponentArgs>
	inline void EntityHandle::AddComponent(ComponentArgs && ...Args) {
		m_world->AddComponent<ComponentType>(entity, std::forward<ComponentArgs>(Args)...);
	}

	template<typename ComponentType>
	inline void EntityHandle::RemoveComponent() {
		m_world->RemoveComponent<ComponentType>(entity);
	}

	template<typename ComponentType>
	inline ComponentType& EntityHandle::GetComponent() {
		return m_world->GetComponent<ComponentType>(entity);
	}
}