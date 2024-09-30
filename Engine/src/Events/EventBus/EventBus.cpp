#include "ccpch.h"
#include "EventBus.h"

namespace Cannis {
	EventBus::EventBus() : m_subscribers() {
		CC_CORE_TRACE("Eventbus created");
	}

	EventBus::~EventBus() {
		CC_CORE_TRACE("Eventbus destroyed");
	}
}