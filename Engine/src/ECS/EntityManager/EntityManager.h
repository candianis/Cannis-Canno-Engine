#pragma once

#include "ccpch.h"
#include "ECS/Entity/Entity.h"
#include "ECS/ECSOptions.h"

namespace Cannis {
	
	class CANNIS_API EntityManager {
	public:
		EntityManager();
		~EntityManager();

		Entity& CreateEntity();
		Entity& CreateEntity(std::string p_name);
		void DestroyEntity(const Entity& p_entity);

		void SetSignature(const Entity& p_entity, Signature& p_signature);
		Signature& GetSignature(const Entity& p_entity);

		inline const std::vector<Entity>& GetEntities() const {
			return m_entities;
		}

	private:
		std::vector<Entity> m_entities;
		std::queue<uint32_t> m_availableIDs;
		std::array<Signature, MaxEntities> m_signatures;
	};
}