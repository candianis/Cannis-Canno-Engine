#include "ccpch.h"
#include "Subsystem.h"
#include "Events/ECSEvents/ECSEvent.h"

namespace Cannis {
	Subsystem::Subsystem(const std::string& p_name)	: m_debugName(p_name) {
		
	}

	Subsystem::~Subsystem()	{

	}

	void Subsystem::OnEntityDestroyed(const SysEvent& p_sysEvent) {
		const EntityDestroyedEvent& curEvent = static_cast<const EntityDestroyedEvent&>(p_sysEvent);
		
		for (std::set<Entity>::iterator i = m_entities.begin(); i != m_entities.end(); i++) {
			if (i->GetID() != curEvent.GetEntityID()) {
				continue;
			}

			m_entities.erase(i);
			break;
		}
	}

	void Subsystem::OnSignatureChanged(const SysEvent& p_sysEvent) {
		const SignatureChangedEvent& curEvent = static_cast<const SignatureChangedEvent&>(p_sysEvent);


		if ((curEvent.GetSignature() & m_desiredComponentSignature) == m_desiredComponentSignature) {
			m_entities.insert(curEvent.GetEntity());
			return;
		}

		m_entities.erase(curEvent.GetEntity());
	}
}