#pragma once

#include "ccpch.h"
#include "Events/SysEvent.h"

namespace Cannis {
	class SysEventDispatcher {
	public:
		using Eventfunc = std::function<void(const SysEvent&)>;

		void Subscribe(const EventType& type, Eventfunc&& p_func);

		void EmitEvent(const SysEvent& p_event) const;

	private:
		std::map<EventType, std::vector<Eventfunc>> m_observers;
	};
}