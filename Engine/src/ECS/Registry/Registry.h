#pragma once

#include "../Entity/Entity.h"
#include "../Component/Component.h"
#include "../System/System.h"
#include "../../Utilities/Pool/ComponentPool.h"
#include "../../Utilities/Interface/IPool.h"
#include "../../Utilities/Signature/Signature.h"

#include <iostream>
#include <cstdint>
#include <memory>
#include <vector>
#include <deque>
#include <unordered_map>
#include <typeindex>

using std::uint32_t;
using std::shared_ptr;
using std::unique_ptr;
using std::vector;
using std::deque;
using std::unordered_map;
using std::type_index;

class Entity;
class System;

class Registry {
private:
	Registry();

	// @brief Amount of entities that are currently in the scene
	static uint32_t m_existingEntities;

	/// -----	Entity	-----///
	// @brief List of pointers to all the entities in the scene
	static vector<Entity> m_entities;

	// @brief Queue of available IDs from destroyed entities
	static deque<uint32_t> m_reusableIDs;

	/// -----	Component	-----///

	// @brief Vector index = component type id
	//Pool index = entity id
	static vector<shared_ptr<IPool>> m_componentPools;

	static vector<Signature> m_entityComponentSignatures;

	// ----- Systems ----- //
	// @brief 
	static unordered_map<type_index, shared_ptr<System>> m_systems;

public:
	~Registry() = default;
// Note: Scott Meyers mentions in his Effective Modern
//       C++ book, that deleted functions should generally
//       be public as it results in better error messages
//       due to the compilers behavior to check accessibility
//       before deleted status
	Registry(const Registry&) = delete;
	Registry(Registry&&) = delete;
	Registry& operator =(const Registry&) = delete;
	Registry& operator =(Registry&&) = delete;

	static Registry& getInstance();

	static void update();

	static shared_ptr<Entity> createEntity();
	static void killEntity(const shared_ptr<Entity>& p_entity);

	//Component management
	// @brief Add a component to an Entity
	// @param p_entity Entity that will receive the new component
	// @param args Parameters for the component's constructor
	template <typename TComponent, typename ...TArgs> static void addComponent(const uint32_t p_entityID, TArgs&& ...args);

	// @brief Remove a component from an Entity
	// @param p_entity Entity that will lose a component
	template <typename TComponent> static void removeComponent(const uint32_t p_entityID);
	
	// @brief Check if an entity has a certain component through its type
	// @param p_entity Entity that will be used to see if it has a particular component
	// @return If the Entity already has that type of component
	template <typename TComponent> static bool hasComponent(const uint32_t p_entityID);

	// @brief Get a reference to a particular component from an Entity
	// @param p_entity Entity from which the component will be obtained
	// @return Reference to the component type of an Entity
	template <typename TComponent> static TComponent& getComponent(const uint32_t p_entityID);

	//System management
	// @brief Adds a new system to the registry so that it may be called each frame. More than one system of the same type cannot be added
	// @param args Parameters needed for the system's constructor 
	template <typename TSystem, typename ...TArgs> static void addSystem(TArgs&& ...args);
	
	// @brief Removes from the registry a system through its type
	template <typename TSystem> static void removeSystem();
	
	// @brief Checks if the registry already has certain type of system
	// @return If the Registry already has that system 
	template <typename TSystem> static bool hasSystem();
	
	// @brief Get a reference of a system through its type
	// @returns Reference to the system the registry has
	template <typename TSystem> static shared_ptr<TSystem>& getSystem();

	// @brief Checks the component signature of an entity and adds the entity to the systems that are interested in it
	static void addEntityToSystem(Entity entity);

	// @brief Remove entities from the systems
	static void removeEntityFromSystems(Entity entity);
};

template<typename TComponent, typename ...TArgs>
void Registry::addComponent(const uint32_t p_entityID, TArgs && ...args) {
	// Component<TComponent>::GetId();
	const uint32_t componentID = Component<TComponent>().GetID();
	
	if (componentID >= m_componentPools.size()) {
		m_componentPools.resize(componentID + 1, nullptr);
	}

	if (!m_componentPools[componentID]) {
		std::shared_ptr<ComponentPool<TComponent>> newComponentPool = std::make_shared<ComponentPool<TComponent>>();
		m_componentPools[componentID] = newComponentPool;
	}

	std::shared_ptr<ComponentPool<TComponent>> componentPool = std::static_pointer_cast<ComponentPool<TComponent>>(m_componentPools[componentID]);

	TComponent newComponent(std::forward<TArgs>(args)...);

	componentPool->set(p_entityID, newComponent);

	m_entityComponentSignatures[p_entityID]->set(componentID);

	std::cout << "COMPONENT ID = " << componentID << " --> Pool Size: " << componentPool->getSize() << std::endl;
}

template<typename TComponent>
void Registry::removeComponent(const uint32_t p_entityID) {
	const uint32_t componentID = Component<TComponent>().GetID();

	//Remove the component from the component list for that entity
	shared_ptr<ComponentPool<TComponent>> componentPool = std::static_pointer_cast<ComponentPool<TComponent>>(m_componentPools[componentID]);
	componentPool->remove(p_entityID);

	//Set this component signature for that entity to false
	m_entityComponentSignatures[p_entityID]->set(componentID, false);

	std::cout << "Component id " << componentID << " was removed from entity id: " << p_entityID << std::endl;
}

template<typename TComponent>
bool Registry::hasComponent(const uint32_t p_entityID) {
	const uint32_t componentID = Component<TComponent>().GetID();

	return m_entityComponentSignatures[p_entityID]->hasComponent(componentID);
}

template<typename TComponent>
TComponent& Registry::getComponent(const uint32_t p_entityID) {
	// TODO: Replace this line with a dictionary<ComponentType, uint> so it is easier to obtain the componentID
	const uint32_t componentID = Component<TComponent>().GetID();
	auto componentPool = std::static_pointer_cast<ComponentPool<TComponent>>(m_componentPools[componentID]);

	return componentPool->get(p_entityID);
}

template<typename TSystem, typename ...TArgs>
void Registry::addSystem(TArgs && ...args) {
	shared_ptr<TSystem> newSystem = std::make_shared<TSystem>(std::forward<TArgs>(args)...);
	m_systems.insert(std::make_pair(std::type_index(typeid(TSystem)), newSystem));
}

template<typename TSystem>
void Registry::removeSystem() {
	auto system = m_systems.find(std::type_index(typeid(TSystem)));
	m_systems.erase(system);
}

template<typename TSystem>
bool Registry::hasSystem() {
	return m_systems.find(std::type_index(typeid(TSystem))) != m_systems.end();
}

template<typename TSystem>
inline shared_ptr<TSystem>& Registry::getSystem() {
	auto system = m_systems.find(std::type_index(typeid(TSystem)));
	return system->second;
}
