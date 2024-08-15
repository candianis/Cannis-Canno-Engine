#include "ccpch.h"
#include "ApplicationEvent.h"

namespace Cannis {
	std::string WindowResizeEvent::ToString() const {
		std::stringstream ss;
		ss << "WindowResizeEvent: " << m_width << ", " << m_height;
		return ss.str();
	}
}
