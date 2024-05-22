#pragma once

#include "../Entity/Entity.h"

#include <queue>
#include <unordered_map>

const uint32_t maxEntities = 100;


using std::unordered_map;
using std::queue;


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
	std::queue<uint32_t> m_availableIDs;

	// @brief 
	unordered_map<uint32_t, Signature> m_entitySignatures;

	// @brief
	uint32_t m_currentEntityAmount;
};