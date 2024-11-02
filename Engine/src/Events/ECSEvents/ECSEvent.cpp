#include "ccpch.h"
#include "ECSEvent.h"

namespace Cannis {
	std::string EntityDestroyedEvent::ToString() const {
		std::stringstream ss;
		ss << "Entity to be destroyed is: " << m_entityID;
		return ss.str();
	}

	std::string SignatureChangedEvent::ToString() const {
		std::stringstream ss;
		ss << "Entity " << m_entity.GetID() << " had its signature changed";
		return ss.str();
	}
}