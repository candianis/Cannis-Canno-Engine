#pragma once

#include "ccpch.h"

#include "Subsystem/Subsystem.h"

#include "ECS/EntityManager/EntityManager.h"
#include "ECS/ComponentManager/ComponentManager.h"
#include "Root/Root.h"
#include "Events/SysEventDispatcher/SysEventDispatcher.h"
#include "Events/ECSEvents/ECSEvent.h"

namespace Cannis {
	class CANNIS_API WorldCoordinator {
	private:
		EntityManager m_entityManager;
		ComponentManager m_componentManager;

		// @brief The system manager
		Root m_root;

		std::shared_ptr<SysEventDispatcher> m_eventDispatcher;

	public:
		WorldCoordinator(std::shared_ptr<SysEventDispatcher>& p_eventDispatcher);
		~WorldCoordinator();

		void Init();
		void Update();
		void Shutdown();
		void OnUIRender();

		void SubscribeToEvent();

		//Entity Management
		Entity& CreateEntity();
		void DestroyEntity(const Entity& p_entity);

		//Component Management
		template<typename ComponentType>
		void RegisterComponent();

		template<typename ComponentType>
		void AddComponent(const Entity& p_entity, ComponentType& p_component);

		template<typename ComponentType, typename ...ComponentArgs>
		void AddComponent(const Entity& p_entity, ComponentArgs&& ...Args);

		template<typename ComponentType>
		void RemoveComponent(const Entity& p_entity);

		template<typename ComponentType>
		ComponentType& GetComponent(const Entity& p_entity);

		// ---- System Management
		template<typename SystemType>
		void AddSubsystem();
		
		template<typename SystemType>
		std::shared_ptr<SystemType>& GetSubsystem();

		template<typename SystemType>
		void SetSubsystemSignature(const Signature& p_signature);
	};

	template<typename ComponentType>
	inline void WorldCoordinator::RegisterComponent() {
		m_componentManager.RegisterComponent<ComponentType>();
	}

	template<typename ComponentType>
	inline void WorldCoordinator::AddComponent(const Entity& p_entity, ComponentType& p_component) {
		m_componentManager.AddComponent(p_entity, p_component);
		Signature& curSignature = m_entityManager.GetSignature(p_entity);
		curSignature.set(m_componentManager.GetComponentID<ComponentType>(), true);
		m_entityManager.SetSignature(p_entity, curSignature);

		SignatureChangedEvent curEvent(p_entity, curSignature);
		m_eventDispatcher->EmitEvent(curEvent);
	}

	template<typename ComponentType, typename ...ComponentArgs>
	inline void WorldCoordinator::AddComponent(const Entity& p_entity, ComponentArgs && ...Args) {
		m_componentManager.AddComponent<ComponentType>(p_entity, std::forward<ComponentArgs>(Args)...);
	}

	template<typename ComponentType>
	inline void WorldCoordinator::RemoveComponent(const Entity& p_entity) {
		m_componentManager.RemoveComponent<ComponentType>(p_entity);
		Signature& curSignature = m_entityManager.GetSignature(p_entity);
		curSignature.set(m_componentManager.GetComponentID<ComponentType>(), false);
		m_entityManager.SetSignature(p_entity, curSignature);

		SignatureChangedEvent curEvent(p_entity, curSignature);
		m_eventDispatcher->EmitEvent(curEvent);
	}

	template<typename ComponentType>
	inline ComponentType& WorldCoordinator::GetComponent(const Entity& p_entity) {
		return m_componentManager.GetComponent<ComponentType>(p_entity);
	}
	
	template<typename SystemType>
	inline void WorldCoordinator::AddSubsystem() {
		m_root.AddSubsystem<SystemType>();
	}

	template<typename SystemType>
	inline std::shared_ptr<SystemType>& WorldCoordinator::GetSubsystem() {
		return m_root.GetSubsystem<SystemType>();
	}
	
	template<typename SystemType>
	inline void WorldCoordinator::SetSubsystemSignature(const Signature& p_signature) {
		m_root.SetSubsystemSignature<SystemType>(p_signature);
	}
}