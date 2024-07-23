#pragma once

#include "../Entity/Entity.h"

#include <queue>
#include <deque>
#include <unordered_map>

const uint32_t maxEntities = 100;

using std::unordered_map;
using std::deque;

class EntityManager {
public: 
	// @brief
	EntityManager();

	// @brief 
	// @returns 
	Entity createEntity();

	// @brief Destroys the 
	// @param p_entityToKill Reference to the Entity that needs to be disposed of
	void killEntity(const Entity& p_entityToKill);

private:
	// @brief
	std::deque<uint32_t> m_reusableIDs;

	// @brief 
	std::vector<Signature> m_entitySignatures;

	// @brief 
	std::vector<Entity> m_entities;

	// @brief
	uint32_t m_existingEntities;
};