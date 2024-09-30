#pragma once 

#include "ccpch.h"
#include "Core/Core.h"
#include "SysEvent.h"

namespace Cannis {
	class CANNIS_API MouseMovedEvent : public SysEvent {
	public:
		MouseMovedEvent(float x, float y) : m_mouseX(x), m_mouseY(y) {}

		inline float GetX() const { return m_mouseX; }
		inline float GetY() const { return m_mouseY; }


		inline EventType GetType() const override { return EventType::MouseMoved; }
		inline EventCategory GetCategory() const override { return EventCategory::ECMouse; }
		std::string ToString() const override {
			std::stringstream ss;
			ss << "Mouse Moved Event: " << m_mouseX << ", " << m_mouseY;
			return ss.str();
		}

	private:
		float m_mouseX, m_mouseY;
	};

	class CANNIS_API MouseScrolledEvent : public SysEvent {
	public:
		MouseScrolledEvent(float p_xOffset, float p_yOffset) : m_xOffset(p_xOffset), m_yOffset(p_yOffset) {}

		inline float GetXOffset() const { return m_xOffset; }
		inline float GetYOffset() const { return m_yOffset; }

		inline EventType GetType() const override { return EventType::MouseScrolled; }
		inline EventCategory GetCategory() const override { return EventCategory::ECMouse; }
		std::string ToString() const override {
			std::stringstream ss;
			ss << "Mouse scrolled event: " << m_xOffset << ", " << m_yOffset;
			return ss.str();
		}

	private:
		float m_xOffset, m_yOffset;
	};

	class CANNIS_API MouseButtonEvent : public SysEvent {
	public:
		inline int GetMouseButton() const { return m_button; }
		
		inline EventCategory GetCategory() const override { return EventCategory::ECMouse; }

	protected:
		MouseButtonEvent(int p_button) : m_button(p_button) {}
		int m_button;
	};

	class CANNIS_API MouseButtonPressedEvent : public MouseButtonEvent {
	public: 
		MouseButtonPressedEvent(int p_button) : MouseButtonEvent(p_button) {}

		inline EventType GetType() const override { return EventType::MouseButtonPressed; }
		std::string ToString() const override {
			std::stringstream ss;
			ss << "Mouse button pressed: " << m_button;
			return ss.str();
		}
	};

	class CANNIS_API MouseButtonReleasedEvent : public MouseButtonEvent {
	public: 
		MouseButtonReleasedEvent(int p_button) : MouseButtonEvent(p_button) {}

		inline EventType GetType() const override { return EventType::MouseButtonReleased; }
		std::string ToString() const override {
			std::stringstream ss;
			ss << "Mouse button released: " << m_button;
			return ss.str();
		}
	};
}