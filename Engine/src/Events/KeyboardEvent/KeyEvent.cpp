#include "ccpch.h"
#include "KeyEvent.h"

namespace Cannis {
	KeyPressedEvent::KeyPressedEvent(int p_key) : m_keyCode(p_key) {

	}

	std::string KeyPressedEvent::ToString() const {
		std::stringstream ss;
		ss << "Key pressed event: " << m_keyCode;
		return ss.str();
	}

	KeyReleasedEvent::KeyReleasedEvent(int p_key) : m_keyCode(p_key)	{

	}
	std::string KeyReleasedEvent::ToString() const {
		std::stringstream ss;
		ss << "Key released event: " << m_keyCode;
		return ss.str();
	}
	std::string KeyTypedEvent::ToString() const
	{
		return std::string();
	}
}