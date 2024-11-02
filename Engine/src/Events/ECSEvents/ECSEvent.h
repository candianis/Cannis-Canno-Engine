#pragma once

#include "Core/Core.h"
#include "Events/SysEvent.h"
#include "ECS/Entity/Entity.h"
#include "ECS/ECSOptions.h"

namespace Cannis {
	class EntityDestroyedEvent : public SysEvent {
	public:
		EntityDestroyedEvent(const Entity& p_entity) : m_entityID(p_entity.GetID()) {}
		~EntityDestroyedEvent() = default;

		inline uint32_t GetEntityID() const { return m_entityID; }
		inline EventType GetType() const override { return EventType::EntityDestroyed; }
		inline EventCategory GetCategory() const override { return EventCategory::ECECS; }
		std::string ToString() const override;

	private:
		uint32_t m_entityID;
	};

	class CANNIS_API SignatureChangedEvent : public SysEvent {
	public:
		SignatureChangedEvent(const Entity& p_entity, const Signature& p_signature) : m_entity(p_entity), m_newSignature(p_signature) {}
		~SignatureChangedEvent() = default;

		inline const Entity& GetEntity() const { return m_entity; }
		inline const Signature& GetSignature() const { return m_newSignature; }
		inline EventType GetType() const override { return EventType::SignatureChanged; }
		inline EventCategory GetCategory() const override { return EventCategory::ECECS; }
		std::string ToString() const override;

	private:
		Entity m_entity;
		Signature m_newSignature;
	};
}