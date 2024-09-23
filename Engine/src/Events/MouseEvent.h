#pragma once 

#include "ccpch.h"
#include "Core/Core.h"
#include "Event.h"

namespace Cannis {
	class CANNIS_API MouseMovedEvent : public Event {
	public:
		MouseMovedEvent(float x, float y) : m_mouseX(x), m_mouseY(y) {}

		inline float GetX() const { return m_mouseX; }
		inline float GetY() const { return m_mouseY; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "Mouse Moved Event: " << m_mouseX << ", " << m_mouseY;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_mouseX, m_mouseY;
	};

	class CANNIS_API MouseScrolledEvent : public Event {
	public:
		MouseScrolledEvent() {}
		MouseScrolledEvent(float p_xOffset, float p_yOffset) : m_xOffset(p_xOffset), m_yOffset(p_yOffset) {}

		inline float GetXOffset() const { return m_xOffset; }
		inline float GetYOffset() const { return m_yOffset; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "Mouse scrolled event: " << m_xOffset << ", " << m_yOffset;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	private:
		float m_xOffset, m_yOffset;
	};

	class CANNIS_API MouseButtonEvent : public Event {
	public:
		inline int GetMouseButton() const { return m_button; }
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	protected:
		MouseButtonEvent(int p_button) : m_button(p_button) {}
		int m_button;
	};

	class CANNIS_API MouseButtonPressedEvent : public MouseButtonEvent {
	public: 
		MouseButtonPressedEvent(int p_button) : MouseButtonEvent(p_button) {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "Mouse button pressed: " << m_button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class CANNIS_API MouseButtonReleasedEvent : public MouseButtonEvent {
	public: 
		MouseButtonReleasedEvent(int p_button) : MouseButtonEvent(p_button) {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "Mouse button released: " << m_button;
			return ss.str();
		}
	};
}