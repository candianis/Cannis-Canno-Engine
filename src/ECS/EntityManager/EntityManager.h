#pragma once

#include "../Entity/Entity.h"

#include <bitset>
#include <queue>
#include <unordered_map>

const uint32_t maxEntities = 100;
const uint8_t maxComponents = 32;

using Signature = std::bitset<maxComponents>;
using std::unordered_map;
using std::queue;


class EntityManager {
public: 
	// @brief
	EntityManager();

	Entity createEntity();

	// @brief 
	// @param p_entity Entity to destroy
	void DestroyEntity(const Entity& p_entity);



private:
	// @brief
	std::queue<uint32_t> m_availableIDs;

	// @brief 
	unordered_map<uint32_t, Signature> m_entitySignatures;

	// @brief
	uint32_t m_currentEntityAmount;
};

