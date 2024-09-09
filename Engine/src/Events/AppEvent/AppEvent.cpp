#include "ccpch.h"
#include "AppEvent.h"

namespace Cannis {
	AppResizeEvent::AppResizeEvent(unsigned int p_width, unsigned int p_height) {

	}

	AppResizeEvent::~AppResizeEvent() {

	}

	inline std::string AppResizeEvent::ToString() const {
		std::stringstream ss;
		ss << "WindowResizeEvent: " << m_width << ", " << m_height;
		return ss.str();
	}

	AppCloseEvent::AppCloseEvent() {

	}

	AppCloseEvent::~AppCloseEvent() {

	}

	std::string AppCloseEvent::ToString() const {
		std::stringstream ss;
		ss << "WindowCloseEvent: true";
		return ss.str();
	}

	CCAppTickEvent::CCAppTickEvent() {

	}

	CCAppTickEvent::~CCAppTickEvent() {

	}

	std::string CCAppTickEvent::ToString() const {
		std::stringstream ss;
		ss << "Application Tick: ";
		return ss.str();
	}

	CCAppUpdateEvent::CCAppUpdateEvent() {

	}

	CCAppUpdateEvent::~CCAppUpdateEvent() {

	}

	std::string CCAppUpdateEvent::ToString() const {
		std::stringstream ss;
		ss << "Application Update: ";
		return ss.str();
	}

	CCAppRenderEvent::CCAppRenderEvent() {
	}

	CCAppRenderEvent::~CCAppRenderEvent() {

	}
	std::string CCAppRenderEvent::ToString() const {
		std::stringstream ss;
		ss << "Application Render: ";
		return ss.str();
	}
}