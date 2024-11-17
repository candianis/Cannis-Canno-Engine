#include "ccpch.h"
#include "World.h"
#include "ECS/Component/TransformComponent.hpp"

namespace Cannis {
	WorldCoordinator::WorldCoordinator(std::shared_ptr<SysEventDispatcher>& p_sysDispatcher) {
		m_eventDispatcher = p_sysDispatcher;
	}

	WorldCoordinator::~WorldCoordinator() {

	}

	void WorldCoordinator::Init() {
		m_root.Init();
	}

	void WorldCoordinator::Update() {
		m_root.Update();
	}

	void WorldCoordinator::Shutdown() {
		m_root.Shutdown();
	}

	void WorldCoordinator::OnUIRender() {
		m_root.OnUIRender();
	}

	void WorldCoordinator::SubscribeToEvent() {
		m_componentManager.SubscribeToEvent(m_eventDispatcher);
		m_root.SubscribeSystemsToEvents(m_eventDispatcher);
	}

	Entity& WorldCoordinator::CreateEntity() {
		return m_entityManager.CreateEntity();
	}

	Entity& WorldCoordinator::CreateEntity(std::string p_name) {
		return m_entityManager.CreateEntity(p_name);
	}

	void WorldCoordinator::DestroyEntity(const Entity& p_entity) {
		m_entityManager.DestroyEntity(p_entity);

		EntityDestroyedEvent curEvent(p_entity);
		m_eventDispatcher->EmitEvent(curEvent);
	}
}