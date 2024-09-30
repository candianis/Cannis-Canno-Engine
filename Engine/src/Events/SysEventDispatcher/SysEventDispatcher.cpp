#include "ccpch.h"
#include "SysEventDispatcher.h"

namespace Cannis {
	void SysEventDispatcher::Subscribe(const EventType& type, Eventfunc&& p_func) {
		m_observers[type].push_back(p_func);
	}

	void SysEventDispatcher::EmitEvent(const SysEvent& p_event) const {
		// If there isnt a single observer for a given type then 
		if (m_observers.find(p_event.GetType()) == m_observers.end()) {
			return;
		}

		auto&& observers = m_observers.at(p_event.GetType());

		for (auto&& observer : observers) {
			observer(p_event);
		}
	}
}
