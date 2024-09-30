#pragma once

#include "Core/Core.h"
#include "Events/SysEvent.h"
#include "Events/SysEventDispatcher/SysEventDispatcher.h"

namespace Cannis {
	// @brief Engine susbsytems
	class CANNIS_API Subsystem {
	public:
		Subsystem(const std::string& p_name = "Subsystem");
		virtual ~Subsystem();

		virtual void Update() {}
		virtual void Shutdown() {}
		virtual void OnEvent(SysEvent& p_event) {}

		inline const std::string& GetName() const { return m_debugName; }

		virtual void SubscribeToEvent(const std::unique_ptr<SysEventDispatcher>& p_sysEventDispatcher) {}

	protected:
		std::string m_debugName;
	};
}