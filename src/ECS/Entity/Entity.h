#pragma once

#include "../Registry/Registry.h"
#include "../../Utilities/Signature/Signature.h"
#include "../Component/Types/Transform.h"

#include <bitset>
#include <cstdint>
#include <string>
#include <memory>

using std::uint32_t;
using std::uint8_t;
using std::string;
using std::shared_ptr;

class Registry;

class Entity {
public:
	string name;

	Transform transform;

	Entity(uint32_t ID);
	Entity(const Entity& entity);
	uint32_t getID() const;
	void kill() const;

	Entity& operator =(const Entity& other) = default;
	bool operator ==(const Entity& other) const { return m_ID == other.m_ID; }
	bool operator !=(const Entity& other) const { return m_ID != other.m_ID; }

	template <typename TComponent, typename ...TArgs> void addComponent(TArgs&& ...Args);
	template <typename TComponent> void removeComponent();
	template <typename TComponent> bool hasComponent() const;
	template <typename TComponent> TComponent& getComponent() const;

private:
	// @brief 
	uint32_t m_ID;
};

template<typename TComponent, typename ...TArgs>
inline void Entity::addComponent(TArgs && ...Args) {
	Registry::getInstance().addComponent<TComponent>(m_ID, std::forward<TArgs>(Args)...);
}

template<typename TComponent>
inline void Entity::removeComponent() {
	Registry::removeComponent<TComponent>(m_ID);
}

template<typename TComponent>
inline bool Entity::hasComponent() const {
	return Registry::hasComponent<TComponent>(m_ID);
}

template<typename TComponent>
inline TComponent& Entity::getComponent() const {
	return Registry::getComponent<TComponent>(m_ID);
}
