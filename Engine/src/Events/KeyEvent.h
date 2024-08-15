#include "ccpch.h"
#include "Core/Core.h"
#include "Event.h"

namespace Cannis {
	class CANNIS_API KeyEvent : public Event {
	public:
		inline int GetKeyCode() const { return m_keyCode; }
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:
		KeyEvent(int p_keyCode) : m_keyCode(p_keyCode) {}

		int m_keyCode;
	};

	class CANNIS_API KeyPressedEvent : public KeyEvent {
	public:
		KeyPressedEvent(int p_keyCode, int p_repeatCount) : KeyEvent(p_keyCode), m_repeatCount(p_repeatCount) {}
		inline int GetRepeatCount() { return m_repeatCount; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "Key pressed event: " << m_keyCode << " (Repeated: " << m_repeatCount << ")";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)

	private:
		int m_repeatCount;
	};

	class CANNIS_API KeyReleasedEvent : public KeyEvent {
	public: 
		KeyReleasedEvent(int p_keyCode) : KeyEvent(p_keyCode) {}
		std::string ToString() const override {
			std::stringstream ss;
			ss << "Key released event: " << m_keyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};
}