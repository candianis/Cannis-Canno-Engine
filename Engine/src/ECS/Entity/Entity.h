#pragma once

#include "ccpch.h"

namespace Cannis {
	class CANNIS_API Entity {
	private:
		uint32_t m_ID;

	public:
		std::string name;

		Entity() = default;
		Entity(const uint32_t& p_ID) : m_ID(p_ID), name("Entity " + m_ID) {}
		Entity(const Entity& p_entity, const uint32_t& p_ID);
		~Entity() = default;

		inline uint32_t GetID() const { return m_ID; }

		Entity& operator =(const Entity& other) = default;
		bool operator ==(const Entity& other) const { return m_ID == other.m_ID; }
		bool operator !=(const Entity& other) const { return m_ID != other.m_ID; }
		bool operator >(const Entity& other) const { return m_ID > other.m_ID; }
		bool operator <(const Entity& other) const { return m_ID < other.m_ID; }
	};
}