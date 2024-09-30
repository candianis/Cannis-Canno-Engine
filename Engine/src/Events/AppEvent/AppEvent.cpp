#include "ccpch.h"
#include "AppEvent.h"

namespace Cannis {
	inline std::string WindowResizeEvent::ToString() const {
		std::stringstream ss;
		ss << "WindowResizeEvent: " << m_width << ", " << m_height;
		return ss.str();
	}

	std::string WindowCloseEvent::ToString() const {
		std::stringstream ss;
		ss << "WindowCloseEvent: true";
		return ss.str();
	}

	AppTickEvent::AppTickEvent() {

	}

	AppTickEvent::~AppTickEvent() {

	}

	std::string AppTickEvent::ToString() const {
		std::stringstream ss;
		ss << "Application Tick: ";
		return ss.str();
	}

	AppUpdateEvent::AppUpdateEvent() {

	}

	AppUpdateEvent::~AppUpdateEvent() {

	}

	std::string AppUpdateEvent::ToString() const {
		std::stringstream ss;
		ss << "Application Update: ";
		return ss.str();
	}

	AppRenderEvent::AppRenderEvent() {
	}

	AppRenderEvent::~AppRenderEvent() {

	}
	std::string AppRenderEvent::ToString() const {
		std::stringstream ss;
		ss << "Application Render: ";
		return ss.str();
	}
}